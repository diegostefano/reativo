/*******************************************************************************
* File Name: TimerMotores_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "TimerMotores.h"

static TimerMotores_backupStruct TimerMotores_backup;


/*******************************************************************************
* Function Name: TimerMotores_SaveConfig
********************************************************************************
*
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
*  TimerMotores_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void TimerMotores_SaveConfig(void) 
{
    #if (!TimerMotores_UsingFixedFunction)
        TimerMotores_backup.TimerUdb = TimerMotores_ReadCounter();
        TimerMotores_backup.InterruptMaskValue = TimerMotores_STATUS_MASK;
        #if (TimerMotores_UsingHWCaptureCounter)
            TimerMotores_backup.TimerCaptureCounter = TimerMotores_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!TimerMotores_UDB_CONTROL_REG_REMOVED)
            TimerMotores_backup.TimerControlRegister = TimerMotores_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: TimerMotores_RestoreConfig
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
*  TimerMotores_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void TimerMotores_RestoreConfig(void) 
{   
    #if (!TimerMotores_UsingFixedFunction)

        TimerMotores_WriteCounter(TimerMotores_backup.TimerUdb);
        TimerMotores_STATUS_MASK =TimerMotores_backup.InterruptMaskValue;
        #if (TimerMotores_UsingHWCaptureCounter)
            TimerMotores_SetCaptureCount(TimerMotores_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!TimerMotores_UDB_CONTROL_REG_REMOVED)
            TimerMotores_WriteControlRegister(TimerMotores_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: TimerMotores_Sleep
********************************************************************************
*
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
*  TimerMotores_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void TimerMotores_Sleep(void) 
{
    #if(!TimerMotores_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(TimerMotores_CTRL_ENABLE == (TimerMotores_CONTROL & TimerMotores_CTRL_ENABLE))
        {
            /* Timer is enabled */
            TimerMotores_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            TimerMotores_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    TimerMotores_Stop();
    TimerMotores_SaveConfig();
}


/*******************************************************************************
* Function Name: TimerMotores_Wakeup
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
*  TimerMotores_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void TimerMotores_Wakeup(void) 
{
    TimerMotores_RestoreConfig();
    #if(!TimerMotores_UDB_CONTROL_REG_REMOVED)
        if(TimerMotores_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                TimerMotores_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
