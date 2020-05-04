/*******************************************************************************
* File Name: TimerCinematico.h
* Version 2.80
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_TIMER_TimerCinematico_H)
#define CY_TIMER_TimerCinematico_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 TimerCinematico_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define TimerCinematico_Resolution                 8u
#define TimerCinematico_UsingFixedFunction         0u
#define TimerCinematico_UsingHWCaptureCounter      0u
#define TimerCinematico_SoftwareCaptureMode        0u
#define TimerCinematico_SoftwareTriggerMode        0u
#define TimerCinematico_UsingHWEnable              0u
#define TimerCinematico_EnableTriggerMode          0u
#define TimerCinematico_InterruptOnCaptureCount    0u
#define TimerCinematico_RunModeUsed                0u
#define TimerCinematico_ControlRegRemoved          0u

#if defined(TimerCinematico_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define TimerCinematico_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (TimerCinematico_UsingFixedFunction)
    #define TimerCinematico_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define TimerCinematico_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End TimerCinematico_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!TimerCinematico_UsingFixedFunction)

        uint8 TimerUdb;
        uint8 InterruptMaskValue;
        #if (TimerCinematico_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!TimerCinematico_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}TimerCinematico_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    TimerCinematico_Start(void) ;
void    TimerCinematico_Stop(void) ;

void    TimerCinematico_SetInterruptMode(uint8 interruptMode) ;
uint8   TimerCinematico_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define TimerCinematico_GetInterruptSource() TimerCinematico_ReadStatusRegister()

#if(!TimerCinematico_UDB_CONTROL_REG_REMOVED)
    uint8   TimerCinematico_ReadControlRegister(void) ;
    void    TimerCinematico_WriteControlRegister(uint8 control) ;
#endif /* (!TimerCinematico_UDB_CONTROL_REG_REMOVED) */

uint8  TimerCinematico_ReadPeriod(void) ;
void    TimerCinematico_WritePeriod(uint8 period) ;
uint8  TimerCinematico_ReadCounter(void) ;
void    TimerCinematico_WriteCounter(uint8 counter) ;
uint8  TimerCinematico_ReadCapture(void) ;
void    TimerCinematico_SoftwareCapture(void) ;

#if(!TimerCinematico_UsingFixedFunction) /* UDB Prototypes */
    #if (TimerCinematico_SoftwareCaptureMode)
        void    TimerCinematico_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!TimerCinematico_UsingFixedFunction) */

    #if (TimerCinematico_SoftwareTriggerMode)
        void    TimerCinematico_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (TimerCinematico_SoftwareTriggerMode) */

    #if (TimerCinematico_EnableTriggerMode)
        void    TimerCinematico_EnableTrigger(void) ;
        void    TimerCinematico_DisableTrigger(void) ;
    #endif /* (TimerCinematico_EnableTriggerMode) */


    #if(TimerCinematico_InterruptOnCaptureCount)
        void    TimerCinematico_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (TimerCinematico_InterruptOnCaptureCount) */

    #if (TimerCinematico_UsingHWCaptureCounter)
        void    TimerCinematico_SetCaptureCount(uint8 captureCount) ;
        uint8   TimerCinematico_ReadCaptureCount(void) ;
    #endif /* (TimerCinematico_UsingHWCaptureCounter) */

    void TimerCinematico_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void TimerCinematico_Init(void)          ;
void TimerCinematico_Enable(void)        ;
void TimerCinematico_SaveConfig(void)    ;
void TimerCinematico_RestoreConfig(void) ;
void TimerCinematico_Sleep(void)         ;
void TimerCinematico_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define TimerCinematico__B_TIMER__CM_NONE 0
#define TimerCinematico__B_TIMER__CM_RISINGEDGE 1
#define TimerCinematico__B_TIMER__CM_FALLINGEDGE 2
#define TimerCinematico__B_TIMER__CM_EITHEREDGE 3
#define TimerCinematico__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define TimerCinematico__B_TIMER__TM_NONE 0x00u
#define TimerCinematico__B_TIMER__TM_RISINGEDGE 0x04u
#define TimerCinematico__B_TIMER__TM_FALLINGEDGE 0x08u
#define TimerCinematico__B_TIMER__TM_EITHEREDGE 0x0Cu
#define TimerCinematico__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define TimerCinematico_INIT_PERIOD             69u
#define TimerCinematico_INIT_CAPTURE_MODE       ((uint8)((uint8)1u << TimerCinematico_CTRL_CAP_MODE_SHIFT))
#define TimerCinematico_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << TimerCinematico_CTRL_TRIG_MODE_SHIFT))
#if (TimerCinematico_UsingFixedFunction)
    #define TimerCinematico_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << TimerCinematico_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << TimerCinematico_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define TimerCinematico_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << TimerCinematico_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << TimerCinematico_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << TimerCinematico_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (TimerCinematico_UsingFixedFunction) */
