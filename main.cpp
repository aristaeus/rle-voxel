#include "rle.hpp"
#include "wrap.hpp"

int main(){
	rle_chunk chunk(5);
	chunk.insert(0, 0);
	chunk.insert(5, 1);
	chunk.insert(16, 2);
	chunk.insert(20, 3);
	chunk.insert(30, 0);

	chunk.print_chunk();

	renderer render;
	while(render.is_open()) render.draw();
	return 0;
}
