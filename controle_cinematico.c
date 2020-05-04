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
#include <stdlib.h>
#include <time.h>

#include "controle_cinematico.h"
#include "aux_functions.h"

#define START_X 0.0f
#define START_Y 0.0f

float dxAnt, dyAnt, dthetaAnt,
	  primDet, nVoltas, fator = 1;

char xStr[ 10 ],
     yStr[ 10 ],
     thetaStr[ 10 ],
     msgInstintivo[ 60 ],
     msgPlayer[ 64 ] = { 0 },
     msgTeste[ 50 ],
     sonar[ 6 ][ 10 ];
    
ControleCinematico cinematico = {
    .setPoint = { 0, 0, 0 }, // Pode ser uma referencia de posicao ou de velocidade.
    .erro = { 0, 0, 0 },
    .erroAnt = { 0, 0, 0 },
    .iErro = { 0, 0, 0 },
    .acao = { 0, 0, 0 },
    
    .velNavegacao = .2,
    .Kp_p = .1,
    .Ki_p = .015,
    .Kp_v = .1,
    .Ki_v = .015,
    .periodo = .05,
    
    .robo = {
        .L = .09,
        .R = .07,
        
        .x = START_X,
        .y = START_Y,
        .theta = 0,
        
        .dx = 0,
        .dy = 0,
        .dtheta = 0,
        
        .v = 0,
        .vn = 0,
        .w = 0,
        
        .motor = {
            { //motor[ 0 ]
                .velRad = 0,
                .velLin = 0,
                
                .nPulsosAtual = 0,
                .nPulsosAnterior = 0,
                .difPulsos = 0,
                
                .pwm = 0,
                .direcao = 0
            },
            
            { //motor[ 1 ]
                .velRad = 0,
                .velLin = 0,
                
                .nPulsosAtual = 0,
                .nPulsosAnterior = 0,
                .difPulsos = 0,
                
                .pwm = 0,
                .direcao = 0
            },
            
            { //motor[ 2 ]
                .velRad = 0,
                .velLin = 0,
                
                .nPulsosAtual = 0,
                .nPulsosAnterior = 0,
                .difPulsos = 0,
                
                .pwm = 0,
                .direcao = 0
            }
        } // motor
    } // robo
};

float sox = START_X, soy = START_Y;
float _t = 0.0f;
float sx = START_X, sy = START_Y;

void acaoControle(ControleCinematico *cc) {
    float ex, ey, ew,
          iex, iey, iew,
          t;
    
    const float Kp_p = cc->Kp_p,
                Ki_p = cc->Ki_p,
                Kp_v = cc->Kp_v,
                Ki_v = cc->Ki_v,
                L = cc->robo.L,
                R = cc->robo.R;
    
    float w1, w2, w3;
    
    ex = cc->erro[ 0 ];
    ey = cc->erro[ 1 ];
    ew = cc->erro[ 2 ];
	
    iex = cc->iErro[ 0 ];
    iey = cc->iErro[ 1 ];
    iew = cc->iErro[ 2 ];
    
    t = cc->robo.theta;
    
    w1 = (cos(t)*(Kp_v*ex + Ki_v*iex))/R + (sin(t)*(Kp_v*ey + Ki_v*iey))/R -
         (L*(Kp_p*ew + Ki_p*iew))/R;
    
    w2 = (sqrt(3)*(3*sin(t) - sqrt(3)*cos(t))*(Kp_v*ex + Ki_v*iex))/(6*R) -
         (L*(Kp_p*ew + Ki_p*iew))/R -
         (sqrt(3)*(3*cos(t) + sqrt(3)*sin(t))*(Kp_v*ey + Ki_v*iey))/(6*R);
         
    w3 = (sqrt(3)*(3*cos(t) - sqrt(3)*sin(t))*(Kp_v*ey + Ki_v*iey))/(6*R) -
         (sqrt(3)*(3*sin(t) + sqrt(3)*cos(t))*(Kp_v*ex + Ki_v*iex))/(6*R) -
         (L*(Kp_p*ew + Ki_p*iew))/R;
    
    // desnecessário?
    cc->robo.motor[ 0 ].velRad = w1;
    cc->robo.motor[ 1 ].velRad = w2;
    cc->robo.motor[ 2 ].velRad = w3;
    
    cc->acao[ 0 ] = w1;
    cc->acao[ 1 ] = w2;
    cc->acao[ 2 ] = w3;
	
	motor[ 0 ].setPoint = cc->acao[ 0 ];
	motor[ 1 ].setPoint = cc->acao[ 1 ];
	motor[ 2 ].setPoint = cc->acao[ 2 ];
}

