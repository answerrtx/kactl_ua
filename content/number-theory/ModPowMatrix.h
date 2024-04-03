/**
 * Author: 
 * Date: 2024-04-03
 * Description:
 * Status: tested
 */
typedef long long LL;
const int mod=1000000007;
LL n, k;

struct matrix{
    LL c[101][101];
    matrix(){memset(c, 0, sizeof c);}
} A, res;

matrix operator*(matrix &x, matrix &y){ 
    matrix t; 
    for(int i=1; i<=n; i++)
      for(int j=1; j<=n; j++)
        for(int k=1; k<=n; k++)    
          t.c[i][j]=(t.c[i][j]+x.c[i][k]*y.c[k][j])%mod;
    return t;
}
void quickpow(LL k, matrix A){ 
    matrix res;
    for(int i=1; i<=n; i++) res.c[i][i]=1; 
    while(k){
        if(k & 1) res = res*A;
        A = A*A, k >>= 1;
    }  
    return res;
}
