#include<cstdio>
#include<cstdlib>
#include<vector>
#include<string>
#include<queue>
using namespace std;

struct Point {
    int i;
    int j;
    int dist;
};

bool check(vector<vector<int>> &mp, int k) {
    int R = mp.size();
    int C = mp[0].size();
    
    bool first = true;
    int max_a, max_s;
    int min_a, min_s;
    
    for (int i=0; i<R; i++) {
        for (int j=0; j<C; j++) {
            if (mp[i][j] > k) {
                if (first) {
                    max_a = i + j;
                    max_s = i - j;
                    min_a = i + j;
                    min_s = i - j;
                    first = false;
                }
                else {
                    max_a = max(max_a, i + j);
                    max_s = max(max_s, i - j);
                    min_a = min(min_a, i + j);
                    min_s = min(min_s, i - j);
                }
            }
        }
    }
    
    if (first) return true;
    
    for (int i=0; i<R; i++) {
        for (int j=0; j<C; j++) {
            if (max(max(abs(i+j - max_a), abs(i+j - min_a)), max(abs(i-j - max_s), abs(i-j - min_s))) <= k) return true;
        }
    }
    return false;
}

int solve(vector<string> &arr) {
    int R = arr.size();
    int C = arr[0].length();
    
    vector<vector<int>> mp(R, vector<int>(C, -1));
    queue<Point> q;
    for (int i=0; i<R; i++) {
        for (int j=0; j<C; j++) {
            if (arr[i][j] == '1') {
                mp[i][j] = 0;
                q.push(Point{i, j, 0});
            }
        }
    }

    while (!q.empty()) {
        Point p = q.front();
        q.pop();
        int di[4] = {0, 0, 1, -1};
        int dj[4] = {1, -1, 0, 0};
        
        for (int k=0; k<4; k++) {
            int new_i = p.i + di[k];
            int new_j = p.j + dj[k];
            if (new_i >=0 && new_i < R && new_j >= 0 && new_j < C && mp[new_i][new_j] == -1) {
                mp[new_i][new_j] = p.dist + 1;
                q.push(Point{new_i, new_j, p.dist+1});
            }
        }
    }
    
    int head = 0;
    int tail = R + C - 1;

    while ((tail - head) > 1) {
        int mid = (head + tail) / 2;
        if (check(mp, mid)) tail = mid;
        else head = mid;
    }

    if (head == 0 && check(mp, head)) return head;
    else return tail;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i=0; i<T; i++) {
        int R, C;
        scanf("%d %d", &R, &C);
        
        vector<string> arr(R);
        for (int j=0; j<R; j++) {
            char buf[251];
            scanf("%s", buf);
            arr[j] = string(buf);
        }
        
        int ans = solve(arr);
        printf("Case #%d: %d\n", i+1, ans);
    }
    return 0;
}