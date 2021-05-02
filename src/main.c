#include <stdio.h>
#include "game.h"

int main(void)
{
    setup();
    while (doLoop)
    {
        draw();
    }
    return 0;
}