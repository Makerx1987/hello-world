importfile('IMG_2018.cr2');
%工作区
I=IMG_2018;
I=im2double(I);
T=dctmtx(4)	;%产生二维DCT变换矩阵
a1=[16 11 10 16 ;
12 12 14 19 ;
14 13 16 24;
14 17 22 29;
];
for k=1:3
B(:,:,k)=blkproc(I(:,:,k),[4,4],'P1*x*P2',T,T');
end
%计算二维DCT，矩阵T及其转置是DCT函数P1*X*P2的参数 
mask=[1 1 1 1 
1 1 1 0 
1 1 0 0
1 0 0 0 ];
%二值掩模，用来压缩DCT系数，只留下DCT系数中左上角的10个
for k=1:3
B2(:,:,k)=blkproc(B(:,:,k),[4 4],'P1.*x',mask);	%只保留DCT变换的10个系数
end
for k=1:3
I2(:,:,k)=blkproc(B2(:,:,k),[4 4],'P1*x*P2',T',T); 
end
subplot(2,2,1) 
imshow(I)	%重构图像
imwrite(I,'DIRECT4.jpg'); 
%imwrite(I,'DIRECT4.bmp'); 
title('原始图像');
subplot(2,2,2) 
imshow(I2); 
imwrite(I2,'DCT4.jpg'); 
%imwrite(I2,'DCT4.bmp'); 
title('重建图像'); 
dI=I-I2;
subplot(2,2,3) 
imshow(dI); 
title('误差图像');
subplot(2,2,4) 
list=dI(:);
hist(list,100)
title('误差图像直方图');