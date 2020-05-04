/*******************************************************************************
* File Name: QuadDec3.c  
* Version 3.0
*
* Description:
*  This file provides the source code to the API for the Quadrature Decoder
*  component.
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

#include "QuadDec3.h"

#if (QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_32_BIT)
    #include "QuadDec3_PVT.h"
#endif /* QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_32_BIT */

uint8 QuadDec3_initVar = 0u;


/*******************************************************************************
* Function Name: QuadDec3_Init
********************************************************************************
*
* Summary:
*  Inits/Restores default QuadDec configuration provided with customizer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void QuadDec3_Init(void) 
{
    #if (QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_32_BIT)
        /* Disable Interrupt. */
        CyIntDisable(QuadDec3_ISR_NUMBER);
        /* Set the ISR to point to the QuadDec3_isr Interrupt. */
        (void) CyIntSetVector(QuadDec3_ISR_NUMBER, & QuadDec3_ISR);
        /* Set the priority. */
        CyIntSetPriority(QuadDec3_ISR_NUMBER, QuadDec3_ISR_PRIORITY);
    #endif /* QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_32_BIT */
}


/*******************************************************************************
* Function Name: QuadDec3_Enable
********************************************************************************
*
* Summary:
*  This function enable interrupts from Component and also enable Component's
*  ISR in case of 32-bit counter.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void QuadDec3_Enable(void) 
{
    uint8 enableInterrupts;

    QuadDec3_SetInterruptMask(QuadDec3_INIT_INT_MASK);

    /* Clear pending interrupts. */
    (void) QuadDec3_GetEvents();
    
    enableInterrupts = CyEnterCriticalSection();

    /* Enable interrupts from Statusi register */
    QuadDec3_SR_AUX_CONTROL |= QuadDec3_INTERRUPTS_ENABLE;

    CyExitCriticalSection(enableInterrupts);        

    #if (QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_32_BIT)
        /* Enable Component interrupts */
        CyIntEnable(QuadDec3_ISR_NUMBER);
    #endif /* QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_32_BIT */
}


/*******************************************************************************
* Function Name: QuadDec3_Start
********************************************************************************
*
* Summary:
*  Initializes UDBs and other relevant hardware.
*  Resets counter, enables or disables all relevant interrupts.
*  Starts monitoring the inputs and counting.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  QuadDec3_initVar - used to check initial configuration, modified on
*  first function call.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void QuadDec3_Start(void) 
{
    #if (QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_8_BIT)
        QuadDec3_Cnt8_Start();
        QuadDec3_Cnt8_WriteCounter(QuadDec3_COUNTER_INIT_VALUE);
    #else
        /* (QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_16_BIT) || 
        *  (QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_32_BIT) 
        */
        QuadDec3_Cnt16_Start();
        QuadDec3_Cnt16_WriteCounter(QuadDec3_COUNTER_INIT_VALUE);
    #endif /* QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_8_BIT */
    
    #if (QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_32_BIT)        
       QuadDec3_count32SoftPart = 0;
    #endif /* QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_32_BIT */

    if (QuadDec3_initVar == 0u)
    {
        QuadDec3_Init();
        QuadDec3_initVar = 1u;
    }

    QuadDec3_Enable();
}


/*******************************************************************************
* Function Name: QuadDec3_Stop
********************************************************************************
*
* Summary:
*  Turns off UDBs and other relevant hardware.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void QuadDec3_Stop(void) 
{
    uint8 enableInterrupts;

    #if (QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_8_BIT)
        QuadDec3_Cnt8_Stop();
    #else 
        /* (QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_16_BIT) ||
        *  (QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_32_BIT)
        */
        QuadDec3_Cnt16_Stop();    /* counter disable */
    #endif /* (QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_8_BIT) */
 
    enableInterrupts = CyEnterCriticalSection();

    /* Disable interrupts interrupts from Statusi register */
    QuadDec3_SR_AUX_CONTROL &= (uint8) (~QuadDec3_INTERRUPTS_ENABLE);

    CyExitCriticalSection(enableInterrupts);

    #if (QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_32_BIT)
        CyIntDisable(QuadDec3_ISR_NUMBER);    /* interrupt disable */
    #endif /* QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_32_BIT */
}


