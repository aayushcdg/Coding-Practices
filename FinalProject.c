/*
Submitted By: Aayush Jain
File Name: Final Project for HSI 255
*/

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "C:\Program Files (x86)\LabJack\Drivers\LabJackUD.h"

int main()
{

	LJ_ERROR lj_cue;
	LJ_HANDLE lj_handle = 0;
	double dblValueAIN1 = 0;
	double dblValueFIO4 = 0;
	double dblValueDAC1 = 0;

	lj_cue = OpenLabJack(LJ_dtU3, LJ_ctUSB, "1", 1, &lj_handle);
	lj_cue = ePut(lj_handle, LJ_ioPIN_CONFIGURATION_RESET, 0, 0, 0);

	lj_cue = AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_chTIMER_COUNTER_PIN_OFFSET, 4, 0, 0);
	lj_cue = AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_chTIMER_CLOCK_BASE, LJ_tc48MHZ_DIV, 0, 0);
	lj_cue = AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_chTIMER_CLOCK_DIVISOR, 48, 0, 0);
	lj_cue = AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_chNUMBER_TIMERS_ENABLED, 1, 0, 0);
	lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_MODE, 0, LJ_tmPWM8, 0, 0);
	lj_cue = Go();

	while (dblValueAIN1 < 1)
	{
		lj_cue = AddRequest(lj_handle, LJ_ioGET_AIN, 1, 0, 0, 0);
		lj_cue = Go();
		lj_cue = GetResult(lj_handle, LJ_ioGET_AIN, 1, &dblValueAIN1);
		printf("AIN1 = %.2lf\n", dblValueAIN1);
		Sleep(250);
	}

	lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 1, 5, 0, 0);
	lj_cue = Go();

	lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 0, 32768, 0, 0);
	lj_cue = Go();

	Sleep(15000);


	lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 1, 0, 0, 0);
	lj_cue = Go();


	lj_cue = ePut(lj_handle, LJ_ioPIN_CONFIGURATION_RESET, 0, 0, 0);
	lj_cue = eGet(lj_handle, LJ_ioGET_DIGITAL_BIT, 4, &dblValueFIO4, 0);

	Close();
	return 0;
}