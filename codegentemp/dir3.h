/*******************************************************************************
* File Name: dir3.h  
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

#if !defined(CY_PINS_dir3_H) /* Pins dir3_H */
#define CY_PINS_dir3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "dir3_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 dir3__PORT == 15 && ((dir3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    dir3_Write(uint8 value);
void    dir3_SetDriveMode(uint8 mode);
uint8   dir3_ReadDataReg(void);
uint8   dir3_Read(void);
void    dir3_SetInterruptMode(uint16 position, uint16 mode);
uint8   dir3_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the dir3_SetDriveMode() function.
     *  @{
     */
        #define dir3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define dir3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define dir3_DM_RES_UP          PIN_DM_RES_UP
        #define dir3_DM_RES_DWN         PIN_DM_RES_DWN
        #define dir3_DM_OD_LO           PIN_DM_OD_LO
        #define dir3_DM_OD_HI           PIN_DM_OD_HI
        #define dir3_DM_STRONG          PIN_DM_STRONG
        #define dir3_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define dir3_MASK               dir3__MASK
#define dir3_SHIFT              dir3__SHIFT
#define dir3_WIDTH              1u

/* Interrupt constants */
#if defined(dir3__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in dir3_SetInterruptMode() function.
     *  @{
     */
        #define dir3_INTR_NONE      (uint16)(0x0000u)
        #define dir3_INTR_RISING    (uint16)(0x0001u)
        #define dir3_INTR_FALLING   (uint16)(0x0002u)
        #define dir3_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define dir3_INTR_MASK      (0x01u) 
#endif /* (dir3__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define dir3_PS                     (* (reg8 *) dir3__PS)
/* Data Register */
#define dir3_DR                     (* (reg8 *) dir3__DR)
/* Port Number */
#define dir3_PRT_NUM                (* (reg8 *) dir3__PRT) 
/* Connect to Analog Globals */                                                  
#define dir3_AG                     (* (reg8 *) dir3__AG)                       
/* Analog MUX bux enable */
#define dir3_AMUX                   (* (reg8 *) dir3__AMUX) 
/* Bidirectional Enable */                                                        
#define dir3_BIE                    (* (reg8 *) dir3__BIE)
/* Bit-mask for Aliased Register Access */
#define dir3_BIT_MASK               (* (reg8 *) dir3__BIT_MASK)
/* Bypass Enable */
#define dir3_BYP                    (* (reg8 *) dir3__BYP)
/* Port wide control signals */                                                   
#define dir3_CTL                    (* (reg8 *) dir3__CTL)
/* Drive Modes */
#define dir3_DM0                    (* (reg8 *) dir3__DM0) 
#define dir3_DM1                    (* (reg8 *) dir3__DM1)
#define dir3_DM2                    (* (reg8 *) dir3__DM2) 
/* Input Buffer Disable Override */
#define dir3_INP_DIS                (* (reg8 *) dir3__INP_DIS)
/* LCD Common or Segment Drive */
#define dir3_LCD_COM_SEG            (* (reg8 *) dir3__LCD_COM_SEG)
/* Enable Segment LCD */
#define dir3_LCD_EN                 (* (reg8 *) dir3__LCD_EN)
/* Slew Rate Control */
#define dir3_SLW                    (* (reg8 *) dir3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define dir3_PRTDSI__CAPS_SEL       (* (reg8 *) dir3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define dir3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) dir3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define dir3_PRTDSI__OE_SEL0        (* (reg8 *) dir3__PRTDSI__OE_SEL0) 
#define dir3_PRTDSI__OE_SEL1        (* (reg8 *) dir3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define dir3_PRTDSI__OUT_SEL0       (* (reg8 *) dir3__PRTDSI__OUT_SEL0) 
#define dir3_PRTDSI__OUT_SEL1       (* (reg8 *) dir3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define dir3_PRTDSI__SYNC_OUT       (* (reg8 *) dir3__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(dir3__SIO_CFG)
    #define dir3_SIO_HYST_EN        (* (reg8 *) dir3__SIO_HYST_EN)
    #define dir3_SIO_REG_HIFREQ     (* (reg8 *) dir3__SIO_REG_HIFREQ)
    #define dir3_SIO_CFG            (* (reg8 *) dir3__SIO_CFG)
    #define dir3_SIO_DIFF           (* (reg8 *) dir3__SIO_DIFF)
#endif /* (dir3__SIO_CFG) */

/* Interrupt Registers */
#if defined(dir3__INTSTAT)
    #define dir3_INTSTAT            (* (reg8 *) dir3__INTSTAT)
    #define dir3_SNAP               (* (reg8 *) dir3__SNAP)
    
	#define dir3_0_INTTYPE_REG 		(* (reg8 *) dir3__0__INTTYPE)
#endif /* (dir3__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_dir3_H */


/* [] END OF FILE */
