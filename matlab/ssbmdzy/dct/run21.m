importfile('IMG_2018.cr2');
%������
I=IMG_2018;
I=im2double(I);
T=dctmtx(2)	;%������άDCT�任����
a1=[16 11 ;
12 12];
for k=1:3
B(:,:,k)=blkproc(I(:,:,k),[2,2],'P1*x*P2',T,T');
end
%�����άDCT������T����ת����DCT����P1*X*P2�Ĳ��� 
mask=[1 1
1 0 ];
%��ֵ��ģ������ѹ��DCTϵ����ֻ����DCTϵ�������Ͻǵ�10��
for k=1:3
B2(:,:,k)=blkproc(B(:,:,k),[2 2],'P1.*x',mask);	%ֻ����DCT�任��10��ϵ��
end
for k=1:3
I2(:,:,k)=blkproc(B2(:,:,k),[2 2],'P1*x*P2',T',T); 
end
subplot(2,2,1) 
imshow(I)	%�ع�ͼ��
imwrite(I,'DIRECT2.jpg'); 
%imwrite(I,'DIRECT2.bmp');
title('ԭʼͼ��');
subplot(2,2,2) 
imshow(I2); 
imwrite(I2,'DCT2.jpg'); 
%imwrite(I2,'DCT2.bmp'); 
title('�ؽ�ͼ��'); 
dI=I-I2;
subplot(2,2,3) 
imshow(dI); 
title('���ͼ��');
subplot(2,2,4) 
list=dI(:);
hist(list,100)
title('���ͼ��ֱ��ͼ');