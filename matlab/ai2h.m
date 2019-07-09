function y=ai2h(user,ai,u)
y=0;
for i=1:167
    y=y+abs( u(i,user*2)-u(i,ai*2+6));
    y=y+abs( u(i,user*2+1)-u(i,ai*2+6+1));
end

