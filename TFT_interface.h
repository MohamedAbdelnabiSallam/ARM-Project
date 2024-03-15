/*
 * TFT_interface.h
 *
 *  Created on: Feb 5, 2024
 *      Author: philo
 */

#ifndef TFT_INTERFACE_H_
#define TFT_INTERFACE_H_


void HTFT_voidInit(void);
void HTFT_voidDisplayImage(const u16 * Copy_pu16Image);
void HTFT_voidSetWindow(u8 Copy_u8X0, u8 Copy_u8X1, u8 Copy_u8Y0, u8 Copy_u8Y1);


#endif /* TFT_INTERFACE_H_ */
