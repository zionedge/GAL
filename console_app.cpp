#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string>
#include <vector>
#include <filesystem>
#include <chrono>

//OGDF
#include <ogdf/basic/graph_generators.h>
#include <ogdf/basic/Graph_d.h>
#include <ogdf/fileformats/GraphIO.h>

//files
#include "stoer_wagner.hpp"
#include "karger.hpp"
#include "min_cut_tree.hpp"


using namespace std;

struct WeightedGraph {
  ogdf::Graph Gr;
  vector<double> weights;
  std::string graphName;
  
  WeightedGraph(ogdf::Graph G, vector<double> arr) : Gr(G), weights(arr) {}
};


void GetMinCutStoerWagner(vector<WeightedGraph> graphs) {
    double cut;
    for (WeightedGraph G : graphs) {
        ogdf::EdgeArray<double> EA(G.Gr);
        int i = 0;
        for(ogdf::edge e : G.Gr.edges){
          EA[e] = G.weights[i];
          i++;
        }        
        auto start = chrono::high_resolution_clock::now();
        cut = StoerWagnerAlgorithm(G.Gr,EA);
        auto stop = chrono::high_resolution_clock::now();

        chrono::duration<double> duration = (stop - start) * 1000;

        cout << "Graph name: " << G.graphName << " StoerWagner MinCut is: " << cut << ", Duration was: "<< duration.count() << "ms" << endl;
    }
}

void GetMinCutMinCutTree(vector<WeightedGraph> graphs) {
    double cut;
    for (WeightedGraph G : graphs) {
        ogdf::EdgeArray<double> EA(G.Gr);
        int i = 0;
        for(ogdf::edge e : G.Gr.edges){
          EA[e] = G.weights[i];
          i++;
        }
        auto start = chrono::high_resolution_clock::now();
        cut = minCutTreeAlgorithm(G.Gr,EA);
        auto stop = chrono::high_resolution_clock::now();

        chrono::duration<double> duration = (stop - start) * 1000;

        cout << "Graph name: " << G.graphName << " MinCutTree MinCut is: " << cut << ", Duration was: "<< duration.count() << "ms" << endl;
    }    
}

void GetMinCutKarger(vector<WeightedGraph> graphs) {
    double cut;
    for (WeightedGraph G : graphs) {
        ogdf::EdgeArray<double> EA(G.Gr);
        int i = 0;
        for(ogdf::edge e : G.Gr.edges){
          EA[e] = G.weights[i];
          i++;
        }   
        auto start = chrono::high_resolution_clock::now();
        cut = KargerApproximation(G.Gr, EA);
        auto stop = chrono::high_resolution_clock::now();

        chrono::duration<double> duration = (stop - start) * 1000;

        cout << "Graph name: " << G.graphName << " Karger MinCut is: " << cut << ", Duration was: "<< duration.count() << "ms" << endl;
    }
}

vector<WeightedGraph> GetGraphsFromFile(string filename, bool weight) {
    fstream GraphGetter(filename);
    string Line;
    vector<WeightedGraph> Graphs;

    for(const auto & entry : filesystem::directory_iterator(filename)) {
        //cout << entry.path() << endl;
        ogdf::Graph G;

        ogdf::GraphAttributes GA(G,
        ogdf::GraphAttributes::nodeGraphics |
        ogdf::GraphAttributes::edgeGraphics |
        ogdf::GraphAttributes::nodeLabel |
        ogdf::GraphAttributes::edgeStyle |
        ogdf::GraphAttributes::nodeStyle |
        ogdf::GraphAttributes::nodeTemplate);

        if (!ogdf::GraphIO::read(GA, G, entry.path(), ogdf::GraphIO::readGML)) {
            cerr << "Could not load file!" << endl;
            exit (1);
        }
        vector<double> weights;
        for(ogdf::edge e : G.edges) {
          if(weight){
            weights.push_back(ogdf::randomDouble(1.0,300.0));
          } else {
            weights.push_back(1.0);
          }
        }
        WeightedGraph WG(G,weights);
        WG.graphName = entry.path().filename().string();
        //cout<< entry.path() << endl;
        Graphs.push_back(WG);     
    }

    return Graphs;
}


int main (int argc, char * argv[]) {

    int input = 0;
    string u_input, graphs_file;
    auto time = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    ogdf::setSeed(time);

    
    cout << "GAL console application\nMinimum cut in graph" << endl;
    cout << "Algorithms in this app:\n 1) Stoer-Wagner algorithm\n 2) MinCutTree Aproximation Algorithm\n 3) Karger apporximation algorithm" << endl;

    cout << "You can specify a directory with graph files and choose which algorithm to use" << endl;
    

    cout << "Please input the directory: ";
    cin >> graphs_file;
    
    cout << "Please choose the algorithm (type 1, 2, 3, 4(use all) or 5(use all with random edge weight)): "; 
    while (!input) {
        cin >> u_input;
        try{
            input = stoi(u_input);
        }
        catch(const std::exception& e){
            cerr << "stoi Bad choice! Please pick 1, 2, 3, 4 or 5: ";
            continue;
        }
        if (!(input == 1 || input == 2 || input == 3 || input == 4 || input == 5)) {
            cerr << "Bad choice! Please pick 1, 2, 3, 4 or 5: ";
            input = 0;
        }
    }

    //TODO Get graphs from file
    vector<WeightedGraph> graphs;
    if(input==5){   
      graphs = GetGraphsFromFile(graphs_file, true);
    } else {
      graphs = GetGraphsFromFile(graphs_file, false);
    }
    switch (input)
    {
    case 1:
        /* Stoer-Wagner*/
        GetMinCutStoerWagner(graphs);
        break;


    case 2:
        /* MinCutTree */
        GetMinCutMinCutTree(graphs);
        break;

    case 3:
        /* Karger */
        GetMinCutKarger(graphs);
        break;
    case 4:
    case 5:
        std::cout << "-- Starting StoerWagnerMinCut --" << std::endl;
        GetMinCutStoerWagner(graphs);
        std::cout << "-- End Of StoerWagnerMinCut --" << std::endl;
        std::cout << "-- Starting MinCutTree --" << std::endl;
        GetMinCutMinCutTree(graphs);
        std::cout << "-- End Of MinCutTree --" << std::endl;
        std::cout << "-- Starting KargerMinCut --" << std::endl;
        GetMinCutKarger(graphs);
        std::cout << "-- End Of KargerMinCut --" << std::endl;
        break;
    default:
        break;
    }

    return 0;
}