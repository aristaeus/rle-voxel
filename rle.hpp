#ifndef RLE_HPP
#define RLE_HPP

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

#endif
