#include <iostream>
using namespace std;

int main(){
	int t;
	cin>>t;
	
	for(int k=0;k<t;k++){
	    int n,x,y;
	    cin>>n;
	    int moves=0;
	    for(int i=0;i<(n/2);i++){
	        for(int j=0;j<((n/2)+1);j++){
	            x=j+1;
	            y=i+1;
	            while(!(x>=n/2+1 || y>=n/2+1)){
	                x++;
	                y++;
	                moves++;
	                
	            }
	            moves+= (n+1-x-y);
	            i+= ((n/2)+1-y);
	            j+= ((n/2)+1-x);
	            
	        }
	        
	    }
	    cout<<moves*4<<endl;
	    
	}
	return 0;
    
}
