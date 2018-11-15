#include <iostream>
#include <cstdlib>

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
 int n,a,c,s,p,v,e;
 cin >> n;

 Graph G(n+2);
 EdgeCapacityMap capacitymap = get(edge_capacity, G);
 EdgeWeightMap weightmap = get(edge_weight, G);
 ReverseEdgeMap revedgemap = get(edge_reverse, G);
 ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
 EdgeAdder eaG(G, capacitymap, weightmap, revedgemap);

 vector<int> nrMenu, menuCost, nrStudents, uniCost, menuStoring, storingCost, uniCostAdapted;
 int maxCost = 0;
 for(int i=0; i<n; i++){
  cin >> a >> c;
  nrMenu.push_back(a);
  menuCost.push_back(c);
 } 
 
 int totalStudents = 0;
 for(int i=0; i<n; i++){
  cin >> s >> p;
  totalStudents += s;
  nrStudents.push_back(s);
  uniCost.push_back(p);
  if(p > maxCost)
   maxCost = p;
 }

 
 for(int i=0; i<n; i++){
  uniCostAdapted.push_back(-uniCost[i]+maxCost);
 }

 for(int i=0; i<n-1; i++){
  cin >> v >> e;
  menuStoring.push_back(v);
  storingCost.push_back(e);
 }
 
 const int src = n;
 const int sink = n+1;

 for(int i=0; i<n-1; i++){
  eaG.addEdge(i,i+1,menuStoring[i],storingCost[i]);
 }

 for(int i=0; i<n; i++){
  eaG.addEdge(src, i, nrMenu[i], menuCost[i]);
 }
 
 for(int i=0; i<n; i++){
  eaG.addEdge(i, sink, nrStudents[i], uniCostAdapted[i]);
 }

 successive_shortest_path_nonnegative_weights(G, src, sink);
 //int cost = find_flow_cost(G);
 int cost = 0;
 int flow = 0;

 OutEdgeIt e1, eend;
 for(tie(e1, eend) = out_edges(vertex(src,G), G); e1 != eend; ++e1){
  flow += capacitymap[*e1] - rescapacitymap[*e1];
 }

 if(flow == totalStudents)
  cout << "possible ";
 else
  cout << "impossible ";

 cout << flow << " ";

 EdgeIt e2, eend2;
 for(tie(e2, eend2) = edges(G); e2 != eend2; ++e2) {
  Vertex v = target(*e2, G), u = source(*e2, G);
  int currFlow = capacitymap[*e2] - rescapacitymap[*e2];
  if(u != src && v != sink && u < v && u != sink && v != src){
   cost -= weightmap[*e2]*currFlow;
  }
  else if(u == src){
   cost -= weightmap[*e2]*currFlow;
  }
  else if(v == sink){
   cost += uniCost[u]*currFlow;
  }
 }

 
 

 cout << cost << endl;

}


int main(){
 int t;
 cin >> t;
 while(t--) test();
}
