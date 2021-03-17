#ifndef __QUEUE_H_
#define __QUEUE_H_

#include <stdio.h>
#include <malloc.h>
#include <stdint.h>

typedef enum _bool {
	False,
	True,
} bool_t;

typedef enum _status {
	Failed,
	Success,
} status_t;

typedef struct _queue_buffer {
    int front;
    int rear;
    int size;
    char *buffer;
} queue_buffer_t;

queue_buffer_t *queueCreate ( int size );
void queueRelease ( queue_buffer_t *queue );
bool_t isQueueEmpty ( queue_buffer_t *queue );
bool_t isQueueFull ( queue_buffer_t *queue );
int enQueue ( queue_buffer_t *queue, char data, uint8_t* u8LengthQueue );
int deQueue ( queue_buffer_t *queue, char *data, uint8_t* u8LengthQueue );


#endif /*__QUEUE_H_ */
