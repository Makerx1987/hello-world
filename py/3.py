# # # myStr='Hello everyone!'
# # # print(myStr[:-9]*2)
# # st='ABCDE'   #所有选项字母
# # while True:
# #     s=input("请输入字符串(输入 '0' for 退出):\n")  #2.7版此句用raw_input
# #     if s=='0':
# #         break
# #     s=s.upper()  #转大写
# #     result=[]
# #     total=len(s)      #答题人数
# #     for i in st:   #遍历各选项字母
# #         c=0
# #         for j in s:
# #             if i==j:
# #                 c+=1
# #         result.append([i,c])
# #     print('有%d人答了本题'%(total))
# #     for k in result:
# #         print('选项%s出现的次数是：%i,' %(k[0],k[1]),end='')
# #         #######
# #         #[注]2.7版为：print(u'选项%s出现的次数是：%i,' %(k[0],_____(4)_____)),
# #         #######
# #         print('选择率是：%.2f %%' %(k[1]*100.0/total))
# import random
# #根据剩余金额rest分配第k个红包的金额
# def redEnv(k,rest):
#     m=random.random()*rest*(k+1)/num
#     return m

# total=float(input("请输入红包金额："))
# num=int(input("请输入红包个数："))
# remain=total
# #逐个红包分配金额
# for i in range(num-1):
#     money=redEnv(i,remain)
#     remain-=money
#     print("红包%d：%.2f"%(i+1,money))
# #分配最后一个红包金额
# print("红包%d：%.2f"%(num,remain))
while True:
    s=input("请输入8位数字学号(输入 '0' 退出程序):\n")
    #2.7版上句改用raw_input
    if s=='0':
        break    
    if not s.isdigit() or len(s)!=8:
        print('输入错误!!!\n')
        #若所输入的学号非数字或不是8位，打印提示后，进入下次循环

    #此处用if语句对所取字符串前2位进行判断，是否在16以内
    elif int(s[:2]) < 16:
        print ('学号 %s 应是 %s 年级学生\n' %(s,"20"+s[:2]))
        #2.7版为print u'学号 %s 应是 %s年级学生\n' %(s,"20"+s[:2])
    else:
        print ('学号 %s 应是 %s 年级学生\n' %(s,"19"+s[:2]))


