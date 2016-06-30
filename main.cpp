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

    std::vector<glm::vec3> volume = gen_volume(glm::vec3(0.0,0.0,0.0),
            glm::vec3(1.0,1.0,1.0));

	// render.add_mesh((GLfloat*)verts.data(), 3*verts.size());
    printf("size: %d\n", volume.size());
    for(int i = 0; i < volume.size(); i++){
        printf("x: %lf y: %lf z %lf\n", volume[i].x,volume[i].y,volume[i].z);
    }
    render.add_mesh((GLfloat*)volume.data(), 3*volume.size());

	for(int i = 0; i < 5; i++){
	    glm::vec3 c= chunk.coord_conv(i);
	    // printf("int: %d, float: %f, %f, %f\n", i, c.x, c.y, c.z);
	}
	while(render.is_open()) render.draw();
	return 0;
}
