#ifndef THE3_H
#define	THE3_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <xc.h>

// YOU CAN CHANGE THE FUNCTION RETURN TYPES, ARGUMENTS, FUNCTION NAMES, VARIABLE NAMES, ANYTHING YOU WANT
#define SHIFT_AMOUNT 2
typedef unsigned char byte;     // define byte here for readability and sanity.    
unsigned int scoreB = 0;
unsigned int scoreA = 0;
unsigned char teamA_1 = 1;
unsigned char teamA_2 = 0;
unsigned char teamB_1 = 0;
unsigned char teamB_2 = 0;
unsigned char isActive = 0;
unsigned short temp_rand = 0;
unsigned short num_of_steps = 0;
unsigned short index = 0;
unsigned char isBlinkOn = 0;
unsigned short teamA1_steps[15];
unsigned short teamA2_steps[15];
unsigned short teamB1_steps[15];
unsigned short teamB2_steps[15];
byte RB0_pressed = 0;
byte RB1_pressed = 0;
byte RB4_pressed = 0;
byte RB5_pressed = 0;
byte RB6_pressed = 0;
byte RB7_pressed = 0;
byte button_pressed = 0;
byte allow_interrupt = 1;
byte timer0_flag = 0;
byte random_move = 0;
byte timer1_flag = 0;
byte changeBlink = 0;
byte target_x, target_y; // hold the target <x,y> coordinates of the frisbee
byte tmr3_count = 0;
byte tmr3_flag = 0;
unsigned short timer0_initVal = 0xC2F7; // timer 0 initial value for 400 ms and 64 prescalar
char values[10] = {0};
unsigned short temp = 0;
unsigned short old_convertion = 1;
unsigned short convertion = 0;
volatile char CONVERT=0;

unsigned short locationOfTeamA1 [] = {
    3,2
} ;
unsigned short locationOfTeamA2 [] = {
    3,3
} ;
unsigned short locationOfTeamB1 [] = {
    14,2
} ;
unsigned short locationOfTeamB2 [] = {
    14,3
} ;
unsigned short frisbeeLocation [] = {
    9, 2
};

byte teamA1_route[15][2];
byte teamA2_route[15][2];
byte teamB1_route[15][2];
byte teamB2_route[15][2];

byte teamA_player[] = {
                  0b10001,
                  0b10101,
                  0b01010,
                  0b00100,
                  0b00100,
                  0b00100,
                  0b01010,
                  0b01010
                };              // teamA_player NOT holding the frisbee, NOT indicated by the cursor

byte teamB_player[] = {
                  0b10001,
                  0b10101,
                  0b01010,
                  0b00100,
                  0b01110,
                  0b11111,
                  0b01010,
                  0b01010
                };              // teamB_player NOT holding the frisbee, NOT indicated by the cursor

byte selected_teamA_player[] = {
                  0b10001,
                  0b10101,
                  0b01010,
                  0b00100,
                  0b00100,
                  0b00100,
                  0b01010,
                  0b11111
                };              // teamA_player, NOT holding the frisbee, indicated by the cursor

byte selected_teamB_player[] = {
                  0b10001,
                  0b10101,
                  0b01010,
                  0b00100,
                  0b01110,
                  0b11111,
                  0b01010,
                  0b11111
                };              // teamB_player, NOT holding the frisbee, indicated by the cursor


byte selected_teamA_player_with_frisbee[] = {
                  0b11111,
                  0b10101,
                  0b01010,
                  0b00100,
                  0b00100,
                  0b00100,
                  0b01010,
                  0b11111
                };              // teamA_player, holding the frisbee, indicated by the cursor

byte selected_teamB_player_with_frisbee[] = {
                  0b11111,
                  0b10101,
                  0b01010,
                  0b00100,
                  0b01110,
                  0b11111,
                  0b01010,
                  0b11111
                };              // teamB_player, holding the frisbee, indicated by the cursor

byte frisbee[] = {
                  0b01110,
                  0b11111,
                  0b11111,
                  0b11111,
                  0b01110,
                  0b00000,
                  0b00000,
                  0b00000
                };              // the frisbee itself

byte frisbee_target[] = {
                  0b01110,
                  0b10001,
                  0b10001,
                  0b10001,
                  0b01110,
                  0b00000,
                  0b00000,
                  0b00000
                };              // the character indicating the target position of the frisbee
                                // you should blink this character 



unsigned short frisbee_steps[15][2];                    // maximum 15 steps in x (horizontal) and y (vertical) directions

