function y=ai2ai(ai2,ai,u)
y=0;
for i=1:167
    y=y+abs( u(i,ai2*2+6)-u(i,ai*2+6));
    y=y+abs( u(i,ai2*2+6+1)-u(i,ai*2+6+1));
end