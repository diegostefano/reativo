/*******************************************************************************
* File Name: QuadDec3_PM.c
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

#include "QuadDec3.h"

static QuadDec3_BACKUP_STRUCT QuadDec3_backup = {0u};


/*******************************************************************************
* Function Name: QuadDec3_SaveConfig
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
void QuadDec3_SaveConfig(void) 
{
    #if (QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_8_BIT)
        QuadDec3_Cnt8_SaveConfig();
    #else 
        /* (QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_16_BIT) || 
         * (QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_32_BIT)
         */
        QuadDec3_Cnt16_SaveConfig();
    #endif /* (QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: QuadDec3_RestoreConfig
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
void QuadDec3_RestoreConfig(void) 
{
    #if (QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_8_BIT)
        QuadDec3_Cnt8_RestoreConfig();
    #else 
        /* (QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_16_BIT) || 
         * (QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_32_BIT) 
         */
        QuadDec3_Cnt16_RestoreConfig();
    #endif /* (QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: QuadDec3_Sleep
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
*  QuadDec3_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void QuadDec3_Sleep(void) 
{
    if (0u != (QuadDec3_SR_AUX_CONTROL & QuadDec3_INTERRUPTS_ENABLE))
    {
        QuadDec3_backup.enableState = 1u;
    }
    else /* The Quadrature Decoder Component is disabled */
    {
        QuadDec3_backup.enableState = 0u;
    }

    QuadDec3_Stop();
    QuadDec3_SaveConfig();
}


/*******************************************************************************
* Function Name: QuadDec3_Wakeup
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
*  QuadDec3_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void QuadDec3_Wakeup(void) 
{
    QuadDec3_RestoreConfig();

    if (QuadDec3_backup.enableState != 0u)
    {
        #if (QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_8_BIT)
            QuadDec3_Cnt8_Enable();
        #else 
            /* (QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_16_BIT) || 
            *  (QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_32_BIT) 
            */
            QuadDec3_Cnt16_Enable();
        #endif /* (QuadDec3_COUNTER_SIZE == QuadDec3_COUNTER_SIZE_8_BIT) */

        /* Enable component's operation */
        QuadDec3_Enable();
    } /* Do nothing if component's block was disabled before */
}


/* [] END OF FILE */

