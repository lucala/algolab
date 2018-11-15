#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <cmath>
#include <stdlib.h>

using namespace std;

void test(int cases){
 for(int c=0; c < cases; c++){
  int n,m,v;
  cin >> n;
  cin >> m;
  vector<int> friends(n);
  map<int, int> books;
  for(int i=0; i<n; i++){
   cin >> v;
   friends[i] = v;
  }
  int heaviest = 0;
  for(int i=0; i<m; i++){
   cin >> v;
   books[v] += 1;
   if(v > heaviest)
    heaviest = v;
  }

  //strongest friend first
  sort(friends.begin(), friends.end());
  reverse(friends.begin(), friends.end());

  //impossible
  if(friends[0] < heaviest){
   cout << "impossible" << endl;
   continue;
  }
  
  int b = m;
  int str;
  int counter = 0;
  while(b > 0){
   
   for(int i=0; i<n; i++){
    
    //greedy, take as many of the heaviest boxes as possible
    str = friends[i];
    while(str > 0){
     if(books[str] > 0){
      b--;
      books[str] -= 1;
      break;
     }else
      str--;
    }

   }
   
   if(b <= 0)
    counter += 2;
   else
    counter += 3;
  }

 cout << counter << endl;

 }
}


void testLin(int cases){
 for(int c=0; c < cases; c++){
  int n,m,v, counter = 0;
  cin >> n;
  cin >> m;
  vector<int> friends(n), books(m), boxes;
  for(int i=0; i<n; i++){
   cin >> v;
   friends[i] = v;
  }
  for(int i=0; i<m; i++){
   cin >> v;
   books[i] = v;
  }

  sort(books.begin(), books.end());
  reverse(books.begin(), books.end());
  sort(friends.begin(), friends.end());
  reverse(friends.begin(), friends.end());


  //impossible
  if(books[0] > friends[0]){
   cout << "impossible" << endl;
   continue;
  }
  

  int bound, curr, i, j;
  for(i=1; i<m; i++){
   if(books[i] != books[i-1])
    break;
  }
  for(j=1; j<n; j++){
   if(friends[j] < books[0])
    break;
  }


  bound = ceil(i/j);
  i = bound * j;

//test init
  i = 0;
  j = 0;
  bound = 1;

  while(i < m){

   curr = 0;
   while(j < n && friends[j] >= books[i]){
    curr++;
    j++;
   }

   if(curr == 0 && i < m){
    bound++;
    i += j;
   }


   i += curr*bound;

  }


  counter = bound*3 - 1;

  cout << counter << endl;

 }
}

int main(void){
 int cases;
 cin >> cases;
 //test(cases);
 testLin(cases);
}