void saidaModelo( ControleCinematico *cc ) {
    const float R = cc->robo.R,
                L = cc->robo.L;

    float w1 = cc->acao[ 0 ],
          w2 = cc->acao[ 1 ],
          w3 = cc->acao[ 2 ],
          t = cc->robo.theta;

    //*******************************************************************************//
    //******************************** ATENÇÃO **************************************//
    //*******************************************************************************//
    // COMENTAR AS LINHAS ABAIXO IMPLICA EM APLICAR A ACAO DE CONTROLE CALCULADA     //
    // PELO CONTROLADOR CINEMÁTICO DIRETAMENTE AO MODELO CINEMÁTICO, AO INVÉS DE     //
    // APLICAR A VELOCIDADE REAL DOS MOTORES. ÚTIL PARA TESTES SEM O ROBÔ            //
    //*******************************************************************************//
	// w1 = motor[ 0 ]._motor.velRad;
	// w2 = motor[ 1 ]._motor.velRad;
	// w3 = motor[ 2 ]._motor.velRad;

    cc->robo.dx = w2*((R*cos(t))/3 - (sqrt(3)*R*sin(t))/3) + w3*((R*cos(t))/3 + (sqrt(3)*R*sin(t))/3) - (2*R*w1*cos(t))/3;
    cc->robo.dy = w2*((R*sin(t))/3 + (sqrt(3)*R*cos(t))/3) + w3*((R*sin(t))/3 - (sqrt(3)*R*cos(t))/3) - (2*R*w1*sin(t))/3;
    cc->robo.dtheta = (R*(w1 + w2 + w3))/(3*L);
}

extern int flg_recv;

