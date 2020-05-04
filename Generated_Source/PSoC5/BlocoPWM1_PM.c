/*******************************************************************************
* File Name: BlocoPWM1_PM.c
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

#include "BlocoPWM1.h"

static BlocoPWM1_backupStruct BlocoPWM1_backup;


/*******************************************************************************
* Function Name: BlocoPWM1_SaveConfig
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
*  BlocoPWM1_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void BlocoPWM1_SaveConfig(void) 
{

    #if(!BlocoPWM1_UsingFixedFunction)
        #if(!BlocoPWM1_PWMModeIsCenterAligned)
            BlocoPWM1_backup.PWMPeriod = BlocoPWM1_ReadPeriod();
        #endif /* (!BlocoPWM1_PWMModeIsCenterAligned) */
        BlocoPWM1_backup.PWMUdb = BlocoPWM1_ReadCounter();
        #if (BlocoPWM1_UseStatus)
            BlocoPWM1_backup.InterruptMaskValue = BlocoPWM1_STATUS_MASK;
        #endif /* (BlocoPWM1_UseStatus) */

        #if(BlocoPWM1_DeadBandMode == BlocoPWM1__B_PWM__DBM_256_CLOCKS || \
            BlocoPWM1_DeadBandMode == BlocoPWM1__B_PWM__DBM_2_4_CLOCKS)
            BlocoPWM1_backup.PWMdeadBandValue = BlocoPWM1_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(BlocoPWM1_KillModeMinTime)
             BlocoPWM1_backup.PWMKillCounterPeriod = BlocoPWM1_ReadKillTime();
        #endif /* (BlocoPWM1_KillModeMinTime) */

        #if(BlocoPWM1_UseControl)
            BlocoPWM1_backup.PWMControlRegister = BlocoPWM1_ReadControlRegister();
        #endif /* (BlocoPWM1_UseControl) */
    #endif  /* (!BlocoPWM1_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: BlocoPWM1_RestoreConfig
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
*  BlocoPWM1_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void BlocoPWM1_RestoreConfig(void) 
{
        #if(!BlocoPWM1_UsingFixedFunction)
            #if(!BlocoPWM1_PWMModeIsCenterAligned)
                BlocoPWM1_WritePeriod(BlocoPWM1_backup.PWMPeriod);
            #endif /* (!BlocoPWM1_PWMModeIsCenterAligned) */

            BlocoPWM1_WriteCounter(BlocoPWM1_backup.PWMUdb);

            #if (BlocoPWM1_UseStatus)
                BlocoPWM1_STATUS_MASK = BlocoPWM1_backup.InterruptMaskValue;
            #endif /* (BlocoPWM1_UseStatus) */

            #if(BlocoPWM1_DeadBandMode == BlocoPWM1__B_PWM__DBM_256_CLOCKS || \
                BlocoPWM1_DeadBandMode == BlocoPWM1__B_PWM__DBM_2_4_CLOCKS)
                BlocoPWM1_WriteDeadTime(BlocoPWM1_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(BlocoPWM1_KillModeMinTime)
                BlocoPWM1_WriteKillTime(BlocoPWM1_backup.PWMKillCounterPeriod);
            #endif /* (BlocoPWM1_KillModeMinTime) */

            #if(BlocoPWM1_UseControl)
                BlocoPWM1_WriteControlRegister(BlocoPWM1_backup.PWMControlRegister);
            #endif /* (BlocoPWM1_UseControl) */
        #endif  /* (!BlocoPWM1_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: BlocoPWM1_Sleep
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
*  BlocoPWM1_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void BlocoPWM1_Sleep(void) 
{
    #if(BlocoPWM1_UseControl)
        if(BlocoPWM1_CTRL_ENABLE == (BlocoPWM1_CONTROL & BlocoPWM1_CTRL_ENABLE))
        {
            /*Component is enabled */
            BlocoPWM1_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            BlocoPWM1_backup.PWMEnableState = 0u;
        }
    #endif /* (BlocoPWM1_UseControl) */

    /* Stop component */
    BlocoPWM1_Stop();

    /* Save registers configuration */
    BlocoPWM1_SaveConfig();
}


/*******************************************************************************
* Function Name: BlocoPWM1_Wakeup
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
*  BlocoPWM1_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void BlocoPWM1_Wakeup(void) 
{
     /* Restore registers values */
    BlocoPWM1_RestoreConfig();

    if(BlocoPWM1_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        BlocoPWM1_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
