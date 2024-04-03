/**
 * Author: Victor Lecomte, chilli
 * Date: 2024-4-2
 * License: CC0
 * Description: 
 * Status: tested
 */
#define N 1054
const double eps = 2e-10, pi2 = M_PI * 2.0;
int n; double r[N]; cirl O[N], l[N * 2]; relation rel[N];
inline double f(cirl O, double r, double t) {return r * (r * t + O.x * sin(t) - O.y * cos(t));}
enum relation {outside = 0, intersective = 1, contained = 2, containing = 3};

relation circle_relation(const cirl O1, double r1, const cirl O2, double r2) {
	double d = (O1 - O2).norm2();
	if (le((r1 + r2) * (r1 + r2), d)) return outside;
	if (ge((r1 - r2) * (r1 - r2), d)) return le(r1, r2) ? contained : containing;
	return intersective;
}

void intersection(const cirl O1, double r1, const cirl O2, double r2, double &beg, double &end) {
	cirl O12 = O2 - O1;
	double d2 = O12.norm2(), d = sqrt(d2),
	Cos = ((r1 + r2) * (r1 - r2) + d2) / (2.0 * d * r1),
	sAng = acos(Cos), iAng = atan2(O12.y, O12.x);
	iAng < 0.0 ? iAng += pi2 : 0.0;
	(beg = iAng - sAng) < 0.0 ? beg += pi2 : 0.0;
	(end = iAng + sAng) >= pi2 ? end -= pi2 : 0.0;
}

double circle_union(){ 
	for (i = 0; i < n; ++i) {
		for (j = 0; j < n; ++j)
			if ((rel[j] = circle_relation(O[i], r[i], O[j], r[j])) == contained)
				if (!eq(r[i], r[j]) || i > j) break;
		if (j < n) continue;
		for (cnt = j = 0; j < n; ++j)
			if (rel[j] == intersective) {
				intersection(O[i], r[i], O[j], r[j], il, ir);
				if (il <= ir) l[cnt++] = cirl(il, ir);
				else l[cnt++] = cirl(0, ir), l[cnt++] = cirl(il, pi2);
			}
		l[cnt++] = cirl(pi2, pi2); std::sort(l, l + cnt);
		for (la = j = 0; j < cnt; ++j)
			if (la < l[j].x) ans += f(O[i], r[i], l[j].x) - f(O[i], r[i], la), la = l[j].y;
			else if (la < l[j].y) la = l[j].y;
	}
	return ans * 0.5;
}