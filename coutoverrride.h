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
