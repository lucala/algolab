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
 int n,m,s;
 cin >> n >> m >> s;

 Graph G(n+2);

 EdgeCapacityMap capacitymap = get(edge_capacity, G);
 ReverseEdgeMap revedgemap = get(edge_reverse, G);
 ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
 EdgeAdder eaG(G, capacitymap, revedgemap);
 
 vector<int> storeLoc(s);
 //store locations
 for(int i=0; i<s; i++){
  cin >> storeLoc[i];
 }

 int st, en;
 //fill graph
 for(int i=0; i<m; i++){
  cin >> st >> en;
  eaG.addEdge(st, en, 1);
  eaG.addEdge(en, st, 1);
 }

 Vertex src = add_vertex(G);
 Vertex sink = add_vertex(G);
 eaG.addEdge(src, 0, s);


 int val, resMust=0;
 for(int i = 0; i<s; i++){
  eaG.addEdge(storeLoc[i], sink, 1);
 }

 long flow = push_relabel_max_flow(G, src, sink);

 if(flow == s)
  cout << "yes" << endl;
 else
  cout << "no" << endl;
 

}


int main(){
 int n;
 cin >> n;
 while(n--) test();
}
