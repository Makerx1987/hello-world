# # #!/usr/bin/python
# # # -*- coding: UTF-8 -*-
 
# # import tkinter
# # top = tkinter.Tk()
# # # 进入消息循环
# # top.mainloop()
# #!/usr/bin/python
# # -*- coding: UTF-8 -*-
 
# from tkinter import *           # 导入 Tkinter 库
# root = Tk()                     # 创建窗口对象的背景色
#                                 # 创建两个列表
# li     = ['C','python','php','html','SQL','java']
# movie  = ['CSS','jQuery','Bootstrap']
# listb  = Listbox(root)          #  创建两个列表组件
# listb2 = Listbox(root)
# for item in li:                 # 第一个小部件插入数据
#     listb.insert(0,item)
 
# for item in movie:              # 第二个小部件插入数据
#     listb2.insert(0,item)
 
# listb.pack()                    # 将小部件放置到主窗口中
# listb2.pack()
# root.mainloop()                 # 进入消息循环
# import random
# envSum=float(input("请输入红包金额："))
# envNum=int(input("请输入红包个数："))
# cash=[]
# rest=envSum
# avg=envSum/envNum
# #分配前envNum-1个红包的金额
# for i in range(envNum-1):
#     cash.append(avg+(random.random()-0.5)*avg)
#     print("红包%d：%.2f"%(i,cash[i]))
#     rest -= cash[i]
# #分配最后一个红包金额
# cash.append(rest)
# print("红包%d：%.2f"%(envNum,cash[envNum - 1]))
# def judge(passwd):
#     n_digit=n_letter=0
#     if len(passwd)<8:
#         return False
#     for i in range(len(passwd)):
#         if '0'<=passwd[i]<='9':
#             n_digit= n_digit+1
#         elif 'A'<=passwd[i].upper()<='Z':
#             n_letter+=1
#     if n_digit>0 and n_letter>0:
#         return True
#     else:
#         return False
    
# while True:
#     st=input("请输入测试密码(直接回车为退出程序):\n") #2.7版用raw_input
#     if st=='':
#         break
#     if judge(st):
#         print("%s: 密码强度合格.\n"%st)
#         #2.7版为print u"%s: 密码强度合格.\n"%st
#     else:
#         print("%s: 弱密码.\n"%st)
#         #2.7版为print u"%s: 弱密码.\n"%st
# dic={1:'本科生',2:'硕士生',3:'博士生'}
# while True:
#     s=input("请输入8位数学号(输入 '0' 退出程序):\n") #2.7版请改用raw_input
#     if s=='0':
#         break
#     if not s.isdigit() or len(s)!=8:
#         print('输入错误!!!\n')
#         #若所输入的学号非数字或不是8位，前句打印提示后，此处跳出本次循环进入下次循环
#         continue
#     #用if语句实现若所输入的学号第3位是1、2或3，则打印字典相应学生类型
#     elif int(s[2]) in (1,2,3):	
#         print ('学号 %s 应是 %s\n' %(s,dic[int(s[2])])) 	
#     else:
#         #按“编号 xxxxxxxx 可能是其他人员”格式化输出
# 	    print ('学号 %s 可能是其他人员' %(s))
# while True:
#     n=int(input("请输入1-9之间的整数(输入 '0' 退出程序):\n"))
#     if n==0:
#         break
#     #此处对sum、t和 sign 变量进行初始化，注意符号,t为多项式中的一个无符号项
#     sum=t=0
#     sign=-1
#     for i in range(1,n+1):
#         #此处按通式计算t和sum
#         t=2*i/((2*i+1)*(2*i-1))*sign
#         sum+=t
#         sign = -sign     #隔项改变符号
#     print ("该多项式前 %i 项之和为 %.5f\n"%(n,sum))
# while True:
#     i=int(input("请输入1-10之间的整数(输入 '0' 退出程序):\n"))
#     if i==0:
#         break
#     elif i>10:
#         continue
#     for j in range(1,i+1):
#         #打印10-j个空格，不换行
#         print(" "*(10-j),end="")
#         #打印j*2-1个字母，提示chr(65)为A
#         print(chr(64+j)*(j*2-1))

#     print()  #2.7版会多显示一个括号，不影响结果
#     #此句为下次输入提示另起一行用，不在for循环内
# from tkinter import *

# def y():
#     a = v1.get()
#     b = v2.get()
#     c = price[a] * b
#     text.set('住%s %d天，住宿费%.1f元'%(content[a],b,c))

# content = ['海景房', '花园房', '行政房']
# price = [500, 480, 380]
# root = Tk()
# root.title('酒店客房计费')
# root.geometry('230x200')

# Label(root, text = '请选择房型：').pack(side = TOP)

# v1 = IntVar()
# v1.set(0)
# for i in range(3):
#     Radiobutton(root, text = content[i], variable = v1, value = i).pack(side = TOP)

# Label(root, text = '请输入入住天数：').pack(side = TOP)

# v2 = IntVar()
# v2.set('')

# Entry(root, textvariable = v2).pack(side = TOP)

# Button(root, text = '计算', command = y).pack(side = TOP)

# text = StringVar()
# text.set('')
# Label(root, textvariable = text).pack(side = TOP)

# root.mainloop()
from tkinter import *
from math import *
root=Tk()
root.geometry('600x600')
cv=Canvas(root,width=600,height=600)
cv.create_line(0,300,600,300,fill="red") # -
cv.create_line(300,0,300,600,fill='green') # |
x0=300.0
y0=300.0
for m in range(0,20*360):
    m=m/360    
    x=(25.0+40.0)*cos(pi*m)+40.0*cos((25.0/40+1)*pi*m)+300
    y=(25.0+40.0)*sin(pi*m)-40.0*sin((25.0/40+1)*pi*m)+300    
    cv.create_line(x0,y0,x,y,fill="blue")
    x0=x
    y0=y
cv.pack()
root.mainloop()
