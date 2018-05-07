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
 *    Module       : UART.C
 *    Description  : This file describes API functions that support you to
 *                   use UART Mode of USCI
 *
 *  Tool           : CCS 5.1
 *  Chip           : MSP430G2xx3 (MCU that haves USCI_A0 module)
 *  History        : 21-7-2012
 *  Version        : 1.1
 *
 *  Author         : Nguyen Tien Manh, CLB NCKH DDT (manhcly@ymail.com)
 *  Notes          :
 *      To apply these functions, you must include the header file uart.h and
 *      add this code file to your project.
 *
 *		To find or edit the UART configuration, check the function uart_init()
 *
******************************************************************************/

 /****************************************************************************
 * IMPORT
******************************************************************************/

#include <msp430.h>
#include "UART.h"

 /****************************************************************************
* FUNCTIONS
******************************************************************************/

 /****************************************************************************
* MODULE PUPLIC FUNCTIONS:
* void uart_init();
* void uart_putc(char c);
* void uart_puts(const char *s);
* void uart_put_num (unsigned long val, char dec, unsigned char neg);
* char uart_data_ready();
* char uart_getc();
* void uart_gets(char *s);
*
******************************************************************************/

//*****************************************************************************
// Initialization for UART module
//*****************************************************************************
void uart_init(void)
{
	P1SEL = BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
	P1SEL2 = BIT1 + BIT2 ;                    // P1.1 = RXD, P1.2=TXD
	UCA0CTL1 |= UCSSEL_2;                     // SMCLK
	UCA0CTL1 |= UCSWRST;
	UCA0BR0 = 104;                            // 1MHz 9600
	UCA0BR1 = 0;                              // 1MHz 9600
	UCA0MCTL = UCBRS_0 +UCBRF_3 + UCOS16;                        // Modulation UCBRSx = 1
	UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
	IE2 |= UCA0RXIE;
}

void uart_disable(void)
{
	IE2 = 0;
}

//*****************************************************************************
// Send a  character through UART
//*****************************************************************************
void uart_putc(char c)
{
	while(!(IFG2&UCA0TXIFG));   // Wait until USCI_A0 TX buffer empty
		UCA0TXBUF = c; 			// assign character to TX buffer
}

//*****************************************************************************
// Send a  string through UART
// Note that the string is ended with '/0' (or 0x00)
//*****************************************************************************
void uart_puts(const char* s)
{
	while(*s != '\0'){
		uart_putc(*s);
		s++;
	}
}

//*****************************************************************************
// Send a constant or a number stored in 'val' through UART
// The number must be multiplied and convert in type "unsigned long"
//                                                or "unsigned int"
//   dec: amount of digits after '.'
//   neg: sign of the number, neg = 0 if the number is positive
//
// Example 1: uart_put_num(val, 3, 0); // val = 12345
//        will put "12.345"
// Example 2: uart_put_num(val, 6, 1); // val = 12345
//        will put "-0.012345"
//
// Note: This function may contain some bugs. If you can detect and fix them
//       , please contact me :d
//*****************************************************************************
void uart_put_num (unsigned long val, char dec, unsigned char neg)
{
    char i, j, digit,k;
    long total;
    long temp;
    for (i = 0, total = val; total > 0;i++) // count number
        total /= 10;
        total = i;

    if (neg !=0 )
      uart_putc ('-');

    if ((total - dec) <=0)	// if total < dec put 0.xxx
        uart_putc('0');
    else
    {

      for (i=0; i< (total-dec); i++)
      {
        temp = 1;
        for (j=1;j<(total-i);j++)
            temp *=10;
        digit = (val/temp)%10;
        uart_putc(digit + 0x30);
      }
    }
    if (dec > 0)
    {
      uart_putc('.');
      if ( (dec - total)> 0)	// ex: val = 55; dec = 3 put 0.055
      {
        for ( i = 0; i < (dec-total);i++)
          uart_putc('0');
        k = 0;
      }
      else
        k = total - dec;
      for (i=k; i< total; i++)
      {
       temp = 1;
       for (j=1;j<(total-i);j++)
           temp *=10;
       digit = (val/temp)%10;
       uart_putc(digit + 0x30);
      }
    }
}


//*****************************************************************************
// Wait to receive a character through UART
//*****************************************************************************
char uart_getc()
{
	while(!(IFG2&UCA0RXIFG));   // Wait until USCI_A0 RX receive a complete character
		return UCA0RXBUF; // assign RX buffer to function 's name
}

//*****************************************************************************
// Wait to receive a string through UART
// Note that the string is ended with '/0' (or 0x00)
//*****************************************************************************
void uart_gets(volatile char *s)
{
	*s = uart_getc();
	while(*s!='\0')
	{
		s++;
		*s = uart_getc();
	}
}

//*****************************************************************************
// Check if USCI_A0 RX Buffer contain a complete character
//*****************************************************************************
char uart_data_ready()
{
	if(UCA0RXIFG) return 1;
	else return 0;
}


/****************************************************************************
* USCI_A0 RECEIVE INTERRUPT SERVICE ROUTINE
******************************************************************************/
#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
	uart_gets(uart_rev.rev_buf);
}

/******************************************************************************
 * END OF UART.C
*******************************************************************************/
