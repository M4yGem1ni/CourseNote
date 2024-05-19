#ifndef __LED_H
#define __LED_H

typedef enum {ON = 1,OFF = 0} LED_Control;

void LED_Init(uint16_t LED_SEL);
void LED(uint16_t LED_Pin,LED_Control State);
void LED_Turn(uint16_t LED_Pin);

#endif
