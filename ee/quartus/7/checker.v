module checker(x,z,clk,reset,state);
input x,clk,reset;
output z;
output[2:0]state;
reg[2:0]state;
reg z;
parameter s0='d0,s1='d1,s2='d2,s3='d3,s4='d4;
always@(posedge clk)
         begin
         if(reset)begin state<=s0;z<=0;end
         else
         casex(state)
         s0: begin
             if(x==0) begin state<=s0;z<=0;end
             else     begin state<=s1;z<=0;end
             end
         s1: begin
                   if(x==0) begin state<=s2;z<=0;end
                   else  begin state<=s1;z<=0;end
                   end
         s2:begin
                   if(x==0) begin state<=s3;z<=0;end
                   else  begin state<=s1;z<=0;end
                   end
         s3:begin
                   if(x==0) begin state<=s0;z<=0;end
                   else  begin state<=s4;z<=1;end
                   end
         s4:begin
                   if(x==0) begin state<=s2;z<=0;end
                   else  begin state<=s1;z<=0;end
                   end
         default: state<=s0;
         endcase
         end
endmodule