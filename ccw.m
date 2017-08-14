function []=ccw(bbb,P1,P2)
writeDigitalPin(bbb,P1,0);
writeDigitalPin(bbb,P2,1);
pause(0.15); % change time depending on motor setup.
writeDigitalPin(bbb,P2,0);
end
