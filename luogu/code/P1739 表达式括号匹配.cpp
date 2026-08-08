#include<iostream>
using namespace std;
class Stack{
    private:
        static const int MAX_SIZE=21;
        char data[MAX_SIZE];
        int topIndex;
    public:
        Stack():topIndex(-1){}
        bool empty() const{
            return topIndex==-1;
        }
        void push(char value){
            if (topIndex + 1 < MAX_SIZE) {
                data[++topIndex] = value;
            }
        }
        void pop(){
            if (!empty()){
                topIndex--;
            }
            else{
                cout<<"NO"<<endl;
                exit(0);
            }
        }


};
int main(){
    char c;
    Stack s;
    while(cin>>c&&c!='@'){
        if (c!='(' && c!=')'){
            continue;
        }
        else if (c=='('){
            s.push(c);
        }
        else{
            s.pop();
        }
    }
    if (s.empty()) {
        cout<<"YES"<<endl;
    }
    else{
        cout<<"NO"<<endl;
    }
}