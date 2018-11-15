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
 int n,m,l,x,y,p;
 cin >> n >> m >> l;

 Graph G(n);
 EdgeCapacityMap capacitymap = get(edge_capacity, G);
 EdgeWeightMap weightmap = get(edge_weight, G);
 ReverseEdgeMap revedgemap = get(edge_reverse, G);
 ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
 EdgeAdder eaG(G, capacitymap, weightmap, revedgemap);

 vector<int> x_pos, y_pos, priority;
 int biggestPrio = 0;
 for(int i=0; i<m; i++){
  cin >> x >> y >> p;
  x_pos.push_back(x);
  y_pos.push_back(y);
  priority.push_back(-p);
  if(p > biggestPrio)
   biggestPrio = p;
 } 
 
 for(int i=0; i<m; i++){
  priority[i]+=biggestPrio*(y_pos[i]-x_pos[i]);
 }
 
 const int src = n;
 const int sink = n+1;

 for(int i=0; i<n-1; i++){
  eaG.addEdge(i,i+1,l,biggestPrio);
 }

 eaG.addEdge(src,0,l,0);
 eaG.addEdge(n-1,sink,l,0);

 for(int i=0; i<m; i++){
  eaG.addEdge(x_pos[i], y_pos[i],1,priority[i]);
 }
 
 successive_shortest_path_nonnegative_weights(G, src, sink);
 int cost = find_flow_cost(G);
 int flow = 0;
 

 EdgeIt e, eend;
 for(tie(e, eend) = edges(G); e != eend; ++e) {
  Vertex v = target(*e, G), u = source(*e, G);
  if(rescapacitymap[*e] == 0 && u != src && v != sink && u < v){
   flow += (weightmap[*e]-biggestPrio*(v-u))*(-1);
//cout << "max flow passes through " << u << " & " << v << " with residual " << rescapacitymap[*e] << " weights " << weightmap[*e] << endl;
  }
 }

 
 

 cout << flow << endl;

}


int main(){
 int t;
 cin >> t;
 while(t--) test();
}
