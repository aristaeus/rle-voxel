#include <cmath>
#include <cstdio>
#include <fstream>
#include <string>

#include "wrap.hpp"
#include "component.hpp"


Renderer::Renderer(){
    run = true;

    sf::ContextSettings s;
    s.antialiasingLevel = 4;
    s.depthBits = 24;

    window.create(sf::VideoMode(800,600), "stuff", sf::Style::Default, s);
    window.setVerticalSyncEnabled(true);

    s = window.getSettings();
    printf("GL: %d.%d\nAA: %d\nDB:%d\nSB: %d\n", s.majorVersion, s.minorVersion, s.antialiasingLevel, s.depthBits, s.stencilBits);
}

Renderer::~Renderer(){

}

void Renderer::draw(){
    sf::Event event;
    while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            window.close();
            run = false;
        }
        if(event.type == sf::Event::KeyPressed){
            switch(event.key.code){
                case sf::Keyboard::Escape:
                    window.close();
                    run = false;
                    break;
                default:
                    break;
            }
        }
    }

    window.display();
}

bool
Renderer::is_open(){
    return run;
}

sf::Window*
Renderer::get_window(){
    return &window;
}
