#include<cstdio>
#include<vector>
#include<string>
#include <algorithm>
using namespace std;

bool dfs(vector<int> &passed, int from, int now, vector<vector<int>> &edges, vector<int>& res) {
    passed[now] = 1;
    for (int i=0; i<edges[now].size(); i++) {
        if (passed[edges[now][i]] == 2) continue;
        if (passed[edges[now][i]] == 1) return true;
        if (dfs(passed, now, edges[now][i], edges, res)) return true;
    }
    res.push_back(now);
    passed[now] = 2;
    return false;
}

vector<int> solve(vector<string> &arr, int R, int C) {
    vector<vector<int>> mp(26, vector<int>(26));
    vector<vector<int>> edges(26, vector<int>());
    vector<bool> exist(26);
    for (int i=0; i<R-1; i++) {
        for (int j=0; j<C; j++) {
            exist[arr[i][j]-'A'] = true;
            if (arr[i][j] != arr[i+1][j]) {
                mp[arr[i+1][j]-'A'][arr[i][j]-'A'] = 1;
            }
        }
    }
    for (int i=0; i<C; i++) exist[arr[R-1][i]-'A'] = true;
    
    for(int i=0; i<26; i++) {
        for (int j=0; j<26; j++) {
            if (mp[i][j] == 1) {
                edges[i].push_back(j);
            }
        }
    }
    
    vector<int> res;
    vector<int> passed(26);
    bool hasRing = false;
    for (int i=0; i<26; i++) {
        if (passed[i] == 0 && exist[i]) {
            hasRing = hasRing || dfs(passed, -1, i, edges, res);
            if (hasRing) break;
        }
    }
    if (hasRing) {
        vector<int> f_res;
        return f_res;
    }
    
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i=0; i<T; i++) {
        int R, C;
        scanf("%d %d", &R, &C);
        
        vector<string> arr(R);
        for (int j=0; j<R; j++) {
            char buf[40];
            scanf("%s", buf);
            arr[j] = string(buf);
        }
        vector<int> ans;
        ans = solve(arr, R, C);
        if (ans.empty()) printf("Case #%d: %d\n", i+1, -1);
        else {
            printf("Case #%d: ", i+1);
            for (int j=0; j<ans.size(); j++) {
                printf("%c", 'A'+ans[j]);
            }
            printf("\n");
        }
    }
    return 0;
}