module mul4x4x(a,b,y); 
output [7:0] y; 
input [3:0] a,b; 
reg reset;
wire [11:0] s,co; 
reg [15:0] c;
reg [7:0] y;
always @ (a or b)
begin 
reset=(a[3]&a[2])|(a[3]&a[1])|(b[3]&b[2])|(b[3]&b[1]);
c[0]=a[0]&b[0]; 
c[1]=a[1]&b[0]; 
c[2]=a[2]&b[0]; 
c[3]=a[3]&b[0]; 
c[4]=a[0]&b[1]; 
c[5]=a[1]&b[1]; 
c[6]=a[2]&b[1]; 
c[7]=a[3]&b[1]; 
c[8]=a[0]&b[2]; 
c[9]=a[1]&b[2]; 
c[10]=a[2]&b[2]; 
c[11]=a[3]&b[2]; 
c[12]=a[0]&b[3]; 
c[13]=a[1]&b[3]; 
c[14]=a[2]&b[3]; 
c[15]=a[3]&b[3];
end 
fulladder add0(s[0],co[0],c[1],c[4],1'b0); 
fulladder add1(s[1],co[1],c[2],c[5],1'b0); 
fulladder add2(s[2],co[2],c[3],c[6],1'b0); 
fulladder add3(s[3],co[3],c[8],s[1],co[0]); 
fulladder add4(s[4],co[4],c[9],s[2],co[1]); 
fulladder add5(s[5],co[5],c[10],c[7],co[2]); 
fulladder add6(s[6],co[6],c[12],s[4],co[3]); 
fulladder add7(s[7],co[7],c[13],s[5],co[4]); 
fulladder add8(s[8],co[8],c[14],c[11],co[5]); 
fulladder add9(s[9],co[9],s[7],co[6],1'b0); 
fulladder add10(s[10],co[10],s[8],co[7],co[9]); 
fulladder add11(s[11],co[11],c[15],co[8],co[10]); 
always @ (a or b)
begin 
y[0]=~reset&c[0]; 
y[1]=~reset&s[0]; 
y[2]=~reset&s[3]; 
y[3]=~reset&s[6]; 
y[4]=~reset&s[9]; 
y[5]=~reset&s[10]; 
y[6]=~reset&s[11]; 
y[7]=~reset&co[11]; 
end
endmodule 
