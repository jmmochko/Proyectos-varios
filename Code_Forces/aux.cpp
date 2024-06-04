#include <bits/stdc++.h>
#define FIN ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define pb push_back
#define fore(a,b,c) for(ll a=b; a<c;++a)
#define show(a) cout<<a<<"\n"
#define showAll(a) for(auto i:a) cout<<i<<" ";cout<<"\n"
#define input(a) for(auto& i:a) cin>>i
#define all(a) a.begin(),a.end()
#define DGB(a) cout<<#a<<" = "<<a<<"\n"
#define RAYA cout<<"=============="<<"\n"
#define pii pair<int,int>
#define pll pair<ll,ll>
#define MAXN 200005
#define ALPH 31
#define M 1000000007
#define fst first
#define snd second
using namespace std;
typedef long long ll;
typedef unsigned int ui;
typedef unsigned long long ull;

bool is_sq(ll a){
    return (ll)sqrt(a)*(ll)sqrt(a) == a;
}

vector<ll> find_eq(multiset<int> &m, ll n){
    ll i = 1;
    ll lm = 10;
    vector<ll> res;
    fore(k,0,n-1){
        i*=10;
        lm*=10;
    }
    fore(j,i,lm){
        if(is_sq(j)){
            ll copi = j;
            multiset<int> e;
            while(copi>0){
                e.insert(copi%10);
                copi/=10;
            }
            bool eq = true;
            for(auto num: e){
                if(e.count(num)!=m.count(num)){
                    eq = false;
                    break;
                }
            }
            if(eq){
                res.push_back(j);
            }
        }
        if(res.size()>=n){
            return res;
        }
    }
    return res;
}

int main(){
    ll n;
    cin>>n;
    ll i = 1;
    ll lm = 10;
    fore(k,0,n-1){
        i*=10;
        lm*=10;
    }
    vector<ll> res;
    fore(j,i,lm){
        if(is_sq(j)){
            ll copi = j;
            multiset<int> e;
            while(copi>0){
                e.insert(copi%10);
                copi/=10;
            }
            res = find_eq(e,n);
            if(res.size()>=n){
                fore(l,0,res.size()){
                    cout<<res[l]<<",";
                }
                cout<<'\n';
                return 0;
            }
        }
    }
    return 0;
}