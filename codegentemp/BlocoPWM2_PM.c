/*******************************************************************************
* File Name: BlocoPWM2_PM.c
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

#include "BlocoPWM2.h"

static BlocoPWM2_backupStruct BlocoPWM2_backup;


/*******************************************************************************
* Function Name: BlocoPWM2_SaveConfig
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
*  BlocoPWM2_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void BlocoPWM2_SaveConfig(void) 
{

    #if(!BlocoPWM2_UsingFixedFunction)
        #if(!BlocoPWM2_PWMModeIsCenterAligned)
            BlocoPWM2_backup.PWMPeriod = BlocoPWM2_ReadPeriod();
        #endif /* (!BlocoPWM2_PWMModeIsCenterAligned) */
        BlocoPWM2_backup.PWMUdb = BlocoPWM2_ReadCounter();
        #if (BlocoPWM2_UseStatus)
            BlocoPWM2_backup.InterruptMaskValue = BlocoPWM2_STATUS_MASK;
        #endif /* (BlocoPWM2_UseStatus) */

        #if(BlocoPWM2_DeadBandMode == BlocoPWM2__B_PWM__DBM_256_CLOCKS || \
            BlocoPWM2_DeadBandMode == BlocoPWM2__B_PWM__DBM_2_4_CLOCKS)
            BlocoPWM2_backup.PWMdeadBandValue = BlocoPWM2_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(BlocoPWM2_KillModeMinTime)
             BlocoPWM2_backup.PWMKillCounterPeriod = BlocoPWM2_ReadKillTime();
        #endif /* (BlocoPWM2_KillModeMinTime) */

        #if(BlocoPWM2_UseControl)
            BlocoPWM2_backup.PWMControlRegister = BlocoPWM2_ReadControlRegister();
        #endif /* (BlocoPWM2_UseControl) */
    #endif  /* (!BlocoPWM2_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: BlocoPWM2_RestoreConfig
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
*  BlocoPWM2_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void BlocoPWM2_RestoreConfig(void) 
{
        #if(!BlocoPWM2_UsingFixedFunction)
            #if(!BlocoPWM2_PWMModeIsCenterAligned)
                BlocoPWM2_WritePeriod(BlocoPWM2_backup.PWMPeriod);
            #endif /* (!BlocoPWM2_PWMModeIsCenterAligned) */

            BlocoPWM2_WriteCounter(BlocoPWM2_backup.PWMUdb);

            #if (BlocoPWM2_UseStatus)
                BlocoPWM2_STATUS_MASK = BlocoPWM2_backup.InterruptMaskValue;
            #endif /* (BlocoPWM2_UseStatus) */

            #if(BlocoPWM2_DeadBandMode == BlocoPWM2__B_PWM__DBM_256_CLOCKS || \
                BlocoPWM2_DeadBandMode == BlocoPWM2__B_PWM__DBM_2_4_CLOCKS)
                BlocoPWM2_WriteDeadTime(BlocoPWM2_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(BlocoPWM2_KillModeMinTime)
                BlocoPWM2_WriteKillTime(BlocoPWM2_backup.PWMKillCounterPeriod);
            #endif /* (BlocoPWM2_KillModeMinTime) */

            #if(BlocoPWM2_UseControl)
                BlocoPWM2_WriteControlRegister(BlocoPWM2_backup.PWMControlRegister);
            #endif /* (BlocoPWM2_UseControl) */
        #endif  /* (!BlocoPWM2_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: BlocoPWM2_Sleep
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
*  BlocoPWM2_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void BlocoPWM2_Sleep(void) 
{
    #if(BlocoPWM2_UseControl)
        if(BlocoPWM2_CTRL_ENABLE == (BlocoPWM2_CONTROL & BlocoPWM2_CTRL_ENABLE))
        {
            /*Component is enabled */
            BlocoPWM2_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            BlocoPWM2_backup.PWMEnableState = 0u;
        }
    #endif /* (BlocoPWM2_UseControl) */

    /* Stop component */
    BlocoPWM2_Stop();

    /* Save registers configuration */
    BlocoPWM2_SaveConfig();
}


/*******************************************************************************
* Function Name: BlocoPWM2_Wakeup
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
*  BlocoPWM2_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void BlocoPWM2_Wakeup(void) 
{
     /* Restore registers values */
    BlocoPWM2_RestoreConfig();

    if(BlocoPWM2_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        BlocoPWM2_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
