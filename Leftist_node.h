/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  bkinuthi @uwaterloo.ca
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

#ifndef LEFTIST_NODE_H
#define LEFTIST_NODE_H

#include <algorithm>
#include <stack>
// You may use std::swap and std::min

#ifndef nullptr
#define nullptr 0
#endif

template <typename Type>
class Leftist_node {
	private:
		Type element;
		Leftist_node *left_tree;
		Leftist_node *right_tree;
		int heap_null_path_length;

	public:
		Leftist_node( Type const & );

		Type retrieve() const;
		bool empty() const;
		Leftist_node *left() const;
		Leftist_node *right() const;
		int count( Type const & ) const;
		int null_path_length() const;

		void push( Leftist_node *, Leftist_node *& );
		void clear();
};

template <typename Type>
Leftist_node<Type>::Leftist_node( Type const &obj ):
element( obj ),
left_tree( nullptr ),
right_tree( nullptr ),
heap_null_path_length( 0 ) {
	// does nothing
}

// You may need this

//returns boolean true if the node pointer is pointing to a null pointer 
template <typename Type>
bool Leftist_node<Type>::empty() const {
	return ( this == nullptr );
}

// You must implement everything
//aye aye Captain!


template <typename Type>
Type Leftist_node<Type>::retrieve() const {
	//Returns the element stored in this node. (O(1))
	return element;

}

template <typename Type>
Leftist_node<Type> *Leftist_node<Type>::left() const {
	//Returns the address/pointer of the left sub-tree
	return left_tree;

}

template <typename Type>
Leftist_node<Type> *Leftist_node<Type>::right() const {
	//Returns the address/pointer of the right sub-tree
	return right_tree;

}

template <typename Type>
int Leftist_node<Type>::null_path_length() const {
	//if the node is empty then set the npl to be -1 
	if (this == nullptr){
		return -1;
	}
	//return npl
	return heap_null_path_length;

}

template <typename Type>
int Leftist_node<Type>::count( const Type &obj ) const {
	//should return number of instances seen through out the structure
	//if empty return 0 else use recursion to go through every node in the structure 
	//the return sends you back to the instruction that called it, so thats why we set it to zero
	//just so for the reason when you reach the leafs of the structure 


	int counter = 0;
	if (empty() ){
		return 0;
	}
		if(element == obj ){
			counter = 1 + left_tree->count(obj) + right_tree->count(obj);	
		}
		else{
			counter = 0 + left_tree->count(obj) + right_tree->count(obj);
		}
		
	
	return counter;




}

template <typename Type>
void Leftist_node<Type>::push(Leftist_node *new_heap, Leftist_node *&ptr_to_this){
	//acts like a merge function as explained on the slides to allow for the pop/push->heap
	//check if either of the two heaps are empty
	//else check if old element is bigger than new element and then push the larger one onto the smaller one 


	if ( new_heap == nullptr ) {
		return;
		}

	else if ( this == nullptr ) {
		ptr_to_this = new_heap;
		return;
	}

	// If the this contains a larger element, we will swap the
	// two heaps and instead merge this heap with the argument.

	if(element <= new_heap->retrieve()){
		ptr_to_this->right_tree->push(new_heap, ptr_to_this->right_tree);
		
		
	}
	else {
	Leftist_node *older = ptr_to_this;
	ptr_to_this = new_heap;
	new_heap = older;
	ptr_to_this->right_tree->push(new_heap, ptr_to_this->right_tree);
	}
	
	//swap the left and right subtree if the right is heavier than the left 
	// set the null path length to smaller of the 2 subtrees
	
	if ( ptr_to_this->left()->null_path_length() < ptr_to_this->right()->null_path_length() ) {
		
		std::swap(ptr_to_this->right_tree,ptr_to_this->left_tree);
		
	}
	heap_null_path_length = std::min( 1 + ptr_to_this->left()->null_path_length(), 1 + ptr_to_this->right()->null_path_length() );
	


}

template <typename Type>
void Leftist_node<Type>::clear(){
	//If its a nullptr, return; else,
	// call clear on the left sub-tree and then on the right and then delete this. (O(n))


	
	if ( left() != 0 ) {
			left()->clear();
		}

	if ( right() != 0 ) {
		right()->clear();
	}

	delete this;

	
}


#endif
