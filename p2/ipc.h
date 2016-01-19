#ifndef IPC_H_
#define IPC_H_

int ipc_open(char *);
void *ipc_map(int, int);
void ipc_close(int, void *, int);

#endif