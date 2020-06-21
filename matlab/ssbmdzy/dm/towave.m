N=16;
fs=8000;
[y,fs]=audioread('test.mp3'); 
y=y(:,1);
audiowrite('test.m4a',y,fs);
subplot(2,2,1); plot(y); 
xlabel('时间t'); ylabel('幅值');
title('原始语音采样后的信号波形'); 
Y=fft(y,2^N); 
Y0(2^N/2+1:2^N)=Y(1:2^N/2);
Y0(1:2^N/2)=Y(2^N/2)/2^N;
ff=fs*(-(2^N/2-1):2^N/2)/2^N; 
subplot(2,2,3);
plot(ff,abs(Y0));
xlabel('频率Hz');
ylabel('幅值');
title('信号原始频率');
% sound(y,Fs);
%适配区
Ts=1/fs; %采样间隔,8KHz
t=0:Ts:161903*Ts; %采样时间序列点数1721714
x=y'; %信号
delta=0.008; %量化阶距
M=[1 1 1 1];
D(1+length(t))=0; %预测器初始状态
for k=1:length(t)
    e(k)=x(k)-D(k); %误差信号 
    e_q(k)=delta*(2*(e(k)>=0)-1); %量化器输出，大于0，delta*1，小于0，delta*-1
    D(k+1)=e_q(k)+D(k); %延迟器状态更新 
    codeout(k)=(e_q(k)>0); %编码输出，大于0为1，小于0为-1
    if k>2 %cfdm核心代码
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
% title('原信号及其离散值');
hold on; 
% subplot(3,1,2);
% stairs(t,codeout);
% axis([0 20*Ts,-2 2]); %解码端 
Dr(1+length(t))=0; %解码端预测器初始状态
for k=1:length(t)
    if k>2 %cfdm核心代码
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
    eq(k)=delta*(2*codeout(k)-1); %解码
    xr(k)=eq(k)+Dr(k); 
    Dr(k+1)=xr(k); %延迟器状态更新
end
subplot(2,2,2);
plot(xr);
hold on; %解码输出
% subplot(2,2,2);
% plot(t,x); %原信号
title('自适应增量调制编解码后波形');
xlabel('时间t'); ylabel('幅值');
X=fft(x,2^N); 
X0(2^N/2+1:2^N)=X(1:2^N/2);
X0(1:2^N/2)=X(2^N/2)/2^N;
ff=fs*(-(2^N/2-1):2^N/2)/2^N; 
subplot(2,2,4);
plot(ff,abs(X0));
xlabel('频率Hz');
ylabel('幅值');
title('输出信号频率');
audiowrite('out.m4a',xr,fs);
