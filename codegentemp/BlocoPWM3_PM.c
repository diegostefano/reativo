/*******************************************************************************
* File Name: BlocoPWM3_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "BlocoPWM3.h"

static BlocoPWM3_backupStruct BlocoPWM3_backup;


/*******************************************************************************
* Function Name: BlocoPWM3_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  BlocoPWM3_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void BlocoPWM3_SaveConfig(void) 
{

    #if(!BlocoPWM3_UsingFixedFunction)
        #if(!BlocoPWM3_PWMModeIsCenterAligned)
            BlocoPWM3_backup.PWMPeriod = BlocoPWM3_ReadPeriod();
        #endif /* (!BlocoPWM3_PWMModeIsCenterAligned) */
        BlocoPWM3_backup.PWMUdb = BlocoPWM3_ReadCounter();
        #if (BlocoPWM3_UseStatus)
            BlocoPWM3_backup.InterruptMaskValue = BlocoPWM3_STATUS_MASK;
        #endif /* (BlocoPWM3_UseStatus) */

        #if(BlocoPWM3_DeadBandMode == BlocoPWM3__B_PWM__DBM_256_CLOCKS || \
            BlocoPWM3_DeadBandMode == BlocoPWM3__B_PWM__DBM_2_4_CLOCKS)
            BlocoPWM3_backup.PWMdeadBandValue = BlocoPWM3_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(BlocoPWM3_KillModeMinTime)
             BlocoPWM3_backup.PWMKillCounterPeriod = BlocoPWM3_ReadKillTime();
        #endif /* (BlocoPWM3_KillModeMinTime) */

        #if(BlocoPWM3_UseControl)
            BlocoPWM3_backup.PWMControlRegister = BlocoPWM3_ReadControlRegister();
        #endif /* (BlocoPWM3_UseControl) */
    #endif  /* (!BlocoPWM3_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: BlocoPWM3_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  BlocoPWM3_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void BlocoPWM3_RestoreConfig(void) 
{
        #if(!BlocoPWM3_UsingFixedFunction)
            #if(!BlocoPWM3_PWMModeIsCenterAligned)
                BlocoPWM3_WritePeriod(BlocoPWM3_backup.PWMPeriod);
            #endif /* (!BlocoPWM3_PWMModeIsCenterAligned) */

            BlocoPWM3_WriteCounter(BlocoPWM3_backup.PWMUdb);

            #if (BlocoPWM3_UseStatus)
                BlocoPWM3_STATUS_MASK = BlocoPWM3_backup.InterruptMaskValue;
            #endif /* (BlocoPWM3_UseStatus) */

            #if(BlocoPWM3_DeadBandMode == BlocoPWM3__B_PWM__DBM_256_CLOCKS || \
                BlocoPWM3_DeadBandMode == BlocoPWM3__B_PWM__DBM_2_4_CLOCKS)
                BlocoPWM3_WriteDeadTime(BlocoPWM3_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(BlocoPWM3_KillModeMinTime)
                BlocoPWM3_WriteKillTime(BlocoPWM3_backup.PWMKillCounterPeriod);
            #endif /* (BlocoPWM3_KillModeMinTime) */

            #if(BlocoPWM3_UseControl)
                BlocoPWM3_WriteControlRegister(BlocoPWM3_backup.PWMControlRegister);
            #endif /* (BlocoPWM3_UseControl) */
        #endif  /* (!BlocoPWM3_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: BlocoPWM3_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  BlocoPWM3_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void BlocoPWM3_Sleep(void) 
{
    #if(BlocoPWM3_UseControl)
        if(BlocoPWM3_CTRL_ENABLE == (BlocoPWM3_CONTROL & BlocoPWM3_CTRL_ENABLE))
        {
            /*Component is enabled */
            BlocoPWM3_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            BlocoPWM3_backup.PWMEnableState = 0u;
        }
    #endif /* (BlocoPWM3_UseControl) */

    /* Stop component */
    BlocoPWM3_Stop();

    /* Save registers configuration */
    BlocoPWM3_SaveConfig();
}


/*******************************************************************************
* Function Name: BlocoPWM3_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  BlocoPWM3_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void BlocoPWM3_Wakeup(void) 
{
     /* Restore registers values */
    BlocoPWM3_RestoreConfig();

    if(BlocoPWM3_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        BlocoPWM3_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
