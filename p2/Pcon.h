#ifndef PCON_H_
#define PCON_H_

#define _TRACE
#define _SYSTEM_DATA_FILE		"/home/rsync-Mint/Pcon.dat" //sd card file


/* character parser fsm */
#define _CHAR_TOKENS     		5
#define _CHAR_STATES     		4
#define _MAX_TOKEN_SIZE			128

/* command parser fsm */
#define _CMD_TOKENS     		34
#define _CMD_STATES     		22 

#define _MAX_SCHLIB_SCH			20

/* buffers */
#define _INPUT_BUFFER_SIZE		128
#define _TOKEN_BUFFER_SIZE		60
#define _PROMPT_BUFFER_SIZE		200

// #define _TIME_STRING_BUFFER     40
// #define _VCMD_BUFFER            128

/* key codes */
#define _ESC        27
#define _SPACE      32
#define _COLON      58
#define _SLASH      47
#define _COMMA      44
#define _BS         8
#define _DEL		127
#define _QUOTE      34
#define _CR         13
#define _NL 		10
#define _FF 		12
#define _EOF		0
#define _NO_CHAR    255
#define _DELIMITER	42	//asterisk

/* fuctions */
int term(int);
void term1(void);
void disp_sys(void);


/* version info */
#define _major_version 			6
#define _minor_version 			0
#define _minor_revision 		0

// /* shared bone-C3 commands */
// #define _PING         	27
// #define _ACK           	6
// #define _WRITE_CMD		1
// #define _READ_CMD		2
// #define _WRITE_SCH		3
// #define _PUSH_STATS		4

/* channel parameters */
#define _NUMBER_OF_CHANNELS 	16
#define _CHANNEL_NAME_SIZE		20

/* schedule parameters */
#define _SCHEDULE_NAME_SIZE		40
#define _MAX_SCHEDULE_RECS		10
#define _SCHEDULE_SIZE			_MAX_SCHEDULE_RECS + 1
// #define _SCHEDULE_BUFFER		128

#define	_BYTES_PER_INT 				4
#define _BYTES_PER_SCHEDULE 	_SCHEDULE_SIZE * _BYTES_PER_INT
#define _BYTES_PER_DAY 			_NUMBER_OF_CHANNELS * _BYTES_PER_SCHEDULE

/* general */
#define _DAYS_PER_WEEK 				7

#endif
