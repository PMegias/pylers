#include "LiveGame.hpp"
#include "utils.hpp"
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
   /*if(ret < 0)
     ret+=N;
   return ret;*/  
   //int sign = (-(ret < 0) + 1);  // if v < 0 then 0, else 1. 
   return (-(ret < 0) + 1)*(ret) + (1-(-(ret < 0) + 1))*(N-1);
}

bool LiveGame::check_rules(int x, int y)
{
    int cont = 0;
    int aux;
    
    for(int i = y-1; i <= y+1; ++i){
        aux = mod(i);
        /*
        if(bm_state[mod(x-1)][aux]) cont++;
        if(bm_state[mod(x)][aux]) cont++;
        if(bm_state[mod(x+1)][aux]) cont++;
        */
        cont += (bm_state[mod(x-1)][aux]);
        cont += (bm_state[mod(x)][aux]);
        cont += (bm_state[mod(x+1)][aux]);
        
    }

    if(!bm_state[x][y] and cont == 3){
        i_birth++;
        i_population++;
        return true;
    } else {
        if(bm_state[x][y] and (cont==3 or cont==4)) {
            i_population++;
             return true;
        }
        else if(bm_state[x][y]) i_death++;
    }
    return false;
    
}

b_matrix LiveGame::update_state()
{
    i_birth = 0;
    i_death = 0;
    i_population = 0;
    b_matrix new_state(N, b_vector(M, false));
    int j;
    #pragma omp parallel for private (j) schedule (static)
    for (int i = 0; i < N; ++i) {
        for (j = 0; j < M; ++j) {
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

            bm_state[x][y] = !bm_state[x][y];
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
    i_days = 0;

    // Ponemos 10 rows con 0,0 para que en los plots no se vean cosas raras
    add_zero_dataset(pobl_csv);
    add_zero_dataset(naci_csv);
    add_zero_dataset(mort_csv);
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

bool LiveGame::get_state(int i, int j) const
{
    return bm_state[i][j];
}

b_matrix LiveGame::get_full_state() const
{
    return bm_state;
}

void LiveGame::set_state(int i, int j, bool value)
{
    bm_state[i][j] = value;
}

void LiveGame::set_state(const b_matrix& state)
{
    bm_state = state;
}

void LiveGame::randomize_state(int threshold)
{
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            bm_state[i][j] = ((rand() % 100) + 1) <= threshold;
        }
    }
}
