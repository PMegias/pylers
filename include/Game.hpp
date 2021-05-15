#ifndef GAME_HPP
#define GAME_HPP

#pragma once
#include "Scene.hpp"
#include "Configuration.hpp"

class Game
{
public:
                        Game();
                        ~Game();

    void                run();
    void                end();

    void                setActiveScene(Scene*);
    void                setBackgroundScene(Scene*);

    Scene*              getActiveScene() const;

    sf::Clock           getClock();

private:
    void                init();
    void                mainLoop();

    void                update();
    void                draw();
    void                events();
    void                scene();

    void                pauseActiveScene();
    void                terminateActiveScene();

    sf::RenderWindow    rw_window;
    sf::Clock           cl_clock;

    Scene*              s_activeScene;
    Scene*              s_backgroundScene;

    bool                b_redraw;
};


#endif // GAME_HPP
