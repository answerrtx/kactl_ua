/** 
 * Author: wucstdio
 * Date: ____
 * License: ____
 * Source: ___
 * Description:[P5325] Given $n$ and $f\left(p^{k}\right)=p^{k}\left(p^{k}-1\right)$, compute $\sum_{i=1}^{n} f(i)$
 * Usage:___
 * Status: tested
 * MOD = 1e9+7
 */

const ll MOD=1000000007,inv2=500000004,inv3=333333336; ll prime[1000005],num,sp1[1000005],sp2[1000005];
ll n,Sqr,tot,g1[1000005],g2[1000005],w[1000005],ind1[1000005],ind2[1000005]; bool flag[1000005];
void pre(int n){ //linear seive
    flag[1]=1;
    for(int i=1;i<=n;i++){
        if(!flag[i]){
            prime[++num]=i;
            sp1[num]=(sp1[num-1]+i)%MOD;
            sp2[num]=(sp2[num-1]+1ll*i*i)%MOD;
        }
        for(int j=1;j<=num&&prime[j]*i<=n;j++){
            flag[i*prime[j]]=1;
            if(i%prime[j]==0)break;
        }
    }
}
ll S(ll x,int y) {//second part
    if(prime[y]>=x)return 0;
    ll k=x<=Sqr?ind1[x]:ind2[n/x];
    ll ans=(g2[k]-g1[k]+MOD-(sp2[y]-sp1[y])+MOD)%MOD;
    for(int i=y+1;i<=num&&prime[i]*prime[i]<=x;i++){
        ll pe=prime[i];
        for(int e=1;pe<=x;e++,pe=pe*prime[i]){
            ll xx=pe%MOD;
            ans=(ans+xx*(xx-1)%MOD*(S(x/pe,i)+(e!=1)))%MOD;
        }
    }
    return ans%MOD; }
int main() {
    scanf("%lld",&n);
    Sqr=sqrt(n);
    pre(Sqr);
    for(ll i=1;i<=n;) {
        ll j=n/(n/i);
        w[++tot]=n/i;
        g1[tot]=w[tot]%MOD;
        g2[tot]=g1[tot]*(g1[tot]+1)/2%MOD*(2*g1[tot]+1)%MOD*inv3%MOD;
        g2[tot]--;
        g1[tot]=g1[tot]*(g1[tot]+1)/2%MOD-1;
        if(n/i<=Sqr)ind1[n/i]=tot;
        else ind2[n/(n/i)]=tot;
        i=j+1;
    }
    for(int i=1;i<=num;i++){ 
        for(int j=1;j<=tot&&prime[i]*prime[i]<=w[j];j++){
            ll k=w[j]/prime[i]<=Sqr?ind1[w[j]/prime[i]]:ind2[n/(w[j]/prime[i])];
            g1[j]-=prime[i]*(g1[k]-sp1[i-1]+MOD)%MOD;
            g2[j]-=prime[i]*prime[i]%MOD*(g2[k]-sp2[i-1]+MOD)%MOD;
            g1[j]%=MOD,g2[j]%=MOD;
            if(g1[j]<0)g1[j]+=MOD;
            if(g2[j]<0)g2[j]+=MOD;
        }
    }
    printf("%lld\n",(S(n,0)+1)%MOD);
    return 0;
}