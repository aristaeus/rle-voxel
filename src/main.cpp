#include <iostream>

#include "rle.hpp"
#include "world.hpp"
#include "wrap.hpp"

int main(){
	renderer render;

	World world;
	world.init(&render);

	while(render.is_open()) render.draw();
	return 0;
}
