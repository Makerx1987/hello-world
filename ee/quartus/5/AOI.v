module AOI (A,B,C,D,F);  //ģ����ΪAOI(�˿��б�A��B��C��D��F)
  input A,B,C,D;		  //ģ�������˿�ΪA��B��C��D
  output F;		  //ģ�������˿�ΪF
  wire A,B,C,D,F;               	  //�����źŵ���������
    assign  F= ~((A&B)|(~(C&D)));	//�߼���������
endmodule
