/***************************************************************************
 *                                                                         *
 *  comedi/drivers/unioxx5.c                                               *
 *  Driver for Fastwel UNIOxx-5 (analog and digital i/o) boards.           *
 *                                                                         *
 *  Copyright (C) 2006 Kruchinin Daniil (asgard) [asgard@etersoft.ru]      *
 *                                                                         *
 *  COMEDI - Linux Control and Measurement Device Interface                *
 *  Copyright (C) 1998,2000 David A. Schleef <ds@schleef.org>              *
 *                                                                         *
 *  This program is free software; you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation; either version 2 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  This program is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with this program; if not, write to the Free Software            *
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.              *
 *                                                                         *
 ***************************************************************************/
/*

               
                                                                         
                                                      
               
                   
                                      

                                                              
                 
                                     
                                 
                                                             
                                           
                              

*/

#include "../comedidev.h"
#include <linux/ioport.h>
#include <linux/slab.h>

#define DRIVER_NAME "unioxx5"
#define UNIOXX5_SIZE 0x10
#define UNIOXX5_SUBDEV_BASE 0xA000	/*                           */
#define UNIOXX5_SUBDEV_ODDS 0x400

/*               */
#define MODULE_DIGITAL 0
#define MODULE_OUTPUT_MASK 0x80	/*                     */

/*                           */
#define UNIOXX5_NUM_OF_CHANS 24

/*                          */
#define TxBE  0x10		/*                        */
#define RxCA  0x20		/*                               */
#define Rx2CA 0x40		/*                               */
#define Rx4CA 0x80		/*                               */

/*                   */
#define Rx2CA_ERR_MASK 0x04	/*                         */
#define Rx4CA_ERR_MASK 0x08	/*                         */

/*               */
#define ALL_2_INPUT  0		/*                                      */
#define ALL_2_OUTPUT 1		/*                                       */

/*                                        */
struct unioxx5_subd_priv {
	int usp_iobase;
	/*                                    */
	unsigned char usp_module_type[12];
	/*                                                      */
	unsigned char usp_extra_data[12][4];
	unsigned char usp_prev_wr_val[3];	/*                        */
	unsigned char usp_prev_cn_val[3];	/*                        */
};

static int unioxx5_attach(struct comedi_device *dev,
			  struct comedi_devconfig *it);
static int unioxx5_subdev_write(struct comedi_device *dev,
				struct comedi_subdevice *subdev,
				struct comedi_insn *insn, unsigned int *data);
static int unioxx5_subdev_read(struct comedi_device *dev,
			       struct comedi_subdevice *subdev,
			       struct comedi_insn *insn, unsigned int *data);
static int unioxx5_insn_config(struct comedi_device *dev,
			       struct comedi_subdevice *subdev,
			       struct comedi_insn *insn, unsigned int *data);
static int unioxx5_detach(struct comedi_device *dev);
static int __unioxx5_subdev_init(struct comedi_subdevice *subdev,
				 int subdev_iobase, int minor);
static int __unioxx5_digital_write(struct unioxx5_subd_priv *usp,
				   unsigned int *data, int channel, int minor);
static int __unioxx5_digital_read(struct unioxx5_subd_priv *usp,
				  unsigned int *data, int channel, int minor);
/*                                                                                */
static int __unioxx5_analog_write(struct unioxx5_subd_priv *usp,
				  unsigned int *data, int channel, int minor);
static int __unioxx5_analog_read(struct unioxx5_subd_priv *usp,
				 unsigned int *data, int channel, int minor);
static int __unioxx5_define_chan_offset(int chan_num);
static void __unioxx5_analog_config(struct unioxx5_subd_priv *usp, int channel);

static struct comedi_driver unioxx5_driver = {
	.driver_name = DRIVER_NAME,
	.module = THIS_MODULE,
	.attach = unioxx5_attach,
	.detach = unioxx5_detach
};

static int __init unioxx5_driver_init_module(void)
{
	return comedi_driver_register(&unioxx5_driver);
}

static void __exit unioxx5_driver_cleanup_module(void)
{
	comedi_driver_unregister(&unioxx5_driver);
}

module_init(unioxx5_driver_init_module);
module_exit(unioxx5_driver_cleanup_module);

