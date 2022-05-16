#include <tice.h>
#include <graphx.h>
#include <keypadc.h>

#include "gfx/gfx.h"

/*
ToDo:
        - Optimize building sprite(slipt building and fire to save litteral kilobites of data(uncompressed))
        - Add smoke
        - Add Misses
        - Add Score display
        - Actually code the game
*/

int score;
int playerPos = 0;
int people[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int i;
int frame = 0;

/*Functions*/
int drawScreen();
int drawPerson();

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

        frame++;
        if (frame > 16)
        {
            frame = 1;
        }
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
        drawScreen();
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

    for (i = 0; i < 23; i++)
    {
        drawPerson(i);
    }

    gfx_TransparentSprite_NoClip(crash, 36, 208);

    gfx_TransparentSprite_NoClip(player, 28 + (playerPos * 75), 177);

    gfx_BlitBuffer();
    return 0;
}

int drawPerson(int location)
{
    switch (location)
    {
    case 1:
        gfx_TransparentSprite_NoClip(person1, 20, 38);
        break;
    case 2:
        gfx_TransparentSprite_NoClip(person2, 37, 75);
        break;
    case 3:
        gfx_TransparentSprite_NoClip(person3, 42, 112);
        break;
    case 4:
        gfx_TransparentSprite_NoClip(person4, 45, 147);
        break;
    case 5:
        gfx_TransparentSprite_NoClip(person5, 54, 174);
        break;
    case 6:
        gfx_TransparentSprite_NoClip(person2, 77, 147);
        break;
    case 7:
        gfx_TransparentSprite_NoClip(person3, 79, 112);
        break;
    case 8:
        gfx_TransparentSprite_NoClip(person4, 81, 75);
        break;
    case 9:
        gfx_TransparentSprite_NoClip(person5, 91, 38);
        break;
    case 10:
        gfx_TransparentSprite_NoClip(person2, 111, 75);
        break;
    case 11:
        gfx_TransparentSprite_NoClip(person3, 117, 112);
        break;
    case 12:
        gfx_TransparentSprite_NoClip(person4, 121, 147);
        break;
    case 13:
        gfx_TransparentSprite_NoClip(person5, 129, 174);
        break;
    case 14:
        gfx_TransparentSprite_NoClip(person2, 154, 147);
        break;
    case 15:
        gfx_TransparentSprite_NoClip(person3, 156, 112);
        break;
    case 16:
        gfx_TransparentSprite_NoClip(person4, 170, 75);
        break;
    case 17:
        gfx_TransparentSprite_NoClip(person5, 190, 112);
        break;
    case 18:
        gfx_TransparentSprite_NoClip(person2, 190, 147);
        break;
    case 19:
        gfx_TransparentSprite_NoClip(person3, 200, 174);
        break;
    case 20:
        gfx_TransparentSprite_NoClip(person4, 222, 147);
        break;
    case 21:
        gfx_TransparentSprite_NoClip(person5, 226, 110);
        break;
    case 22:
        gfx_TransparentSprite_NoClip(person2, 252, 136);
        break;
    default:
        return 1;
    }
    return 0;
}
