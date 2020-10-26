#include "Queue.h"

queue_buffer_t *queueCreate ( int size )
{
    queue_buffer_t *queue = ( queue_buffer_t * ) malloc ( sizeof(queue_buffer_t) );
    if ( !queue )
        return NULL;

    queue->buffer = ( char * ) malloc ( size * sizeof(char) );
    if ( !queue->buffer )
        return NULL;

    queue->front = -1;
    queue->rear = -1;
    queue->size = size;

    return queue;
}

void queueRelease ( queue_buffer_t *queue )
{
    free ( queue->buffer );
    free ( queue );
}

bool_t isQueueEmpty ( queue_buffer_t *queue )
{
    if ( queue->front == -1 )
        return True;

    return False;
}

bool_t isQueueFull ( queue_buffer_t *queue )
{
    if ( (queue->front == rear + 1) ||
         (queue->front == 0 && queue->rear == queue->size - 1) )
        return True;

    return False;
}

int enQueue ( queue_buffer_t *queue, char data )
{
    if ( isQueueFull( queue ) )
        return Failed;
    else {
        if (queue->front == -1)
			queue->fron = 0;
		rear = (rear + 1) % queue->size;
		queue->buffer[rear] = data;
    }
    return Success;
}

int deQueue ( queue_buffer_t *queue, char *data )
{
	char byte;
	
    if ( isQueueEmpty( queue ) )
        return Failed;
    else {
        byte = queue->buffer[queue->front];
        if ( queue->front == queue->rear ) {
            queue->front = -1;
            queue->rear = -1;
		} else /* Queue has only one element. Reset the queue after dequeuing */
			queue->front = (queue->front + 1) % queue->size;

		*data = byte;
    }
    return Success;
}
