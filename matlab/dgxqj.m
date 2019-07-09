mtlb=csvread(file);
x=mtlb(:,1);
y=mtlb(:,2);
z=mtlb(:,3);
[X,Y,Z]=griddata(x,y,z,linspace(1,10)',linspace(1,10),'v4');
pcolor(X,Y,Z);shading interp;
figure,contourf(X,Y,Z);