module  mux4_1(out,in,sel);
parameter n=6;
output  out;
input[n-1:0]  in;
input[2:0]  sel;
reg  out;
always @(in or sel)  //敏感信号列表
out=in[sel];
endmodule
