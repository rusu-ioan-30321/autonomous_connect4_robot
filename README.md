# Autonomous Connect4 Robot – UR10e (Webots Simulation)

## Project Overview
This project simulates an industrial robotic arm (UR10e) capable of autonomously playing the game Connect4. 
The system integrates game logic, robotic motion control, and custom-designed game components with Fusion 360.

## System Architecture
The project combines:

- Game decision algorithm (C language)
- Robotic arm control (UR10e manipulator)
- Webots simulation environment
- Custom 3D game components designed in Fusion360

The robot evaluates the board state, selects the next move based on the implemented algorithm, and executes the move by placing the game piece in the correct column.

## Robot Motion Strategy
The robot executes moves using predefined joint configurations corresponding to each board column.  
Each configuration ensures consistent and accurate placement of the game pieces.

This approach was chosen to ensure reliability and simplify motion control at the project stage.

## Components
- UR10e robotic manipulator (simulated)
- Game pieces (Fusion360 design)
- Webots world configuration file
- C-based controller

## Technologies Used
- C programming language
- Webots Robotics Simulator
- Fusion360 (CAD design)
- Industrial robot kinematic structure (UR10e)

## Team Contributions
This project was developed in a 2-person team.

- My contribution:
  - Defined robot motion logic using predefined joint positions (the project was p=done in the first year, and I was new to the field)
  - Integrated game logic with robot control
  - Designed mechanical components in Fusion360


- @Rares793 contribution:
  - Implemented the Connect4 decision-making algorithm in C
  - Designed mechanical components in Fusion360

## Key Learning Outcomes
- Integration of software logic with robotic motion control
- Simulation of industrial robotic systems
- Implementation of decision-making algorithms
- Basic robotic motion planning strategies
- Team-based engineering project development
