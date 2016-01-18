

#include <sys/types.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
// #include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
// #include <linux/i2c-dev.h>
#include <string.h>
#include <unistd.h>    //sleep
#include <stdint.h>   //uint_8, uint_16, uint_32, etc.

#include "p2.h"

/* ipc data - memory mapped */
typedef	struct {
	uint32_t    sch[_DAYS_PER_WEEK][_NUMBER_OF_CHANNELS][_SCHEDULE_SIZE];	// system schedule
	int			force_update;		// force daemon to update channel
    struct {
    	int 		c_state;		// 0 = off, 1 = on	
		int 		c_mode; 		// Control mode: 0-manual, 1-time, 2-time & sensor, 3-cycle
		int			on_sec ;		// on cycle in seconds
		int 		off_sec;		// off cycle in seconds    
	} c_dat[_NUMBER_OF_CHANNELS];
	struct{
		int			temp;
		int			humidity;
		int			lup_sec;
		int			lup_min;
		int			lup_hour;
		int			lup_wday;
	} s_dat[_NUMBER_OF_SENSORS];

} IPC_DAT;

int main(void){

	IPC_DAT			l, *com_block;
	char			*fname = "/home/rsync-Mint/ipc.dat";
	int 			fd;
	mode_t 			mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	char			*data;
	int 			*int_ptr;


	long page_size = sysconf (_SC_PAGESIZE);
	printf("\n ***** ipc test ****\n\n");
	printf("page size %i\n",(int)page_size);
	printf("system control block size %i\n",sizeof(*com_block));
	printf("     system schedule size %i\n",sizeof(com_block->sch));
	printf("        channel data size  %i\n",sizeof(com_block->c_dat));
	printf("         sensor data size  %i\n",sizeof(com_block->s_dat));
	printf("wasted memory %i\n\n", 2*(int)page_size - sizeof(*com_block));

/* create ipc file */
    fd = open(fname, O_RDWR | O_CREAT | O_TRUNC, mode);
    if(fd == -1){
        printf("\n*** error opening system data file\r\n");
        perror(fname);
        printf("*** terminating program\n\n");
        exit(1);
    }
	printf("file descriptor %i returned from open\n",fd);

/* map the file */
	com_block = mmap((caddr_t)0, page_size * 2, PROT_READ |  PROT_WRITE, MAP_SHARED, fd, 0);
	if((caddr_t)com_block == (caddr_t)(-1)){
        printf("\n*** error mapping system data file\r\n");
        perror("mmap");
        printf("*** terminating program\n\n");
        exit(1);
	}
	printf("file mapped to memory\n");

/* write some data */
	l.s_dat[5].temp = 202;
	memcpy(data,&l,sizeof(l));
	printf("****<%i>****\n",l.s_dat[5].temp);
	if (munmap (com_block, sizeof(*com_block)) == −1) {
        perror ("munmap");
        exit(1);
    }
	close(fd);

/* read some data */
	fd = open(fname, O_RDWR | O_CREAT | O_TRUNC, mode);
    if(fd == -1){
        printf("\n*** error opening system data file\r\n");
        perror(fname);
        printf("*** terminating program\n\n");
        exit(1);
    }
    printf("file descriptor %i returned from open\n",fd);
	memcpy(&l,data,sizeof(l));
	printf("****<%i>****\n",l.s_dat[5].temp);


	close(fd);
	printf("\n");
	return 0;
}
