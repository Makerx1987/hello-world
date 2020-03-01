module mux821(out, data1,data2,n,s,E);
output out;
input[7:0] data1;
input[7:0] data2;
input[2:0] n;
input s,E;
assign out=E&(((~s)&data1[n])|((s)&data2[n]));
endmodule