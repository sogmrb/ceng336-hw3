/* 
 * File:   main.c
 * Authors: Tahira Kazimi, e2415354
 *          Sogol Mehrabi, e2547321

 */
#include "Pragmas.h"
#include <string.h>
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <pic18f4620.h>
#include "lcd.h"
#include "the3.h"
#include "ADC.h"
/*
 * 
 */

unsigned short temp_0 ;
unsigned short temp_1;

void seven_seg_disp(unsigned int scoreA, unsigned int scoreB){
    PORTA = 0x00;
    if (scoreA==0){
        
        PORTAbits.RA3 = 1;
        PORTD = 0x3F;
        
    }
    else if (scoreA == 1){
        PORTAbits.RA3 = 0x01;
        PORTD = 0x06;
    }
    else if(scoreA == 2){
        PORTAbits.RA3 = 1;
        PORTD = 0x5B;
    }
    else if(scoreA == 3){
        PORTAbits.RA3 = 1;
        PORTD = 0x4F;
    }
    else if(scoreA == 4){
        PORTAbits.RA3 = 1;
        PORTD = 0x66;
    }
    else if(scoreA == 5){
        PORTAbits.RA3 = 1;
        PORTD = 0x6D;
    }
    __delay_us(SEG_PULSE_TIME);
    PORTD = 0x00;
    PORTA = 0x00;
    PORTAbits.RA4 = 1;
    PORTD = 0x40;
    
    __delay_us(SEG_PULSE_TIME);
    PORTD = 0x00;
    PORTA = 0x00;
    if (scoreB==0){
        
        
        PORTAbits.RA5 = 1;
        PORTD = 0x3F;
    }
    else if (scoreB == 1){
        PORTAbits.RA5 = 0x01;
        PORTD = 0x06;
       
    }
    else if(scoreB == 2){
        PORTAbits.RA5 = 1;
        PORTD = 0x5B;

    }
    else if(scoreB == 3){
        PORTAbits.RA5 = 1;
        PORTD = 0x4F;
    }
    else if(scoreB == 4){
        PORTAbits.RA5 = 1;
        PORTD = 0x66;
    }
    else if(scoreB == 5){
        PORTAbits.RA5 = 1;
        PORTD = 0x6D;
    }
    __delay_us(SEG_PULSE_TIME);
    return;
}




void init_players_frisbee(){
    LCDGoto(locationOfTeamA1[0],locationOfTeamA1[1]);
    LCDDat(0);

    LCDGoto(frisbeeLocation[0],frisbeeLocation[1]);
    LCDDat(4);
    LCDGoto(locationOfTeamA2[0],locationOfTeamA2[1]);
    LCDDat(1);
    LCDGoto(locationOfTeamB1[0],locationOfTeamB1[1]);
    LCDDat(2);
    LCDGoto(locationOfTeamB2[0],locationOfTeamB2[1]);
    LCDDat(2);
    
    return;
}

unsigned short * active_playerLoc(){
    if(teamA_1){
        return locationOfTeamA1;
    }
    else if(teamA_2){
        return locationOfTeamA2;
    }
    else if(teamB_1){
        return locationOfTeamB1;
    }
    else if(teamB_2){
        return locationOfTeamB2;
    }
}


unsigned char holdsFrisbee(unsigned short * frisbeeLoc, unsigned short * playerLoc){
    if (frisbeeLoc[0]==playerLoc[0] && frisbeeLoc[1] == playerLoc[1]) return 1;
    return 0;
}


void changeControl(){
    if(teamA_1){
        LCDGoto(locationOfTeamB2[0],locationOfTeamB2[1]);
        LCDDat(2);
        LCDGoto(locationOfTeamA1[0],locationOfTeamA1[1]);
        LCDDat(0);
    }
    else if(teamA_2){
        LCDGoto(locationOfTeamA1[0],locationOfTeamA1[1]);
        LCDDat(1);
        LCDGoto(locationOfTeamA2[0],locationOfTeamA2[1]);
        LCDDat(0);
    }
    else if(teamB_1){
        LCDGoto(locationOfTeamA2[0],locationOfTeamA2[1]);
        LCDDat(1);
        LCDGoto(locationOfTeamB1[0],locationOfTeamB1[1]);
        LCDDat(3);
    }
    else if(teamB_2){
        LCDGoto(locationOfTeamB1[0],locationOfTeamB1[1]);
        LCDDat(2);
        LCDGoto(locationOfTeamB2[0],locationOfTeamB2[1]);
        LCDDat(3);
    }
     
}

