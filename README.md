# JuRP
The MATLAB scripts establish a communication between the BBB and MATLAB. The BBB sends the PWM signal to run the motor through the Escon 50/5 driver controller. 

The Simulink model establish a communication to the Arduino Mega. The Simulink sketch needs the Arduino I/O library in order to work. The instruction of installation are included in a readme file in the Arduino I/O folder. 

The Arduino code is there only for reference or in case that some changes are necessary in the future. The Simulink model handles all instructions regarding the Arduino Mega. 

In addition, I tested the robotic system running the MATLAB and the Simulink mnodel at the same time. 
