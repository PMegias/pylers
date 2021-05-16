#include "GameScene.hpp"                                                                                              
#include <fstream>
#include <unistd.h>
#include <cmath>

GameScene::GameScene(Game& game) : Scene(game) {}
GameScene::~GameScene() {}

void GameScene::onInit()
{
    Scene::onInit();
    std::cout << "onInit : GameScene" << std::endl;

    f_font.loadFromFile(FONT_FILE);

    b_pause = false;
    b_lost_focus = false;

    float scale = 1.f;
    float width = 150, height = 75; 
    sf::Vector2f position = { 1050.f, 10.f };
    float buttons_margin = 75.f;

    sb_days = SelectBox(scale, width, height, position, "0", f_font, { 67.5f, 15.f });
    
    position.y += buttons_margin;
    sb_pause = SelectBox(scale, width, height, position, s_play, f_font, { 40.5f, 15.f });

    position.y += buttons_margin;
    sb_grid = SelectBox(scale, width, height, position, s_add_grid, f_font, { 10.f, 15.f });
    
    position.y += buttons_margin;
    sb_switch_mode = SelectBox(scale, width, height, position, s_switch_colors, f_font, { 25.f, 5.f });

    position.y += buttons_margin;
    sb_reset = SelectBox(scale, width, height, position, s_reset, f_font, { 30.f, 15.f });

    position.y += buttons_margin;
    sb_main_menu = SelectBox(scale, width, height, position, s_main_menu, f_font, { 35.f, 2.5f });

    position.y += buttons_margin;
    sb_exit = SelectBox(scale, width, height, position, s_exit, f_font, { 47.5f, 15.f });

    sp_poblation.setPosition(sf::Vector2f(1250, 10));
    sp_births.setPosition(sf::Vector2f(1250, 310));
    sp_deaths.setPosition(sf::Vector2f(1250, 610));
}

void GameScene::onResume()
{    
    Scene::onResume();
    std::cout << "onResume : GameScene" << std::endl;
} 

void GameScene::onPause()
{
    Scene::onPause();
    std::cout << "onPause : GameScene" << std::endl;
}   

void GameScene::onEnd()
{   
    Scene::onEnd();
    std::cout << "onEnd : GameScene" << std::endl;

}   
    
void GameScene::processEvent(const sf::Event& event, sf::RenderWindow& window)
{
    if (sb_pause.clicked(window, event)) b_pause = !b_pause;
    if (sb_grid.clicked(window, event)) lg_game.set_grid(!lg_game.get_grid());
    if (sb_switch_mode.clicked(window, event)) lg_game.set_epilepsia(!lg_game.get_epilepsia());
    if (sb_reset.clicked(window, event)) lg_game.reset();
    if (sb_main_menu.clicked(window, event)) {
        b_matrix state = lg_game.get_full_state();
        auto scene = Scene::create(g_game, Scene::MAIN_MENU);
        g_game.setActiveScene(scene);
        scene->set_live_game(state);
    }
    if (sb_exit.clicked(window, event)) end();

    lg_game.processEvent(event, window);
}

void GameScene::draw(sf::RenderWindow& window)
{
    if (lg_game.get_days() == 0) {
        sb_pause.set_text(s_play);
        sb_pause.set_offset(sf::Vector2f(40.5f, 15.f));
    } else if (b_pause) {
        sb_pause.set_text(s_resume);
        sb_pause.set_offset(sf::Vector2f(22.5f, 15.f));
    } else {
        sb_pause.set_text(s_pause);
        sb_pause.set_offset(sf::Vector2f(30.f, 15.f));
    }

    if (lg_game.get_grid()) sb_grid.set_text(s_no_grid);
    else sb_grid.set_text(s_add_grid);

    int days = lg_game.get_days();
    sb_days.set_text(std::to_string(days));
    sf::Vector2f offset = { 67.5f, 15.f };
    if (days > 0) {
        int decimales = floor(log(days) / log(10));
        offset.x -= 7.5f * decimales;
    }
    sb_days.set_offset(offset);

    sb_days.draw(window);
    sb_pause.draw(window);
    sb_grid.draw(window);
    sb_switch_mode.draw(window);
    sb_reset.draw(window);
    sb_main_menu.draw(window);
    sb_exit.draw(window);

    sf::Texture texturep, textureb, textured;
    if (texturep.loadFromFile(pobl_png)) {
        sp_poblation.setTexture(texturep);
        window.draw(sp_poblation);
    }

    if (textureb.loadFromFile(naci_png)) {
        sp_births.setTexture(textureb);
        window.draw(sp_births);
    }

    if (textured.loadFromFile(mort_png)) {
        sp_deaths.setTexture(textured);
        window.draw(sp_deaths);
    }
    
    lg_game.draw(window);
}

void GameScene::update()
{
    if (!b_pause) {
        int days = lg_game.get_days();
        int population = lg_game.get_population();
        int naci = lg_game.get_birth();
        int mort = lg_game.get_death();        

        sf::Thread thread(&LiveGame::update, &lg_game);
        thread.launch();
        generate_plots(days, population, naci, mort);
        //lg_game.update();
        //thread.wait();
    }
}



void GameScene::generate_plots(int days, int population, int naci, int mort){

    std::string argv;
    std::string max_population = std::to_string(N * N);
    // Plots de poblacion DATOS
    std::ofstream pobl_file(pobl_csv, std::ofstream::out | std::ofstream::app);
    pobl_file << std::to_string(days) + ",";
    pobl_file << std::to_string(population) + "\n";
    pobl_file.close();
    argv = "gnuplot -c " + PLOTTER_FILE + " " + pobl_ftitle + " " + pobl_csv + " " + pobl_png + " " + max_population;
    system(argv.c_str());


    //Datos de Nacis-mientos
    std::ofstream naci_file(naci_csv, std::ofstream::out | std::fstream::app);
    naci_file << std::to_string(days) + ",";
    naci_file << std::to_string(naci) + "\n";
    naci_file.close();
    argv = "gnuplot -c " + PLOTTER_FILE + " " + naci_ftitle + " " + naci_csv + " " + naci_png + " " + max_population;
    system(argv.c_str());


    // Datos de Morticiones
    std::ofstream mort_file(mort_csv, std::ofstream::out | std::fstream::app);
    mort_file << std::to_string(days) + ",";
    mort_file << std::to_string(mort) + "\n";
    mort_file.close();
    argv = "gnuplot -c " + PLOTTER_FILE + " " + mort_ftitle + " " + mort_csv + " " + mort_png + " " + max_population;
    system(argv.c_str());

}

void GameScene::set_live_game(b_matrix& lg)
{
    lg_game.set_state(lg);
}
