#ifndef IPC_H_
#define IPC_H_

#include "shared.h"

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
		int			lup_sec;		// last update
		int			lup_min;		// last update
		int			lup_hour;		// last update
		int			lup_wday;		// last update
	} s_dat[_NUMBER_OF_SENSORS];

} IPC_DAT;

int ipc_open(char *);
void *ipc_map(int, int);
void ipc_close(int, void *, int);

#endif