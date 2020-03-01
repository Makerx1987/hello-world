module adderx(cout,sum,ina,inb,cin);
  parameter x=9;
  output[x-1:0] sum;
  output cout;
  input[x-1:0] ina,inb;
  input cin;
  assign {cout,sum}=ina+inb+cin;
endmodule