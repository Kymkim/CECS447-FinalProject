/*
 * I2C.h
 *
 *	Provides the I2C Init, Read, and Write Function
 *
 * Created on: November 13, 2024
 *		Author: Oliver Cabral and Jason Chan
 *
 */

#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "util.h"

#include "UART0.h"

/* List of Fill In Macros */

//Init Function
//B2 = SCL
//B3 = SDA
#define EN_I2C0_CLOCK			(0x1)
#define EN_GPIOB_CLOCK		(0x2)
#define I2C0_PINS					(0xC)
#define I2C0_ALT_FUNC_MSK	(0xFFFF00FF)
#define I2C0_ALT_FUNC_SET	(0x00003300)
#define I2C0_SDA_PIN			(0x8)
#define I2C0_SCL_PIN			(0x4)
#define EN_I2C0_MASTER		(0x10)
#define I2C_MTPR_TPR_VALUE	(19)
#define I2C_MTPR_STD_SPEED (0x00)

//Transmit Function (Most came from above Macros)
#define I2C0_RW_PIN				(0x1)

//Burst Transmit Function
#define RUN_CMD						(I2C_MCS_RUN)

/*
 *	-------------------I2C0_Init------------------
 *	Basic I2C Initialization function for master mode @ 100kHz
 *	Input: None
 *	Output: None
 */
void I2C0_Init(void);

/*
 *	-------------------I2C0_Receive------------------
 *	Polls to receive data from specified peripheral
 *	Input: Slave address & Slave Register Address
 *	Output: Returns 8-bit data that has been received
 */
uint8_t I2C0_Receive(uint8_t slave_addr, uint8_t slave_reg_addr);

/*
 *	-------------------I2C0_Transmit------------------
 *	Transmit a byte of data to specified peripheral
 *	Input: Slave address, Slave Register Address, Data to Transmit
 *	Output: Any Errors if detected, otherwise 0
 */
uint8_t I2C0_Transmit(uint8_t slave_addr, uint8_t slave_reg_addr, uint8_t data);

//Has Yet to be Implemented
/*
 *	----------------I2C0_Burst_Receive-----------------
 *	Polls to receive multiple bytes of data from specified
 *  peripheral by incrementing starting slave register address
 *	Input: Slave address, Slave Register Address, Data Buffer
 *	Output: None
 */
void I2C0_Burst_Receive(uint8_t slave_addr, uint8_t slave_reg_addr, uint8_t* data, uint32_t size);

/*
 *	----------------I2C0_Burst_Transmit-----------------
 *	Transmit multiple bytes of data to specified peripheral
 *  by incrementing starting slave address
 *	Input: Slave address, Slave Register Address, Data Buffer to transmit, Size of Transmit
 *	Output: None
 */
uint8_t I2C0_Burst_Transmit(uint8_t slave_addr, uint8_t slave_reg_addr, uint8_t* data, uint32_t size);

#endif //I2C_H_


