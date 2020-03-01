module AOI (A,B,C,D,F);  //模块名为AOI(端口列表A，B，C，D，F)
  input A,B,C,D;		  //模块的输入端口为A，B，C，D
  output F;		  //模块的输出端口为F
  wire A,B,C,D,F;               	  //定义信号的数据类型
    assign  F= ~((A&B)|(~(C&D)));	//逻辑功能描述
endmodule
