#pragma once

#include "Scene.hpp"
#include "Game.hpp"
#include "LiveGame.hpp"
#include <iostream>

class MainMenu : public Scene
{
public:
				MainMenu(Game&);
				~MainMenu() final;

	void		onInit() final;
	void		onResume() final;
	void		onPause() final;
	void		onEnd() final;

	void		draw(sf::RenderWindow&) final;
	void		processEvent(const sf::Event&, sf::RenderWindow&) final;

    void        set_live_game(b_matrix& state) final;

private:
	sf::Font	f_font;

	SelectBox   sb_play;
    SelectBox   sb_random;
    SelectBox   sb_random_up;
    SelectBox   sb_random_down;
    SelectBox   sb_random_value;
	SelectBox	sb_exit;

    int         i_random;

    LiveGame    lg_setup;
};
