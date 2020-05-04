/*******************************************************************************
* File Name: BlocoPWM3.h
* Version 3.30
*
* Description:
*  Contains the prototypes and constants for the functions available to the
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PWM_BlocoPWM3_H)
#define CY_PWM_BlocoPWM3_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 BlocoPWM3_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define BlocoPWM3_Resolution                     (16u)
#define BlocoPWM3_UsingFixedFunction             (0u)
#define BlocoPWM3_DeadBandMode                   (0u)
#define BlocoPWM3_KillModeMinTime                (0u)
#define BlocoPWM3_KillMode                       (0u)
#define BlocoPWM3_PWMMode                        (0u)
#define BlocoPWM3_PWMModeIsCenterAligned         (0u)
#define BlocoPWM3_DeadBandUsed                   (0u)
#define BlocoPWM3_DeadBand2_4                    (0u)

#if !defined(BlocoPWM3_PWMUDB_genblk8_stsreg__REMOVED)
    #define BlocoPWM3_UseStatus                  (1u)
#else
    #define BlocoPWM3_UseStatus                  (0u)
#endif /* !defined(BlocoPWM3_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(BlocoPWM3_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define BlocoPWM3_UseControl                 (1u)
#else
    #define BlocoPWM3_UseControl                 (0u)
#endif /* !defined(BlocoPWM3_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define BlocoPWM3_UseOneCompareMode              (1u)
#define BlocoPWM3_MinimumKillTime                (1u)
#define BlocoPWM3_EnableMode                     (0u)

#define BlocoPWM3_CompareMode1SW                 (0u)
#define BlocoPWM3_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define BlocoPWM3__B_PWM__DISABLED 0
#define BlocoPWM3__B_PWM__ASYNCHRONOUS 1
#define BlocoPWM3__B_PWM__SINGLECYCLE 2
#define BlocoPWM3__B_PWM__LATCHED 3
#define BlocoPWM3__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define BlocoPWM3__B_PWM__DBMDISABLED 0
#define BlocoPWM3__B_PWM__DBM_2_4_CLOCKS 1
#define BlocoPWM3__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define BlocoPWM3__B_PWM__ONE_OUTPUT 0
#define BlocoPWM3__B_PWM__TWO_OUTPUTS 1
#define BlocoPWM3__B_PWM__DUAL_EDGE 2
#define BlocoPWM3__B_PWM__CENTER_ALIGN 3
#define BlocoPWM3__B_PWM__DITHER 5
#define BlocoPWM3__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define BlocoPWM3__B_PWM__LESS_THAN 1
#define BlocoPWM3__B_PWM__LESS_THAN_OR_EQUAL 2
#define BlocoPWM3__B_PWM__GREATER_THAN 3
#define BlocoPWM3__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define BlocoPWM3__B_PWM__EQUAL 0
#define BlocoPWM3__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!BlocoPWM3_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!BlocoPWM3_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!BlocoPWM3_PWMModeIsCenterAligned) */
        #if (BlocoPWM3_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (BlocoPWM3_UseStatus) */

        /* Backup for Deadband parameters */
        #if(BlocoPWM3_DeadBandMode == BlocoPWM3__B_PWM__DBM_256_CLOCKS || \
            BlocoPWM3_DeadBandMode == BlocoPWM3__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(BlocoPWM3_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (BlocoPWM3_KillModeMinTime) */

        /* Backup control register */
        #if(BlocoPWM3_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (BlocoPWM3_UseControl) */

    #endif /* (!BlocoPWM3_UsingFixedFunction) */

}BlocoPWM3_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    BlocoPWM3_Start(void) ;
void    BlocoPWM3_Stop(void) ;

#if (BlocoPWM3_UseStatus || BlocoPWM3_UsingFixedFunction)
    void  BlocoPWM3_SetInterruptMode(uint8 interruptMode) ;
    uint8 BlocoPWM3_ReadStatusRegister(void) ;
#endif /* (BlocoPWM3_UseStatus || BlocoPWM3_UsingFixedFunction) */

#define BlocoPWM3_GetInterruptSource() BlocoPWM3_ReadStatusRegister()

