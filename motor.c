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

#include <math.h>

#include "motor.h"
#include "aux_functions.h"
#include "gain_scheduling_kb.h"

#define TAM     100

volatile ControleMotor motor[ 3 ] =
{
    {
    	._motor.velRad = 0.0,
		._motor.velRadMed = 0.0,
        ._motor.direcao = 0,
    	._motor.radPorPulso = RADSPERPULSE400RPM,
    	._motor.nPulsosAtual = 0,
    	._motor.nPulsosAnterior = 0,
    	._motor.difPulsos = 0,
        ._motor.maxVelRad = 31.0f,
        
    	.setPoint = 0.0,
    	.integral = 0.0,
    	.acao = 0.0,

    	.Kp = 0.239,
    	.Ki = 0.051,
        .Kd = 0.0,
    	.maxAcao = 300,
    	.maxIntegral = 100.0,
    	
    	.periodo = 0.01
    },
    
    {
    	._motor.velRad = 0.0,
		._motor.velRadMed = 0.0,
        ._motor.direcao = 0,
    	._motor.radPorPulso = RADSPERPULSE400RPM,
    	._motor.nPulsosAtual = 0,
    	._motor.nPulsosAnterior = 0,
    	._motor.difPulsos = 0,
    	._motor.maxVelRad = 31.0f,
        
    	.setPoint = 0.0,
    	.integral = 0.0,
    	.acao = 0.0,

    	.Kp = 0.239,
    	.Ki = 0.051,
        .Kd = 0.0,
    	.maxAcao = 300.0,
    	.maxIntegral = 100.0,
    	
    	.periodo = 0.01
    },
    
    {
    	._motor.velRad = 0.0,
		._motor.velRadMed = 0.0,
        ._motor.direcao = 0,
    	._motor.radPorPulso = RADSPERPULSE400RPM,
    	._motor.nPulsosAtual = 0,
    	._motor.nPulsosAnterior = 0,
    	._motor.difPulsos = 0,
    	._motor.maxVelRad = 31.0f,
        
    	.setPoint = 0.0,
    	.integral = 0.0,
    	.acao = 0.0,

    	.Kp = 0.239,
    	.Ki = 0.051,
        .Kd = 0.0,
    	.maxAcao = 300.0,
    	.maxIntegral = 100.0,
    	
    	.periodo = 0.01
    }
};

float memoria[3][TAM] = {{0.0}};
uint8 mem_idx = 0;

#define percent 0.9f

//float Kp_min = 0.239 * (1 - percent),
//        Kp_max = 0.239 * (1 + percent),
//        Ki_min = 0.051 * (1 - percent),
//        Ki_max = 0.051 * (1 + percent);

float Kp_min = 0.0f, Kp_max = 0.239,
      Ki_min = 0.0f, Ki_max = 0.051;

float y[MAXOUTVARS] = { 0.0f }, x[MAXINVARS] = { 0.0f };

void atualiza(volatile ControleMotor *motor) {
    motor->_motor.difPulsos = motor->_motor.nPulsosAtual - motor->_motor.nPulsosAnterior;
    motor->_motor.velRad = motor->_motor.radPorPulso * motor->_motor.difPulsos / motor->periodo;
    
    motor->erro = motor->setPoint - motor->_motor.velRad;
    
    //x[1] = motor->erro - motor->erroAnt;
    //x[0] = motor->erro;
    //inference(rules, 49, PROD, PROD, x, y);
    
    //motor->Kp = (Kp_max - Kp_min) * y[0] + Kp_min;
    //motor->Kd = y[1];
    //motor->Ki = motor->Kp * motor->Kp / (motor->Kd * y[2]);
    
    //motor->Kp = y[0];
    //motor->Kd = y[1];
    //motor->Ki = motor->Kp * motor->Kp / (y[2]);
    
    //motor->integral += (motor->erro + motor->erroAnt) * motor->periodo / 2.0;
    motor->integral += motor->erro;
    
    motor->acao = motor->Kp * motor->erro + motor->Ki * motor->integral;
    //motor->acao = motor->Kp * motor->erro + motor->Ki * motor->integral +
    //    motor->Kd * (motor->erro - motor->erroAnt);
        
    //motor->acao = (motor->acao > MAX_PWM ? MAX_PWM : motor->acao);
    motor->_motor.direcao = (motor->acao > 0);
    
    motor->_motor.pwm = (int)fabsf((motor->acao / motor->_motor.maxVelRad) * (MAX_PWM - MIN_PWM));
    //motor->_motor.pwm = (motor->_motor.pwm > MAX_PWM ? MAX_PWM : motor->_motor.pwm);
    
    //motor->_motor.pwm = (int)fabsf(motor->acao);
    
    motor->_motor.nPulsosAnterior = motor->_motor.nPulsosAtual;
    motor->erroAnt = motor->erro;
}

void controle_motores_isr() {
    motor[0]._motor.nPulsosAtual = QuadDec1_GetCounter();
    motor[1]._motor.nPulsosAtual = QuadDec2_GetCounter();
    motor[2]._motor.nPulsosAtual = QuadDec3_GetCounter();
    
    for (int m = 0; m < 3; m++)
        atualiza(&motor[m]);
    
    int index = (mem_idx + 1 >= TAM ? (mem_idx = 0) : ++mem_idx);
    
    memoria[0][index] = motor[0]._motor.velRad;
    motor[0]._motor.velRadMed = media(memoria[0], TAM);
    
    memoria[1][index] = motor[1]._motor.velRad;
    motor[1]._motor.velRadMed = media(memoria[1], TAM);
    
    memoria[2][index] = motor[2]._motor.velRad;
    motor[2]._motor.velRadMed = media(memoria[2], TAM);
    
    dir1_Write(motor[0].acao < 0);
    BlocoPWM1_WriteCompare(motor[0]._motor.pwm);
    
    dir2_Write(motor[1].acao < 0);
    BlocoPWM2_WriteCompare(motor[1]._motor.pwm);
    
    dir3_Write(motor[2].acao < 0);
    BlocoPWM3_WriteCompare(motor[2]._motor.pwm);
}
/* [] END OF FILE */
