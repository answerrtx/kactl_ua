#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 262144
 
const long long P=50000000001507329LL; // 190734863287 * 2 ^ 18 + 1
//const int P=1004535809; // 479 * 2 ^ 21 + 1
//const int P=998244353; // 119 * 2 ^ 23 + 1
const int G=3;
 
long long mul(long long x,long long y){
	return (x*y-(long long)(x/(long double)P*y+1e-3)*P+P)%P;
}
long long qpow(long long x,long long k,long long p){
	long long ret=1;
	while(k){
		if(k&1) ret=mul(ret,x);
		k>>=1;
		x=mul(x,x);
	}
	return ret;
}
 
long long wn[25];
void getwn(){
	for(int i=1; i<=18; ++i){
		int t=1<<i;
		wn[i]=qpow(G,(P-1)/t,P);
	}
}
 
int len;
void NTT(long long y[],int op){
	for(int i=1,j=len>>1,k; i<len-1; ++i){
		if(i<j) swap(y[i],y[j]);
		k=len>>1;
		while(j>=k){
			j-=k;
			k>>=1;
		}
		if(j<k) j+=k;
	}
	int id=0;
	for(int h=2; h<=len; h<<=1) {
		++id;
		for(int i=0; i<len; i+=h){
			long long w=1;
			for(int j=i; j<i+(h>>1); ++j){
				long long u=y[j],t=mul(y[j+h/2],w);
				y[j]=u+t;
				if(y[j]>=P) y[j]-=P;
				y[j+h/2]=u-t+P;
				if(y[j+h/2]>=P) y[j+h/2]-=P;
				w=mul(w,wn[id]);
			}
		}
    }
    if(op==-1){
		for(int i=1; i<len/2; ++i) swap(y[i],y[len-i]);
		long long inv=qpow(len,P-2,P);
		for(int i=0; i<len; ++i) y[i]=mul(y[i],inv);
    }
}
void Convolution(long long A[],long long B[],int n){
	for(len=1; len<(n<<1); len<<=1);
	for(int i=n; i<len; ++i){
		A[i]=B[i]=0;
	}
	
	NTT(A,1); NTT(B,1);
	for(int i=0; i<len; ++i){
		A[i]=mul(A[i],B[i]);
	}
	NTT(A,-1);
}
 
long long A[MAXN],B[MAXN];
int main(){
	getwn();
	int t,n;
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		long long ans=0;
		for(int i=0; i<n; ++i){
			scanf("%lld",&A[i]);
			ans+=A[i]*A[i];
		}
		for(int i=0; i<n; ++i){
			scanf("%lld",&B[n-i-1]);
			ans+=B[n-i-1]*B[n-i-1];
		}
		for(int i=0; i<n; ++i){
			A[i+n]=A[i];
			B[i+n]=0;
		}
		Convolution(A,B,2*n);
		long long mx=0;
		for(int i=n; i<2*n; ++i){
			mx=max(mx,A[i]);
		}
		printf("%lld\n",ans-2*mx);
	}
	return 0;
}
```
```cpp
const LL P = 50000000001507329LL; //190734863287 * 2 ^ 18 + 1, g = 3
//const LL P = 4179340454199820289LL; // 29 * (2 ^ 57), 4e18, g = 3
//const LL P = 1945555039024054273LL; // 27 * (2 ^ 56), 1e18, g = 5

const int G = 3;

LL a[N], b[N];
LL wn[25];
int n;

LL mul(LL x, LL y) {
    return (x * y - (LL)(x / (long double)P * y + 1e-3) * P + P) % P;
}

LL qpow(LL x, LL k, LL p) {
    LL ret = 1;
    while(k) {
        if(k & 1) ret = mul(ret, x);
        k >>= 1;
        x = mul(x, x);
    }
    return ret;
}

void getwn() {
    for(int i = 1; i <= 18; ++i) {
        int t = 1 << i;
        wn[i] = qpow(G, (P - 1) / t, P);
    }
}

void change(LL *y, int len) {
    for(int i = 1, j = len / 2; i < len - 1; ++i) {
        if(i < j) swap(y[i], y[j]);
        int k = len / 2;
        while(j >= k) {
            j -= k;
            k /= 2;
        }
        j += k;
    }
}

void NTT(LL *y, int len, int on) {
    change(y, len);
    int id = 0;
    
    for(int h = 2; h <= len; h <<= 1) {
        ++id;
        for(int j = 0; j < len; j += h) {
            LL w = 1;
            for(int k = j; k < j + h / 2; ++k) {
                LL u = y[k];
                LL t = mul(y[k+h/2], w);
                y[k] = u + t;
                if(y[k] >= P) y[k] -= P;
                y[k+h/2] = u - t + P;
                if(y[k+h/2] >= P) y[k+h/2] -= P;
                w = mul(w, wn[id]);
            }
        }
    }
    if(on == -1) {
        for(int i = 1; i < len / 2; ++i) swap(y[i], y[len-i]);
        LL inv = qpow(len, P - 2, P);
        for(int i = 0; i < len; ++i)
            y[i] = mul(y[i], inv);
    }
}
