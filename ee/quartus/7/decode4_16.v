module  decode4_16(decodeout,indec,E1,E2);
output[15:0]  decodeout;
input[3:0]  indec;
input E1;
input E2;
reg[15:0]  decodeout;
always @(indec)
    begin
    if(E1 && !E2)
      case(indec)        			//”√case”Ôæ‰Ω¯––“Î¬Î
        4'd0:decodeout= 16'b1111111111111110;
        4'd1:decodeout= 16'b1111111111111101;
        4'd2:decodeout= 16'b1111111111111011;
        4'd3:decodeout= 16'b1111111111110111;
        4'd4:decodeout= 16'b1111111111101111;
        4'd5:decodeout= 16'b1111111111011111;
        4'd6:decodeout= 16'b1111111110111111;
        4'd7:decodeout= 16'b1111111101111111;
        4'd8:decodeout= 16'b1111111011111111; 
        4'd9:decodeout= 16'b1111110111111111;
        4'd10:decodeout=16'b1111101111111111;
        4'd11:decodeout=16'b1111011111111111;
        4'd12:decodeout=16'b1110111111111111;
        4'd13:decodeout=16'b1101111111111111;
        4'd14:decodeout=16'b1011111111111111;
        4'd15:decodeout=16'b0111111111111111;
        default: decodeout=16'b1111111111111111;
      endcase
    end
endmodule