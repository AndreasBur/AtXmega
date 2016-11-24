/**************************************************************************************
*   I N C L U D E
***************************************************************************************/
#include "queue.h"


/**************************************************************************************
*
*   \fn mqd_t queue_init()
*
*   \brief creates a message queue
*
*   \return mqd_t: message queue handler
*
***************************************************************************************/
mqd_t queue_init()
{
    struct mq_attr attr;
    mqd_t mq;

    /* Form the queue attributes */
	attr.mq_flags = 0; /* i.e mq_send will be block if message queue is full */
	attr.mq_maxmsg = MQ_MAX_NUM_OF_MESSAGES;
	attr.mq_msgsize = sizeof(event_t);
	attr.mq_curmsgs = 0; /* mq_curmsgs is dont care */

    // Create the message queue with some default settings.
	mq = mq_open(MQ_NAME, O_RDWR | O_CREAT, MQ_MODE, &attr);

	if( mq != (mqd_t)-1 )
	{
		printf("message queue opened\n");
		printf("message queue timeout in %d ms \n", (MQ_RECEIVE_TIMEOUT));
	}
	else
    {
        perror("could not open message queue");
    }

	return mq;
}


/**************************************************************************************
*
*   \fn event_t queue_read(mqd_t mq)
*
*   \brief read message queue until timeout
*
*   \return event_t: type of event
*
***************************************************************************************/
event_t queue_read(mqd_t mq)
{
    struct timespec current_time;
	struct timespec abs_timeout;
    unsigned long ntime;
    int msg_len;
    event_t event;

    clock_gettime(CLOCK_REALTIME, &current_time);
    ntime = (long) current_time.tv_nsec + (long) (MQ_RECEIVE_TIMEOUT * 1000000);
    if(ntime > 1000000000 && ntime < 2000000000)
    {
        ntime -= 1000000000;
        abs_timeout.tv_sec = current_time.tv_sec + 1;

    }
    else
    {
        abs_timeout.tv_sec = current_time.tv_sec;
    }

    abs_timeout.tv_nsec = ntime;
    msg_len = mq_timedreceive(mq, (char *)(&event), sizeof(event_t), NULL, &abs_timeout);

    if(msg_len < 0)
    {
        /* mq_timedreceive returned with an error */
        if(errno == ETIMEDOUT) return EVENT_TIMEOUT;
        else perror("unknown ERROR happened");
    }

    return event;
}


/**************************************************************************************
*
*   \fn int queue_write(mqd_t mq, event_t event)
*
*   \brief close message queue
*
*   \return event_t: type of event
*
***************************************************************************************/
int queue_write(mqd_t mq, event_t event)
{
    return mq_send(mq, (char *)(&event), sizeof(event_t), 1);
}


/**************************************************************************************
*
*   \fn int queue_close(mqd_t mq)
*
*   \brief close message queue
*
*   \return event_t: type of event
*
***************************************************************************************/
void queue_close(mqd_t mq)
{
	int ret;

    /* Close the message queue */
    ret = mq_close(mq);
    if(ret) perror("message queue close failed");
    else printf("message queue closed\n");

    ret = mq_unlink(MQ_NAME);
    if(ret) perror("message queue unlink failed");
    else printf("message queue unlinked\n");
}
