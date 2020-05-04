/*******************************************************************************
* File Name: QuadDec2_PM.c
* Version 3.0
*
* Description:
*  This file contains the setup, control and status commands to support 
*  component operations in low power mode.  
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

static QuadDec2_BACKUP_STRUCT QuadDec2_backup = {0u};


/*******************************************************************************
* Function Name: QuadDec2_SaveConfig
********************************************************************************
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void QuadDec2_SaveConfig(void) 
{
    #if (QuadDec2_COUNTER_SIZE == QuadDec2_COUNTER_SIZE_8_BIT)
        QuadDec2_Cnt8_SaveConfig();
    #else 
        /* (QuadDec2_COUNTER_SIZE == QuadDec2_COUNTER_SIZE_16_BIT) || 
         * (QuadDec2_COUNTER_SIZE == QuadDec2_COUNTER_SIZE_32_BIT)
         */
        QuadDec2_Cnt16_SaveConfig();
    #endif /* (QuadDec2_COUNTER_SIZE == QuadDec2_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: QuadDec2_RestoreConfig
********************************************************************************
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void QuadDec2_RestoreConfig(void) 
{
    #if (QuadDec2_COUNTER_SIZE == QuadDec2_COUNTER_SIZE_8_BIT)
        QuadDec2_Cnt8_RestoreConfig();
    #else 
        /* (QuadDec2_COUNTER_SIZE == QuadDec2_COUNTER_SIZE_16_BIT) || 
         * (QuadDec2_COUNTER_SIZE == QuadDec2_COUNTER_SIZE_32_BIT) 
         */
        QuadDec2_Cnt16_RestoreConfig();
    #endif /* (QuadDec2_COUNTER_SIZE == QuadDec2_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: QuadDec2_Sleep
********************************************************************************
* 
* Summary:
*  Prepare Quadrature Decoder Component goes to sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  QuadDec2_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void QuadDec2_Sleep(void) 
{
    if (0u != (QuadDec2_SR_AUX_CONTROL & QuadDec2_INTERRUPTS_ENABLE))
    {
        QuadDec2_backup.enableState = 1u;
    }
    else /* The Quadrature Decoder Component is disabled */
    {
        QuadDec2_backup.enableState = 0u;
    }

    QuadDec2_Stop();
    QuadDec2_SaveConfig();
}


/*******************************************************************************
* Function Name: QuadDec2_Wakeup
********************************************************************************
*
* Summary:
*  Prepare Quadrature Decoder Component to wake up.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  QuadDec2_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void QuadDec2_Wakeup(void) 
{
    QuadDec2_RestoreConfig();

    if (QuadDec2_backup.enableState != 0u)
    {
        #if (QuadDec2_COUNTER_SIZE == QuadDec2_COUNTER_SIZE_8_BIT)
            QuadDec2_Cnt8_Enable();
        #else 
            /* (QuadDec2_COUNTER_SIZE == QuadDec2_COUNTER_SIZE_16_BIT) || 
            *  (QuadDec2_COUNTER_SIZE == QuadDec2_COUNTER_SIZE_32_BIT) 
            */
            QuadDec2_Cnt16_Enable();
        #endif /* (QuadDec2_COUNTER_SIZE == QuadDec2_COUNTER_SIZE_8_BIT) */

        /* Enable component's operation */
        QuadDec2_Enable();
    } /* Do nothing if component's block was disabled before */
}


/* [] END OF FILE */

