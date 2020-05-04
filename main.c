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
#include "project.h"
#include "aux_functions.h"
#include "controle_cinematico.h"
#include "isr.h"
#include "motor.h"

#include "defines.h"
#include "fuzzy_set.h"
#include "membership_functions.h"
#include "linguistic_variable.h"
#include "fis.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DELAY_MS            100
#define TIMER_MOTORES       0.015
#define NUM_OBST            6

//#include "gain_scheduling_kb.h"

uint8 can_msg_tx[8] = { 'o', 'i', ' ', 'm', 'b', 'e', 'd', 0 };

union Data goal_dist[2], closest_obst[2], action[2];
uint8 received = 1, is_positive[2] = {0};

float obstacles[NUM_OBST][2] = {{3.0f, 3.0f },
                                {5.0f, 7.0f },
                                {2.0f, 10.0f},
                                {8.0f, 12.0f},
                                {11.0f, 7.0f},
                                {7.0f, 4.0f}},
      goal[2] = {10.0f, 10.0f};

float distance(float x1, float y1, float x2, float y2) {
    return sqrtf(powf(x1 - x2, 2.0f) + powf(y1 - y2, 2.0f));
}

void update_state(float x, float y) {
    int closest = 0;
    float min_dist = 10000.0f;
    
    for (int i = 0; i < NUM_OBST; i++) {
        float dist = distance(x, y, obstacles[i][0], obstacles[i][1]);
        if (dist < min_dist) {
            min_dist = dist;
            closest = i;
        }
    }
    
    closest_obst[0].word = x - obstacles[closest][0];
    closest_obst[1].word = y - obstacles[closest][1];
    
    //goal_dist[0].word = x - goal[0];
    //goal_dist[1].word = y - goal[1];
    goal_dist[0].word = x;
    goal_dist[1].word = y;
}

int main(void)
{
    //QuadDec1_Start();
    //QuadDec2_Start();
    //QuadDec3_Start();
    
    TimerCinematico_Start();
    isr_timer_cinematico_StartEx(timer_cinematico_isr_handler);

    //TimerMotores_Start();
    //isr_timer_motores_StartEx(timer_motores_isr_handler);
    
    //BlocoPWM1_Start();
    //BlocoPWM2_Start();
    //BlocoPWM3_Start();
    
    UART_Start();
    CAN_Start();
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    char uart_msg[100];
    
    char str_rps1[10] = {0};
    char str_rps2[10] = {0};
    char str_rps3[10] = {0};
    
    motor[MOTOR1].periodo = TIMER_MOTORES;
    motor[MOTOR2].periodo = TIMER_MOTORES;
    motor[MOTOR3].periodo = TIMER_MOTORES;
    
    motor[MOTOR1].setPoint = 0;
    motor[MOTOR2].setPoint = 0;
    motor[MOTOR3].setPoint = 0;
    
    dir1_Write(0);
    dir2_Write(0);
    dir3_Write(0);
    
    char str_x[7] = {0},
        str_y[7] = {0},
        str_ex[7] = {0},
        str_ey[7] = {0},
        str_et[7] = {0},
        str_spx[10] = {0},
        str_spy[10] = {0};
    
    CyDelay(5000);
    
    CAN_SendMsg0();
    
    uint8 goal1 = 0, goal2 = 0;
    
    while (!received);
    
    for(;;)
    {
        //closest_obst[0].word = -3.14f;
        //closest_obst[1].word = 3.14f;
        
        //float2string(action[0].word, str_spx, 3);
        //float2string(action[1].word, str_spy, 3);
        //float2string(cinematico.setPoint[0], str_spx, 3);
        //float2string(cinematico.setPoint[1], str_spy, 3);
        float2string(goal[0], str_spx, 3);
        float2string(goal[1], str_spy, 3);
        
        float2string(cinematico.erro[0], str_ex, 3);
        float2string(cinematico.erro[1], str_ey, 3);
        float2string(cinematico.erro[2], str_et, 3);
        
        float2string(cinematico.robo.x, str_x, 3);
        float2string(cinematico.robo.y, str_y, 3);
        //float2string(CAN_GetTXErrorCount(), str_x, 3);
        //float2string(CAN_GetRXErrorCount(), str_y, 3);
        
        //sprintf(uart_msg, "---\r\nMotores: %s %s %s\r\nRobo: [%s, %s]\r\n",
        //    str_rps1, str_rps2, str_rps2, str_x, str_y);
        //sprintf(uart_msg, "Kp=%s Ki=%s rps1=%s\r\n",
        //    str_Kp, str_Kd, str_rps1);
        sprintf(uart_msg, "%s %s %s %s;\r\n",
            str_ex,
            str_ey,
            str_x,
            str_y);
        UART_PutString(uart_msg);
        
        update_state(cinematico.robo.x, cinematico.robo.y);
        
        //CAN_SendMsg1();
        
        if (received) {
            cinematico.setPoint[0] = action[0].word * 2.0f;
            cinematico.setPoint[1] = action[1].word * 2.0f;
            
            CAN_SendMsg0();
            CyDelay(30);
            CAN_SendMsg1();
            
            received = 0;
        }
        
        float dist_to_goal = distance(
            cinematico.robo.x, cinematico.robo.y,
            goal[0], goal[1]);
        
        if (dist_to_goal < 1.0f) {
            if (goal1 == 0) {
                goal1 = 1;
                
                goal[0] = 5;
                goal[1] = 2;
                
                dist_to_goal = distance(
                    cinematico.robo.x, cinematico.robo.y,
                    goal[0], goal[1]);
            } else
                break;
        }
        
        CyDelay(30);
    }
}

/* [] END OF FILE */
