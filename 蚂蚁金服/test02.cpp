#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int maxsum = 0; // 步数和最大值

void maxvalstep(int currsum, pair<int, int> pos, vector<vector<int>> mat, int n, int k) { //当前步数和，当前位置下标
    maxsum = max(currsum, maxsum); // 更新最大值

    pair<int, int> direction[k][4]; // 下一步方向
    for (int i = 0; i < k; i++) {
        direction[i][0] = make_pair(0, i + 1);
        direction[i][1] = make_pair(i + 1, 0);
        direction[i][2] = make_pair(0, -i - 1);
        direction[i][3] = make_pair(-i - 1, 0);
    }

    for (int j = 0; j < k; j++) { // 一次走多少步 <k
        for (int c = 0; c < 4; c++) { // 遍历4个方向
            int pos_x = pos.first + direction[j][c].first; // 下一步x下标
            int pos_y = pos.second + direction[j][c].second; // 下一步y下标

            if (0 > pos_x || pos_x > n - 1 || 0 > pos_y || pos_y > n - 1)
                ;
            else {
                int nextval = mat[pos_x][pos_y];
                int currval = mat[pos.first][pos.second];

                if (nextval > currval) { //  # 可以继续条件，终止条件
                    currsum += mat[pos_x][pos_y];
                    pos = make_pair(pos_x, pos_y); // 坐标

                    maxvalstep(currsum, pos, mat, n, k);
                }
            }
        }
    }
}

int main() {
    int T;
    int n, k;

    cin >> T;
    cin >> n;
    cin >> k;

    for (int ti = 0; ti < T; ti++) {
        vector<int> vec; // 一维数组
        vector<vector<int>> mat; // 二维数组
        int tmp;
        for (int i = 0; i < n; i++) {
            vec.clear();
            for (int j = 0; j < n; j++) {
                cin >> tmp;
                vec.push_back(tmp);
            }
            mat.push_back(vec);
        }

        int initsum = mat[0][0];
        pair<int, int> initpos = make_pair(0, 0); // 起始坐标

        // 递归
        maxvalstep(initsum, initpos, mat, n, k); // 左上开始

        cout << maxsum;
    }
}