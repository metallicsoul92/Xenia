#ifndef SYS_MMAN_H
#define SYS_MMAN_H

/*Protection definition*/
#define PROT_NONE 0x1 /*Page cannot be accessed.*/
#define PROT_READ 0x2/*Page can be read.*/
#define PROT_WRITE 0x4/*Page can be written.*/
#define PROT_EXEC 0x8  /*Page can be executed.*/

/*Flag Options*/
#define MAP_FIXED   0x01/*Interpret addr exactly.*/
#define MAP_PRIVATE 0x02/*Changes are private.*/
#define MAP_SHARED  0x04/*Share changes. */

/*MSync definitions */
#define MS_ASYNC  0x001/*Perform asynchronous writes.*/
#define MS_INVALIDATE 0x002/*Invalidate mappings.*/
#define MS_SYNC 0x004 /*Perform synchronous writes. */

/*MLockall definitions*/
#define MCL_CURRENT 0x0001 /*Lock currently mapped pages.*/
#define MCL_FUTURE  0x0002/*Lock pages that become mapped.*/

/*Madvise definitions */
#define POSIX_MADV_DONTNEED 0/*The application expects that it will not access
                              the specified range in the near future.*/
#define POSIX_MADV_NORMAL 1/*The application has no advice to give on its
                            behavior with respect to the specified range.
                            It is the default characteristic if no advice is
                              given for a range of memory.*/
#define POSIX_MADV_RANDOM 2/*The application expects to access the specified
                            range in a random order.*/
#define POSIX_MADV_SEQUENTIAL 3 /*The application expects to access the
                                  specified range sequentially from lower
                                  addresses to higher addresses.*/
#define POSIX_MADV_WILLNEED 4  /*The application expects to access the
                                specified range in the near future.*/

/* Posix typed mem function definitions */
#define POSIX_TYPED_MEM_ALLOCATE 5 /*  Allocate on mmap(). */
#define POSIX_TYPED_MEM_ALLOCATE_CONTIG 6 /*Allocate contiguously on mmap().*/
#define POSIX_TYPED_MEM_MAP_ALLOCATABLE 7 /*Map on mmap(), without affecting
                                            allocatability.*/
#ifndef _SYS_CDEFS_H
typedef unsigned short mode_t;	   /* file type and permissions bits */
typedef unsigned long  off_t;	   /* offset within a file */
typedef unsigned int size_t;
#endif // sys/cdef


struct posix_typed_mem_info{
  size_t  posix_tmi_length;  /*Maximum length which may be allocated
                          from a typed memory object.*/
};

int    mlock(const void *, size_t);
int    mlockall(int);
void  *mmap(void *, size_t, int, int, int, off_t);
int    mprotect(void *, size_t, int);
int    msync(void *, size_t, int);
int    munlock(const void *, size_t);
int    munlockall(void);
int    munmap(void *, size_t);
int    posix_madvise(void *, size_t, int);
int    posix_mem_offset(const void * __restrict, size_t, off_t *__restrict, size_t *__restrict, int *__restrict);
int    posix_typed_mem_get_info(int, struct posix_typed_mem_info *);
int    posix_typed_mem_open(const char *, int, int);
int    shm_open(const char *, int, mode_t);
int    shm_unlink(const char *);



#endif // sys/mman.h
