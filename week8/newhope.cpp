#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <climits>

using namespace std;

class Stormtrooper{
 int station;
 int unit;
 vector<pair<int,int> > supervises; //1. int station, 2. int unit
 //Stormtrooper(int station, int unit, vector<pair<int,int> > supervises): station(station), unit(unit), supervises(supervises) {}

}

int rec(bool mc, int center, int unit, vector<vector<Stormtrooper> > &troops){
 if(mc && troops[center][unit].supervise.isEmpty())
  return 1;
 if(!mc && troops[center][unit].supervise.isEmpty())
  return 0;

 Stormtrooper curr = troops[center][unit];
 vector<pair<int,int> >::iterator it;
 for(it = curr.supervise.begin(); it != curr.supervise.end(); it++){
  
 }
 
}

void test(){
 int k,s,m,u,v,h,x,y;
 cin >> k >> s >> m;
 

 vector<vector<Stormtrooper> > troops(k, vector<Stormtrooper>(s), -1);
 for(int i=0; i<m; i++){
  cin >> u >> v >> h;
  for(int j=0; j<2*h; j+=2){
   cin >> x >> y;
   troops[u][x].supervises.append(make_pair(v,y));
  }
 }

 //go through all troops in C_0 and call recursion
 int val = 0, best = 0;
 for(int i=0; i<s; i++){
  val = max(rec(true, 0, i, troops), rec(false, 0, i, troops));
  if(val > best)
   best = val;
 }

 cout << best << endl;

}


int main(){
 int n;
 cin >> n;
 while(n--) test();
}
