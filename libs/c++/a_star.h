// A Star Algorithm
// Developed by:
//		- Marcos Yukio Siraichi <sir.yukio@gmail.com>
//		- Lucas Georges Helal

#ifndef A_STAR
#define A_STAR

#include <cstdlib>
#include <list>
#include <unordered_map>
#include <vector>
#include <queue>
#include "a_node.h"
#define a_star_gen a_star<node_t, fgh_t, node_key>

template <class node_t, class fgh_t, class node_key>
class a_star {
	private:
		a_vector_gen open_set;
		std::unordered_map<node_key, a_node_gen> open_ref;
		std::unordered_map<node_key, a_node_gen> closed_set;
		node_t start, end;

		void init_set();
		std::list<node_t> *back_trace(a_node_gen);
		a_node_gen *create_node(node_t);

	public:
		fgh_t (*calc_h)(node_t);
		fgh_t (*calc_dist)(node_t, node_t);
		node_key (*generate_key)(node_t);
		bool (*node_equal)(node_t, node_t);
		std::vector<node_t> *(*create_nodes)(node_t);

		a_star(fgh_t (*)(node_t), fgh_t (*)(node_t, node_t), node_key (*)(node_t), bool (*)(node_t, node_t), std::vector<node_t>* (*)(node_t));
		std::list<node_t> *do_a_star(node_t, node_t);
};

template <class node_t, class fgh_t, class node_key>
a_star_gen::a_star(fgh_t (*h)(node_t), fgh_t (*g)(node_t, node_t),
		node_key (*gen)(node_t), bool (*eq)(node_t, node_t),
		std::vector<node_t> *(*new_n)(node_t)) {
	this->calc_h = h;
	this->calc_dist = g;
	generate_key = gen;
	node_equal = eq;
	create_nodes = new_n;

	init_set();
}

template <class node_t, class fgh_t, class node_key>
void a_star_gen::init_set() {
	open_ref.clear();
	open_set.clear();
	closed_set.clear();
};

template <class node_t, class fgh_t, class node_key>
a_node_gen *a_star_gen::create_node(node_t content) {
	a_node_gen *new_node = new a_node_gen();
	new_node->n = content;
	return new_node;
};

template <class node_t, class fgh_t, class node_key>
std::list<node_t> *a_star_gen::back_trace(a_node_gen n) {
	a_node_gen last;
	std::list<node_t> *path = new std::list<node_t>();
	last.parent = (*generate_key)(n.n);
	do {
		last = closed_set[last.parent];
		path->push_front(last.n);
	} while(last.n != start);
	return path;
};

template <class node_t, class fgh_t, class node_key>
std::list<node_t> *a_star_gen::do_a_star(node_t start, node_t end) {
	this->start = start;
	this->end = end;
	a_node_gen *s = create_node(start), *former_node, *aux;
	a_node_gen closest_node;
	fgh_t g_try_score;
	std::vector<node_t> *new_nodes;
	node_key i_key;
	typename std::unordered_map<node_key, a_node_gen>::iterator it;

	open_ref[(*generate_key)(s->n)] = *s;
	open_set.push_node(&(open_ref[(*generate_key)(s->n)]));
	while(!open_set.empty()) {
		closest_node = *(open_set.front());
		open_set.pop_node();
		open_ref.erase((*generate_key)(closest_node.n));
		closed_set[(*generate_key)(closest_node.n)] = closest_node;
		if((*node_equal)(closest_node.n, end)) return back_trace(closest_node);

		new_nodes = (*create_nodes)(closest_node.n);
		for(typename std::vector<node_t>::iterator i=new_nodes->begin(); i!=new_nodes->end(); i++) {
			aux = create_node(*i);
			g_try_score = closest_node.g + (*calc_dist)(aux->n, closest_node.n);
			i_key = (*generate_key)(aux->n);
			if(closed_set.find(i_key) != closed_set.end()) continue;
			if((it = open_ref.find(i_key)) != open_ref.end()) {
				former_node = &(it->second);
				if(former_node->g <= g_try_score) continue;
				aux = former_node;
			}
			aux->g = g_try_score;
			aux->h = (*calc_h)(aux->n);
			aux->f = aux->g + aux->h;
			aux->parent = (*generate_key)(closest_node.n);
			if(aux->n == (*i)) {
				open_ref[i_key] = *aux;
				free(aux);
			}
			open_set.push_node(&(open_ref[i_key]));
		}
		new_nodes->clear();
		free(new_nodes);
	}
};

#endif
