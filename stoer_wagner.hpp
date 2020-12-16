#include <ogdf/basic/Graph_d.h>
#include <ogdf/basic/EdgeArray.h>
#include <ogdf/basic/PriorityQueue.h>

double StoerWagnerAlgorithm(ogdf::Graph &G, ogdf::EdgeArray<double> &arr) {

  ogdf::Graph cp(G);
  ogdf::EdgeArray<double> cpArr(arr);
  ogdf::PrioritizedMapQueue<ogdf::node, double> pq(cp);
  double weight = 0.0;
  double maxWeight = 3.40282e+10;
  ogdf::List<ogdf::node> markedNodes;
  
  while(cp.numberOfNodes() > 1) {
    for(ogdf::node n : cp.nodes) {
      pq.push(n,0.0);     
    }
    ogdf::node v = pq.topElement();
    pq.pop();
    markedNodes.pushBack(v);
    for(ogdf::adjEntry adj : v->adjEntries) {
      pq.decrease(adj->twinNode(), -cpArr[adj->theEdge()]);
    }
    ogdf::node maxWeightNodePq;
    
	while(markedNodes.size() != cp.numberOfNodes()){
    	double mostTightly = 0.0;
		maxWeightNodePq = nullptr;
		if (pq.topPriority() < mostTightly)
		{
    		maxWeightNodePq = pq.topElement();
 			mostTightly = pq.topPriority();
 		  	pq.pop();
    	} else {      	
			maxWeightNodePq = pq.topElement();
		}
        markedNodes.pushBack(maxWeightNodePq);

		for(ogdf::adjEntry a : maxWeightNodePq->adjEntries) {
			if(pq.contains(a->twinNode())){
				pq.decrease(a->twinNode(), pq.priority(a->twinNode())-cpArr[a->theEdge()]);
			}
		}
    }

    weight = 0.0;
  	ogdf::ListConstReverseIterator<ogdf::node> last = markedNodes.rbegin();
  	ogdf::node minValNode = (*last); 
	ogdf::node otherNode = *(last.succ());
  	for(ogdf::adjEntry t_adj : minValNode->adjEntries) {
  		weight += cpArr[t_adj->theEdge()];
  	}
    if(weight < maxWeight){
      maxWeight = weight;
    }
    ogdf::adjEntry adj = minValNode->firstAdj();
    while (adj != nullptr) {
      ogdf::adjEntry succ = adj->succ();
      
      ogdf::edge e = adj->theEdge();
  		if (e->source() == otherNode || e->target() == otherNode) {
  			cp.delEdge(e);
  		}
  		else if (e->source() == minValNode) {
  			cp.moveSource(e,otherNode);
  		}
  		else {
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
    pq.clear();
    markedNodes.clear();
  }
  
  return maxWeight;
}