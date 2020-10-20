#include "Queue.h"

queue_buffer_t *queueCreate ( int size )
{
    queue_buffer_t *queue = ( queue_buffer_t * ) malloc ( sizeof(queue_buffer_t) );
    if ( !queue )
        return NULL;

    queue->buffer = ( char * ) malloc ( size * sizeof(char) );
    if ( !queue->buffer )
        return NULL;

    queue->front = 0;
    queue->rear = 0;
    queue->size = size;
    queue->count = size;

    return queue;
}

void queueRelease ( queue_buffer_t *queue )
{
    free ( queue->buffer );
    free ( queue );
}

bool_t isQueueEmpty ( queue_buffer_t *queue )
{
    if ( queue->count == queue->size )
        return True;

    return False;
}

bool_t isQueueFull ( queue_buffer_t *queue )
{
    if ( queue->count == 0 )
        return True;

    return False;
}

int enQueue ( queue_buffer_t *queue, char data )
{
    if ( isQueueFull( queue ) )
        return Failed;
    else {
        queue->buffer[queue->rear] = data;
        queue->rear++;
        queue->count--;
        if ( queue->rear == queue->size )
            queue->rear = 0;
    }
    return Success;
}

int deQueue ( queue_buffer_t *queue, char *data )
{
    if ( isQueueEmpty( queue ) )
        return Failed;
    else {
        *data = queue->buffer[queue->front];
        queue->front++;
        queue->count++;
        if ( queue->front == queue->size )
            queue->front = 0;
    }
    return Success;
}