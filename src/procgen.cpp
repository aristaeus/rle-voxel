#include <iostream>

#include "procgen.hpp"

void
Terrain::init(){
    module.SetOctaveCount(8);
    module.SetFrequency(1);
    module.SetPersistence(0.1);
}

double
Terrain::get_value(glm::vec3 p){
    return 10*(1+module.GetValue(p.x/50, 11, p.z/50));
}
