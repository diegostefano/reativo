/*******************************************************************************
* File Name: dir1.h  
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

#if !defined(CY_PINS_dir1_H) /* Pins dir1_H */
#define CY_PINS_dir1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "dir1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 dir1__PORT == 15 && ((dir1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    dir1_Write(uint8 value);
void    dir1_SetDriveMode(uint8 mode);
uint8   dir1_ReadDataReg(void);
uint8   dir1_Read(void);
void    dir1_SetInterruptMode(uint16 position, uint16 mode);
uint8   dir1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the dir1_SetDriveMode() function.
     *  @{
     */
        #define dir1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define dir1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define dir1_DM_RES_UP          PIN_DM_RES_UP
        #define dir1_DM_RES_DWN         PIN_DM_RES_DWN
        #define dir1_DM_OD_LO           PIN_DM_OD_LO
        #define dir1_DM_OD_HI           PIN_DM_OD_HI
        #define dir1_DM_STRONG          PIN_DM_STRONG
        #define dir1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define dir1_MASK               dir1__MASK
#define dir1_SHIFT              dir1__SHIFT
#define dir1_WIDTH              1u

/* Interrupt constants */
#if defined(dir1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in dir1_SetInterruptMode() function.
     *  @{
     */
        #define dir1_INTR_NONE      (uint16)(0x0000u)
        #define dir1_INTR_RISING    (uint16)(0x0001u)
        #define dir1_INTR_FALLING   (uint16)(0x0002u)
        #define dir1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define dir1_INTR_MASK      (0x01u) 
#endif /* (dir1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define dir1_PS                     (* (reg8 *) dir1__PS)
/* Data Register */
#define dir1_DR                     (* (reg8 *) dir1__DR)
/* Port Number */
#define dir1_PRT_NUM                (* (reg8 *) dir1__PRT) 
/* Connect to Analog Globals */                                                  
#define dir1_AG                     (* (reg8 *) dir1__AG)                       
/* Analog MUX bux enable */
#define dir1_AMUX                   (* (reg8 *) dir1__AMUX) 
/* Bidirectional Enable */                                                        
#define dir1_BIE                    (* (reg8 *) dir1__BIE)
/* Bit-mask for Aliased Register Access */
#define dir1_BIT_MASK               (* (reg8 *) dir1__BIT_MASK)
/* Bypass Enable */
#define dir1_BYP                    (* (reg8 *) dir1__BYP)
/* Port wide control signals */                                                   
#define dir1_CTL                    (* (reg8 *) dir1__CTL)
/* Drive Modes */
#define dir1_DM0                    (* (reg8 *) dir1__DM0) 
#define dir1_DM1                    (* (reg8 *) dir1__DM1)
#define dir1_DM2                    (* (reg8 *) dir1__DM2) 
/* Input Buffer Disable Override */
#define dir1_INP_DIS                (* (reg8 *) dir1__INP_DIS)
/* LCD Common or Segment Drive */
#define dir1_LCD_COM_SEG            (* (reg8 *) dir1__LCD_COM_SEG)
/* Enable Segment LCD */
#define dir1_LCD_EN                 (* (reg8 *) dir1__LCD_EN)
/* Slew Rate Control */
#define dir1_SLW                    (* (reg8 *) dir1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define dir1_PRTDSI__CAPS_SEL       (* (reg8 *) dir1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define dir1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) dir1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define dir1_PRTDSI__OE_SEL0        (* (reg8 *) dir1__PRTDSI__OE_SEL0) 
#define dir1_PRTDSI__OE_SEL1        (* (reg8 *) dir1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define dir1_PRTDSI__OUT_SEL0       (* (reg8 *) dir1__PRTDSI__OUT_SEL0) 
#define dir1_PRTDSI__OUT_SEL1       (* (reg8 *) dir1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define dir1_PRTDSI__SYNC_OUT       (* (reg8 *) dir1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(dir1__SIO_CFG)
    #define dir1_SIO_HYST_EN        (* (reg8 *) dir1__SIO_HYST_EN)
    #define dir1_SIO_REG_HIFREQ     (* (reg8 *) dir1__SIO_REG_HIFREQ)
    #define dir1_SIO_CFG            (* (reg8 *) dir1__SIO_CFG)
    #define dir1_SIO_DIFF           (* (reg8 *) dir1__SIO_DIFF)
#endif /* (dir1__SIO_CFG) */

/* Interrupt Registers */
#if defined(dir1__INTSTAT)
    #define dir1_INTSTAT            (* (reg8 *) dir1__INTSTAT)
    #define dir1_SNAP               (* (reg8 *) dir1__SNAP)
    
	#define dir1_0_INTTYPE_REG 		(* (reg8 *) dir1__0__INTTYPE)
#endif /* (dir1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_dir1_H */


/* [] END OF FILE */