static int unioxx5_attach(struct comedi_device *dev,
			  struct comedi_devconfig *it)
{
	int iobase, i, n_subd;
	int id, num, ba;

	iobase = it->options[0];

	dev->board_name = DRIVER_NAME;
	dev->iobase = iobase;
	iobase += UNIOXX5_SUBDEV_BASE;

	/*                                                                          */
	for (i = n_subd = 0, ba = iobase; i < 4; i++, ba += UNIOXX5_SUBDEV_ODDS) {
		id = inb(ba + 0xE);
		num = inb(ba + 0xF);

		if (id != 'g' || num != 1)
			continue;

		n_subd++;
	}

	/*                                             */
	if (n_subd < 2) {
		printk(KERN_ERR
		       "your card must has at least 2 'g01' subdevices\n");
		return -1;
	}

	if (alloc_subdevices(dev, n_subd) < 0) {
		printk(KERN_ERR "out of memory\n");
		return -ENOMEM;
	}

	/*                                          */
	for (i = 0; i < n_subd; i++, iobase += UNIOXX5_SUBDEV_ODDS) {
		if (__unioxx5_subdev_init(&dev->subdevices[i], iobase,
					  dev->minor) < 0)
			return -1;
	}

	printk(KERN_INFO "attached\n");
	return 0;
}

static int unioxx5_subdev_read(struct comedi_device *dev,
			       struct comedi_subdevice *subdev,
			       struct comedi_insn *insn, unsigned int *data)
{
	struct unioxx5_subd_priv *usp = subdev->private;
	int channel, type;

	channel = CR_CHAN(insn->chanspec);
	/*                                         */
	type = usp->usp_module_type[channel / 2];

	if (type == MODULE_DIGITAL) {
		if (!__unioxx5_digital_read(usp, data, channel, dev->minor))
			return -1;
	} else {
		if (!__unioxx5_analog_read(usp, data, channel, dev->minor))
			return -1;
	}

	return 1;
}

static int unioxx5_subdev_write(struct comedi_device *dev,
				struct comedi_subdevice *subdev,
				struct comedi_insn *insn, unsigned int *data)
{
	struct unioxx5_subd_priv *usp = subdev->private;
	int channel, type;

	channel = CR_CHAN(insn->chanspec);
	/*                                         */
	type = usp->usp_module_type[channel / 2];

	if (type == MODULE_DIGITAL) {
		if (!__unioxx5_digital_write(usp, data, channel, dev->minor))
			return -1;
	} else {
		if (!__unioxx5_analog_write(usp, data, channel, dev->minor))
			return -1;
	}

	return 1;
}

/*                          */
static int unioxx5_insn_config(struct comedi_device *dev,
			       struct comedi_subdevice *subdev,
			       struct comedi_insn *insn, unsigned int *data)
{
	int channel_offset, flags, channel = CR_CHAN(insn->chanspec), type;
	struct unioxx5_subd_priv *usp = subdev->private;
	int mask = 1 << (channel & 0x07);

	type = usp->usp_module_type[channel / 2];

	if (type != MODULE_DIGITAL) {
		printk(KERN_ERR
		       "comedi%d: channel configuration accessible only for digital modules\n",
		       dev->minor);
		return -1;
	}

	channel_offset = __unioxx5_define_chan_offset(channel);
	if (channel_offset < 0) {
		printk(KERN_ERR
		       "comedi%d: undefined channel %d. channel range is 0 .. 23\n",
		       dev->minor, channel);
		return -1;
	}

	/*                               */
	flags = usp->usp_prev_cn_val[channel_offset - 1];

	switch (*data) {
	case COMEDI_INPUT:
		flags &= ~mask;
		break;
	case COMEDI_OUTPUT:
		flags |= mask;
		break;
	default:
		printk(KERN_ERR "comedi%d: unknown flag\n", dev->minor);
		return -1;
	}

	/*                                                          
                                                            
                                                            
                                                            */
	outb(1, usp->usp_iobase + 0);
	/*                               */
	outb(flags, usp->usp_iobase + channel_offset);
	/*                                                       */
	outb(0, usp->usp_iobase + 0);
	/*                     */
	usp->usp_prev_cn_val[channel_offset - 1] = flags;

	return 0;
}

