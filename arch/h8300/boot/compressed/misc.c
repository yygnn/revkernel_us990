/*
                                    
  
                                                           
                     
  
                                                            
  
                                           
 */

#include <asm/uaccess.h>

/*
                    
 */

#define OF(args)  args
#define STATIC static

#undef memset
#undef memcpy
#define memzero(s, n)     memset ((s), 0, (n))

typedef unsigned char  uch;
typedef unsigned short ush;
typedef unsigned long  ulg;

#define WSIZE 0x8000		/*                                   */
				/*                    */

static uch *inbuf;	     /*              */
static uch window[WSIZE];    /*                       */

static unsigned insize = 0;  /*                      */
static unsigned inptr = 0;   /*                                             */
static unsigned outcnt = 0;  /*                        */

/*                */
#define ASCII_FLAG   0x01 /*                                     */
#define CONTINUATION 0x02 /*                                                 */
#define EXTRA_FIELD  0x04 /*                                */
#define ORIG_NAME    0x08 /*                                       */
#define COMMENT      0x10 /*                                 */
#define ENCRYPTED    0x20 /*                              */
#define RESERVED     0xC0 /*                     */

#define get_byte()  (inptr < insize ? inbuf[inptr++] : fill_inbuf())

/*                      */
#ifdef DEBUG
#  define Assert(cond,msg) {if(!(cond)) error(msg);}
#  define Trace(x) fprintf x
#  define Tracev(x) {if (verbose) fprintf x ;}
#  define Tracevv(x) {if (verbose>1) fprintf x ;}
#  define Tracec(c,x) {if (verbose && (c)) fprintf x ;}
#  define Tracecv(c,x) {if (verbose>1 && (c)) fprintf x ;}
#else
#  define Assert(cond,msg)
#  define Trace(x)
#  define Tracev(x)
#  define Tracevv(x)
#  define Tracec(c,x)
#  define Tracecv(c,x)
#endif

static int  fill_inbuf(void);
static void flush_window(void);
static void error(char *m);

extern char input_data[];
extern int input_len;

static long bytes_out = 0;
static uch *output_data;
static unsigned long output_ptr = 0;

static void error(char *m);

int puts(const char *);

extern int _text;		/*                          */
extern int _end;
static unsigned long free_mem_ptr;
static unsigned long free_mem_end_ptr;

#define HEAP_SIZE             0x10000

#include "../../../../lib/inflate.c"

#define SCR *((volatile unsigned char *)0xffff8a)
#define TDR *((volatile unsigned char *)0xffff8b)
#define SSR *((volatile unsigned char *)0xffff8c)

int puts(const char *s)
{
	return 0;
}

void* memset(void* s, int c, size_t n)
{
	int i;
	char *ss = (char*)s;

	for (i=0;i<n;i++) ss[i] = c;
	return s;
}

void* memcpy(void* __dest, __const void* __src,
			    size_t __n)
{
	int i;
	char *d = (char *)__dest, *s = (char *)__src;

	for (i=0;i<__n;i++) d[i] = s[i];
	return __dest;
}

/*                                                                            
                                                                      
                                          
 */
static int fill_inbuf(void)
{
	if (insize != 0) {
		error("ran out of input data");
	}

	inbuf = input_data;
	insize = input_len;
	inptr = 1;
	return inbuf[0];
}

/*                                                                            
                                                                            
                                         
 */
static void flush_window(void)
{
    ulg c = crc;         /*                    */
    unsigned n;
    uch *in, *out, ch;

    in = window;
    out = &output_data[output_ptr];
    for (n = 0; n < outcnt; n++) {
	    ch = *out++ = *in++;
	    c = crc_32_tab[((int)c ^ ch) & 0xff] ^ (c >> 8);
    }
    crc = c;
    bytes_out += (ulg)outcnt;
    output_ptr += (ulg)outcnt;
    outcnt = 0;
}

static void error(char *x)
{
	puts("\n\n");
	puts(x);
	puts("\n\n -- System halted");

	while(1);	/*      */
}

#define STACK_SIZE (4096)
long user_stack [STACK_SIZE];
long* stack_start = &user_stack[STACK_SIZE];

void decompress_kernel(void)
{
	output_data = 0;
	output_ptr = (unsigned long)0x400000;
	free_mem_ptr = (unsigned long)&_end;
	free_mem_end_ptr = free_mem_ptr + HEAP_SIZE;

	makecrc();
	puts("Uncompressing Linux... ");
	gunzip();
	puts("Ok, booting the kernel.\n");
}
