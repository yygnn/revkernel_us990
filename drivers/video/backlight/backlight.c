/*
 * Backlight Lowlevel Control Abstraction
 *
 * Copyright (C) 2003,2004 Hewlett-Packard Company
 *
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/backlight.h>
#include <linux/notifier.h>
#include <linux/ctype.h>
#include <linux/err.h>
#include <linux/fb.h>
#include <linux/slab.h>

#ifdef CONFIG_PMAC_BACKLIGHT
#include <asm/backlight.h>
#endif

static const char *const backlight_types[] = {
	[BACKLIGHT_RAW] = "raw",
	[BACKLIGHT_PLATFORM] = "platform",
	[BACKLIGHT_FIRMWARE] = "firmware",
};

#if defined(CONFIG_FB) || (defined(CONFIG_FB_MODULE) && \
			   defined(CONFIG_BACKLIGHT_CLASS_DEVICE_MODULE))
/*                                                                    
                                                                         
                                                            
 */
static int fb_notifier_callback(struct notifier_block *self,
				unsigned long event, void *data)
{
	struct backlight_device *bd;
	struct fb_event *evdata = data;

	/*                                                                */
	if (event != FB_EVENT_BLANK && event != FB_EVENT_CONBLANK)
		return 0;

	bd = container_of(self, struct backlight_device, fb_notif);
	mutex_lock(&bd->ops_lock);
	if (bd->ops)
		if (!bd->ops->check_fb ||
		    bd->ops->check_fb(bd, evdata->info)) {
			bd->props.fb_blank = *(int *)evdata->data;
			if (bd->props.fb_blank == FB_BLANK_UNBLANK)
				bd->props.state &= ~BL_CORE_FBBLANK;
			else
				bd->props.state |= BL_CORE_FBBLANK;
			backlight_update_status(bd);
		}
	mutex_unlock(&bd->ops_lock);
	return 0;
}

static int backlight_register_fb(struct backlight_device *bd)
{
	memset(&bd->fb_notif, 0, sizeof(bd->fb_notif));
	bd->fb_notif.notifier_call = fb_notifier_callback;

	return fb_register_client(&bd->fb_notif);
}

static void backlight_unregister_fb(struct backlight_device *bd)
{
	fb_unregister_client(&bd->fb_notif);
}
#else
static inline int backlight_register_fb(struct backlight_device *bd)
{
	return 0;
}

static inline void backlight_unregister_fb(struct backlight_device *bd)
{
}
#endif /*           */

static void backlight_generate_event(struct backlight_device *bd,
				     enum backlight_update_reason reason)
{
	char *envp[2];

	switch (reason) {
	case BACKLIGHT_UPDATE_SYSFS:
		envp[0] = "SOURCE=sysfs";
		break;
	case BACKLIGHT_UPDATE_HOTKEY:
		envp[0] = "SOURCE=hotkey";
		break;
	default:
		envp[0] = "SOURCE=unknown";
		break;
	}
	envp[1] = NULL;
	kobject_uevent_env(&bd->dev.kobj, KOBJ_CHANGE, envp);
	sysfs_notify(&bd->dev.kobj, NULL, "actual_brightness");
}

static ssize_t backlight_show_power(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct backlight_device *bd = to_backlight_device(dev);

	return sprintf(buf, "%d\n", bd->props.power);
}

static ssize_t backlight_store_power(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	int rc;
	struct backlight_device *bd = to_backlight_device(dev);
	unsigned long power;

	rc = kstrtoul(buf, 0, &power);
	if (rc)
		return rc;

	rc = -ENXIO;
	mutex_lock(&bd->ops_lock);
	if (bd->ops) {
		pr_debug("backlight: set power to %lu\n", power);
		if (bd->props.power != power) {
			bd->props.power = power;
			backlight_update_status(bd);
		}
		rc = count;
	}
	mutex_unlock(&bd->ops_lock);

	return rc;
}

static ssize_t backlight_show_brightness(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct backlight_device *bd = to_backlight_device(dev);

	return sprintf(buf, "%d\n", bd->props.brightness);
}

