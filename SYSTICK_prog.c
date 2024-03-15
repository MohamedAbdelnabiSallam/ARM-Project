/*
 * SYSTICK_prog.c
 *
 *  Created on: Jan 21, 2024
 *      Author: Ahmed
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SYSTICK_int.h"
#include "SYSTICK_cfg.h"
#include "SYSTICK_priv.h"

static pf pfSysTickISRGlb = NULL_PTR;
static u8 u8PeriodicModeGlb = 0;

void SYSTICK_voidInit(void)
{
	/*Clock*/
#if SYSTICK_CLK_SOURCE == SYSTICK_AHB_DIVBY8
	CLR_BIT(SYSTICK_REG->CTRL,CTRL_CLKSOURCE);
#elif SYSTICK_CLK_SOURCE == SYSTICK_AHB_DIVBY1
	SET_BIT(SYSTICK_REG->CTRL,CTRL_CLKSOURCE);
#endif

	/*Interrupt EN/DISABLE*/
#if SYSTICK_INTERRUPT == SYSTICK_INTERRUPT_DISABLE
	CLR_BIT(SYSTICK_REG->CTRL,CTRL_TICKINT);
#elif SYSTICK_INTERRUPT == SYSTICK_INTERRUPT_ENABLE
	SET_BIT(SYSTICK_REG->CTRL,CTRL_TICKINT);
#endif

	/*SysTick EN/DISABLE*/
#if SYSTICK_STATE == SYSTICK_STATE_DISABLE
	CLR_BIT(SYSTICK_REG->CTRL,CTRL_ENABLE);
#elif SYSTICK_STATE == SYSTICK_STATE_ENABLE
	SET_BIT(SYSTICK_REG->CTRL,CTRL_ENABLE);
#endif
}

void SYSTICK_voidEnable(void)
{
	SET_BIT(SYSTICK_REG->CTRL,CTRL_ENABLE);
}

void SYSTICK_voidDisable(void)
{
	CLR_BIT(SYSTICK_REG->CTRL,CTRL_ENABLE);
}

void SYSTICK_voidStart(u32 u32LoadValueCpy)
{
	SYSTICK_REG->LOAD = u32LoadValueCpy;
	SYSTICK_REG->VAL = 0;
}

void SYSTICK_voidDelayUs(u32 u32DelayCpy)
{
	SYSTICK_voidCtrlIntState(SYSTICK_INT_DISABLE);

#if SYSTICK_CLK_SOURCE == SYSTICK_AHB_DIVBY8
	SYSTICK_voidStart(u32DelayCpy*2);
#elif SYSTICK_CLK_SOURCE == SYSTICK_AHB_DIVBY1
	SYSTICK_voidStart(u32DelayCpy*16);
#endif

	while(GET_BIT(SYSTICK_REG->CTRL,CTRL_COUNTFLAG)==0);
}

void SYSTICK_voidDelayMs(u32 u32DelayCpy)
{
	SYSTICK_voidCtrlIntState(SYSTICK_INT_DISABLE);

#if SYSTICK_CLK_SOURCE == SYSTICK_AHB_DIVBY8
	SYSTICK_voidStart(u32DelayCpy*2000);
#elif SYSTICK_CLK_SOURCE == SYSTICK_AHB_DIVBY1
	SYSTICK_voidStart(u32DelayCpy*16000);
#endif

	while(GET_BIT(SYSTICK_REG->CTRL,CTRL_COUNTFLAG)==0);
}

u8 SYSTICK_u8ReadFlag(void)
{
	return (GET_BIT(SYSTICK_REG->CTRL,CTRL_COUNTFLAG));
}

void SYSTICK_voidCtrlIntState(SYSTICK_IntState_t enuStateCpy)
{
	SYSTICK_REG->CTRL = (SYSTICK_REG->CTRL & ~(1<<CTRL_TICKINT)) | (enuStateCpy<<CTRL_TICKINT);
}

u32 SYSTICK_u32GetElapsedTime(void)
{
	return ((SYSTICK_REG->LOAD)-(SYSTICK_REG->VAL));
}

u32 SYSTICK_u32GetRemainingTime(void)
{
	return (SYSTICK_REG->VAL);
}

void SYSTICK_voidSetInterval_single(u32 u32LoadValue, pf pfCallBackFun)
{
	pfSysTickISRGlb = pfCallBackFun;
	SYSTICK_voidStart(u32LoadValue);
	u8PeriodicModeGlb=SINGLE_MODE;
}

void SYSTICK_voidSetInterval_periodic(u32 u32LoadValue, pf pfCallBackFun)
{
	pfSysTickISRGlb = pfCallBackFun;
	SYSTICK_voidStart(u32LoadValue);
	u8PeriodicModeGlb=PERIODIC_MODE;
}

void SysTick_Handler(void)
{
	if(pfSysTickISRGlb!=NULL_PTR)
	{
		pfSysTickISRGlb();
		if(u8PeriodicModeGlb==SINGLE_MODE)
		{
			pfSysTickISRGlb = NULL_PTR;
		}
	}
	else
	{

	}
}
