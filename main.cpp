// base
#include <ogdf/basic/graph_generators.h>
#include <ogdf/basic/Graph_d.h>
#include <unistd.h>
#include <ctime>

// min cut
#include <ogdf/basic/EdgeArray.h>
#include <ogdf/graphalg/MinimumCut.h>

// graph drawing
#include <ogdf/basic/GraphAttributes.h>
#include <ogdf/fileformats/GraphIO.h>
#include <ogdf/layered/SugiyamaLayout.h>
#include <ogdf/layered/OptimalRanking.h>
#include <ogdf/layered/MedianHeuristic.h>
#include <ogdf/layered/OptimalHierarchyLayout.h>

int main(int argc, char *argv[]){

  int opt, directed = 0, edges = 0, vertices = 0, fromFile = 0, toFile = 0;
  char* inputPath;
  char* outputPath;
  ogdf::setSeed((unsigned int)std::time(NULL));
  
  while ((opt = getopt(argc,argv,"de:v:i:o:")) != -1){
    switch (opt) {
    case 'd':
      directed = 1;
      break;
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
    case 'o':
      toFile = 1;
      outputPath = optarg;
      break;
    default:
      fprintf(stderr, "Usage: %s [-d] [-e numOfEdges] [-v numOfVertices] [-i InPATH] [-o OutPATH]\n", argv[0]);
      return 1;
      break;
    }
  }
  
  ogdf::Graph G;
  if(edges!=0 && vertices!=0){
    ogdf::randomSimpleConnectedGraph(G, vertices, edges);
  } else if(edges!=0){
    ogdf::randomSimpleConnectedGraph(G, ogdf::randomNumber(edges, 2*edges), edges);
  } else if(vertices!=0){
    ogdf::randomSimpleConnectedGraph(G, vertices, ogdf::randomNumber(vertices, 2*vertices));
  } else {
    vertices = ogdf::randomNumber(5,20);
    edges = ogdf::randomNumber(2*vertices, 3*vertices);
    ogdf::randomSimpleConnectedGraph(G, vertices, edges);
  }
  
  ogdf::EdgeArray<double> arr = ogdf::EdgeArray<double>(G, 1.0);
  ogdf::MinCut cut = ogdf::MinCut(G, arr);
  
  // draw start
  ogdf::GraphAttributes GA( G, ogdf::GraphAttributes::nodeGraphics |
    ogdf::GraphAttributes::edgeGraphics |
    ogdf::GraphAttributes::nodeLabel |
    ogdf::GraphAttributes::nodeStyle |
    ogdf::GraphAttributes::edgeType |
    ogdf::GraphAttributes::edgeArrow |
    ogdf::GraphAttributes::edgeStyle |
    ogdf::GraphAttributes::edgeDoubleWeight |
    ogdf::GraphAttributes::edgeIntWeight );
    
  for(ogdf::node v : G.nodes){ // iterate through all the node in the graph
    GA.fillColor( v ) = ogdf::Color( "#FFFF00" ); // set node color to yellow
 
    GA.height( v ) = 20.0; // set the height to 20.0
    GA.width( v ) = 20.0; // set the width to 40.0
    GA.shape(v) = ogdf::Shape::Ellipse;
 
    std::string s = ogdf::to_string(v->index());
    char const *pchar = s.c_str(); //use char const* as target type
    GA.label( v ) = pchar;
  }
 
  for(ogdf::edge e : G.edges) // set default edge color and type
  {
    GA.bends(e);
    GA.arrowType(e) = ogdf::EdgeArrow::None;
    GA.strokeColor(e) = ogdf::Color("#0000FF");
    GA.doubleWeight(e) = 1.0;
    GA.intWeight(e) = 1;
  }
 
  ogdf::SugiyamaLayout SL; //Compute a hierarchical drawing of G (using SugiyamaLayout)
  SL.setRanking( new ogdf::OptimalRanking );
  SL.setCrossMin( new ogdf::MedianHeuristic );
  
  ogdf::OptimalHierarchyLayout *ohl = new ogdf::OptimalHierarchyLayout;
  SL.setLayout( ohl );
  SL.call( GA );
  
  std::filebuf fb;
  fb.open ("Output.svg",std::ios::out);
  std::ostream os(&fb);
    
  ogdf::GraphIO::drawSVG( GA, os);
  // draw end

  
  std::cout << "Edges: " << edges << " Vertices: " << vertices << "\n";
  std::cout << "MinCut: " << cut.minimumCut() << "\n";

  return 0;
}