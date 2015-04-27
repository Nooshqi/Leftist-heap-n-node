/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  bkinuthi@uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter) 2015
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef LEFTIST_HEAP_H
#define LEFTIST_HEAP_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Leftist_node.h"
#include <stack>

template <typename Type>
class Leftist_heap {
	private:
		Leftist_node<Type> *root_node;
		int heap_size;

	public:
		Leftist_heap();
		Leftist_heap( Leftist_heap const & );
		~Leftist_heap();

		void swap( Leftist_heap &heap );
		Leftist_heap &operator=( Leftist_heap );

		bool empty() const;
		int size() const;
		int null_path_length() const;
		Type top() const;
		int count( Type const & ) const;

		void push( Type const & );
		Type pop();
		void clear();

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Leftist_heap<T> const & );
};

// some sample functions are given

template <typename Type>
Leftist_heap<Type>::Leftist_heap():
root_node( nullptr ),
heap_size( 0 ) {
	// does nothing
}

template <typename Type>
Leftist_heap<Type>::Leftist_heap( Leftist_heap const &heap ):
root_node( nullptr ),
heap_size( 0 ) {
	// Traverses through the argument heap by pushing nodes onto the stack(using a while loop)
	// and popping them while pushing the popped nodes' elements into a copy heap 

	if (!heap.empty() ) {

		std::stack<Leftist_node<Type> *> walkthru;

		walkthru.push(heap.root_node);
		//root_node = heap.root_node;

		while (!walkthru.empty() ){
			Leftist_node<Type> *top_node = walkthru.top();
			walkthru.pop();
			this->push(top_node->retrieve());
			//std::cout << '1' << std::endl ;

			if ( top_node == 0 ) {
				
			} 
			else {
				if (top_node->left() != nullptr){
				walkthru.push(top_node->left());
				}

				if (top_node->right() != nullptr){
				walkthru.push(top_node->right());

				}
			}
			

			
		}

		
	}


}

template <typename Type>
Leftist_heap<Type>::~Leftist_heap() {
	clear();  // might as well use it...
}

template <typename Type>
void Leftist_heap<Type>::swap( Leftist_heap<Type> &heap ) {
	std::swap( root_node, heap.root_node );
	std::swap( heap_size, heap.heap_size );
}

template <typename Type>
Leftist_heap<Type> &Leftist_heap<Type>::operator=( Leftist_heap<Type> rhs ) {
	swap( rhs );

	return *this;
}

// Your implementation here
// STRONG HINT:  Write a default definition of each function, even if
// it only returns the default value (false, 0, or Type()).
// 
// Once you have done this, you can proceed and implement the member functions
// one at a time.  If you do not, and just start implementing the member
// functions so that you can't compile and test your function, good luck. :-)

// You can modify this function however you want:  it will not be tested







template <typename Type>
bool Leftist_heap<Type>::empty() const {
    // return boolean:True if size is 0
    return(size() == 0);
}


template <typename Type>
int Leftist_heap<Type>::size() const {
    //return the size of the heap
    return heap_size;
}


template <typename Type>
int Leftist_heap<Type>::null_path_length() const {
    //returns the null path length of the root node

    return root_node->null_path_length();

}


template <typename Type>
int Leftist_heap<Type>::count(const Type &obj) const {
    //should return number of instances seen through out the structure
	return root_node->count(obj);
    
}

template <typename Type>
Type Leftist_heap<Type>::top() const {
    //Returns the element at the very top of the heap aka the root node's element
    //throws underflow if heaop is empty
    if (empty()){
    	throw underflow();
    }
    else {
    	return root_node->retrieve();
    }

}

template <typename Type>
void Leftist_heap<Type>::push(Type const &e ){
	//Insert the new element into the heap by setting it in a new leftist node(intro_node)
	// and calling push on the root node with intro_node and root_node as a second argument. 
	//Increment the heap size. (O(ln(n)))


		Leftist_node<Type> *intro_node = new Leftist_node<Type>(e);

		root_node->push( intro_node, root_node );
		++heap_size;




}

template <typename Type>
Type Leftist_heap<Type>::pop(){
	//Pop the least element(root node) in the heap and delete its node
	//reduce heap size by 1

	
		if ( empty() ) {
			throw underflow();
		}
		Type tmp = root_node->retrieve();
		Leftist_node<Type> *orig_root = root_node;
		Leftist_node<Type> *orig_left = root_node->left();
		
		root_node = orig_left;
		root_node->push(orig_root->right(),root_node);
		
		
		
		
		
		
		delete orig_root;
		--heap_size;

		return tmp;




}

template <typename Type>
void Leftist_heap<Type>::clear(){
	//clears root node and reset the root node to nullptr and heap size to 0

	if ( !empty() ) {
			root_node->clear();
			root_node = nullptr;
			heap_size = 0;
		}

}



//implementation got from the discussion page in learn for project three
template <typename Type>
std::ostream &operator<<( std::ostream &out, const Leftist_heap<Type> &heap ) {
	out << "Size:     " << heap.heap_size << std::endl;

	if ( !heap.empty() ) {

		std::stack<Leftist_node<Type> *> traversal;

		std::stack<int> indentation;

		traversal.push( heap.root_node );
		indentation.push( 0 );

		while ( !traversal.empty() ) {
			Leftist_node<Type> *node = traversal.top();
			int indent = indentation.top();

			traversal.pop();
			indentation.pop();

			out.width( indent );
			out.fill( ' ' );
			out << "";

			if ( node == 0 ) {
				out << "-" << std::endl;
			} else {
				out << node->retrieve() << std::endl;

				if ( node->left() != 0 || node->right() != 0 ) {
					traversal.push( node->right());
					indentation.push( indent + 1 );

					traversal.push( node->left());
					indentation.push( indent + 1 );
				}
			}
		}
	}



	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif



