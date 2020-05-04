/*******************************************************************************
* File Name: qb2.h  
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

#if !defined(CY_PINS_qb2_H) /* Pins qb2_H */
#define CY_PINS_qb2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "qb2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 qb2__PORT == 15 && ((qb2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    qb2_Write(uint8 value);
void    qb2_SetDriveMode(uint8 mode);
uint8   qb2_ReadDataReg(void);
uint8   qb2_Read(void);
void    qb2_SetInterruptMode(uint16 position, uint16 mode);
uint8   qb2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the qb2_SetDriveMode() function.
     *  @{
     */
        #define qb2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define qb2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define qb2_DM_RES_UP          PIN_DM_RES_UP
        #define qb2_DM_RES_DWN         PIN_DM_RES_DWN
        #define qb2_DM_OD_LO           PIN_DM_OD_LO
        #define qb2_DM_OD_HI           PIN_DM_OD_HI
        #define qb2_DM_STRONG          PIN_DM_STRONG
        #define qb2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define qb2_MASK               qb2__MASK
#define qb2_SHIFT              qb2__SHIFT
#define qb2_WIDTH              1u

/* Interrupt constants */
#if defined(qb2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in qb2_SetInterruptMode() function.
     *  @{
     */
        #define qb2_INTR_NONE      (uint16)(0x0000u)
        #define qb2_INTR_RISING    (uint16)(0x0001u)
        #define qb2_INTR_FALLING   (uint16)(0x0002u)
        #define qb2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define qb2_INTR_MASK      (0x01u) 
#endif /* (qb2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define qb2_PS                     (* (reg8 *) qb2__PS)
/* Data Register */
#define qb2_DR                     (* (reg8 *) qb2__DR)
/* Port Number */
#define qb2_PRT_NUM                (* (reg8 *) qb2__PRT) 
/* Connect to Analog Globals */                                                  
#define qb2_AG                     (* (reg8 *) qb2__AG)                       
/* Analog MUX bux enable */
#define qb2_AMUX                   (* (reg8 *) qb2__AMUX) 
/* Bidirectional Enable */                                                        
#define qb2_BIE                    (* (reg8 *) qb2__BIE)
/* Bit-mask for Aliased Register Access */
#define qb2_BIT_MASK               (* (reg8 *) qb2__BIT_MASK)
/* Bypass Enable */
#define qb2_BYP                    (* (reg8 *) qb2__BYP)
/* Port wide control signals */                                                   
#define qb2_CTL                    (* (reg8 *) qb2__CTL)
/* Drive Modes */
#define qb2_DM0                    (* (reg8 *) qb2__DM0) 
#define qb2_DM1                    (* (reg8 *) qb2__DM1)
#define qb2_DM2                    (* (reg8 *) qb2__DM2) 
/* Input Buffer Disable Override */
#define qb2_INP_DIS                (* (reg8 *) qb2__INP_DIS)
/* LCD Common or Segment Drive */
#define qb2_LCD_COM_SEG            (* (reg8 *) qb2__LCD_COM_SEG)
/* Enable Segment LCD */
#define qb2_LCD_EN                 (* (reg8 *) qb2__LCD_EN)
/* Slew Rate Control */
#define qb2_SLW                    (* (reg8 *) qb2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define qb2_PRTDSI__CAPS_SEL       (* (reg8 *) qb2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define qb2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) qb2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define qb2_PRTDSI__OE_SEL0        (* (reg8 *) qb2__PRTDSI__OE_SEL0) 
#define qb2_PRTDSI__OE_SEL1        (* (reg8 *) qb2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define qb2_PRTDSI__OUT_SEL0       (* (reg8 *) qb2__PRTDSI__OUT_SEL0) 
#define qb2_PRTDSI__OUT_SEL1       (* (reg8 *) qb2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define qb2_PRTDSI__SYNC_OUT       (* (reg8 *) qb2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(qb2__SIO_CFG)
    #define qb2_SIO_HYST_EN        (* (reg8 *) qb2__SIO_HYST_EN)
    #define qb2_SIO_REG_HIFREQ     (* (reg8 *) qb2__SIO_REG_HIFREQ)
    #define qb2_SIO_CFG            (* (reg8 *) qb2__SIO_CFG)
    #define qb2_SIO_DIFF           (* (reg8 *) qb2__SIO_DIFF)
#endif /* (qb2__SIO_CFG) */

/* Interrupt Registers */
#if defined(qb2__INTSTAT)
    #define qb2_INTSTAT            (* (reg8 *) qb2__INTSTAT)
    #define qb2_SNAP               (* (reg8 *) qb2__SNAP)
    
	#define qb2_0_INTTYPE_REG 		(* (reg8 *) qb2__0__INTTYPE)
#endif /* (qb2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_qb2_H */


/* [] END OF FILE */