#if (BlocoPWM3_UseControl)
    uint8 BlocoPWM3_ReadControlRegister(void) ;
    void  BlocoPWM3_WriteControlRegister(uint8 control)
          ;
#endif /* (BlocoPWM3_UseControl) */

#if (BlocoPWM3_UseOneCompareMode)
   #if (BlocoPWM3_CompareMode1SW)
       void    BlocoPWM3_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (BlocoPWM3_CompareMode1SW) */
#else
    #if (BlocoPWM3_CompareMode1SW)
        void    BlocoPWM3_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (BlocoPWM3_CompareMode1SW) */
    #if (BlocoPWM3_CompareMode2SW)
        void    BlocoPWM3_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (BlocoPWM3_CompareMode2SW) */
#endif /* (BlocoPWM3_UseOneCompareMode) */

#if (!BlocoPWM3_UsingFixedFunction)
    uint16   BlocoPWM3_ReadCounter(void) ;
    uint16 BlocoPWM3_ReadCapture(void) ;

    #if (BlocoPWM3_UseStatus)
            void BlocoPWM3_ClearFIFO(void) ;
    #endif /* (BlocoPWM3_UseStatus) */

    void    BlocoPWM3_WriteCounter(uint16 counter)
            ;
#endif /* (!BlocoPWM3_UsingFixedFunction) */

void    BlocoPWM3_WritePeriod(uint16 period)
        ;
uint16 BlocoPWM3_ReadPeriod(void) ;

#if (BlocoPWM3_UseOneCompareMode)
    void    BlocoPWM3_WriteCompare(uint16 compare)
            ;
    uint16 BlocoPWM3_ReadCompare(void) ;
#else
    void    BlocoPWM3_WriteCompare1(uint16 compare)
            ;
    uint16 BlocoPWM3_ReadCompare1(void) ;
    void    BlocoPWM3_WriteCompare2(uint16 compare)
            ;
    uint16 BlocoPWM3_ReadCompare2(void) ;
#endif /* (BlocoPWM3_UseOneCompareMode) */


#if (BlocoPWM3_DeadBandUsed)
    void    BlocoPWM3_WriteDeadTime(uint8 deadtime) ;
    uint8   BlocoPWM3_ReadDeadTime(void) ;
#endif /* (BlocoPWM3_DeadBandUsed) */

#if ( BlocoPWM3_KillModeMinTime)
    void BlocoPWM3_WriteKillTime(uint8 killtime) ;
    uint8 BlocoPWM3_ReadKillTime(void) ;
#endif /* ( BlocoPWM3_KillModeMinTime) */

void BlocoPWM3_Init(void) ;
void BlocoPWM3_Enable(void) ;
void BlocoPWM3_Sleep(void) ;
void BlocoPWM3_Wakeup(void) ;
void BlocoPWM3_SaveConfig(void) ;
void BlocoPWM3_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define BlocoPWM3_INIT_PERIOD_VALUE          (2000u)
#define BlocoPWM3_INIT_COMPARE_VALUE1        (1000u)
#define BlocoPWM3_INIT_COMPARE_VALUE2        (63u)
#define BlocoPWM3_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    BlocoPWM3_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    BlocoPWM3_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    BlocoPWM3_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    BlocoPWM3_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define BlocoPWM3_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  BlocoPWM3_CTRL_CMPMODE2_SHIFT)
#define BlocoPWM3_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  BlocoPWM3_CTRL_CMPMODE1_SHIFT)
#define BlocoPWM3_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (BlocoPWM3_UsingFixedFunction)
   #define BlocoPWM3_PERIOD_LSB              (*(reg16 *) BlocoPWM3_PWMHW__PER0)
   #define BlocoPWM3_PERIOD_LSB_PTR          ( (reg16 *) BlocoPWM3_PWMHW__PER0)
   #define BlocoPWM3_COMPARE1_LSB            (*(reg16 *) BlocoPWM3_PWMHW__CNT_CMP0)
   #define BlocoPWM3_COMPARE1_LSB_PTR        ( (reg16 *) BlocoPWM3_PWMHW__CNT_CMP0)
   #define BlocoPWM3_COMPARE2_LSB            (0x00u)
   #define BlocoPWM3_COMPARE2_LSB_PTR        (0x00u)
   #define BlocoPWM3_COUNTER_LSB             (*(reg16 *) BlocoPWM3_PWMHW__CNT_CMP0)
   #define BlocoPWM3_COUNTER_LSB_PTR         ( (reg16 *) BlocoPWM3_PWMHW__CNT_CMP0)
   #define BlocoPWM3_CAPTURE_LSB             (*(reg16 *) BlocoPWM3_PWMHW__CAP0)
   #define BlocoPWM3_CAPTURE_LSB_PTR         ( (reg16 *) BlocoPWM3_PWMHW__CAP0)
   #define BlocoPWM3_RT1                     (*(reg8 *)  BlocoPWM3_PWMHW__RT1)
   #define BlocoPWM3_RT1_PTR                 ( (reg8 *)  BlocoPWM3_PWMHW__RT1)

