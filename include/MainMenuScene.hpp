#pragma once

#include "Scene.hpp"
#include "Game.hpp"
#include <iostream>

class MainMenu : public Scene
{
public:
								MainMenu(Game&);
								~MainMenu() final;

	void						onInit() final;
	void						onResume() final;
	void						onPause() final;
	void						onEnd() final;

	void						draw(sf::RenderWindow&) final;
	void						processEvent(const sf::Event&, sf::RenderWindow&) final;

private:
	sf::Font					f_font;

	SelectBox					sb_play;
	SelectBox					sb_exit;
};
