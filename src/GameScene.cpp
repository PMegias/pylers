#include "GameScene.hpp"

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
    sf::Vector2f offset = { 20.f, 5.f };
    float buttons_margin = 75.f;

    sb_days = SelectBox(scale, width, height, position, "0", f_font, offset);
    
    position.y += buttons_margin;
    sb_pause = SelectBox(scale, width, height, position, s_pause, f_font, offset);

    position.y += buttons_margin;
    sb_grid = SelectBox(scale, width, height, position, s_add_grid, f_font, offset);;
    
    position.y += buttons_margin;
    sb_switch_mode = SelectBox(scale, width, height, position, s_switch_colors, f_font, offset);;

    position.y += buttons_margin;
    sb_reset = SelectBox(scale, width, height, position, s_reset, f_font, offset);
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
    /* if (event.type == sf::Event::KeyPressed) { */
    /*     if (event.key.code == sf::Keyboard::Escape) { */
    /*         pause(); */
    /*         g_game.setActiveScene(Scene::create(g_game, Scene::PAUSE)); */
    /*     } */      
    /* } */

    /* b_background.processEvents(event); */
    /* p_player.processEvents(event, window); */

    if (sb_pause.clicked(window, event)) b_pause = !b_pause;
    if (sb_grid.clicked(window, event)) lg_game.set_grid(!lg_game.get_grid());
    if (sb_switch_mode.clicked(window, event)) lg_game.set_epilepsia(!lg_game.get_epilepsia());
    if (sb_reset.clicked(window, event)) lg_game.reset();

    lg_game.processEvent(event, window);
}

void GameScene::draw(sf::RenderWindow& window)
{
    if (b_pause) {
        sb_pause.set_text(s_resume);
    } else {
        sb_pause.set_text(s_pause);
    }

    if (lg_game.get_grid()) sb_grid.set_text(s_no_grid);
    else sb_grid.set_text(s_add_grid);

    sb_days.set_text(std::to_string(lg_game.get_days()));

    sb_days.draw(window);
    sb_pause.draw(window);
    sb_grid.draw(window);
    sb_switch_mode.draw(window);
    sb_reset.draw(window);

    lg_game.draw(window);
}

void GameScene::update()
{
    if (!b_pause) lg_game.update();
}
