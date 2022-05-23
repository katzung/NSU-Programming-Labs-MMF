#pragma once
#include <iostream>
#include "Simulation.h"

class Simulation;

class Animal {
    friend class Simulation;
protected:
    int x, y;
    int direction;
    int constancy;
    int age;
    bool is_alive = true;
public:
    Animal();
    Animal(Animal const & that);
    ~Animal();
    Animal& operator=(const Animal & copy);
    friend std::istream& operator>> (std::istream &in, Animal & animal);

    virtual void move(Simulation & simulation) = 0;
    virtual void eat(Simulation & simulation) = 0;
    virtual void eat(Simulation & simulation, int a, int b) = 0;
    virtual void age_inc(Simulation & simulation) = 0;
    virtual void reproduct(Simulation & simulation) = 0;
    virtual void die(Simulation & simulation) = 0;
    virtual bool is_rabbit(Simulation & simulation) {return false;}
    virtual bool is_wolf(Simulation & simulation) {return false;}
    virtual bool is_hyena(Simulation & simulation) {return false;}
    virtual int get_animal_count(Simulation & simulation) {return -1;}
};

class Wolf final: public Animal {
    friend class Simulation;
private:
    int rabbit_count = 0;
public:
    Wolf();
    Wolf(Wolf const & that);
    ~Wolf();
    Wolf& operator=(const Wolf & copy);

    void move(Simulation & simulation) override;
    void eat(Simulation & simulation, int a, int b) override;
    void eat(Simulation & simulation) override {}
    void age_inc(Simulation & simulation) override;
    void reproduct(Simulation & simulation) override;
    void die(Simulation & simulation) override;
    bool is_rabbit(Simulation & simulation) override;
    bool is_wolf(Simulation & simulation) override;
    bool is_hyena(Simulation & simulation) override;
};

class Rabbit final: public Animal {
    friend class Simulation;
public:
    Rabbit();
    Rabbit(Rabbit const & that);
    ~Rabbit();
    Rabbit& operator=(const Rabbit & copy);

    void move(Simulation & simulation) override;
    void eat(Simulation & simulation) override;
    void eat(Simulation & simulation, int a, int b) override {}
    void age_inc(Simulation & simulation) override;
    void reproduct(Simulation & simulation) override;
    void die(Simulation & simulation) override;
    bool is_rabbit(Simulation & simulation) override;
    bool is_wolf(Simulation & simulation) override;
    bool is_hyena(Simulation & simulation) override;
};

class Hyena final: public Animal {
    friend class Simulation;
private:
    int animal_count = 0;
public:
    Hyena();
    Hyena(Hyena const & that);
    ~Hyena();
    Hyena& operator=(const Hyena & copy);

    void move(Simulation & simulation) override;
    void eat(Simulation & simulation) override;
    void eat(Simulation & simulation, int a, int b) override {}
    void age_inc(Simulation & simulation) override;
    void reproduct(Simulation & simulation) override;
    void die(Simulation & simulation) override;
    bool is_rabbit(Simulation & simulation) override;
    bool is_wolf(Simulation & simulation) override;
    bool is_hyena(Simulation & simulation) override;
    int get_animal_count(Simulation & simulation) override;
};

std::istream& operator>> (std::istream &in, Animal &animal);

