#include "Simulation.h"

Simulation::Simulation() {
    std::cin >> N >> M >> length >> R >> W >> H;
    for (int i = 0; i < R; ++i) {
        Rabbit *temp = new Rabbit;
        std::cin >> *temp;
        Animals.push_back(temp);
    }
    for (int i = 0; i < W; ++i) {
        Wolf *temp = new Wolf;
        std::cin >> *temp;
        Animals.push_back(temp);
    }
    for (int i = 0; i < W; ++i) {
        Hyena *temp = new Hyena;
        std::cin >> *temp;
        Animals.push_back(temp);
    }

    w_mat = new int*[N];
    for (int i = 0; i < N; ++i) {
        w_mat[i] = new int[M];
    }
    r_mat = new int*[N];
    for (int i = 0; i < N; ++i) {
        r_mat[i] = new int[M];
    }
    h_mat = new int*[N];
    for (int i = 0; i < N; ++i) {
        h_mat[i] = new int[M];
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            w_mat[i][j] = 0;
            r_mat[i][j] = 0;
            h_mat[i][j] = 0;
        }
    }

    for (int i = 0; i < R; ++i) {
        r_mat[Animals[i]->y][Animals[i]->x] += 1;
    }
    for (int i = R; i < R + W; ++i) {
        w_mat[Animals[i]->y][Animals[i]->x] += 1;
    }
    for (int i = R + W; i < R + W + H; ++i) {
        h_mat[Animals[i]->y][Animals[i]->x] += 1;
    }
}

Simulation::~Simulation() = default;

void Simulation::movement() {
    for (int i = 0; i < R+W+H; ++i) {
        Animals[i]->move(*this);
    }
}

void Simulation::eating() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            for (int k = 0; k < R + W + H; ++k) { // Первой ест гиена
                if (Animals[k]->is_hyena(*this)) {
                    if (Animals[k]->is_alive && Animals[k]->x == j && Animals[k]->y == i) {
                        for (int l = 0; l < R + W + H; ++l) { // Съели зайцев
                            if (Animals[l]->x == j && Animals[l]->y == i && Animals[l]->is_alive && l != k && Animals[l]->is_rabbit(*this)) {
                                int temp = Animals[k]->get_animal_count(*this);
                                Animals[k]->eat(*this);
                                if (Animals[k]->get_animal_count(*this) > temp) {Animals[l]->eat(*this);r_mat[i][j]-=1;}
                            }
                        }
                        for (int l = 0; l < R + W + H; ++l) { //Съели волков
                            if (Animals[l]->x == j && Animals[l]->y == i && Animals[l]->is_alive && l != k && Animals[l]->is_wolf(*this)) {
                                int temp = Animals[k]->get_animal_count(*this);
                                Animals[k]->eat(*this);
                                if (Animals[k]->get_animal_count(*this) > temp) {Animals[l]->is_alive = false;w_mat[i][j]-=1;}
                            }
                        }
                    }
                }
            } //Тут гиена заканчивает есть
            for (int k = 0; k < R + W + H; ++k) { //Тут едят волки
                if (Animals[k]->is_wolf(*this)) {
                    if (Animals[k]->is_alive && Animals[k]->x == j && Animals[k]->y == i) {
                        for (int l = 0; l < R + W + H; ++l) {
                            if (Animals[l]->x == j && Animals[l]->y == i && Animals[l]->is_alive && Animals[l]->is_rabbit(*this) && l != k) {
                                Animals[k]->eat(*this);
                                Animals[l]->eat(*this);
                                r_mat[i][j] = 0;
                            }
                        }
                    }
                }
            } //Тут волки наелись
        }
    }
}

void Simulation::aging() {
    for (int i = 0; i < R+W+H; ++i) {
        Animals[i]->age_inc(*this);
    }
}

void Simulation::reproduction() {
    for (int i = 0; i < R+W+H; ++i) {
        Animals[i]->reproduct(*this);
    }
}

void Simulation::dying() {
    for (int i = 0; i < R+W+H; ++i) {
        Animals[i]->die(*this);
    }
}

void Simulation::print_current_state() {
    std::cout << "Rabbits\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            std::cout << r_mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Wolfs\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            std::cout << w_mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Hyenas\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            std::cout << h_mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Simulation::start_simulation() {
    //print_current_state();
    for (time = 1; time < length+1; ++time) {
        movement();
        //print_current_state();
        eating();
        //print_current_state();
        aging();
        //print_current_state();
        reproduction();
        //print_current_state();
        dying();
        //print_current_state();
    }
    print_current_state();
}