#include <iostream>
#include <tuple>
#include <queue>
#include <stdlib.h>

using namespace std;

class myComparator
{
public:
 bool operator() (tuple<int,int,int> lhs, tuple<int,int,int> rhs)
 {
  return (get<2>(lhs) > get<2>(rhs) || (get<2>(lhs) == get<2>(rhs) && get<0>(lhs) > get<0>(rhs)));
 }
};

void test(int cases){
 for(int c=0; c < cases; c++){
  int nrBoats,m,v;
  cin >> nrBoats;


//first = position of pole, second = length of boat, third = min pos boat takes up
  priority_queue<tuple<int,int,int>, vector<tuple<int,int,int> >, myComparator> prioQueue;

  for(int i=0; i<nrBoats; i++){
   cin >> m;
   cin >> v;
   prioQueue.push(make_tuple(v,m,v));
  }



  int counter = 1, boatLen, boatPolePos, minEndPos;
  int currPos = get<0>(prioQueue.top());
  prioQueue.pop();
  tuple<int,int,int> currBoat;

  while(!prioQueue.empty()){
   currBoat = prioQueue.top();
   prioQueue.pop();
   boatLen = get<1>(currBoat);
   boatPolePos = get<0>(currBoat);
   minEndPos = get<2>(currBoat);

   if(boatLen <= minEndPos-currPos){
    counter++;
    currPos = minEndPos;
   }else if(currPos <= boatPolePos){
    currBoat = make_tuple(boatPolePos,boatLen,currPos+boatLen);
    prioQueue.push(currBoat);
   }

  }
  
  cout << counter << endl;

 }
}



int main(void){
 int cases;
 cin >> cases;
 test(cases);
}
