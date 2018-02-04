/* ###################################################################
**     Filename    : main.c
**     Project     : Mata
**     Processor   : MC9S08QE128CLK
**     Version     : Driver 01.12
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2018-01-17, 15:01, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.12
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "AS1.h"
#include "Bit1.h"
#include "TI1.h"
#include "Byte1.h"
#include "AS2.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

unsigned char estado = ESPERAR;
unsigned char CodError;
unsigned int Enviados = 3;		// Esta variable no aporta nada m�s sino el n�mero de elementos del arreglo a enviar.
unsigned int error;
bool primero = FALSE;
unsigned int periodo;

unsigned int ADC16;

unsigned char i = 0;

unsigned char mTrama[3]={0xFF,0x00,0x00}; 	// Esta es una primera trama que yo hice de ejemplo.
unsigned char dTrama[2]={0x00,0x00};			// Esta es la trama que declar� para rellenarla con la medici�n del ADC.	

void servo_send (unsigned char motor, unsigned char posicion);

void main(void)
{
  /* Write your local variable definition here */

	
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
    
  /* For example: for(;;) { } */

  for(;;){

  	switch (estado){
  		
  		case ESPERAR:
  			break;
  			
  		case MEDIR:
  			i = i+7;
  			estado = ENVIAR;
  			break;
  	
  		case ENVIAR:
  			
		
			
  			servo_send (0, i);
  			estado = ESPERAR;
  			
  			break;
  			
  		default:
  			break;
  	
  	}
  }
  
  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/



void servo_send (unsigned char motor, unsigned char posicion){
	mTrama[1] = motor; // Direccion del motor
	mTrama[2] = posicion;	// Posicion a colocar del servo
	AS2_SendBlock(mTrama, 3, &Enviados);
	AS1_SendBlock(mTrama, 3, &Enviados);
}
/* END ProcessorExpert */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.08]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/
