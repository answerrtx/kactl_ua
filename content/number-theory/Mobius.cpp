#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long  ll;
const ll p =1000000007;
const int  N=100000;
bool is_prime[N+500];
int prime[N+50];
int mu[N+50];
ll sum[N+50];
ll tot;
void Moblus()
{
    tot = 0;
    mu[1] = 1;
    for(ll i = 2; i < N; i++)
    {
        if(!is_prime[i])
        {
            prime[tot++] = i;
            mu[i] = -1;
        }
        for(ll j = 0; j < tot && i*prime[j] < N; j++)
        {
            is_prime[i*prime[j]] = 1;
            if(i % prime[j])
            {
                mu[i*prime[j]] = -mu[i];
            }
            else
            {
                mu[i*prime[j]] = 0;
                break;
            }
        }
    }
}
//找[1,n],[1,m]内互质的数的对数
ll solve(ll n,ll m )
{
    if (n>m)swap(n,m);
    ll ret=0;
    for (int i=1;i<=n;i++)
        ret+=mu[i]*(n/i)*(m/i);
    return ret;
}
int main()
{
    Moblus();
    for (int i=1;i<N;i++)
        sum[i]=sum[i-1]+mu[i];
    int t;cin>>t;
    while(t--)
    {
        ll k,a,b,c,d;
        scanf("%lld",&a);
        scanf("%lld",&b);
        ll ans1=solve(a,b);
        printf("%lld\n",ans1);
    }


    return 0;
}