#define TimerCinematico_INIT_CAPTURE_COUNT      (2u)
#define TimerCinematico_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << TimerCinematico_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (TimerCinematico_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define TimerCinematico_STATUS         (*(reg8 *) TimerCinematico_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define TimerCinematico_STATUS_MASK    (*(reg8 *) TimerCinematico_TimerHW__SR0 )
    #define TimerCinematico_CONTROL        (*(reg8 *) TimerCinematico_TimerHW__CFG0)
    #define TimerCinematico_CONTROL2       (*(reg8 *) TimerCinematico_TimerHW__CFG1)
    #define TimerCinematico_CONTROL2_PTR   ( (reg8 *) TimerCinematico_TimerHW__CFG1)
    #define TimerCinematico_RT1            (*(reg8 *) TimerCinematico_TimerHW__RT1)
    #define TimerCinematico_RT1_PTR        ( (reg8 *) TimerCinematico_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define TimerCinematico_CONTROL3       (*(reg8 *) TimerCinematico_TimerHW__CFG2)
        #define TimerCinematico_CONTROL3_PTR   ( (reg8 *) TimerCinematico_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define TimerCinematico_GLOBAL_ENABLE  (*(reg8 *) TimerCinematico_TimerHW__PM_ACT_CFG)
    #define TimerCinematico_GLOBAL_STBY_ENABLE  (*(reg8 *) TimerCinematico_TimerHW__PM_STBY_CFG)

    #define TimerCinematico_CAPTURE_LSB         (* (reg16 *) TimerCinematico_TimerHW__CAP0 )
    #define TimerCinematico_CAPTURE_LSB_PTR       ((reg16 *) TimerCinematico_TimerHW__CAP0 )
    #define TimerCinematico_PERIOD_LSB          (* (reg16 *) TimerCinematico_TimerHW__PER0 )
    #define TimerCinematico_PERIOD_LSB_PTR        ((reg16 *) TimerCinematico_TimerHW__PER0 )
    #define TimerCinematico_COUNTER_LSB         (* (reg16 *) TimerCinematico_TimerHW__CNT_CMP0 )
    #define TimerCinematico_COUNTER_LSB_PTR       ((reg16 *) TimerCinematico_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define TimerCinematico_BLOCK_EN_MASK                     TimerCinematico_TimerHW__PM_ACT_MSK
    #define TimerCinematico_BLOCK_STBY_EN_MASK                TimerCinematico_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define TimerCinematico_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define TimerCinematico_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define TimerCinematico_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define TimerCinematico_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define TimerCinematico_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define TimerCinematico_CTRL_ENABLE                        ((uint8)((uint8)0x01u << TimerCinematico_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define TimerCinematico_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define TimerCinematico_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << TimerCinematico_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define TimerCinematico_CTRL_MODE_SHIFT                 0x01u
        #define TimerCinematico_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << TimerCinematico_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define TimerCinematico_CTRL_RCOD_SHIFT        0x02u
        #define TimerCinematico_CTRL_ENBL_SHIFT        0x00u
        #define TimerCinematico_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define TimerCinematico_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << TimerCinematico_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define TimerCinematico_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << TimerCinematico_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define TimerCinematico_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << TimerCinematico_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define TimerCinematico_CTRL_RCOD       ((uint8)((uint8)0x03u << TimerCinematico_CTRL_RCOD_SHIFT))
        #define TimerCinematico_CTRL_ENBL       ((uint8)((uint8)0x80u << TimerCinematico_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define TimerCinematico_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define TimerCinematico_RT1_MASK                        ((uint8)((uint8)0x03u << TimerCinematico_RT1_SHIFT))
    #define TimerCinematico_SYNC                            ((uint8)((uint8)0x03u << TimerCinematico_RT1_SHIFT))
    #define TimerCinematico_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define TimerCinematico_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << TimerCinematico_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define TimerCinematico_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << TimerCinematico_SYNCDSI_SHIFT))

    #define TimerCinematico_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << TimerCinematico_CTRL_MODE_SHIFT))
    #define TimerCinematico_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << TimerCinematico_CTRL_MODE_SHIFT))
    #define TimerCinematico_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << TimerCinematico_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define TimerCinematico_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define TimerCinematico_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define TimerCinematico_STATUS_TC_INT_MASK_SHIFT        (TimerCinematico_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define TimerCinematico_STATUS_CAPTURE_INT_MASK_SHIFT   (TimerCinematico_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define TimerCinematico_STATUS_TC                       ((uint8)((uint8)0x01u << TimerCinematico_STATUS_TC_SHIFT))
    #define TimerCinematico_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << TimerCinematico_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define TimerCinematico_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << TimerCinematico_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define TimerCinematico_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << TimerCinematico_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define TimerCinematico_STATUS              (* (reg8 *) TimerCinematico_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define TimerCinematico_STATUS_MASK         (* (reg8 *) TimerCinematico_TimerUDB_rstSts_stsreg__MASK_REG)
    #define TimerCinematico_STATUS_AUX_CTRL     (* (reg8 *) TimerCinematico_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define TimerCinematico_CONTROL             (* (reg8 *) TimerCinematico_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(TimerCinematico_Resolution <= 8u) /* 8-bit Timer */
        #define TimerCinematico_CAPTURE_LSB         (* (reg8 *) TimerCinematico_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define TimerCinematico_CAPTURE_LSB_PTR       ((reg8 *) TimerCinematico_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define TimerCinematico_PERIOD_LSB          (* (reg8 *) TimerCinematico_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define TimerCinematico_PERIOD_LSB_PTR        ((reg8 *) TimerCinematico_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define TimerCinematico_COUNTER_LSB         (* (reg8 *) TimerCinematico_TimerUDB_sT8_timerdp_u0__A0_REG )
        #define TimerCinematico_COUNTER_LSB_PTR       ((reg8 *) TimerCinematico_TimerUDB_sT8_timerdp_u0__A0_REG )
    #elif(TimerCinematico_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define TimerCinematico_CAPTURE_LSB         (* (reg16 *) TimerCinematico_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define TimerCinematico_CAPTURE_LSB_PTR       ((reg16 *) TimerCinematico_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define TimerCinematico_PERIOD_LSB          (* (reg16 *) TimerCinematico_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define TimerCinematico_PERIOD_LSB_PTR        ((reg16 *) TimerCinematico_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define TimerCinematico_COUNTER_LSB         (* (reg16 *) TimerCinematico_TimerUDB_sT8_timerdp_u0__A0_REG )
            #define TimerCinematico_COUNTER_LSB_PTR       ((reg16 *) TimerCinematico_TimerUDB_sT8_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define TimerCinematico_CAPTURE_LSB         (* (reg16 *) TimerCinematico_TimerUDB_sT8_timerdp_u0__16BIT_F0_REG )
            #define TimerCinematico_CAPTURE_LSB_PTR       ((reg16 *) TimerCinematico_TimerUDB_sT8_timerdp_u0__16BIT_F0_REG )
            #define TimerCinematico_PERIOD_LSB          (* (reg16 *) TimerCinematico_TimerUDB_sT8_timerdp_u0__16BIT_D0_REG )
            #define TimerCinematico_PERIOD_LSB_PTR        ((reg16 *) TimerCinematico_TimerUDB_sT8_timerdp_u0__16BIT_D0_REG )
            #define TimerCinematico_COUNTER_LSB         (* (reg16 *) TimerCinematico_TimerUDB_sT8_timerdp_u0__16BIT_A0_REG )
            #define TimerCinematico_COUNTER_LSB_PTR       ((reg16 *) TimerCinematico_TimerUDB_sT8_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(TimerCinematico_Resolution <= 24u)/* 24-bit Timer */
        #define TimerCinematico_CAPTURE_LSB         (* (reg32 *) TimerCinematico_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define TimerCinematico_CAPTURE_LSB_PTR       ((reg32 *) TimerCinematico_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define TimerCinematico_PERIOD_LSB          (* (reg32 *) TimerCinematico_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define TimerCinematico_PERIOD_LSB_PTR        ((reg32 *) TimerCinematico_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define TimerCinematico_COUNTER_LSB         (* (reg32 *) TimerCinematico_TimerUDB_sT8_timerdp_u0__A0_REG )
        #define TimerCinematico_COUNTER_LSB_PTR       ((reg32 *) TimerCinematico_TimerUDB_sT8_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define TimerCinematico_CAPTURE_LSB         (* (reg32 *) TimerCinematico_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define TimerCinematico_CAPTURE_LSB_PTR       ((reg32 *) TimerCinematico_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define TimerCinematico_PERIOD_LSB          (* (reg32 *) TimerCinematico_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define TimerCinematico_PERIOD_LSB_PTR        ((reg32 *) TimerCinematico_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define TimerCinematico_COUNTER_LSB         (* (reg32 *) TimerCinematico_TimerUDB_sT8_timerdp_u0__A0_REG )
            #define TimerCinematico_COUNTER_LSB_PTR       ((reg32 *) TimerCinematico_TimerUDB_sT8_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define TimerCinematico_CAPTURE_LSB         (* (reg32 *) TimerCinematico_TimerUDB_sT8_timerdp_u0__32BIT_F0_REG )
            #define TimerCinematico_CAPTURE_LSB_PTR       ((reg32 *) TimerCinematico_TimerUDB_sT8_timerdp_u0__32BIT_F0_REG )
            #define TimerCinematico_PERIOD_LSB          (* (reg32 *) TimerCinematico_TimerUDB_sT8_timerdp_u0__32BIT_D0_REG )
            #define TimerCinematico_PERIOD_LSB_PTR        ((reg32 *) TimerCinematico_TimerUDB_sT8_timerdp_u0__32BIT_D0_REG )
            #define TimerCinematico_COUNTER_LSB         (* (reg32 *) TimerCinematico_TimerUDB_sT8_timerdp_u0__32BIT_A0_REG )
            #define TimerCinematico_COUNTER_LSB_PTR       ((reg32 *) TimerCinematico_TimerUDB_sT8_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define TimerCinematico_COUNTER_LSB_PTR_8BIT       ((reg8 *) TimerCinematico_TimerUDB_sT8_timerdp_u0__A0_REG )
    
    #if (TimerCinematico_UsingHWCaptureCounter)
        #define TimerCinematico_CAP_COUNT              (*(reg8 *) TimerCinematico_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define TimerCinematico_CAP_COUNT_PTR          ( (reg8 *) TimerCinematico_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define TimerCinematico_CAPTURE_COUNT_CTRL     (*(reg8 *) TimerCinematico_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define TimerCinematico_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) TimerCinematico_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (TimerCinematico_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define TimerCinematico_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define TimerCinematico_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define TimerCinematico_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define TimerCinematico_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define TimerCinematico_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define TimerCinematico_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << TimerCinematico_CTRL_INTCNT_SHIFT))
    #define TimerCinematico_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << TimerCinematico_CTRL_TRIG_MODE_SHIFT))
    #define TimerCinematico_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << TimerCinematico_CTRL_TRIG_EN_SHIFT))
    #define TimerCinematico_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << TimerCinematico_CTRL_CAP_MODE_SHIFT))
    #define TimerCinematico_CTRL_ENABLE                    ((uint8)((uint8)0x01u << TimerCinematico_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define TimerCinematico_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define TimerCinematico_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define TimerCinematico_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define TimerCinematico_STATUS_TC_INT_MASK_SHIFT       TimerCinematico_STATUS_TC_SHIFT
    #define TimerCinematico_STATUS_CAPTURE_INT_MASK_SHIFT  TimerCinematico_STATUS_CAPTURE_SHIFT
    #define TimerCinematico_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define TimerCinematico_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define TimerCinematico_STATUS_FIFOFULL_INT_MASK_SHIFT TimerCinematico_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define TimerCinematico_STATUS_TC                      ((uint8)((uint8)0x01u << TimerCinematico_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define TimerCinematico_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << TimerCinematico_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define TimerCinematico_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << TimerCinematico_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define TimerCinematico_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << TimerCinematico_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define TimerCinematico_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << TimerCinematico_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define TimerCinematico_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << TimerCinematico_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define TimerCinematico_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << TimerCinematico_STATUS_FIFOFULL_SHIFT))

    #define TimerCinematico_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define TimerCinematico_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define TimerCinematico_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define TimerCinematico_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define TimerCinematico_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define TimerCinematico_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_TimerCinematico_H */


/* [] END OF FILE */
