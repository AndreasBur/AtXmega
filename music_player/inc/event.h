#ifndef EVENT_H
#define EVENT_H


/**************************************************************************************
*   T Y P E D E F
***************************************************************************************/
typedef enum {
	EVENT_NONE,
	EVENT_TIMEOUT,
    EVENT_ROTATION_L,
    EVENT_ROTATION_R,
	EVENT_BUTTON1,
	EVENT_BUTTON2,
} event_t;


#endif // EVENT_H
