#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#pragma once
#include <omp.h>
#include <iostream>
#include <stdlib.h>

const std::string TITLE = "Te liveo la vida";

const std::string FONT_FILE = "res/fonts/font.ttf";

const float FPS = 15.f;

const int WINDOW_WIDTH = 1900;
const int WINDOW_HEIGHT = 1000;

const int SIMULATION_HEIGHT = 1000;
const int SIMULATION_WIDTH = 1000;

const int N = 100;
const int M = 100;

const std::string s_pause = "Pause";
const std::string s_resume = "Resume";

const std::string s_add_grid = "Add grid";
const std::string s_no_grid = "No grid";

const std::string s_switch_colors = "Switch\nColors";

const std::string s_reset = "Reset";

const std::string s_main_menu = "Main\nMenu";

const std::string s_play = "Play";
const std::string s_exit = "Exit";
const std::string s_random = "Random";

const std::string PLOTTER_FILE = "res/plotter.gnp";
const std::string PLOT_FILE = "/tmp/plot.png";

const std::string pobl_csv = "res/poblacion.csv";
const std::string pobl_png = "res/poblacion.png";
const std::string pobl_ftitle = "poblacion";

const std::string naci_csv = "res/nacimiento.csv";
const std::string naci_png = "res/nacimiento.png";
const std::string naci_ftitle = "nacimiento";

const std::string mort_csv = "res/morticion.csv";
const std::string mort_png = "res/morticion.png";
const std::string mort_ftitle = "morticion";

#endif // CONFIGURATION_HPP
