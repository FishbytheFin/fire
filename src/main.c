#include <tice.h>
#include <graphx.h>

#include "gfx/gfx.h"

int score;
int gameVersion;
int playerPos = 0;
int people[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int main(void)
{
    /* Initialization */
    gfx_Begin();
    gfx_SetDrawBuffer();
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);
    gfx_SetTransparentColor(0);

    /*Drawing*/
    drawScreen();

    /* Waits for a key */
    while (!os_GetCSC())
        ;

    gfx_End();

    return 0;
}

void drawScreen()
{
    gfx_FillScreen(1);

    gfx_TransparentSprite_NoClip(building, 0, 0);
    gfx_TransparentSprite_NoClip(floor, 72, 135);
    gfx_TransparentSprite_NoClip(person1, 0, 0);

    gfx_BlitBuffer();
}