// function declarations
unsigned short compute_frisbee_target_and_route(unsigned short current_fisbee_x_position, unsigned short current_fisbee_y_position);   // a simple implementation is given below
unsigned short random_generator(unsigned short modulo); // YOU SHOULD IMPLEMENT THIS FUNCTION ON YOUR OWN

unsigned short compute_frisbee_target_and_route(unsigned short current_fisbee_x_position, unsigned short current_fisbee_y_position) {
    
   // YOU CAN DO ANY NECESSARY CHANGES IN THIS FUNCTION //
    
    unsigned short x_step_size, y_step_size;    // hold the number of cells to walk in x and y dimensions, respectively
    unsigned short number_of_steps;             // hold the maximum number of steps to walk

    
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    // compute target <x,y> position for the frisbee
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    while(1) {  // loop until finding a valid position
        
        target_x = random_generator(16) + 1; // find a random integer in [0, 15] + 1
        target_y = random_generator(4) + 1;  // find a random integer in [0, 3] + 1
        
        // how many cells are there in x-dimension (horizontal) between the target and current positions of the frisbee
        if (target_x < current_fisbee_x_position)
            x_step_size = current_fisbee_x_position - target_x;
        else
            x_step_size = target_x - current_fisbee_x_position;
        
        // how many cells are there in y-dimension (vertical) between the target and current positions of the frisbee
        if (target_y < current_fisbee_y_position)
            y_step_size = current_fisbee_y_position - target_y;
        else
            y_step_size = target_y - current_fisbee_y_position;
        
        // a close target cell is not preferred much, so change the target if it is very close
        if (x_step_size <= 2 && y_step_size <= 2)
            continue;
        
        // total number of steps can be as many as the maximum of {x_step_size, y_step_size}
        if (x_step_size > y_step_size)
            number_of_steps = x_step_size;
        else
            number_of_steps = y_step_size;
        
        break;
    }
    
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    // compute a route for the frisbee to reach the target step-by-step
    // note that each step corresponds to a 1-cell-movement in x and y directions simultaneously
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    
    // steps in x direction
    unsigned short x = current_fisbee_x_position;
    for (unsigned short i = 0; i < 16; i++){
        frisbee_steps[i][0] = -1;
        frisbee_steps[i][1] = -1;
    }
    if (target_x < current_fisbee_x_position) {
        for (unsigned short i = 0; i < x_step_size; i++) {
            x = x - 1;                  // move in -x direction
            frisbee_steps[i][0] = x;    // the x-position at i^th step
        }  
    }
    else {
        for (unsigned short i = 0; i < x_step_size; i++) {
            x = x + 1;                  // move in +x direction
            frisbee_steps[i][0] = x;    // the x-position at i^th step
        } 
    }
    for (unsigned short i = x_step_size; i < number_of_steps; i++)
        frisbee_steps[i][0] = x;        // fill the rest of the steps as "no movement" in x direction 
    
    // steps in y direction
    unsigned short y = current_fisbee_y_position;
    if (target_y < current_fisbee_y_position) {
        for (unsigned short i = 0; i < y_step_size; i++) {
            y = y - 1;                  // move in -y direction
            frisbee_steps[i][1] = y;    // the y-position at i^th step
        }  
    }
    else {
        for (unsigned short i = 0; i < y_step_size; i++) {
            y = y + 1;                  // move in +y direction
            frisbee_steps[i][1] = y;    // the y-position at i^th step
        } 
    }
    for (unsigned short i = y_step_size; i < number_of_steps; i++)
        frisbee_steps[i][1] = y;        // fill the rest of the steps as "no movement" in y direction
    
    return number_of_steps;
}


void init_timer0(){
    INTCONbits.TMR0IE = 1;
    T0CON = 0x05; // prescalar of 1:64, the timer is in 16-bits
    TMR0 = timer0_initVal;
    T0CONbits.TMR0ON = 1;         
          
}
void init_timer1() // for blinking target
{ 
    TMR1 = 0x85EE;  // reset Timer1 counter
    T1CON = 0xB0;   // set Timer1 in 16 bit mode and start timer
    PIE1bits.TMR1IE = 1;
    T1CONbits.TMR1ON = 1;
}
void init_timer2(){
    TMR2 = 0;  // reset Timer1 counter
    T2CON = 0x04;   //turn on tmr2 for randomness
    
}

void init_timer3(){
    TMR3 = 0x85EE;
    T3CON = 0xB0; // 16-bits, 8 prescalar
    PIE2bits.TMR3IE = 1;
    T3CONbits.TMR3ON = 1;
}


