#include<cstdio>
#include<vector>
using namespace std;


double solve(int W, int H, int L, int U, int R, int D) {
    double res = 0;
    if (R < W && U > 1) {
        int total = R + U - 2;
        int a = U - 1;
        double sum = 1;
        double comb = 1;
        int remain = total;
        for (int i=1; i<a; i++) {
            comb = comb * (((double)(total-i+1)) / i);
            while (comb > 1 && remain > 0) {
                comb /= 2;
                sum /= 2;
                remain--;
            }
            sum += comb;
        }
        while(remain--) sum /= 2;
        res += sum;
    }
    if (L > 1 && D < H) {
        int total = L + D - 2;
        int a = L - 1;
        double sum = 1;
        double comb = 1;
        int remain = total;
        for (int i=1; i<a; i++) {
            comb = comb * (((double)(total-i+1)) / i);
            while (comb > 1 && remain > 0) {
                comb /= 2;
                sum /= 2;
                remain--;
            }
            sum += comb;
        }
        while(remain--) sum /= 2;
        res += sum;
    }
    return res;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i=0; i<T; i++) {
        int W, H, L, U, R, D;
        scanf("%d %d %d %d %d %d", &W, &H, &L, &U, &R, &D);
        double ans = solve(W, H, L, U, R, D);
        printf("Case #%d: %f\n", i+1, ans);
    }
    return 0;
}