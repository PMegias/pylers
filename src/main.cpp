#include "Game.hpp"
#include <iostream>

int main() {
    Game game;
    game.run();

    std::cout << "Cerrado con X" << std::endl;
    //Limpiamos ficheros al acabar todo
    std::string argv = "rm -rf " + mort_csv + " " + mort_png +" " +  
                        naci_csv +" " +  naci_png +" " +  
                        pobl_csv +" " +  pobl_png;
    
    std::cout << argv << std::endl;
    //system(argv.c_str());


    return 0;
}