void moveCharacters(){
    random_move = 0;
    LCDClearSection(frisbeeLocation[0], frisbeeLocation[1]);
    frisbeeLocation[0] = frisbee_steps[index][0];
    frisbeeLocation[1] = frisbee_steps[index][1];
    LCDGoto(frisbee_steps[index][0],frisbee_steps[index][1]);
    LCDDat(4);
    if(teamA_1){    
        LCDGoto(locationOfTeamA1[0],locationOfTeamA1[1]);
        LCDDat(0);
        
        LCDClearSection(locationOfTeamA2[0], locationOfTeamA2[1]);
        if (!isOccupied(teamA2_route[index][0],teamA2_route[index][1]) && !(teamA2_route[index] == frisbeeLocation)){
            locationOfTeamA2[0] = teamA2_route[index][0];
            locationOfTeamA2[1] = teamA2_route[index][1];
        }
        LCDGoto(locationOfTeamA2[0],locationOfTeamA2[1]);
        LCDDat(1);
        
        LCDClearSection(locationOfTeamB1[0], locationOfTeamB1[1]);
        if (!isOccupied(teamB1_route[index][0],teamB1_route[index][1]) && !(teamB1_route[index] == frisbeeLocation)){
            locationOfTeamB1[0] = teamB1_route[index][0];
            locationOfTeamB1[1] = teamB1_route[index][1];
        }
        LCDGoto(locationOfTeamB1[0],locationOfTeamB1[1]);
        LCDDat(2);
        
        LCDClearSection(locationOfTeamB2[0], locationOfTeamB2[1]);
        if (!isOccupied(teamB2_route[index][0],teamB2_route[index][1]) && !(teamB2_route[index] == frisbeeLocation)){
            locationOfTeamB2[0] = teamB2_route[index][0];
            locationOfTeamB2[1] = teamB2_route[index][1];
        }
        LCDGoto(locationOfTeamB2[0],locationOfTeamB2[1]);
        LCDDat(2);

        }
    else if(teamA_2){
        LCDGoto(locationOfTeamA2[0],locationOfTeamA2[1]);
        LCDDat(0);
        
        LCDClearSection(locationOfTeamA1[0], locationOfTeamA1[1]);
        if (!isOccupied(teamA1_route[index][0],teamA1_route[index][1]) && !(teamA1_route[index] == frisbeeLocation)){
            locationOfTeamA1[0] = teamA1_route[index][0];
            locationOfTeamA1[1] = teamA1_route[index][1];
        }
        LCDGoto(locationOfTeamA1[0],locationOfTeamA1[1]);
        LCDDat(1);
        
        LCDClearSection(locationOfTeamB1[0], locationOfTeamB1[1]);
        if (!isOccupied(teamB1_route[index][0],teamB1_route[index][1]) && !(teamB1_route[index] == frisbeeLocation)){
            locationOfTeamB1[0] = teamB1_route[index][0];
            locationOfTeamB1[1] = teamB1_route[index][1];
        }
        LCDGoto(locationOfTeamB1[0],locationOfTeamB1[1]);
        LCDDat(2);
        
        LCDClearSection(locationOfTeamB2[0], locationOfTeamB2[1]);
        if (!isOccupied(teamB2_route[index][0],teamB2_route[index][1]) && !(teamB2_route[index] == frisbeeLocation)){
            locationOfTeamB2[0] = teamB2_route[index][0];
            locationOfTeamB2[1] = teamB2_route[index][1];
        }
        LCDGoto(locationOfTeamB2[0],locationOfTeamB2[1]);
        LCDDat(2);

    }
    else if(teamB_1){
        LCDGoto(locationOfTeamB1[0],locationOfTeamB1[1]);
        LCDDat(3);
        
        LCDClearSection(locationOfTeamA1[0], locationOfTeamA1[1]);
        if (!isOccupied(teamA1_route[index][0],teamA1_route[index][1]) && !(teamA1_route[index] == frisbeeLocation)){
            locationOfTeamA1[0] = teamA1_route[index][0];
            locationOfTeamA1[1] = teamA1_route[index][1];
        }
        LCDGoto(locationOfTeamA1[0],locationOfTeamA1[1]);
        LCDDat(1);
        
        LCDClearSection(locationOfTeamA2[0], locationOfTeamA2[1]);
        if (!isOccupied(teamA2_route[index][0],teamA2_route[index][1]) && !(teamA2_route[index] == frisbeeLocation)){
            locationOfTeamA2[0] = teamA2_route[index][0];
            locationOfTeamA2[1] = teamA2_route[index][1];
        }
        LCDGoto(locationOfTeamA2[0],locationOfTeamA2[1]);
        LCDDat(1);
        
        LCDClearSection(locationOfTeamB2[0], locationOfTeamB2[1]);
        if (!isOccupied(teamB2_route[index][0],teamB2_route[index][1]) && !(teamB2_route[index] == frisbeeLocation)){
            locationOfTeamB2[0] = teamB2_route[index][0];
            locationOfTeamB2[1] = teamB2_route[index][1];
        }
        LCDGoto(locationOfTeamB2[0],locationOfTeamB2[1]);
        LCDDat(2);

    }
    else if(teamB_2){
        LCDGoto(locationOfTeamB2[0],locationOfTeamB2[1]);
        LCDDat(3);
        
        LCDClearSection(locationOfTeamA1[0], locationOfTeamA1[1]);
        if (!isOccupied(teamA1_route[index][0],teamA1_route[index][1]) && !(teamA1_route[index] == frisbeeLocation)){
            locationOfTeamA1[0] = teamA1_route[index][0];
            locationOfTeamA1[1] = teamA1_route[index][1];
        }
        LCDGoto(locationOfTeamA1[0],locationOfTeamA1[1]);
        LCDDat(1);
        
        LCDClearSection(locationOfTeamA2[0], locationOfTeamA2[1]);
        if (!isOccupied(teamA2_route[index][0],teamA2_route[index][1]) && !(teamA2_route[index] == frisbeeLocation)){
            locationOfTeamA2[0] = teamA2_route[index][0];
            locationOfTeamA2[1] = teamA2_route[index][1];
        }
        LCDGoto(locationOfTeamA2[0],locationOfTeamA2[1]);
        LCDDat(1);

        LCDClearSection(locationOfTeamB1[0], locationOfTeamB1[1]);
        if (!isOccupied(teamB1_route[index][0],teamB1_route[index][1]) && !(teamB1_route[index] == frisbeeLocation)){
            locationOfTeamB1[0] = teamB1_route[index][0];
            locationOfTeamB1[1] = teamB1_route[index][1];
        }
        LCDGoto(locationOfTeamB1[0],locationOfTeamB1[1]);
        LCDDat(2);
               
        
    }
    
    if (frisbeeLocation[0] == target_x && frisbeeLocation[1] == target_y) {
            isActive = 0;
            timer0_flag = 0;
            timer1_flag = 0;
            LCDClearSection(target_x, target_y);
            changeBlink = 0;
             index = 0;
            if (holdsFrisbee(frisbeeLocation, locationOfTeamA1) || holdsFrisbee(frisbeeLocation, locationOfTeamA2)){
                LCDGoto(target_x, target_y);
                LCDDat(6);
                scoreA++;
            }
            else if (holdsFrisbee(frisbeeLocation, locationOfTeamB1) || holdsFrisbee(frisbeeLocation, locationOfTeamB2)){
                LCDGoto(target_x, target_y);
                LCDDat(7);
                scoreB++;
            }
            else{
                LCDGoto(target_x, target_y);
                LCDDat(4);
                
            }
            
        }
    else{
        index++;
    }
}

