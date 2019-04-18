#pragma once
#include <iostream>
#include "graph.h"

struct HEAP {
	int capacity;
	int size;
	ELEMENT *H;
};

class heap {

	public:
	bool checkValidHeap(HEAP heap);
	virtual void printHeap(HEAP heap);
	virtual int parent(int i);
	virtual int left(int i);
	virtual int right(int i);
	virtual void Exchange(ELEMENT A[], int i, int i2);
	virtual void MinHeapify(ELEMENT A[], int i, int n);
	virtual HEAP Initialize(GRAPH &G, int sourceNode);
	virtual ELEMENT ExtractMin(HEAP& heap);
	void DecreaseKey(HEAP & heap, int index, int value);
};

