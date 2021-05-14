
/* 
 Python se encargará de abrir una matriz dentro de un while
      --> se acabará si no quedan celulas vivas
      --> existe boton de STOP simulacion
      --> existe boton hacer una iteracion
 Al inicio de muestra una matriz Cuadrada vacía 
      --> el usuario coloca X cantidad de celulas y empieza la simulacion
      --> El usuario puede escribir mientras esta running? Nah que la pare o itere poquito a poco
      --> El usario puede volver atras? Cuanto si puede?
*/







Todo en C++
Viz con SFML

class LiveGame {
    b_matrix state(100,100,false); //100x100
    
    b_matrix STEP(const b_matrix& current_state) {
        b_matrix new_state;
        // aeaeaeaeae
        return new_state;
    }

public:
    void STEP() {
        state = STEP(state);
    }

    b_matrix getstate() const {
        return state;
    }
    
};

class Game {

    bool is_paused = false;
    bool is_initialized = false;
    float FPS = 60.f;
    int onestep = 0;
    LiveGame lv;

    void events() {
        if ("user pressed start")   state_initialized = true;
        if ("user pressed pause")   paused = true;
        if ("user pressed play")    paused = false;
        if ("user pressed onestep") onestep++, paused = true;
    }

    void update() {
        if (state_initialized && !paused) lv.STEP();
        if (onestep) lv.STEP(), onestep--;
    }

    void draw() {
        b_matrix state = lv.getstate();
        visualiza_la_magia_de_la_vida(state);
    }

public:
    void run() {
        while (1)
        events()
        // cada 60 fps
        if (elapsedtime >= 1/FPS) {
            if (!paused) {
                update()   // solo puedes pausar entre m1 y m2, no intermedio
                draw()
            }
            elapsedtime = 0
        }
    }

    
};

int main(int argc, char ** argv) {
    Game g;
    g.run();
}


