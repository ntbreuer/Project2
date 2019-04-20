#include "graph.h"
#include "util.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "main.h"
#include "heap.h"


/**
* This program finds the shortest path through a graph using dijkstra's shortest path algorithm
* 4/11/19
* Nic Breuer
*/

using namespace std;

graph graph_c;
heap heap_c;
util util_c;
ifstream myfile;

// READS GRAPH AND BUILDS GRAPH AND ADJ LISTS
void inputGraph(GRAPH &G) {

	int n, m; //verts , edges
	int u, v, w; //node, neighbor, weight
	int counter = 0;

	myfile >> n; myfile >> m; //reads first line
	G = graph_c.Initialize(n, m); //creates temp graph will null ptrs to work on

	while (myfile >> u >> v >> w) { //reads all other lines
		graph_c.InsertEdge(G, u, v, w); //creates elements and adj lists
		counter++;
		if (counter >= m) {
			break; //breaks loop early if data lines is greater than # of vert provided
		} 
	}

	if (counter < m) {
		cout << "\nError: Data does not match # of verts";
		G = graph_c.Initialize(0, 0);
	}
}

void Dijkstra(GRAPH &G) {
	// get source and destination node value

	int sourceNode = -1; int destination = -1; int flag = -1;
	int error = 0;
	util_c.DCommand(&sourceNode, &destination, &flag);
	if (flag < 0 || flag > 1) {
		cout << "\nERROR: Invalid flag value.\n";
		error = 1;
	}
	if (sourceNode < 1 || sourceNode > G.v || destination < 0 || destination > G.v) {
		cout << "\nERROR: One or more of the nodes is invalid.\n";
		error = 1;
	}
	if (error) {
		return;
	}

	cout << " - Run Dijkstra's Alg";

	if (sourceNode == destination) {
		if (flag == 0) {
			cout << "\nLength: 0";
		}
		else {
			cout << "\nPATH: " << sourceNode;
		}
		return;
	}

	// ---------STEP 1--------
	// CREATE MIN HEAP (USING DISTANCE AS THE VALUE) OF SIZE v AND INIT SOURCE d TO 0
	inputGraph(G);
	HEAP tempHeap = heap_c.Initialize(G, sourceNode);

	// ---------STEP 2--------
	// WHILE MIN HEAP NOT EMPTY, EXTRA MIN AND RETRIEVE THE ADJ LIST OF THAT NODE
	while (tempHeap.size > 0) {
		ELEMENT u = heap_c.ExtractMin(tempHeap); //get extracted node (u)
		LIST *TempList = G.A[u.node]; //get adj list of node

		while (TempList != NULL) { //while an adj list exists 

			// ---------STEP 3--------
			// FOR EACH ELEMENT IN ADJ LIST, IF THE NEIGHBORING NODE IS STILL IN THE HEAP, CHECK TO
			//	 SEE IF (v.d > w + u.d) WHERE v IS THE NEIGHBOR NODE, u IS THE EXTRACTED NODE, AND w
			//   IS THE WEIGHT OF THE EDGE BETWEEN u AND v (PULLED FROM ADJ LIST)
			//   IF TRUE, SET THE NEIGHBOR NODE'S DISTANCE TO (w + u.d) AND THE NEIGHBOR'S PREVIOUS NODE TO u;

			//cout << "u: " << u.node << endl;
			//cout << "u.d: " << u.d << endl;
			ELEMENT* v = &G.H[TempList->neighbor]; //cout << "\nv: " << TempList->neighbor << endl;//get neighbor (v)
			int w = TempList->weight; //cout << "u->v w: " << w << endl; //get weight (u->v)

			for (int i = 1; i <= tempHeap.size; i++) { //If neighbor still exists in heap 
				if (v->node == tempHeap.H[i].node) {
					// perform relax
					if (v->d > w + u.d) { //if its distance is larger than u->p + u.d
						v->p = u.node; //cout << v->node << ".p =" << u.node << endl; //set neighbors previous node to u
						v->d = w + u.d; //cout << v->node << ".d =" << w + u.d << endl;//set neighbor distance to w + u.d
						tempHeap.H[i].d = v->d; //update heap values as well
						tempHeap.H[i].p = v->p;
						heap_c.DecreaseKey(tempHeap, i, v->d); //decrease key of heap distance to ensure min heap
					}
					break;
				}
			}
			TempList = TempList->next;
		}
		//graph_c.PrintGraph(G);
	}
	
	// print path
	ELEMENT tempElement = G.H[destination];
	if (flag == 0) {
		if (tempElement.d != 999) {
			cout << "\nLength: " << tempElement.d;
		}
		else {
			cout << "\nNo path available";
		}
	}
	else {
		cout << "\n";
		if (tempElement.d == 999) {
			cout << "No path available from " << sourceNode << " to " << destination;
		}
		else {
			
			string s = "";
			cout << "PATH: " << sourceNode;
			while (tempElement.node != sourceNode) {
				int i = tempElement.node;
				string newS;
				stringstream out;
				out << i;
				newS = out.str();

				s = ", " + newS + s;
				//cout << tempElement.node << " <- ";
				tempElement = G.H[tempElement.p];
			}
			cout << s;
			

		}
	}
}

void Relax(ELEMENT u, ELEMENT &v, int w) {
	if (v.d > u.d + w){
		v.d = w;
		v.p = u.node;
	}
}


int main(){
	GRAPH mygraph = graph_c.Initialize(0,0);
	HEAP myheap;
	
	while (1) {
		// GET COMMAND FROM USER
		cout << "\n\nENTER A COMMAND: \n";
		int i = 0;
		char c = util_c.nextCommand(); //return input values as 0 if none found
		cout << "COMMAND: " << c;
		c = tolower(c);
		

		// EXECUTE COMMAND
		switch (c) {
		case 'e': //stop
			cout << " - exit case" << endl;
			exit(0);

		case 'i': //input graph
			//TODO pointer stuff
			cout << " - Input graph";
			myfile.open("Ginput.txt");
			if (myfile.is_open()) {
				inputGraph(mygraph);
			}
			else {
				cout << "\nError: There was a problem opening file Ginput.txt for reading.";
			}
			myfile.close();
			break;
			

		case 'w': //write graph
			cout << " - Write graph";
			if (mygraph.v != 0) { graph_c.PrintGraph(mygraph); }
			else { cout << "\nERROR: no graph exists."; }
			break;

		case 'c': //run shortest path alg
			if (mygraph.v != 0) { 
				myfile.open("Ginput.txt");
				Dijkstra(mygraph); 
				myfile.close();
			}
			else { cout << "\nERROR: no graph exists."; }
			break;

		default:
			cout << "\nERROR: Unrecognized Command\n"; break;
		}
	}

	int nothing;
	cin >> nothing;
	return 0;
}
