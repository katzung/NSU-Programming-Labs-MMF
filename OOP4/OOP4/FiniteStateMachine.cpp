#include "FiniteStateMachine.h"

void FiniteStateMachine::duplicate()
{
    int temp = (int)conds.size();
    conds.resize(conds.size()*2);
    for (int i = 0; i < temp; ++i)
    {
        for (int j = 0; j < conds[i].size(); ++j)
        {
            conds[temp+i].push_back(conds[i][j]);
        }
    }
}

void FiniteStateMachine::cond_determinization()
{
    Condition temp;
    conds.resize(2);
    conds[0].push_back(temp); conds[1].push_back(cond[0]);
    for (int i = 0; i < cond_size-1; ++i)
    {
        duplicate();
        for (int j = (int)conds.size()/2; j < conds.size(); ++j)
        {
            conds[j].push_back(cond[i+1]);
        }
    }
    for (int i = 2; i < conds.size(); ++++i)
    {
        conds[i].erase(conds[i].begin());
    }
}

void FiniteStateMachine::jump_determinization()
{
    jumps.resize(conds.size());
    for (auto & jump : jumps)
    {
        for (char & j : alphabet)
        {
            jump.insert(std::pair<char, int>(j, -2));
        }
    }
    for (char & i : alphabet)
    {
        jumps[0].find(i)->second = 0;
    }
    for (int i = 1; i < conds.size(); ++i) {
        for (char & j : alphabet)
        {
            std::vector<int> where_to;
            for (auto & k : conds[i])
            {
                for (auto & iter : k.jump)
                {
                    if (iter.first == j) where_to.push_back(iter.second);
                }
                std::sort(where_to.begin(), where_to.begin()+where_to.size());
            }

            for (int k = 0; k < conds.size(); ++k)
            {
                if (conds[k].size() == where_to.size() && !where_to.empty())
                {
                    bool found = true;
                    for (int l = 0; l < where_to.size(); ++l)
                    {
                        if (conds[k][l].number == where_to[l]) {continue;}
                        else {found = false;}
                    }
                    if (found)
                    {
                        jumps[i].find(j)->second = k;
                        break;
                    }
                }
                if (where_to.empty())
                {
                    jumps[i].find(j)->second = 0;
                    break;
                }
            }
        }
    }
}

void FiniteStateMachine::conds_types_determinization()
{
    conds_types.resize(conds.size());
    for (int i = 0; i < conds.size(); ++i)
    {
        if (conds[i].size() == 1 && conds[i][0].is_start) conds_types[i].is_start = true;
        for (int j = 0; j < conds[i].size(); ++j)
        {
            if (conds[i][j].condition_type == end) {conds_types[i].condition_type = end;}
            else {continue;}
        }
    }
}

void FiniteStateMachine::determinization()
{
    cond_determinization();
    jump_determinization();
    conds_types_determinization();
}

void FiniteStateMachine::run_through_fsm(std::istream &in)
{
    std::string word;
    in >> word;
    int start, current;
    for (int i = 1; i < conds.size(); ++i)
    {
        if (conds[i].size()==1 && conds[i][0].is_start) start = i;
    }
    current = start;
    for (char & i : word)
    {
        current = jumps[current].find(i)->second;
    }
    if (conds_types[current].condition_type == end) {std::cout << "YES\n";}
    else {std::cout << "NO\n";}
}

bool FiniteStateMachine::is_in_alphabet(char x)
{
    bool is_there = false;
    for (char j : alphabet)
    {
        if (j == x) {is_there = true; break;}
        else {continue;}
    }
    if (!is_there) {return false;}
    else {return true;}
}

void FiniteStateMachine::print_it()
{
    for (int i = 0; i < cond_size; ++i)
    {
        std::cout << "Condition " << i;
        if (cond[i].is_start) std::cout << "(Start) ";
        if (cond[i].condition_type == end) std::cout << "(End)";
        std::cout << std::endl;
        for (auto & e : cond[i].jump)
            std::cout << "{" << e.first << "," << e.second << "} ";
        std::cout << '\n';
    }
}

std::istream& operator>> (std::istream &in, FiniteStateMachine &fsm)
{
    int N;
    in >> N; fsm.cond = new FiniteStateMachine::Condition[N];               //
    for (int i = 0; i < N; ++i)                                             //
    {                                                                       //
        fsm.cond[i].number = i;                                             //Количество состояний
    }                                                                       //
    fsm.cond_size = N;                                                      //

    in >> N; fsm.cond[N].is_start = true;                                   //Стартовое состояние

    int end_N; in >> end_N;                                                 //
    for (int i = 0; i < end_N; ++i)                                         //
    {                                                                       //Конечное
        in >> N; fsm.cond[N].condition_type = end;                          //состояние
    }                                                                       //

    int p; in >> p; int from, to; char value;                               //
    for (int i = 0; i < p; ++i)                                             //
    {                                                                       //Функция
        in >> from >> to >> value;                                          //перехода
        fsm.cond[from].jump.insert(std::pair<char, int>(value, to));     //
        if (!fsm.is_in_alphabet(value)) fsm.alphabet.push_back(value);      //
    }                                                                       //
    return in;
}