#include <tice.h>
#include <graphx.h>
#include <keypadc.h>

#include "gfx/gfx.h"

int score;
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
    gfx_TransparentSprite_NoClip(floor1, 76, 211);
    gfx_TransparentSprite_NoClip(floor2, 257, 142);

    gfx_TransparentSprite_NoClip(person1, 20, 38);
    gfx_TransparentSprite_NoClip(person2, 37, 75);
    gfx_TransparentSprite_NoClip(person3, 42, 112);
    gfx_TransparentSprite_NoClip(person4, 45, 147);
    gfx_TransparentSprite_NoClip(person5, 54, 174);

    gfx_TransparentSprite_NoClip(crash, 36, 208);

    gfx_TransparentSprite_NoClip(player, 28 + (playerPos * 75), 177);

    gfx_BlitBuffer();
    return 0;
}
