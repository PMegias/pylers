#include "Scene.hpp"
#include "MainMenuScene.hpp"
#include "GameScene.hpp"
/* #include "PauseScene.h" */
        
Scene::Scene(Game& game) : g_game(game), ss_currentState(UNINITIALIZED) {}
Scene::~Scene() {}
            
void Scene::onInit()    {}
void Scene::onResume()  {}
void Scene::onPause()   {}
void Scene::onEnd()     {}
        
void Scene::update()    {}
void Scene::draw(sf::RenderWindow&) {}
void Scene::processEvent(const sf::Event&, sf::RenderWindow&) {}

void Scene::set_live_game(b_matrix& ) {}
void Scene::set_epilepsia(bool) {}
        
void Scene::init()
{           
    ss_currentState = INITIALIZED;
    onInit();
}       
    
void Scene::pause()
{
    ss_currentState = PAUSED;
    onPause();
}   
        
void Scene::resume()
{       
    ss_currentState = RUNNING;
    onResume();
}

void Scene::end()
{
    ss_currentState = ENDED;
    onEnd();
}       
    
void Scene::restart()
{   
    end();
    init();
}   
Scene::SceneState Scene::getCurrentState() const { return ss_currentState; }

Scene* Scene::create(Game& game, Scene::SceneType sceneType)
{
    Scene* scene = nullptr;

    switch (sceneType)
    {
    case Scene::MAIN_MENU:
        scene = new MainMenu(game);
        break;
    case Scene::GAME:
        scene = new GameScene(game);
        break;
    /* case Scene::PAUSE: */
    /*     scene = new PauseScene(game); */
    /*     break; */
    default:
        break;
    }

    return scene;
}

void Scene::setPausedScene(Scene*) {} 
