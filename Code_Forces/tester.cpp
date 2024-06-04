#include <bits/stdc++.h>
#define FIN ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define pb push_back
#define fore(a,b,c) for(unsigned int a=b; a<c;++a)
#define dfore(a,b,c) for(int a=b; a>=c;--a)
#define show(a) cout<<a<<"\n"
#define showAll(a) for(auto i:a) cout<<i<<" ";cout<<"\n"
#define input(a) for(auto& i:a) cin>>i
#define all(a) a.begin(),a.end()
#define DGB(a) cout<<#a<<" = "<<a<<"\n"
#define RAYA cout<<"=============="<<"\n"
#define pii pair<int,int>
#define pll pair<ll,ll>
#define MAXN 100005
#define MAXLL (1ll<<61)
using namespace std;
typedef long long ll;
typedef unsigned int ui;

void solve(){
    int n,m,e;
    cin>>n>>m;
    vector<int> psums(n*m);
    cin>>psums[0];
    fore(i,1,n*m){
        cin>>e;
        psums[i] = psums[i-1] + e;
    }
    
}

int main(){
    FIN;
    int t = 1;
    //cin>>t;
    while(t--){
        solve();
    }
    return 0;
}