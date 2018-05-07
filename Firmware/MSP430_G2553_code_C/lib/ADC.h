#ifndef __ADC__H__
#define __ADC__H__

#include <stdint.h>

//Chu y thach anh ngoai khong mo phong bang protues duoc
typedef enum { 	ON2_5V,		//Dien ap tham chieu noi 2.5V
				ON1_5V,		//Dien ap tham chieu noi 2.5V
				VCC,//Dien ap nguon,luu y phai loc nhieu tot cho nguon neu dung che do nay
				VeREF
				} Vref;

//Khoi tao ADC
void ADC10_Init(Vref V_tham_chieu);
//Doc 1 kenh ADC
unsigned int ADC10_Read_Channel(unsigned char channel);	//1->16
//Che do chuyen doi lien tuc
// Neu sequence = 0 thi ghi 1 gia tri cua channel vao *pointer
// Neu sequence = 1 thi cac gia tri ghi vao cua cac channel tu channel ->A0
// Quet tu channel A(channel) ->A0 , che 1 chuyen giao 1 block
// Chu y la A(channel) dc ghi vao pointer[0]
void ADC10_DTC(unsigned char channel,unsigned int pointer[], unsigned char sequence);

#endif
