# def DToR(m,r):
#     t=''
#     while m!=0 and r!=0:
#         c=m % r    #求模
#         if (c>9):
#             t=chr(c-10+65)+t
#         else:
#             t=str(c)+t
#             m = m // r   #整除
#     return t

# while True:
#     ipt=input("请输入十进制整数('q' 退出程序):\n")
#     if ipt=='q':
#         break
#     ipt=int(ipt)
#     r=int(input("请输入欲转换进制（如2，8，16等）:\n"))
#     rst=DToR(ipt,r)
#     print('将%s转换为%s进制的结果为：%s' %(ipt,r,rst))
boy = [1.69, 1.72, 1.78, 1.83, 1.89]
girl = [1.61, 1.64, 1.65, 1.72]
i = j = 0
print('男队身高：', end='')
for b in boy:
    print(b, end=' ')
print('\n女队身高：', end='')
for g in girl:
    print(g, end=' ')
print('\n合并后：', end='')
while i < len(boy) and j < len(girl):
    if boy[i] < girl[j]:
        print(boy[i], '(男)', sep='', end = ' ')
        i += 1
    else:
        print(girl[j], '(女)', sep='', end = ' ')
        j += 1
while i < len(boy):
    print(boy[i], '(男)', sep='', end = ' ')
    i += 1
while j < len(girl):
    print(girl[j], '(女)', sep='', end = ' ')
    j = j+1










