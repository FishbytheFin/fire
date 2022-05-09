#include <tice.h>
#include <graphx.h>
#include <keypadc.h>

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

    kb_key_t key;

    /*game and watch logo*/

    gfx_TransparentSprite_NoClip(logo, 60, 36);
    gfx_BlitBuffer();

    while (!os_GetCSC())
        ;

    /*Drawing*/
    drawScreen();

    while (true)
    {
        kb_Scan();

        key = kb_Data[7];
        switch (key)
        {
        case kb_Right:
            playerPos++;
            if (playerPos > 2)
                playerPos = 2;
            drawScreen();
            break;
        case kb_Left:
            playerPos--;
            if (playerPos < 0)
                playerPos = 0;
            drawScreen();
            break;

        default:
            break;
        }
        if (kb_Data[6] == kb_Clear)
        {
            break;
        }
    }

    /* Waits for a key */

    gfx_End();

    return 0;
}

int drawScreen()
{
    gfx_FillScreen(1);

    gfx_TransparentSprite_NoClip(building, 0, 0);
    gfx_TransparentSprite_NoClip(floor, 72, 135);
    gfx_TransparentSprite_NoClip(person1, 20, 38);
    gfx_TransparentSprite_NoClip(player, 28 + (playerPos * 79), 177);

    gfx_BlitBuffer();
    return 0;
}
