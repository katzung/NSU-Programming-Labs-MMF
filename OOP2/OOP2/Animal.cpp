#include "Animal.h"


Animal::Animal(): x(-1), y(-1), direction(-1), constancy(-1), age(0) {}

Animal::Animal(Animal const & that): x(that.x), y(that.y), direction(that.direction), constancy(that.constancy), age(that.age) {}

Animal::~Animal() = default;

Animal& Animal::operator=(const Animal & copy) = default;

std::istream& operator>> (std::istream &in, Animal & animal) {
    in >> animal.x >> animal.y >> animal.direction >> animal.constancy;
    return in;
}

Wolf::Wolf(): Animal(){};

Wolf::Wolf(Wolf const & that): Animal(that){};

Wolf::~Wolf() = default;

Wolf& Wolf::operator=(const Wolf & copy) = default;

void Wolf::move(Simulation & simulation) {
    if (is_alive) {
        simulation.w_mat[y][x] -= 1;
        if (direction == north) y -= 2;
        if (direction == east) x += 2;
        if (direction == south) y += 2;
        if (direction == west) x -= 2;
        y += simulation.N;
        x += simulation.M;
        y %= simulation.N;
        x %= simulation.M;
        simulation.w_mat[y][x] += 1;
        if (simulation.time % constancy == 0) direction = (direction + 1) % 4;
    }
}

void Wolf::eat(Simulation & simulation, int x, int y) {
    rabbit_count += simulation.r_mat[x][y];
}

void Wolf::age_inc(Simulation &simulation) {
    age+=1;
}

void Wolf::reproduct(Simulation &simulation) {
    if (rabbit_count>=2) {
        Wolf * child = new Wolf;
        *child = *this;
        child->rabbit_count = 0;
        simulation.Animals.push_back(child);
        rabbit_count = 0;
        simulation.w_mat[y][x] += 1;
        simulation.W += 1;
    }
}

void Wolf::die(Simulation &simulation) {
    if (age == 15) {
        is_alive = false;
        simulation.w_mat[y][x] -= 1;
    }
    if (age >= 15) {
        is_alive = false;
    }
}

bool Wolf::is_rabbit(Simulation &simulation) {return false;}
bool Wolf::is_wolf(Simulation &simulation) {return true;}
bool Wolf::is_hyena(Simulation & simulation) {return false;}

Rabbit::Rabbit(): Animal(){};

Rabbit::Rabbit(Rabbit const & that): Animal(that) {};

Rabbit::~Rabbit() = default;

Rabbit& Rabbit::operator=(const Rabbit & copy) = default;

void Rabbit::move(Simulation &simulation) {
    if (is_alive) {
        simulation.r_mat[y][x] -= 1;
        if (direction == north) y -= 1;
        if (direction == east) x += 1;
        if (direction == south) y += 1;
        if (direction == west) x -= 1;
        y += simulation.N;
        x += simulation.M;
        y %= simulation.N;
        x %= simulation.M;
        simulation.r_mat[y][x] += 1;
        if (simulation.time % constancy == 0) direction = (direction + 1) % 4;
    }
}

void Rabbit::eat(Simulation &simulation) {
    is_alive = false;
}

void Rabbit::age_inc(Simulation &simulation) {
    age+=1;
}

void Rabbit::reproduct(Simulation &simulation) {
    if ((age == 5 || age == 10) && is_alive) {
        Rabbit * child = new Rabbit;
        *child = *this;
        child->age = 0;
        simulation.Animals.push_back(child);
        simulation.r_mat[y][x] += 1;
        simulation.R += 1;
    }
}

void Rabbit::die(Simulation &simulation) {
    if (age == 10) {
        is_alive = false;
        simulation.r_mat[y][x] -= 1;
    }
    if (age >= 10) {
        is_alive = false;
    }
}

bool Rabbit::is_rabbit(Simulation &simulation) {return true;}
bool Rabbit::is_wolf(Simulation &simulation) {return false;}
bool Rabbit::is_hyena(Simulation & simulation) {return false;}


Hyena::Hyena(): Animal(){};

Hyena::Hyena(Hyena const & that): Animal(that) {};

Hyena::~Hyena() = default;

Hyena& Hyena::operator=(const Hyena & copy) = default;

void Hyena::move(Simulation &simulation) {
    if (is_alive) {
        simulation.r_mat[y][x] -= 1;
        if (direction == north) y -= 2;
        if (direction == east) x += 2;
        if (direction == south) y += 2;
        if (direction == west) x -= 2;
        y += simulation.N;
        x += simulation.M;
        y %= simulation.N;
        x %= simulation.M;
        simulation.r_mat[y][x] += 1;
        if (simulation.time % constancy == 0) direction = (direction + 1) % 4;
    }
}
void Hyena::eat(Simulation &simulation) {
    if (animal_count < 2) animal_count += 1;
}

void Hyena::age_inc(Simulation &simulation) {
    age+=1;
}

void Hyena::reproduct(Simulation &simulation) {
    if (animal_count>=2) {
        Hyena * child = new Hyena;
        *child = *this;
        child->animal_count = 0;
        simulation.Animals.push_back(child);
        animal_count = 0;
        simulation.h_mat[y][x] += 1;
        simulation.H += 1;
    }
}

void Hyena::die(Simulation &simulation) {
    if (age == 15) {
        is_alive = false;
        simulation.h_mat[y][x] -= 1;
    }
    if (age >= 15) {
        is_alive = false;
    }
}

bool Hyena::is_rabbit(Simulation &simulation) {return false;}
bool Hyena::is_wolf(Simulation &simulation) {return false;}
bool Hyena::is_hyena(Simulation & simulation) {return true;}

int Hyena::get_animal_count(Simulation &simulation) {
    return animal_count;
}

