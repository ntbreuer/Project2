#pragma once

struct ELEMENT {
	int node; //vertex
	int d; //distance from source
	int p; //previous vertex
};

struct LIST { 
	int neighbor; //neighbor node
	int weight; //weight of edge
	struct LIST* next; //next list
};

struct GRAPH {
	int v; //verts
	int e; //edges
	ELEMENT *H; //nodes
	LIST** A; //adj lists
};

class graph {

	public:
		GRAPH Initialize(int v, int e);
		void InsertEdge(GRAPH &G, int u, int v, int w);
		void PrintGraph(GRAPH G);
		void reset(GRAPH &G);
};

