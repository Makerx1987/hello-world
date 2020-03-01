module adder8(cout,sum,ina,inb,cin);
  output[7:0] sum;
  output cout;
  input[7:0] ina,inb;
  input cin;
  assign {cout,sum}=ina+inb+cin;
endmodule