#else
   #if (BlocoPWM3_Resolution == 8u) /* 8bit - PWM */

       #if(BlocoPWM3_PWMModeIsCenterAligned)
           #define BlocoPWM3_PERIOD_LSB      (*(reg8 *)  BlocoPWM3_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define BlocoPWM3_PERIOD_LSB_PTR  ((reg8 *)   BlocoPWM3_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define BlocoPWM3_PERIOD_LSB      (*(reg8 *)  BlocoPWM3_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define BlocoPWM3_PERIOD_LSB_PTR  ((reg8 *)   BlocoPWM3_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (BlocoPWM3_PWMModeIsCenterAligned) */

       #define BlocoPWM3_COMPARE1_LSB        (*(reg8 *)  BlocoPWM3_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define BlocoPWM3_COMPARE1_LSB_PTR    ((reg8 *)   BlocoPWM3_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define BlocoPWM3_COMPARE2_LSB        (*(reg8 *)  BlocoPWM3_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define BlocoPWM3_COMPARE2_LSB_PTR    ((reg8 *)   BlocoPWM3_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define BlocoPWM3_COUNTERCAP_LSB      (*(reg8 *)  BlocoPWM3_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define BlocoPWM3_COUNTERCAP_LSB_PTR  ((reg8 *)   BlocoPWM3_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define BlocoPWM3_COUNTER_LSB         (*(reg8 *)  BlocoPWM3_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define BlocoPWM3_COUNTER_LSB_PTR     ((reg8 *)   BlocoPWM3_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define BlocoPWM3_CAPTURE_LSB         (*(reg8 *)  BlocoPWM3_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define BlocoPWM3_CAPTURE_LSB_PTR     ((reg8 *)   BlocoPWM3_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(BlocoPWM3_PWMModeIsCenterAligned)
               #define BlocoPWM3_PERIOD_LSB      (*(reg16 *) BlocoPWM3_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define BlocoPWM3_PERIOD_LSB_PTR  ((reg16 *)  BlocoPWM3_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define BlocoPWM3_PERIOD_LSB      (*(reg16 *) BlocoPWM3_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define BlocoPWM3_PERIOD_LSB_PTR  ((reg16 *)  BlocoPWM3_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (BlocoPWM3_PWMModeIsCenterAligned) */

            #define BlocoPWM3_COMPARE1_LSB       (*(reg16 *) BlocoPWM3_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define BlocoPWM3_COMPARE1_LSB_PTR   ((reg16 *)  BlocoPWM3_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define BlocoPWM3_COMPARE2_LSB       (*(reg16 *) BlocoPWM3_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define BlocoPWM3_COMPARE2_LSB_PTR   ((reg16 *)  BlocoPWM3_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define BlocoPWM3_COUNTERCAP_LSB     (*(reg16 *) BlocoPWM3_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define BlocoPWM3_COUNTERCAP_LSB_PTR ((reg16 *)  BlocoPWM3_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define BlocoPWM3_COUNTER_LSB        (*(reg16 *) BlocoPWM3_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define BlocoPWM3_COUNTER_LSB_PTR    ((reg16 *)  BlocoPWM3_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define BlocoPWM3_CAPTURE_LSB        (*(reg16 *) BlocoPWM3_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define BlocoPWM3_CAPTURE_LSB_PTR    ((reg16 *)  BlocoPWM3_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(BlocoPWM3_PWMModeIsCenterAligned)
               #define BlocoPWM3_PERIOD_LSB      (*(reg16 *) BlocoPWM3_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define BlocoPWM3_PERIOD_LSB_PTR  ((reg16 *)  BlocoPWM3_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define BlocoPWM3_PERIOD_LSB      (*(reg16 *) BlocoPWM3_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define BlocoPWM3_PERIOD_LSB_PTR  ((reg16 *)  BlocoPWM3_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (BlocoPWM3_PWMModeIsCenterAligned) */

            #define BlocoPWM3_COMPARE1_LSB       (*(reg16 *) BlocoPWM3_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define BlocoPWM3_COMPARE1_LSB_PTR   ((reg16 *)  BlocoPWM3_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define BlocoPWM3_COMPARE2_LSB       (*(reg16 *) BlocoPWM3_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define BlocoPWM3_COMPARE2_LSB_PTR   ((reg16 *)  BlocoPWM3_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define BlocoPWM3_COUNTERCAP_LSB     (*(reg16 *) BlocoPWM3_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define BlocoPWM3_COUNTERCAP_LSB_PTR ((reg16 *)  BlocoPWM3_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define BlocoPWM3_COUNTER_LSB        (*(reg16 *) BlocoPWM3_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define BlocoPWM3_COUNTER_LSB_PTR    ((reg16 *)  BlocoPWM3_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define BlocoPWM3_CAPTURE_LSB        (*(reg16 *) BlocoPWM3_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define BlocoPWM3_CAPTURE_LSB_PTR    ((reg16 *)  BlocoPWM3_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define BlocoPWM3_AUX_CONTROLDP1          (*(reg8 *)  BlocoPWM3_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define BlocoPWM3_AUX_CONTROLDP1_PTR      ((reg8 *)   BlocoPWM3_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (BlocoPWM3_Resolution == 8) */

   #define BlocoPWM3_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  BlocoPWM3_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define BlocoPWM3_AUX_CONTROLDP0          (*(reg8 *)  BlocoPWM3_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define BlocoPWM3_AUX_CONTROLDP0_PTR      ((reg8 *)   BlocoPWM3_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (BlocoPWM3_UsingFixedFunction) */

