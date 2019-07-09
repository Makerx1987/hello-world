function y=inter167(u1t1,u1x1) 
y=zeros(1,167);
for i=1:length(u1t1)-1
    m=1;
    j=floor(u1t1(i)/30);
    if j>=166
        return;
    end
    k=floor(u1t1(i+m)/30);
    while k<=j+1
        m=m+1;
        if i+m>=length(u1t1)
            return ;
        end
        k=floor(u1t1(i+m)/30);
    end
    y(k)=(u1x1(i+m)-u1x1(i))/(u1t1(i+m)-u1t1(i))*(k*30-u1t1(i))+u1x1(i);
    if(k==j+2)
        y(k-1)=(u1x1(i+m)-u1x1(i))/(u1t1(i+m)-u1t1(i))*(k*30-u1t1(i)-30)+u1x1(i);
    end
end
y=y';
 