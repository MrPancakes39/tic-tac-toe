#include <stdio.h>
#include "game.h"

int main(void)
{
    while (!finish)
    {
        setup();
        while (doLoop)
        {
            draw();
        }
    }
    return 0;
}