/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : FC161.h
**     Project     : Integracion_Fase3
**     Processor   : MC9S08QE128CLK
**     Component   : FreeCntr16
**     Version     : Component 02.078, Driver 01.22, CPU db: 3.00.067
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2018-03-29, 23:43, # CodeGen: 1
**     Abstract    :
**         This device "FreeCntr16" implements 16-bit Free Running Counter
**     Settings    :
**         Timer name                  : TPM3 (16-bit)
**         Compare name                : TPM32
**         Counter shared              : No
**
**         High speed mode
**             Prescaler               : divide-by-1
**             Clock                   : 16777216 Hz
**           Resolution of timer
**             Xtal ticks              : 16
**             microseconds            : 500
**             milliseconds            : 1
**             seconds (real)          : 0.000500023365
**             Hz                      : 2000
**             kHz                     : 2
**
**         Initialization:
**              Timer                  : Enabled
**
**         Timer registers
**              Counter                : TPM3CNT   [$0061]
**              Mode                   : TPM3SC    [$0060]
**              Run                    : TPM3SC    [$0060]
**              Prescaler              : TPM3SC    [$0060]
**
**         Compare registers
**              Compare                : TPM3C2V   [$006C]
**     Contents    :
**         Reset     - byte FC161_Reset(void);
**         GetTimeUS - byte FC161_GetTimeUS(word *Time);
**         GetTimeMS - byte FC161_GetTimeMS(word *Time);
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file FC161.h
** @version 01.22
** @brief
**         This device "FreeCntr16" implements 16-bit Free Running Counter
*/         
/*!
**  @addtogroup FC161_module FC161 module documentation
**  @{
*/         

#ifndef __FC161
#define __FC161

/* MODULE FC161. */

/*Include shared modules, which are used for whole project*/
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PE_Timer.h"
#include "Cpu.h"

byte FC161_Reset(void);
/*
** ===================================================================
**     Method      :  FC161_Reset (component FreeCntr16)
*/
/*!
**     @brief
**         This method clears the counter.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
*/
/* ===================================================================*/

byte FC161_GetTimeUS(word *Time);
/*
** ===================================================================
**     Method      :  FC161_GetTimeUS (component FreeCntr16)
**     Description :
**         Returns the time (as a 16-bit unsigned integer) in microseconds
**         since the last resetting after the last reset.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Time            - A pointer to the returned 16-bit value
**                           in microseconds
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_OVERFLOW - Software counter overflow
**                           ERR_MATH - Overflow during evaluation
** ===================================================================
*/

byte FC161_GetTimeMS(word *Time);
/*
** ===================================================================
**     Method      :  FC161_GetTimeMS (component FreeCntr16)
**     Description :
**         Returns the time (as a 16-bit unsigned integer) in milliseconds
**         since the last resetting after the last reset.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Time            - A pointer to the returned 16-bit value
**                           in milliseconds
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_OVERFLOW - Software counter overflow
**                           ERR_MATH - Overflow during evaluation
** ===================================================================
*/

void FC161_Init(void);
/*
** ===================================================================
**     Method      :  FC161_Init (component FreeCntr16)
**
**     Description :
**         Initializes the associated peripheral(s) and the component 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

__interrupt void FC161_Interrupt(void);
/*
** ===================================================================
**     Method      :  FC161_Interrupt (component FreeCntr16)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes the component event(s).
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/


/* END FC161. */

#endif /* ifndef __FC161 */
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
