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


using namespace std;

void GetMinCutStoerWagner(vector<ogdf::Graph> graphs) {
    int cut;
    for (ogdf::Graph G : graphs) {
        
        auto start = chrono::high_resolution_clock::now();
        cut = StoerWagnerAlgorithm(G);
        auto stop = chrono::high_resolution_clock::now();

        chrono::duration<double> duration = (stop - start) * 1000;

        cout << "Graph StoerWagner MinCut is: " << cut << ", Duration was: "<< duration.count() << "ms" << endl;
    }
}

void GetMinCutMaxFlowMinCut() {
    
}

void GetMinCutKarger(vector<ogdf::Graph> graphs) {
    int cut;
    for (ogdf::Graph G : graphs) {
    
        auto start = chrono::high_resolution_clock::now();
        cut = KargerApproximation(G);
        auto stop = chrono::high_resolution_clock::now();

        chrono::duration<double> duration = (stop - start) * 1000;

        cout << "Graph Karger MinCut is: " << cut << ", Duration was: "<< duration.count() << "ms" << endl;
    }
}

vector<ogdf::Graph> GetGraphsFromFile(string filename) {
    fstream GraphGetter(filename);
    string Line;
    vector<ogdf::Graph> Graphs;

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
        cout<< entry.path() << endl;
        Graphs.push_back(G);     
    }

    return Graphs;
}


int main (int argc, char * argv[]) {

    int input = 0;
    string u_input, graphs_file;

    
    cout << "GAL console application\nMinimum cut in graph" << endl;
    cout << "Algorithms in this app:\n 1) Stoer-Wagner algorithm\n 2) MaxFlow MinCut Aproximation Algorithm 3) Karger apporximation algorithm" << endl;

    cout << "You can specify a directory with graph files and choose which algorithm to use" << endl;
    

    cout << "Please input the directory: ";
    cin >> graphs_file;
    
    cout << "Please choose the algorithm (type 1, 2 or 3): "; 
    while (!input) {
        cin >> u_input;
        try{
            input = stoi(u_input);
        }
        catch(const std::exception& e){
            cerr << "stoi Bad choice! Please pick 1, 2 or 3: ";
            continue;
        }
        if (!(input == 1 || input == 2 || input == 3)) {
            cerr << "Bad choice! Please pick 1, 2 or 3: ";
            input = 0;
        }
    }

    //TODO Get graphs from file   
    vector<ogdf::Graph> graphs = GetGraphsFromFile(graphs_file);

    switch (input)
    {
    case 1:
        /* Stoer-Wagner*/
        GetMinCutStoerWagner(graphs);
        break;


    case 2:
        /* MaxFlow MinCut */
        break;

    case 3:
        /* Karger */
        GetMinCutKarger(graphs);
        break;
    
    default:
        break;
    }

    return 0;
}