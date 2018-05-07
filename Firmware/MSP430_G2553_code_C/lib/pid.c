/*
 * pid.c
 *
 *  Created on: May 5, 2018
 *      Author: Nguyen Khoi Nguyen
 */
#include "pid.h"

void PID_process(volatile pidparams *pid, float error)
{
//	pid->P_part = pid->Kp*(pid->Error - pid->pre_Error);
//	pid->I_part = 0.5*pid->Ki*pid->T*(pid->Error + pid->pre_Error);
//	pid->D_part = pid->Kd/pid->T*( pid->Error - 2*pid->pre_Error+ pid->pre_pre_Error);
//	pid->Out = pid->pre_Out + pid->P_part + pid->I_part + pid->D_part ;
//	pid->pre_pre_Error = pid->pre_Error;
//	pid->pre_Error = pid->Error;
//	pid->pre_Out = pid->Out;

	pid->P_part = pid->Kp * pid->Error;
	pid->I_part += pid->Ki * pid->Error / pid->T;
	pid->I_part = pid->I_part < pid->I_part_sat ? pid->I_part : pid->I_part_sat;
	pid->I_part = pid->I_part > -pid->I_part_sat ? pid->I_part : -pid->I_part_sat;
	pid->D_part = pid->Kd * (pid->Error - pid->pre_Error) * pid->T;
	pid->Out += pid->P_part + pid->I_part + pid->D_part;
	pid->pre_Error = pid->Error;


	if (pid->Out < pid->saturate_l)
		pid->Out = pid->saturate_l;
	else if(pid->Out > pid->saturate_h)
		pid->Out = pid->saturate_h;
}
void PID_init(volatile pidparams *pid, float _Kp,float _Ki,float _Kd,
			float _saturate_l, float _saturate_h,float _t,float _I_part_sat)
{
	pid->Kp = _Kp;
	pid->Ki = _Ki;
	pid->Kd = _Kd;
	pid->saturate_l = _saturate_l;
	pid->saturate_h = _saturate_h;
	pid->T = _t;
	pid->I_part_sat = _I_part_sat;
}


