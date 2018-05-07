/*
 * pid.h
 *
 *  Created on: May 5, 2018
 *      Author: knguy
 */

#ifndef PID_H_
#define PID_H_

typedef
    struct {
        // The fields are ordered to reduce memory over caused by struct-padding
		float Ki;
		float Kp;
		float Kd;
		float D_part;
		float I_part;
		float P_part;
		float T;
		float pre_Out;
		float Out;
		float pre_pre_Error;
		float pre_Error;
		float saturate_h;
		float saturate_l;
		float I_part_sat;
		float Error;

    }
pidparams;

void PID_process(volatile pidparams *pid, float error);
void PID_init(volatile pidparams *pid, float Kp,float Ki,float Kd,
			float saturate_l, float saturate_h,float t,float I_part_sat);


#endif /* LIB_PID_H_ */
