module mulplus2(sum,a0,a1,a2,a3);
output[9:0] sum;
input[7:0] a0,a1,a2,a3;
reg[9:0] sum;
always @(a0 or a1 or a2)           
begin
sum=((a0>>2+a1>>1)+a2)+a3<<1;
end  
endmodule
