#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <set>
#include <stdlib.h>

using namespace std;

class myComparator
{
public:
 bool operator() (pair<int,int> lhs, pair<int,int> rhs)
 {
  return (lhs.first > rhs.first);
 }
};

void test(int cases){
 for(int c=0; c < cases; c++){
  int nrWords,m,v;
  cin >> nrWords;
  vector<int> words(nrWords);
  for(int i=0; i<nrWords; i++){
   cin >> m;
   words[i] = m;
  }

//pair.first = position of word, pair.second = ith word
  priority_queue<pair<int,int>, vector<pair<int,int> >, myComparator> prioQueue;

  for(int i=0; i<nrWords; i++){
   m = words[i];
   for(int j=0; j<m; j++){
    cin >> v;
    prioQueue.push(make_pair(v,i));
   }
  }
  //cin >> m; //NO, M IN USE
  
  int count=0;
  vector<int> pole(nrWords, -1);
  pair<int, int> curr;
  while(count < nrWords && !prioQueue.empty()){
   curr = prioQueue.top();
   prioQueue.pop();
   if(pole[curr.second] == -1)
    count++;
   
   pole[curr.second] = curr.first;
  }

  set<pair<int,int> > distanceSet;
  for(int i=0; i<nrWords; i++){
   distanceSet.insert(make_pair(pole[i],i));
  }

  int bestDistance = (--distanceSet.end())->first - distanceSet.begin()->first + 1;
  int distance;
  while(!prioQueue.empty()){
   curr = prioQueue.top();
   prioQueue.pop();
   distanceSet.erase(make_pair(pole[curr.second], curr.second));
   pole[curr.second] = curr.first;
   distanceSet.insert(curr);
   
   distance = (--distanceSet.end())->first - distanceSet.begin()->first + 1;
   if (distance < bestDistance)
    bestDistance = distance;

  }
  
  cout << bestDistance << endl;

 }
}



int main(void){
 std::ios_base::sync_with_stdio(false);
 int cases;
 cin >> cases;
 test(cases);
}
