/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : FC161.c
**     Project     : Integracion_Fase1
**     Processor   : MC9S08QE128CLK
**     Component   : FreeCntr16
**     Version     : Component 02.078, Driver 01.22, CPU db: 3.00.067
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2018-03-04, 16:21, # CodeGen: 80
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
** @file FC161.c
** @version 01.22
** @brief
**         This device "FreeCntr16" implements 16-bit Free Running Counter
*/         
/*!
**  @addtogroup FC161_module FC161 module documentation
**  @{
*/         


/* MODULE FC161. */

#include "PE_Error.h"
#include "FC161.h"

#pragma MESSAGE DISABLE C4002          /* Disable warning C4002 "Result not used" */


static word TTicks;                    /* Counter of timer ticks */
static word LTicks;                    /* Working copy of variable TTicks */
static bool TOvf;                      /* Counter overflow flag */
static bool LOvf;                      /* Working copy of variable TOvf */

/*** Internal macros and method prototypes ***/

/*
** ===================================================================
**     Method      :  SetCV (component FreeCntr16)
**
**     Description :
**         The method computes and sets compare eventually modulo value 
**         for time measuring.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
#define FC161_SetCV(_Val) ( \
  TPM3MOD = (TPM3C2V = (word)(_Val)) )

/*
** ===================================================================
**     Method      :  LoadTicks (component FreeCntr16)
**
**     Description :
**         The method loads actual number of timer ticks and actual state 
**         of overflow flag.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void LoadTicks(void);

/*** End of Internal methods declarations ***/

/*
** ===================================================================
**     Method      :  LoadTicks (component FreeCntr16)
**
**     Description :
**         The method loads actual number of timer ticks and actual state 
**         of overflow flag.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void LoadTicks(void)
{
  EnterCritical();                     /* Save the PS register */
  LTicks = TTicks;                     /* Loading actual number of timer ticks */
  LOvf = TOvf;                         /* Loading actual state of "overflow flag" */
  ExitCritical();                      /* Restore the PS register */
}

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
byte FC161_Reset(void)
{
  EnterCritical();
  TPM3CNTH = 0x00U;                    /* Reset HW counter */
  TTicks =  0x00U;                     /* Reset counter of timer ticks */
  TOvf = FALSE;                        /* Reset counter overflow flag */
  ExitCritical();                      /* Restore the PS register */
  return ERR_OK;                       /* OK */
}

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
byte FC161_GetTimeUS(word *Time)
{
  dlong RtVal;                         /* Result of two 32-bit numbers multiplication */

  LoadTicks();                         /* Load actual state of counter */
  if (LOvf) {                          /* Testing counter overflow */
    return ERR_OVERFLOW;               /* If yes then error */
  }
  PE_Timer_LngMul((dword)LTicks, 0x01F405FBUL, &RtVal); /* Multiply timer ticks and High speed CPU mode coefficient */
  if (PE_Timer_LngHi2(RtVal[0], RtVal[1], Time)) { /* Get result value into word variable */
    return ERR_MATH;                   /* Overflow, value too big */
  } else {
    return ERR_OK;                     /* OK: Value calculated */
  }
}

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
byte FC161_GetTimeMS(word *Time)
{
  dlong RtVal;                         /* Result of two 32-bit numbers multiplication */

  LoadTicks();                         /* Load actual state of counter */
  if (LOvf) {                          /* Testing counter overflow */
    return ERR_OVERFLOW;               /* If yes then error */
  }
  PE_Timer_LngMul((dword)LTicks, 0x80018800UL, &RtVal); /* Multiply timer ticks and High speed CPU mode coefficient */
  if (PE_Timer_LngHi4(RtVal[0], RtVal[1], Time)) { /* Get result value into word variable */
    return ERR_MATH;                   /* Overflow, value too big */
  } else {
    return ERR_OK;                     /* OK: Value calculated */
  }
}

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
void FC161_Init(void)
{
  /* TPM3SC: TOF=0,TOIE=0,CPWMS=0,CLKSB=0,CLKSA=0,PS2=0,PS1=0,PS0=0 */
  setReg8(TPM3SC, 0x00U);              /* Stop HW; disable overflow interrupt and set prescaler to 0 */ 
  /* TPM3C2SC: CH2F=0,CH2IE=1,MS2B=0,MS2A=1,ELS2B=0,ELS2A=0,??=0,??=0 */
  setReg8(TPM3C2SC, 0x50U);            /* Set output compare mode and enable compare interrupt */ 
  TTicks = 0U;                         /* Counter of timer ticks */
  TOvf = FALSE;                        /* Counter overflow flag */
  FC161_SetCV(0x20C4U);                /* Initialize appropriate value to the compare/modulo/reload register */
  /* TPM3CNTH: BIT15=0,BIT14=0,BIT13=0,BIT12=0,BIT11=0,BIT10=0,BIT9=0,BIT8=0 */
  setReg8(TPM3CNTH, 0x00U);            /* Reset HW Counter */ 
  /* TPM3SC: TOF=0,TOIE=0,CPWMS=0,CLKSB=0,CLKSA=1,PS2=0,PS1=0,PS0=0 */
  setReg8(TPM3SC, 0x08U);              /* Set prescaler and run counter */ 
}

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
ISR(FC161_Interrupt)
{
  /* TPM3C2SC: CH2F=0 */
  clrReg8Bits(TPM3C2SC, 0x80U);        /* Reset compare interrupt request flag */ 
  if (++TTicks == 0x00U) {             /* Increment #ticks, check overflow */
    TOvf = TRUE;                       /* If yes then set overflow flag */
  }
}



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
