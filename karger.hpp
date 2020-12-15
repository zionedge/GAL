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

int fact(int n) {
    if ( n == 0 || n == 1) 
        return 1;
    else
        return n * fact(n-1);
}

double ComputeT (int count) {
    double comb_number = fact(count) / (fact(2) * fact(count - 2));

    return comb_number * log(count);
}

int KargerApproximation(ogdf::Graph G) {

    vector <ogdf::Graph> AproximatedGraphs;

    int edge_count = G.numberOfEdges();
    int verticies_count = G.numberOfNodes();

    //number of repetitions to find optimal solution
    double repetitions = ComputeT(verticies_count);

    for (int i = 0; i < (int) repetitions; i++) {
        ogdf::Graph GI = G;
        while (GI.numberOfNodes() > 2) {
            ogdf::edge e = GI.chooseEdge();
            GI.contract(e);
            /*
            cout << "Edge:" << e->source() << " " << e->target() << " with " << GI.numberOfEdges() << " " << GI.numberOfNodes() << endl;
            for (ogdf::node n : GI.nodes) {
                cout << n->index() << " ";
            }
            cout << endl;
            */
        }

        AproximatedGraphs.push_back(GI);
    }

    int min_cut = INT32_MAX;
    for (auto it = begin(AproximatedGraphs); it != end(AproximatedGraphs); ++it) {
        if (it->numberOfEdges() < min_cut) {
            min_cut = it->numberOfEdges();
        }
    }

    return min_cut;
}