void movePlayerbyGamePad(){
    if (teamA_1){
        
        
        if(RB4_pressed && locationOfTeamA1[1]+1 <= 4 && !isOccupied(locationOfTeamA1[0], locationOfTeamA1[1]+1)){
            
            LCDClearSection(locationOfTeamA1[0], locationOfTeamA1[1]);
            if(holdsFrisbee(frisbeeLocation, locationOfTeamA1)){
                locationOfTeamA1[1] = locationOfTeamA1[1]+1;
                seven_seg_disp(scoreA,scoreB);
                LCDGoto(locationOfTeamA1[0],locationOfTeamA1[1]);
                LCDDat(0);
                LCDGoto(frisbeeLocation[0],frisbeeLocation[1]);
                LCDDat(4);                
            }
            
            else{
                locationOfTeamA1[1] = locationOfTeamA1[1]+1;
                
                seven_seg_disp(scoreA,scoreB);
                if(holdsFrisbee(frisbeeLocation, locationOfTeamA1)){
                    //seven_seg_disp(scoreA,scoreB);
                    LCDClearSection(frisbeeLocation[0],frisbeeLocation[1]); // clear frisbee too
                    LCDGoto(frisbeeLocation[0],frisbeeLocation[1]);
                    LCDDat(6); // player holds the frisbee 
                    seven_seg_disp(scoreA,scoreB);
                }
                else{
                        LCDGoto(locationOfTeamA1[0],locationOfTeamA1[1]);
                        LCDDat(0);
                        seven_seg_disp(scoreA,scoreB);
                }
                
            }
            
        }
        else if( RB5_pressed && locationOfTeamA1[0]+1 <= 16 && !isOccupied(locationOfTeamA1[0]+1, locationOfTeamA1[1])){ // does the index start from zero or one???? 
           LCDClearSection(locationOfTeamA1[0], locationOfTeamA1[1]);
           seven_seg_disp(scoreA,scoreB); 
            if(holdsFrisbee(frisbeeLocation, locationOfTeamA1)){
                locationOfTeamA1[0] = locationOfTeamA1[0]+1;
                LCDGoto(locationOfTeamA1[0],locationOfTeamA1[1]);
                LCDDat(0);
                LCDGoto(frisbeeLocation[0],frisbeeLocation[1]);
                LCDDat(4);
                seven_seg_disp(scoreA,scoreB);
            }
            
            else{
                locationOfTeamA1[0] = locationOfTeamA1[0]+1;
                
                
                seven_seg_disp(scoreA,scoreB);
                if(holdsFrisbee(frisbeeLocation, locationOfTeamA1)){
                    LCDClearSection(frisbeeLocation[0],frisbeeLocation[1]); // clear frisbee too
                    LCDGoto(frisbeeLocation[0],frisbeeLocation[1]);
                    LCDDat(6); // player holds the frisbee 
                    seven_seg_disp(scoreA,scoreB);
                }
                else{
                    LCDGoto(locationOfTeamA1[0],locationOfTeamA1[1]);
                    LCDDat(0); 
                    seven_seg_disp(scoreA,scoreB);
                }
            }       
        }
        
        else if(RB6_pressed && locationOfTeamA1[1]-1 >= 1 && !isOccupied(locationOfTeamA1[0], locationOfTeamA1[1]-1)){
            LCDClearSection(locationOfTeamA1[0], locationOfTeamA1[1]);
            seven_seg_disp(scoreA,scoreB);
            if(holdsFrisbee(frisbeeLocation, locationOfTeamA1)){
                locationOfTeamA1[1] = locationOfTeamA1[1]-1;
                LCDGoto(locationOfTeamA1[0],locationOfTeamA1[1]);
                LCDDat(0);
                LCDGoto(frisbeeLocation[0],frisbeeLocation[1]);
                LCDDat(4);
                seven_seg_disp(scoreA,scoreB);
            }
            
            else{
                locationOfTeamA1[1] = locationOfTeamA1[1]-1;
                
                seven_seg_disp(scoreA,scoreB);
                if(holdsFrisbee(frisbeeLocation, locationOfTeamA1)){
                    LCDClearSection(frisbeeLocation[0],frisbeeLocation[1]); // clear frisbee too
                    LCDGoto(frisbeeLocation[0],frisbeeLocation[1]);
                    LCDDat(6); // player holds the frisbee 
                    seven_seg_disp(scoreA,scoreB);
                }
                else{
                    LCDGoto(locationOfTeamA1[0],locationOfTeamA1[1]);
                    LCDDat(0); 
                    seven_seg_disp(scoreA,scoreB);
                }
            }
        }
        
        else if(RB7_pressed && locationOfTeamA1[0]-1 >= 1 && !isOccupied(locationOfTeamA1[0]-1, locationOfTeamA1[1])){
             LCDClearSection(locationOfTeamA1[0], locationOfTeamA1[1]);
             seven_seg_disp(scoreA,scoreB);
            if(holdsFrisbee(frisbeeLocation, locationOfTeamA1)){
                locationOfTeamA1[0] = locationOfTeamA1[0]-1;
                LCDGoto(locationOfTeamA1[0],locationOfTeamA1[1]);
                LCDDat(0);
                LCDGoto(frisbeeLocation[0],frisbeeLocation[1]);
                LCDDat(4);
                seven_seg_disp(scoreA,scoreB);
            }
             
            else{
                locationOfTeamA1[0] = locationOfTeamA1[0]-1;
                
                if(holdsFrisbee(frisbeeLocation, locationOfTeamA1)){
                    LCDClearSection(frisbeeLocation[0],frisbeeLocation[1]); // clear frisbee too
                    LCDGoto(frisbeeLocation[0],frisbeeLocation[1]);
                    LCDDat(6); // player holds the frisbee 
                    seven_seg_disp(scoreA,scoreB);
                }
                else{
                    LCDGoto(locationOfTeamA1[0],locationOfTeamA1[1]);
                    LCDDat(0); 
                    seven_seg_disp(scoreA,scoreB);
                }
            }
        }
        
    }
    else if (teamA_2){
        if(RB4_pressed && locationOfTeamA2[1]+1 <= 4 && !isOccupied(locationOfTeamA2[0], locationOfTeamA2[1]+1)){
            
            LCDClearSection(locationOfTeamA2[0], locationOfTeamA2[1]);
            if(holdsFrisbee(frisbeeLocation, locationOfTeamA2)){
                locationOfTeamA2[1] = locationOfTeamA2[1]+1;
                LCDGoto(locationOfTeamA2[0],locationOfTeamA2[1]);
                LCDDat(0);
                LCDGoto(frisbeeLocation[0],frisbeeLocation[1]);
                LCDDat(4);
            }
            else{
                locationOfTeamA2[1] = locationOfTeamA2[1]+1;
                
                if(holdsFrisbee(frisbeeLocation, locationOfTeamA2)){
                    LCDClearSection(frisbeeLocation[0],frisbeeLocation[1]); // clear frisbee too
                    LCDGoto(frisbeeLocation[0],frisbeeLocation[1]);
                    LCDDat(6); // player holds the frisbee 
                }
                else{
                    LCDGoto(locationOfTeamA2[0],locationOfTeamA2[1]);
                    LCDDat(0); 
                }
            }
            
        }
        else if( RB5_pressed && locationOfTeamA2[0]+1 <= 16 && !isOccupied(locationOfTeamA2[0]+1, locationOfTeamA2[1])){ // does the index start from zero or one????
             LCDClearSection(locationOfTeamA2[0], locationOfTeamA2[1]);
            if(holdsFrisbee(frisbeeLocation, locationOfTeamA2)){
                locationOfTeamA2[0] = locationOfTeamA2[0]+1;
                LCDGoto(locationOfTeamA2[0],locationOfTeamA2[1]);
                LCDDat(0);
                LCDGoto(frisbeeLocation[0],frisbeeLocation[1]);
                LCDDat(4);
            }
            else{
                locationOfTeamA2[0] = locationOfTeamA2[0]+1;
                LCDGoto(locationOfTeamA2[0],locationOfTeamA2[1]);
                if(holdsFrisbee(frisbeeLocation, locationOfTeamA2)){
                    LCDClearSection(frisbeeLocation[0],frisbeeLocation[1]); // clear frisbee too
                    LCDGoto(frisbeeLocation[0],frisbeeLocation[1]);
                    LCDDat(6); // player holds the frisbee 
                }
                else{
                    LCDGoto(locationOfTeamA2[0],locationOfTeamA2[1]);
                    LCDDat(0); 
                }
            }       
        }
        else if(RB6_pressed && locationOfTeamA2[1]-1 >= 1 && !isOccupied(locationOfTeamA2[0], locationOfTeamA2[1]-1)){
            LCDClearSection(locationOfTeamA2[0], locationOfTeamA2[1]);
            if(holdsFrisbee(frisbeeLocation, locationOfTeamA2)){
                locationOfTeamA2[1] = locationOfTeamA2[1]-1;
                LCDGoto(locationOfTeamA2[0],locationOfTeamA2[1]);
                LCDDat(0);
                LCDGoto(frisbeeLocation[0],frisbeeLocation[1]);
                LCDDat(4);
            }
            else{
                locationOfTeamA2[1] = locationOfTeamA2[1]-1;
                LCDGoto(locationOfTeamA2[0],locationOfTeamA2[1]);
                if(holdsFrisbee(frisbeeLocation, locationOfTeamA2)){
                    LCDClearSection(frisbeeLocation[0],frisbeeLocation[1]); // clear frisbee too
                    LCDGoto(frisbeeLocation[0],frisbeeLocation[1]);
                    LCDDat(6); // player holds the frisbee 
                }
                else{
                    LCDGoto(locationOfTeamA2[0],locationOfTeamA2[1]);
                    LCDDat(0); 
                }
            }
        }
        else if(RB7_pressed && locationOfTeamA2[0]-1 >= 1 && !isOccupied(locationOfTeamA2[0]-1, locationOfTeamA2[1])){
             LCDClearSection(locationOfTeamA2[0], locationOfTeamA2[1]);
            if(holdsFrisbee(frisbeeLocation, locationOfTeamA2)){
                locationOfTeamA2[0] = locationOfTeamA2[0]-1;
                LCDGoto(locationOfTeamA2[0],locationOfTeamA2[1]);
                LCDDat(0);
                LCDGoto(frisbeeLocation[0],frisbeeLocation[1]);
                LCDDat(4);
            }
            else{
                locationOfTeamA2[0] = locationOfTeamA2[0]-1;
                LCDGoto(locationOfTeamA2[0],locationOfTeamA2[1]);
                if(holdsFrisbee(frisbeeLocation, locationOfTeamA2)){
                    LCDClearSection(frisbeeLocation[0],frisbeeLocation[1]); // clear frisbee too
                    LCDGoto(frisbeeLocation[0],frisbeeLocation[1]);
                    LCDDat(6); // player holds the frisbee 
                }
                else{
                    LCDGoto(locationOfTeamA2[0],locationOfTeamA2[1]);
                    LCDDat(0); 
                }
            }
        }
    }
    else if (teamB_1){
        if(RB4_pressed && locationOfTeamB1[1]+1 <= 4 && !isOccupied(locationOfTeamB1[0], locationOfTeamB1[1]+1)){
            
            LCDClearSection(locationOfTeamB1[0], locationOfTeamB1[1]);
            if(holdsFrisbee(frisbeeLocation, locationOfTeamB1)){
                locationOfTeamB1[1] = locationOfTeamB1[1]+1;
                LCDGoto(locationOfTeamB1[0],locationOfTeamB1[1]);
                LCDDat(3);
                LCDGoto(frisbeeLocation[0],frisbeeLocation[1]);
                LCDDat(4);
            }
            else{
                locationOfTeamB1[1] = locationOfTeamB1[1]+1;               
                if(holdsFrisbee(frisbeeLocation, locationOfTeamB1)){
                    LCDClearSection(frisbeeLocation[0],frisbeeLocation[1]); // clear frisbee too
                    LCDGoto(frisbeeLocation[0],frisbeeLocation[1]);
                    LCDDat(7); // player holds the frisbee 
                }
                else{
                    LCDGoto(locationOfTeamB1[0],locationOfTeamB1[1]);
                    LCDDat(3); 
                }
            }
            
        }
        else if( RB5_pressed && locationOfTeamB1[0]+1 <= 16 && !isOccupied(locationOfTeamB1[0]+1, locationOfTeamB1[1])){ // does the index start from zero or one????
             LCDClearSection(locationOfTeamB1[0], locationOfTeamB1[1]);
            if(holdsFrisbee(frisbeeLocation, locationOfTeamB1)){
                locationOfTeamB1[0] = locationOfTeamB1[0]+1;
                LCDGoto(locationOfTeamB1[0],locationOfTeamB1[1]);
                LCDDat(3);
                LCDGoto(frisbeeLocation[0],frisbeeLocation[1]);
                LCDDat(4);
            }
            else{
                locationOfTeamB1[0] = locationOfTeamB1[0]+1;
                if(holdsFrisbee(frisbeeLocation, locationOfTeamB1)){
                    LCDClearSection(frisbeeLocation[0],frisbeeLocation[1]); // clear frisbee too
                    LCDGoto(frisbeeLocation[0],frisbeeLocation[1]);
                    LCDDat(7); // player holds the frisbee 
                }
                else{
                    LCDGoto(locationOfTeamB1[0],locationOfTeamB1[1]);
                    LCDDat(3); 
                }
            }       
        }
        else if(RB6_pressed && locationOfTeamB1[1]-1 >= 1 && !isOccupied(locationOfTeamB1[0], locationOfTeamB1[1]-1)){
            LCDClearSection(locationOfTeamB1[0], locationOfTeamB1[1]);
            if(holdsFrisbee(frisbeeLocation, locationOfTeamB1)){
                locationOfTeamB1[1] = locationOfTeamB1[1]-1;
                LCDGoto(locationOfTeamB1[0],locationOfTeamB1[1]);
                LCDDat(3);
                LCDGoto(frisbeeLocation[0],frisbeeLocation[1]);
                LCDDat(4);
            }
            else{
                locationOfTeamB1[1] = locationOfTeamB1[1]-1;
                if(holdsFrisbee(frisbeeLocation, locationOfTeamB1)){
                    LCDClearSection(frisbeeLocation[0],frisbeeLocation[1]); // clear frisbee too
                    LCDGoto(frisbeeLocation[0],frisbeeLocation[1]);
                    LCDDat(7); // player holds the frisbee 
                }
                else{
                    LCDGoto(locationOfTeamB1[0],locationOfTeamB1[1]);
                    LCDDat(3); 
                }
            }
        }
        else if(RB7_pressed && locationOfTeamB1[0]-1 >= 1 && !isOccupied(locationOfTeamB1[0]-1, locationOfTeamB1[1])){
             LCDClearSection(locationOfTeamB1[0], locationOfTeamB1[1]);
            if(holdsFrisbee(frisbeeLocation, locationOfTeamB1)){
                locationOfTeamB1[0] = locationOfTeamB1[0]-1;
                LCDGoto(locationOfTeamB1[0],locationOfTeamB1[1]);
                LCDDat(3);
                LCDGoto(frisbeeLocation[0],frisbeeLocation[1]);
                LCDDat(4);
            }
            else{
                locationOfTeamB1[0] = locationOfTeamB1[0]-1;
                if(holdsFrisbee(frisbeeLocation, locationOfTeamB1)){
                    LCDClearSection(frisbeeLocation[0],frisbeeLocation[1]); // clear frisbee too
                    LCDGoto(frisbeeLocation[0],frisbeeLocation[1]);
                    LCDDat(7); // player holds the frisbee 
                }
                else{
                    LCDGoto(locationOfTeamB1[0],locationOfTeamB1[1]);
                    LCDDat(3); 
                }
            }
        }
    }
    else if (teamB_2){
        if(RB4_pressed && locationOfTeamB2[1]+1 <= 4 && !isOccupied(locationOfTeamB2[0], locationOfTeamB2[1]+1)){
            
            LCDClearSection(locationOfTeamB2[0], locationOfTeamB2[1]);
            if(holdsFrisbee(frisbeeLocation, locationOfTeamB2)){
                locationOfTeamB2[1] = locationOfTeamB2[1]+1;
                LCDGoto(locationOfTeamB2[0],locationOfTeamB2[1]);
                LCDDat(3);
                LCDGoto(frisbeeLocation[0],frisbeeLocation[1]);
                LCDDat(4);
            }
            else{
                locationOfTeamB2[1] = locationOfTeamB2[1]+1;
                if(holdsFrisbee(frisbeeLocation, locationOfTeamB2)){
                    LCDClearSection(frisbeeLocation[0],frisbeeLocation[1]); // clear frisbee too
                    LCDGoto(frisbeeLocation[0],frisbeeLocation[1]);
                    LCDDat(7); // player holds the frisbee 
                }
                else{
                    LCDGoto(locationOfTeamB2[0],locationOfTeamB2[1]);
                    LCDDat(3); 
                }
            }
            
        }
        else if(RB5_pressed && locationOfTeamB2[0]+1 <= 16 && !isOccupied(locationOfTeamB2[0]+1, locationOfTeamB2[1])){ // does the index start from zero or one????
             LCDClearSection(locationOfTeamB2[0], locationOfTeamB2[1]);
            if(holdsFrisbee(frisbeeLocation, locationOfTeamB2)){
                locationOfTeamB2[0] = locationOfTeamB2[0]+1;
                LCDGoto(locationOfTeamB2[0],locationOfTeamB2[1]);
                LCDDat(3);
                LCDGoto(frisbeeLocation[0],frisbeeLocation[1]);
                LCDDat(4);
            }
            else{
                locationOfTeamB2[0] = locationOfTeamB2[0]+1;   
                if(holdsFrisbee(frisbeeLocation, locationOfTeamB2)){
                    LCDClearSection(frisbeeLocation[0],frisbeeLocation[1]); // clear frisbee too
                    LCDGoto(frisbeeLocation[0],frisbeeLocation[1]);
                    LCDDat(7); // player holds the frisbee 
                }
                else{
                    LCDGoto(locationOfTeamB2[0],locationOfTeamB2[1]);
                    LCDDat(3); 
                }
            }       
        }
        else if(RB6_pressed && locationOfTeamB2[1]-1 >= 1 && !isOccupied(locationOfTeamB2[0], locationOfTeamB2[1]-1)){
            LCDClearSection(locationOfTeamB2[0], locationOfTeamB2[1]);
            if(holdsFrisbee(frisbeeLocation, locationOfTeamB2)){
                locationOfTeamB2[1] = locationOfTeamB2[1]-1;
                LCDGoto(locationOfTeamB2[0],locationOfTeamB2[1]);
                LCDDat(3);
                LCDGoto(frisbeeLocation[0],frisbeeLocation[1]);
                LCDDat(4);
            }
            else{
                locationOfTeamB2[1] = locationOfTeamB2[1]-1;
                if(holdsFrisbee(frisbeeLocation, locationOfTeamB2)){
                    LCDClearSection(frisbeeLocation[0],frisbeeLocation[1]); // clear frisbee too
                    LCDGoto(frisbeeLocation[0],frisbeeLocation[1]);
                    LCDDat(7); // player holds the frisbee 
                }
                else{
                    LCDGoto(locationOfTeamB2[0],locationOfTeamB2[1]);
                    LCDDat(3); 
                }
            }
        }
        else if(RB7_pressed && locationOfTeamB2[0]-1 >= 1 && !isOccupied(locationOfTeamB2[0]-1, locationOfTeamB2[1])){
             LCDClearSection(locationOfTeamB2[0], locationOfTeamB2[1]);
            if(holdsFrisbee(frisbeeLocation, locationOfTeamB2)){
                locationOfTeamB2[0] = locationOfTeamB2[0]-1;
                LCDGoto(locationOfTeamB2[0],locationOfTeamB2[1]);
                LCDDat(3);
                LCDGoto(frisbeeLocation[0],frisbeeLocation[1]);
                LCDDat(4);
            }
            else{
                locationOfTeamB2[0] = locationOfTeamB2[0]-1;
                if(holdsFrisbee(frisbeeLocation, locationOfTeamB2)){
                    LCDClearSection(frisbeeLocation[0],frisbeeLocation[1]); // clear frisbee too
                    LCDGoto(frisbeeLocation[0],frisbeeLocation[1]);
                    LCDDat(7); // player holds the frisbee 
                }
                else{
                    LCDGoto(locationOfTeamB2[0],locationOfTeamB2[1]);
                    LCDDat(3); 
                }
            }
        }
    }
    
    return;
}



