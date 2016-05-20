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
	std::vector<GLfloat> verts = add_square(-1, -1, -1, 1, -1, 1);
	std::vector<GLfloat> verts2 = add_square(-1, -1, -1, 1, 1, -1);
	verts.insert(verts.begin(), verts2.begin(), verts2.end());

	render.add_mesh(verts.data(), verts.size());
	while(render.is_open()) render.draw();
	return 0;
}
