module  counter8(out,reset,clk);
  output[7:0]  out;
  input  reset,clk;
  reg[7:0]  out;
  always @(posedge clk)
  begin
    if(reset) out<=0;   //同步复位
    else    out<=out+1; //计数
   end
endmodule
