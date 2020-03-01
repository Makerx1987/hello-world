include<add8>;
include<reg8>;
module acc(accout,cout,accin,cin,clk,clear);
output[7:0] accout;
output cout;
input[7:0] accin;
input cin,clk,clear;
wire[7:0] sum;
add8 accadd8(sum,cout,accout,accin,cin);	 	//调用add8子模块
reg8 accreg8(accout,sum,clk,clear);		   //调用reg8子模块
endmodule