/*******************************************************************************
* Function Name: QuadDec3_GetCounter
********************************************************************************
*
* Summary:
*  Reports the current value of the counter.
*
* Parameters:
*  None.
*
* Return:
*  The counter value. Return type is signed and per the counter size setting.
*  A positive value indicates clockwise movement (B before A).
*
* Global variables:
*  QuadDec3_count32SoftPart - used to get hi 16 bit for current value
*  of the 32-bit counter, when Counter size equal 32-bit.
*
*******************************************************************************/
int32 QuadDec3_GetCounter(void) 
{
    int32 count;
    uint16 tmpCnt;

    #if (QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_32_BIT)
        int16 hwCount;

        CyIntDisable(QuadDec3_ISR_NUMBER);

        tmpCnt = QuadDec3_Cnt16_ReadCounter();
        hwCount = (int16) ((int32) tmpCnt - (int32) QuadDec3_COUNTER_INIT_VALUE);
        count = QuadDec3_count32SoftPart + hwCount;

        CyIntEnable(QuadDec3_ISR_NUMBER);
    #else 
        /* (QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_8_BIT) || 
        *  (QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_16_BIT)
        */
        #if (QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_8_BIT)
            tmpCnt = QuadDec3_Cnt8_ReadCounter();
        #else /* (QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_16_BIT) */
            tmpCnt = QuadDec3_Cnt16_ReadCounter();
        #endif  /* QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_8_BIT */

        count = (int32) ((int32) tmpCnt -
                (int32) QuadDec3_COUNTER_INIT_VALUE);

    #endif /* QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_32_BIT */ 

    return (count);
}


/*******************************************************************************
* Function Name: QuadDec3_SetCounter
********************************************************************************
*
* Summary:
*  Sets the current value of the counter.
*
* Parameters:
*  value:  The new value. Parameter type is signed and per the counter size
*  setting.
*
* Return:
*  None.
*
* Global variables:
*  QuadDec3_count32SoftPart - modified to set hi 16 bit for current
*  value of the 32-bit counter, when Counter size equal 32-bit.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void QuadDec3_SetCounter(int32 value) 
{
    #if ((QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_8_BIT) || \
         (QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_16_BIT))
        uint16 count;
        
        if (value >= 0)
        {
            count = (uint16) value + QuadDec3_COUNTER_INIT_VALUE;
        }
        else
        {
            count = QuadDec3_COUNTER_INIT_VALUE - (uint16)(-value);
        }
        #if (QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_8_BIT)
            QuadDec3_Cnt8_WriteCounter(count);
        #else /* (QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_16_BIT) */
            QuadDec3_Cnt16_WriteCounter(count);
        #endif  /* QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_8_BIT */
    #else /* (QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_32_BIT) */
        CyIntDisable(QuadDec3_ISR_NUMBER);

        QuadDec3_Cnt16_WriteCounter(QuadDec3_COUNTER_INIT_VALUE);
        QuadDec3_count32SoftPart = value;

        CyIntEnable(QuadDec3_ISR_NUMBER);
    #endif  /* (QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_8_BIT) ||
             * (QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_16_BIT)
             */
}


/*******************************************************************************
* Function Name: QuadDec3_GetEvents
********************************************************************************
* 
* Summary:
*   Reports the current status of events. This function clears the bits of the 
*   status register.
*
* Parameters:
*  None.
*
* Return:
*  The events, as bits in an unsigned 8-bit value:
*    Bit      Description
*     0        Counter overflow.
*     1        Counter underflow.
*     2        Counter reset due to index, if index input is used.
*     3        Invalid A, B inputs state transition.
*
*******************************************************************************/
uint8 QuadDec3_GetEvents(void) 
{
    return (QuadDec3_STATUS_REG & QuadDec3_INIT_INT_MASK);
}


/*******************************************************************************
* Function Name: QuadDec3_SetInterruptMask
********************************************************************************
*
* Summary:
*  Enables / disables interrupts due to the events.
*  For the 32-bit counter, the overflow, underflow and reset interrupts cannot
*  be disabled, these bits are ignored.
*
* Parameters:
*  mask: Enable / disable bits in an 8-bit value, where 1 enables the interrupt.
*
* Return:
*  None.
*
*******************************************************************************/
void QuadDec3_SetInterruptMask(uint8 mask) 
{
    #if (QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_32_BIT)
        /* Underflow, Overflow and Reset interrupts for 32-bit Counter are always enable */
        mask |= (QuadDec3_COUNTER_OVERFLOW | QuadDec3_COUNTER_UNDERFLOW |
                 QuadDec3_COUNTER_RESET);
    #endif /* QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_32_BIT */

    QuadDec3_STATUS_MASK = mask;
}


/*******************************************************************************
* Function Name: QuadDec3_GetInterruptMask
********************************************************************************
*
* Summary:
*  Reports the current interrupt mask settings.
*
* Parameters:
*  None.
*
* Return:
*  Enable / disable bits in an 8-bit value, where 1 enables the interrupt.
*  For the 32-bit counter, the overflow, underflow and reset enable bits are
*  always set.
*
*******************************************************************************/
uint8 QuadDec3_GetInterruptMask(void) 
{
    return (QuadDec3_STATUS_MASK & QuadDec3_INIT_INT_MASK);
}


/* [] END OF FILE */
