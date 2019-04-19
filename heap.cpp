
#include "heap.h"

using namespace std;

/**
* Heap class providing the functionality of a heap data structure
* 3/8/19
* Nic Breuer
*/


// checks to see if a heap is valid
bool heap::checkValidHeap(HEAP heap) {
	if (heap.capacity > 0) {
		return true;
	}
	cout << "\nERROR: No heap available";
	return false;
}

// print contents of heap
void heap::printHeap(HEAP heap) {
	cout << "\nCapacity: " << heap.capacity;
	cout << "\nSize: " << heap.size;
	cout << "\nHeap:\n";
	for (int i = 1; i <= heap.size; i++) {
		cout << heap.H[i].node << ", " << heap.H[i].d << ", " << heap.H[i].p << endl;;
	}
	cout << "\n";
}

int heap::parent(int i) {
	return i / 2;
}
int heap::left(int i) {
	return i * 2;
}
int heap::right(int i) {
	return i * 2 + 1;
}

// swaps two elementas of an array
void heap::Exchange(ELEMENT A[], int i, int i2) {
	ELEMENT tempE = A[i];
	A[i] = A[i2];
	A[i2] = tempE;
}

// ensures a min heap at specified index
void heap::MinHeapify(ELEMENT A[], int i, int n) {
	int L = 2 * i; // left child
	int R = 2 * i + 1; // right child
	int largest;

	if (L <= n && A[L].d < A[i].d) { largest = L; }
	else { largest = i; }
	if (R <= n && A[R].d < A[largest].d) { largest = R; }
	if (largest != i) {
		heap::Exchange(A, largest, i);
		heap::MinHeapify(A, largest, n);
	}
}

// places the Contents of G into heap to form a min-heap
HEAP heap::Initialize(GRAPH &G, int sourceNode) {
	HEAP *heapPtr = new HEAP;
	heapPtr->size = G.v;
	heapPtr->capacity = G.v;
	heapPtr->H = new ELEMENT[G.v + 1];
	for (int i = 1; i <= G.v; i++) {
		heapPtr->H[i].node = G.H[i].node;
		heapPtr->H[i].d = 999;
		heapPtr->H[i].p = 0;
	}
	heapPtr->H[sourceNode].d = 0;
	G.H[sourceNode].d = 0;
	DecreaseKey(*heapPtr, sourceNode, 0);

	return *heapPtr;
}

// extracts min element from heap
ELEMENT heap::ExtractMin(HEAP& heap) {
	ELEMENT tempElement = heap.H[1];
	heap.H[1] = heap.H[heap.size];
	heap.size--;
	heap::MinHeapify(heap.H, 1, heap.size - 1);
	
	return tempElement;
}

void heap::DecreaseKey(HEAP& heap, int index, int value) {
	if (value > heap.H[index].d) {
		cout << "\nERROR: Value larger than current key";
	}
	else {
		heap.H[index].d = value;
		while (index > 1 && heap.H[heap::parent(index)].d > heap.H[index].d) {
			heap::Exchange(heap.H, index, heap::parent(index));
			index = parent(index);
		}
	}
}