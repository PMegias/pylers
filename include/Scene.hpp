#ifndef SCENE_HPP
#define SCENE_HPP

#pragma once
#include "SelectBox.hpp"

#include <SFML/Graphics.hpp>

class Game;

class Scene
{
public:
                        Scene(Game&);
    virtual             ~Scene();

    virtual void        onInit();
    virtual void        onResume();
    virtual void        onPause();
    virtual void        onEnd();

    virtual void        update();
    virtual void        draw(sf::RenderWindow&);
    virtual void        processEvent(const sf::Event&, sf::RenderWindow&);

    void                init();
    void                pause();
    void                resume();                                                                                     
    void                end();

    void                restart();

    enum SceneState
    {   
        UNINITIALIZED,
        INITIALIZED,
        RUNNING,
        PAUSED,
        ENDED,

        NUM_STATES
    };  

    Scene::SceneState   getCurrentState() const;

    enum SceneType
    {   
        /* MAIN_MENU, */
        GAME,
        /* PAUSE, */

        NUM_SCENES
    };  
    
    static Scene*       create(Game&, Scene::SceneType);

    virtual void        setPausedScene(Scene*);

    protected:
    Game&               g_game;

private:
    SceneState          ss_currentState;
};
#endif // SCENE_HPP
