#include<bits/stdc++.h>
using namespace std;
#define FIN ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define fore(i,a,b) for(ll i=a, xx=b; i<xx; i++)
#define pb push_back
#define fst first
#define snd second
#define sz(x) ((ll)x.size())
typedef long long ll;
typedef vector <ll> vi;
typedef pair<ll,ll> ii;

vector<int> g[5005];
int dist[5005][5005];

void bfs(int a){
	queue<int> q;
	q.push(a);
	int vis[5005];
	fore(i,0,5005) vis[i]=0;
	while(!q.empty()){
		int p=q.front();
		q.pop();
		vis[p]=1;
		for(auto x : g[p]){
			if(vis[x]!=0) continue;
			q.push(x);
			dist[a][x]=dist[a][p]+1;
		
		}
	}
	return;
} 

int main(){
	int n,m,d;
	cin>>n>>m>>d;
	fore(i,0,m){
		int a,b;
		cin>>a>>b;
		a--;
		b--;
		g[a].pb(b);
		g[b].pb(a);
	}
	fore(i,0,n){
		bfs(i);
	}
	int mind=1e6;
	int node=-1;
	fore(i,0,n){
		int aux=1e6;
		fore(j,0,n){
			aux=max(aux,dist[i][j]);
		}
		mind=min(aux,mind);
		if(mind==aux) node=i;
	}
	int dos=1e6;
	fore(i,0,n){
		dos=max(dist[node][i],dos);
	}
	int rta=max(d+1-mind,0);
	rta+=max(0,d+1-dos);
	cout<<rta<<" "<<rta<<"\n";
}