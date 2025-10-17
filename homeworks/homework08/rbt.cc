#include "rbt.h"

// ---------------------------------------
// Node class
// Default constructor
RBTNode::RBTNode() : Node() {
    color = BLACK;
}

// Constructor
RBTNode::RBTNode(int in) : Node(in) {
	color = BLACK;
	add_left(nullptr);
	add_right(nullptr);
	add_parent(nullptr);
}
// Destructor
RBTNode::~RBTNode() {
}

void RBTNode::add_color(Node_color c)
{
  color = c;
}

void RBTNode::print_color(ostream& to)
{
    if(color == RED) {
        to << "Red";
    } else if (color == BLACK) {
        to << "Black";
    } else {
        cerr << "ERR: invalid color" << endl;
    }
}
void RBTNode::print_info(ostream& to)
{
    to << get_key() << " ";
    print_color(to);
}

Node_color RBTNode::get_color()
{
  return color;
}
// ---------------------------------------


// ---------------------------------------
// RBT class
// Constructor and destructor
RBT::RBT() : BST()
{
  sentinel = new RBTNode(-1);
  sentinel->add_color(BLACK);
  sentinel->add_left(sentinel);
  sentinel->add_right(sentinel);
  sentinel->add_parent(sentinel);
  root = sentinel;
}
RBT::~RBT()
{
    // re-using BST's inorder_free
    inorder_free(root, sentinel);
    // This makes sure that root is set to nullptr, so that the parent class's
    // constructor does not try to free the tree again
    root = nullptr;
    delete sentinel; 
}

// Functions that are basically wrappers for the parent class functions
// minimum key in the BST
RBTNode* RBT::tree_min()
{
    // return (RBTNode*) get_min(root);
    // return (RBTNode*) BST::tree_min();
    return (RBTNode*) BST::get_min(root, sentinel);
}
// maximum key in the BST
RBTNode* RBT::tree_max()
{
    // return (RBTNode*) get_max(root);
    // return (RBTNode*) BST::tree_max();
    return (RBTNode*) BST::get_max(root, sentinel);
}

// Get successor of the given node
RBTNode* RBT::get_succ(RBTNode* in)
{
  return (RBTNode*) BST::get_succ((Node*) in, sentinel);
}

// Get predecessor of the given node
RBTNode* RBT::get_pred(RBTNode* in)
{
  return (RBTNode*) BST::get_pred((Node*) in, sentinel);
}

// Search the tree for a given key
RBTNode* RBT::tree_search(int search_key)
{
  return (RBTNode*) BST::tree_search(search_key, sentinel);
}

void RBT::walk(ostream& to)
{
  BST::inorder_walk(root, to, sentinel);
}



// New functions to RBT
// right rotate
void RBT::right_rotate(RBTNode* y)
{
    /* TODO */

	RBTNode* x = (RBTNode*) y->get_left();
	if (x->get_right() != sentinel) {
		x->get_right()->add_parent(y);
	}
	x->add_parent(y->get_parent());
	if (y->get_parent() == sentinel) {
		root = x;
	} else if (y == y->get_parent()->get_right()) {
		y->get_parent()->add_right(x);
	} else {
		y->get_parent()->add_left(x);
	}
	x->add_right(y);
	y->add_parent(x);
}
// Left rotate
void RBT::left_rotate(RBTNode* x)
{
    /* TODO */
	RBTNode* y = (RBTNode*) x->get_right();
    	x->add_right(y->get_left());
    	if (y->get_left() != sentinel) {
		y->get_left()->add_parent(x);
	}
	y->add_parent(x->get_parent());
	if (x->get_parent() == sentinel) {
        	root = y;
    	} else if (x == x->get_parent()->get_left()) {
        	x->get_parent()->add_left(y);
    	} else {
        	x->get_parent()->add_right(y);
    	}
    	y->add_left(x);
    	x->add_parent(y);
}
void RBT::rb_insert_fixup(RBTNode* in)
{
    /* TODO */
	while (((RBTNode*)in->get_parent())->get_color() == RED) {
        	RBTNode* parent = (RBTNode*) in->get_parent();
        	RBTNode* grandparent = (RBTNode*) parent->get_parent();

        	if (parent == grandparent->get_left()) {
            		RBTNode* uncle = (RBTNode*) grandparent->get_right();
            		if (uncle->get_color() == RED) {
                		parent->add_color(BLACK);
                		uncle->add_color(BLACK);
                		grandparent->add_color(RED);
                		in = grandparent;
            	} else {
                	if (in == parent->get_right()) {
                    		in = parent;
                    		left_rotate(in);
                }
                ((RBTNode*) in->get_parent())->add_color(BLACK);
                ((RBTNode*) in->get_parent()->get_parent())->add_color(RED);
                right_rotate((RBTNode*) in->get_parent()->get_parent());
            }
        } else {
            RBTNode* uncle = (RBTNode*) grandparent->get_left();
            if (uncle->get_color() == RED) {
                parent->add_color(BLACK);
                uncle->add_color(BLACK);
                grandparent->add_color(RED);
                in = grandparent;
            } else {
                if (in == parent->get_left()) {
                    in = parent;
                    right_rotate(in);
                }
                ((RBTNode*) in->get_parent())->add_color(BLACK);
                ((RBTNode*) in->get_parent()->get_parent())->add_color(RED);
                left_rotate((RBTNode*) in->get_parent()->get_parent());
            }
        }
    }
    ((RBTNode*) root)->add_color(BLACK);
}

