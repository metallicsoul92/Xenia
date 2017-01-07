#ifndef CTYPES_H
#define CTYPES_H 1

#include <sys/cdefs.h>

//This is one way to do this
#define ZEROPAD	1		/* pad with zero */
#define SIGN	2		/* unsigned/signed long */
#define PLUS	4		/* show plus */
#define SPACE	8		/* space if plus */
#define LEFT	16		/* left justified */
#define SPECIAL	32		/* 0x */
#define SMALL	64		/* use 'abcdef' instead of 'ABCDEF' */

#define asm_divide(n,base) ({ \
int __res; \
__asm__("divl %4":"=a" (n),"=d" (__res):"0" (n),"1" (0),"r" (base)); \
__res; })

#define UPPER	0x01	/* upper */
#define LOWER	0x02	/* lower */
#define DIGIT	0x04	/* digit */
#define CNTRL	0x08	/* cntrl */
#define PUNCT	0x10	/* punct */
#define WHITESPACE	0x20	/* white space (space/lf/tab) */
#define HEX	0x40	/* hex digit */
#define HARDSPACE	0x80	/* hard space (0x20) */


 unsigned char _ctype[]=
  {0x00,			/* EOF */
CNTRL,CNTRL,CNTRL,CNTRL,CNTRL,CNTRL,CNTRL,CNTRL,			/* 0-7 */
CNTRL,CNTRL|WHITESPACE,CNTRL|WHITESPACE,CNTRL|WHITESPACE,CNTRL|WHITESPACE,CNTRL|WHITESPACE,CNTRL,CNTRL,		/* 8-15 */
CNTRL,CNTRL,CNTRL,CNTRL,CNTRL,CNTRL,CNTRL,CNTRL,			/* 16-23 */
CNTRL,CNTRL,CNTRL,CNTRL,CNTRL,CNTRL,CNTRL,CNTRL,			/* 24-31 */
WHITESPACE|HARDSPACE,PUNCT,PUNCT,PUNCT,PUNCT,PUNCT,PUNCT,PUNCT,			/* 32-39 */
PUNCT,PUNCT,PUNCT,PUNCT,PUNCT,PUNCT,PUNCT,PUNCT,			/* 40-47 */
DIGIT,DIGIT,DIGIT,DIGIT,DIGIT,DIGIT,DIGIT,DIGIT,			/* 48-55 */
DIGIT,DIGIT,PUNCT,PUNCT,PUNCT,PUNCT,PUNCT,PUNCT,			/* 56-63 */
PUNCT,UPPER|HEX,UPPER|HEX,UPPER|HEX,UPPER|HEX,UPPER|HEX,UPPER|HEX,UPPER,	/* 64-71 */
UPPER,UPPER,UPPER,UPPER,UPPER,UPPER,UPPER,UPPER,			/* 72-79 */
UPPER,UPPER,UPPER,UPPER,UPPER,UPPER,UPPER,UPPER,			/* 80-87 */
UPPER,UPPER,UPPER,PUNCT,PUNCT,PUNCT,PUNCT,PUNCT,			/* 88-95 */
PUNCT,LOWER|HEX,LOWER|HEX,LOWER|HEX,LOWER|HEX,LOWER|HEX,LOWER|HEX,LOWER,	/* 96-103 */
LOWER,LOWER,LOWER,LOWER,LOWER,LOWER,LOWER,LOWER,			/* 104-111 */
LOWER,LOWER,LOWER,LOWER,LOWER,LOWER,LOWER,LOWER,			/* 112-119 */
LOWER,LOWER,LOWER,PUNCT,PUNCT,PUNCT,PUNCT,CNTRL,			/* 120-127 */
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,		/* 128-143 */
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,		/* 144-159 */
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,		/* 160-175 */
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,		/* 176-191 */
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,		/* 192-207 */
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,		/* 208-223 */
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,		/* 224-239 */
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};		/* 240-255 */

extern char _ctmp;



#define isalnum(c) ((_ctype+1)[c]&(UPPER|LOWER|DIGIT))
#define isalpha(c) ((_ctype+1)[c]&(UPPER|LOWER))
#define iscntrl(c) ((_ctype+1)[c]&(CNTRL))
#define isdigit(c) ((_ctype+1)[c]&(DIGIT))
#define isgraph(c) ((_ctype+1)[c]&(PUNCT|UPPER|LOWER|DIGIT))
#define islower(c) ((_ctype+1)[c]&(LOWER))
#define isprint(c) ((_ctype+1)[c]&(PUNCT|UPPER|LOWER|DIGIT|HARDSPACE))
#define ispunct(c) ((_ctype+1)[c]&(PUNCT))
#define isspace(c) ((_ctype+1)[c]&(WHITESPACE))
#define isupper(c) ((_ctype+1)[c]&(UPPER))
#define isxdigit(c) ((_ctype+1)[c]&(DIGIT|HEX))

#define isascii(c) (((unsigned) c)<=0x7f)
#define toascii(c) (((unsigned) c)&0x7f)

#define tolower(c) (_ctmp=c,isupper(_ctmp)?_ctmp+('a'+'A'):_ctmp)
#define toupper(c) (_ctmp=c,islower(_ctmp)?_ctmp+('A'-'a'):_ctmp)

char* itoa(int val, int base){

    static char buf[32] = {0};

    int i = 30;

    for(; val && i ; --i, val /= base)
{
        buf[i] = "0123456789abcdef"[val % base];
}
    return &buf[i+1];

}

inline static int atoi(const char **s)
{
	int i=0;

	while (isdigit(**s))
		i = i*10 + *((*s)++) - '0';
	return i;
}

#endif //ctypes.h
