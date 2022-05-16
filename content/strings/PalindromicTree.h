/**
 * Author: calabash_boy
 * License: ————
 * Source: https://github.com/4thcalabash/ACM-Code-Library/blob/master/String/Automaton/Palindromic_Automaton.cpp
 * Description: [BZOJ 3676] All palindromic substrings of the original string can be found within its structure
 * Time: O(N)
 * Usage:
 *  calc max(len(t)*cnt(t)) t is the palindromic subsring of s, and cnt(t)=t is the number of occurrences
 * Status: tested
 */

const int maxn = 3e5+100;
struct Palindromic_AutoMaton{
    //basic
    int s[maxn],now;
    int nxt[maxn][26],fail[maxn],l[maxn],last,tot;
    // extension
    int num[maxn];/*the number of occurrences*/
    void clear(){
        //1:odd length root, 0:even length root
        s[0]=l[1]=-1;
        fail[0] = tot = now =1;
        last = l[0]=0;
        memset(nxt[0],0,sizeof nxt[0]);
        memset(nxt[1],0,sizeof nxt[1]);
    }
    Palindromic_AutoMaton(){clear();}
    int newnode(int ll){
        tot++;
        memset(nxt[tot],0,sizeof nxt[tot]);
        fail[tot]=num[tot]=0;
        l[tot]=ll;
        return tot;
    }
    int get_fail(int x){
        while (s[now-l[x]-2]!=s[now-1])x = fail[x];
        return x;
    }
    void add(int ch){
        s[now++] = ch;
        int cur = get_fail(last);
        if(!nxt[cur][ch]){
            int tt = newnode(l[cur]+2);
            fail[tt] = nxt[get_fail(fail[cur])][ch];
            nxt[cur][ch] = tt;
        }
        last = nxt[cur][ch];num[last]++;
    }
    void build(){
        //fail[i]<i,Topology updates can be scanned monotonically.
        for (int i=tot;i>=2;i--){
            num[fail[i]]+=num[i];
        }
        num[0]=num[1]=0;
    }
    void init(char* ss){
        while (*ss){
            add(*ss-'a');ss++;
        }
    }
    void init(string str){
        for (int i=0;i<str.size();i++){
            add(str[i]-'a');
        }
    }
    long long query();
}pam;
long long Palindromic_AutoMaton::query(){
    long long ret =1;
    for (int i=2;i<=tot;i++){
        ret = max(ret,1LL*l[i]*num[i]);
    }
    return ret;
}
char s[maxn];
int main(){
    scanf("%s",s);
    pam.init(s);
    pam.build();
    printf("%lld\n",pam.query());
    return 0;
}