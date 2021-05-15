#include "MainMenuScene.hpp"

MainMenu::MainMenu(Game& game) : Scene(game) {}
MainMenu::~MainMenu() {}

void MainMenu::onInit()
{
	Scene::onInit();
	std::cout << "onInit : MainMenu" << std::endl;

	f_font.loadFromFile(FONT_FILE);
	
	float w = 150, h = 75;
	sf::Vector2f position = { 40.f, 10.f };
    sf::Vector2f offset = { 20.f, 5.f };
	position += {0, 100.f };
	sb_play = SelectBox(1.f, w, h, position, s_play, f_font, offset);
	position.y += 75.f;
	sb_exit = SelectBox(1.f, w, h, position, s_exit, f_font, offset);
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
	sb_play.draw(window);
	sb_exit.draw(window);
}

void MainMenu::processEvent(const sf::Event& event, sf::RenderWindow& window)
{
	if (sb_play.clicked(window, event))
		g_game.setActiveScene(Scene::create(g_game, Scene::GAME));
	else if (sb_exit.clicked(window, event))
		end();
}
