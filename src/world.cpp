#include "world.hpp"

void
World::init(renderer* render){
	int array[] = {0, 1, 1, 1, 1,
	               1, 1, 0, 0, 0,
	               0, 0, 1, 1, 1,
	               0, 0, 1, 1, 1,
	               0, 0, 1, 1, 1,
	               1, 1 };

    for(int i = 0; i < 9; i++){
        chunks[i].init(array,3);
        std::vector<glm::vec3> verts = chunks[i].less_naive();
        glm::vec3 pos ((i%3)*3, 0, (i/3)*3);
	    render->add_mesh((GLfloat*)verts.data(), 3*verts.size(),pos);
    }
}
