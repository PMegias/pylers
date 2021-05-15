#include "LiveGame.hpp"
#include <SFML/Graphics.hpp>
#include <random>

LiveGame::LiveGame()
{
    b_show_grid = false;
    b_modo_epilepsia_activado = false;

    i_population = i_birth = i_death = i_days = 0;

    bm_state = b_matrix(N, b_vector(M, false));
    rsm_squares = rs_matrix(N, rs_vector(M, sf::RectangleShape(sf::Vector2f(SIMULATION_WIDTH / N, SIMULATION_HEIGHT / M))));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (i == 0 || j == 0) bm_state[i][j] = true;
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            rsm_squares[i][j].setOutlineColor(sf::Color::White);
            rsm_squares[i][j].setPosition(sf::Vector2f(i * SIMULATION_WIDTH / N, j * SIMULATION_HEIGHT / M));
        }
    }
}

LiveGame::~LiveGame()
{

}

int mod (int a)
{ //mas ifes :3
   int ret = a % N;
   if(ret < 0)
     ret+=N;
   return ret;

   // return (ret < 0) ? ret + N : ret; 
}

bool LiveGame::check_rules(int x, int y)
{
    int cont = 0;
    i_birth = 0;
    i_death = 0;
    i_population = 0;
    for(int i = y-1; i <= y+1; ++i){
        if(bm_state[mod(x-1)][mod(i)]) cont++;
        if(bm_state[mod(x)][mod(i)]) cont++;
        if(bm_state[mod(x+1)][mod(i)]) cont++;
    }/*
    if(!state[x][y] and cont == 3) return true; // norma 3
    else if(state[x][y] and (cont==3 or cont==4)) return true;
    return false;
    */
    if(!bm_state[x][y] and cont == 3){
        i_birth++;
        i_population++;
        return true;
    } else {
        if(bm_state[x][y] and (cont==3 or cont==4)) {
            i_population++;
             return true;
        }
        else i_death++;
    }
    return false;
}

b_matrix LiveGame::update_state()
{
    b_matrix new_state(N, b_vector(M, false));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            new_state[i][j] = check_rules(i, j);
        }
    }
    return new_state;
}

void LiveGame::processEvent(const sf::Event& event, sf::RenderWindow& window) 
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
        int x = event.mouseButton.x;
        int y = event.mouseButton.y;

        if (x <= SIMULATION_WIDTH) {
            x /= SIMULATION_WIDTH / N;
            y /= SIMULATION_HEIGHT / M;

            bm_state[x][y] = true;
        }
    }
}

void LiveGame::draw(sf::RenderWindow& window)
{
    int r = rand() % 256;
    int g = rand() % 256;
    int b = rand() % 256;
    sf::Color random_color = sf::Color(r, g, b);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (b_show_grid) rsm_squares[i][j].setOutlineThickness(1.f);
            else rsm_squares[i][j].setOutlineThickness(0.f);

            if (bm_state[i][j]) {
                if (b_modo_epilepsia_activado) rsm_squares[i][j].setFillColor(random_color);
                else rsm_squares[i][j].setFillColor(sf::Color::White);
            } else rsm_squares[i][j].setFillColor(sf::Color::Black);

            window.draw(rsm_squares[i][j]);
        }
    }
}

void LiveGame::update()
{
    bm_state = update_state();
    ++i_days;
}

void LiveGame::reset()
{
    bm_state = b_matrix(N, b_vector(M, false));
}

bool LiveGame::get_grid() const
{
    return b_show_grid;
}

void LiveGame::set_grid(bool grid)
{
    b_show_grid = grid;
}

bool LiveGame::get_epilepsia() const
{
    return b_modo_epilepsia_activado;
}

void LiveGame::set_epilepsia(bool mode)
{
    b_modo_epilepsia_activado = mode;
}

int LiveGame::get_population() const
{
    return i_population;
}

int LiveGame::get_birth() const
{
    return i_birth;
}

int LiveGame::get_death() const
{
    return i_death;
}

int LiveGame::get_days() const
{
    return i_days;
}