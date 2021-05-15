#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#pragma once

const std::string TITLE = "Te liveo la vida";

const std::string FONT_FILE = "res/fonts/font.ttf";

const float FPS = 10.f;

const int WINDOW_WIDTH = 1400;
const int WINDOW_HEIGHT = 1000;

const int SIMULATION_HEIGHT = 1000;
const int SIMULATION_WIDTH = 1000;

const int N = 100;
const int M = 100;

// int population;
// int birth;
// int death;
// int dias;
// bool show_grid;

const std::string s_pause = "Pause";
const std::string s_resume = "Resume";

const std::string s_add_grid = "Add grid";
const std::string s_no_grid = "No grid";

const std::string s_switch_colors = "Switch\nColors";

CONFLICT (content): Merge conflict in res/poblacion.csv
const std::string s_reset = "Reset";

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
