function y=h2h(user,user2,u)
y=0;
for i=1:167
    y=y+abs( u(i,user*2)-u(i,user2*2));
    y=y+abs( u(i,user*2+1)-u(i,user2*2+1));
end