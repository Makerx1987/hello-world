module  counterx(out,reset,clk);
  parameter x=16;
  output[x-1:0]  out;
  input  reset,clk;
  reg[x-1:0]  out;
  always @(posedge clk)
  begin
    if(reset) out<=0;   //ͬ����λ
    else    out<=out+1; //����
   end
endmodule
