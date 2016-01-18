
#include <stdio.h>
#include <unistd.h>		//sleep
#include <stdint.h>		//uint_8, uint_16, uint_32, etc.
#include <unistd.h>
#include <stdio.h>

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

	IPC_DAT		com_block;

	long page_size = sysconf (_SC_PAGESIZE);
	printf("page size %i\n",(int)page_size);

	printf("system control block size %i\n",sizeof(com_block));
	printf("     system schedule size %i\n",sizeof(com_block.sch));
	printf("        channel data size  %i\n",sizeof(com_block.c_dat));
	printf("         sensor data size  %i\n",sizeof(com_block.s_dat));



	return 0;
}
