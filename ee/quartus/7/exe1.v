module exe1(out, d3, d2,d1,d0, s1,s0);
output out;
input d3, d2,d1,d0, s1,s0;
not (not_s1,s1), (not_s0,s0);
and (out0, d0, not_s1, not_s0), (out1, d1, not_s1, s0);
and (out2, d2, s1, not_s0), (out3, d3, s1, s0);
or (out, out0, out1, out2, out3);
endmodule
