#include<bits/stdc++.h>
using namespace std;
#define fore(i,a,b) for(ll i=a, xx=b; i<xx; i++)
#define pb push_back
#define fst first
#define snd second
#define sz(x) ((ll)x.size())
typedef long long ll;
typedef vector <ll> vi;
typedef pair<ll,ll> ii;

int main(){
    int n,m,k,l; cin>>n>>m>>k>>l;
    char tab[n][m];
    fore(i,0,n)fore(j,0,m){
        cin>>tab[i][j];
    }
    k--;l--;
    if(k>l)swap(k,l);
    int maxt=-1;
    pair<int,int> rta=make_pair(0,0);
    fore(i,0,n){
        fore(j,0,m){
            int aux=0;
            if(tab[i][j]=='*') continue;
            if(i-k>=0){
                if(j-l>=0) aux+=(tab[i-k][j-l]=='*');
                if(j+l<n) aux+=(tab[i-k][j+l]=='*');
            }
            if(i+k<n && k!=0){
                if(j-l>=0) aux+=(tab[i+k][j-l]=='*');
                if(j+l<n) aux+=(tab[i+k][j+l]=='*');
            }
            if(j-k>=0){
                if(i-l>=0) aux+=(tab[i-l][j-k]=='*');
                if(i+l<n) aux+=(tab[i+l][j-k]=='*');
            }
            if(j+k<n && k!=0){
                if(i-l>=0) aux+=(tab[i-l][j+k]=='*');
                if(i+l<n) aux+=(tab[i+l][j+k]=='*');
            }
            if(aux>maxt){
                rta=make_pair(i+1,j+1);
                maxt=aux;
            }
        }
    }
    std::cout<<rta.fst<<" "<<rta.snd<<"\n";
}