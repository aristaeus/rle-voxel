#include <iostream>

#include "component.hpp"
#include "rle.hpp"
#include "world.hpp"
#include "wrap.hpp"

int main(){
	SFWindow render;
	Game game;
	game.init(render.get_window());

	while(render.is_open()){
	    render.draw();
	    game.update();
	}
	return 0;
}