void __interrupt(high_priority) isr(void)
{
    if(!allow_interrupt){
        byte portb_temp = PORTB;
        portb_temp = portb_temp;
        INTCONbits.RBIF = 0;  // clear the interrupt flag
        INTCONbits.INT0IF = 0;
        INTCON3bits.INT1F = 0;
    }
    else {
        
        if(INTCONbits.RBIF)  // if there is a change on PORTB
        {
            //seven_seg_disp(scoreA,scoreB);
            byte portb_temp = PORTB;
            portb_temp = portb_temp;
            INTCONbits.RBIF = 0;  // clear the interrupt flag
            button_pressed = 1;
            allow_interrupt = 0;
            TMR3 = 0x0BDC;
            if(!PORTBbits.RB4) RB4_pressed = 1;
            else if (!PORTBbits.RB5) RB5_pressed = 1;
            else if (!PORTBbits.RB6) RB6_pressed = 1;
            else if (!PORTBbits.RB7) RB7_pressed = 1;
            //seven_seg_disp(scoreA,scoreB);
        }
        if (INTCONbits.INT0IF){
            INTCONbits.INT0IF = 0;
            TMR3 = 0x0BDC;
            button_pressed = 1;
            allow_interrupt = 0;
            RB0_pressed = 1;
            //seven_seg_disp(scoreA,scoreB);

        }
        if(INTCON3bits.INT1F){
            INTCON3bits.INT1F = 0;
            TMR3 = 0x0BDC;
            button_pressed = 1;
            allow_interrupt = 0;
            RB1_pressed = 1;
            //seven_seg_disp(scoreA,scoreB);
        }
    }
    if(INTCONbits.TMR0IF){
        INTCONbits.TMR0IF = 0;
        TMR0 = timer0_initVal;
        if(timer0_flag){
            random_move = 1;
        }
        //seven_seg_disp(scoreA,scoreB);
    }
    if (PIR1bits.TMR1IF){
        PIR1bits.TMR1IF = 0;
        TMR1 = 0x85EE;
        if(timer1_flag){
            isBlinkOn ^= 0x01;
            changeBlink = 1;
        }
        seven_seg_disp(scoreA,scoreB);
    }
    if(PIR2bits.TMR3IF){
        PIR2bits.TMR3IF = 0;
        TMR3 = 0x85EE;        
        if(button_pressed){
           if (tmr3_count == 0) tmr3_count++;
           else{
               allow_interrupt = 1; // make this zero or sth
               button_pressed = 0;
               tmr3_count = 0;
           }   
        }
        seven_seg_disp(scoreA,scoreB);
    }
    if(PIR1bits.ADIF){
        PIR1bits.ADIF = 0;
        CONVERT = 1;
        convertion = (unsigned short)((ADRESH << 8) + ADRESL);
        //ADCON0bits.GODONE = 1;
        
    }
}