static int unioxx5_detach(struct comedi_device *dev)
{
	int i;
	struct comedi_subdevice *subdev;
	struct unioxx5_subd_priv *usp;

	for (i = 0; i < dev->n_subdevices; i++) {
		subdev = &dev->subdevices[i];
		usp = subdev->private;
		release_region(usp->usp_iobase, UNIOXX5_SIZE);
		kfree(subdev->private);
	}

	return 0;
}

/*                                           */
static int __unioxx5_subdev_init(struct comedi_subdevice *subdev,
				 int subdev_iobase, int minor)
{
	struct unioxx5_subd_priv *usp;
	int i, to, ndef_flag = 0;

	if (!request_region(subdev_iobase, UNIOXX5_SIZE, DRIVER_NAME)) {
		printk(KERN_ERR "comedi%d: I/O port conflict\n", minor);
		return -EIO;
	}

	usp = kzalloc(sizeof(*usp), GFP_KERNEL);

	if (usp == NULL) {
		printk(KERN_ERR "comedi%d: error! --> out of memory!\n", minor);
		return -1;
	}

	usp->usp_iobase = subdev_iobase;
	printk(KERN_INFO "comedi%d: |", minor);

	/*                        */
	for (i = 0; i < 12; i++) {
		to = 10000;

		__unioxx5_analog_config(usp, i * 2);
		/*                              */
		outb(i + 1, subdev_iobase + 5);
		outb('H', subdev_iobase + 6);	/*                       */
		while (!(inb(subdev_iobase + 0) & TxBE))
			;	/*                                      */
		outb(0, subdev_iobase + 6);

		/*                                                  */
		while (!(inb(subdev_iobase + 0) & Rx2CA)) {
			if (--to <= 0) {
				ndef_flag = 1;
				break;
			}
		}

		if (ndef_flag) {
			usp->usp_module_type[i] = 0;
			ndef_flag = 0;
		} else
			usp->usp_module_type[i] = inb(subdev_iobase + 6);

		printk(" [%d] 0x%02x |", i, usp->usp_module_type[i]);
		udelay(1);
	}

	printk("\n");

	/*                                             */
	subdev->type = COMEDI_SUBD_DIO;
	subdev->private = usp;
	subdev->subdev_flags = SDF_READABLE | SDF_WRITABLE;
	subdev->n_chan = UNIOXX5_NUM_OF_CHANS;
	subdev->maxdata = 0xFFF;
	subdev->range_table = &range_digital;
	subdev->insn_read = unioxx5_subdev_read;
	subdev->insn_write = unioxx5_subdev_write;
	/*                             */
	subdev->insn_config = unioxx5_insn_config;

	printk(KERN_INFO "subdevice configured\n");

	return 0;
}

static int __unioxx5_digital_write(struct unioxx5_subd_priv *usp,
				   unsigned int *data, int channel, int minor)
{
	int channel_offset, val;
	int mask = 1 << (channel & 0x07);

	channel_offset = __unioxx5_define_chan_offset(channel);
	if (channel_offset < 0) {
		printk(KERN_ERR
		       "comedi%d: undefined channel %d. channel range is 0 .. 23\n",
		       minor, channel);
		return 0;
	}

	/*                                */
	val = usp->usp_prev_wr_val[channel_offset - 1];

	if (*data)
		val |= mask;
	else
		val &= ~mask;

	outb(val, usp->usp_iobase + channel_offset);
	/*                          */
	usp->usp_prev_wr_val[channel_offset - 1] = val;

	return 1;
}

/*                              */
static int __unioxx5_digital_read(struct unioxx5_subd_priv *usp,
				  unsigned int *data, int channel, int minor)
{
	int channel_offset, mask = 1 << (channel & 0x07);

	channel_offset = __unioxx5_define_chan_offset(channel);
	if (channel_offset < 0) {
		printk(KERN_ERR
		       "comedi%d: undefined channel %d. channel range is 0 .. 23\n",
		       minor, channel);
		return 0;
	}

	*data = inb(usp->usp_iobase + channel_offset);
	*data &= mask;

	if (channel_offset > 1)
		channel -= 2 << channel_offset;	/*                                                              */
	*data >>= channel;
	return 1;
}

