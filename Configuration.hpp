#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

bool modo_epilepsia_activado = false;

const float FPS = 25.f;

const int WINDOW_WIDTH = 1400;
const int WINDOW_HEIGHT = 1000;

const int SIMULATION_HEIGHT = 1000;
const int SIMULATION_WIDTH = 1000;

const int N = 100;
const int M = 100;

int population;
int birth;
int death;
bool redraw = false;
int dias = 0;
bool pause = true;
bool lost_focus = false;
bool show_grid = false;



std::string s_Pausa = "Pause";
std::string s_Resume = "Resume";

std::string s_AddGrid = "Add grid";
std::string s_NoGrid = "No grid";

#endif // CONFIGURATION_HPP