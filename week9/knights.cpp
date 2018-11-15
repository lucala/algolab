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
 int m,n,k,c;
 cin >> m >> n >> k >> c;

 Graph G(2*m*n+2);

 EdgeCapacityMap capacitymap = get(edge_capacity, G);
 ReverseEdgeMap revedgemap = get(edge_reverse, G);
 ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
 EdgeAdder eaG(G, capacitymap, revedgemap);
 
 int sink = 2*m*n+1;
 int source = 2*m*n;

 int resMust=0;
 int offset = m*n;
 //fill graph
 for(int i=0; i<m; i++){
  for(int j=0; j<n; j++){
   int locOffset = i+m*j;
   //connection
   eaG.addEdge(locOffset, offset+locOffset, c);
   //outgoing
   if(i>0) eaG.addEdge(offset+locOffset,i-1+m*j,1);
   if(j>0) eaG.addEdge(offset+locOffset,i+(j-1)*m,1);
   if(i<m-1) eaG.addEdge(offset+locOffset,i+1+m*j,1);
   if(j<n-1) eaG.addEdge(offset+locOffset,i+(j+1)*m,1);
   //sink
   if((i==0&&j==0)||(i==0&&j==(n-1))||(i==(m-1)&&j==0)||(i==(m-1)&&j==(n-1)))
    eaG.addEdge(offset+locOffset, sink, 2);
   else if(i == 0 || i == (m-1) || j == 0 || j == (n-1))
    eaG.addEdge(offset+locOffset, sink, 1);
  }
 }

 //add source
 int tmpx, tmpy;
 for(int i=0; i<k; i++){
  cin >> tmpx >> tmpy;
  eaG.addEdge(source, tmpx + m*tmpy, 1);
 }


 long flow = push_relabel_max_flow(G, source, sink);
 cout << flow << endl;
 

}


int main(){
 int n;
 cin >> n;
 while(n--) test();
}
