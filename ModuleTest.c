/*
 * ModuleTest.c
 *
 *	Provides the testing functions all of individual peripheral testing
 *	and full system testing
 *
 * Created on: November 13, 2024
 *		Author: Oliver Cabral and Jason Chan
 *
 */
 
#include "ModuleTest.h"
#include "TCS34727.h"
#include "MPU6050.h"
#include "UART0.h"
#include "Servo.h"
#include "LCD.h"
#include "I2C.h"
#include "util.h"
#include "ButtonLED.h"
#include "tm4c123gh6pm.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

static char printBuf[100];
static char angleBuf[LCD_ROW_SIZE];
static char colorBuf[LCD_ROW_SIZE];
static char colorString[6];

/* RGB Color Struct Instance */
RGB_COLOR_HANDLE_t RGB_COLOR;
	
/* MPU6050 Struct Instance */
MPU6050_ACCEL_t Accel_Instance;
MPU6050_GYRO_t 	Gyro_Instance;
MPU6050_ANGLE_t Angle_Instance;

uint8_t Color[] = {RED, GREEN, BLUE};
uint8_t Color_Idx = 0;
void GPIOPortF_Handler(){
	if(SW1_PIN){
		GPIO_PORTF_ICR_R = SW1_FLAG;
		Color_Idx = (Color_Idx+1)%3;
		LEDs = Color[Color_Idx];
	}
}

static void Test_Delay(void){
	/*CODE_FILL*/				//Toggle Red Led
	/*CODE_FILLor*/				//Delay for 0.5s using millisecond delay
	LEDs ^= Color[Color_Idx];
	DELAY_1MS(500);
}

float num = 0.0f;
static void Test_UART(void){
	/*CODE_FILL*/						
	// 1. Construct a string with letters, decimal numbers and floats using sprintf
	// 2. Send the string to PC serial terminal for display	
	// 3. Delay for 1s using ms delay function
	WTIMER0_Init();
	float num = 0.0f;
	while(1){
		sprintf(printBuf, "Floating Number: %.2f\r\n", num);
		UART0_OutString(printBuf);
		DELAY_1MS(1000);
		num += 0.25f;
	}
}

static void Test_I2C(void){
	/*CODE_FILL*/						
	
	/* Check if RGB Color Sensor has been detected and display the ret value on PC serial terminal. */
		/* Check if RGB Color Sensor has been detected */	
	//Print ID or Error to Terminal
	sprintf(printBuf, "ID: %x\r\n", I2C0_Receive(TCS34727_ADDR, TCS34727_CMD|TCS34727_ID_R_ADDR));
	UART0_OutString(printBuf);
}


static void Test_MPU6050(void){
	/* Grab Accelerometer and Gyroscope Raw Data*/

	
	/*CODE_FILL*/
	MPU6050_Get_Accel(&Accel_Instance);
	MPU6050_Get_Gyro(&Gyro_Instance);
		
	/* Process Raw Accelerometer and Gyroscope Data */
	/*CODE_FILL*/
	MPU6050_Process_Accel(&Accel_Instance);
	MPU6050_Process_Gyro(&Gyro_Instance);
	
	//Clear Terminal
	UART0_OutString("\033[2J");
			
	/* Calculate Tilt Angle */
	/*CODE_FILL*/
	MPU6050_Get_Angle(&Accel_Instance, &Gyro_Instance, &Angle_Instance);
		
	/* Format buffer to print data and angle */
	/*CODE_FILL*/
	//UART0_OutString("Accel Instance\r\n");
	sprintf(printBuf, "X: %f\r\nY: %f\r\nY: %f\r\n", Accel_Instance.Ax, Accel_Instance.Ay, Accel_Instance.Az);
	UART0_OutString(printBuf);
  UART0_OutString("Gyro Instance\r\n");
	sprintf(printBuf, "X: %f\r\nY: %f\r\nY: %f\r\n", Gyro_Instance.Gx, Gyro_Instance.Gy, Gyro_Instance.Gz);
	UART0_OutString(printBuf);
	UART0_OutString("Angle Instance\r\n");
	sprintf(printBuf, "X: %f Y: %f Z: %f", Angle_Instance.ArX, Angle_Instance.ArY, Angle_Instance.ArZ);
	UART0_OutString(printBuf);
	
	DELAY_1MS(50);
}

