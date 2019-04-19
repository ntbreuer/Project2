
#include "graph.h"
#include <iostream>

using namespace std;

/**
* Graph class providing the functionality of a graph data structure
* 4/11/19
* Nic Breuer
*/

// INITIALIZE GRAPH
GRAPH graph::Initialize(int v, int e) {

	GRAPH *graph = new GRAPH;

	graph->v = v;
	graph->e = e;

	//INITIALIZE LISTS
	graph->A = new LIST *[v+1]; //dynamic allocation of v pointers to LISTS
	for (int i = 0; i <= v; i++) {
		graph->A[i] = NULL; // initialize every list pointer to null
	}

	//INITIALIZE ELEMENTS
	graph->H = new ELEMENT[v+1];
	for (int i = 0; i <= v; i++) {
		graph->H[i].node = i; //Add node index(i) to element i
		graph->H[i].d = 999; //source -> node distance initialized to null
		graph->H[i].p = 0; //previous node initialized to null
	}

	return *graph;
}

// ADD EDGE BY ADJUSTING ADJ LISTS
void graph::InsertEdge(GRAPH &G, int u, int v, int w) {
	
	// list pointer which goes in double pointer list array
	LIST *listptr = new LIST;
	listptr->neighbor = v;
	listptr->weight = w;
	listptr->next = NULL;

	//find place to insert new list
	if (G.A[u] == NULL) { //if no lists are found for that node
		G.A[u] = listptr; //insert list pointer
	}
	else { //if at least one list is found for that node
		LIST *L = G.A[u];
		while (L->next != NULL) { //go to next list until null list is found
			L = L->next; 
		}
		L->next = listptr; //insert list pointer
	}
}

// PRINT GRAPH (VERTS/EDGES, NODES AND ADJ LISTS)
void graph::PrintGraph(GRAPH G) {
	// PRINT # OF VERTS / EDGES
	cout << "\n" << G.v << ",  " << G.e << "\n"; 

	// PRINT ADJ LISTS OF NODES
	for (int i = 1; i <= G.v; i++) {
		cout << G.H[i].node << ": "; // print node
		//cout << G.H[i].d << " : ";
		//cout << G.H[i].p << " : ";
		LIST *L = NULL;
		if (G.A[i] != NULL) { //if adj list exists for that node
			L = G.A[i];
			cout << "( " << L->neighbor << " , " << L->weight << " )"; // print adj 

			while (L->next != NULL) { //if more lists exist beyond the base list
				L = L->next;
				cout << "( " << L->neighbor << " , " << L->weight << " )"; // print adj
			}
		}
		cout << "\n";
	}
}

void graph::reset(GRAPH &G) {
	for (int i = 1; i <= G.v; i++) {
		G.H[i].d = 99999;
		G.H[i].p = 0;
	}
}


/*

graph::Weight(ELEMENT u, ELEMENT v) {

}

graph::Relax(ELEMENT u, ELEMENT v) {
	int w = graph::Weight(u, v);
	if (v.d > u.d + w) {
		v.d = u.d + w;
	}
	else {
		v.p = u;
	}
}

void graph::Initialize(GRAPH &G, ELEMENT source) {
	for (int i = 1; i < G.v; i++) {
		G.H[i].node = i;
		G.H[i].d = NULL;
		G.H[i].p = NULL;
	}
	source.d = 0;
}

graph::dijkstra(Graph G, int weight, ELEMENT source) {
	graph::InitSingleSource(G, source);
	
}

*/