void RBT::rb_insert_node(RBTNode* in)
{
    /* TODO */
	in->add_color(RED);
    	in->add_left(sentinel);
    	in->add_right(sentinel);
    	in->add_parent(nullptr);

    	BST::insert_node(in, sentinel);
    	rb_insert_fixup(in);
}

void RBT::rb_delete_fixup(RBTNode* in)
{
    /* TODO */
	while (in != (RBTNode*)root && in->get_color() == BLACK) {
        	if (in == in->get_parent()->get_left()) {
            		RBTNode* w = (RBTNode*)in->get_parent()->get_right();
            		if (w->get_color() == RED) {
                		w->add_color(BLACK);
                		((RBTNode*)in->get_parent())->add_color(RED);
                		left_rotate((RBTNode*)in->get_parent());
                		w = (RBTNode*)in->get_parent()->get_right();
            		}
            		if (((RBTNode*)w->get_left())->get_color() == BLACK &&
                		((RBTNode*)w->get_right())->get_color() == BLACK) {
                		w->add_color(RED);
                		in = (RBTNode*)in->get_parent();
            		} else {
                		if (((RBTNode*)w->get_right())->get_color() == BLACK) {
                    			((RBTNode*)w->get_left())->add_color(BLACK);
                    			w->add_color(RED);
                    			right_rotate(w);
                    			w = (RBTNode*)in->get_parent()->get_right();
                }
                w->add_color(((RBTNode*)in->get_parent())->get_color());
                ((RBTNode*)in->get_parent())->add_color(BLACK);
                ((RBTNode*)w->get_right())->add_color(BLACK);
                left_rotate((RBTNode*)in->get_parent());
                in = (RBTNode*)root;
            }
        } else {
            RBTNode* w = (RBTNode*)in->get_parent()->get_left();
            if (w->get_color() == RED) {
                w->add_color(BLACK);
                ((RBTNode*)in->get_parent())->add_color(RED);
                right_rotate((RBTNode*)in->get_parent());
                w = (RBTNode*)in->get_parent()->get_left();
            }
            if (((RBTNode*)w->get_right())->get_color() == BLACK &&
                ((RBTNode*)w->get_left())->get_color() == BLACK) {
                w->add_color(RED);
                in = (RBTNode*)in->get_parent();
            } else {
                if (((RBTNode*)w->get_left())->get_color() == BLACK) {
                    ((RBTNode*)w->get_right())->add_color(BLACK);
                    w->add_color(RED);
                    left_rotate(w);
                    w = (RBTNode*)in->get_parent()->get_left();
                }
                w->add_color(((RBTNode*)in->get_parent())->get_color());
                ((RBTNode*)in->get_parent())->add_color(BLACK);
                ((RBTNode*)w->get_left())->add_color(BLACK);
                right_rotate((RBTNode*)in->get_parent());
                in = (RBTNode*)root;
            }
        }
    }
    in->add_color(BLACK);
}

void RBT::rb_delete_node(RBTNode* out)
{
    /* TODO */
	RBTNode* y = out;
    	RBTNode* x;
    	Node_color y_original_color = y->get_color();

    	if (out->get_left() == sentinel) {
        	x = (RBTNode*)out->get_right();
        	transplant(out, out->get_right());
    	} else if (out->get_right() == sentinel) {
        	x = (RBTNode*)out->get_left();
        	transplant(out, out->get_left());
    	} else {
        	y = (RBTNode*)get_min(out->get_right(), sentinel);
        	y_original_color = y->get_color();
        	x = (RBTNode*)y->get_right();
        	if (y->get_parent() == out) {
            		x->add_parent(y);
        	} else {
            		transplant(y, y->get_right());
            		y->add_right(out->get_right());
            		y->get_right()->add_parent(y);
        	}
        	transplant(out, y);
        	y->add_left(out->get_left());
        	y->get_left()->add_parent(y);
        	y->add_color(out->get_color());
    }

    delete out;

    if (y_original_color == BLACK) {
        rb_delete_fixup(x);
    }
}

void RBT::transplant(Node* u, Node* v)
{
    if (u->get_parent() == sentinel) {
        root = v;
    } else if (u == u->get_parent()->get_left()) {
        u->get_parent()->add_left(v);
    } else {
        u->get_parent()->add_right(v);
    }
    v->add_parent(u->get_parent());
}

// ---------------------------------------
