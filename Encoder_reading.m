clear all
close all
clc

bbb = beaglebone;

P14 = 'P9_14';
P21 = 'P9_21';
P12 = 'P9_12';

enablePWM(bbb, P14);
writePWMDutyCycle(bbb, P14, 1);
writePWMFrequency(bbb, P14, 4500);
writePWMVoltage(bbb, P14, 3);

configureDigitalPin(bbb,P21,'output');
configureDigitalPin(bbb,P12,'output');
% rotaryEncoder(bbb,PA,PB)

counter = 0;

while(1)
   
    
    ccw(bbb,P21,P12);
   counter = counter + 1;
   if (counter == 10)
       writePWMVoltage(bbb, P14, 0);
       writeDigitalPin(bbb,'P9_21',0);
       writeDigitalPin(bbb,'P9_12',0);
       writePWMDutyCycle(bbb, P14, 0);
       
       break;
   end

cw(bbb,P21,P12);

disp(counter)
end