static ssize_t backlight_store_brightness(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	int rc;
	struct backlight_device *bd = to_backlight_device(dev);
	unsigned long brightness;

	rc = kstrtoul(buf, 0, &brightness);
	if (rc)
		return rc;

	rc = -ENXIO;

	mutex_lock(&bd->ops_lock);
	if (bd->ops) {
		if (brightness > bd->props.max_brightness)
			rc = -EINVAL;
		else {
			pr_debug("backlight: set brightness to %lu\n",
				 brightness);
			bd->props.brightness = brightness;
			backlight_update_status(bd);
			rc = count;
		}
	}
	mutex_unlock(&bd->ops_lock);

	backlight_generate_event(bd, BACKLIGHT_UPDATE_SYSFS);

	return rc;
}

static ssize_t backlight_show_type(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct backlight_device *bd = to_backlight_device(dev);

	return sprintf(buf, "%s\n", backlight_types[bd->props.type]);
}

static ssize_t backlight_show_max_brightness(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct backlight_device *bd = to_backlight_device(dev);

	return sprintf(buf, "%d\n", bd->props.max_brightness);
}

static ssize_t backlight_show_actual_brightness(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	int rc = -ENXIO;
	struct backlight_device *bd = to_backlight_device(dev);

	mutex_lock(&bd->ops_lock);
	if (bd->ops && bd->ops->get_brightness)
		rc = sprintf(buf, "%d\n", bd->ops->get_brightness(bd));
	mutex_unlock(&bd->ops_lock);

	return rc;
}

static struct class *backlight_class;

#if defined(CONFIG_MACH_LGE_BACKLIGHT_SUPPORT)
struct backlight_device *get_backlight_device()
{
	struct class_dev_iter iter;
	struct backlight_device *bd = NULL;
	struct device *dev = NULL;

	if (!backlight_class)
		return NULL;
	if (!backlight_class->p) {
		WARN(1, "%s called for class '%s' before it was initialized",
						__func__, backlight_class->name);
		return NULL;
	}

	class_dev_iter_init(&iter, backlight_class, NULL, NULL);
	dev = class_dev_iter_next(&iter);
	if (dev) {
		bd = to_backlight_device(dev);
		pr_info("%s: backlight device name is %s", __func__,
						(bd) ? bd->dev.kobj.name : "NULL");
	}
	class_dev_iter_exit(&iter);
	return bd;
}
#endif

static int backlight_suspend(struct device *dev, pm_message_t state)
{
	struct backlight_device *bd = to_backlight_device(dev);

	mutex_lock(&bd->ops_lock);
	if (bd->ops && bd->ops->options & BL_CORE_SUSPENDRESUME) {
		bd->props.state |= BL_CORE_SUSPENDED;
		backlight_update_status(bd);
	}
	mutex_unlock(&bd->ops_lock);

	return 0;
}

static int backlight_resume(struct device *dev)
{
	struct backlight_device *bd = to_backlight_device(dev);

	mutex_lock(&bd->ops_lock);
	if (bd->ops && bd->ops->options & BL_CORE_SUSPENDRESUME) {
		bd->props.state &= ~BL_CORE_SUSPENDED;
		backlight_update_status(bd);
	}
	mutex_unlock(&bd->ops_lock);

	return 0;
}

static void bl_device_release(struct device *dev)
{
	struct backlight_device *bd = to_backlight_device(dev);
	kfree(bd);
}

static struct device_attribute bl_device_attributes[] = {
	__ATTR(bl_power, 0644, backlight_show_power, backlight_store_power),
	__ATTR(brightness, 0644, backlight_show_brightness,
		     backlight_store_brightness),
	__ATTR(actual_brightness, 0444, backlight_show_actual_brightness,
		     NULL),
	__ATTR(max_brightness, 0444, backlight_show_max_brightness, NULL),
	__ATTR(type, 0444, backlight_show_type, NULL),
	__ATTR_NULL,
};

/* 
                                                                            
                
                                      
  
                                                                               
                                            
 */
