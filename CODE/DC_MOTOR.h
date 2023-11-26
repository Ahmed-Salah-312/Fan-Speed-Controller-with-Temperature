#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_
#include "std_types.h"
#include"gpio.h"
#define max_speed 255
typedef enum {
    CW,   // Clockwise
    ACW,  // Anti-clockwise
    STOP  // Stop
} DcMotor_State;
void DcMotor_Init(void);

void DcMotor_Rotate(uint8 state,uint8 speed);


#endif /* DC_MOTOR_H_ */
