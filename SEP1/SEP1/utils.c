#include <math.h>
#include "cprocessing.h"

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
{
    if (click_x < (area_center_x + area_width / 2) && click_x >(area_center_x - area_width / 2) && click_y < (area_center_y + area_height / 2) && click_y >(area_center_y - area_height / 2))
    {
        if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT))
        {
            return 1;
        }
    }
    else {
        return 0;
    }
    return 0;
}

int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y)
{
    if (click_x < (circle_center_x + diameter / 2) && click_x >(circle_center_x - diameter / 2) && click_y < (circle_center_y + diameter / 2) && click_y >(circle_center_y - diameter / 2))
    {
        if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT))
        {
            return 1;
        }
    }
    else {
        return 0;
    }
    return 0;
}

int AreIntersecting(float w1, float s2_x, float w2)
{
      // Check if one rectangle is completely to the left of the other
    if (w1 >= s2_x-w2 && w1 <= s2_x) {
        return 1; // No intersection
    }
    else {
        return 0; // There is an intersection
    }
}

void drawHearts(float x, float y, float size) {
    //Player Hearts
    CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));

    // Draw heart using vertices
    CP_Graphics_BeginShape();
    CP_Graphics_AddVertex(x - size, y); // Left corner
    CP_Graphics_AddVertex(x - size * 0.5f, y - size * 0.5f); // Top left
    CP_Graphics_AddVertex(x, y); // Center top
    CP_Graphics_AddVertex(x + size * 0.5f, y - size * 0.5f); // Top right
    CP_Graphics_AddVertex(x + size, y); // Right corner
    CP_Graphics_AddVertex(x, y + size * 1.5f); // Bottom point
    CP_Graphics_EndShape();
}