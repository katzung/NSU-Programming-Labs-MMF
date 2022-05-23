#include <vector>
#include <fstream>
#include <map>
#include <algorithm>
#include <iostream>
#include <cmath>

//Перечисление для удобства задавания типа состояния
enum condition_types
{
    normal,
    end,
};

class FiniteStateMachine
{
    friend std::istream& operator>> (std::istream &in, FiniteStateMachine &fsm); //Ввод НКА из файла
    friend struct Condition;
private:
    struct Condition
    {
        int number;
        bool is_start;
        int condition_type;
        std::multimap<char, int> jump; //Функция перехода НКА

        Condition(): condition_type(normal), is_start(false), number(-1) {};
    };

    struct Condition_type
    {
        bool is_start;
        int condition_type;

        Condition_type() : is_start(false), condition_type(normal) {};
    };

    Condition * cond; //НКА
    std::vector<std::vector<Condition>> conds;   //ДКА
    std::vector<std::multimap<char, int>> jumps; //Функция перехода ДКА
    std::vector<Condition_type> conds_types; //Типы состояний ДКА
    int cond_size;
    std::vector<char> alphabet; //Конечный алфавит символов, считываемых автоматом
public:
    //Вспомогательная функция дупликации состояний автомата, использующаяся в функции Детерминизации состояний
    void duplicate();
    //Детерминизация состояний
    void cond_determinization();
    //Детерминизация функции перехода(здесь надо доделать на случай когда из одной вершины выходит несколько переходов с одним символом
    void jump_determinization();
    //Детерминизация типов состояний
    void conds_types_determinization();
    void determinization();
    //Проверка строки на распознаваемость автоматом
    void run_through_fsm(std::istream &in);

    //Вспомогательные функции
    bool is_in_alphabet(char x);
    void print_it();
};

std::istream& operator>> (std::istream &in, FiniteStateMachine &fsm);