static void Test_TCS34727(void){
	WTIMER0_Init();
	/* Grab Raw Color Data From Sensor */
	RGB_COLOR.R_RAW = TCS34727_GET_RAW_RED();
	RGB_COLOR.G_RAW = TCS34727_GET_RAW_GREEN();
	RGB_COLOR.B_RAW = TCS34727_GET_RAW_BLUE();
	RGB_COLOR.C_RAW = TCS34727_GET_RAW_CLEAR();
	
	//Clear Terminal
	UART0_OutChar(0x1B);
	UART0_OutChar(0x5B);
	UART0_OutChar(0x32);
	UART0_OutChar(0x1B);
	
	sprintf(printBuf,"RED RAW: %x\r\nGREEN RAW: %x\r\nBLUE RAW: %x\r\n",RGB_COLOR.R_RAW, RGB_COLOR.G_RAW, RGB_COLOR.B_RAW);
	UART0_OutString(printBuf);
	
	/* Process Raw Color Data to RGB Value */
	/*CODE_FILL*/
	TCS34727_GET_RGB(&RGB_COLOR);
		
	
	/* Change Onboard RGB LED Color to Detected Color */
	switch(Detect_Color(&RGB_COLOR)){
		case RED_DETECT:
			LEDs = RED;
			break;
		case GREEN_DETECT:
			LEDs = GREEN;
			break;
		case BLUE_DETECT:
			LEDs = BLUE;
			break;
		case NOTHING_DETECT:
			LEDs = DARK;
			break;
		}
		
	/* Format String to Print */
	/*CODE_FILL*/
		
	/* Print String to Terminal through USB */
	/*CODE_FILL*/
		
	DELAY_1MS(10);
}

static void Test_Servo(void){

	/*
	 * In this test, follow the series of steps below (each step requires a 1s delay after)
	 * 1. Drive Servo to 0 degree
	 * 2. Drive Servo to -45 degree
	 * 3. Drive Servo to 0 degree
	 * 4. Drive Servo to 45 degree
	 * 5. Drive Servo to 0 degree
	 * 6. Drive Servo to -90 degree
	 * 7. Drive Servo to 0 degree
	 * 8. Drive Servo to 90 degree
	 */ 
	
	
	UART0_OutString("Setting Angle to 0 Degree\r\n");
	Drive_Servo(0);
	DELAY_1MS(1000);
	
	UART0_OutString("Setting Angle to -45 Degree\r\n");
	Drive_Servo(-45);
	DELAY_1MS(1000);
	
	UART0_OutString("Setting Angle to 0 Degree\r\n");
	Drive_Servo(0);
	DELAY_1MS(1000);
	
	UART0_OutString("Setting Angle to 45 Degree\r\n");
	Drive_Servo(45);
	DELAY_1MS(1000);
	
	UART0_OutString("Setting Angle to 0 Degree\r\n");
	Drive_Servo(0);
	DELAY_1MS(1000);
	
	UART0_OutString("Setting Angle to -90 Degree\r\n");
	Drive_Servo(-90);
	DELAY_1MS(1000);
	
	UART0_OutString("Setting Angle to 0 Degree\r\n");
	Drive_Servo(0);
	DELAY_1MS(1000);
	
	UART0_OutString("Setting Angle to 90 Degree\r\n");
	Drive_Servo(90);
	DELAY_1MS(1000);
	
	/*CODE_FILL*/
	
}

static void Test_LCD(void){
	/* Print Name to LCD at Center Location */
	/*CODE_FILL*/
	LCD_Clear();
	DELAY_1MS(10);
	LCD_Set_Cursor(ROW1,5);
	DELAY_1MS(10);
	LCD_Print_Str((uint8_t *) "Oliver");
	DELAY_1MS(1000);
	LCD_Set_Cursor(ROW2,5);
	DELAY_1MS(10);
	LCD_Print_Str((uint8_t *) "Cabral");
	DELAY_1MS(1000);
}

