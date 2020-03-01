module moveregister(clk, in, dout,din,LR,clr,load);
 
input clk,in,LR,clr,load;
parameter n=39-1;
input [n:0] din;
output [n:0] dout;
reg [n:0] dout;
 
always@(posedge clk or negedge clr)
begin
	if(!clr)dout=0;
	else if(!load)dout=din;
	else if(!LR)dout = {in, din[n:1]};
	else dout={din[n-1:0],in};
end
 
endmodule
