#include <iostream>

#include "rle.hpp"
#include "wrap.hpp"

int main(){
	// rle_chunk chunk(4);
	// chunk.insert(0, 0);
	// chunk.insert(1, 1);
	// chunk.insert(5, 0);
	// chunk.insert(6, 1);
	// chunk.insert(38, 0);
	// chunk.insert(5, 1);
	// chunk.insert(16, 2);
	// chunk.insert(20, 3);
	// chunk.insert(30, 0);
	
	int array[] = {0, 1, 1, 1, 1,
	               1, 1, 0, 0, 0,
	               0, 0, 1, 1, 1,
	               0, 0, 1, 1, 1,
	               0, 0, 1, 1, 1,
	               1, 1 };
	rle_chunk chunk(array, 3);

	renderer render;

    std::vector<glm::vec3> verts = chunk.less_naive();

	render.add_mesh((GLfloat*)verts.data(), 3*verts.size());

	while(render.is_open()) render.draw();
	return 0;
}
