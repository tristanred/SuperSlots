#include <stdio.h>
#include "ReelManager.h"

int main(int argc, char** argv)
{
    ReelManager* rm = new ReelManager(5, 3);
    rm->CreateDefaultObjects();
    rm->Spin();
    rm->PrintCurrentCombination();

    int res = rm->CalculateWins();

    printf("Won: %d\n", res);

    delete(rm);

    return 0;
}