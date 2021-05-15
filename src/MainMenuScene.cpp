#include "MainMenuScene.hpp"
#include "GameScene.hpp"

MainMenu::MainMenu(Game& game) : Scene(game) {}
MainMenu::~MainMenu() {}

void MainMenu::onInit()
{
	Scene::onInit();
	std::cout << "onInit : MainMenu" << std::endl;

	f_font.loadFromFile(FONT_FILE);
	
	float w = 150, h = 75;
    float buttons_margin = 75.f;
	sf::Vector2f position = { 1050.f, 85.f };
    sf::Vector2f offset = { 20.f, 5.f };
	sb_play = SelectBox(1.f, w, h, position, s_play, f_font, offset);
	position.y += buttons_margin * 5;
	sb_exit = SelectBox(1.f, w, h, position, s_exit, f_font, offset);

	lg_setup.set_grid(true);
}

void MainMenu::onResume()
{
	Scene::onResume();
	std::cout << "onResume : MainMenu" << std::endl;
}

void MainMenu::onPause()
{
	Scene::onPause();
	std::cout << "onPause : MainMenu" << std::endl;
}

void MainMenu::onEnd()
{
	Scene::onEnd();
	std::cout << "onEnd : MainMenu" << std::endl;
	g_game.end();
}

void MainMenu::draw(sf::RenderWindow& window)
{
    lg_setup.draw(window);
	sb_play.draw(window);
	sb_exit.draw(window);
}

void MainMenu::processEvent(const sf::Event& event, sf::RenderWindow& window)
{
	if (sb_play.clicked(window, event)) {
		b_matrix state = lg_setup.get_full_state();
		auto scene = Scene::create(g_game, Scene::GAME);
		g_game.setActiveScene(scene);
		scene->set_live_game(state);
    }
	else if (sb_exit.clicked(window, event))
		end();

    lg_setup.processEvent(event, window);
}

void MainMenu::set_live_game(b_matrix& state)
{
    lg_setup.set_state(state);
}