void backlight_force_update(struct backlight_device *bd,
			    enum backlight_update_reason reason)
{
	mutex_lock(&bd->ops_lock);
	if (bd->ops && bd->ops->get_brightness)
		bd->props.brightness = bd->ops->get_brightness(bd);
	mutex_unlock(&bd->ops_lock);
	backlight_generate_event(bd, reason);
}
EXPORT_SYMBOL(backlight_force_update);

/* 
                                                                  
                            
                                                                        
                                    
                                          
                                                                         
                                                      
                                            
  
                                                                
                                                        
 */
struct backlight_device *backlight_device_register(const char *name,
	struct device *parent, void *devdata, const struct backlight_ops *ops,
	const struct backlight_properties *props)
{
	struct backlight_device *new_bd;
	int rc;

	pr_debug("backlight_device_register: name=%s\n", name);

	new_bd = kzalloc(sizeof(struct backlight_device), GFP_KERNEL);
	if (!new_bd)
		return ERR_PTR(-ENOMEM);

	mutex_init(&new_bd->update_lock);
	mutex_init(&new_bd->ops_lock);

	new_bd->dev.class = backlight_class;
	new_bd->dev.parent = parent;
	new_bd->dev.release = bl_device_release;
	dev_set_name(&new_bd->dev, name);
	dev_set_drvdata(&new_bd->dev, devdata);

	/*                        */
	if (props) {
		memcpy(&new_bd->props, props,
		       sizeof(struct backlight_properties));
		if (props->type <= 0 || props->type >= BACKLIGHT_TYPE_MAX) {
			WARN(1, "%s: invalid backlight type", name);
			new_bd->props.type = BACKLIGHT_RAW;
		}
	} else {
		new_bd->props.type = BACKLIGHT_RAW;
	}

	rc = device_register(&new_bd->dev);
	if (rc) {
		kfree(new_bd);
		return ERR_PTR(rc);
	}

	rc = backlight_register_fb(new_bd);
	if (rc) {
		device_unregister(&new_bd->dev);
		return ERR_PTR(rc);
	}

	new_bd->ops = ops;

#ifdef CONFIG_PMAC_BACKLIGHT
	mutex_lock(&pmac_backlight_mutex);
	if (!pmac_backlight)
		pmac_backlight = new_bd;
	mutex_unlock(&pmac_backlight_mutex);
#endif

	return new_bd;
}
EXPORT_SYMBOL(backlight_device_register);

/* 
                                                                       
                                                                 
  
                                                                            
 */
void backlight_device_unregister(struct backlight_device *bd)
{
	if (!bd)
		return;

#ifdef CONFIG_PMAC_BACKLIGHT
	mutex_lock(&pmac_backlight_mutex);
	if (pmac_backlight == bd)
		pmac_backlight = NULL;
	mutex_unlock(&pmac_backlight_mutex);
#endif
	mutex_lock(&bd->ops_lock);
	bd->ops = NULL;
	mutex_unlock(&bd->ops_lock);

	backlight_unregister_fb(bd);
	device_unregister(&bd->dev);
}
EXPORT_SYMBOL(backlight_device_unregister);

static void __exit backlight_class_exit(void)
{
	class_destroy(backlight_class);
}

static int __init backlight_class_init(void)
{
	backlight_class = class_create(THIS_MODULE, "backlight");
	if (IS_ERR(backlight_class)) {
		printk(KERN_WARNING "Unable to create backlight class; errno = %ld\n",
				PTR_ERR(backlight_class));
		return PTR_ERR(backlight_class);
	}

	backlight_class->dev_attrs = bl_device_attributes;
	backlight_class->suspend = backlight_suspend;
	backlight_class->resume = backlight_resume;
	return 0;
}

/*
                                                                  
                                                                      
 */
postcore_initcall(backlight_class_init);
module_exit(backlight_class_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jamey Hicks <jamey.hicks@hp.com>, Andrew Zabolotny <zap@homelink.ru>");
MODULE_DESCRIPTION("Backlight Lowlevel Control Abstraction");
