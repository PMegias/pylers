#include "MainMenuScene.hpp"
#include "GameScene.hpp"

MainMenu::MainMenu(Game& game) : Scene(game) {}
MainMenu::~MainMenu() {}

void MainMenu::onInit()
{
	Scene::onInit();
	std::cout << "onInit : MainMenu" << std::endl;

	f_font.loadFromFile(FONT_FILE);

    i_random = 50;
	
	float w = 150, h = 75;
    float buttons_margin = 75.f;
	sf::Vector2f position = { 1050.f, 85.f };
	sb_play = SelectBox(1.f, w, h, position, s_play, f_font, { 40.5f, 15.f });
    position.y += buttons_margin;
    sb_random = SelectBox(1.f, w, h, position, s_random, f_font, { 25.f, 15.f });
    sf::Vector2f aux = position;
    aux.x += w + 1.f;
    sb_random_up = SelectBox(.75, w / 2, h / 2, aux, "up", f_font, { 25.f, 2.5f });
    aux.y += h / 2;
    sb_random_down = SelectBox(.75, w / 2, h / 2, aux, "down", f_font, { 10.f, 2.5f });
    aux.x += w / 2;
    aux.y -= h / 2;
    sb_random_value = SelectBox(1, h, h, aux, std::to_string(i_random) + "%", f_font, { 15.f, 15.f });
	position.y += buttons_margin * 4;
	sb_exit = SelectBox(1.f, w, h, position, s_exit, f_font, { 47.5f, 15.f });

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
    sb_random_value.set_text(std::to_string(i_random) + "%");

    lg_setup.draw(window);
	sb_play.draw(window);
    sb_random.draw(window);
    sb_random_up.draw(window);
    sb_random_down.draw(window);
    sb_random_value.draw(window);
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
    else if (sb_random.clicked(window, event)) lg_setup.randomize_state(i_random);
    else if (sb_random_up.clicked(window, event) && i_random < 100) i_random += 10;
    else if (sb_random_down.clicked(window, event) && i_random > 0) i_random -= 10;
	else if (sb_exit.clicked(window, event))
		end();

    lg_setup.processEvent(event, window);
}

void MainMenu::set_live_game(b_matrix& state)
{
    lg_setup.set_state(state);
}
