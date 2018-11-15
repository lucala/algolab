#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <algorithm>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>


using namespace boost;
using namespace std;

typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
    property<edge_capacity_t, long,
        property<edge_residual_capacity_t, long,
            property<edge_reverse_t, Traits::edge_descriptor,
                property <edge_weight_t, long> > > > > Graph;

typedef property_map<Graph, edge_capacity_t>::type      EdgeCapacityMap;
typedef property_map<Graph, edge_weight_t >::type       EdgeWeightMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type       ReverseEdgeMap;
typedef graph_traits<Graph>::vertex_descriptor          Vertex;
typedef graph_traits<Graph>::edge_descriptor            Edge;
typedef graph_traits<Graph>::edge_iterator EdgeIt;
typedef graph_traits<Graph>::out_edge_iterator  OutEdgeIt; // Iterator

class EdgeAdder {
    Graph &G;
    EdgeCapacityMap &capacitymap;
    EdgeWeightMap &weightmap;
    ReverseEdgeMap  &revedgemap;

public:
    EdgeAdder(Graph & G, EdgeCapacityMap &capacitymap, EdgeWeightMap &weightmap, ReverseEdgeMap &revedgemap) 
        : G(G), capacitymap(capacitymap), weightmap(weightmap), revedgemap(revedgemap) {}

    void addEdge(int u, int v, long c, long w) {
        Edge e, reverseE;
        tie(e, tuples::ignore) = add_edge(u, v, G);
        tie(reverseE, tuples::ignore) = add_edge(v, u, G);
        capacitymap[e] = c;
        weightmap[e] = w;
        capacitymap[reverseE] = 0;
        weightmap[reverseE] = -w;
        revedgemap[e] = reverseE; 
        revedgemap[reverseE] = e; 
    }
};

void test(){
 int g,s,l,tmpL, tmpR;
 cin >> g >> s >> l;

 Graph G(g+s+2);
 EdgeCapacityMap capacitymap = get(edge_capacity, G);
 EdgeWeightMap weightmap = get(edge_weight, G);
 ReverseEdgeMap revedgemap = get(edge_reverse, G);
 ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
 EdgeAdder eaG(G, capacitymap, weightmap, revedgemap);

 const int src = g+s;
 const int sink = g+s+1;

 //ground 0 - (g-1), satellite g - (g+s-1)
 for(int i=0; i<l; i++){
  cin >> tmpL >> tmpR;
  eaG.addEdge(tmpL, tmpR+g, 1, 0);
 } 

 for(int i=0; i<g; i++){
  eaG.addEdge(src, i, 1, 0);
 }

 for(int i=0; i<s; i++){
  eaG.addEdge(i+g, sink, 1, 0);
 }

 successive_shortest_path_nonnegative_weights(G, src, sink); 

 //bfs
 vector<int> vis(g+s+2, false);
 std::queue<int> Q;
 vis[src] = true;
 Q.push(src);
 while(!Q.empty()){
  const int u = Q.front();
  Q.pop();
  OutEdgeIt ebeg, eend;
  for(tie(ebeg, eend) = out_edges(u,G); ebeg != eend; ++ebeg){
   const int v = target(*ebeg, G);
   if(rescapacitymap[*ebeg] == 0 || vis[v]) continue;
   vis[v] = true;
   Q.push(v);
  }
 }

 vector<int> tmpG, tmpS;
 for(int i=0; i<g; i++){
  if(vis[i]==false)
   tmpG.push_back(i);
 } 

 for(int i=0; i<s; i++){
  if(vis[i+g]==true)
   tmpS.push_back(i);
 } 

 cout << tmpG.size() << " " << tmpS.size() << endl;

 for(int i=0; i<tmpG.size(); i++){
   cout << tmpG[i] << " ";
 } 

 for(int i=0; i<tmpS.size(); i++){
   cout << tmpS[i] << " ";
 } 

 cout << endl;
}


int main(){
 int t;
 cin >> t;
 while(t--) test();
}
