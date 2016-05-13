#include "wrap.hpp"

renderer::renderer(){
	run = true;
	window.create(sf::VideoMode(800,600), "stuff");
}

void renderer::draw(){
	sf::Event event;
	while(window.pollEvent(event)){
		if(event.type == sf::Event::Closed){
			window.close();
			run = false;
		}
	}
}

bool
renderer::is_open(){
	return run;
}
