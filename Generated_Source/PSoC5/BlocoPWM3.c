/*******************************************************************************
* File Name: BlocoPWM3.c
* Version 3.30
*
* Description:
*  The PWM User Module consist of an 8 or 16-bit counter with two 8 or 16-bit
*  comparitors. Each instance of this user module is capable of generating
*  two PWM outputs with the same period. The pulse width is selectable between
*  1 and 255/65535. The period is selectable between 2 and 255/65536 clocks.
*  The compare value output may be configured to be active when the present
*  counter is less than or less than/equal to the compare value.
*  A terminal count output is also provided. It generates a pulse one clock
*  width wide when the counter is equal to zero.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "BlocoPWM3.h"

/* Error message for removed <resource> through optimization */
#ifdef BlocoPWM3_PWMUDB_genblk1_ctrlreg__REMOVED
    #error PWM_v3_30 detected with a constant 0 for the enable or \
         constant 1 for reset. This will prevent the component from operating.
#endif /* BlocoPWM3_PWMUDB_genblk1_ctrlreg__REMOVED */

uint8 BlocoPWM3_initVar = 0u;


/*******************************************************************************
* Function Name: BlocoPWM3_Start
********************************************************************************
*
* Summary:
*  The start function initializes the pwm with the default values, the
*  enables the counter to begin counting.  It does not enable interrupts,
*  the EnableInt command should be called if interrupt generation is required.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  BlocoPWM3_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void BlocoPWM3_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(BlocoPWM3_initVar == 0u)
    {
        BlocoPWM3_Init();
        BlocoPWM3_initVar = 1u;
    }
    BlocoPWM3_Enable();

}


/*******************************************************************************
* Function Name: BlocoPWM3_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  BlocoPWM3_Start().
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void BlocoPWM3_Init(void) 
{
    #if (BlocoPWM3_UsingFixedFunction || BlocoPWM3_UseControl)
        uint8 ctrl;
    #endif /* (BlocoPWM3_UsingFixedFunction || BlocoPWM3_UseControl) */

    #if(!BlocoPWM3_UsingFixedFunction)
        #if(BlocoPWM3_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 BlocoPWM3_interruptState;
        #endif /* (BlocoPWM3_UseStatus) */
    #endif /* (!BlocoPWM3_UsingFixedFunction) */

    #if (BlocoPWM3_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        BlocoPWM3_CONTROL |= BlocoPWM3_CFG0_MODE;
        #if (BlocoPWM3_DeadBand2_4)
            BlocoPWM3_CONTROL |= BlocoPWM3_CFG0_DB;
        #endif /* (BlocoPWM3_DeadBand2_4) */

        ctrl = BlocoPWM3_CONTROL3 & ((uint8 )(~BlocoPWM3_CTRL_CMPMODE1_MASK));
        BlocoPWM3_CONTROL3 = ctrl | BlocoPWM3_DEFAULT_COMPARE1_MODE;

         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        BlocoPWM3_RT1 &= ((uint8)(~BlocoPWM3_RT1_MASK));
        BlocoPWM3_RT1 |= BlocoPWM3_SYNC;

        /*Enable DSI Sync all all inputs of the PWM*/
        BlocoPWM3_RT1 &= ((uint8)(~BlocoPWM3_SYNCDSI_MASK));
        BlocoPWM3_RT1 |= BlocoPWM3_SYNCDSI_EN;

    #elif (BlocoPWM3_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = BlocoPWM3_CONTROL & ((uint8)(~BlocoPWM3_CTRL_CMPMODE2_MASK)) &
                ((uint8)(~BlocoPWM3_CTRL_CMPMODE1_MASK));
        BlocoPWM3_CONTROL = ctrl | BlocoPWM3_DEFAULT_COMPARE2_MODE |
                                   BlocoPWM3_DEFAULT_COMPARE1_MODE;
    #endif /* (BlocoPWM3_UsingFixedFunction) */

    #if (!BlocoPWM3_UsingFixedFunction)
        #if (BlocoPWM3_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            BlocoPWM3_AUX_CONTROLDP0 |= (BlocoPWM3_AUX_CTRL_FIFO0_CLR);
        #else /* (BlocoPWM3_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            BlocoPWM3_AUX_CONTROLDP0 |= (BlocoPWM3_AUX_CTRL_FIFO0_CLR);
            BlocoPWM3_AUX_CONTROLDP1 |= (BlocoPWM3_AUX_CTRL_FIFO0_CLR);
        #endif /* (BlocoPWM3_Resolution == 8) */

        BlocoPWM3_WriteCounter(BlocoPWM3_INIT_PERIOD_VALUE);
    #endif /* (!BlocoPWM3_UsingFixedFunction) */

    BlocoPWM3_WritePeriod(BlocoPWM3_INIT_PERIOD_VALUE);

        #if (BlocoPWM3_UseOneCompareMode)
            BlocoPWM3_WriteCompare(BlocoPWM3_INIT_COMPARE_VALUE1);
        #else
            BlocoPWM3_WriteCompare1(BlocoPWM3_INIT_COMPARE_VALUE1);
            BlocoPWM3_WriteCompare2(BlocoPWM3_INIT_COMPARE_VALUE2);
        #endif /* (BlocoPWM3_UseOneCompareMode) */

        #if (BlocoPWM3_KillModeMinTime)
            BlocoPWM3_WriteKillTime(BlocoPWM3_MinimumKillTime);
        #endif /* (BlocoPWM3_KillModeMinTime) */

        #if (BlocoPWM3_DeadBandUsed)
            BlocoPWM3_WriteDeadTime(BlocoPWM3_INIT_DEAD_TIME);
        #endif /* (BlocoPWM3_DeadBandUsed) */

    #if (BlocoPWM3_UseStatus || BlocoPWM3_UsingFixedFunction)
        BlocoPWM3_SetInterruptMode(BlocoPWM3_INIT_INTERRUPTS_MODE);
    #endif /* (BlocoPWM3_UseStatus || BlocoPWM3_UsingFixedFunction) */

    #if (BlocoPWM3_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        BlocoPWM3_GLOBAL_ENABLE |= BlocoPWM3_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        BlocoPWM3_CONTROL2 |= BlocoPWM3_CTRL2_IRQ_SEL;
    #else
        #if(BlocoPWM3_UseStatus)

            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            BlocoPWM3_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            BlocoPWM3_STATUS_AUX_CTRL |= BlocoPWM3_STATUS_ACTL_INT_EN_MASK;

             /* Exit Critical Region*/
            CyExitCriticalSection(BlocoPWM3_interruptState);

            /* Clear the FIFO to enable the BlocoPWM3_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            BlocoPWM3_ClearFIFO();
        #endif /* (BlocoPWM3_UseStatus) */
    #endif /* (BlocoPWM3_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: BlocoPWM3_Enable