static void Test_Full_System(void){
	/* Grab Accelerometer and Gyroscope Raw Data*/
	MPU6050_Get_Accel(&Accel_Instance);
	MPU6050_Get_Gyro(&Gyro_Instance);
	
		
	/* Process Raw Accelerometer and Gyroscope Data */
	MPU6050_Process_Accel(&Accel_Instance);
	MPU6050_Process_Gyro(&Gyro_Instance);
		
	/* Calculate Tilt Angle */
	MPU6050_Get_Angle(&Accel_Instance, &Gyro_Instance, &Angle_Instance);
		
	/* Drive Servo Accordingly to Tilt Angle on X-Axis*/
	Drive_Servo(Angle_Instance.ArX);
		
	/* Format buffer to print MPU6050 data and angle */
	sprintf(printBuf, "X: %f\r\nY: %f\r\nY: %f\r\n", Accel_Instance.Ax, Accel_Instance.Ay, Accel_Instance.Az);
	UART0_OutString(printBuf);
  UART0_OutString("Gyro Instance\r\n");
	sprintf(printBuf, "X: %f\r\nY: %f\r\nY: %f\r\n", Gyro_Instance.Gx, Gyro_Instance.Gy, Gyro_Instance.Gz);
	UART0_OutString(printBuf);
	UART0_OutString("Angle Instance\r\n");
	sprintf(printBuf, "X: %f Y: %f Z: %f", Angle_Instance.ArX, Angle_Instance.ArY, Angle_Instance.ArZ);
	UART0_OutString(printBuf);
		
	/* Grab Raw Color Data From Sensor */
	RGB_COLOR.R_RAW = TCS34727_GET_RAW_RED();
	RGB_COLOR.G_RAW = TCS34727_GET_RAW_GREEN();
	RGB_COLOR.B_RAW = TCS34727_GET_RAW_BLUE();
	RGB_COLOR.C_RAW = TCS34727_GET_RAW_CLEAR();
		
	/* Process Raw Color Data to RGB Value */
	TCS34727_GET_RGB(&RGB_COLOR);
		
	/* Change Onboard RGB LED Color to Detected Color */
	switch(Detect_Color(&RGB_COLOR)){
		case RED_DETECT:
			LEDs = RED;
			strcpy(colorString, "RED");
			break;
		case GREEN_DETECT:
			LEDs = GREEN;
			strcpy(colorString, "GREEN");
			break;
		case BLUE_DETECT:
			LEDs = BLUE;
			strcpy(colorString, "BLUE");
			break;
		case NOTHING_DETECT:
			LEDs = DARK;
			strcpy(colorString, "NA");
			break;
	}
		
	/* Format String to Print RGB value*/
	sprintf(printBuf,"RED RAW: %x\r\nGREEN RAW: %x\r\nBLUE RAW: %x\r\n",RGB_COLOR.R_RAW, RGB_COLOR.G_RAW, RGB_COLOR.B_RAW);
		
	/* Print String to Terminal through USB */
	UART0_OutString(printBuf);
		
	/* Update LCD With Current Angle and Color Detected */
	sprintf(angleBuf, "Angle:%0.2f", Angle_Instance.ArX);				//Format String to print angle to 2 Decimal Place
	sprintf(colorBuf, "Color:%s", colorString);									//Format String to print color detected
	
	LCD_Clear();						//Clear LCD
	DELAY_1MS(2);						//Safety Delay of 2ms
	LCD_Set_Cursor(ROW1,0);						//Set Cursor to Row 1 Column 0
	LCD_Print_Str((uint8_t*)angleBuf);						//Print angleBuf String on LCD
	DELAY_1MS(2);					//Safety Delay of 2ms
	LCD_Set_Cursor(ROW2,0);						
	LCD_Print_Str((uint8_t*)colorString);
		
	DELAY_1MS(20);
}

void Module_Test(MODULE_TEST_NAME test){
	
	switch(test){
		case DELAY_TEST:
			Test_Delay();
			break;
		
		case I2C_TEST:
			Test_I2C();
			break;
		
		case UART_TEST:
			Test_UART();
			break;
		
		case MPU6050_TEST:
			Test_MPU6050();
			break;
		
		case TCS34727_TEST:
			Test_TCS34727();
			break;
		
		case SERVO_TEST:
			Test_Servo();
			break;
		
		case LCD_TEST:
			Test_LCD();
			break;
			
		case FULL_SYSTEM_TEST:
			Test_Full_System();
			break;
		
		
		default:
			break;
	}
	
}

 