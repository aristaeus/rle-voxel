#ifndef RLE_HPP
#define RLE_HPP

#include <vector>

#include "wrap.hpp"

struct int_node{
	int coord;
	int type;
};

class rle_chunk{
	int dim;
	int rle_count;
	int_node* voxels;
  public:
	void print_chunk();
	void insert(int coord, int type);
	rle_chunk(int dim);
	~rle_chunk();
};

std::vector<glm::vec3>
add_square(double xs, double ys, double zs, double xe, double ye, double ze);

#endif
