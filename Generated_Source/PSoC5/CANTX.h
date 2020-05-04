/*******************************************************************************
* File Name: CANTX.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_CANTX_H) /* Pins CANTX_H */
#define CY_PINS_CANTX_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "CANTX_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 CANTX__PORT == 15 && ((CANTX__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    CANTX_Write(uint8 value);
void    CANTX_SetDriveMode(uint8 mode);
uint8   CANTX_ReadDataReg(void);
uint8   CANTX_Read(void);
void    CANTX_SetInterruptMode(uint16 position, uint16 mode);
uint8   CANTX_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the CANTX_SetDriveMode() function.
     *  @{
     */
        #define CANTX_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define CANTX_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define CANTX_DM_RES_UP          PIN_DM_RES_UP
        #define CANTX_DM_RES_DWN         PIN_DM_RES_DWN
        #define CANTX_DM_OD_LO           PIN_DM_OD_LO
        #define CANTX_DM_OD_HI           PIN_DM_OD_HI
        #define CANTX_DM_STRONG          PIN_DM_STRONG
        #define CANTX_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define CANTX_MASK               CANTX__MASK
#define CANTX_SHIFT              CANTX__SHIFT
#define CANTX_WIDTH              1u

/* Interrupt constants */
#if defined(CANTX__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in CANTX_SetInterruptMode() function.
     *  @{
     */
        #define CANTX_INTR_NONE      (uint16)(0x0000u)
        #define CANTX_INTR_RISING    (uint16)(0x0001u)
        #define CANTX_INTR_FALLING   (uint16)(0x0002u)
        #define CANTX_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define CANTX_INTR_MASK      (0x01u) 
#endif /* (CANTX__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define CANTX_PS                     (* (reg8 *) CANTX__PS)
/* Data Register */
#define CANTX_DR                     (* (reg8 *) CANTX__DR)
/* Port Number */
#define CANTX_PRT_NUM                (* (reg8 *) CANTX__PRT) 
/* Connect to Analog Globals */                                                  
#define CANTX_AG                     (* (reg8 *) CANTX__AG)                       
/* Analog MUX bux enable */
#define CANTX_AMUX                   (* (reg8 *) CANTX__AMUX) 
/* Bidirectional Enable */                                                        
#define CANTX_BIE                    (* (reg8 *) CANTX__BIE)
/* Bit-mask for Aliased Register Access */
#define CANTX_BIT_MASK               (* (reg8 *) CANTX__BIT_MASK)
/* Bypass Enable */
#define CANTX_BYP                    (* (reg8 *) CANTX__BYP)
/* Port wide control signals */                                                   
#define CANTX_CTL                    (* (reg8 *) CANTX__CTL)
/* Drive Modes */
#define CANTX_DM0                    (* (reg8 *) CANTX__DM0) 
#define CANTX_DM1                    (* (reg8 *) CANTX__DM1)
#define CANTX_DM2                    (* (reg8 *) CANTX__DM2) 
/* Input Buffer Disable Override */
#define CANTX_INP_DIS                (* (reg8 *) CANTX__INP_DIS)
/* LCD Common or Segment Drive */
#define CANTX_LCD_COM_SEG            (* (reg8 *) CANTX__LCD_COM_SEG)
/* Enable Segment LCD */
#define CANTX_LCD_EN                 (* (reg8 *) CANTX__LCD_EN)
/* Slew Rate Control */
#define CANTX_SLW                    (* (reg8 *) CANTX__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define CANTX_PRTDSI__CAPS_SEL       (* (reg8 *) CANTX__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define CANTX_PRTDSI__DBL_SYNC_IN    (* (reg8 *) CANTX__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define CANTX_PRTDSI__OE_SEL0        (* (reg8 *) CANTX__PRTDSI__OE_SEL0) 
#define CANTX_PRTDSI__OE_SEL1        (* (reg8 *) CANTX__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define CANTX_PRTDSI__OUT_SEL0       (* (reg8 *) CANTX__PRTDSI__OUT_SEL0) 
#define CANTX_PRTDSI__OUT_SEL1       (* (reg8 *) CANTX__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define CANTX_PRTDSI__SYNC_OUT       (* (reg8 *) CANTX__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(CANTX__SIO_CFG)
    #define CANTX_SIO_HYST_EN        (* (reg8 *) CANTX__SIO_HYST_EN)
    #define CANTX_SIO_REG_HIFREQ     (* (reg8 *) CANTX__SIO_REG_HIFREQ)
    #define CANTX_SIO_CFG            (* (reg8 *) CANTX__SIO_CFG)
    #define CANTX_SIO_DIFF           (* (reg8 *) CANTX__SIO_DIFF)
#endif /* (CANTX__SIO_CFG) */

/* Interrupt Registers */
#if defined(CANTX__INTSTAT)
    #define CANTX_INTSTAT            (* (reg8 *) CANTX__INTSTAT)
    #define CANTX_SNAP               (* (reg8 *) CANTX__SNAP)
    
	#define CANTX_0_INTTYPE_REG 		(* (reg8 *) CANTX__0__INTTYPE)
#endif /* (CANTX__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_CANTX_H */


/* [] END OF FILE */
