#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <climits>
#include <cassert>


using namespace std;

int rec(vector<vector<int> > &matrix, vector<int> &coins, int i, int j){
//cout << "being called with i=" << i << " and j=" << j << endl;
 if(i==j){
  //one coin remains
  return coins[i];
 }

 if(matrix[i][j] > 0){
  //already computed
  return matrix[i][j];
 }

 

 if(j-i <= 2){
   //pick i or j, whichever is greater, since opponent will pick middle one or leftover
   int tmpMoney;
   if(j-i == 2){
    tmpMoney = max(coins[i],coins[j]) + min(coins[i+1],min(coins[i],coins[j]));
   }else{
    tmpMoney = max(coins[i],coins[j]);
   }
   matrix[i][j] = tmpMoney;
   return tmpMoney;
 }

 //choose max of taking left coin or taking right coin, depending on future events discovered with rec
 int money = max(coins[i]+min(rec(matrix, coins, i+1, j-1),rec(matrix,coins, i+2, j)), coins[j]+min(rec(matrix,coins,i,j-2),rec(matrix,coins,i+1,j-1)));
 matrix[i][j] = money;
 return money;

}

void test(){
 int n;
 cin >> n;
 vector<int> coins(n);
 for(int i=0; i<n; i++){
  cin >> coins[i];
 }

 vector<vector<int> > matrix(n+1, vector<int>(n+1));
 cout << rec(matrix, coins, 0, n-1) << endl;
/*
for(int i=0;i<n+1;i++){
for(int j=0;j<n+1;j++){
cout << matrix[i][j] << " ";
}
cout << endl;
}
*/

}


int main(){
 std::ios_base::sync_with_stdio(false);
 int n;
 cin >> n;
 while(n--) test();
}
