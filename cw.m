function []=cw(bbb,P1,P2)
writeDigitalPin(bbb,P2,0);
writeDigitalPin(bbb,P1,1);
pause(0.15); % change time depending on motor setup. 
writeDigitalPin(bbb,P1,0);
end
