#include <iostream>
#include <set>
using namespace std;

int main(){
    int n,x,possible=1;
    set<int> inc;
    set<int> dec;
    cin>>n;
    
    for(int i=0;i<n;i++){
        cin>>x;
        if(inc.find(x)!=inc.end()){
            if(dec.find(x) == dec.end()){
                dec.insert(x);
            }
            else{
                cout<<"NO";
                possible=0;
                break;
            }
        }
        else{
            inc.insert(x);
        }
    }
    
    if(possible != 0){
        cout<<"YES"<<endl;
        cout<<inc.size()<<endl;
        for(auto it:inc){
            cout<<it<<" ";
        }
        cout<<endl;
        cout<<dec.size()<<endl;
        for(auto iter=dec.rbegin();iter!=dec.rend();iter++){
            cout<<*iter<<" ";
        }
    }
	
	return 0;
}
