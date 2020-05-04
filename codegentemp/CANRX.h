/*******************************************************************************
* File Name: CANRX.h  
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

#if !defined(CY_PINS_CANRX_H) /* Pins CANRX_H */
#define CY_PINS_CANRX_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "CANRX_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 CANRX__PORT == 15 && ((CANRX__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    CANRX_Write(uint8 value);
void    CANRX_SetDriveMode(uint8 mode);
uint8   CANRX_ReadDataReg(void);
uint8   CANRX_Read(void);
void    CANRX_SetInterruptMode(uint16 position, uint16 mode);
uint8   CANRX_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the CANRX_SetDriveMode() function.
     *  @{
     */
        #define CANRX_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define CANRX_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define CANRX_DM_RES_UP          PIN_DM_RES_UP
        #define CANRX_DM_RES_DWN         PIN_DM_RES_DWN
        #define CANRX_DM_OD_LO           PIN_DM_OD_LO
        #define CANRX_DM_OD_HI           PIN_DM_OD_HI
        #define CANRX_DM_STRONG          PIN_DM_STRONG
        #define CANRX_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define CANRX_MASK               CANRX__MASK
#define CANRX_SHIFT              CANRX__SHIFT
#define CANRX_WIDTH              1u

/* Interrupt constants */
#if defined(CANRX__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in CANRX_SetInterruptMode() function.
     *  @{
     */
        #define CANRX_INTR_NONE      (uint16)(0x0000u)
        #define CANRX_INTR_RISING    (uint16)(0x0001u)
        #define CANRX_INTR_FALLING   (uint16)(0x0002u)
        #define CANRX_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define CANRX_INTR_MASK      (0x01u) 
#endif /* (CANRX__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define CANRX_PS                     (* (reg8 *) CANRX__PS)
/* Data Register */
#define CANRX_DR                     (* (reg8 *) CANRX__DR)
/* Port Number */
#define CANRX_PRT_NUM                (* (reg8 *) CANRX__PRT) 
/* Connect to Analog Globals */                                                  
#define CANRX_AG                     (* (reg8 *) CANRX__AG)                       
/* Analog MUX bux enable */
#define CANRX_AMUX                   (* (reg8 *) CANRX__AMUX) 
/* Bidirectional Enable */                                                        
#define CANRX_BIE                    (* (reg8 *) CANRX__BIE)
/* Bit-mask for Aliased Register Access */
#define CANRX_BIT_MASK               (* (reg8 *) CANRX__BIT_MASK)
/* Bypass Enable */
#define CANRX_BYP                    (* (reg8 *) CANRX__BYP)
/* Port wide control signals */                                                   
#define CANRX_CTL                    (* (reg8 *) CANRX__CTL)
/* Drive Modes */
#define CANRX_DM0                    (* (reg8 *) CANRX__DM0) 
#define CANRX_DM1                    (* (reg8 *) CANRX__DM1)
#define CANRX_DM2                    (* (reg8 *) CANRX__DM2) 
/* Input Buffer Disable Override */
#define CANRX_INP_DIS                (* (reg8 *) CANRX__INP_DIS)
/* LCD Common or Segment Drive */
#define CANRX_LCD_COM_SEG            (* (reg8 *) CANRX__LCD_COM_SEG)
/* Enable Segment LCD */
#define CANRX_LCD_EN                 (* (reg8 *) CANRX__LCD_EN)
/* Slew Rate Control */
#define CANRX_SLW                    (* (reg8 *) CANRX__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define CANRX_PRTDSI__CAPS_SEL       (* (reg8 *) CANRX__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define CANRX_PRTDSI__DBL_SYNC_IN    (* (reg8 *) CANRX__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define CANRX_PRTDSI__OE_SEL0        (* (reg8 *) CANRX__PRTDSI__OE_SEL0) 
#define CANRX_PRTDSI__OE_SEL1        (* (reg8 *) CANRX__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define CANRX_PRTDSI__OUT_SEL0       (* (reg8 *) CANRX__PRTDSI__OUT_SEL0) 
#define CANRX_PRTDSI__OUT_SEL1       (* (reg8 *) CANRX__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define CANRX_PRTDSI__SYNC_OUT       (* (reg8 *) CANRX__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(CANRX__SIO_CFG)
    #define CANRX_SIO_HYST_EN        (* (reg8 *) CANRX__SIO_HYST_EN)
    #define CANRX_SIO_REG_HIFREQ     (* (reg8 *) CANRX__SIO_REG_HIFREQ)
    #define CANRX_SIO_CFG            (* (reg8 *) CANRX__SIO_CFG)
    #define CANRX_SIO_DIFF           (* (reg8 *) CANRX__SIO_DIFF)
#endif /* (CANRX__SIO_CFG) */

/* Interrupt Registers */
#if defined(CANRX__INTSTAT)
    #define CANRX_INTSTAT            (* (reg8 *) CANRX__INTSTAT)
    #define CANRX_SNAP               (* (reg8 *) CANRX__SNAP)
    
	#define CANRX_0_INTTYPE_REG 		(* (reg8 *) CANRX__0__INTTYPE)
#endif /* (CANRX__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_CANRX_H */


/* [] END OF FILE */
