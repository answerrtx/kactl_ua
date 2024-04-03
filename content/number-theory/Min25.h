/** 
 * Author: wucstdio
 * Date: ____
 * License: ____
 * Source: ___
 * Description:[P6053] Given $n$ and $f\left(p^{k}\right)=p^{k}\left(p^{k}-1\right)$, compute $\sum_{i=1}^{n} f(i)$ with $O(n^{3/4}/log n)$
 * Usage:___
 * Status: tested
 * MOD = 1e9+7
 */

using ll=long long;
constexpr ll mod=1000000007;
ll n,g1[200010],g2[200010],lim[200010],p[100010];
int sqrtn,tot,m,id1[100010],id2[100010];
auto at=[](ll v)->int&{return v<=sqrtn?id1[v]:id2[n/v];};
void init(){
	for(int i=2;i<=sqrtn;i++){
		if(!p[i])p[++tot]=i;
		for(int j=1;j<=tot&&i*p[j]<=sqrtn;j++)
		{p[i*p[j]]=1;if(i%p[j]==0)break;}
	}
}
ll calcsum(ll x,int y){
	if(p[y]>x)return 0;
	ll ret=(g1[at(x)]+g2[at(x)]-(g1[at(p[y])]+g2[at(p[y])])+mod)%mod;
	for(int i=y+1;p[i]*p[i]<=x&&i<=tot;i++){
		ll to=1;
		for(int t=1;(to*=p[i])<=x;t++)
		(ret+=(p[i]^t)*(calcsum(x/to,i)+(t>1)))%=mod;
	}return ret;
}
ll min_25(){
	sqrtn=sqrt(n)+1;init();
	for(ll l=1;l<=n;l=n/(n/l)+1)
	m++,g1[m]=(n/l+1)%mod*(n/l)%mod*(mod+1>>1)%mod-1,g2[m]=mod-(n/l-1),at(lim[m]=n/l)=m;
	for(int i=1;i<=tot;i++)
	for(int j=1;p[i]*p[i]<=lim[j];j++)
	(g1[j]+=mod-p[i]*(g1[at(lim[j]/p[i])]-g1[at(p[i-1])])%mod)%=mod,
	(g2[j]+=mod-(g2[at(lim[j]/p[i])]-g2[at(p[i-1])]))%=mod;
	for(int i=1;i<m;i++)(g2[i]+=2)%=mod;
	return calcsum(n,0)+1;
}
int main(){ cin>>n; cout<<min_25()%mod;return 0;}