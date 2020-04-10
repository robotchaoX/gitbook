#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int maxsum = 0; // 步数和最大值

void maxvalstep(int currsum, int currval, int tmp_1[2], vector<vector<int>> mat, int n,
                int k) { //当前步数和，当前格值i，当前位置下标
    maxsum = max(currsum, maxsum); // 更新最大值

    int direction[k][4][2];
    for (int i = 0; i < k; i++) {
        direction[i][0][0] = 0;
        direction[i][0][1] = i + 1;
        direction[i][1][0] = i + 1;
        direction[i][1][1] = 0;
        direction[i][2][0] = 0;
        direction[i][2][1] = -i - 1;
        direction[i][3][0] = -i - 1;
        direction[i][3][1] = 0;
    }

    for (int j = 0; j < k; j++) { // 一次走多少步 <k
        for (int c = 0; c < 4; c++) { // 4个方向
            int tem_2 = tmp_1[0] + direction[j][c][0]; // x下标
            int tem_3 = tmp_1[1] + direction[j][c][1];

            if (0 > tem_2 || tem_2 > n - 1 || 0 > tem_3 || tem_3 > n - 1)
                ;
            else if (mat[tem_2][tem_3] > currval) {
                int pos[2] = {tem_2, tem_3}; // 坐标
                maxvalstep(currsum + mat[tem_2][tem_3], mat[tem_2][tem_3], pos, mat, n, k);
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

        int initpos[2] = {0, 0}; // 坐标
        // 递归
        maxvalstep(mat[0][0], mat[0][0], initpos, mat, n, k); // 左上开始

        cout << maxsum;
        //
    }
}