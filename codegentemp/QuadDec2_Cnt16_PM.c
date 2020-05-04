/*******************************************************************************
* File Name: QuadDec2_Cnt16_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "QuadDec2_Cnt16.h"

static QuadDec2_Cnt16_backupStruct QuadDec2_Cnt16_backup;


/*******************************************************************************
* Function Name: QuadDec2_Cnt16_SaveConfig
********************************************************************************
* Summary:
*     Save the current user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  QuadDec2_Cnt16_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void QuadDec2_Cnt16_SaveConfig(void) 
{
    #if (!QuadDec2_Cnt16_UsingFixedFunction)

        QuadDec2_Cnt16_backup.CounterUdb = QuadDec2_Cnt16_ReadCounter();

        #if(!QuadDec2_Cnt16_ControlRegRemoved)
            QuadDec2_Cnt16_backup.CounterControlRegister = QuadDec2_Cnt16_ReadControlRegister();
        #endif /* (!QuadDec2_Cnt16_ControlRegRemoved) */

    #endif /* (!QuadDec2_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: QuadDec2_Cnt16_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  QuadDec2_Cnt16_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void QuadDec2_Cnt16_RestoreConfig(void) 
{      
    #if (!QuadDec2_Cnt16_UsingFixedFunction)

       QuadDec2_Cnt16_WriteCounter(QuadDec2_Cnt16_backup.CounterUdb);

        #if(!QuadDec2_Cnt16_ControlRegRemoved)
            QuadDec2_Cnt16_WriteControlRegister(QuadDec2_Cnt16_backup.CounterControlRegister);
        #endif /* (!QuadDec2_Cnt16_ControlRegRemoved) */

    #endif /* (!QuadDec2_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: QuadDec2_Cnt16_Sleep
********************************************************************************
* Summary:
*     Stop and Save the user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  QuadDec2_Cnt16_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void QuadDec2_Cnt16_Sleep(void) 
{
    #if(!QuadDec2_Cnt16_ControlRegRemoved)
        /* Save Counter's enable state */
        if(QuadDec2_Cnt16_CTRL_ENABLE == (QuadDec2_Cnt16_CONTROL & QuadDec2_Cnt16_CTRL_ENABLE))
        {
            /* Counter is enabled */
            QuadDec2_Cnt16_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            QuadDec2_Cnt16_backup.CounterEnableState = 0u;
        }
    #else
        QuadDec2_Cnt16_backup.CounterEnableState = 1u;
        if(QuadDec2_Cnt16_backup.CounterEnableState != 0u)
        {
            QuadDec2_Cnt16_backup.CounterEnableState = 0u;
        }
    #endif /* (!QuadDec2_Cnt16_ControlRegRemoved) */
    
    QuadDec2_Cnt16_Stop();
    QuadDec2_Cnt16_SaveConfig();
}


/*******************************************************************************
* Function Name: QuadDec2_Cnt16_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  QuadDec2_Cnt16_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void QuadDec2_Cnt16_Wakeup(void) 
{
    QuadDec2_Cnt16_RestoreConfig();
    #if(!QuadDec2_Cnt16_ControlRegRemoved)
        if(QuadDec2_Cnt16_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            QuadDec2_Cnt16_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!QuadDec2_Cnt16_ControlRegRemoved) */
    
}


/* [] END OF FILE */
