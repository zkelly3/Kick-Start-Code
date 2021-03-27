#include<stdio.h>
#include <algorithm>
using namespace std;
int main() {
    int t;
    scanf("%d", &t);
    for (int i=0; i<t; i++) {
        int n, k, s;
        scanf(" %d %d %d", &n, &k, &s);
        
        int res = min(k+n, k+k-s-s+n);
        
        printf("Case #%d: %d\n", i+1, res);
    }
    return 0;
}