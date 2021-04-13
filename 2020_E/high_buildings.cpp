#include<cstdio>
#include<vector>
using namespace std;

vector<int> solve(int N, int A, int B, int C) {
    if (A + B - C > N || (A == 1 && B == 1 && A + B - C < N)) {
        vector<int> f_res;
        return f_res;
    }
    vector<int> res(N);
    if (N == 1) {
        res[0] = N;
        return res;
    }
    
    
    int past = 0;
    if (C == 1) {
        int a = A - C;
        int left = N - (A + B - C);
        if (a == 0) {
            res[0] = N;
            past++;
            
            for (int i=0; i<left; i++) res[past+i] = 1;
            past += left;
            
            res[past] = N - 1;
            past++;
            
            for (int i=0; i<B-2; i++) res[past+i] = 1;
        }
        else {
            for (int i=0; i<a-1; i++) res[i] = 1;
            past += a-1;
            
            res[past] = N - 1;
            past++;
            
            for (int i=0; i<left; i++) res[past+i] = 1;
            past += left;
            
            res[past] = N;
            past++;
            
            for (int i=0; i<B-1; i++) res[past+i] = 1;
        }
    }
    else {
        for (int i=0; i<A-C; i++) res[i] = 1;
        past += A-C;
        
        res[past] = N;
        past++;
        
        int left = N - (A + B - C);
        for (int i=0; i<left; i++) res[past+i] = 1;
        past += left;
        
        for (int i=0; i<C-1; i++) res[past+i] = N;
        past += C-1;
        
        for (int i=0; i<B-C; i++) res[past+i] = 1;
    }
    return res;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i=0; i<T; i++) {
        int N, A, B, C;
        scanf("%d %d %d %d", &N, &A, &B, &C);
        
        vector<int> ans = solve(N, A, B, C);
        printf("Case #%d:", i+1);
        if (ans.empty()) printf(" IMPOSSIBLE");
        else {
            for (int i=0; i<ans.size(); i++) {
                printf(" %d", ans[i]);
            }
        }
        printf("\n");
    }
    return 0;
}