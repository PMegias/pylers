#include "Game.hpp"
#include <iostream>
#include <fstream>

int main() {
    Game game;
    std::fstream pob_file(pobl_csv);
    pob_file.close();

    std::fstream naci_file(naci_csv);
    naci_file.close();

    std::fstream mort_file(mort_csv);
    mort_file.close();


    game.run();

    std::cout << "Cerrado con X" << std::endl;
    //Limpiamos ficheros al acabar todo
    std::string argv = "rm -rf " + mort_csv + " " + mort_png +" " +  
                        naci_csv +" " +  naci_png +" " +  
                        pobl_csv +" " +  pobl_png;
    
    std::cout << argv << std::endl;
    system(argv.c_str());


    return 0;
}
