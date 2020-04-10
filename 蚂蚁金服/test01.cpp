#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int T;
    unsigned long long n, m, a, b;
    unsigned long long res;

    cin >> T;

    for (int i = 0; i < T; i++) {
        cin >> n;
        cin >> m;
        cin >> a;
        cin >> b;

        if (n * b > m * a) { // 所有人
            res = m;
        } else if (n < a) { // 杀不死一个人
            res = 0;
        } else {
            res = n * b / a;
        }
        cout << res;
    }
}