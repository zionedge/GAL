#include <ogdf/basic/Graph_d.h>
#include <ogdf/basic/EdgeArray.h>
#include <ogdf/graphalg/MinimumCut.h>

int StoerWagnerAlgorithm(ogdf::Graph graph) {
    int min_cut;

    ogdf::EdgeArray<double> arr = ogdf::EdgeArray<double> (graph, 1.0);

    ogdf::MinCut cut = ogdf::MinCut(graph, arr);

    return cut.minimumCut();
}