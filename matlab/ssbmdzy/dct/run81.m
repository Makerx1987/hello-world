importfile('IMG_2018.cr2');
%������
I=IMG_2018;
I=im2double(I);
T=dctmtx(8)	;%������άDCT�任����
a1=[16 11 10 16 24 40 51 61;
12 12 14 19 26 58 60 55;
14 13 16 24 40 57 69 56;
14 17 22 29 51 87 80 62;
18 22 37 56 68 109 103 77;
24 35 55 64 81 104 113 92;
49 64 78 87 103 121 120 101;
72 92 95 98 112 100 103 99 ];
for k=1:3
B(:,:,k)=blkproc(I(:,:,k),[8,8],'P1*x*P2',T,T');
end
%�����άDCT������T����ת����DCT����P1*X*P2�Ĳ��� 
mask=[1 1 1 1 0 0 0 0
1 1 1 0 0 0 0 0
1 1 0 0 0 0 0 0
1 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 ];
%��ֵ��ģ������ѹ��DCTϵ����ֻ����DCTϵ�������Ͻǵ�10��
for k=1:3
B2(:,:,k)=blkproc(B(:,:,k),[8 8],'P1.*x',mask);	%ֻ����DCT�任��10��ϵ��
end
for k=1:3
I2(:,:,k)=blkproc(B2(:,:,k),[8 8],'P1*x*P2',T',T); 
end
subplot(2,2,1) 
imshow(I)	%�ع�ͼ��
imwrite(I,'DIRECT8.jpg'); 
imwrite(I,'DIRECT8.bmp');
title('ԭʼͼ��');
subplot(2,2,2) 
imshow(I2); 
imwrite(I2,'DCT8.jpg'); 
imwrite(I2,'DCT8.bmp'); 
title('�ؽ�ͼ��'); 
dI=I-I2;
subplot(2,2,3) 
imshow(dI); 
title('���ͼ��');
subplot(2,2,4) 
list=dI(:);
hist(list,100)
title('���ͼ��ֱ��ͼ');
