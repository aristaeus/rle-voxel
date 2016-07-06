#include <fstream>
#include <iostream>


#include "component.hpp"

void
Game::init(sf::Window* window){
    vaos.init(this, window);
    chunks.init(16,this);
    // help me
    player = base_components.find(0);
}

void
Game::update(){
    chunks.update_chunks();
    vaos.update();
}

int
Game::new_component(glm::vec3 pos){
    int id = base_components.size();
    BaseComponent base;
    base.position = pos;
    base_components.insert(std::pair<int,BaseComponent>(id,base));
    return id;
}
