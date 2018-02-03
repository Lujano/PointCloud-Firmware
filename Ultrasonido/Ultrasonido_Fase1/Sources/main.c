/* ###################################################################
**     Filename    : main.c
**     Project     : Ultrasonido_Fase1
**     Processor   : MC9S08QE128CLK
**     Version     : Driver 01.12
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2018-02-03, 08:14, # CodeGen: 0
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
#include "TI1.h"
#include "AS2.h"
#include "Bit1.h"
#include "TI2.h"
#include "Bit2.h"
#include "Cap1.h"
#include "Bit3.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

unsigned char estado = ESPERAR;
unsigned char estado_trigger = TRIGGER_TERMINADO;
unsigned char estado_echo = ECHO_TERMINADO;

unsigned int medicion = 0;

void trigger(void);
void init(void);
/* User includes (#include below this line is not maintained by Processor Expert) */
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
  			trigger();
  			estado_echo = ECHO_TRIGGERED;
  			while(estado_echo!= ECHO_TERMINADO){
  				
  			}
  			estado = ENVIAR;
  			break;
	  			
  		case ENVIAR:
  			AS1_SendChar((medicion) & 0xFF);
  			AS1_SendChar((medicion>>8) & 0xFF);
  			  			
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



void trigger(void){
	estado_trigger = TRIGGER_BAJO;
	TI1_Enable();
	while (estado_trigger != TRIGGER_TERMINADO){
		}
	TI1_Disable();	
}

void init(void){
	Bit1_ClrVal();
	
};
/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/
