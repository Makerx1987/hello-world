importfile('IMG_2018.cr2');
%工作区
I=IMG_2018;
I=im2double(I);
T=dctmtx(2)	;%产生二维DCT变换矩阵
a1=[16 11 ;
12 12];
for k=1:3
B(:,:,k)=blkproc(I(:,:,k),[2,2],'P1*x*P2',T,T');
end
%计算二维DCT，矩阵T及其转置是DCT函数P1*X*P2的参数 
mask=[1 1
1 0 ];
%二值掩模，用来压缩DCT系数，只留下DCT系数中左上角的10个
for k=1:3
B2(:,:,k)=blkproc(B(:,:,k),[2 2],'P1.*x',mask);	%只保留DCT变换的10个系数
end
for k=1:3
I2(:,:,k)=blkproc(B2(:,:,k),[2 2],'P1*x*P2',T',T); 
end
subplot(2,2,1) 
imshow(I)	%重构图像
imwrite(I,'DIRECT2.jpg'); 
%imwrite(I,'DIRECT2.bmp');
title('原始图像');
subplot(2,2,2) 
imshow(I2); 
imwrite(I2,'DCT2.jpg'); 
%imwrite(I2,'DCT2.bmp'); 
title('重建图像'); 
dI=I-I2;
subplot(2,2,3) 
imshow(dI); 
title('误差图像');
subplot(2,2,4) 
list=dI(:);
hist(list,100)
title('误差图像直方图');