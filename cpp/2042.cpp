//구간 합 구하기 #2042
#include <iostream>
#include <vector>

using namespace std;
using ll=long long;
struct segtree{
    vector<ll> arr;
    vector<ll> tree;
    ll n;
    
    ll merge(ll a, ll b){
        return a+b;
    }

    // segtree(vector<ll>&_arr){
    //     arr=_arr;
    //     for(n=1;n<arr.size();n<<=1);
    //     tree.resize(n<<1);
    //     build(1,0,arr.size()-1);
    // }

    ll build(ll idx, ll nl, ll nr){
        if(nl==nr) return tree[idx]=arr[nl];
        ll nm =nl +nr>>1;
        return tree[idx]=merge(build(idx*2,nl,nm),build(idx*2+1,nm+1,nr));
    }

    ll find(ll idx, ll nl, ll nr, ll tl, ll tr){
        if (tr < nl || nr < tl) return 0;
        if (tl <= nl && nr <= tr) return tree[idx];
        ll nm = nl + nr >> 1;
        return merge(
            find(idx*2, nl, nm, tl, tr),
            find(idx*2+1, nm+1, nr, tl, tr)
        );
    }
    ll find(ll tl, ll tr) { return find(1, 0, arr.size()-1, tl, tr); }
    ll update(ll idx, ll nl, ll nr, ll tx, ll val){
        if (tx < nl || nr < tx) return tree[idx];
        if (tx == nl && nr == tx) return tree[idx] = val;
        ll nm = nl + nr >> 1;
        return tree[idx] = merge(
            update(idx*2, nl, nm, tx, val),
            update(idx*2+1, nm+1, nr, tx, val)
        );
    }
    void update(ll tx, ll val) { update(1, 0, arr.size()-1, tx, val); }
}segtree;


int main(){
    cin.tie(0)->sync_with_stdio(0);
    ll n,m,k;
    cin>>n>>m>>k;
    for(ll x,i=0; i<n;i++){
        cin>>x;
        segtree.arr.push_back(x);
    }
    segtree.build(1,0,segtree.arr.size()-1);
    for(ll i=0;i<m+k;i++){
        ll f,tl,tr;
        cin>>f>>tl>>tr;
        if(f==1){
            segtree.update(tl,tr);
        }else if(f==2){
            segtree.find(tl,tr);
        }
    }
    return 0;
}