********************************************************************************
*
* Summary:
*  Enables the PWM block operation
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  This works only if software enable mode is chosen
*
*******************************************************************************/
void BlocoPWM3_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (BlocoPWM3_UsingFixedFunction)
        BlocoPWM3_GLOBAL_ENABLE |= BlocoPWM3_BLOCK_EN_MASK;
        BlocoPWM3_GLOBAL_STBY_ENABLE |= BlocoPWM3_BLOCK_STBY_EN_MASK;
    #endif /* (BlocoPWM3_UsingFixedFunction) */

    /* Enable the PWM from the control register  */
    #if (BlocoPWM3_UseControl || BlocoPWM3_UsingFixedFunction)
        BlocoPWM3_CONTROL |= BlocoPWM3_CTRL_ENABLE;
    #endif /* (BlocoPWM3_UseControl || BlocoPWM3_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: BlocoPWM3_Stop
********************************************************************************
*
* Summary:
*  The stop function halts the PWM, but does not change any modes or disable
*  interrupts.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  If the Enable mode is set to Hardware only then this function
*  has no effect on the operation of the PWM
*
*******************************************************************************/
void BlocoPWM3_Stop(void) 
{
    #if (BlocoPWM3_UseControl || BlocoPWM3_UsingFixedFunction)
        BlocoPWM3_CONTROL &= ((uint8)(~BlocoPWM3_CTRL_ENABLE));
    #endif /* (BlocoPWM3_UseControl || BlocoPWM3_UsingFixedFunction) */

    /* Globally disable the Fixed Function Block chosen */
    #if (BlocoPWM3_UsingFixedFunction)
        BlocoPWM3_GLOBAL_ENABLE &= ((uint8)(~BlocoPWM3_BLOCK_EN_MASK));
        BlocoPWM3_GLOBAL_STBY_ENABLE &= ((uint8)(~BlocoPWM3_BLOCK_STBY_EN_MASK));
    #endif /* (BlocoPWM3_UsingFixedFunction) */
}

