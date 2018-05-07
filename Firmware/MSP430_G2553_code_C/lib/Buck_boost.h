/******************************************************************************
 *
 * www.payitforward.edu.vn
 *
 ******************************************************************************/

/******************************************************************************
 *
 * TI LAUNCH PAD CODING
 *
 ******************************************************************************/

/******************************************************************************
 *
 *    Module       : Buck_boost.H
 *    Description  : This header file includes definitions and prototypes of
 *          basic configuration functions such as Initialization clock or delay
 *
 *  Tool           : CCS 6.1
 *  Chip           : MSP430G2xxx
 *  History        : 10/4/2018
 *  Version        : 1.1
 *
 *  Author         : Nguyen Khoi Nguyen, Pay It Forward Club
 *  Email		   : knguyentnh98@gmail.com
 *
 *  Notes          :
 *      To apply these functions, you must include the this header file and add
 *      the Basic_config.c file to your project.
 *
******************************************************************************/



#ifndef BUCK_BOOST_H_
#define BUCK_BOOST_H_

#include "UART.h"
#include "Basic_config.h"
#include "ADC.h"
#include "pid.h"
#include <stdint.h>

//#define TIMER

#define TIME_PERIOD 	16			//calculate 1us

#define TIME_INTERVAL	50			// in microsecond
#define DUTY_CIRCLE    	0.5			// 0 < DUTY_CIRCLE < 1
#define PWM_CIRCLE  		(uint16_t)(TIME_INTERVAL*SMCLK_)

#define SMCLK_			16
#define SAMPLING_TIME   (SMCLK_*1000)     	// sampling at 100us with clock at 16MHz

#define PIN_IN          BIT5        		// read form P1.5
#define PIN_OUT			(BIT2 + BIT4)		// output at P2.2, P2.4

#define LED_RED			BIT0
#define LED_GREEN		BIT6
#define BTN1			BIT3

#define SAMPLE_NUM		10
#define VOLTAGE_K		6.0
#define V_REF			2.5

#define DESIRE_VOLTAGE	5.0					//Set out put voltage
#define ADC_RESOLUTION	1024.0
#define ADC_SET_POINT	(DESIRE_VOLTAGE/VOLTAGE_K/V_REF*ADC_RESOLUTION)

typedef
    struct {
        // The fields are ordered to reduce memory over caused by struct-padding
		float Ki;
		float Kp;
		float Kd;
		char rev_buf[100];
    }
uartstring;

volatile uint16_t voltage_buf[SAMPLE_NUM];
volatile uint16_t current_buf[SAMPLE_NUM];

volatile pidparams voltage_pid;

volatile uartstring uart_rev;
volatile uint16_t data_buf[SAMPLE_NUM];
volatile uint16_t data;


void Buck_boost_init(void);
void GPIO_init(void);
void Timer_start(void);
void Timer_stop(void);

void PWM_start(void);
void PWM_update(uint16_t duty);
void PWM_stop(void);

//void PID_process(volatile pidparams *pid, float error);
void PID_update(pidparams *pid);

float Average_filter(volatile uint16_t *array);

#endif /* LIB_BUCK_BOOST_H_ */