void controle_cinematico_isr() {
    //if (!POSICAO) {
    //   cinematico.setPoint[2] =
    //        atan2(cinematico.setPoint[1], cinematico.setPoint[0]);
    //}
    
    dxAnt = cinematico.robo.dx;
    dyAnt = cinematico.robo.dy;
    dthetaAnt = cinematico.robo.dtheta;
    
    saidaModelo(&cinematico);
    
    /*
    cinematico.robo.x +=
        (cinematico.periodo / 2) * (cinematico.robo.dx + dxAnt);
    cinematico.robo.y +=
        (cinematico.periodo / 2) * (cinematico.robo.dy + dyAnt);
    cinematico.robo.theta +=
        (cinematico.periodo / 2) * (cinematico.robo.dtheta + dthetaAnt);
    */
    
    cinematico.robo.x += cinematico.robo.dx;
    cinematico.robo.y += cinematico.robo.dy;
    cinematico.robo.theta += cinematico.robo.dtheta;
    
	/*nVoltas = cinematico.robo.theta / ( 2 * __PI );

	primDet = nVoltas - floor( nVoltas );

	if ( primDet < .5 )
	    cinematico.robo.theta = 2 * primDet * __PI;
	else
	    cinematico.robo.theta = -( 2 * __PI - 2 * primDet * __PI );*/
	
	nVoltas = cinematico.robo.theta / (2 * CY_M_PI);

    if (nVoltas < 0) {
        nVoltas *= -1;
        fator = -1;
    } else
        fator = 1;
    
	primDet = nVoltas - floor(nVoltas);

	cinematico.robo.theta = 2 * primDet * CY_M_PI * fator;
	
    cinematico.erroAnt[0] = cinematico.erro[0];
    cinematico.erroAnt[1] = cinematico.erro[1];
    cinematico.erroAnt[2] = cinematico.erro[2];
    
    // A variável "dados" é atualizada em ambos os casos (controle de posição ou
    // de velocidade) para que possa ser utilizada depois para mostrar no display
    // ou enviar via CAN ou UART.
    if (POSICAO) { // Se for controlador de posicao
        cinematico.erro[0] = -(cinematico.setPoint[0] - cinematico.robo.x);
        cinematico.erro[1] = -(cinematico.setPoint[1] - cinematico.robo.y);
        cinematico.erro[2] = -(cinematico.setPoint[2] - cinematico.robo.theta);
    } else { // Se for controlador de velocidade.
        cinematico.erro[0] = -(cinematico.setPoint[0] - cinematico.robo.dx);
        cinematico.erro[1] = -(cinematico.setPoint[1] - cinematico.robo.dy);
        cinematico.erro[2] = -(cinematico.setPoint[2] - cinematico.robo.theta); // continua theta.
    }
    
    cinematico.iErro[0] +=
        (cinematico.periodo / 2) * (cinematico.erro[0] + cinematico.erroAnt[0]);
    cinematico.iErro[1] +=
        (cinematico.periodo / 2) * (cinematico.erro[1] + cinematico.erroAnt[1]);
    cinematico.iErro[2] +=
        (cinematico.periodo / 2) * (cinematico.erro[2] + cinematico.erroAnt[2]);
    
    acaoControle(&cinematico);
    //***************************************************************************************//
    //********************* TRANSMISSÃO/EXIBIÇÃO DAS VARIÁVEIS DE PROCESSO ******************//
    //***************************************************************************************//
    // -----------------
    //Converte "float" para string:
	//ftoa( cinematico.robo.x, xStr );
	//ftoa( cinematico.robo.y, yStr );
	//ftoa( cinematico.robo.theta, thetaStr );
    // -----------------
    
    // -----------------
    // Gera string com dados para o Player/Stage:
    //sprintf( msgPlayer, "<%s,%s,%s>", xStr, yStr, thetaStr );
    // -----------------
    
    //sprintf( msgPlayer, "asdfghjklqwertyuiopasdfghjklqw" );
    //strcpy( msgPlayer, "<" );
    //strcat( msgPlayer, xStr );
    //strcat( msgPlayer, "," );
    //strcat( msgPlayer, yStr );
    //strcat( msgPlayer, "," );
    //strcat( msgPlayer, xStr );
    //strcat( msgPlayer, ">" );
    
    // Mostra dados no display:
	//LCD_Position( 1, 0 );
	//LCD_PrintString( msgPlayer );
	
    // Manda para Player/Stage (descomentar se player/stage estiver na UART):
    //UART_PutString( msgPlayer );
    //   
    //for ( it = 0; it < strlen( msgPlayer ); it++ )
	//	msgInstintivo[ it ] = msgPlayer[ it ];
	//
	//msgInstintivo[ it - 1 ] = ',';
	//
    //if ( strlen( recebido ) == 43 )
    //	for ( it1 = 0; it1 < strlen( recebido ); it1++ )
    //		msgInstintivo[ it++ ] = recebido[ it1 + 1 ];
    
    //strcpy( msgInstintivo,
    //    "<-7.000,-7.000,+0.000,+5.000,+5.000,+1.822,+0.880,+0.993,+0.993>" );
    
//        srand( time( 0 ) ); ftoa( ( float )( -5.0 + rand() % 10 ), sonar[ 0 ] );
//        srand( time( 0 ) ); ftoa( ( float )( -5.0 + rand() % 10 ), sonar[ 1 ] );
//        srand( time( 0 ) ); ftoa( ( float )( -5.0 + rand() % 10 ), sonar[ 2 ] );
//        srand( time( 0 ) ); ftoa( ( float )( -5.0 + rand() % 10 ), sonar[ 3 ] );
//        srand( time( 0 ) ); ftoa( ( float )( -5.0 + rand() % 10 ), sonar[ 4 ] );
//        srand( time( 0 ) ); ftoa( ( float )( -5.0 + rand() % 10 ), sonar[ 5 ] );
//        
//        sprintf( msgTeste, "%s,%s,%s,%s,%s,%s",
//            sonar[ 0 ], sonar[ 1 ], sonar[ 2 ],
//            sonar[ 3 ], sonar[ 4 ], sonar[ 5 ] );
//        
//        for ( it1 = 0; it1 < strlen( msgTeste ) + 1; it1++ )
//    		msgInstintivo[ it++ ] = msgTeste[ it1 ];
    
    // Função "externa" (isto é, não é uma tarefa) para enviar via CAN:
	/*taskENTER_CRITICAL();
	for ( it = 0; it <= strlen( xx ) + 1; it++ )
		_CANTxMessage[ it ] = xx[ it ];
	
    CANSendMessage( _CANTxMessage );
    taskEXIT_CRITICAL();*/
    
    // Utiliza tarefa para enviar via CAN. Tem a vantagem de poder utilizar "vTaskDelay" para
    // gerar delays sem travar outras tarefas.
    // Esta tarefa fica bloqueada esperando por um semáforo. Para mandar uma mensagem, esta
    // deve ser copiada para a variável global "_CANTxMessage" e então o semáforo deve ser
    // fornecido para a tarefa executar.
	// OBS.: misteriosamente "sprintf" e "strcpy" não estavam funcionando propriamente, por isso
	// a cópia "manual".
    //for ( it = 0; it <= strlen( msgInstintivo ) + 1; it++ )
	//	_CANTxMessage[ it ] = msgInstintivo[ it ];
    
    // -----------------
    //LCD_Position( 0, 0 );
    //LCD_PrintNumber( strlen( msgPlayer ) + 1 );
    //for ( it = 0; it <= strlen( msgPlayer ); it++ )
	//	_CANTxMessage[ it ] = msgPlayer[ it ];
	//xSemaphoreGive( xCANTxSemaphore );
    // -----------------
    
    // OBS.: se player/stage estiver na UART, manda msgInstintivo pela CAN.
    
	//CANSendMessage( _CANTxMessage );
    //***************************************************************************************//
}

/* [] END OF FILE */
