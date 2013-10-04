// A* NODES
// Developed by:
//		- Marcos Yukio Siraichi <sir.yukio@gmail.com>
//		- Lucas Georges Helal
// This code is under MIT license

#ifndef A_NODE_H
#define A_NODE_H
#define a_node_gen a_node<node_t, fgh_t, node_key>
#define compare_gen compare_node<node_t, fgh_t, node_key>
#define a_vector_gen a_vector<node_t, fgh_t, node_key>

template <class node_t, class fgh_t, class node_key>
class a_node {
	public:
		node_t n;
		fgh_t h, g, f;
		node_key parent;
};

template <class node_t, class fgh_t, class node_key>
class a_vector : public std::vector<a_node_gen*> {
	public:
		a_vector();
		void push_node(a_node_gen*);
		void pop_node();
};

template <class node_t, class fgh_t, class node_key>
class compare_node {
	public:
		bool operator() (a_node_gen *&a1, a_node_gen *&a2);
};

template <class node_t, class fgh_t, class node_key>
void a_vector_gen::push_node(a_node_gen *n) {
	this->push_back(n);
	std::push_heap(this->begin(), this->end(), compare_gen()); 
};

template <class node_t, class fgh_t, class node_key>
void a_vector_gen::pop_node() {
	std::pop_heap(this->begin(), this->end(), compare_gen());
	this->pop_back();
};

template <class node_t, class fgh_t, class node_key>
a_vector_gen::a_vector() {
	std::make_heap(this->begin(), this->end(), compare_gen());
};

template <class node_t, class fgh_t, class node_key>
bool compare_gen::operator()(a_node_gen *&a1, a_node_gen *&a2) {
	return ( a1->f > a2->f );
};

#endif
