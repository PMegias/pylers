#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;

typedef vector<bool> b_vector;
typedef vector<b_vector> b_matrix;          // El objeto para cálculo

typedef vector<RectangleShape> rs_vector;
typedef vector<rs_vector> rs_matrix;        // El objeto dibujable por SFML


const int WINDOW_HEIGHT = 500;
const int WINDOW_WIDTH = 500;
const int N = 50;
const int M = 50;

void draw(RenderWindow& window, const b_matrix& state, rs_matrix& squares) {
   for (int i = 0; i < N; ++i) {
      for(int j = 0; j < M; ++j) {
         squares[i][j].setOutlineColor(Color::Black);
         if (state[i][j]) squares[i][j].setFillColor(Color::White);
         else squares[i][j].setFillColor(Color::Blue);    
         window.draw(squares[i][j]);
      }
   }
}

int main() {
    const float FPS = 60.f;
    bool redraw = false;

    b_matrix state(N, b_vector(M, false));
    state[0][0] = state[1][1] = state[2][2] = state[0][9] = state[9][9] = true; //solo para ver k estos serán blancos

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
            draw(window, state, squares);
            window.display();
            redraw = false;
        }
    }
}
  