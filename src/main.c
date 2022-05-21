#include <tice.h>
#include <graphx.h>
#include <keypadc.h>
#include <fileioc.h>

#include "gfx/gfx.h"

/*
ToDo:
        - Pausing
        - more control options(7, 9, 4, 6, 1, 3)
*/

int score = 0;
int highScore = 0;
int nextScore = 30;
int misses = 0;
int playerPos = 0;
int crashed = 0;
int frame = 0;
int smokeFrame = 0;
int frameDelay = 100;
int addedPeople = 0;
int again = 0;

int i;

int people[] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int tempPeople[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/*Functions*/
int drawScreen();
int drawPerson();
int update();
int addScore();
int saveHighScore();
int loadHighScore();

int main(void)
{
    /* Initialization */
    loadHighScore();

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

        /*User input:*/
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
        // kb_Data[6] == kb_Clear ||
        if (misses >= 3)
        {
            loadHighScore();
            if (score > highScore)
            {
                highScore = score;
                saveHighScore();
            }
            while (true)
            {
                kb_Scan();
                key = kb_Data[6];
                if (key == kb_Clear)
                {
                    again = 0;
                    break;
                }
                else if (key == kb_Enter)
                {
                    score = 0;
                    highScore = 0;
                    nextScore = 30;
                    misses = 0;
                    playerPos = 0;
                    crashed = 0;
                    frame = 0;
                    smokeFrame = 0;
                    frameDelay = 100;
                    addedPeople = 0;
                    again = 1;

                    for (i = 0; i < 22; i++)
                    {
                        people[i] = 0;
                        tempPeople[i] = 0;
                    }
                    people[1] = 1;
                    break;
                }

                gfx_FillScreen(3);
                gfx_SetTextFGColor(1);
                gfx_PrintStringXY("Score:", 2, 2);
                gfx_PrintStringXY("Hi:", 2, 12);
                gfx_PrintStringXY("Enter: Play again", 2, 22);
                gfx_PrintStringXY("Clear: Exit", 2, 32);

                gfx_SetTextXY(50, 12);
                gfx_PrintInt(highScore, 1);
                gfx_SetTextXY(50, 2);
                gfx_PrintInt(score, 1);
                gfx_BlitBuffer();
            }
            if (again == 0)
            {
                break;
            }
        }

        /*Logic + graphics:*/
        if (frame % frameDelay == 0)
        {
            update();
            drawScreen();
        }
    }

    gfx_End();

    return 0;
}

int drawScreen()
{
    gfx_FillScreen(1);

    // Background elements:
    gfx_TransparentSprite_NoClip(building1, 0, 0);
    gfx_TransparentSprite_NoClip(building0, 0, 45);
    gfx_TransparentSprite_NoClip(building2, 0, 211);

    switch (smokeFrame)
    {
    case 1:
        gfx_TransparentSprite_NoClip(smoke0, 34, 5);
        break;
    case 2:
        gfx_TransparentSprite_NoClip(smoke0, 34, 5);
        gfx_TransparentSprite_NoClip(smoke1, 70, 0);
        break;
    case 3:
        gfx_TransparentSprite_NoClip(smoke1, 70, 0);
        break;

    default:
        break;
    }

    gfx_TransparentSprite_NoClip(floor1, 76, 211);
    gfx_TransparentSprite_NoClip(floor2, 257, 142);

    // People:
    for (i = 0; i < 22; i++)
    {
        if (people[i] == 1)
        {
            drawPerson(i + 1);
        }
    }

    // Misses:
    if (misses > 0)
    {
        for (i = 0; i < misses; i++)
        {
            gfx_TransparentSprite_NoClip(miss, 300 - (20 * i), 10);
        }
    }

    // Crash:
    switch (crashed)
    {
    case 1:
        gfx_TransparentSprite_NoClip(crash, 36, 208);
        people[5] = 1;
        break;
    case 2:
        gfx_TransparentSprite_NoClip(crash, 111, 208);
        people[13] = 1;
        break;
    case 3:
        gfx_TransparentSprite_NoClip(crash, 186, 208);
        people[19] = 1;
        break;

    default:
        break;
    }

    gfx_TransparentSprite_NoClip(player, 28 + (playerPos * 75), 185);

    // Text:
    gfx_SetTextFGColor(3); // From global pallet. Double check if text colors are funky

    gfx_PrintStringXY("Score:", 190, 2);
    gfx_PrintStringXY("Hi:", 120, 2);
    gfx_PrintStringXY("Misses", 270, 0);

    gfx_SetTextXY(140, 2);
    gfx_PrintInt(highScore, 1);
    gfx_SetTextXY(240, 2);
    gfx_PrintInt(score, 1);
    gfx_BlitBuffer();

    if (crashed != 0)
    {
        delay(1500);
        crashed = 0;
        misses++;
    }

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

int update()
{

    // Smoke
    smokeFrame += randInt(0, 1);
    if (smokeFrame == 4)
    {
        smokeFrame = 0;
    }

    // People
    for (i = 0; i < 22; i++)
    {
        tempPeople[i] = people[i];
    }

    for (i = 0; i < 22; i++)
    {
        if (tempPeople[i] == 1)
        {

            // Catching + Landing in the ambulence:
            if (i == 21)
            {
                addScore(1);
                people[0] = 1;
            }
            else if (i == 4)
            {
                if (playerPos == 0)
                {
                    addScore(1);
                    people[i + 1] = 1;
                }
                else
                {
                    crashed = 1;
                }
            }
            else if (i == 12)
            {
                if (playerPos == 1)
                {
                    addScore(1);
                    people[i + 1] = 1;
                }
                else
                {
                    crashed = 2;
                }
            }
            else if (i == 18)
            {
                if (playerPos == 2)
                {
                    addScore(1);
                    people[i + 1] = 1;
                }
                else
                {
                    crashed = 3;
                }
            }
            else
            {
                people[i + 1] = 1;
            }
            people[i] = 0;
        }
    }
    if (score >= nextScore && addedPeople < 3 && people[0] == 0 && people[1] == 0 && people[5] == 0 && people[6] == 0 && people[7] == 0 && people[8] == 0 && people[13] == 0 && people[14] == 0 && people[15] == 0 && people[16] == 0)
    {
        nextScore *= 2;
        addedPeople++;
        people[0] = 1;
    }

    return 0;
}

int addScore(int amount)
{
    score += amount;
    if (frameDelay > 50 && score % 40 == 0)
    {
        frameDelay -= 5;
    }
    if (score == 200 || score == 500)
    {
        misses = 0;
    }
    return 0;
}

int saveHighScore()
{
    ti_var_t hiScore;
    ti_CloseAll();
    if ((hiScore = ti_Open("FIREHISCORE", "w")))
    {
        ti_Write(&highScore, sizeof highScore, 1, hiScore);
        ti_SetArchiveStatus(true, hiScore);
        return 0;
    }
    return 1;
}

int loadHighScore()
{
    ti_var_t hiScore;
    ti_CloseAll();
    if ((hiScore = ti_Open("FIREHISCORE", "r")))
    {
        ti_Read(&highScore, sizeof highScore, 1, hiScore);
    }
    else
    {
        highScore = 0;
    }
    return 0;
}
