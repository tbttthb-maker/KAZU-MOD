#pragma once
#include "Includes.h"

/********************************************
 * Project: KAZU-MOD (Future Tech ESP)
 * Developer: KAZU
 * Telegram: https://t.me/K_4441
 ********************************************/

#define COLOR_NEON_CYAN ImColor(0, 255, 255, 255)
#define COLOR_NEON_PINK ImColor(255, 0, 127, 255)
#define COLOR_GLOW      ImColor(0, 255, 255, 30)

class FutureESP {
public:
    void Draw(ImDrawList* draw, Vector2 foot, Vector2 head, float health, float distance) {
        float h = foot.y - head.y;
        float w = h / 2.4f;
        float l = w * 0.25f;
        
        ImVec2 tl = ImVec2(foot.x - w/2, head.y);
        ImVec2 br = ImVec2(foot.x + w/2, foot.y);

        // 1. Futuristic Corner Box
        draw->AddLine(tl, {tl.x + l, tl.y}, COLOR_NEON_CYAN, 2.0f);
        draw->AddLine(tl, {tl.x, tl.y + l}, COLOR_NEON_CYAN, 2.0f);

        draw->AddLine({br.x - l, tl.y}, {br.x, tl.y}, COLOR_NEON_CYAN, 2.0f);
        draw->AddLine({br.x, tl.y}, {br.x, tl.y + l}, COLOR_NEON_CYAN, 2.0f);

        draw->AddLine({tl.x, br.y - l}, {tl.x, br.y}, COLOR_NEON_CYAN, 2.0f);
        draw->AddLine({tl.x, br.y}, {tl.x + l, br.y}, COLOR_NEON_CYAN, 2.0f);

        draw->AddLine({br.x - l, br.y}, br, COLOR_NEON_CYAN, 2.0f);
        draw->AddLine({br.x, br.y - l}, br, COLOR_NEON_CYAN, 2.0f);

        // 2. Glow Background
        draw->AddRectFilled(tl, br, COLOR_GLOW);

        // 3. Vertical Health Bar
        float hpHeight = h * (health / 100.0f);
        ImColor hpCol = ImColor::HSV((health / 100.0f) * 0.33f, 1.0f, 1.0f);
        draw->AddRectFilled({tl.x - 6, br.y}, {tl.x - 3, br.y - hpHeight}, hpCol);

        // 4. Data Display (Distance)
        char distBuf[32];
        sprintf(distBuf, "%dm", (int)distance);
        draw->AddText(NULL, 14.0f, {br.x + 5, tl.y}, COLOR_NEON_PINK, distBuf);
    }

    void DrawSkeleton(ImDrawList* draw, Vector2 joints[], int count) {
        for (int i = 0; i < count - 1; i++) {
            draw->AddLine({joints[i].x, joints[i].y}, {joints[i+1].x, joints[i+1].y}, ImColor(255, 255, 255, 180), 1.2f);
        }
    }
};

extern FutureESP* g_ESP;
