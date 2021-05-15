#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

#pragma once

#include "Scene.hpp"
#include "Game.hpp"
#include "SelectBox.hpp"
#include "LiveGame.hpp"
#include <iostream>

class GameScene : public Scene
{
public:
                GameScene(Game&);
                ~GameScene() final;

    void        onInit() final;
    void        onResume() final;
    void        onPause() final;
    void        onEnd() final;

    void        processEvent(const sf::Event&, sf::RenderWindow&) final;
    void        draw(sf::RenderWindow&) final;
    void        update() final;
    void        generate_plots(int, int, int, int);

    void        set_live_game(b_matrix& ) final;

private:

    sf::Time    t_frameTime;
    sf::Time    t_currentFrameTime;

    sf::Font    f_font;

    SelectBox   sb_days;
    SelectBox   sb_pause;
    SelectBox   sb_grid;
    SelectBox   sb_switch_mode;
    SelectBox   sb_reset;
    SelectBox   sb_main_menu;
    SelectBox   sb_exit;

    bool        b_pause;
    bool        b_lost_focus;

    LiveGame    lg_game;

    sf::Sprite  sp_poblation;
    sf::Sprite  sp_births;
    sf::Sprite  sp_deaths;
};

#endif // GAME_SCENE_HPP
