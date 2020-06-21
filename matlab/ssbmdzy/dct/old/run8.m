importfile('IMG_20200527_084043.dng');
%工作区
I=IMG_20200527_084043;
I=im2double(I);
I=mat2gray(I);
T=dctmtx(8)	;%产生二维DCT变换矩阵
a1=[16 11 10 16 24 40 51 61;
12 12 14 19 26 58 60 55;
14 13 16 24 40 57 69 56;
14 17 22 29 51 87 80 62;
18 22 37 56 68 109 103 77;
24 35 55 64 81 104 113 92;
49 64 78 87 103 121 120 101;
72 92 95 98 112 100 103 99 ];
for i=1:8:434
    for j=1:8:578
        P=I(i:i+7,j:j+7);
        K=T*P*T';
        I2(i:i+7,j:j+7)=K;
        K=K./a1; %量化
        K(abs(K)<0.03)=0;
        I3(i:i+7,j:j+7)=K; 
    end
end
for i=1:8:434
    for j=1:8:578	%显示DCT变换后的频域图像
        P=I3(i:i+7,j:j+7).*a1;
        K=T'*P*T;
        I4(i:i+7,j:j+7)=K;	%反量化
    end
end
B=blkproc(I,[8,8],'P1*x*P2',T,T');
%计算二维DCT，矩阵T及其转置是DCT函数P1*X*P2的参数 
mask=[1 1 1 1 0 0 0 0
1 1 1 0 0 0 0 0
1 1 0 0 0 0 0 0
1 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 ];
%二值掩模，用来压缩DCT系数，只留下DCT系数中左上角的10个
B2=blkproc(B,[8 8],'P1.*x',mask);	%只保留DCT变换的10个系数
I2=blkproc(B2,[8 8],'P1*x*P2',T',T); 
subplot(2,2,1) 
imshow(I)	%重构图像
imwrite(I,'gray.jpg'); 
title('原始图像');
subplot(2,2,2) 
imshow(I2); 
imwrite(I2,'gray_DCT.jpg'); 
title('重建图像'); 
dI=I-I2;
subplot(2,2,3) 
imshow(dI); 
title('误差图像');
subplot(2,2,4) 
list=dI(:);
hist(list,40)
title('误差图像直方图');
