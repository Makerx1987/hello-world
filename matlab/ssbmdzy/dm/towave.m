N=16;
fs=8000;
[y,fs]=audioread('test.mp3'); 
y=y(:,1);
audiowrite('test.m4a',y,fs);
subplot(2,2,1); plot(y); 
xlabel('ʱ��t'); ylabel('��ֵ');
title('ԭʼ������������źŲ���'); 
Y=fft(y,2^N); 
Y0(2^N/2+1:2^N)=Y(1:2^N/2);
Y0(1:2^N/2)=Y(2^N/2)/2^N;
ff=fs*(-(2^N/2-1):2^N/2)/2^N; 
subplot(2,2,3);
plot(ff,abs(Y0));
xlabel('Ƶ��Hz');
ylabel('��ֵ');
title('�ź�ԭʼƵ��');
% sound(y,Fs);
%������
Ts=1/fs; %�������,8KHz
t=0:Ts:161903*Ts; %����ʱ�����е���1721714
x=y'; %�ź�
delta=0.008; %�����׾�
M=[1 1 1 1];
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
% subplot(3,1,1);
% plot(t,x,'-o');
% axis([0 20*Ts,-2 2]);
% title('ԭ�źż�����ɢֵ');
hold on; 
% subplot(3,1,2);
% stairs(t,codeout);
% axis([0 20*Ts,-2 2]); %����� 
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
subplot(2,2,2);
plot(xr);
hold on; %�������
% subplot(2,2,2);
% plot(t,x); %ԭ�ź�
title('����Ӧ�������Ʊ�������');
xlabel('ʱ��t'); ylabel('��ֵ');
X=fft(x,2^N); 
X0(2^N/2+1:2^N)=X(1:2^N/2);
X0(1:2^N/2)=X(2^N/2)/2^N;
ff=fs*(-(2^N/2-1):2^N/2)/2^N; 
subplot(2,2,4);
plot(ff,abs(X0));
xlabel('Ƶ��Hz');
ylabel('��ֵ');
title('����ź�Ƶ��');
audiowrite('out.m4a',xr,fs);
