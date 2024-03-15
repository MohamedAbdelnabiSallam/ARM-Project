/*
 * R2RDAC_PROGRAM.c
 *
 *  Created on: Jan 23, 2024
 *      Author: Ahmed Hamada
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "R2RDAC_INTERFACE.h"
#include "R2RDAC_CONFIG.h"
#include "R2RDAC_PRIVATE.h"
#include "GPIO_interface.h"
#include "SYSTICK_int.h"

void R2RDAC_Init(void)
{
for(u8 i =0 ;i<8;i++)
{
	MGPIO_vSetMode(PORT_B,i,MODE_OUTPUT);
	MGPIO_vSetOutputMode(PORT_B,i,OUTPUT_PUSHPULL,SPEED_MEDUIEM);
}

}

void R2RDAC_SetData(const u8 *arr,u32 arrsize)
{
u32 counter;
for(counter=0;counter<arrsize;counter++)
{
	for(u8 i =0 ;i<8;i++)
	{
		MGPIO_vWritePin(PORT_B,i,GET_BIT(arr[counter],i));

	}
	SYSTICK_voidDelayUs(125);
}

}


