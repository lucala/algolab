#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <climits>

using namespace std;

int rec(int round, int finalPos, int red, int black, vector<vector<int> > &trans){
 if(red==finalPos)
  return 0;
 if(black==finalPos)
  return 1;


 if(round%2==0){
  for(int i=0; i<trans.size(0); i++){
   
  }
 }else{
  
 }

}

void test(){
 int n,m,r,b,u,v;
 cin >> n >> m;
 
 cin >> r >> b;
 r--; b--; // start at 0 index

 vector<vector<int> > trans(m, vector<int>());
 for(int i=0; i<m; i++){
  cin >> u >> v;
  u--; v--; //start at index 0
  trans[u].push_back(v);
 }

 //start with 0. round, holmes=red, moriarty=black
 cout << rec(0, n, r, b, trans) << endl;

}


int main(){
 int n;
 cin >> n;
 while(n--) test();
}
