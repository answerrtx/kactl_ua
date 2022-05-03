typedef long long ll;
using namespace std;
//**************************************************************************************

void extend_gcd(ll a,ll &x,ll b,ll &y)
{
    if(b==0)
    {
        x=1,y=0;
        return;
    }
    ll x1,y1;
    extend_gcd(b,x1,a%b,y1);
    x=y1;
    y=x1-(a/b)*y1;
}
ll inv(ll a,ll m)
{
    ll t1,t2;
    extend_gcd(a,t1,m,t2);
    return (t1%m+m)%m;
}
ll qpow(ll x,ll y,ll m)
{
    if(!y)return 1;
    ll ans = qpow(x,y>>1,m);
    ans = ans*ans%m;
    if(y&1)ans = ans*x%m;
    return ans;
}

ll nump(ll x,ll p)
{
    ll ans = 0;
    while(x)ans+=x/p,x/=p;
    return ans;
}
ll fac(ll n,ll p,ll pk)
{
    if(n==0)return 1;
    ll ans = 1;
    for(ll i=1;i<=pk;i++)
    {
        if(i%p==0)continue;
        ans = ans*i%pk;
    }
    ans = qpow(ans,n/pk,pk);
    ll to = n%pk;
    for(ll i =1;i<=to;i++)
    {
        if(i%p==0)continue;
        ans = ans*i%pk;
    }
    return fac(n/p,p,pk)*ans%pk;
}
ll cal(ll n,ll m,ll p ,ll pi,ll pk)
{
    ll a = fac(n,pi,pk),b=fac(m,pi,pk),c=fac(n-m,pi,pk);
    ll d = nump(n,pi)-nump(m,pi)-nump(n-m,pi);
    ll ans = a%pk * inv(b,pk)%pk * inv(c,pk)%pk*qpow(pi,d,pk)%pk;
    return ans*(p/pk)%p*inv(p/pk,pk)%p;
}
ll mCnmodp(ll n,ll m,ll p)
{
    ll ans = 0;
    ll x = p;
    for(ll i =2;i*i<=x&&x>1;i++)
    {
        ll k=0,pk=1;
        while(x%i==0)
        {
            x/=i;
            k++;
            pk*=i;
        }
        if(k>0)
            ans=(ans+cal(n,m,p,i,pk))%p;
    }
    if(x>1)ans=(ans+cal(n,m,p,x,x))%p;
    return ans;
}
ll qtpow(ll x,ll y,ll M)
{
    ll ret=0LL;
    for(x%=M;y;y>>=1LL)
    {
        if(y&1LL)
        {
            ret+=x;
            ret%=M;
            if(ret<0) ret+=M;
        }
        x+=x;
        x%=M;
        if(x<0) x+=M;
    }
    return ret;
}
void solve(ll r[],ll s[],int t)
{
    ll M=1LL,ans=0LL;
    ll p[20],q[20],e[20];
    for(int i=0;i<t;i++)
        M*=r[i];
    for(int i=0;i<t;i++)
    {
        ll tmp=M/r[i],tt;
        extend_gcd(tmp,p[i],r[i],q[i]);
        p[i]%=M;
        if(p[i]<0) p[i]+=M;
        e[i]=qtpow(tmp,p[i],M);
        tt=qtpow(e[i],s[i],M);
        ans=(ans+tt)%M;
        if(ans<0) ans+=M;
    }
    printf("%I64d\n",ans);
}

ll CCC[20],DDD[20];
int main()
{
    int t;
    scanf("%d",&t);
    int num = 0;
    ll n,m,p;
    while(t--)
    {
        memset(CCC,0,sizeof(CCC));
        memset(DDD,0,sizeof(DDD));
        scanf("%I64d %I64d %d",&n,&m,&num);
        for(int i=0;i<num;i++)
        {
            scanf("%I64d",&CCC[i]);
            DDD[i]=mCnmodp(n,m,CCC[i]);
        }
        solve(CCC,DDD,num);
    }
    return 0;
}
