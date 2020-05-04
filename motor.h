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

#include <project.h>

#ifndef MOTOR_H
    #define MOTOR_H
    
    #define PPR300RPM           224.4
    #define PPR400RPM           231
    #define PPR600RPM           224.4

    #define RADSPERPULSE300RPM  ((2 * CY_M_PI) / PPR300RPM)
    #define RADSPERPULSE400RPM  ((2 * CY_M_PI) / PPR400RPM)
    #define RADSPERPULSE600RPM  ((2 * CY_M_PI) / PPR600RPM)

    #define MOTOR1  0
    #define MOTOR2  1
    #define MOTOR3  2
    
    #define MAX_PWM             2000
    #define MIN_PWM             0
    
    typedef struct {
    	float velRad,
    		  velRadMed,
              velLin;

        uint16 nPulsosAtual,
               nPulsosAnterior;
        int16 difPulsos;
        
        uint16 pwm;
        uint8 direcao;
        
        const float radPorPulso,
                    maxVelRad;
    } Motor;

    typedef struct {
        float setPoint,
              erro,
              erroAnt,
              integral,
              acao,
              periodo;
        
        float Kp,
              Kd,
              Ki,
              maxIntegral,
              maxAcao;
        
        Motor _motor;
    } ControleMotor;
    
    extern volatile ControleMotor motor[3];
    
    void controle_motores_isr();
#endif

/* [] END OF FILE */
