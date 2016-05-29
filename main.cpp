#include "rle.hpp"
#include "wrap.hpp"

int main(){
	rle_chunk chunk(5);
	chunk.insert(0, 0);
	chunk.insert(5, 1);
	chunk.insert(16, 2);
	chunk.insert(20, 3);
	chunk.insert(30, 0);

	renderer render;
	std::vector<glm::vec3> verts = add_square(1, -1, 1, -1, -1, -1);
	std::vector<glm::vec3> verts2 = add_square(-1, -1, -1, 1, 1, -1);
	std::vector<glm::vec3> verts3 = add_square(-1, -1, -1, -1, 1, 1);
	std::vector<glm::vec3> verts4 = add_square(-1, 1, -1, 1, 1, 1);
	std::vector<glm::vec3> verts5 = add_square(-1, -1, 1, 1, 1, 1);
	std::vector<glm::vec3> verts6 = add_square(1, -1, -1, 1, 1, 1);
	verts.insert(verts.begin(), verts2.begin(), verts2.end());
	verts.insert(verts.begin(), verts3.begin(), verts3.end());
	verts.insert(verts.begin(), verts4.begin(), verts4.end());
	verts.insert(verts.begin(), verts5.begin(), verts5.end());
	verts.insert(verts.begin(), verts6.begin(), verts6.end());

	render.add_mesh((GLfloat*)verts.data(), 3*verts.size());
	while(render.is_open()) render.draw();
	return 0;
}
