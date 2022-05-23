#pragma once
#include <iostream>
#include <vector>
#include "Animal.h"

class Animal;
class Rabbit;
class Wolf;
class Hyena;

enum direction {
    north = 0,
    east = 1,
    south = 2,
    west = 3,
};

class Simulation {
    friend class Animal;
    friend class Wolf;
    friend class Rabbit;
    friend class Hyena;
private:
    int N=-1;
    int M=-1;
    int length = -1;
    int R = -1;
    int W = -1;
    int H = -1;
    int time = 1;
    std::vector<Animal*> Animals;
    int ** w_mat;
    int ** r_mat;
    int ** h_mat;
public:
    Simulation();
    ~Simulation();

    void movement();
    void eating();
    void aging();
    void reproduction();
    void dying();

    void print_current_state();

    void start_simulation();
};
