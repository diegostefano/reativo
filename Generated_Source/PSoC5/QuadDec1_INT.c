/*******************************************************************************
* File Name: QuadDec1_INT.c
* Version 3.0
*
* Description:
*  This file contains the Interrupt Service Routine (ISR) for the Quadrature
*  Decoder component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "QuadDec1.h"
#include "QuadDec1_PVT.h"
#include "cyapicallbacks.h"

volatile int32 QuadDec1_count32SoftPart = 0;


/*******************************************************************************
* FUNCTION NAME: void QuadDec1_ISR
********************************************************************************
*
* Summary:
*  Interrupt Service Routine for Quadrature Decoder Component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  QuadDec1_count32SoftPart - modified to update hi 16 bit for current
*  value of the 32-bit counter, when Counter size equal 32-bit.
*  QuadDec1_swStatus - modified with the updated values of STATUS
*  register.
*
*******************************************************************************/
CY_ISR( QuadDec1_ISR )
{
   uint8 QuadDec1_swStatus;

   QuadDec1_swStatus = QuadDec1_STATUS_REG;

    #ifdef QuadDec1_ISR_ENTRY_CALLBACK
        QuadDec1_ISR_EntryCallback();
    #endif /* QuadDec1_ISR_ENTRY_CALLBACK */

    /* User code required at start of ISR */
    /* `#START QuadDec1_ISR_START` */

    /* `#END` */

    if (0u != (QuadDec1_swStatus & QuadDec1_COUNTER_OVERFLOW))
    {
        QuadDec1_count32SoftPart += (int32) QuadDec1_COUNTER_MAX_VALUE;
    }
    else if (0u != (QuadDec1_swStatus & QuadDec1_COUNTER_UNDERFLOW))
    {
        QuadDec1_count32SoftPart -= (int32) QuadDec1_COUNTER_INIT_VALUE;
    }
    else
    {
        /* Nothing to do here */
    }
    
    if (0u != (QuadDec1_swStatus & QuadDec1_COUNTER_RESET))
    {
        QuadDec1_count32SoftPart = 0;
    }
    
    /* User code required at end of ISR */
    /* `#START QuadDec1_ISR_END` */

    /* `#END` */

    #ifdef QuadDec1_ISR_EXIT_CALLBACK
        QuadDec1_ISR_ExitCallback();
    #endif /* QuadDec1_ISR_EXIT_CALLBACK */
}


/* [] END OF FILE */
