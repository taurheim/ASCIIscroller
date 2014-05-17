#include <vector>
#include <iostream>

void runPhysics(Entity& ent, char mesh[][95]){
    SHORT *posx = &ent.position.X;
    SHORT *posy = &ent.position.Y;

    if(mesh[*posy+1][*posx] == ' '){
        *posy = *posy + 1;
    }


    //std::cout << "(" << *posx << "," << *posy << ")";
}
