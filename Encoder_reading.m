%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% This program run the motor upwards and downwards with the help of two functions: cw, and ccw. 
% These two functions change the direction of the motor clockwise and counter-clockwise.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear all
close all
clc

bbb = beaglebone; % This line creates the connection between the BBB and MATLAB.

P14 = 'P9_14';
P21 = 'P9_21';
P12 = 'P9_12';

enablePWM(bbb, P14); % enabling pin 14 to produce a pwm signal
writePWMDutyCycle(bbb, P14, 1); % set the duty cycle of the signal range 0 (0%) to 1 (100%)
writePWMFrequency(bbb, P14, 4500); % sets the frequency of the signal.
writePWMVoltage(bbb, P14, 3); % voltage that produce the pwm signal (implicit duty cycle)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% setting pin 21 and 12 to change direction of the motor. 
configureDigitalPin(bbb,P21,'output'); 
configureDigitalPin(bbb,P12,'output');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

counter = 0;

while(1)
   
    
    ccw(bbb,P21,P12);
   counter = counter + 1;
   if (counter == 10)
   % shutting down the motor after the counter reach its limit. 
       writePWMVoltage(bbb, P14, 0);
       writeDigitalPin(bbb,'P9_21',0);
       writeDigitalPin(bbb,'P9_12',0);
       writePWMDutyCycle(bbb, P14, 0);
       
       break;
   end

cw(bbb,P21,P12);

disp(counter)
end