void random_player_move_A1(unsigned short numOfSteps){
    
    for(unsigned short i=0; i < numOfSteps; i++){
        teamA1_steps[i] = random_generator(8);
        
        
        teamA1_route[i][0] = locationOfTeamA1[0];
        teamA1_route[i][1] = locationOfTeamA1[1];
        byte x = locationOfTeamA1[0];
        byte y = locationOfTeamA1[1];

        if (teamA1_steps[i]==0){
            if (x < 4 && !(x == target_x && y+1 == target_y)) teamA1_route[i][1] = y - 1;
            
        }
       
        else if (teamA1_steps[i]==1){
            if(x < 16 && !(x+1 == target_x && y == target_y)) teamA1_route[i][0] = x + 1;
        }
        else if (teamA1_steps[i]==2){
            if(x > 0 && !(x == target_x && y-1 == target_y)) teamA1_route[i][1] = y - 1;
        }
        else if (teamA1_steps[i]==3){
            if(x > 0 && !(x-1 == target_x && y == target_y)) teamA1_route[i][0] = x - 1;
        }
        else if (teamA1_steps[i]==4){
            if(y < 16 && y < 4 && !(x+1 == target_x && y+1 == target_y)) {
                teamA1_route[i][0] = x + 1;
                teamA1_route[i][1] = y + 1;
            }
        }
        else if (teamA1_steps[i]==5){
            if(x < 16 && y > 0 && !(x+1 == target_x && y-1 == target_y)) {
                teamA1_route[i][0] = x + 1;
                teamA1_route[i][1] = y - 1;
            }
        }
        else if (teamA1_steps[i]==6){
            if(x > 0 && y > 0 && !(x-1 == target_x && y-1 == target_y)) {
                teamA1_route[i][0] = x - 1;
                teamA1_route[i][1] = y - 1;
            }
        }
        else if (teamA1_steps[i]==7){
            if(x > 0 && y < 4 && !(x-1 == target_x && y+1 == target_y)) {
                teamA1_route[i][0] = x - 1;
                teamA1_route[i][1] = y + 1;
            }
        }
    }
    
}

void random_player_move_A2(unsigned short numOfSteps){
    
    for(unsigned short i=0; i < numOfSteps; i++){
        teamA2_steps[i] = random_generator(8);
        
        
        teamA2_route[i][0] = locationOfTeamA2[0];
        teamA2_route[i][1] = locationOfTeamA2[1];
        byte x = locationOfTeamA2[0];
        byte y = locationOfTeamA2[1];

        if (teamA2_steps[i]==0){
            if (x < 4 && !(x == target_x && y + 1 == target_y)) teamA2_route[i][1] = y - 1;     
        }
       
        else if (teamA2_steps[i]==1){
            if(x < 16 && !(x + 1 == target_x && y == target_y)) teamA2_route[i][0] = x + 1;
        }
        else if (teamA2_steps[i]==2){
            if(x > 0 && !(x == target_x && y - 1 == target_y)) teamA2_route[i][1] = y - 1;
        }
        else if (teamA2_steps[i]==3){
            if(x > 0 && !(x - 1 == target_x && y == target_y)) teamA2_route[i][0] = x - 1;
        }
        else if (teamA2_steps[i]==4){
            if(y < 16 && y < 4 && !(x + 1 == target_x && y + 1 == target_y)) {
                teamA2_route[i][0] = x + 1;
                teamA2_route[i][1] = y + 1;
            }
        }
        else if (teamA2_steps[i]==5){
            if(x < 16 && y > 0 && !(x + 1 == target_x && y-  1 == target_y)) {
                teamA2_route[i][0] = x + 1;
                teamA2_route[i][1] = y - 1;
            }
        }
        else if (teamA2_steps[i]==6){
            if(x > 0 && y > 0 && !(x - 1 == target_x && y - 1 == target_y)) {
                teamA2_route[i][0] = x - 1;
                teamA2_route[i][1] = y - 1;
            }
        }
        else if (teamA2_steps[i]==7){
            if(x > 0 && y < 4 && !(x - 1 == target_x && y+1 == target_y)) {
                teamA2_route[i][0] = x - 1;
                teamA2_route[i][1] = y + 1;
            }
        }
    }
    
}

