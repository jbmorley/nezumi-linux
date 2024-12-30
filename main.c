#include "raylib.h"
#include <stdio.h>

#define FRAME_COUNT 7

int main(void)
{
    const int screenWidth = 540;
    const int screenHeight = 540;

    const float scale = 6.0f;
    
    InitWindow(screenWidth, screenHeight, "Nezumi");

    // Load the frames.
    Texture2D frames[FRAME_COUNT];
    for (int i = 0; i < FRAME_COUNT; i++) {
        char path[255];  // TODO: Cleaner string handling?
        sprintf(path, "resources/sleep-%02d.png", i);
        printf("Loading '%s'...\n", path);
        Image image = LoadImage(path);
        frames[i] = LoadTextureFromImage(image);
        SetTextureFilter(frames[i], TEXTURE_FILTER_POINT);
        UnloadImage(image);
    }

    const float framesPerSecond = 3;
    const float frameDuration = 1.0 / framesPerSecond;
    int frame = 0;
    float accumulator = 0.0f;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // We use an accumulator to ensure accurate frame timing and allow
        // us to maintain a consistent frame irrespective of our rendering
        // performance.
        accumulator += GetFrameTime();
        while (accumulator > frameDuration) {
            accumulator -= frameDuration;
            frame = (frame + 1) % FRAME_COUNT;
        }

        Texture2D texture = frames[frame];
        DrawTextureEx(
            texture,
            (Vector2){
                (screenWidth - (texture.width * scale)) / 2,
                (screenHeight - (texture.height * scale)) / 2
            },
            0.0f,
            scale,
            WHITE
        );

        EndDrawing();
    }

    CloseWindow();

    // Unload the textures.
    for (int i = 0; i < FRAME_COUNT; i++) {
        UnloadTexture(frames[i]);
    }


    return 0;
}
