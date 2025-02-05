#include "scene.h"
#include "stdlib.h"
#include "utils.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#define MAX_HIERARCHY_LENGTH 1000
#define EachOnScene(actor) \
    for (size_t i = 0; i < MAX_HIERARCHY_LENGTH; i++) \
        if (hierarchy[i].instantiated) \
            for (int keep = 1; keep; keep = 0) \
                for (actor = hierarchy[i]; keep; keep = 0)

static const float maxSpeed = 35.f;
static const int backgroundSize = 32000;

static Actor hierarchy[MAX_HIERARCHY_LENGTH];
static int _id_counter = 0;
static Actor* player;
static Vector2 playerVelocity = {0,0};
static float playerHp = 100.f;
static Texture2D background;

Actor* AddActor(Vector2 position, Vector2 rotation, Texture2D texture) {
    if (_id_counter == MAX_HIERARCHY_LENGTH) {
        abort();
    }
    Actor act = { _id_counter, true, position, rotation, texture };
    hierarchy[_id_counter] = act;
    _id_counter++;
    return &hierarchy[_id_counter-1];
}

static void DrawBackground() {
    DrawTexturePro(
        background,
        (Rectangle) {0, 0, backgroundSize, backgroundSize},
        (Rectangle) {-backgroundSize/2, -backgroundSize/2, backgroundSize, backgroundSize},
        (Vector2) {0.f, 0.f},
        0, 
        WHITE);
}

void InitScene(Context ctx) {
    Vector2 playerPos = { 0, 0 };
    Vector2 playerRotation = { 0.f, 0.f };
    player = AddActor(playerPos, playerRotation, LoadTexture("resources/fighter.png"));
    background = LoadTexture("resources/wallpaper.png");
}

void OnDraw(Context ctx) {
    DrawBackground();
    EachOnScene(Actor actor) {
        DrawTexturePro(
            actor.texture, 
            (Rectangle) { 0, 0, actor.texture.width, actor.texture.height},
            (Rectangle) { actor.position.x, actor.position.y, actor.texture.width, actor.texture.height },
            (Vector2) { actor.texture.width / 2, actor.texture.height / 2 }, 
            actor.rotation.x, WHITE);
    };
}

void OnDrawGui(Context ctx) {
    GuiProgressBar((Rectangle) { 24, 24, 120, 20 }, "", "HP", & playerHp, 0.f, 100.f);
}

void OnUpdate(Context ctx) {
    Vector2 newVelocity = playerVelocity;
    if (IsKeyDown(KEY_W)) {
        newVelocity = Vector2ClampValue(Vector2Add(playerVelocity, GetForwardVector2D(player->rotation.x)), -maxSpeed, maxSpeed);
    }
    if (IsKeyDown(KEY_S)) {
        newVelocity = Vector2ClampValue(Vector2Subtract(playerVelocity, GetForwardVector2D(player->rotation.x)), -maxSpeed, maxSpeed);
    }

    playerVelocity = newVelocity;

    if (IsKeyDown(KEY_A)) {
        player->rotation.x-=2;
    }
    if (IsKeyDown(KEY_D)) {
        player->rotation.x+=2;
    }
    
    player->position = Vector2Add(player->position, Vector2Scale(playerVelocity, 0.1f));
    ctx.camera->target = player->position;
    ctx.camera->offset = (Vector2) { GetScreenWidth() / 2.f, GetScreenHeight() / 2.f };
}

void OnDestroy(Context ctx) {
    
}