#if 0				/*           */
static void __unioxx5_digital_config(struct unioxx5_subd_priv *usp, int mode)
{
	int i, mask;

	mask = (mode == ALL_2_OUTPUT) ? 0xFF : 0x00;
	printk("COMEDI: mode = %d\n", mask);

	outb(1, usp->usp_iobase + 0);

	for (i = 0; i < 3; i++)
		outb(mask, usp->usp_iobase + i);

	outb(0, usp->usp_iobase + 0);
}
#endif

static int __unioxx5_analog_write(struct unioxx5_subd_priv *usp,
				  unsigned int *data, int channel, int minor)
{
	int module, i;

	module = channel / 2;	/*                                */
	i = (channel % 2) << 1;	/*                                     */

	/*                                             */
	if (!(usp->usp_module_type[module] & MODULE_OUTPUT_MASK)) {
		printk(KERN_ERR
		       "comedi%d: module in position %d with id 0x%0x is for input only!\n",
		       minor, module, usp->usp_module_type[module]);
		return 0;
	}

	__unioxx5_analog_config(usp, channel);
	/*                   */
	usp->usp_extra_data[module][i++] = (unsigned char)(*data & 0x00FF);
	/*                   */
	usp->usp_extra_data[module][i] = (unsigned char)((*data & 0xFF00) >> 8);

	/*                                              */
	/*                                        */
	outb(module + 1, usp->usp_iobase + 5);
	outb('W', usp->usp_iobase + 6);	/*                                 */

	/*                                                           */
	for (i = 0; i < 4; i++) {
		while (!((inb(usp->usp_iobase + 0)) & TxBE))
			;	/*                                      */
		outb(usp->usp_extra_data[module][i], usp->usp_iobase + 6);
	}

	return 1;
}

static int __unioxx5_analog_read(struct unioxx5_subd_priv *usp,
				 unsigned int *data, int channel, int minor)
{
	int module_no, read_ch;
	char control;

	module_no = channel / 2;
	read_ch = channel % 2;	/*                                    */

	/*                                            */
	if (usp->usp_module_type[module_no] & MODULE_OUTPUT_MASK) {
		printk(KERN_ERR
		       "comedi%d: module in position %d with id 0x%02x is for output only",
		       minor, module_no, usp->usp_module_type[module_no]);
		return 0;
	}

	__unioxx5_analog_config(usp, channel);
	/*                                      */
	outb(module_no + 1, usp->usp_iobase + 5);
	outb('V', usp->usp_iobase + 6);	/*                                  */
	control = inb(usp->usp_iobase);	/*                           */

	/*                                                */
	while (!((control = inb(usp->usp_iobase + 0)) & Rx4CA))
		;

	/*                                                       */
	if ((control & Rx4CA_ERR_MASK)) {
		printk("COMEDI: 4 bytes error\n");
		return 0;
	}

	if (read_ch)
		*data = inw(usp->usp_iobase + 6);	/*           */
	else
		*data = inw(usp->usp_iobase + 4);	/*           */

	return 1;
}

/*                                                                  */
static void __unioxx5_analog_config(struct unioxx5_subd_priv *usp, int channel)
{
	int chan_a, chan_b, conf, channel_offset;

	channel_offset = __unioxx5_define_chan_offset(channel);
	conf = usp->usp_prev_cn_val[channel_offset - 1];
	chan_a = chan_b = 1;

	/*                                      */
	if (channel % 2 == 0) {
		chan_a <<= channel & 0x07;
		chan_b <<= (channel + 1) & 0x07;
	} else {
		chan_a <<= (channel - 1) & 0x07;
		chan_b <<= channel & 0x07;
	}

	conf |= chan_a;		/*                        */
	conf &= ~chan_b;	/*                      */

	outb(1, usp->usp_iobase + 0);
	outb(conf, usp->usp_iobase + channel_offset);
	outb(0, usp->usp_iobase + 0);

	usp->usp_prev_cn_val[channel_offset - 1] = conf;
}

/*                                                      
                                                       
                                                       
                                                       
                                                       
                                                      */

static int __unioxx5_define_chan_offset(int chan_num)
{

	if (chan_num < 0 || chan_num > 23)
		return -1;

	return (chan_num >> 3) + 1;
}

MODULE_AUTHOR("Comedi http://www.comedi.org");
MODULE_DESCRIPTION("Comedi low-level driver");
MODULE_LICENSE("GPL");
