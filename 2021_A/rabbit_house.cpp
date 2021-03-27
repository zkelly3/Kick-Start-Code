#include<cstdio>
#include<vector>
#include<queue>
using namespace std;

struct House {
    int h;
    int i;
    int j;
};

struct Comp {
    bool operator()(const House &a, const House &b) const {
        return a.h < b.h;
    }
};

long long solve(vector<vector<int>> &arr) {
    int R = arr.size();
    int C = arr[0].size();
    priority_queue<House, vector<House>, Comp> p;
    
    int xs[4] = {1, -1, 0, 0};
    int ys[4] = {0, 0, 1, -1};
    
    for (int i=0; i<R; i++) {
        for (int j=0; j<C; j++) {
            p.push(House{arr[i][j], i, j});
        }
    }
    long long res = 0;
    while (!p.empty()) {
        while (!p.empty() && p.top().h != arr[p.top().i][p.top().j]) p.pop();
        if (!p.empty()) {
            House t = p.top();
            p.pop();
            for (int k=0; k<4; k++) {
                int nx = t.j + xs[k];
                int ny = t.i + ys[k];
                if (nx >=0 && nx < C && ny >= 0 && ny < R) {
                    if (t.h - arr[ny][nx] >= 2) {
                        res += t.h - 1 - arr[ny][nx];
                        arr[ny][nx] = t.h - 1;
                        p.push(House{arr[ny][nx], ny, nx});
                    }
                }
            }
        }
    }
    
    return res;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i=0; i<T; i++) {
        int R, C;
        scanf("%d %d", &R, &C);
        
        vector<vector<int>> arr(R, vector<int>(C));
        for (int j=0; j<R; j++) {
            for (int k=0; k<C; k++) {
                scanf("%d", &arr[j][k]);
            }
        }
        long long ans = solve(arr);
        printf("Case #%d: %lld\n", i+1, ans);
    }
    return 0;
}