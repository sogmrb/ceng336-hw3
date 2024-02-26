Ultimate Frisbee Simulation

Description:
This repository contains the solution for an assignment in an embedded systems class focusing on LCD and A/D Converter (ADC) concepts using Picsimlab with PIC18F4620. The assignment involved simulating a miniature ultimate frisbee match involving teams, players, frisbee movements displayed on an LCD, and scoring shown on a 7-segment display.

Objective:
The objective of this assignment was to implement a simulation of an ultimate frisbee match using embedded systems concepts, including LCD display, custom character creation, player movements using a gamepad, frisbee throw and catch mechanics, and scoring updates.

Problem Definition:
The assignment required the simulation to include:
- Two teams with two players each
- Players aiming to throw or catch the frisbee to increase their team's score
- Players and frisbee movements displayed on a 16x4 LCD
- Scores displayed on a 7-segment display
- User interaction via push buttons and gamepad
- Adjustable game speed using ADC
  
Implementation:
The assignment was implemented following the general flow of the game as described in the problem definition. Key components of the implementation included:
- Initializing LCD with custom characters
- Handling player movements using a gamepad and push buttons
- Managing frisbee throw and catch mechanics
- Utilizing timer interrupts for timing-related operations
- Using ADC interrupts to adjust game speed
- Updating scores on the 7-segment display
- Implementing a pseudo-random number generator for simulation purposes

Usage:
To run the simulation:
Set up the environment using Picsimlab with PIC18F4620.
Compile and upload the provided source code to the microcontroller.
Follow the instructions provided in the code documentation to interact with the simulation using push buttons, gamepad, and ADC dial.

Credits
This assignment solution was developed by Sogol Mehrabi and Tahira Kazimi for the Introduction to Embedded Systems Development (CENG336) course.
