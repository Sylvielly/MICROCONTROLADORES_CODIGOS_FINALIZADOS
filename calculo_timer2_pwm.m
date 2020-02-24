F_clock = 20000000;
PRE = 4;
POS = 1;
PR2 = 249

TMR2 = (4*PRE*POS*(PR2+1))/F_clock
F_tmr2 = 1/TMR2
