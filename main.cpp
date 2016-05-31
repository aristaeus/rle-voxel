#include "rle.hpp"
#include "wrap.hpp"

int main(){
	rle_chunk chunk(5);
	chunk.insert(0, 0);
	chunk.insert(1, 1);
	chunk.insert(5, 0);
	chunk.insert(6, 1);
	chunk.insert(38, 0);
	// chunk.insert(5, 1);
	// chunk.insert(16, 2);
	// chunk.insert(20, 3);
	// chunk.insert(30, 0);

	renderer render;

    std::vector<glm::vec3> verts = chunk.naive_mesh();

	render.add_mesh((GLfloat*)verts.data(), 3*verts.size());

	for(int i = 0; i < 5; i++){
	    glm::vec3 c= chunk.coord_conv(i);
	    printf("int: %d, float: %f, %f, %f\n", i, c.x, c.y, c.z);
	}
	while(render.is_open()) render.draw();
	return 0;
}
