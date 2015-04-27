#include <iostream>
#include <cstring>
#include "Leftist_heap_tester.h"
#include "Leftist_node.h"
#include "Leftist_heap.h"

using namespace std;

int main(){

	Leftist_heap<Type> *heap = new Leftist_heap<Type>();
	cout << heap << endl;
	cout << heap.null_path_length() << endl;
	return 0;

}