#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define fst first
#define snd second
#define str string
#define fore(i,a,b) for(int i=a,thxMat=b;i<thxMat;++i)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(),x.end()
#define mset(a,v) memset((a),(v),sizeof(a))
#define FIN ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef tuple<ull, ull, ull> uuu;
typedef vector<uuu> vuuu;
typedef tuple<ull, ull, ull, ull> uuuu;
typedef vector<uuuu> vuuuu;
typedef tuple<ull, ull, ull, ull, ull> uuuuu;
typedef vector<uuuuu> vuuuuu;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;
typedef tuple<ll, ll, ll, ll> iiii;
typedef vector<iiii> viiii;
typedef tuple<ll, ll, ll, ll, ll> iiiii;
typedef vector<iiiii> viiiii;
typedef long double ld;
typedef vector<ld> vd;
typedef pair<ld, ld> dd;
typedef vector<dd> vdd;
typedef tuple<ld, ld, ld> ddd;
typedef vector<ddd> vddd;
typedef tuple<ld, ld, ld, ld> dddd;
typedef vector<dddd> vdddd;
typedef vector<bool> vb;

#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;
const ld eps = 1e-7;


ull solveTree(const set<uu>& edges_, const vb& leafs) {
  ull n  = leafs.size();

  vuu edges(ALL(edges_));

  vector<vuu> adj(n);
  fore(i, 0, n - 1) {
    auto [u, v] = edges[i];
    adj[u].push_back({v, i});
    adj[v].push_back({u, i});
  }

  vector<vu> treeLeafs(n - 1, vu(2, inf));

  function<ull(ull, bool)> fsz = [&](ull e, bool s) {
    assert(treeLeafs[e][s] != inf + 1);
    if (treeLeafs[e][s] != inf) {
      return treeLeafs[e][s];
    }
    treeLeafs[e][s] = inf + 1;

    ull ans = 0;

    ull u = s ? edges[e].second : edges[e].first;
    ull v = s ? edges[e].first : edges[e].second;

    if (adj[u].size() == 1) {
      return treeLeafs[e][s] = leafs[u];
    }

    for (auto [w, e_] : adj[u]) {
      if (w != v) {
        ans += fsz(e_, edges[e_].first == u);
      }
    }

    return treeLeafs[e][s] = ans;
  };

  fore(e, 0, n - 1) {
    fsz(e, 0);
    fsz(e, 1);
  }

  vector<vu> dp(n - 1, vu(2, inf));
  // dp[edge][side]

  function<ull(ull, bool)> f = [&](ull e, bool s) {
    assert(dp[e][s] != inf + 1);
    if (dp[e][s] != inf) {
      return dp[e][s];
    }
    dp[e][s] = inf + 1;

    ull ans = 0;

    ull u = s ? edges[e].second : edges[e].first;
    ull v = s ? edges[e].first : edges[e].second;

    for (auto [w, e_] : adj[u]) {
      if (w != v) {
        ans += f(e_, edges[e_].first == u) + treeLeafs[e_][edges[e_].first == u];
      }
    }

    return dp[e][s] = ans;
  };

  ull ans = inf;

  fore(e, 0, n - 1) {
    auto [u, v] = edges[e];
    if (!leafs[u] && !leafs[v]) {
      ans = min(ans, f(e, 0) + f(e, 1) + treeLeafs[e][0]);
      ans = min(ans, f(e, 0) + f(e, 1) + treeLeafs[e][1]);
    } else if (leafs[u]) {
      ans = min(ans, f(e, 1) + 1);
    } else {
      ans = min(ans, f(e, 0) + 1);
    }
  }

  return ans;
}


ull solve(vector<string>& cmds) {
  ull n = cmds.size();

  set<uu> edges;

  vector<map<string, ull>> names = {{}};
  vb leafs = {false};

  for (string& cmd : cmds) {
    ull i = cmd.find('/', 1);
    string s = cmd.substr(1, i-1);
    ull u;

    if (!names[0].count(s)) {
      u = names[0][s] = leafs.size();
      leafs.push_back(false);
      names.push_back({});
    } else {
      u = names[0][s];
    }

    edges.insert({0, u});

    while (i < cmd.size()) {
      ull j = cmd.find('/', i + 1);
      string t = cmd.substr(i + 1, j - i - 1);
      ull v;


      if (j == string::npos || !names[u].count(t)) {
        v = leafs.size();
        if (j != string::npos) {
          names[u][t] = v;
        }
        leafs.push_back(false);
        names.push_back({});
      } else {
        v = names[u][t];
      }

      edges.insert({u, v});
      u = v;
      i = j;
    }

    leafs.back() = true;
  }

  ull ans = solveTree(edges, leafs);

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n;
  cin >> n;
  vector<string> cmds(n);
  for (auto &cm : cmds) {
    cin >> cm;
  }


  auto ans = solve(cmds);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
