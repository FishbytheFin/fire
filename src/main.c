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
    kb_key_t prevkey = kb_Sub;

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

        if (key == kb_Right && key != prevkey)
        {
            playerPos++;
            if (playerPos > 2)
                playerPos = 2;
            drawScreen();
        }
        else if (key == kb_Left && key != prevkey)
        {
            playerPos--;
            if (playerPos < 0)
                playerPos = 0;
            drawScreen();
        }

        prevkey = key;

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
    gfx_TransparentSprite_NoClip(person2, 50, 38);
    gfx_TransparentSprite_NoClip(person3, 80, 38);
    gfx_TransparentSprite_NoClip(person4, 110, 38);
    gfx_TransparentSprite_NoClip(person5, 140, 38);
    gfx_TransparentSprite_NoClip(person6, 170, 38);
    gfx_TransparentSprite_NoClip(person7, 200, 38);

    gfx_TransparentSprite_NoClip(crash);

    gfx_TransparentSprite_NoClip(player, 28 + (playerPos * 79), 177);

    gfx_BlitBuffer();
    return 0;
}
