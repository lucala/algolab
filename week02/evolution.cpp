#include <iostream>
#include <tuple>
#include <queue>
#include <unordered_map>
#include <stdlib.h>
#include <tuple>

using namespace std;


class myComparator
{
public:
 bool operator() (tuple<string,int,int> lhs, tuple<string,int,int> rhs)
 {
  return (get<1>(lhs) > get<1>(rhs));
 }
};

void test(int cases){
 for(int c=0; c < cases; c++){
  int nrSpecies,nrQueries,v, maxAge;
  string str1, str2, name;
  cin >> nrSpecies;
  cin >> nrQueries;

  unordered_map<string, int> species;
  unordered_map<string, string> ancestor;

  for(int i=0; i<nrSpecies; i++){
   cin >> str1;
   cin >> v;
   species[str1] = v;
  }

  for(int i=0; i<nrSpecies-1; i++){
   cin >> str1;
   cin >> str2;
   ancestor[str1] = str2;
  }

  string anc;
  for(int i=0; i<nrQueries; i++){
   cin >> name;
   cin >> maxAge;
//cout << "query for " << name << " and max age " << maxAge << endl;
   anc = name;
   while(species[ancestor[anc]] <= maxAge && ancestor[anc] != ""){
//cout << "working .. " << anc << " ancestor with age " << species[ancestor[anc]] << " species[anc]=" << species[anc] << endl;
    anc = ancestor[anc];
   }

  cout << anc << " ";
 
  }

 cout << endl;

 }
}



//------------------------


void testLin(int cases){
 for(int c=0; c < cases; c++){
  int nrSpecies,nrQueries,v, maxAge;
  string str1, str2, name;
  cin >> nrSpecies;
  cin >> nrQueries;

  unordered_map<string, int> species;
  unordered_map<string, string> ancestor;

  for(int i=0; i<nrSpecies; i++){
   cin >> str1;
   cin >> v;
   species[str1] = v;
  }

  for(int i=0; i<nrSpecies-1; i++){
   cin >> str1;
   cin >> str2;
   ancestor[str1] = str2;
  }

  string anc;
  priority_queue<tuple<string, int, int>, vector<tuple<string, int, int> >, myComparator > prioQ;
  vector<string> queries(nrQueries);
  for(int i=0; i<nrQueries; i++){
   cin >> name;
   cin >> maxAge;
   prioQ.push(make_tuple(name, maxAge, i));
 //cout << "reading in queries... top query-> " << get<0>(prioQ.top()) << " " << get<1>(prioQ.top())  << " " << get<2>(prioQ.top()) << endl;
  }

  tuple<string, int, int> curr;
  queue<string> reAlloc;
  string tmp;
  while(!prioQ.empty()){
   curr = prioQ.top();
   prioQ.pop();
   anc = get<0>(curr);
   maxAge = get<1>(curr);
//cout << "query for " << anc << " and max age " << get<1>(curr) << endl;
   while(species[ancestor[anc]] <= maxAge && ancestor[anc] != ""){
    reAlloc.push(anc);
//cout << "pushing " << anc << " into reAlloc, ";
    anc = ancestor[anc];
//cout << "ancestor is " << anc << endl;
   }

   //top el. will be new ancestor of rest of el.
   if(!reAlloc.empty())
    reAlloc.pop();
   while(!reAlloc.empty()){
    tmp = reAlloc.front();
    reAlloc.pop();
    ancestor[tmp] = anc;
   }

   queries[get<2>(curr)] = anc;
  }


 for(int i=0; i<nrQueries; i++){
  cout << queries[i] << " ";
 }

 cout << endl;

 }
}




int main(void){
 std::ios_base::sync_with_stdio(false);
 int cases;
 cin >> cases;
//cout << "this many cases! " << cases << endl;
 //test(cases);
 testLin(cases);
}
