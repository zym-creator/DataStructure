#include<iostream>
#include<queue>
#include<vector>
#include<utility>
#include<array>
using namespace std;
using pos=pair<int,int>;

int main(){
    int n,m,x,y;
    cin>>n>>m>>x>>y;
    vector<vector<int>> a(n,vector<int>(m,-1));
    queue<pos> q;
    q.push({x-1,y-1});
    a[x-1][y-1]=0;
    array<pos,8>move={{
        {2,1},{2,-1},{-2,1},{-2,-1},
        {1,2},{1,-2},{-1,2},{-1,-2}}};
    while(!q.empty()){
        pos p=q.front();
        q.pop();
        for(auto [dx,dy]:move){
            int nx=p.first+dx;
            int ny=p.second+dy;
            bool inside=nx>=0&&nx<n&&ny>=0&&ny<m;
            if (inside&&a[nx][ny]==-1){
                a[nx][ny]=a[p.first][p.second]+1;
                q.push({nx,ny});
            }
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cout<<a[i][j]<<" ";
        }
        cout<<"\n";
    }
}