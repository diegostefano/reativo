/*******************************************************************************
* File Name: TimerCinematico_PM.c
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

#include "TimerCinematico.h"

static TimerCinematico_backupStruct TimerCinematico_backup;


/*******************************************************************************
* Function Name: TimerCinematico_SaveConfig
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
*  TimerCinematico_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void TimerCinematico_SaveConfig(void) 
{
    #if (!TimerCinematico_UsingFixedFunction)
        TimerCinematico_backup.TimerUdb = TimerCinematico_ReadCounter();
        TimerCinematico_backup.InterruptMaskValue = TimerCinematico_STATUS_MASK;
        #if (TimerCinematico_UsingHWCaptureCounter)
            TimerCinematico_backup.TimerCaptureCounter = TimerCinematico_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!TimerCinematico_UDB_CONTROL_REG_REMOVED)
            TimerCinematico_backup.TimerControlRegister = TimerCinematico_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: TimerCinematico_RestoreConfig
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
*  TimerCinematico_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void TimerCinematico_RestoreConfig(void) 
{   
    #if (!TimerCinematico_UsingFixedFunction)

        TimerCinematico_WriteCounter(TimerCinematico_backup.TimerUdb);
        TimerCinematico_STATUS_MASK =TimerCinematico_backup.InterruptMaskValue;
        #if (TimerCinematico_UsingHWCaptureCounter)
            TimerCinematico_SetCaptureCount(TimerCinematico_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!TimerCinematico_UDB_CONTROL_REG_REMOVED)
            TimerCinematico_WriteControlRegister(TimerCinematico_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: TimerCinematico_Sleep
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
*  TimerCinematico_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void TimerCinematico_Sleep(void) 
{
    #if(!TimerCinematico_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(TimerCinematico_CTRL_ENABLE == (TimerCinematico_CONTROL & TimerCinematico_CTRL_ENABLE))
        {
            /* Timer is enabled */
            TimerCinematico_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            TimerCinematico_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    TimerCinematico_Stop();
    TimerCinematico_SaveConfig();
}


/*******************************************************************************
* Function Name: TimerCinematico_Wakeup
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
*  TimerCinematico_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void TimerCinematico_Wakeup(void) 
{
    TimerCinematico_RestoreConfig();
    #if(!TimerCinematico_UDB_CONTROL_REG_REMOVED)
        if(TimerCinematico_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                TimerCinematico_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
