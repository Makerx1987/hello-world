Ts=1e-3; %�������,1KHz
t=0:Ts:20*Ts; %����ʱ�����е���20
x=sin(2*pi*50*t)+0.5*sin(2*pi*150*t); %�ź�
delta=0.4; %�����׾�
M=[0.4 0.9 1.5 2];
D(1+length(t))=0; %Ԥ������ʼ״̬
for k=1:length(t)
    e(k)=x(k)-D(k); %����ź� 
    e_q(k)=delta*(2*(e(k)>=0)-1); %���������������0��delta*1��С��0��delta*-1
    D(k+1)=e_q(k)+D(k); %�ӳ���״̬���� 
    codeout(k)=(e_q(k)>0); %�������������0Ϊ1��С��0Ϊ-1
    if k>2 %cfdm���Ĵ���
        if codeout(k)~=codeout(k-1)&& codeout(k-1)==codeout(k-2)
            delta=delta*M(1);
        elseif codeout(k)~=codeout(k-1)&& codeout(k-1)~=codeout(k-2)
            delta=delta*M(2);
        elseif codeout(k)==codeout(k-1)&& codeout(k-1)~=codeout(k-2)
            delta=delta*M(3);
        elseif codeout(k)==codeout(k-1)&& codeout(k-1)==codeout(k-2) 
            delta=delta*M(4);
        end
    end  
end
subplot(3,1,1);
plot(t,x,'-o');
axis([0 20*Ts,-2 2]);
title('ԭ�źż�����ɢֵ');
hold on; 
subplot(3,1,2);
stairs(t,codeout);
axis([0 20*Ts,-2 2]); %����� 
Dr(1+length(t))=0; %�����Ԥ������ʼ״̬
for k=1:length(t)
    if k>2 %cfdm���Ĵ���
        if codeout(k)~=codeout(k-1)&& codeout(k-1)==codeout(k-2)
            delta=delta*M(1);
        elseif codeout(k)~=codeout(k-1)&& codeout(k-1)~=codeout(k-2)
            delta=delta*M(2);
        elseif codeout(k)==codeout(k-1)&& codeout(k-1)~=codeout(k-2)
            delta=delta*M(3);
        elseif codeout(k)==codeout(k-1)&& codeout(k-1)==codeout(k-2) 
            delta=delta*M(4);
        end
    end     
    eq(k)=delta*(2*codeout(k)-1); %����
    xr(k)=eq(k)+Dr(k); 
    Dr(k+1)=xr(k); %�ӳ���״̬����
end
title('�����������������ֵ');
subplot(3,1,3);
stairs(t,xr);
hold on; %�������
subplot(3,1,3);
plot(t,x); %ԭ�ź�
title('�����ź���ԭ�źŶԱ�');