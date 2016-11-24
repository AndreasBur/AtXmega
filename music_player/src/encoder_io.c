/*********************************************************************************
*   I N C L U D E
*********************************************************************************/
#include <wiringPi.h>
#include "encoder_io.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>


/*********************************************************************************
	I N T E R R U P T
*********************************************************************************/
void encoder_read()
{
	static int last_value, step;
	int new_value = 0, diff, enc_delta=0;

	if(digitalRead(PHASE_A))
		new_value = 3;
	if(digitalRead(PHASE_B))
		new_value ^= 1;					// convert gray to binary
	diff = last_value - new_value;				// difference last_value - new_value
	if( diff & 1 )					// bit 0 = value (1)
	{	last_value = new_value;					// store new_value as next last_value
		step++;
		if(step == number_of_steps)
		{
			step = 0;
			enc_delta = (diff & 2) - 1;        // bit 1 = direction (+/-)
			//printf ("counter: %5d\n", enc_delta);
			rotation_event(enc_delta);
		}
	}
}


/*********************************************************************************
*
*   \fn void encoder_init()
*
*   \brief initialization of the rotation encoder
*
*   \return --
*
*********************************************************************************/
int encoder_init()
{
	if (wiringPiSetup() < 0)
	{
		fprintf(stderr, "Unable to setup wiringPi: %s\n", strerror(errno)) ;
		return 1;
	}

	if (wiringPiISR(PHASE_A, INT_EDGE_BOTH, &encoder_read) < 0)
	{
		fprintf (stderr, "Unable to setup ISR: %s\n", strerror(errno)) ;
		return 1;
	}

	if (wiringPiISR(PHASE_B, INT_EDGE_BOTH, &encoder_read) < 0)
	{
		//fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno)) ;
		return 1;
	}

	return 0;
}
