#include <ogdf/basic/graph_generators.h>
#include <ogdf/basic/Graph_d.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>

#include <ogdf/fileformats/GraphIO.h>
#include <ogdf/basic/GraphCopy.h>

using namespace std;

double ComputeT (int count) {
    
    int k = 2;
    int n = count;
    
    if (k > n) return 0;
    if (k * 2 > n) k = n-k;
    if (k == 0) return 1;

    double comb_number = n;
    for( int i = 2; i <= k; ++i ) {
        comb_number *= (n-i+1);
        comb_number /= i;
    }
    
    double ret = (comb_number * log(count))> 1.0e+4 ? count/2 : comb_number * log(count);
    return ret;
}

double KargerApproximation(ogdf::Graph &G, ogdf::EdgeArray<double> &arr) {

    double minWeight = 3.40282e+10;
    double weight = 0.0;
    ogdf::EdgeArray<double> cpArr(arr);
    int verticies_count = G.numberOfNodes();

    //number of repetitions to find optimal solution
    double repetitions = ComputeT(verticies_count);
    //std::cout << "Reps " << repetitions << " count: " << verticies_count <<  "\n";
    for (int i = 0; i < (int) repetitions; i++) {
        ogdf::Graph GI = G;
        while (GI.numberOfNodes() > 2) {
            ogdf::edge e = GI.chooseEdge();
            ogdf::node minValNode = e->source();
            ogdf::node otherNode = e->target();
            ogdf::adjEntry adj = minValNode->firstAdj();
            while (adj != nullptr) {
              ogdf::adjEntry succ = adj->succ();
              
              ogdf::edge e = adj->theEdge();
          		if (e->source() == otherNode || e->target() == otherNode) {
          			GI.delEdge(e);
          		}
          		else if (e->source() == minValNode) {
          			GI.moveSource(e,otherNode);
          		}
          		else {
          			GI.moveTarget(e,otherNode);
          		}
              adj = succ;
            }
            GI.delNode(minValNode);
            
            ogdf::NodeArray<ogdf::List<ogdf::edge> > adjNodes(GI);
            
           	for(ogdf::adjEntry adjT : otherNode->adjEntries) {
        		  adjNodes[adjT->twinNode()].pushBack(adjT->theEdge());
        	  }
        
          	ogdf::node nd = GI.firstNode();
          	while (nd!=nullptr) {
          		if (adjNodes[nd].size() > 1) {
          			ogdf::edge e = adjNodes[nd].front();
          			adjNodes[nd].popFront();
          			for (ogdf::edge ei : adjNodes[nd]) {
          				cpArr[e] += cpArr[ei];
          				GI.delEdge(ei);
          			}
          		}
          		nd = nd->succ();
          	}
        }
        weight = 0.0;
        for(ogdf::edge e : GI.edges) {
          weight += cpArr[e];
        }
        if(weight < minWeight){
          minWeight = weight;
        }  
    }

    return minWeight;
}
