/*                                        */

/*          */
#define _PAGE_HASHPTE	0x0400 /*                                      */
#define _PAGE_SECONDARY 0x8000 /*                                      */
#define _PAGE_GROUP_IX  0x7000 /*                                   */
#define _PAGE_F_SECOND  _PAGE_SECONDARY
#define _PAGE_F_GIX     _PAGE_GROUP_IX
#define _PAGE_SPECIAL	0x10000 /*                        */

/*                                               */
#define _PAGE_HPTEFLAGS (_PAGE_BUSY | _PAGE_HASHPTE | \
			 _PAGE_SECONDARY | _PAGE_GROUP_IX)

/*                                   */
#define PTE_RPN_SHIFT	(17)

