/*******************************************************************************
* File Name: qb3.h  
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

#if !defined(CY_PINS_qb3_H) /* Pins qb3_H */
#define CY_PINS_qb3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "qb3_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 qb3__PORT == 15 && ((qb3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    qb3_Write(uint8 value);
void    qb3_SetDriveMode(uint8 mode);
uint8   qb3_ReadDataReg(void);
uint8   qb3_Read(void);
void    qb3_SetInterruptMode(uint16 position, uint16 mode);
uint8   qb3_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the qb3_SetDriveMode() function.
     *  @{
     */
        #define qb3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define qb3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define qb3_DM_RES_UP          PIN_DM_RES_UP
        #define qb3_DM_RES_DWN         PIN_DM_RES_DWN
        #define qb3_DM_OD_LO           PIN_DM_OD_LO
        #define qb3_DM_OD_HI           PIN_DM_OD_HI
        #define qb3_DM_STRONG          PIN_DM_STRONG
        #define qb3_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define qb3_MASK               qb3__MASK
#define qb3_SHIFT              qb3__SHIFT
#define qb3_WIDTH              1u

/* Interrupt constants */
#if defined(qb3__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in qb3_SetInterruptMode() function.
     *  @{
     */
        #define qb3_INTR_NONE      (uint16)(0x0000u)
        #define qb3_INTR_RISING    (uint16)(0x0001u)
        #define qb3_INTR_FALLING   (uint16)(0x0002u)
        #define qb3_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define qb3_INTR_MASK      (0x01u) 
#endif /* (qb3__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define qb3_PS                     (* (reg8 *) qb3__PS)
/* Data Register */
#define qb3_DR                     (* (reg8 *) qb3__DR)
/* Port Number */
#define qb3_PRT_NUM                (* (reg8 *) qb3__PRT) 
/* Connect to Analog Globals */                                                  
#define qb3_AG                     (* (reg8 *) qb3__AG)                       
/* Analog MUX bux enable */
#define qb3_AMUX                   (* (reg8 *) qb3__AMUX) 
/* Bidirectional Enable */                                                        
#define qb3_BIE                    (* (reg8 *) qb3__BIE)
/* Bit-mask for Aliased Register Access */
#define qb3_BIT_MASK               (* (reg8 *) qb3__BIT_MASK)
/* Bypass Enable */
#define qb3_BYP                    (* (reg8 *) qb3__BYP)
/* Port wide control signals */                                                   
#define qb3_CTL                    (* (reg8 *) qb3__CTL)
/* Drive Modes */
#define qb3_DM0                    (* (reg8 *) qb3__DM0) 
#define qb3_DM1                    (* (reg8 *) qb3__DM1)
#define qb3_DM2                    (* (reg8 *) qb3__DM2) 
/* Input Buffer Disable Override */
#define qb3_INP_DIS                (* (reg8 *) qb3__INP_DIS)
/* LCD Common or Segment Drive */
#define qb3_LCD_COM_SEG            (* (reg8 *) qb3__LCD_COM_SEG)
/* Enable Segment LCD */
#define qb3_LCD_EN                 (* (reg8 *) qb3__LCD_EN)
/* Slew Rate Control */
#define qb3_SLW                    (* (reg8 *) qb3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define qb3_PRTDSI__CAPS_SEL       (* (reg8 *) qb3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define qb3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) qb3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define qb3_PRTDSI__OE_SEL0        (* (reg8 *) qb3__PRTDSI__OE_SEL0) 
#define qb3_PRTDSI__OE_SEL1        (* (reg8 *) qb3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define qb3_PRTDSI__OUT_SEL0       (* (reg8 *) qb3__PRTDSI__OUT_SEL0) 
#define qb3_PRTDSI__OUT_SEL1       (* (reg8 *) qb3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define qb3_PRTDSI__SYNC_OUT       (* (reg8 *) qb3__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(qb3__SIO_CFG)
    #define qb3_SIO_HYST_EN        (* (reg8 *) qb3__SIO_HYST_EN)
    #define qb3_SIO_REG_HIFREQ     (* (reg8 *) qb3__SIO_REG_HIFREQ)
    #define qb3_SIO_CFG            (* (reg8 *) qb3__SIO_CFG)
    #define qb3_SIO_DIFF           (* (reg8 *) qb3__SIO_DIFF)
#endif /* (qb3__SIO_CFG) */

/* Interrupt Registers */
#if defined(qb3__INTSTAT)
    #define qb3_INTSTAT            (* (reg8 *) qb3__INTSTAT)
    #define qb3_SNAP               (* (reg8 *) qb3__SNAP)
    
	#define qb3_0_INTTYPE_REG 		(* (reg8 *) qb3__0__INTTYPE)
#endif /* (qb3__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_qb3_H */


/* [] END OF FILE */
