#include <bits/stdc++.h>
#define FIN ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define pb push_back
#define fore(a,b,c) for(int a=b; a<c;++a)
#define show(a) cout<<a<<"\n"
#define showAll(a) for(auto i:a) cout<<i<<" ";cout<<"\n"
#define input(a) for(auto& i:a) cin>>i
#define all(a) a.begin(),a.end()
#define DGB(a) cout<<#a<<" = "<<a<<"\n"
#define RAYA cout<<"=============="<<"\n"
#define pii pair<int,int>
#define pll pair<ll,ll>
#define MAXN 200005
#define ALPH 26
#define M 1000000007
#define fst first
#define snd second
using namespace std;
typedef long long ll;
typedef unsigned int ui;
typedef unsigned long long ull;

vector<int> tree[MAXN];
int szsubtr[MAXN];
int fres=0;

int dfs(int s){
    int res = 1;
    for(auto v: tree[s]){
        res += dfs(v);
    }
    szsubtr[s] = res;
    return res;
}

void process(int s, int used){
    used = max(used -1, 0);
    int tot = szsubtr[s] - 1;
    if(tot<=0){
        return;
    }
    if(tree[s].size() == 1){
        process(tree[s][0],used);
        return;
    }
    int maxpos = -1;
    for(auto v: tree[s]){
        if(szsubtr[v]-used > tot - szsubtr[v]){
            maxpos = v;
        }
    }
    if(maxpos==-1){
        fres += (tot - used)/2;
        return;
    }
    used += tot - szsubtr[maxpos];
    fres += tot - szsubtr[maxpos];
    process(maxpos, used);
}

void solve(){
    int n;
    cin>>n;
    int elem;
    fore(i,2,n+1){
        cin>>elem;
        tree[elem].push_back(i);
    }
    dfs(1);
    process(1,0);
    show(fres);
    fore(i,0,n+1){
        szsubtr[i] = 0;
        tree[i].clear();
    }
    fres = 0;
}

int main(){
    FIN;
    int t;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}

/*TT.TT*/
/*-.;*//*;.-*/
/*-{-}-*//*-{-}{-}-*//*-{-}{--}{-}-*/
/*---...---*//*...---...*//*.-.-.-*//*-.-.-.*//*~~>.<~~*/
/*>>>>>>>.<<<<<<<*//*>>>>>>.<<<<<<*//*>>>>>.<<<<<*//*>>>>.<<<<*//*>>>.<<<*//*>>.<<*//*>.<*/
/*-.-*//*-.-*//*-.-*//*-.-*//*-.-*//*-.-*//*-.-*//*-.-*//*-.-*//*-.-*//*-.-*/
/*-.-*//*-.-*//*-.-*//*-.-*//*-.-*//*-.-*//*-.-*//*-.-*//*-.-*//*-.-*//*-.-*//*-.-*//*-.-*/