#if(BlocoPWM3_KillModeMinTime )
    #define BlocoPWM3_KILLMODEMINTIME        (*(reg8 *)  BlocoPWM3_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define BlocoPWM3_KILLMODEMINTIME_PTR    ((reg8 *)   BlocoPWM3_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (BlocoPWM3_KillModeMinTime ) */

#if(BlocoPWM3_DeadBandMode == BlocoPWM3__B_PWM__DBM_256_CLOCKS)
    #define BlocoPWM3_DEADBAND_COUNT         (*(reg8 *)  BlocoPWM3_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define BlocoPWM3_DEADBAND_COUNT_PTR     ((reg8 *)   BlocoPWM3_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define BlocoPWM3_DEADBAND_LSB_PTR       ((reg8 *)   BlocoPWM3_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define BlocoPWM3_DEADBAND_LSB           (*(reg8 *)  BlocoPWM3_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(BlocoPWM3_DeadBandMode == BlocoPWM3__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (BlocoPWM3_UsingFixedFunction)
        #define BlocoPWM3_DEADBAND_COUNT         (*(reg8 *)  BlocoPWM3_PWMHW__CFG0)
        #define BlocoPWM3_DEADBAND_COUNT_PTR     ((reg8 *)   BlocoPWM3_PWMHW__CFG0)
        #define BlocoPWM3_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << BlocoPWM3_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define BlocoPWM3_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define BlocoPWM3_DEADBAND_COUNT         (*(reg8 *)  BlocoPWM3_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define BlocoPWM3_DEADBAND_COUNT_PTR     ((reg8 *)   BlocoPWM3_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define BlocoPWM3_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << BlocoPWM3_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define BlocoPWM3_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (BlocoPWM3_UsingFixedFunction) */
#endif /* (BlocoPWM3_DeadBandMode == BlocoPWM3__B_PWM__DBM_256_CLOCKS) */



