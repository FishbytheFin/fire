#include <tice.h>
#include <graphx.h>

#include "gfx/gfx.h"

int score;
int gameVersion;
int playerPos = 0;
int people[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/*Functions*/
int drawScreen();

int main(void)
{
    /* Initialization */
    gfx_Begin();
    gfx_SetDrawBuffer();
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);
    gfx_SetTransparentColor(0);
    gfx_FillScreen(1);

    /*fintendo logo*/

    gfx_TransparentSprite_NoClip(logo, 60, 36);
    gfx_BlitBuffer();

    while (!os_GetCSC())
        ;

    /*Drawing*/
    drawScreen();

    /* Waits for a key */
    while (!os_GetCSC())
        ;

    gfx_End();

    return 0;
}

int drawScreen()
{
    gfx_FillScreen(1);

    gfx_TransparentSprite_NoClip(building, 0, 0);
    gfx_TransparentSprite_NoClip(floor, 72, 135);
    gfx_TransparentSprite_NoClip(person1, 20, 38);

    gfx_BlitBuffer();
    return 0;
}
