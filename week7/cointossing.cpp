#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <climits>
#include <cassert>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property, property<edge_capacity_t, long, property<edge_residual_capacity_t, long, property<edge_reverse_t, Traits::edge_descriptor> > > > Graph;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef property_map<Graph, edge_capacity_t>::type EdgeCapacityMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type ReverseEdgeMap;

class EdgeAdder{
 Graph &G;
 EdgeCapacityMap &capacitymap;
 ReverseEdgeMap &revedgemap;

public:
 EdgeAdder(Graph & G, EdgeCapacityMap &capacitymap, ReverseEdgeMap &revedgemap): G(G), capacitymap(capacitymap), revedgemap(revedgemap){}

 void addEdge(int from, int to, long capacity){
  Edge e, reverseE;
  bool success;
  tie(e,success) = add_edge(from, to, G);
  tie(reverseE, success) = add_edge(to, from, G);
  capacitymap[e] = capacity;
  capacitymap[reverseE] = 0;
  revedgemap[e] = reverseE;
  revedgemap[reverseE] = e;
 }
};




void test(){
 int n,m,a,b,c;
 cin >> n >> m;

 Graph G(n+m+2);

 EdgeCapacityMap capacitymap = get(edge_capacity, G);
 ReverseEdgeMap revedgemap = get(edge_reverse, G);
 ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
 EdgeAdder eaG(G, capacitymap, revedgemap);
 
 //fill graph //first m are games, second n are players
 for(int i=n; i<m+n; i++){
  cin >> a >> b >> c;
  if(c == 1)
   eaG.addEdge(i, a, 1);
  else if(c == 2)
   eaG.addEdge(i, b, 1);
  else{
   eaG.addEdge(i, a, 1);
   eaG.addEdge(i, b, 1);
  }
 }

 Vertex src = add_vertex(G);
 Vertex sink = add_vertex(G);
 for(int i = n; i<m+n; i++){
  eaG.addEdge(src, i, 1);
 }

 int val, resMust=0;
 for(int i = 0; i<n; i++){
  cin >> val;
  resMust += val;
  eaG.addEdge(i, sink, val);
 }

 long flow = push_relabel_max_flow(G, src, sink);
 //for(int i=0; i<n; i++){
 // if(edge_capacity
 //}
 if(flow == resMust && resMust == m)
  cout << "yes" << endl;
 else
  cout << "no" << endl;
 

}


int main(){
 int n;
 cin >> n;
 while(n--) test();
}
