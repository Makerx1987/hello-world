module  mux4_1(out,in,sel);
parameter n=6;
output  out;
input[n-1:0]  in;
input[2:0]  sel;
reg  out;
always @(in or sel)  //�����ź��б�
out=in[sel];
endmodule