#if (BlocoPWM3_UseOneCompareMode)
    #if (BlocoPWM3_CompareMode1SW)


        /*******************************************************************************
        * Function Name: BlocoPWM3_SetCompareMode
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm output when in Dither mode,
        *  Center Align Mode or One Output Mode.
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void BlocoPWM3_SetCompareMode(uint8 comparemode) 
        {
            #if(BlocoPWM3_UsingFixedFunction)

                #if(0 != BlocoPWM3_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << BlocoPWM3_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != BlocoPWM3_CTRL_CMPMODE1_SHIFT) */

                BlocoPWM3_CONTROL3 &= ((uint8)(~BlocoPWM3_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
                BlocoPWM3_CONTROL3 |= comparemodemasked;

            #elif (BlocoPWM3_UseControl)

                #if(0 != BlocoPWM3_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << BlocoPWM3_CTRL_CMPMODE1_SHIFT)) &
                                                BlocoPWM3_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & BlocoPWM3_CTRL_CMPMODE1_MASK;
                #endif /* (0 != BlocoPWM3_CTRL_CMPMODE1_SHIFT) */

                #if(0 != BlocoPWM3_CTRL_CMPMODE2_SHIFT)
                    uint8 comparemode2masked = ((uint8)((uint8)comparemode << BlocoPWM3_CTRL_CMPMODE2_SHIFT)) &
                                               BlocoPWM3_CTRL_CMPMODE2_MASK;
                #else
                    uint8 comparemode2masked = comparemode & BlocoPWM3_CTRL_CMPMODE2_MASK;
                #endif /* (0 != BlocoPWM3_CTRL_CMPMODE2_SHIFT) */

                /*Clear existing mode */
                BlocoPWM3_CONTROL &= ((uint8)(~(BlocoPWM3_CTRL_CMPMODE1_MASK |
                                            BlocoPWM3_CTRL_CMPMODE2_MASK)));
                BlocoPWM3_CONTROL |= (comparemode1masked | comparemode2masked);

            #else
                uint8 temp = comparemode;
            #endif /* (BlocoPWM3_UsingFixedFunction) */
        }
    #endif /* BlocoPWM3_CompareMode1SW */

#else /* UseOneCompareMode */

    #if (BlocoPWM3_CompareMode1SW)


        /*******************************************************************************
        * Function Name: BlocoPWM3_SetCompareMode1
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm or pwm1 output
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void BlocoPWM3_SetCompareMode1(uint8 comparemode) 
        {
            #if(0 != BlocoPWM3_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << BlocoPWM3_CTRL_CMPMODE1_SHIFT)) &
                                           BlocoPWM3_CTRL_CMPMODE1_MASK;
            #else
                uint8 comparemodemasked = comparemode & BlocoPWM3_CTRL_CMPMODE1_MASK;
            #endif /* (0 != BlocoPWM3_CTRL_CMPMODE1_SHIFT) */

            #if (BlocoPWM3_UseControl)
                BlocoPWM3_CONTROL &= ((uint8)(~BlocoPWM3_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
                BlocoPWM3_CONTROL |= comparemodemasked;
            #endif /* (BlocoPWM3_UseControl) */
        }
    #endif /* BlocoPWM3_CompareMode1SW */

#if (BlocoPWM3_CompareMode2SW)


    /*******************************************************************************
    * Function Name: BlocoPWM3_SetCompareMode2
    ********************************************************************************
    *
    * Summary:
    *  This function writes the Compare Mode for the pwm or pwm2 output
    *
    * Parameters:
    *  comparemode:  The new compare mode for the PWM output. Use the compare types
    *                defined in the H file as input arguments.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void BlocoPWM3_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != BlocoPWM3_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << BlocoPWM3_CTRL_CMPMODE2_SHIFT)) &
                                                 BlocoPWM3_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & BlocoPWM3_CTRL_CMPMODE2_MASK;
        #endif /* (0 != BlocoPWM3_CTRL_CMPMODE2_SHIFT) */

        #if (BlocoPWM3_UseControl)
            BlocoPWM3_CONTROL &= ((uint8)(~BlocoPWM3_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            BlocoPWM3_CONTROL |= comparemodemasked;
        #endif /* (BlocoPWM3_UseControl) */
    }
    #endif /*BlocoPWM3_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!BlocoPWM3_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: BlocoPWM3_WriteCounter
    ********************************************************************************
    *
    * Summary:
    *  Writes a new counter value directly to the counter register. This will be
    *  implemented for that currently running period and only that period. This API
    *  is valid only for UDB implementation and not available for fixed function
    *  PWM implementation.
    *
    * Parameters:
    *  counter:  The period new period counter value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  The PWM Period will be reloaded when a counter value will be a zero
    *
    *******************************************************************************/
    void BlocoPWM3_WriteCounter(uint16 counter) \
                                       
    {
        CY_SET_REG16(BlocoPWM3_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: BlocoPWM3_ReadCounter
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current value of the counter.  It doesn't matter
    *  if the counter is enabled or running.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  The current value of the counter.
    *
    *******************************************************************************/
    uint16 BlocoPWM3_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
          (void)CY_GET_REG8(BlocoPWM3_COUNTERCAP_LSB_PTR_8BIT);

        /* Read the data from the FIFO */
        return (CY_GET_REG16(BlocoPWM3_CAPTURE_LSB_PTR));
    }

    #if (BlocoPWM3_UseStatus)


        /*******************************************************************************
        * Function Name: BlocoPWM3_ClearFIFO
        ********************************************************************************
        *
        * Summary:
        *  This function clears all capture data from the capture FIFO
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void BlocoPWM3_ClearFIFO(void) 
        {
            while(0u != (BlocoPWM3_ReadStatusRegister() & BlocoPWM3_STATUS_FIFONEMPTY))
            {
                (void)BlocoPWM3_ReadCapture();
            }
        }

    #endif /* BlocoPWM3_UseStatus */

#endif /* !BlocoPWM3_UsingFixedFunction */


/*******************************************************************************
* Function Name: BlocoPWM3_WritePeriod
********************************************************************************
*
* Summary:
*  This function is used to change the period of the counter.  The new period
*  will be loaded the next time terminal count is detected.
*
* Parameters:
*  period:  Period value. May be between 1 and (2^Resolution)-1.  A value of 0
*           will result in the counter remaining at zero.
*
* Return:
*  None
*
*******************************************************************************/
void BlocoPWM3_WritePeriod(uint16 period) 
{
    #if(BlocoPWM3_UsingFixedFunction)
        CY_SET_REG16(BlocoPWM3_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG16(BlocoPWM3_PERIOD_LSB_PTR, period);
    #endif /* (BlocoPWM3_UsingFixedFunction) */
}

#if (BlocoPWM3_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: BlocoPWM3_WriteCompare
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value when the PWM is in Dither
    *  mode. The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  compared to the compare value based on the compare mode defined in
    *  Dither Mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  This function is only available if the PWM mode parameter is set to
    *  Dither Mode, Center Aligned Mode or One Output Mode
    *
    *******************************************************************************/
    void BlocoPWM3_WriteCompare(uint16 compare) \
                                       
    {
        #if(BlocoPWM3_UsingFixedFunction)
            CY_SET_REG16(BlocoPWM3_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(BlocoPWM3_COMPARE1_LSB_PTR, compare);
        #endif /* (BlocoPWM3_UsingFixedFunction) */

        #if (BlocoPWM3_PWMMode == BlocoPWM3__B_PWM__DITHER)
            #if(BlocoPWM3_UsingFixedFunction)
                CY_SET_REG16(BlocoPWM3_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
            #else
                CY_SET_REG16(BlocoPWM3_COMPARE2_LSB_PTR, (compare + 1u));
            #endif /* (BlocoPWM3_UsingFixedFunction) */
        #endif /* (BlocoPWM3_PWMMode == BlocoPWM3__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: BlocoPWM3_WriteCompare1
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value.  The compare output will
    *  reflect the new value on the next UDB clock.  The compare output will be
    *  driven high when the present counter value is less than or less than or
    *  equal to the compare register, depending on the mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void BlocoPWM3_WriteCompare1(uint16 compare) \
                                        
    {
        #if(BlocoPWM3_UsingFixedFunction)
            CY_SET_REG16(BlocoPWM3_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(BlocoPWM3_COMPARE1_LSB_PTR, compare);
        #endif /* (BlocoPWM3_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: BlocoPWM3_WriteCompare2
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare value, for compare1 output.
    *  The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  less than or less than or equal to the compare register, depending on the
    *  mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void BlocoPWM3_WriteCompare2(uint16 compare) \
                                        
    {
        #if(BlocoPWM3_UsingFixedFunction)
            CY_SET_REG16(BlocoPWM3_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG16(BlocoPWM3_COMPARE2_LSB_PTR, compare);
        #endif /* (BlocoPWM3_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (BlocoPWM3_DeadBandUsed)


    /*******************************************************************************
    * Function Name: BlocoPWM3_WriteDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function writes the dead-band counts to the corresponding register
    *
    * Parameters:
    *  deadtime:  Number of counts for dead time
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void BlocoPWM3_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!BlocoPWM3_DeadBand2_4)
            CY_SET_REG8(BlocoPWM3_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */
            /* Clear existing data */
            BlocoPWM3_DEADBAND_COUNT &= ((uint8)(~BlocoPWM3_DEADBAND_COUNT_MASK));

            /* Set new dead time */
            #if(BlocoPWM3_DEADBAND_COUNT_SHIFT)
                BlocoPWM3_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << BlocoPWM3_DEADBAND_COUNT_SHIFT)) &
                                                    BlocoPWM3_DEADBAND_COUNT_MASK;
            #else
                BlocoPWM3_DEADBAND_COUNT |= deadtime & BlocoPWM3_DEADBAND_COUNT_MASK;
            #endif /* (BlocoPWM3_DEADBAND_COUNT_SHIFT) */

        #endif /* (!BlocoPWM3_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: BlocoPWM3_ReadDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function reads the dead-band counts from the corresponding register
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Dead Band Counts
    *
    *******************************************************************************/
    uint8 BlocoPWM3_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!BlocoPWM3_DeadBand2_4)
            return (CY_GET_REG8(BlocoPWM3_DEADBAND_COUNT_PTR));
        #else

            /* Otherwise the data has to be masked and offset */
            #if(BlocoPWM3_DEADBAND_COUNT_SHIFT)
                return ((uint8)(((uint8)(BlocoPWM3_DEADBAND_COUNT & BlocoPWM3_DEADBAND_COUNT_MASK)) >>
                                                                           BlocoPWM3_DEADBAND_COUNT_SHIFT));
            #else
                return (BlocoPWM3_DEADBAND_COUNT & BlocoPWM3_DEADBAND_COUNT_MASK);
            #endif /* (BlocoPWM3_DEADBAND_COUNT_SHIFT) */
        #endif /* (!BlocoPWM3_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (BlocoPWM3_UseStatus || BlocoPWM3_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: BlocoPWM3_SetInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  This function configures the interrupts mask control of theinterrupt
    *  source status register.
    *
    * Parameters:
    *  uint8 interruptMode: Bit field containing the interrupt sources enabled
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void BlocoPWM3_SetInterruptMode(uint8 interruptMode) 
    {
        CY_SET_REG8(BlocoPWM3_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: BlocoPWM3_ReadStatusRegister
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current state of the status register.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current status register value. The status register bits are:
    *  [7:6] : Unused(0)
    *  [5]   : Kill event output
    *  [4]   : FIFO not empty
    *  [3]   : FIFO full
    *  [2]   : Terminal count
    *  [1]   : Compare output 2
    *  [0]   : Compare output 1
    *
    *******************************************************************************/
    uint8 BlocoPWM3_ReadStatusRegister(void) 
    {
        return (CY_GET_REG8(BlocoPWM3_STATUS_PTR));
    }

#endif /* (BlocoPWM3_UseStatus || BlocoPWM3_UsingFixedFunction) */


#if (BlocoPWM3_UseControl)


    /*******************************************************************************
    * Function Name: BlocoPWM3_ReadControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Returns the current state of the control register. This API is available
    *  only if the control register is not removed.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current control register value
    *
    *******************************************************************************/
    uint8 BlocoPWM3_ReadControlRegister(void) 
    {
        uint8 result;

        result = CY_GET_REG8(BlocoPWM3_CONTROL_PTR);
        return (result);
    }


    /*******************************************************************************
    * Function Name: BlocoPWM3_WriteControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Sets the bit field of the control register. This API is available only if
    *  the control register is not removed.
    *
    * Parameters:
    *  uint8 control: Control register bit field, The status register bits are:
    *  [7]   : PWM Enable
    *  [6]   : Reset
    *  [5:3] : Compare Mode2
    *  [2:0] : Compare Mode2
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void BlocoPWM3_WriteControlRegister(uint8 control) 
    {
        CY_SET_REG8(BlocoPWM3_CONTROL_PTR, control);
    }

#endif /* (BlocoPWM3_UseControl) */


#if (!BlocoPWM3_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: BlocoPWM3_ReadCapture
    ********************************************************************************
    *
    * Summary:
    *  Reads the capture value from the capture FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: The current capture value
    *
    *******************************************************************************/
    uint16 BlocoPWM3_ReadCapture(void) 
    {
        return (CY_GET_REG16(BlocoPWM3_CAPTURE_LSB_PTR));
    }

#endif /* (!BlocoPWM3_UsingFixedFunction) */


#if (BlocoPWM3_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: BlocoPWM3_ReadCompare
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare output when the PWM Mode parameter is
    *  set to Dither mode, Center Aligned mode, or One Output mode.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value
    *
    *******************************************************************************/
    uint16 BlocoPWM3_ReadCompare(void) 
    {
        #if(BlocoPWM3_UsingFixedFunction)
            return ((uint16)CY_GET_REG16(BlocoPWM3_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG16(BlocoPWM3_COMPARE1_LSB_PTR));
        #endif /* (BlocoPWM3_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: BlocoPWM3_ReadCompare1
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare1 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint16 BlocoPWM3_ReadCompare1(void) 
    {
        return (CY_GET_REG16(BlocoPWM3_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: BlocoPWM3_ReadCompare2
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare2 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint16 BlocoPWM3_ReadCompare2(void) 
    {
        return (CY_GET_REG16(BlocoPWM3_COMPARE2_LSB_PTR));
    }

#endif /* (BlocoPWM3_UseOneCompareMode) */


/*******************************************************************************
* Function Name: BlocoPWM3_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the period value used by the PWM hardware.
*
* Parameters:
*  None
*
* Return:
*  uint8/16: Period value
*
*******************************************************************************/
uint16 BlocoPWM3_ReadPeriod(void) 
{
    #if(BlocoPWM3_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(BlocoPWM3_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(BlocoPWM3_PERIOD_LSB_PTR));
    #endif /* (BlocoPWM3_UsingFixedFunction) */
}

#if ( BlocoPWM3_KillModeMinTime)


    /*******************************************************************************
    * Function Name: BlocoPWM3_WriteKillTime
    ********************************************************************************
    *
    * Summary:
    *  Writes the kill time value used by the hardware when the Kill Mode
    *  is set to Minimum Time.
    *
    * Parameters:
    *  uint8: Minimum Time kill counts
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void BlocoPWM3_WriteKillTime(uint8 killtime) 
    {
        CY_SET_REG8(BlocoPWM3_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: BlocoPWM3_ReadKillTime
    ********************************************************************************
    *
    * Summary:
    *  Reads the kill time value used by the hardware when the Kill Mode is set
    *  to Minimum Time.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8: The current Minimum Time kill counts
    *
    *******************************************************************************/
    uint8 BlocoPWM3_ReadKillTime(void) 
    {
        return (CY_GET_REG8(BlocoPWM3_KILLMODEMINTIME_PTR));
    }

#endif /* ( BlocoPWM3_KillModeMinTime) */

/* [] END OF FILE */
