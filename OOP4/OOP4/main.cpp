#include "FiniteStateMachine.h"

int main() {
    FiniteStateMachine finiteStateMachine;
    std::fstream inf("C:\\\\Users\\\\romag\\\\CLionProjects\\\\OOP4\\\\input.txt");
    inf >> finiteStateMachine;
    finiteStateMachine.determinization();
    int N; inf >> N;
    for (int i = 0; i < N; ++i)
    {
        finiteStateMachine.run_through_fsm(inf);
    }
    return 0;
}
