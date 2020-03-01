module exe2(out, d3, d2,d1,d0, s1,s0);
output out;
input d3, d2,d1,d0, s1,s0;
assign out=((~s1)&(~s0)&d0)|((~s1)&(s0)&d1)|((s1)&(~s0)&d2)|((s1)&(s0)&d3);
endmodule
