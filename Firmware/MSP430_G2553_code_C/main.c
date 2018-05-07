#include "msp430.h"
#include <stdio.h>
#include <stdint.h>
#include "lib/Buck_boost.h"


volatile uint16_t duty=0;
uint16_t voltage_error;
uint16_t voltage_out;
volatile uint32_t time = 0;

int main(void)
{
	Config_stop_WDT();
	Config_Clocks();
	GPIO_init();
	uart_init();
	Timer_start();
	ADC10_Init(ON2_5V);
	PWM_start();

	char str[100];

	//void PID_init(&voltage_pid, 1, 1,1,1, 1,1);
	voltage_pid.Kp = 0.01;
	voltage_pid.Ki = 0;
	voltage_pid.Kd = 0.001;
	voltage_pid.saturate_l = 50;
	voltage_pid.saturate_h = 450;
	voltage_pid.T = 1;
	voltage_pid.I_part_sat = 50;

	while(1)
	{
		//uart_puts("aaa");
		voltage_error = voltage_pid.Error;
		voltage_out = voltage_pid.Out;
		sprintf(str, "0 %d %d 1023", (uint16_t)voltage_error,(uint16_t)voltage_out);
		uart_puts(str);
		uart_puts("\n\r");
		delay_ms(1);

	}

}

#pragma vector = PORT1_VECTOR
__interrupt void BUTTON_Interrupt_Handle(void)
{
	P1OUT ^= LED_GREEN;
	//delay_us (20);
    if ((P1IFG & BTN1) == BTN1)
    {
    	P1OUT ^= LED_RED;
    	duty += 100;
    	if(duty>1000)
    		duty=100;
        PWM_update(duty);
    }
    P1IFG &= ~BTN1;
}

