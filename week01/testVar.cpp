#include <iostream>
#include <vector>

using namespace std;

int main(void){
 int n,c = 5;
 vector<bool> bo(c,true);
 vector<bool> bo2(c,false);
 bo2[4] = true;
 bo = bo & bo2;
 cout << bo[4] << endl;
 cout << bo[3] << endl;
 
}
