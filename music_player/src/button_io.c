/**************************************************************************************
*   I N C L U D E
***************************************************************************************/
#include <wiringPi.h>
#include "button_io.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>


/**************************************************************************************
*
*   \fn void button1_init()
*
*   \brief initialization of button1
*
*   \return --
*
***************************************************************************************/
int button_init(int Button_pin, void (*function)(void))
{
	if (wiringPiSetup() < 0)
	{
		fprintf(stderr, "Unable to setup wiringPi: %s\n", strerror(errno));
		return 1;
	}

	if (wiringPiISR(Button_pin, INT_EDGE_RISING, function) < 0)
	{
		fprintf (stderr, "Unable to setup ISR: %s\n", strerror(errno)) ;
		return 1;
	}

	return 0;
}
