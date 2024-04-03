/**
 * Author: 
 * Date: 2024-04-03
 * License: CC0
 * Source: 	Panda Preserve
 * Description: Voronoi with halfplane
 * tested in Panda Preserve
 */
int cnt,l,r;
bool Onleft(Pt p,Line L){return L.v*(p-L.p)>0;}
Pt Inter(Line a,Line b){return a.p+a.v*((b.v*(a.p-b.p))/(a.v*b.v));}
void HalfPlane(){
    sort(L+1,L+1+cnt),q[l=r=1]=L[1];
    for(int i=2;i<=cnt;i++) if(sgn(L[i].ang-L[i-1].ang)){
        while(l<r&&!Onleft(p[r-1],L[i])) r--;
        while(l<r&&!Onleft(p[l],L[i])) l++;
        q[++r]=L[i],p[r-1]=Inter(q[r-1],q[r]);
    }
    while(l<r-1&&!Onleft(p[r-1],q[l])) r--;
    p[r]=Inter(q[r],q[l]);
}
bool InPolygon(Pt p){
    bool crs=0;
    for(int i=1;i<=n;i++){
        if(!sgn((a[i]-p).len()+(a[i+1]-p).len()-(a[i+1]-a[i]).len())) return 1;
        double u=a[i].y,v=a[i+1].y;
        if(u==v||p.y<min(u,v)||p.y>=max(u,v)) continue;
        crs^=(a[i].x+(a[i+1].x-a[i].x)*(p.y-u)/(v-u))>p.x;
    }
    return crs;
}
bool Intersect(Line a,Line b){
    return ((b.p-a.p)*a.v) * ((b.p+b.v-a.p)*a.v) < 0
        && ((a.p-b.p)*b.v) * ((a.p+a.v-b.p)*b.v) < 0;
}
int main(){
    cin>>n; for(int i=1;i<=n;i++)  cin>>a[i].x>>a[i].y; 
    a[n+1]=a[1]; double ans=0;
    for(int i=1;i<=n;i++){
        L[cnt=1]=Line(Pt(-1e4,-1e4),Pt(1,0)); L[++cnt]=Line(Pt(1e4,-1e4),Pt(0,1));
        L[++cnt]=Line(Pt(1e4,1e4),Pt(-1,0));L[++cnt]=Line(Pt(-1e4,1e4),Pt(0,-1));
        for(int j=1;j<=n;j++) if(i^j){
            Pt o=a[i]+a[j],v=a[j]-a[i]; L[++cnt]=Line(Pt(o.x/2,o.y/2),Pt(-v.y,v.x));
        }
        HalfPlane(),p[r+1]=p[l];
        for(int j=l;j<=r;j++){
            if(InPolygon(p[j])) ans=max(ans,(p[j]-a[i]).len());
            for(int k=1;k<=n;k++){
                Line x=Line(p[j],p[j+1]-p[j],0),y=Line(a[k],a[k+1]-a[k],0);
                if(Intersect(x,y)) ans=max(ans,(Inter(x,y)-a[i]).len());
    }}} 
    cout<<fixed<<setprecision(12)<<ans<<"\n";
}