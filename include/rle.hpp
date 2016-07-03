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
    // print chunk info to stdout
	void print_chunk();

	// insert a run into the chunk
	void insert(int coord, int type);

	// convert vector coords to int ID
	int  coord_conv(glm::vec3 in);

	// convert an int ID into a vector coord
	glm::vec3 coord_conv(int in);

	// slightly less basic meshing
	std::vector<glm::vec3> less_naive();

	// get a run length at an ID
	int_node get_rle(int i);

    // constructors and stuff
	rle_chunk(int dim);
	rle_chunk(int* array, int dim);
	~rle_chunk();
};

// does what it says on the tin
std::vector<glm::vec3>
add_square(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d);

// generate a volume between two points
std::vector<glm::vec3>
gen_volume(glm::vec3 a, glm::vec3 b);

#endif
