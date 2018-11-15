#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <stdlib.h>

using namespace std;


void testQuad(int cases){
 for(int c=0; c < cases; c++){
  int n,v;
  cin >> n;

  vector<int> base(n);
  for(int i=0; i<n; i++){
   cin >> v;
   base[i] = v;
  }
  
  int len = n;
  set<pair<int,int> > maxSet;
  maxSet.insert(make_pair(base[0],0)); //timer, pos in vector
  stack<int> timers;
  pair<int, int> curr;
  int pos;

  //calculate
  while(!maxSet.empty()){
   curr = *(--maxSet.end());
   maxSet.erase(curr);
   timers.push(curr.first);
   pos = curr.second;
   if(2*pos+2 < n){
    maxSet.insert(make_pair(base[2*pos+1],2*pos+1));
    maxSet.insert(make_pair(base[2*pos+2],2*pos+2));
    len -= 2;
   }
   
  }

  int time, counter=1;
  bool possible = true;
  for(int i=0; i<n; i++){
   time = timers.top();
   timers.pop();
   if(time < counter){
    possible = false;
    break;
   }
   counter++;
  }
  
  if(possible)
   cout << "yes" << endl;
  else
   cout << "no" << endl;

 }
}


int main(void){
 int cases;
 cin >> cases;
 testQuad(cases);
}
