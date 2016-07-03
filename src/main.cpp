#include <iostream>

#include "rle.hpp"
#include "world.hpp"
#include "wrap.hpp"

int main(){
	Renderer render;

	World world;
	world.init(&render, 3);

	while(render.is_open()) render.draw();
	return 0;
}
