#include<cstdio>
#include<vector>
using namespace std;

int count(int l, int s) {
    if (l < 2 || s < 2) return 0;
    
    int largest = l / 2;
    return max(0, (min(largest, s) - 2 + 1));
}

int solve(vector<vector<int>> &arr) {
    int R = arr.size();
    int C = arr[0].size();
    vector<vector<int>> up(R, vector<int>(C));
    vector<vector<int>> down(R, vector<int>(C));
    vector<vector<int>> left(R, vector<int>(C));
    vector<vector<int>> right(R, vector<int>(C));
    
    for (int i=0; i<R; i++) {
        for (int j=0; j<C; j++) {
            if (arr[i][j] == 0) left[i][j] = 0;
            else if (j == 0) left[i][j] = 1;
            else left[i][j] = left[i][j-1] + 1;
        }
        for (int j=C-1; j>=0; j--) {
            if (arr[i][j] == 0) right[i][j] = 0;
            else if (j == C-1) right[i][j] = 1;
            else right[i][j] = right[i][j+1] + 1;
        }
    }
    
    for (int i=0; i<C; i++) {
        for (int j=0; j<R; j++) {
            if (arr[j][i] == 0) up[j][i] = 0;
            else if (j == 0) up[j][i] = 1;
            else up[j][i] = up[j-1][i] + 1;
        }
        for (int j=R-1; j>=0; j--) {
            if (arr[j][i] == 0) down[j][i] = 0;
            else if (j == R-1) down[j][i] = 1;
            else down[j][i] = down[j+1][i] + 1;
        }
    }

    
    int res = 0;
    for (int i=0; i<R; i++) {
        for (int j=0; j<C; j++) {
            res += count(left[i][j], up[i][j]);
            res += count(up[i][j], right[i][j]);
            res += count(right[i][j], down[i][j]);
            res += count(down[i][j], left[i][j]);
            res += count(left[i][j], down[i][j]);
            res += count(down[i][j], right[i][j]);
            res += count(right[i][j], up[i][j]);
            res += count(up[i][j], left[i][j]);
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
        int ans = solve(arr);
        printf("Case #%d: %d\n", i+1, ans);
    }
    return 0;
}