#include <stdio.h>
#include<vector>
#include <string>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    for (int i=0; i<t; i++) {
        int n, q;
        scanf("%d %d", &n, &q);
        vector<string> ns(n);
        vector<int>nsl(n);
        for (int j=0; j<n; j++) {
            char tmp[30];
            scanf("%s", tmp);
            ns[j] = string(tmp);
            nsl[j] = ns[j].length();
        }
        
        int max_l = 100;
        vector<vector<int>> dist(26, vector<int>(26, max_l));
        for (int j=0; j < 26; ++j) {
            dist[j][j] = 0;
        }
        for (int j=0; j<n; j++) {
            for (int k=0;k<nsl[j]-1; k++) {
                for (int l=k+1; l<nsl[j]; l++) {
                    if (ns[j][k] != ns[j][l]) {
                        dist[ns[j][k]-'A'][ns[j][l]-'A'] = 1;
                        dist[ns[j][l]-'A'][ns[j][k]-'A'] = 1;
                    }
                }
            }
        }
        
        for (int j=0; j<26; j++) {
            for (int k=0; k<26; k++) {
                for (int l=0; l<26; l++) {
                    if (dist[k][l] > dist[k][j] + dist[j][l]) dist[k][l] = dist[k][j] + dist[j][l];
                }
            }
        }
        
        printf("Case #%d:", i+1);
        for (int j=0; j<q; j++) {
            int src, tgt;
            scanf("%d %d", &src, &tgt);
            int res = max_l;
            for (int k=0; k<nsl[src-1]; k++) {
                for (int l=0; l<nsl[tgt-1]; l++) {
                    if (res > dist[ns[src-1][k]-'A'][ns[tgt-1][l]-'A']) res = dist[ns[src-1][k]-'A'][ns[tgt-1][l]-'A'];
                }
            }
            res += 2;
            if (res >= max_l) res = -1;
            printf(" %d", res);
        }
        printf("\n");
    }
    return 0;
}