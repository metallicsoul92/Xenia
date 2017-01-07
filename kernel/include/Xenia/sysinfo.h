#ifndef SYSINFO_H_
#define SYSINFO_H_


/**
  system info is based off of Linux verison 0.99.15
*/


struct sysinfo{
	long uptime;			/* Seconds since boot */
	unsigned long loads[3];		/* 1, 5, and 15 minute load averages */
	unsigned long totalram;		/* Total usable main memory size */
	unsigned long freeram;		/* Available memory size */
	unsigned long sharedram;	/* Amount of shared memory */
	unsigned long bufferram;	/* Memory used by buffers */
	unsigned long totalswap;	/* Total swap space size */
	unsigned long freeswap;		/* swap space still available */
	unsigned short procs;		/* Number of current processes */
	char _f[22];			/* Pads structure to 64 bytes */
};


#endif //sysinfo.h
