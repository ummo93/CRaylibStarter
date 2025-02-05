#include "raylib.h"
#include "settings.h"
#include "structs.h"
#include "scene.h"

int main(void) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    SetWindowState(FLAG_WINDOW_ALWAYS_RUN | FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(TARGET_FPS);
#ifdef _DEBUG
    SetTraceLogLevel(LOG_ALL);
#else
    SetTraceLogLevel(LOG_ERROR);
#endif

    Camera2D camera = { {0.f, 0.f}, {0.f, 0.f}, 0.f, 1.f };
    Context ctx = { &camera };

    InitScene(ctx);

    // Main game loop
    while (!WindowShouldClose()) {
        OnUpdate(ctx);
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(camera);
        OnDraw(ctx);
        EndMode2D();
        OnDrawGui(ctx);
        EndDrawing();
    }
    OnDestroy(ctx);
    CloseWindow();
    return 0;
}
