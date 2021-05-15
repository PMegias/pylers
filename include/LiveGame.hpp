#ifndef LIVE_GAME_HPP
#define LIVE_GAME_HPP

#pragma once

#include "SelectBox.hpp"
#include "Configuration.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

typedef std::vector<bool>               b_vector;
typedef std::vector<b_vector>           b_matrix;

typedef std::vector<sf::RectangleShape> rs_vector;
typedef std::vector<rs_vector>          rs_matrix;

class LiveGame 
{

private:
    bool check_rules(int, int);

    b_matrix update_state();

public:
    LiveGame();
    ~LiveGame();

    void processEvent(const sf::Event&, sf::RenderWindow&);
    void draw(sf::RenderWindow&);
    void update();

    void reset();

    bool get_grid() const;
    void set_grid(bool);

    bool get_epilepsia() const;
    void set_epilepsia(bool);

    int get_population() const;
    int get_birth() const;
    int get_death() const;
    int get_days() const;

    bool get_state(int, int) const;
    b_matrix get_full_state() const;
    void set_state(int, int, bool);
    void set_state(const b_matrix& );

private:

    b_matrix bm_state;
    rs_matrix rsm_squares;

    bool b_show_grid;
    bool b_modo_epilepsia_activado;

    int i_population;
    int i_birth;
    int i_death;
    int i_days;
};

#endif // LIVE_GAME_HPP