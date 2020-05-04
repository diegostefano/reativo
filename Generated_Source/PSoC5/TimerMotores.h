/*******************************************************************************
* File Name: TimerMotores.h
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

#if !defined(CY_TIMER_TimerMotores_H)
#define CY_TIMER_TimerMotores_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 TimerMotores_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define TimerMotores_Resolution                 8u
#define TimerMotores_UsingFixedFunction         0u
#define TimerMotores_UsingHWCaptureCounter      0u
#define TimerMotores_SoftwareCaptureMode        0u
#define TimerMotores_SoftwareTriggerMode        0u
#define TimerMotores_UsingHWEnable              0u
#define TimerMotores_EnableTriggerMode          0u
#define TimerMotores_InterruptOnCaptureCount    0u
#define TimerMotores_RunModeUsed                0u
#define TimerMotores_ControlRegRemoved          0u

#if defined(TimerMotores_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define TimerMotores_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (TimerMotores_UsingFixedFunction)
    #define TimerMotores_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define TimerMotores_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End TimerMotores_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!TimerMotores_UsingFixedFunction)

        uint8 TimerUdb;
        uint8 InterruptMaskValue;
        #if (TimerMotores_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!TimerMotores_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}TimerMotores_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    TimerMotores_Start(void) ;
void    TimerMotores_Stop(void) ;

void    TimerMotores_SetInterruptMode(uint8 interruptMode) ;
uint8   TimerMotores_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define TimerMotores_GetInterruptSource() TimerMotores_ReadStatusRegister()

#if(!TimerMotores_UDB_CONTROL_REG_REMOVED)
    uint8   TimerMotores_ReadControlRegister(void) ;
    void    TimerMotores_WriteControlRegister(uint8 control) ;
#endif /* (!TimerMotores_UDB_CONTROL_REG_REMOVED) */

uint8  TimerMotores_ReadPeriod(void) ;
void    TimerMotores_WritePeriod(uint8 period) ;
uint8  TimerMotores_ReadCounter(void) ;
void    TimerMotores_WriteCounter(uint8 counter) ;
uint8  TimerMotores_ReadCapture(void) ;
void    TimerMotores_SoftwareCapture(void) ;

#if(!TimerMotores_UsingFixedFunction) /* UDB Prototypes */
    #if (TimerMotores_SoftwareCaptureMode)
        void    TimerMotores_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!TimerMotores_UsingFixedFunction) */

    #if (TimerMotores_SoftwareTriggerMode)
        void    TimerMotores_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (TimerMotores_SoftwareTriggerMode) */

    #if (TimerMotores_EnableTriggerMode)
        void    TimerMotores_EnableTrigger(void) ;
        void    TimerMotores_DisableTrigger(void) ;
    #endif /* (TimerMotores_EnableTriggerMode) */


    #if(TimerMotores_InterruptOnCaptureCount)
        void    TimerMotores_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (TimerMotores_InterruptOnCaptureCount) */

    #if (TimerMotores_UsingHWCaptureCounter)
        void    TimerMotores_SetCaptureCount(uint8 captureCount) ;
        uint8   TimerMotores_ReadCaptureCount(void) ;
    #endif /* (TimerMotores_UsingHWCaptureCounter) */

    void TimerMotores_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void TimerMotores_Init(void)          ;
void TimerMotores_Enable(void)        ;
void TimerMotores_SaveConfig(void)    ;
void TimerMotores_RestoreConfig(void) ;
void TimerMotores_Sleep(void)         ;
void TimerMotores_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define TimerMotores__B_TIMER__CM_NONE 0
#define TimerMotores__B_TIMER__CM_RISINGEDGE 1
#define TimerMotores__B_TIMER__CM_FALLINGEDGE 2
#define TimerMotores__B_TIMER__CM_EITHEREDGE 3
#define TimerMotores__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define TimerMotores__B_TIMER__TM_NONE 0x00u
#define TimerMotores__B_TIMER__TM_RISINGEDGE 0x04u
#define TimerMotores__B_TIMER__TM_FALLINGEDGE 0x08u
#define TimerMotores__B_TIMER__TM_EITHEREDGE 0x0Cu
#define TimerMotores__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define TimerMotores_INIT_PERIOD             14u
#define TimerMotores_INIT_CAPTURE_MODE       ((uint8)((uint8)1u << TimerMotores_CTRL_CAP_MODE_SHIFT))
#define TimerMotores_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << TimerMotores_CTRL_TRIG_MODE_SHIFT))
#if (TimerMotores_UsingFixedFunction)
    #define TimerMotores_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << TimerMotores_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << TimerMotores_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define TimerMotores_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << TimerMotores_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << TimerMotores_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << TimerMotores_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (TimerMotores_UsingFixedFunction) */
