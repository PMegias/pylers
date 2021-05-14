#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
//#include "boton.h"

//mt19937 rng;

using namespace std;
using namespace sf;

typedef vector<bool> b_vector;
typedef vector<b_vector> b_matrix;          // El objeto para cálculo

typedef vector<RectangleShape> rs_vector;
typedef vector<rs_vector> rs_matrix;        // El objeto dibujable por SFML

bool modo_epilepsia_activado = false;


const int WINDOW_HEIGHT = 1000;
const int WINDOW_WIDTH = 1000;
const int N = 50;
const int M = 50;
b_matrix state(N, b_vector(M, false));


void draw(RenderWindow& window, const b_matrix& state, rs_matrix& squares) {
   for (int i = 0; i < N; ++i) {
      for(int j = 0; j < M; ++j) {
         squares[i][j].setOutlineColor(Color::White);
         squares[i][j].setOutlineThickness(1.f);

         if (state[i][j]) {
            if (modo_epilepsia_activado) squares[i][j].setFillColor(Color(rand() % 256, rand() % 256, rand() % 256));
            else squares[i][j].setFillColor(Color::White);

         } 
         else squares[i][j].setFillColor(Color::Black);    
         window.draw(squares[i][j]);
      }
   }
}


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
bool check_normas(int x, int y){ // Como la amtriz es global, exploramos desde el centro, la celula
    int cont = 0;
    if(x < 2 or x > 48 or y < 2 or y > 48) return false; // dejemos los bordes para mas adelante

    // Aplicando norma 3: (RE)nacimientos
    /*if(!state[x][y]){
        for(int i = y-1; i <= y+1; ++i){
            if(state[x-1][i]) cont++;
            if(state[x][i]) cont++;
            if(state[x+1][i]) cont++;
        }
        if(cont==3) return true;
        return false;
    }
    if(state[x][y]){
        for(int i = y-1; i <= y+1; ++i){
            if(state[x-1][i]) cont++;
            if(state[x][i]) cont++;
            if(state[x+1][i]) cont++;
        }
        cont--;
        if(cont==3 or cont==2) return true;
        return false;
    }*/

    for(int i = y-1; i <= y+1; ++i){
            if(state[x-1][i]) cont++;
            if(state[x][i]) cont++;
            if(state[x+1][i]) cont++;
    }
    if(!state[x][y] and cont == 3) return true; // norma 3
    else if(state[x][y] and (cont==3 or cont==4)) return true;
    return false;
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



int main() {
    const float FPS = 10.f;
    bool redraw = false;
    int dias=0;

    //b_matrix state(N, b_vector(M, false));
    //state[0][0] = state[1][1] = state[2][2] = state[0][9] = state[9][9] = true; //solo para ver k estos serán blancos
    //state[6][6] = state[6][5] = state [5][6] = true;
    
    //todo blanco
    /*for(int i = 0; i < N; ++i)
        for(int j = 0; j < M; ++j)
            state[i][j] = true;*/
    state[20][20]=state[20][21]=state[20][22]=state[19][22]=state[18][21]=true;

    rs_matrix squares(N, rs_vector(M, RectangleShape(Vector2f(WINDOW_WIDTH / N, WINDOW_HEIGHT / M))));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            squares[i][j].setPosition(Vector2f(i * WINDOW_HEIGHT / N, j * WINDOW_WIDTH / M));
        }
    } // Aqui indicamos dónde va cada cuadro dentro de la ventana del juego

    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Demo", Style::Titlebar | Style::Close);

    Event event;
    Clock clk;

    while(window.isOpen()) {

        if (clk.getElapsedTime().asSeconds() >= 1.f / FPS) {
            redraw = true;
            clk.restart();
        }

        while(window.pollEvent(event)) {
            if (event.type == Event::Closed) window.close();
        }

        if (redraw) {
            window.clear();
            state = update();
            draw(window, state, squares);
            window.display();
            redraw = false;

            //mierdas
            dias++;
            printf("Cantidad de dias --> %d \n", dias);
        }
    }
}
  