void random_player_move_B1(unsigned short numOfSteps){
    
    for(unsigned short i=0; i < numOfSteps; i++){
        teamB1_steps[i] = random_generator(8);
        
        
        teamB1_route[i][0] = locationOfTeamB1[0];
        teamB1_route[i][1] = locationOfTeamB1[1];
        byte x = locationOfTeamB1[0];
        byte y = locationOfTeamB1[1];

        if (teamB1_steps[i]==0){
            if (x < 4 && !(x == target_x && y + 1 == target_y)) teamB1_route[i][1] = y - 1;
            
        }
       
        else if (teamB1_steps[i]==1){
            if(x < 16 && !(x + 1 == target_x && y == target_y)) teamB1_route[i][0] = x + 1;
        }
        else if (teamB1_steps[i]==2){
            if(x > 0 && !(x == target_x && y - 1 == target_y)) teamB1_route[i][1] = y - 1;
        } 
        else if (teamB1_steps[i]==3){
            if(x > 0 && !(x - 1 == target_x && y == target_y)) teamB1_route[i][0] = x - 1;
        }
        else if (teamB1_steps[i]==4){
            if(y < 16 && y < 4 && !(x + 1 == target_x && y + 1 == target_y)) {
                teamB1_route[i][0] = x + 1;
                teamB1_route[i][1] = y + 1;
            }
        }
        else if (teamB1_steps[i]==5){
            if(x < 16 && y > 0 && !(x + 1 == target_x && y - 1 == target_y)) {
                teamB1_route[i][0] = x + 1;
                teamB1_route[i][1] = y - 1;
            }
        }
        else if (teamB1_steps[i]==6){
            if(x > 0 && y > 0 && !(x - 1 == target_x && y - 1 == target_y)) {
                teamB1_route[i][0] = x - 1;
                teamB1_route[i][1] = y - 1;
            }
        }
        else if (teamB1_steps[i]==7){
            if(x > 0 && y < 4 && !(x - 1 == target_x && y + 1 == target_y)) {
                teamB1_route[i][0] = x - 1;
                teamB1_route[i][1] = y + 1;
            }
        }
    }
    
}

void random_player_move_B2(unsigned short numOfSteps){
    
    for(unsigned short i=0; i < numOfSteps; i++){
        teamB2_steps[i] = random_generator(8);
        
        
        teamB2_route[i][0] = locationOfTeamB2[0];
        teamB2_route[i][1] = locationOfTeamB2[1];
        byte x = locationOfTeamB2[0];
        byte y = locationOfTeamB2[1];

        if (teamB2_steps[i]==0){
            if (x < 4 && !(x == target_x && y + 1 == target_y)) teamB2_route[i][1] = y - 1;
            
        }
       
        else if (teamB2_steps[i]==1){
            if(x < 16 && !(x + 1 == target_x && y == target_y)) teamB2_route[i][0] = x + 1;
        }
        else if (teamB2_steps[i]==2){
            if(x > 0 && !(x == target_x && y - 1 == target_y)) teamB2_route[i][1] = y - 1;
        } 
        else if (teamB2_steps[i]==3){
            if(x > 0 && !(x - 1 == target_x && y == target_y)) teamB2_route[i][0] = x - 1;
        }
        else if (teamB2_steps[i]==4){
            if(y < 16 && y < 4 && !(x + 1 == target_x && y + 1 == target_y)) {
                teamB2_route[i][0] = x + 1;
                teamB2_route[i][1] = y + 1;
            }
        }
        else if (teamB2_steps[i]==5){
            if(x < 16 && y > 0 && !(x + 1 == target_x && y - 1 == target_y)) {
                teamB2_route[i][0] = x + 1;
                teamB2_route[i][1] = y - 1;
            }
        }
        else if (teamB2_steps[i]==6){
            if(x > 0 && y > 0 && !(x - 1 == target_x && y - 1 == target_y)) {
                teamB2_route[i][0] = x - 1;
                teamB2_route[i][1] = y - 1;
            }
        }
        else if (teamB2_steps[i]==7){
            if(x > 0 && y < 4 && !(x - 1 == target_x && y + 1 == target_y)) {
                teamB2_route[i][0] = x - 1;
                teamB2_route[i][1] = y + 1;
            }
        }
    }
    
}


unsigned short random_generator(unsigned short mod) {
    
    unsigned short random_value = 0;
    unsigned short timer_value = 0;
    unsigned short shift_amount;
    timer_value = TMR2;  
    shift_amount = timer_value & 0x0F; 
    random_value = (timer_value % mod);  // calculate random value

    timer_value = (timer_value >> shift_amount) | (timer_value << (16 - shift_amount)); // shift to create randomness
    
    TMR2 = timer_value; 

    return random_value;

    
}

byte isOccupied(byte x, byte y){
    
    if((locationOfTeamA1[0]==x && locationOfTeamA1[1]==y)
            || (locationOfTeamA2[0]==x && locationOfTeamA2[1]==y)
            || (locationOfTeamB1[0]==x && locationOfTeamB1[1]==y)
            || (locationOfTeamB2[0]==x && locationOfTeamB2[1]==y)) return 1;
    else return 0;
    
}

#ifdef	__cplusplus
}
#endif

#endif	/* THE3_H */