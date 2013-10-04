// Algorithm that solves the 15(fifteen) puzzle.
// Developed by 
//		- Marcos Yukio Siraichi <sir.yukio@gmail.com>
//		- Lucas Georges Helal

#include <iostream>
#include <vector>
#include <string>
#include "../../libs/c++/a_star.h"

float out_of_order_heuristic(int mat[][4]) {
	int n = 1;
	float pieces_n = 0;
	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {
			if(mat[i][j] != n) pieces_n++;
			n++;
		}
	}
	return pieces_n;
}

float out_of_sequence_heuristic(int mat[][4]) {
	float pieces_n = 0;
	int next_lin, next_col;
	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {
			if(mat[i][j] != 0) {
				next_col = j+1;
				next_lin = i;
				if((j == 3) && (i != 3)) {
					next_col = 0;
					next_lin = i+1;
				}
				if(!((i == 3) && (j == 3)) && (mat[i][j]+1 != mat[next_lin][next_col]))
					pieces_n++;
			}
		}
	}
	return pieces_n;
}

float calc_dist(int mat[][4], int lin, int col) {
	int pos_lin, pos_col;
	float total;
	pos_lin = (mat[lin][col] - 1) / 4;
	pos_col = (mat[lin][col] - 1) % 4;
	pos_lin -= lin;
	pos_col -= col;
	if(pos_lin < 0) pos_lin *= -1; 
	if(pos_col < 0) pos_col *= -1; 
	return (float) (pos_lin + pos_col);
}

float rect_distance_heuristic(int mat[][4]) {
	float mov = 0;
	int n = 1;
	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {
			if(mat[i][j] != 0)
				if(mat[i][j] != n)
					mov += calc_dist(mat, i, j); 
			n++;
		}   
	}   
	return mov;
}

float calculate_h(int matrix[][4]) {
	return (out_of_order_heuristic(matrix) +
			out_of_sequence_heuristic(matrix) +
			rect_distance_heuristic(matrix));
}

std::string generate_key(int mat[][4]) {
	std::string key = "";
	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {
			if(mat[i][j] < 10) key += "0";
			key += mat[i][j];
		}
	}
	return key;
}

void print(int mat[][4]) {
	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {
			if(mat[i][j] > 9) std::cout << mat[i][j] << "  ";
			else std::cout << mat[i][j] << "   ";
		}
		std::cout << std::endl;
	}	
}

bool node_equal(int matrix1[][4],int matrix2[][4]) {
	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {
			if(matrix1[i][j] != matrix2[i][j]) return false;
		}
	}
	return true;
}

void swap_block(int matrix[][4], int lin, int col, int lin_t, int col_t) {
	int aux;
	aux = matrix[lin][col];
	matrix[lin][col] = matrix[lin_t][col_t];
	matrix[lin_t][col_t] = aux;
}

void copy_m(int m[][4], int m2[][4]) {
	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {
			m[i][j] = m2[i][j];
		}
	}
}

std::vector<int(*)[4]> *create_nodes(int matrix[][4]) {
	std::vector<int(*)[4]> *new_nodes = new std::vector<int(*)[4]>();
	int (*new_node)[4] = new int[4][4];
	int i, j;
	for(i=0; i<4; i++) {
		for(j=0; j<4; j++) {
			if(matrix[i][j] == 0) break;
		}
		if(matrix[i][j] == 0 && j < 4) break;
	}
	copy_m(new_node, matrix);
	if(i != 0) {
		swap_block(new_node, i, j, i-1, j);
		new_nodes->push_back(new_node);
		new_node = new int[4][4];
		copy_m(new_node, matrix);
	}
	if(i != 3) {
		swap_block(new_node, i, j, i+1, j);
		new_nodes->push_back(new_node);
		new_node = new int[4][4];
		copy_m(new_node, matrix);
	}
	if(j != 0) {
		swap_block(new_node, i, j, i, j-1);
		new_nodes->push_back(new_node);
		new_node = new int[4][4];
		copy_m(new_node, matrix);
	}
	if(j != 3) {
		swap_block(new_node, i, j, i, j+1);
		new_nodes->push_back(new_node);
	}
	return new_nodes;
}

float calc_g(int m[][4], int m2[][4]) {
	return 1;
}

int main() {
	int s[4][4], e[4][4];
	int n=1;
	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {
			e[i][j] = n;
			n++;
		}
	}
	e[3][3] = 0;
	int m[16] = {2,6,8,3,1,14,9,11,7,12,13,0,5,15,4,10};
	for (int o=0; o<16; o++) {
		s[o/4][o%4] = m[o];
	}
	print(s);

	a_star<int(*)[4], float, std::string> astar(&calculate_h, &calc_g, &generate_key, &node_equal, &create_nodes);
	std::list<int(*)[4]> *path;
	path = astar.do_a_star(s, e);
	int mov = path->size();
	for(std::list<int(*)[4]>::iterator i=path->begin(); i!=path->end(); i++) {
		std::cout << std::endl;
		print(*i);
		std::cout << std::endl;
	}
	std::cout << "Moves: " << mov << std::endl;
}

