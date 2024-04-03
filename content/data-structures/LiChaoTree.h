/**
 * Author: 
 * Date: 2024-04-03
 * License: CC0
 * Source: Shopping in AtCoder store
 * Description: LiChaoTree with creating nodes dynamically
 * tested in Shopping in AtCoder store
 */
const int N=2e5+10,inf=1e9;
struct LiChaoTree{
    static const int N = 2e5 + 7, M = N * 30, inf = 1e9;
    struct line {
        ll k, b;
        line (ll kk = 0, ll bb = 0) { k = kk, b = bb;}
        ll get(ll x) { return x * k + b;}
    };
    ll inter(line aa, line bb) { return (bb.b - aa.b) / (aa.k - bb.k);}
    int tot = 0, ch[M][2];
    line seg[M];
    void add(int &id, int L, int R, line now) {
        if(!id) return id = ++tot, seg[id] = now, void();
        int mid = (L + R) >> 1;
        ll La = seg[id].get(L), Ra = seg[id].get(R), Lb = now.get(L), Rb = now.get(R);
        if(La <= Lb && Ra <= Rb) return;
        if(La >= Lb && Ra >= Rb) return seg[id] = now, void();
        ll it = inter(seg[id], now);
        if(La <= Lb) { 
            if(it <= mid) add(ch[id][0], L, mid, seg[id]), seg[id] = now;
            else add(ch[id][1], mid + 1, R, now);
        }
        else {
            if(it <= mid) add(ch[id][0], L, mid, now);
            else add(ch[id][1], mid + 1, R, seg[id]), seg[id] = now;
        }
    }
    ll qry(int id, int L, int R, int wz) {
        if(!id) return (ll)inf * inf;
        int mid = (L + R) >> 1;
        if(wz <= mid) return min(seg[id].get(wz), qry(ch[id][0], L, mid, wz));
        else return min(seg[id].get(wz), qry(ch[id][1], mid + 1, R, wz));   
    }
}lc;