int main(void ){
    INTCONbits.GIE = 0;
    
    InitLCD();
    
    ADCON1bits.PCFG0 = 0;
    ADCON1bits.PCFG1 = 0;
    ADCON1bits.PCFG2 = 1; //Analog to digital bits conversion
    ADCON1bits.PCFG3 = 1;
    INTCON2bits.RBPU = 1; //disable pull-ups to prevent the portb from being set to 1 in the start
    PORTB = 0xFF; //  make portb zero
    
    TRISA = 0x00;
    TRISD = 0x00;
    // 8 , 9, 10, 11 , 12T0CONbits.TMR0ON = 1; // turn on timer0 // GET THIS CHECKED AT THE END MIGHT NOT NEED TO TURN ON
    
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB4 = 1;  // RB4 as input
    TRISBbits.TRISB5 = 1;  // RB5 as input
    TRISBbits.TRISB6 = 1;  // RB6 as input
    TRISBbits.TRISB7 = 1;  // RB7 as input

    INTCONbits.RBIE = 0;   // PORTB change interrupt enable
    INTCONbits.RBIF = 0;
    INTCONbits.INT0IE = 1;
    INTCON3bits.INT1E = 1;
    INTCON2bits.INTEDG0 = 0;
    INTCON2bits.INTEDG1 = 0;
    init_timer0();
    init_timer1();
    init_timer2();
    init_timer3();
    PIR1bits.TMR1IF = 0;
    RCONbits.IPEN = 1;
    INTCON3bits.INT1IP = 1;
    IPR1bits.TMR1IP = 1;
    IPR2bits.TMR3IP = 1;
    INTCON2bits.RBIP=1;
    INTCON2bits.TMR0IP = 1; // setting the priority for timers 
        // global interrupt enable
    //INTCONbits.PEIE = 1;   // peripheral interrupt enable
    __delay_us(2000);
    byte portb_temp = PORTB;
    INTCONbits.RBIF = 0;
    INTCONbits.RBIE = 1;
    INTCONbits.GIE = 1;
    
    
    LCDAddSpecialCharacter(0, selected_teamA_player);
    LCDAddSpecialCharacter(1, teamA_player);
    LCDAddSpecialCharacter(2, teamB_player);
    LCDAddSpecialCharacter(3, selected_teamB_player);
    LCDAddSpecialCharacter(4, frisbee);
    LCDAddSpecialCharacter(5, frisbee_target);
    LCDAddSpecialCharacter(6, selected_teamA_player_with_frisbee);
    LCDAddSpecialCharacter(7, selected_teamB_player_with_frisbee);
    init_players_frisbee();
    initADC();
    ADCON0bits.GODONE = 1;
    

    while(1){
        if(RB4_pressed){
            movePlayerbyGamePad();
            RB4_pressed = 0;
        }
        if(RB5_pressed){
            movePlayerbyGamePad();
            RB5_pressed = 0;
        }
        if(RB6_pressed){
            movePlayerbyGamePad();
            RB6_pressed = 0;
        }
        if(RB7_pressed){
            movePlayerbyGamePad();
            RB7_pressed = 0;
        }
        if(RB0_pressed){
            RB0_pressed = 0;
            if(!isActive){
                unsigned short * playerLoc = active_playerLoc();
                if(holdsFrisbee(frisbeeLocation, playerLoc)){
                    isActive = 1;
                    num_of_steps = compute_frisbee_target_and_route(frisbeeLocation[0], frisbeeLocation[1]);;
                    random_player_move_A1(num_of_steps);
                    random_player_move_A2(num_of_steps);
                    random_player_move_B1(num_of_steps);
                    random_player_move_B2(num_of_steps);
                    TMR0 = 0x0BDC;
                    TMR1 = 0x85EE;
                    timer0_flag = 1;
                    timer1_flag = 1; // this is for blinking of target when frisbee is thrown

                }
            }
        }
        if(random_move){
            moveCharacters();
        }
        if(RB1_pressed){
            RB1_pressed = 0;
            unsigned short * playerLoc = active_playerLoc();
            if(isActive || (!isActive && !holdsFrisbee(frisbeeLocation, playerLoc))){
                if(teamA_1){
                    teamA_2 = 1;
                    teamA_1 = 0;
                }
                else if(teamA_2){
                    teamA_2 = 0;
                    teamB_1 = 1;
                }
                else if(teamB_1){
                    teamB_1 = 0;
                    teamB_2 = 1;
                }
                else if(teamB_2){
                    teamB_2 = 0;
                    teamA_1 = 1;
                }
                changeControl();
            }
        }
        if(changeBlink){
            if(isBlinkOn){
            LCDClearSection(target_x,target_y);
            changeBlink = 0;
            
            }
            else{
                LCDGoto(target_x, target_y);
                LCDDat(5);
                changeBlink = 0;
            }
        }
        if(CONVERT == 1)
        {
             CONVERT = 0;
            
            
            if(convertion != old_convertion ){
                if(convertion >= 0 && convertion <= 255){
                    timer0_initVal = 0xC2F7;
                    
                }
                else if(convertion >= 256 && convertion <= 511){
                    timer0_initVal = 0x85EE;
                }
                else if(convertion >= 512 && convertion <= 767){
                    timer0_initVal = 0x48E5;
                }
                else if(convertion >= 768 && convertion <= 1023){
                    timer0_initVal = 0x0BDC;
                }
                //sprintf(values, "%d", temp);
                //LCDCmd(LCD_CLEAR);
                //LCDGoto(5, 2);  
                //LCDStr(values);            
                
                old_convertion = convertion;
            }
           startADCConversion(0);
           
            
        }
        
        seven_seg_disp(scoreA,scoreB);
        
    }
    
    return (EXIT_SUCCESS);
}

