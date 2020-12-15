#include <ogdf/basic/graph_generators.h>
#include <ogdf/basic/Graph_d.h>
#include <unistd.h>
#include <iostream>
#include <fstream>

#include <ogdf/fileformats/GraphIO.h>

using namespace std;

int main(int argc, char *argv[]) {
    int opt,edges = 0, vertices = 0, fromFile = 0;
    char* inputPath;
    ogdf::setSeed((unsigned int)std::time(NULL));

    while ((opt = getopt(argc,argv,"e:v:i:")) != -1){
    switch (opt) {
    case 'e':
      edges = atoi(optarg);
      break;
    case 'v':
      vertices = atoi(optarg);
      break;
    case 'i':
      fromFile = 1;
      inputPath = optarg;
      break;
    default:
      fprintf(stderr, "Usage: %s [-d] [-e numOfEdges] [-v numOfVertices] [-i InPATH] [-o OutPATH]\n", argv[0]);
      return 1;
      break;
        }
    }

    

    if(fromFile == 0) {
        ogdf::Graph G;
        if(edges!=0 && vertices!=0){
            cout << vertices << " " << edges << endl;
            if(!ogdf::randomSimpleConnectedGraph(G, vertices, edges)) {
                cout << "true" << endl;
            }
            cout << G.numberOfNodes() << endl;
        } else if(edges!=0){
            ogdf::randomSimpleConnectedGraph(G, ogdf::randomNumber(edges, 2*edges), edges);
        } else if(vertices!=0){
            ogdf::randomSimpleConnectedGraph(G, vertices, ogdf::randomNumber(vertices, 2*vertices));
        } else {
            vertices = ogdf::randomNumber(5,20);
            edges = ogdf::randomNumber(2*vertices, 3*vertices);
            ogdf::randomSimpleConnectedGraph(G, vertices, edges);
        }
        ogdf::GraphIO::write(G, "graphs/graph.gml",ogdf::GraphIO::writeGML);
    }
    else {
        ifstream MyReadFile(inputPath);
        string myText;
        int i = 0;
        string file;

        while (getline(MyReadFile, myText)) {
            char space(' ');
            vector<string> ve;
            istringstream ss(myText);
            for(string s; ss >> s;)
                ve.push_back(s);

            ogdf::Graph G;
            ogdf::randomSimpleConnectedGraph(G, stoi(ve[0]), stoi(ve[1]));
            file = "graphs/graph" + to_string(i);
            file = file + ".gml";
            i++;
            ogdf::GraphIO::write(G, file ,ogdf::GraphIO::writeGML);
        }
    }
}