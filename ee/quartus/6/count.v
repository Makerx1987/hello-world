module count(out,data,load,reset,clk);
parameter n=9;
output[n-1:0] out;
input[n-1:0] data;
input load,clk,reset;
reg[n-1:0] out;
always @(posedge clk or negedge reset)           //clk上升沿触发,reset升沿触发
      begin
        if(!reset)  	out=0;    //同步清0，低电平有效
        else  if(load) out=data;	  //同步预置
        else	 	out=out+1;	  //计数
     end
endmodule
