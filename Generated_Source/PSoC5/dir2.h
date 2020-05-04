/*******************************************************************************
* File Name: dir2.h  
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

#if !defined(CY_PINS_dir2_H) /* Pins dir2_H */
#define CY_PINS_dir2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "dir2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 dir2__PORT == 15 && ((dir2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    dir2_Write(uint8 value);
void    dir2_SetDriveMode(uint8 mode);
uint8   dir2_ReadDataReg(void);
uint8   dir2_Read(void);
void    dir2_SetInterruptMode(uint16 position, uint16 mode);
uint8   dir2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the dir2_SetDriveMode() function.
     *  @{
     */
        #define dir2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define dir2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define dir2_DM_RES_UP          PIN_DM_RES_UP
        #define dir2_DM_RES_DWN         PIN_DM_RES_DWN
        #define dir2_DM_OD_LO           PIN_DM_OD_LO
        #define dir2_DM_OD_HI           PIN_DM_OD_HI
        #define dir2_DM_STRONG          PIN_DM_STRONG
        #define dir2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define dir2_MASK               dir2__MASK
#define dir2_SHIFT              dir2__SHIFT
#define dir2_WIDTH              1u

/* Interrupt constants */
#if defined(dir2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in dir2_SetInterruptMode() function.
     *  @{
     */
        #define dir2_INTR_NONE      (uint16)(0x0000u)
        #define dir2_INTR_RISING    (uint16)(0x0001u)
        #define dir2_INTR_FALLING   (uint16)(0x0002u)
        #define dir2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define dir2_INTR_MASK      (0x01u) 
#endif /* (dir2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define dir2_PS                     (* (reg8 *) dir2__PS)
/* Data Register */
#define dir2_DR                     (* (reg8 *) dir2__DR)
/* Port Number */
#define dir2_PRT_NUM                (* (reg8 *) dir2__PRT) 
/* Connect to Analog Globals */                                                  
#define dir2_AG                     (* (reg8 *) dir2__AG)                       
/* Analog MUX bux enable */
#define dir2_AMUX                   (* (reg8 *) dir2__AMUX) 
/* Bidirectional Enable */                                                        
#define dir2_BIE                    (* (reg8 *) dir2__BIE)
/* Bit-mask for Aliased Register Access */
#define dir2_BIT_MASK               (* (reg8 *) dir2__BIT_MASK)
/* Bypass Enable */
#define dir2_BYP                    (* (reg8 *) dir2__BYP)
/* Port wide control signals */                                                   
#define dir2_CTL                    (* (reg8 *) dir2__CTL)
/* Drive Modes */
#define dir2_DM0                    (* (reg8 *) dir2__DM0) 
#define dir2_DM1                    (* (reg8 *) dir2__DM1)
#define dir2_DM2                    (* (reg8 *) dir2__DM2) 
/* Input Buffer Disable Override */
#define dir2_INP_DIS                (* (reg8 *) dir2__INP_DIS)
/* LCD Common or Segment Drive */
#define dir2_LCD_COM_SEG            (* (reg8 *) dir2__LCD_COM_SEG)
/* Enable Segment LCD */
#define dir2_LCD_EN                 (* (reg8 *) dir2__LCD_EN)
/* Slew Rate Control */
#define dir2_SLW                    (* (reg8 *) dir2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define dir2_PRTDSI__CAPS_SEL       (* (reg8 *) dir2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define dir2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) dir2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define dir2_PRTDSI__OE_SEL0        (* (reg8 *) dir2__PRTDSI__OE_SEL0) 
#define dir2_PRTDSI__OE_SEL1        (* (reg8 *) dir2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define dir2_PRTDSI__OUT_SEL0       (* (reg8 *) dir2__PRTDSI__OUT_SEL0) 
#define dir2_PRTDSI__OUT_SEL1       (* (reg8 *) dir2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define dir2_PRTDSI__SYNC_OUT       (* (reg8 *) dir2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(dir2__SIO_CFG)
    #define dir2_SIO_HYST_EN        (* (reg8 *) dir2__SIO_HYST_EN)
    #define dir2_SIO_REG_HIFREQ     (* (reg8 *) dir2__SIO_REG_HIFREQ)
    #define dir2_SIO_CFG            (* (reg8 *) dir2__SIO_CFG)
    #define dir2_SIO_DIFF           (* (reg8 *) dir2__SIO_DIFF)
#endif /* (dir2__SIO_CFG) */

/* Interrupt Registers */
#if defined(dir2__INTSTAT)
    #define dir2_INTSTAT            (* (reg8 *) dir2__INTSTAT)
    #define dir2_SNAP               (* (reg8 *) dir2__SNAP)
    
	#define dir2_0_INTTYPE_REG 		(* (reg8 *) dir2__0__INTTYPE)
#endif /* (dir2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_dir2_H */


/* [] END OF FILE */
