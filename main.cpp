#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <random>
#include "SelectBox.h"
#include "Configuration.hpp"

using namespace std;
using namespace sf;

typedef vector<bool> b_vector;
typedef vector<b_vector> b_matrix;          // El objeto para cálculo

typedef vector<RectangleShape> rs_vector;
typedef vector<rs_vector> rs_matrix;        // El objeto dibujable por SFML

typedef vector<SelectBox> sb_buttons;       // Los botoncicos

//#define N 50
//#define M 50
b_matrix state;
rs_matrix squares;
sb_buttons buttons;

int population;
int birth;
int death;
bool redraw = false;
int dias = 0;
bool pause = false;
bool lost_focus = false;


void draw(RenderWindow& window, const b_matrix& state, rs_matrix& squares) {
    int r = rand() % 256;
    int g = rand() % 256;
    int b = rand() % 256;
    for (int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
            squares[i][j].setOutlineColor(Color::White);
            squares[i][j].setOutlineThickness(1.f);

            if (state[i][j]) {
                if (modo_epilepsia_activado) squares[i][j].setFillColor(Color(r, g, b));
                else squares[i][j].setFillColor(Color::White);

            }
            else squares[i][j].setFillColor(Color::Black);    
            window.draw(squares[i][j]);
        }
    }
}

/*
void draw_graphic(){
    population += birth - death;
}
*/


/*bool check_normas(b_matrix& mini_state){ //Se checkean 8 vecinos

    // Cuando estas muerto, revives si tienes 3 vecinos vivos
    if(!mini_state[1][1]){
        int cont = 0;
        for(int i=0; i < 3; ++i){
            if(mini_state[0][i]) cont++;
            if(mini_state[1][i]) cont++;
            if(mini_state[2][i]) cont++;
        }
        if (cont == 3) return true;
        return false;
    }

}*/
/*
Normas del juego de la vida:
  1- Soledad:     Si estas vivo y tienes menos de 2 vecinos o mas de 3 vecinos vivos, mueres
  2- Simbiosis:   Si estas vivo y tienes 2 o 3 vecinos vivos, vives
  3- (RE)Nacimientos: Si estas muerta y tienes 3 vecinos vivos, se vuelve una celda viva

*/
int mod (int a)
{ //mas ifes :3
   int ret = a % N;
   if(ret < 0)
     ret+=N;
   return ret;

   // return (ret < 0) ? ret + N : ret;
   
}

bool check_normas(int x, int y){ // Como la matriz es global, exploramos desde el centro, la celula
    int cont = 0;

    for(int i = y-1; i <= y+1; ++i){
        if(state[mod(x-1)][mod(i)]) cont++;
        if(state[mod(x)][mod(i)]) cont++;
        if(state[mod(x+1)][mod(i)]) cont++;
    }
    if(!state[x][y] and cont == 3) return true; // norma 3
    else if(state[x][y] and (cont==3 or cont==4)) return true;
    return false;
    /*
    
    */
}

b_matrix update() {
   b_matrix new_state(state);
   
   for (int i = 0; i < N; ++i) {
      for (int j = 0; j < M; ++j) {

         new_state[i][j] = check_normas(i,j);
      }
   }
   return new_state;
}

void simulation() {
    state = update();
    ++dias;
}

void draw_all(RenderWindow& window) {
    window.clear();
    draw(window, state, squares);
    buttons[0].set_text(to_string(dias));
    if(pause) buttons[1].set_text(s_Resume);
    else buttons[1].set_text(s_Pausa);
    buttons[0].draw(window);
    buttons[1].draw(window);
    window.display();
}

int main() {
    

    state = b_matrix(N, b_vector(M, false));
    squares = rs_matrix(N, rs_vector(M, RectangleShape(Vector2f(SIMULATION_WIDTH / N, SIMULATION_HEIGHT / M))));

    //todo blanco
    /*for(int i = 0; i < N; ++i)
        for(int j = 0; j < M; ++j)
            if (i==0 or j == 0) state[i][j] = true;*/

    //state[20][30]=state[20][31]=state[20][32]=state[19][32]=state[18][31]=true; // :3


    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            squares[i][j].setPosition(Vector2f(i * SIMULATION_HEIGHT / N, j * SIMULATION_WIDTH / M));
        }
    } // Aqui indicamos dónde va cada cuadro dentro de la ventana del juego

    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Demo", Style::Titlebar | Style::Close);

    Event event;
    Clock clk;

    //Botonsitoss
    Vector2f posb1(1050,20);
    Vector2f off_b1(20, 5);
    float heigh_b1 = 75;
    float width_b1 = 150;
    Font font;
    font.loadFromFile("res/fonts/font.ttf");


    buttons.push_back(SelectBox(1, width_b1, heigh_b1,posb1, to_string(dias), font, off_b1)); // boton con el contador de dias
    buttons.push_back(SelectBox(1, width_b1, heigh_b1, Vector2f(1050, 915), s_Pausa, font, Vector2f(20, 5))); // boton pause / resume

    while(window.isOpen()) {

        if (clk.getElapsedTime().asSeconds() >= 1.f / FPS) {
            redraw = true;
            clk.restart();
        }

        while(window.pollEvent(event)) {
            if (event.type == Event::Closed) window.close();
            if (buttons[1].clicked(window, event)) pause = !pause;

            if (event.type == Event::LostFocus) pause = true, lost_focus = true;
            if (event.type == Event::GainedFocus && lost_focus) pause = false, lost_focus = false;

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
                //state[x][y] = true;
                int x = event.mouseButton.x;
                int y = event.mouseButton.y;

                if (x <= SIMULATION_WIDTH) {
                    x /= SIMULATION_HEIGHT / N;
                    y /= SIMULATION_WIDTH / M;

                    state[x][y] = true;
                    std::cout << "mouse x: " << x << std::endl;
                    std::cout << "mouse y: " << y << std::endl;
                }
            }
        }
        
        if (redraw) {
            if (!pause) simulation();
            draw_all(window);

            redraw = false;
        }
    }
}