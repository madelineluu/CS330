#include "bst.h"

// ---------------------------------------
// Node class
// Default constructor - use initializer list
Node::Node() : key(0), parent(nullptr), left(nullptr), right(nullptr) {}

// Constructor - use initializer list
Node::Node(int in) : key(in), parent(nullptr), left(nullptr), right(nullptr) {}

// Destructor
Node::~Node() {}

// Add parent 
void Node::add_parent(Node* in) {
	parent = in;
}
// Add to left of current node
void Node::add_left(Node* in) {
	left = in;
	// Point node in to parent
	if (in) in->add_parent(this);
}

// Add to right of current node
void Node::add_right(Node* in) {
	right = in;
	// Point node in to parent
	if (in) in->add_parent(this);
}

// Get key
int Node::get_key()
{
	return key;
}
// Get parent node
Node* Node::get_parent()
{
	return parent;
}
// Get left node
Node* Node::get_left()
{
	return left;
}
// Get right node
Node* Node::get_right()
{
	return right;
}
// Print the key to ostream to
// Do not change this
void Node::print_info(ostream& to)
{
    to << key << endl;
}
// ---------------------------------------


// ---------------------------------------
// BST class
// Walk the subtree from the given node
void BST::inorder_walk(Node* in, ostream& to)
{
	// Inorder: left, root, right
	if (in != nullptr) {
		inorder_walk(in->get_left(), to);
		in->print_info(to);
		inorder_walk(in->get_right(), to);
	}
}
// Constructor - initialize root
BST::BST() : root(nullptr) {}
// Destructor
BST::~BST()
{
	// Delete all nodes recursively
	while (root) {
		delete_node(root);
	}
}
// Insert a node to the subtree
void BST::insert_node(Node* in)
{
	// Traverse BST to find insertion position, given new node key
	//  y tracks parent node to maintain linkages
	Node* y = nullptr;
	Node* x = root;
	while (x != nullptr) {
		y = x;
		if (in->get_key() < x->get_key())
			x = x->get_left();
		else
			x = x->get_right();
	}

	// Insert at correct position
	in->add_parent(y);
	if (y == nullptr)
		root = in;
	else if (in->get_key() < y->get_key())
		y->add_left(in);
	else
		y->add_right(in);
}

// Delete a node to the subtree
void BST::delete_node(Node* out)
{
    Node* out_parent = out->get_parent();
    Node* out_left = out->get_left();
    Node* out_right = out->get_right();

    // Case 1: No left child
    if (out_left == nullptr) {
        if (out_parent == nullptr) {
            root = out_right;
            if (root != nullptr) root->add_parent(nullptr);
        } else if (out == out_parent->get_left()) {
            out_parent->add_left(out_right);
        } else {
            out_parent->add_right(out_right);
        }
        if (out_right != nullptr) {
            out_right->add_parent(out_parent);
        }

    // Case 2: No right child
    } else if (out_right == nullptr) {
        if (out_parent == nullptr) {
            root = out_left;
            if (root != nullptr) root->add_parent(nullptr);
        } else if (out == out_parent->get_left()) {
            out_parent->add_left(out_left);
        } else {
            out_parent->add_right(out_left);
        }
        if (out_left != nullptr) {
            out_left->add_parent(out_parent);
        }

    // Case 3: Two children
    } else {
        Node* y = get_min(out_right);  // successor
        Node* y_parent = y->get_parent();
        Node* y_right = y->get_right();

        if (y_parent != out) {
            // Replace y with its right child
            if (y_right != nullptr) {
                y_parent->add_left(y_right);
                y_right->add_parent(y_parent);
            } else {
                y_parent->add_left(nullptr);
            }
            y->add_right(out_right);
            if (out_right != nullptr) {
                out_right->add_parent(y);
            }
        }

        if (out_parent == nullptr) {
            root = y;
        } else if (out == out_parent->get_left()) {
            out_parent->add_left(y);
        } else {
            out_parent->add_right(y);
        }

        y->add_parent(out_parent);
        y->add_left(out_left);
        if (out_left != nullptr) {
            out_left->add_parent(y);
        }
    }

    // Finally delete out
    delete out;
}

// minimum key in the BST
Node* BST::tree_min()
{
	return get_min(root);
}
// maximum key in the BST
Node* BST::tree_max()
{
	return get_max(root);
}
// Get the minimum node from the subtree of given node
Node* BST::get_min(Node* in)
{
	// Traverse left until reaching leftmost child
	while (in->get_left() != nullptr) {
		in = in->get_left();
	}
	return in;
}
// Get the maximum node from the subtree of given node
Node* BST::get_max(Node* in)
{
	// Traverse to rightmost node
	while (in->get_right() != nullptr) {
		in = in->get_right();
	}
	return in;
}
// Get successor of the given node
Node* BST::get_succ(Node* in)
{
	// Successor = next largest node; minimum of right subtree
	if (in->get_right() != nullptr)
		return get_min(in->get_right());
	
	// Traverse up until next right subtree, if needed
	Node* y = in->get_parent();
	while (y != nullptr && in == y->get_right()) {
		in = y;
		y = y->get_parent();
	}
	return y;
}
// Get predecessor of the given node
Node* BST::get_pred(Node* in)
{
	// Predecessor: next smallest node; max of left subtree
	if (in->get_left() != nullptr) 
		return get_max(in->get_left());
	
	// Traverse to next left subtree if needed
	Node *y = in->get_parent();
	while (y != nullptr && in == y->get_left()) {
		in = y;
		y = y->get_parent();
	}
	return y;
}
// Walk the BST from min to max
void BST::walk(ostream& to)
{
	inorder_walk(root, to);
}
// Search the tree for a given key
Node* BST::tree_search(int search_key)
{
	Node *x = root;
	while (x != nullptr && search_key != x->get_key()) {
		if (x->get_key() > search_key) {
			x = x->get_left();
		} else {
			x = x->get_right();
		}
	}
	return x;
}
// ---------------------------------------
