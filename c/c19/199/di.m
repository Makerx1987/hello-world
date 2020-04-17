function integral=di(x,y,x0)
%xl=length(x);
%yl=length(y);
integral=0;
for i=2:x0
    integral=integral+y(i-1)*(x(i)-x(i-1));
end
