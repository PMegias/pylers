#include "Game.hpp"
#include <iostream>
#include <unistd.h>

Game::Game() : s_activeScene(nullptr), s_backgroundScene(nullptr) {}

Game::~Game()
{
    if (s_activeScene) delete s_activeScene;
    if (s_backgroundScene) delete s_backgroundScene;
}
    
void Game::run()        
{   
    init(); 
    mainLoop();
}   
    
void Game::init()       
{
    // sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    rw_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), TITLE, sf::Style::Titlebar | sf::Style::Close);
    rw_window.setKeyRepeatEnabled(false);
    
    Scene* scene = Scene::create(*this, Scene::GAME);
    setActiveScene(scene);

    b_redraw = true;

    cl_clock.restart();
}   
        
void Game::mainLoop()
{       
    while (rw_window.isOpen()) {
        if (cl_clock.getElapsedTime().asSeconds() >= 1.f / FPS) {
            b_redraw = true;
            cl_clock.restart();
        }

        events();

        if (b_redraw) {
            generate_plots();
            update();
            draw();
            b_redraw = false;
        }

        scene();
    }
}

void Game::generate_plots(){
    int pid = fork();
    if (pid != 0){
        // int execv(const char *pathname, char *const argv[]);
        // char * argv[] = {" -e \"set term png ; set output 'plot.png' ; plot sin(x)\"" };
        //char * argv[];
        // int ret = execv("/bin/gnuplot", argv );
        //execv("ls", argv );
        //std::cout << "exec ret " << ret << std::endl;
        std::cout << "HIJI "  << std::endl;
        exit(0);
    }
     //padre espera aqui por ejemplo
    std::cout << "PAPI " << std::endl;

}

void Game::events()
{   
    sf::Event event;
    while (rw_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) rw_window.close();
        if (s_activeScene) s_activeScene->processEvent(event, rw_window);
    }   
}

void Game::update()
{
    if (s_activeScene) s_activeScene->update();
}

void Game::draw()
{
    rw_window.clear();
    if (s_activeScene) s_activeScene->draw(rw_window);
    rw_window.display();
}

void Game::end()
{
    rw_window.close();
}

void Game::setActiveScene(Scene* scene)
{
    if (s_activeScene) delete s_activeScene;
    s_activeScene = scene;
}

void Game::setBackgroundScene(Scene* scene)
{
    if (s_backgroundScene) delete s_backgroundScene;
    s_backgroundScene = scene;
}

void Game::scene()
{
    if (s_activeScene) {
        switch (s_activeScene->getCurrentState())
        {
        case Scene::UNINITIALIZED:
            s_activeScene->init();
            break;
        case Scene::INITIALIZED:
            s_activeScene->resume();
            break;
        case Scene::RUNNING: break;
        case Scene::PAUSED:
            pauseActiveScene();
            break;
        case Scene::ENDED:
            terminateActiveScene();
            break;
        default:
            break;
        }
    }
}

void Game::pauseActiveScene()
{
    if (s_backgroundScene) {
        Scene* aux = s_activeScene;
        s_activeScene = s_backgroundScene;
        s_backgroundScene = aux;
    }
    else s_activeScene->resume();
}

void Game::terminateActiveScene()
{
    if (s_activeScene) {
        delete s_activeScene;
        s_activeScene = nullptr;
    }

    if (s_backgroundScene) {
        s_activeScene = s_backgroundScene;
        s_backgroundScene = nullptr;
    }
    else rw_window.close();
}

sf::Clock Game::getClock()
{
    return cl_clock;
}
