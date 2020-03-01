module counter(out,data,load,reset,clk);
parameter n=939;
output[n-1:0] out;
input[n-1:0] data;
input load,clk,reset;
reg[n-1:0] out;
always @(posedge clk or negedge reset)           //clk�����ش���
      begin
        if(!reset)  	out=0;    //ͬ����0���͵�ƽ��Ч
        else  if(!load) out=data;	  //ͬ��Ԥ��
        else	 	out=out+1;	  //����
     end
endmodule
