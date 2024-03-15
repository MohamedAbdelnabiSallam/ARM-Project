/*
 * SYSTICK_int.h
 *
 *  Created on: Jan 21, 2024
 *      Author: Ahmed
 */

#ifndef SYSTICK_INT_H_
#define SYSTICK_INT_H_

typedef enum{
	SYSTICK_INT_DISABLE,
	SYSTICK_INT_ENABLE
}SYSTICK_IntState_t;

/*Clock Configuration*/
void SYSTICK_voidInit(void);

void SYSTICK_voidEnable(void);

void SYSTICK_voidDisable(void);

void SYSTICK_voidStart(u32 u32LoadValueCpy);

void SYSTICK_voidDelayUs(u32 u32DelayCpy);

void SYSTICK_voidDelayMs(u32 u32DelayCpy);

u8 SYSTICK_u8ReadFlag(void);

void SYSTICK_voidCtrlIntState(SYSTICK_IntState_t enuStateCpy);

u32 SYSTICK_u32GetElapsedTime(void);

void SYSTICK_voidSetInterval_single(u32 u32LoadValue, pf pfCallBackFun);

void SYSTICK_voidSetInterval_periodic(u32 u32LoadValue, pf pfCallBackFun);

#endif /* SYSTICK_INT_H_ */
