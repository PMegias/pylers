#include "utils.hpp"

#include <fstream>

void add_zero_dataset(const std::string& dataset) {
    std::ofstream dt(dataset, std::fstream::out | std::fstream::trunc);
    if (!dt.is_open()) return;

    for (int i = 0; i < 10; ++i) {
        dt << "0,0\n";
    }

    dt.close();
}
