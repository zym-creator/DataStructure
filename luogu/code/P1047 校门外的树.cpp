#include<iostream>
#include<vector>
using namespace std;
int main(){
    int length=0,n=0,a=0,b=0;
    cin>>length>>n;
    vector<int> v(length+1,1);
    for(int i=0;i<n;i++){
        cin>>a>>b;
        for(int j=a;j<=b;j++){
            v[j]=0;
        }
    }
    int count=0;
    for(int i=0;i<=length;i++){
        if(v[i]==1){
            count++;
        }
    }
    cout<<count<<endl;
}