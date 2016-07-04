#include <iostream>

#include "component.hpp"
#include "rle.hpp"
#include "world.hpp"
#include "wrap.hpp"

int main(){
	Renderer render;
	Game game;

	World world;
	world.init(&render, 3, &game);

	while(render.is_open()) render.draw();
	return 0;
}
