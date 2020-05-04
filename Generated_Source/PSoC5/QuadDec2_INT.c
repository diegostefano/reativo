/*******************************************************************************
* File Name: QuadDec2_INT.c
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

#include "QuadDec2.h"
#include "QuadDec2_PVT.h"
#include "cyapicallbacks.h"

volatile int32 QuadDec2_count32SoftPart = 0;


/*******************************************************************************
* FUNCTION NAME: void QuadDec2_ISR
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
*  QuadDec2_count32SoftPart - modified to update hi 16 bit for current
*  value of the 32-bit counter, when Counter size equal 32-bit.
*  QuadDec2_swStatus - modified with the updated values of STATUS
*  register.
*
*******************************************************************************/
CY_ISR( QuadDec2_ISR )
{
   uint8 QuadDec2_swStatus;

   QuadDec2_swStatus = QuadDec2_STATUS_REG;

    #ifdef QuadDec2_ISR_ENTRY_CALLBACK
        QuadDec2_ISR_EntryCallback();
    #endif /* QuadDec2_ISR_ENTRY_CALLBACK */

    /* User code required at start of ISR */
    /* `#START QuadDec2_ISR_START` */

    /* `#END` */

    if (0u != (QuadDec2_swStatus & QuadDec2_COUNTER_OVERFLOW))
    {
        QuadDec2_count32SoftPart += (int32) QuadDec2_COUNTER_MAX_VALUE;
    }
    else if (0u != (QuadDec2_swStatus & QuadDec2_COUNTER_UNDERFLOW))
    {
        QuadDec2_count32SoftPart -= (int32) QuadDec2_COUNTER_INIT_VALUE;
    }
    else
    {
        /* Nothing to do here */
    }
    
    if (0u != (QuadDec2_swStatus & QuadDec2_COUNTER_RESET))
    {
        QuadDec2_count32SoftPart = 0;
    }
    
    /* User code required at end of ISR */
    /* `#START QuadDec2_ISR_END` */

    /* `#END` */

    #ifdef QuadDec2_ISR_EXIT_CALLBACK
        QuadDec2_ISR_ExitCallback();
    #endif /* QuadDec2_ISR_EXIT_CALLBACK */
}


/* [] END OF FILE */