#if (BlocoPWM3_UsingFixedFunction)
    #define BlocoPWM3_STATUS                 (*(reg8 *) BlocoPWM3_PWMHW__SR0)
    #define BlocoPWM3_STATUS_PTR             ((reg8 *) BlocoPWM3_PWMHW__SR0)
    #define BlocoPWM3_STATUS_MASK            (*(reg8 *) BlocoPWM3_PWMHW__SR0)
    #define BlocoPWM3_STATUS_MASK_PTR        ((reg8 *) BlocoPWM3_PWMHW__SR0)
    #define BlocoPWM3_CONTROL                (*(reg8 *) BlocoPWM3_PWMHW__CFG0)
    #define BlocoPWM3_CONTROL_PTR            ((reg8 *) BlocoPWM3_PWMHW__CFG0)
    #define BlocoPWM3_CONTROL2               (*(reg8 *) BlocoPWM3_PWMHW__CFG1)
    #define BlocoPWM3_CONTROL3               (*(reg8 *) BlocoPWM3_PWMHW__CFG2)
    #define BlocoPWM3_GLOBAL_ENABLE          (*(reg8 *) BlocoPWM3_PWMHW__PM_ACT_CFG)
    #define BlocoPWM3_GLOBAL_ENABLE_PTR      ( (reg8 *) BlocoPWM3_PWMHW__PM_ACT_CFG)
    #define BlocoPWM3_GLOBAL_STBY_ENABLE     (*(reg8 *) BlocoPWM3_PWMHW__PM_STBY_CFG)
    #define BlocoPWM3_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) BlocoPWM3_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define BlocoPWM3_BLOCK_EN_MASK          (BlocoPWM3_PWMHW__PM_ACT_MSK)
    #define BlocoPWM3_BLOCK_STBY_EN_MASK     (BlocoPWM3_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define BlocoPWM3_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define BlocoPWM3_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define BlocoPWM3_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define BlocoPWM3_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define BlocoPWM3_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define BlocoPWM3_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define BlocoPWM3_CTRL_ENABLE            (uint8)((uint8)0x01u << BlocoPWM3_CTRL_ENABLE_SHIFT)
    #define BlocoPWM3_CTRL_RESET             (uint8)((uint8)0x01u << BlocoPWM3_CTRL_RESET_SHIFT)
    #define BlocoPWM3_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << BlocoPWM3_CTRL_CMPMODE2_SHIFT)
    #define BlocoPWM3_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << BlocoPWM3_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define BlocoPWM3_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define BlocoPWM3_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << BlocoPWM3_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define BlocoPWM3_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define BlocoPWM3_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define BlocoPWM3_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define BlocoPWM3_STATUS_TC_INT_EN_MASK_SHIFT            (BlocoPWM3_STATUS_TC_SHIFT - 4u)
    #define BlocoPWM3_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define BlocoPWM3_STATUS_CMP1_INT_EN_MASK_SHIFT          (BlocoPWM3_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define BlocoPWM3_STATUS_TC              (uint8)((uint8)0x01u << BlocoPWM3_STATUS_TC_SHIFT)
    #define BlocoPWM3_STATUS_CMP1            (uint8)((uint8)0x01u << BlocoPWM3_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define BlocoPWM3_STATUS_TC_INT_EN_MASK              (uint8)((uint8)BlocoPWM3_STATUS_TC >> 4u)
    #define BlocoPWM3_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)BlocoPWM3_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define BlocoPWM3_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define BlocoPWM3_RT1_MASK              (uint8)((uint8)0x03u << BlocoPWM3_RT1_SHIFT)
    #define BlocoPWM3_SYNC                  (uint8)((uint8)0x03u << BlocoPWM3_RT1_SHIFT)
    #define BlocoPWM3_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define BlocoPWM3_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << BlocoPWM3_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define BlocoPWM3_SYNCDSI_EN            (uint8)((uint8)0x0Fu << BlocoPWM3_SYNCDSI_SHIFT)


