#ifndef QUEUE_H
#define QUEUE_H

#ifdef __cplusplus
	extern "C" {
#endif

/**************************************************************************************
*   I N C L U D E
***************************************************************************************/
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include "event.h"

/**************************************************************************************
*   D E F I N E
***************************************************************************************/
#define MQ_NAME "/mqueue"
#define MQ_MAX_NUM_OF_MESSAGES 10
#define MQ_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define MQ_RECEIVE_TIMEOUT 200 // timeout in ms (! min: 1ms and max: 1000ms !)
#define MQ_MESSAGE_PRIORITY 0


/**************************************************************************************
*   P R O T O T Y P E
***************************************************************************************/
mqd_t queue_init();
event_t queue_read(mqd_t mq);
int queue_write(mqd_t mq, event_t event);
void queue_close(mqd_t mq);

#ifdef __cplusplus
        }
#endif
#endif
