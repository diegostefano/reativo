/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "isr.h"
#include "controle_cinematico.h"

#include <math.h>

CY_ISR(timer_motores_isr_handler) {
    TimerMotores_ReadStatusRegister();
    
    controle_motores_isr();
}

CY_ISR(timer_cinematico_isr_handler) {
    TimerCinematico_ReadStatusRegister();
    
    _t += 0.07;
    
    controle_cinematico_isr();
    //cinematico.robo.x += 1;
    
    if (!POSICAO) {
        sx = sox + _t * cinematico.setPoint[0];
        sy = soy + _t * cinematico.setPoint[1];
    } else {
        sx = cinematico.setPoint[0];
        sy = cinematico.setPoint[1];
    }
}

/* [] END OF FILE */
