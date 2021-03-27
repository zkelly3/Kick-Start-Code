#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

struct Edge {
    int r;
    int c;
    int cost;
};

bool comp(Edge a, Edge b) {
    return a.cost > b.cost;
}

int findRoot(vector<int> &ds, int a) {
    if (ds[a] != a) ds[a] = findRoot(ds, ds[a]);
    return ds[a];
}

void merge(vector<int> &ds, int a, int b) {
    ds[findRoot(ds, b)] = ds[findRoot(ds, a)];
}

int solve(vector<vector<int>> &A, vector<vector<int>> &B, vector<int> &R, vector<int> &C) {
    int N = A.size();
    
    vector<int> ds(N*2);
    for (int i=0; i<N*2; i++) ds[i] = i;
    
    vector<Edge> edges;
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            if (A[i][j] == -1) {
                edges.push_back(Edge{i, j, B[i][j]});
            }
        }
    }
    sort(edges.begin(), edges.end(), comp);
    
    int res = 0;
    for (int i=0; i<edges.size(); i++) {
        //printf("%d %d %d %d %d\n", edges[i].r, edges[i].c, edges[i].cost, findRoot(ds, edges[i].r), findRoot(ds, N+edges[i].c));
        if (findRoot(ds, edges[i].r) == findRoot(ds, N+edges[i].c)) {
            res += edges[i].cost;
        }
        else {
            merge(ds, edges[i].r, N+edges[i].c);
        }
    }
    return res;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i=0; i<T; i++) {
        int N;
        scanf("%d", &N);
        
        vector<vector<int>> A(N, vector<int>(N));
        for (int j=0; j<N; j++) {
            for (int k=0; k<N; k++) {
                scanf("%d", &A[j][k]);
            }
        }
        vector<vector<int>> B(N, vector<int>(N));
        for (int j=0; j<N; j++) {
            for (int k=0; k<N; k++) {
                scanf("%d", &B[j][k]);
            }
        }
        
        vector<int> R(N);
        for (int j=0; j<N; j++) {
            scanf("%d", &R[j]);
        }
        vector<int> C(N);
        for (int j=0; j<N; j++) {
            scanf("%d", &C[j]);
        }
        
        int ans = solve(A, B, R, C);
        printf("Case #%d: %d\n", i+1, ans);
    }
    return 0;
}