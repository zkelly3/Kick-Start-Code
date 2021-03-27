#include<stdio.h>
#include <string>
#include <algorithm>
using namespace std;

string i2a(long long n) {
    string res = "";
    while (n != 0) {
        res += to_string(n%10);
        n /= 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

long long countSame(string a, bool isodd) {
    long long res = 0;
    int len = a.length();
    
    if (len == 1) {
        if (isodd) return (a[0]-'0'+1) / 2;
        else return (a[0]-'0') / 2 + 1;
    }
    
    if (a[0]-'0' > 0) {
        long long lower;
        if (isodd) lower = (a[0]-'0') / 2;
        else lower = (a[0]-'0'-1) / 2 + 1;
        for (int i=1; i<len; i++) lower *= 5;
        res += lower;
    }
    
    if (((a[0]-'0') % 2 != 0) == isodd) res += countSame(a.substr(1), !isodd); 
    
    return res;
}

long long count(string a) {
    long long res = 0;
    int len = a.length();
    
    res += countSame(a, true);
    
    long long fives = 1;
    for (int i=1; i<len; i++) {
        fives *= 5;
        res += fives;
    }
    
    return res;
    
}

int main() {
    int t;
    scanf("%d", &t);
    for (int i=0; i<t; i++) {
        long long l, r;
        scanf(" %lld %lld", &l, &r);
        
        string ls, rs;
        ls = i2a(l-1);
        rs = i2a(r);
        
        long long rres = count(rs);
        long long lres = count(ls);
        
        //printf("%lld %lld\n", lres, rres);
        
        long long res = rres - lres;
        printf("Case #%d: %lld\n", i+1, res);
    }
    return 0;
}