#include "LiveGame.hpp"
#include "utils.hpp"
#include <SFML/Graphics.hpp>
#include <random>

LiveGame::LiveGame()
{
    b_show_grid = false;
    b_modo_epilepsia_activado = false;

    i_population = i_birth = i_death = i_days = 0;

    tx_background.loadFromFile(BACKGROUND_FILE);
    /* tx_background.loadFromFile(BACKGROUND_FILE_SMALL); */
    tx_background.setSmooth(true);
    /* tx_background.setRepeated(true); */
    
    /* sf::IntRect bounds(sf::FloatRect(0.f, 0.f, 1000.f, 1000.f)); */
    /* sp_background = sf::Sprite(tx_background, bounds); */
    sp_background = sf::Sprite(tx_background);

    resize(N, M);
}

LiveGame::~LiveGame()
{

}

int mod (int a, int n)
{ //mas ifes :3
   int ret = a % n;
   if(ret < 0)
     ret+=n;
   return ret;

   // return (ret < 0) ? ret + N : ret; 
}

void LiveGame::resize(int n, int m)
{
    bm_state = b_matrix(n, b_vector(m, false));
    rsm_squares = rs_matrix(n, rs_vector(m, sf::RectangleShape(sf::Vector2f(SIMULATION_WIDTH / n, SIMULATION_HEIGHT / m))));
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            rsm_squares[i][j].setOutlineColor(sf::Color::White);
            rsm_squares[i][j].setPosition(sf::Vector2f(i * SIMULATION_WIDTH / n, j * SIMULATION_HEIGHT / m));
        }
    }
}

bool LiveGame::check_rules(int x, int y)
{
    int cont = 0;
    
    for(int i = y-1; i <= y+1; ++i){
        if(bm_state[mod(x-1, bm_state.size())][mod(i, bm_state.size())]) cont++;
        if(bm_state[mod(x, bm_state.size())][mod(i, bm_state.size())]) cont++;
        if(bm_state[mod(x+1, bm_state.size())][mod(i, bm_state.size())]) cont++;
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
    
    /* if(!bm_state[x][y] and cont == 3){ */
    /*     i_birth++; */
    /*     i_population++; */
    /*     return true; */
    /* } else { */
    /*     if(bm_state[x][y] and (cont==3 or cont==4)) { */
    /*         i_population++; */
    /*         return true; */
    /*     } */
    /*     else i_death++; */
    /* } */
    /* return false; */
}

b_matrix LiveGame::update_state()
{
    i_birth = 0;
    i_death = 0;
    i_population = 0;
    b_matrix new_state(bm_state.size(), b_vector(bm_state[0].size(), false));
    int j;
    #pragma omp parallel for private(j)
    //#pragma omp simd private(j)
    for (int i = 0; i < (int)bm_state.size(); ++i) {
        for (j = 0; j < (int)bm_state[i].size(); ++j) {
            //std::cout << omp_get_thread_num() << std::endl;
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
            x /= SIMULATION_WIDTH / bm_state.size();
            y /= SIMULATION_HEIGHT / bm_state[0].size();

            bm_state[x][y] = !bm_state[x][y];
        }
    }
}

void LiveGame::draw(sf::RenderWindow& window)
{
    if (b_modo_epilepsia_activado) window.draw(sp_background);

    for (int i = 0; i < bm_state.size(); ++i) {
        for (int j = 0; j < bm_state[i].size(); ++j) {
            if (b_show_grid) rsm_squares[i][j].setOutlineThickness(1.f);
            else rsm_squares[i][j].setOutlineThickness(0.f);

            if (bm_state[i][j]) {
                if (b_modo_epilepsia_activado) rsm_squares[i][j].setFillColor(sf::Color::Transparent);
                else rsm_squares[i][j].setFillColor(sf::Color::White);
            } else rsm_squares[i][j].setFillColor(sf::Color::Black);

            /* if (b_modo_epilepsia_activado) rsm_squares[i][j].setFillColor(sf::Color::Transparent); */

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
    bm_state = b_matrix(bm_state.size(), b_vector(bm_state[0].size(), false));
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
    for (int i = 0; i < (int)bm_state.size(); ++i) {
        for (int j = 0; j < (int)bm_state[i].size(); ++j) {
            bm_state[i][j] = ((rand() % 100) + 1) <= threshold;
        }
    }
}

int LiveGame::get_size() const
{
    return bm_state.size();
}