#define TimerMotores_INIT_CAPTURE_COUNT      (2u)
#define TimerMotores_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << TimerMotores_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (TimerMotores_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define TimerMotores_STATUS         (*(reg8 *) TimerMotores_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define TimerMotores_STATUS_MASK    (*(reg8 *) TimerMotores_TimerHW__SR0 )
    #define TimerMotores_CONTROL        (*(reg8 *) TimerMotores_TimerHW__CFG0)
    #define TimerMotores_CONTROL2       (*(reg8 *) TimerMotores_TimerHW__CFG1)
    #define TimerMotores_CONTROL2_PTR   ( (reg8 *) TimerMotores_TimerHW__CFG1)
    #define TimerMotores_RT1            (*(reg8 *) TimerMotores_TimerHW__RT1)
    #define TimerMotores_RT1_PTR        ( (reg8 *) TimerMotores_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define TimerMotores_CONTROL3       (*(reg8 *) TimerMotores_TimerHW__CFG2)
        #define TimerMotores_CONTROL3_PTR   ( (reg8 *) TimerMotores_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define TimerMotores_GLOBAL_ENABLE  (*(reg8 *) TimerMotores_TimerHW__PM_ACT_CFG)
    #define TimerMotores_GLOBAL_STBY_ENABLE  (*(reg8 *) TimerMotores_TimerHW__PM_STBY_CFG)

    #define TimerMotores_CAPTURE_LSB         (* (reg16 *) TimerMotores_TimerHW__CAP0 )
    #define TimerMotores_CAPTURE_LSB_PTR       ((reg16 *) TimerMotores_TimerHW__CAP0 )
    #define TimerMotores_PERIOD_LSB          (* (reg16 *) TimerMotores_TimerHW__PER0 )
    #define TimerMotores_PERIOD_LSB_PTR        ((reg16 *) TimerMotores_TimerHW__PER0 )
    #define TimerMotores_COUNTER_LSB         (* (reg16 *) TimerMotores_TimerHW__CNT_CMP0 )
    #define TimerMotores_COUNTER_LSB_PTR       ((reg16 *) TimerMotores_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define TimerMotores_BLOCK_EN_MASK                     TimerMotores_TimerHW__PM_ACT_MSK
    #define TimerMotores_BLOCK_STBY_EN_MASK                TimerMotores_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define TimerMotores_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define TimerMotores_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define TimerMotores_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define TimerMotores_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define TimerMotores_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define TimerMotores_CTRL_ENABLE                        ((uint8)((uint8)0x01u << TimerMotores_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define TimerMotores_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define TimerMotores_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << TimerMotores_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define TimerMotores_CTRL_MODE_SHIFT                 0x01u
        #define TimerMotores_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << TimerMotores_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define TimerMotores_CTRL_RCOD_SHIFT        0x02u
        #define TimerMotores_CTRL_ENBL_SHIFT        0x00u
        #define TimerMotores_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define TimerMotores_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << TimerMotores_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define TimerMotores_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << TimerMotores_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define TimerMotores_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << TimerMotores_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define TimerMotores_CTRL_RCOD       ((uint8)((uint8)0x03u << TimerMotores_CTRL_RCOD_SHIFT))
        #define TimerMotores_CTRL_ENBL       ((uint8)((uint8)0x80u << TimerMotores_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define TimerMotores_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define TimerMotores_RT1_MASK                        ((uint8)((uint8)0x03u << TimerMotores_RT1_SHIFT))
    #define TimerMotores_SYNC                            ((uint8)((uint8)0x03u << TimerMotores_RT1_SHIFT))
    #define TimerMotores_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define TimerMotores_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << TimerMotores_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define TimerMotores_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << TimerMotores_SYNCDSI_SHIFT))

    #define TimerMotores_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << TimerMotores_CTRL_MODE_SHIFT))
    #define TimerMotores_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << TimerMotores_CTRL_MODE_SHIFT))
    #define TimerMotores_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << TimerMotores_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define TimerMotores_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define TimerMotores_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define TimerMotores_STATUS_TC_INT_MASK_SHIFT        (TimerMotores_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define TimerMotores_STATUS_CAPTURE_INT_MASK_SHIFT   (TimerMotores_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define TimerMotores_STATUS_TC                       ((uint8)((uint8)0x01u << TimerMotores_STATUS_TC_SHIFT))
    #define TimerMotores_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << TimerMotores_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define TimerMotores_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << TimerMotores_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define TimerMotores_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << TimerMotores_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define TimerMotores_STATUS              (* (reg8 *) TimerMotores_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define TimerMotores_STATUS_MASK         (* (reg8 *) TimerMotores_TimerUDB_rstSts_stsreg__MASK_REG)
    #define TimerMotores_STATUS_AUX_CTRL     (* (reg8 *) TimerMotores_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define TimerMotores_CONTROL             (* (reg8 *) TimerMotores_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(TimerMotores_Resolution <= 8u) /* 8-bit Timer */
        #define TimerMotores_CAPTURE_LSB         (* (reg8 *) TimerMotores_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define TimerMotores_CAPTURE_LSB_PTR       ((reg8 *) TimerMotores_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define TimerMotores_PERIOD_LSB          (* (reg8 *) TimerMotores_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define TimerMotores_PERIOD_LSB_PTR        ((reg8 *) TimerMotores_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define TimerMotores_COUNTER_LSB         (* (reg8 *) TimerMotores_TimerUDB_sT8_timerdp_u0__A0_REG )
        #define TimerMotores_COUNTER_LSB_PTR       ((reg8 *) TimerMotores_TimerUDB_sT8_timerdp_u0__A0_REG )
    #elif(TimerMotores_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define TimerMotores_CAPTURE_LSB         (* (reg16 *) TimerMotores_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define TimerMotores_CAPTURE_LSB_PTR       ((reg16 *) TimerMotores_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define TimerMotores_PERIOD_LSB          (* (reg16 *) TimerMotores_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define TimerMotores_PERIOD_LSB_PTR        ((reg16 *) TimerMotores_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define TimerMotores_COUNTER_LSB         (* (reg16 *) TimerMotores_TimerUDB_sT8_timerdp_u0__A0_REG )
            #define TimerMotores_COUNTER_LSB_PTR       ((reg16 *) TimerMotores_TimerUDB_sT8_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define TimerMotores_CAPTURE_LSB         (* (reg16 *) TimerMotores_TimerUDB_sT8_timerdp_u0__16BIT_F0_REG )
            #define TimerMotores_CAPTURE_LSB_PTR       ((reg16 *) TimerMotores_TimerUDB_sT8_timerdp_u0__16BIT_F0_REG )
            #define TimerMotores_PERIOD_LSB          (* (reg16 *) TimerMotores_TimerUDB_sT8_timerdp_u0__16BIT_D0_REG )
            #define TimerMotores_PERIOD_LSB_PTR        ((reg16 *) TimerMotores_TimerUDB_sT8_timerdp_u0__16BIT_D0_REG )
            #define TimerMotores_COUNTER_LSB         (* (reg16 *) TimerMotores_TimerUDB_sT8_timerdp_u0__16BIT_A0_REG )
            #define TimerMotores_COUNTER_LSB_PTR       ((reg16 *) TimerMotores_TimerUDB_sT8_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(TimerMotores_Resolution <= 24u)/* 24-bit Timer */
        #define TimerMotores_CAPTURE_LSB         (* (reg32 *) TimerMotores_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define TimerMotores_CAPTURE_LSB_PTR       ((reg32 *) TimerMotores_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define TimerMotores_PERIOD_LSB          (* (reg32 *) TimerMotores_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define TimerMotores_PERIOD_LSB_PTR        ((reg32 *) TimerMotores_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define TimerMotores_COUNTER_LSB         (* (reg32 *) TimerMotores_TimerUDB_sT8_timerdp_u0__A0_REG )
        #define TimerMotores_COUNTER_LSB_PTR       ((reg32 *) TimerMotores_TimerUDB_sT8_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define TimerMotores_CAPTURE_LSB         (* (reg32 *) TimerMotores_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define TimerMotores_CAPTURE_LSB_PTR       ((reg32 *) TimerMotores_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define TimerMotores_PERIOD_LSB          (* (reg32 *) TimerMotores_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define TimerMotores_PERIOD_LSB_PTR        ((reg32 *) TimerMotores_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define TimerMotores_COUNTER_LSB         (* (reg32 *) TimerMotores_TimerUDB_sT8_timerdp_u0__A0_REG )
            #define TimerMotores_COUNTER_LSB_PTR       ((reg32 *) TimerMotores_TimerUDB_sT8_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define TimerMotores_CAPTURE_LSB         (* (reg32 *) TimerMotores_TimerUDB_sT8_timerdp_u0__32BIT_F0_REG )
            #define TimerMotores_CAPTURE_LSB_PTR       ((reg32 *) TimerMotores_TimerUDB_sT8_timerdp_u0__32BIT_F0_REG )
            #define TimerMotores_PERIOD_LSB          (* (reg32 *) TimerMotores_TimerUDB_sT8_timerdp_u0__32BIT_D0_REG )
            #define TimerMotores_PERIOD_LSB_PTR        ((reg32 *) TimerMotores_TimerUDB_sT8_timerdp_u0__32BIT_D0_REG )
            #define TimerMotores_COUNTER_LSB         (* (reg32 *) TimerMotores_TimerUDB_sT8_timerdp_u0__32BIT_A0_REG )
            #define TimerMotores_COUNTER_LSB_PTR       ((reg32 *) TimerMotores_TimerUDB_sT8_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define TimerMotores_COUNTER_LSB_PTR_8BIT       ((reg8 *) TimerMotores_TimerUDB_sT8_timerdp_u0__A0_REG )
    
    #if (TimerMotores_UsingHWCaptureCounter)
        #define TimerMotores_CAP_COUNT              (*(reg8 *) TimerMotores_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define TimerMotores_CAP_COUNT_PTR          ( (reg8 *) TimerMotores_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define TimerMotores_CAPTURE_COUNT_CTRL     (*(reg8 *) TimerMotores_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define TimerMotores_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) TimerMotores_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (TimerMotores_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define TimerMotores_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define TimerMotores_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define TimerMotores_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define TimerMotores_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define TimerMotores_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define TimerMotores_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << TimerMotores_CTRL_INTCNT_SHIFT))
    #define TimerMotores_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << TimerMotores_CTRL_TRIG_MODE_SHIFT))
    #define TimerMotores_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << TimerMotores_CTRL_TRIG_EN_SHIFT))
    #define TimerMotores_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << TimerMotores_CTRL_CAP_MODE_SHIFT))
    #define TimerMotores_CTRL_ENABLE                    ((uint8)((uint8)0x01u << TimerMotores_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define TimerMotores_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define TimerMotores_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define TimerMotores_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define TimerMotores_STATUS_TC_INT_MASK_SHIFT       TimerMotores_STATUS_TC_SHIFT
    #define TimerMotores_STATUS_CAPTURE_INT_MASK_SHIFT  TimerMotores_STATUS_CAPTURE_SHIFT
    #define TimerMotores_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define TimerMotores_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define TimerMotores_STATUS_FIFOFULL_INT_MASK_SHIFT TimerMotores_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define TimerMotores_STATUS_TC                      ((uint8)((uint8)0x01u << TimerMotores_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define TimerMotores_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << TimerMotores_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define TimerMotores_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << TimerMotores_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define TimerMotores_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << TimerMotores_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define TimerMotores_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << TimerMotores_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define TimerMotores_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << TimerMotores_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define TimerMotores_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << TimerMotores_STATUS_FIFOFULL_SHIFT))

    #define TimerMotores_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define TimerMotores_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define TimerMotores_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define TimerMotores_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define TimerMotores_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define TimerMotores_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_TimerMotores_H */


/* [] END OF FILE */
