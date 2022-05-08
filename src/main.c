#include <tice.h>
#include <graphx.h>

#include "gfx/gfx.h"

int main(void)
{
    /* Initialize graphics drawing */
    gfx_Begin();

    /* Draw to buffer instead of directly to screen */
    /* This is the same as gfx_SetDraw(gfx_buffer) */
    gfx_SetDrawBuffer();

    gfx_SetPalette(global_palette, sizeof_global_palette, 0);

    gfx_SetTransparentColor(0);
    gfx_FillScreen(1);

    gfx_TransparentSprite_NoClip(building, 0, 0);
    gfx_TransparentSprite_NoClip(floor, 72, 135);

    gfx_BlitBuffer();

    /* Waits for a key */
    while (!os_GetCSC())
        ;

    /* End graphics drawing */
    gfx_End();

    return 0;
}
