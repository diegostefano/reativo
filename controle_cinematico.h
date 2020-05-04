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

#ifndef __KINEMATIC_CONTROL_H
#define __KINEMATIC_CONTROL_H

#include "motor.h"

// A flag abaixo determina se o controlador é de posicao ou de velocidade.
#define POSICAO 0
    
typedef struct {
    const float L, R;
    
	float x, y, theta,
          dx, dy, dtheta,
          v, vn, w;
    
    Motor motor[ 3 ];
} EstadoRobo;

typedef struct {
	float setPoint[ 3 ],
		  erro[ 3 ],
          erroAnt[ 3 ],
          iErro[ 3 ],
          acao[ 3 ];
    
    const float velNavegacao,
                Kp_p, Ki_p,
                Kp_v, Ki_v,
                periodo;
    
    EstadoRobo robo;
} ControleCinematico;

extern float _t;
extern float sox, soy;
extern float sx, sy;

extern ControleCinematico cinematico;

extern float dxAnt,
             dyAnt,
             dthetaAnt,
             primDet,
             nVoltas,
             fator;

extern char xStr[ 10 ],
            yStr[ 10 ],
            thetaStr[ 10 ],
            msgInstintivo[ 60 ],
            msgPlayer[ 64 ],
            msgTeste[ 50 ],
            sonar[ 6 ][ 10 ];

void acaoControle(ControleCinematico *);
void saidaModelo(ControleCinematico *);

void controle_cinematico_isr();

#endif

/* [] END OF FILE */