#else
    #define BlocoPWM3_STATUS                (*(reg8 *)   BlocoPWM3_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define BlocoPWM3_STATUS_PTR            ((reg8 *)    BlocoPWM3_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define BlocoPWM3_STATUS_MASK           (*(reg8 *)   BlocoPWM3_PWMUDB_genblk8_stsreg__MASK_REG)
    #define BlocoPWM3_STATUS_MASK_PTR       ((reg8 *)    BlocoPWM3_PWMUDB_genblk8_stsreg__MASK_REG)
    #define BlocoPWM3_STATUS_AUX_CTRL       (*(reg8 *)   BlocoPWM3_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define BlocoPWM3_CONTROL               (*(reg8 *)   BlocoPWM3_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define BlocoPWM3_CONTROL_PTR           ((reg8 *)    BlocoPWM3_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define BlocoPWM3_CTRL_ENABLE_SHIFT      (0x07u)
    #define BlocoPWM3_CTRL_RESET_SHIFT       (0x06u)
    #define BlocoPWM3_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define BlocoPWM3_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define BlocoPWM3_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define BlocoPWM3_CTRL_ENABLE            (uint8)((uint8)0x01u << BlocoPWM3_CTRL_ENABLE_SHIFT)
    #define BlocoPWM3_CTRL_RESET             (uint8)((uint8)0x01u << BlocoPWM3_CTRL_RESET_SHIFT)
    #define BlocoPWM3_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << BlocoPWM3_CTRL_CMPMODE2_SHIFT)
    #define BlocoPWM3_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << BlocoPWM3_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define BlocoPWM3_STATUS_KILL_SHIFT          (0x05u)
    #define BlocoPWM3_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define BlocoPWM3_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define BlocoPWM3_STATUS_TC_SHIFT            (0x02u)
    #define BlocoPWM3_STATUS_CMP2_SHIFT          (0x01u)
    #define BlocoPWM3_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define BlocoPWM3_STATUS_KILL_INT_EN_MASK_SHIFT          (BlocoPWM3_STATUS_KILL_SHIFT)
    #define BlocoPWM3_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (BlocoPWM3_STATUS_FIFONEMPTY_SHIFT)
    #define BlocoPWM3_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (BlocoPWM3_STATUS_FIFOFULL_SHIFT)
    #define BlocoPWM3_STATUS_TC_INT_EN_MASK_SHIFT            (BlocoPWM3_STATUS_TC_SHIFT)
    #define BlocoPWM3_STATUS_CMP2_INT_EN_MASK_SHIFT          (BlocoPWM3_STATUS_CMP2_SHIFT)
    #define BlocoPWM3_STATUS_CMP1_INT_EN_MASK_SHIFT          (BlocoPWM3_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define BlocoPWM3_STATUS_KILL            (uint8)((uint8)0x00u << BlocoPWM3_STATUS_KILL_SHIFT )
    #define BlocoPWM3_STATUS_FIFOFULL        (uint8)((uint8)0x01u << BlocoPWM3_STATUS_FIFOFULL_SHIFT)
    #define BlocoPWM3_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << BlocoPWM3_STATUS_FIFONEMPTY_SHIFT)
    #define BlocoPWM3_STATUS_TC              (uint8)((uint8)0x01u << BlocoPWM3_STATUS_TC_SHIFT)
    #define BlocoPWM3_STATUS_CMP2            (uint8)((uint8)0x01u << BlocoPWM3_STATUS_CMP2_SHIFT)
    #define BlocoPWM3_STATUS_CMP1            (uint8)((uint8)0x01u << BlocoPWM3_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define BlocoPWM3_STATUS_KILL_INT_EN_MASK            (BlocoPWM3_STATUS_KILL)
    #define BlocoPWM3_STATUS_FIFOFULL_INT_EN_MASK        (BlocoPWM3_STATUS_FIFOFULL)
    #define BlocoPWM3_STATUS_FIFONEMPTY_INT_EN_MASK      (BlocoPWM3_STATUS_FIFONEMPTY)
    #define BlocoPWM3_STATUS_TC_INT_EN_MASK              (BlocoPWM3_STATUS_TC)
    #define BlocoPWM3_STATUS_CMP2_INT_EN_MASK            (BlocoPWM3_STATUS_CMP2)
    #define BlocoPWM3_STATUS_CMP1_INT_EN_MASK            (BlocoPWM3_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define BlocoPWM3_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define BlocoPWM3_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define BlocoPWM3_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define BlocoPWM3_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define BlocoPWM3_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* BlocoPWM3_UsingFixedFunction */

#endif  /* CY_PWM_BlocoPWM3_H */


/* [] END OF FILE */
