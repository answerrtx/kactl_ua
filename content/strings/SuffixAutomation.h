/**
 * date: 
 * Author: 
 * Source: 
 * Description: [P6139] Suffix Automation and general version, put original SAM to trie to solve substring problems across multiple strings
 * Time: O(N)
 * Usage: 
 * Status: tested
 */
/*original sam*/
template<int N,int M=26> struct suffixam{
    int tot,ch[N*2+10][M],link[N*2+10],len[N*2+10],siz[N*2+10],last;
    suffixam():tot(1),last(1){memset(ch,0,sizeof ch),memset(siz,0,sizeof siz),len[1]=link[1]=0;}
    void expand(int r){
        int u=++tot,p=last;last=u; len[u]=len[p]+1,siz[u]=1;
        while(p&&!ch[p][r]) ch[p][r]=u,p=link[p];
        if(!p) return void(link[u]=1); int q=ch[p][r];
        if(len[q]==len[p]+1) return void(link[u]=q);
        int cq=++tot;memcpy(ch[cq],ch[q],sizeof ch[cq]);
        len[cq]=len[p]+1,link[cq]=link[q]; link[u]=link[q]=cq;
        while(p&&ch[p][r]==q) ch[p][r]=cq,p=link[p];
    }
};
/*general sam*/
const int N=2e6+5; struct trie{int fa,c,s[26];} tr[N]; int idx=1;
il void ins(char *s) {
    int len=strlen(s+1),now=1;
    for(int i=1;i<=len;i++) {
        int &to=tr[now].s[s[i]-'a'];
        if(!to) to=++idx,tr[to].fa=now,tr[to].c=s[i]-'a'; now=to;
    }
}
struct SAM{int fa,len,s[26];} d[N]; int tot=1;
// offline bfs O(n), n is the number of nodes in trie
il int insert(int c,int lst) {
    int p=lst,np=lst=++tot; d[np].len=d[p].len+1;
    for(;p&&!d[p].s[c];p=d[p].fa) d[p].s[c]=np;
    if(!p) {d[np].fa=1;return np;}
    int q=d[p].s[c];
    if(d[q].len==d[p].len+1) {d[np].fa=q;return np;}
    int nq=++tot; d[nq]=d[q],d[nq].len=d[p].len+1;
    d[q].fa=d[np].fa=nq;
    for(;p&&d[p].s[c]==q;p=d[p].fa) d[p].s[c]=nq;
    return np;
}
int pos[N];
il void build(){
    queue<int> q;
    for(int i=0;i<26;i++) if(tr[1].s[i]) q.push(tr[1].s[i]);
    pos[1]=1;
    while(!q.empty()){
        int u=q.front(); q.pop(); pos[u]=insert(tr[u].c,pos[tr[u].fa]);
        for(int i=0;i<26;i++) if(tr[u].s[i]) q.push(tr[u].s[i]);
    }
}
// offline dfs O(m), m is the length of all strings
il int insert(int c,int lst){
    if(d[lst].s[c]&&d[d[lst].s[c]].len==d[lst].len+1) {return d[lst].s[c];}
    int p=lst,np=++tot,flag=0; d[np].len=d[p].len+1;
    for(;p&&!d[p].s[c];p=d[p].fa) d[p].s[c]=np;
    if(!p) {d[np].fa=1;return np;}
    int q=d[p].s[c];
    if(d[q].len==d[p].len+1) {d[np].fa=q;return np;}
    if(p==lst) flag=1,np=0,tot--;
    int nq=++tot; d[nq]=d[q],d[nq].len=d[p].len+1;
    d[q].fa=d[np].fa=nq;
    for(;p&&d[p].s[c]==q;p=d[p].fa) d[p].s[c]=nq;
    return flag?nq:np;
}
int pos[N];char s[N];
il void dfs(int u) {
    for(int i=0;i<26;i++){ int v=tr[u].s[i];
        if(v) pos[v]=insert(i,pos[u]),dfs(v);
    }
}
int main() {
    int n=read(); for(int i=1;i<=n;i++) scanf("%s",s+1),ins(s);
    build();//bfs 
    pos[1]=1,dfs(1);//dfs
    long long ans=0;
    for(int i=2;i<=tot;i++) ans+=d[i].len-d[d[i].fa].len;
    printf("%lld\n%d\n",ans,tot);
    return 0;
}