const long long  MOD = 1000000007;
int fast_mod(int n)    // 求 (t^n)%MOD 
{
    int t[2][2] = {1, 1, 1, 0};
    int ans[2][2] = {1, 0, 0, 1};  // 初始化为单位矩阵
    int tmp[2][2];    //自始至终都作为矩阵乘法中的中间变量 

    while(n)
    {
        if(n & 1)  //实现 ans *= t; 其中要先把 ans赋值给 tmp，然后用 ans = tmp * t 
        {
            for(int i = 0; i < 2; ++i)
                for(int j = 0; j < 2; ++j)
                    tmp[i][j] = ans[i][j]; 
            ans[0][0] = ans[1][1] = ans[0][1] = ans[1][0] = 0;  // 注意这里要都赋值成 0 

            for(int i = 0; i < 2; ++i)    //  矩阵乘法 
            {
                for(int j = 0; j < 2; ++j)
                {
                    for(int k = 0; k < 2; ++k)
                        ans[i][j] = (ans[i][j] + tmp[i][k] * t[k][j]) % MOD;
                }
            }

        }

        //  下边要实现  t *= t 的操作，同样要先将t赋值给中间变量  tmp ，t清零，之后 t = tmp* tmp 
        for(int i = 0; i < 2; ++i)
            for(int j = 0; j < 2; ++j)
                tmp[i][j] = t[i][j];
        t[0][0] = t[1][1] = 0;
        t[0][1] = t[1][0] = 0;
        for(int i = 0; i < 2; ++i)
        {
            for(int j = 0; j < 2; ++j)
            {
                for(int k = 0; k < 2; ++k)
                    t[i][j] = (t[i][j] + tmp[i][k] * tmp[k][j]) % MOD;
            }
        }

        n >>= 1;
    }
    return ans[0][1];
}

int main()
{
    int n;
    while(scanf("%d", &n) && n != -1)
    {    
    int k;
    if(n!=1&&n&1) k=n-1;
    else k=n;
        printf("%d\n", fast_mod(k));
    }
    return 0;
}
