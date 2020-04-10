num = int(input())
while num > 0:
    list_1 = input().split(" ")
    list_1 = list(map(int, list_1))
    num -= 1
    n = list_1[0]
    k = list_1[1]
    A = [[0 for _ in range(n)] for _ in range(n)]
    n1 = n
    while n > 0:
        list_2 = input().split(" ")
        A[list_1[0]-n][:] = list(map(int, list_2))
        n -= 1

    direction = [[(0, _+1), (_+1, 0), (0, -_-1), (-_-1, 0)] for _ in range(k)]
    maxsum = 0

    def maxvalstep(currsum, i, tmp_1):  # 当前步数和，当前格值i，当前位置下标，
        global maxsum  # 步数和最大值

        maxsum = max(currsum, maxsum)  # 更新最大值

        for j in range(k):  # 一次走多少步 <k
            for c in range(4):  # 4个方向
                tem_2 = tmp_1[0]+direction[j][c][0]  # x下标
                tem_3 = tmp_1[1] + direction[j][c][1]  # y下标

                if 0 > tem_2 or tem_2 > n1-1 or 0 > tem_3 or tem_3 > n1-1:
                    pass
                else:
                    if A[tem_2][tem_3] > i:  # 可以继续条件，终止条件
                        maxvalstep(currsum+A[tem_2][tem_3], A[tem_2]
                                   [tem_3], [tem_2, tem_3])

    maxvalstep(A[0][0], A[0][0], [0, 0])
    print(maxsum)
