importfile('IMG_20200527_084043.dng');
%������
I=IMG_20200527_084043;
I=im2double(I);
I=mat2gray(I);
T=dctmtx(2)	;%������άDCT�任����
a1=[16 11 ;
12 12];
for i=1:2:1736
    for j=1:2:2312
        P=I(i:i+1,j:j+1);
        K=T*P*T';
        I2(i:i+1,j:j+1)=K;
        K=K./a1; %����
        K(abs(K)<0.03)=0;
        I3(i:i+1,j:j+1)=K; 
    end
end
for i=1:2:1736
    for j=1:2:2312	%��ʾDCT�任���Ƶ��ͼ��
        P=I3(i:i+1,j:j+1).*a1;
        K=T'*P*T;
        I4(i:i+1,j:j+1)=K;	%������
    end
end
B=blkproc(I,[2,2],'P1*x*P2',T,T');
%�����άDCT������T����ת����DCT����P1*X*P2�Ĳ��� 
mask=[1 1
1 0 ];
%��ֵ��ģ������ѹ��DCTϵ����ֻ����DCTϵ�������Ͻǵ�10��
B2=blkproc(B,[2 2],'P1.*x',mask);	%ֻ����DCT�任��10��ϵ��
I2=blkproc(B2,[2 2],'P1*x*P2',T',T); 
subplot(2,2,1) 
imshow(I)	%�ع�ͼ��
imwrite(I,'gray.jpg'); 
title('ԭʼͼ��');
subplot(2,2,2) 
imshow(I2); 
imwrite(I2,'gray_DCT.jpg'); 
title('�ؽ�ͼ��'); 
dI=I-I2;
subplot(2,2,3) 
imshow(dI); 
title('���ͼ��');
subplot(2,2,4) 
list=dI(:);
hist(list,40)
title('���ͼ��ֱ��ͼ');
