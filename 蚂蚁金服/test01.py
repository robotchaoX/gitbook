num = int(input())
while num > 0:
    list_1 = input().split(' ')
    list_1 = list(map(int, list_1))
    n = list_1[0]
    m = list_1[1]
    a = list_1[2]
    b = list_1[3]
    if n*b > m*a:  # 杀死所有人
        print(m)
    else if n < a:  # 杀不死一个人
        print(0)
    else:
        print(n*b//a)
    num -= 1
