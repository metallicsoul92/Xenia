#ifndef _SYS_CDEFS_H
#define _SYS_CDEFS_H 1

#define __xenia_libc 1

typedef char int8;
typedef unsigned char uint8;
typedef short int16;
typedef unsigned short uint16;
typedef int int32;
typedef unsigned int uint32;
typedef long long int64;
typedef unsigned long long uint64;
typedef unsigned long uintptr;
//useful gnu typedef
typedef long ssize_t;

/* This typedefs are defined in */
/* Types used in disk, inode, etc. data structures. */
typedef short          dev_t;	   /* holds (major|minor) device pair */
typedef char           gid_t;	   /* group id */
typedef unsigned long  ino_t; 	   /* i-node number (V3 filesystem) */
typedef unsigned short mode_t;	   /* file type and permissions bits */
typedef short        nlink_t;	   /* number of links to a file */
typedef unsigned long  off_t;	   /* offset within a file */
typedef int            pid_t;	   /* process id (must be signed) */
typedef short          uid_t;	   /* user id */
typedef unsigned long zone_t;	   /* zone number */
typedef unsigned long block_t;	   /* block number */
typedef unsigned long  bit_t;	   /* bit number in a bit map */
typedef unsigned short zone1_t;	   /* zone number for V1 file systems */
typedef unsigned short bitchunk_t; /* collection of bits in a bitmap */

#endif //_SYS_CDEFS_H
