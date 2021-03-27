#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    for (int i=0; i<t; i++) {
        int n;
        scanf("%d", &n);
        
        vector<int> ys(n);
        vector<int> xs(n);
        for (int i=0; i<n; i++) {
            scanf("%d %d", &xs[i], &ys[i]);
        }
        
        long long res = 0;
        if (n > 1) {
            
            sort(ys.begin(), ys.end());
            long long midy = ys[(n-1) / 2];
            for (int i=0; i<n; i++) res += abs(ys[i] - midy);
            
            sort(xs.begin(), xs.end());
            vector<long long> dist(n);
            for (int i=0; i<n; i++) dist[i] = xs[i] - i;
            sort(dist.begin(), dist.end());
            long long middist = dist[(n-1) / 2];
            for (int i=0; i<n; i++) res += abs(dist[i] - middist);
        }
        printf("Case #%d: %lld\n", i+1, res);
    }
    return 0;
}