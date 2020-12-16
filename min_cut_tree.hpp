#include <ogdf/basic/Graph_d.h>
#include <ogdf/basic/EdgeArray.h>
#include <ogdf/basic/List.h>

double minCutTreeAlgorithm(ogdf::Graph &G, ogdf::EdgeArray<double> &arr) {

  ogdf::Graph cp(G);
  ogdf::EdgeArray<double> cpArr(arr);
  ogdf::NodeArray<double> nodePrio(cp);
  
  // Calculate the upper-bound values for each node
  double minWeight = 3.40282e+10;
  double weight = 0.0;
  for(ogdf::node n : cp.nodes) {
    for(ogdf::adjEntry adj : n->adjEntries) {
      ogdf::edge e = adj->theEdge();
      weight+=arr[e];
    }
    nodePrio[n] = weight;
    weight = 0.0;  
  }
  ogdf::List<ogdf::node> currNodes;
  for(ogdf::node n: cp.nodes){
    currNodes.pushBack(n);
  }
  ogdf::ListIterator<ogdf::node> minValNodeIt;
  bool found = false;
  
  // While (number of vertices in the current graph >1 )
  while(cp.numberOfNodes() > 1) {
  //   Loop (Consider the vertices in the increasing order of upper-bound value)
  	double minInc = 3.40282e+10;
  	ogdf::node minIncNode = nullptr;
  	ogdf::node minIncNode2 = nullptr;
  	ogdf::node minValNode = nullptr;
  	ogdf::node otherNode = nullptr;
    while(currNodes.size()>1) {
      
      double minVal = 3.40282e+10;
      ogdf::ListIterator<ogdf::node> it1;
      for(it1=currNodes.begin(); it1.valid(); ++it1) {
        // find minval node
        if(nodePrio[*it1] < minVal){
          minValNode = *it1;
          minValNodeIt = it1;
          minVal = nodePrio[*it1];
        }
      }
      
      currNodes.del(minValNodeIt);
         
      double otherVal = 0.0;
      double edgeVal = 0.0;
      
      for(ogdf::adjEntry adj : minValNode->adjEntries){
        edgeVal = cpArr[adj->theEdge()];
        otherNode = adj->twinNode();
        otherVal = nodePrio[adj->twinNode()];
        if((std::max(otherVal,minVal)>(otherVal+minVal-(2.0*edgeVal)))){
          found = true;
          weight = minVal>otherVal ? otherVal : minVal;
          break;
        } else {
          if(otherVal+minVal-2*edgeVal < minInc){
            minInc = otherVal+minVal-2*edgeVal;
            minIncNode = minValNode;
            minIncNode2 = otherNode;
            weight = minVal>otherVal ? otherVal : minVal;
          }
        }
      }
      if(found){
        break;
      }
    }
	if(!found){
		minValNode = minIncNode;
		otherNode = minIncNode2;
	}
	
	if(weight < minWeight)
		minWeight = weight;
		
	ogdf::adjEntry adj = minValNode->firstAdj();
	while (adj != nullptr) {
		ogdf::adjEntry succ = adj->succ();
        
        ogdf::edge e = adj->theEdge();
		if (e->source() == otherNode || e->target() == otherNode) {
    		cp.delEdge(e);
    	} else if (e->source() == minValNode) {
    		cp.moveSource(e,otherNode);
    	} else {
    		cp.moveTarget(e,otherNode);
    	}
        adj = succ;
      }
    cp.delNode(minValNode);
      
    ogdf::NodeArray<ogdf::List<ogdf::edge> > adjNodes(cp);
    for(ogdf::adjEntry adjT : otherNode->adjEntries) {
  		adjNodes[adjT->twinNode()].pushBack(adjT->theEdge());
  	}
	ogdf::node nd = cp.firstNode();
    while (nd!=nullptr) {
    	if (adjNodes[nd].size() > 1) {
    		ogdf::edge e = adjNodes[nd].front();
    		adjNodes[nd].popFront();
    		for (ogdf::edge ei : adjNodes[nd]) {
    			cpArr[e] += cpArr[ei];
    			cp.delEdge(ei);
    		}
    	}
    	nd = nd->succ();
    }
    currNodes.clear();
    for(ogdf::node n: cp.nodes){
    	currNodes.pushBack(n);
  	}
	for(ogdf::node n : cp.nodes) {
	  for(ogdf::adjEntry adj : n->adjEntries) {
	    ogdf::edge e = adj->theEdge();
	    weight+=cpArr[e];
	  }
	  nodePrio[n] = weight;
	  weight = 0.0;  
	}
  	found = false;
  	if(currNodes.size()==1)
  		break;
  }  
  //   End While
  return minWeight; 
}