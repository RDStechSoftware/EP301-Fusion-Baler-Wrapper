/*			 - INH83.H -

   Intrinsic functions for the ICCH83
	   
   Version: 1.00 [ICAP]

*/

#ifndef _INTRINS_INCLUDED
#define _INTRINS_INCLUDED

#if __TID__ & 0x8000
#pragma function=intrinsic(0)
#endif

#pragma language = extended

void sleep(void);

void no_operation(void);

void set_interrupt_mask(unsigned char mask);

unsigned char read_e_port(unsigned char *);

void write_e_port(unsigned char *, unsigned char);

void do_byte_eepmov(unsigned char*, unsigned char*, unsigned char);

void do_word_eepmov(unsigned char*, unsigned char*, unsigned short);

unsigned char read_ccr(void);

void write_ccr(unsigned char);

void and_ccr(unsigned char);

void or_ccr(unsigned char);

void xor_ccr(unsigned char);

void *func_stack_base(void);

void disable_max_time(unsigned long);

void _opc(unsigned short);

#if __TID__ & 0x8000
#pragma function=default
#endif

#endif
