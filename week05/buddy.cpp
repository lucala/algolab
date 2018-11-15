#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <set>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS> Graph;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::vertex_descriptor Vertex;


void test(){
 int n, c, f;
 string str;
 cin >> n >> c >> f;
 
 vector<set<string> > chars(n);
 for(int i=0; i < n; i++){
  set<string> tmpSet;
  for(int j=0; j<c; j++){
   cin >> str;
   tmpSet.insert(str);
  }
  chars[i] = tmpSet;
 }
 
 //create empty graph
 Graph G(n);

 //match students
 for(int i=0; i<n; i++){
  for(int j=0; j<i; j++){
   vector<string> tmp;
   set_intersection(chars[i].begin(), chars[i].end(), chars[j].begin(), chars[j].end(), back_inserter(tmp));
   if(f < tmp.size()){
    //create edge between i and j
    Edge e; bool success;
    tie(e, success) = add_edge(i,j,G);
   }
  }
 }

 //maximum cardinality matching
 vector<Vertex> matemap(n);
 edmonds_maximum_cardinality_matching(G, make_iterator_property_map(matemap.begin(),get(vertex_index,G)));
 int matchingSize = matching_size(G, make_iterator_property_map(matemap.begin(), get(vertex_index, G)));

 if(n-2*matchingSize == 0)
  cout << "not optimal" << endl;
 else
  cout << "optimal" << endl;
 

}


int main(){
 int n;
 cin >> n;
 while(n--) test();
}
