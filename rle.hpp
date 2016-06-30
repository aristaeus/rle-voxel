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

	// extremely basic meshing
	std::vector<glm::vec3> naive_mesh();

	// slightly less basic meshing
	std::vector<glm::vec3> less_naive();

	// get a run length at an ID
	int_node get_rle(int i);

    // constructors and stuff
	rle_chunk(int dim);
	~rle_chunk();
};

// add a square between point a and point b
// this really needs another vector I think
// Or a normal or something
std::vector<glm::vec3>
add_square(double xs, double ys, double zs, double xe, double ye, double ze);

// new square function
std::vector<glm::vec3> add_square(glm::vec3 a, glm::vec3 b, glm::vec3 c);

// generate a volume between two points
std::vector<glm::vec3> gen_volume(glm::vec3 a, glm::vec3 b);

// create a cube between points *s and *e (DEPRECATED)
std::vector<glm::vec3> add_cube(double x, double y, double z);

#endif
