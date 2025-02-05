#ifndef SCENE_H
#define SCENE_H

#include "structs.h"

void InitScene(Context ctx);
void OnDraw(Context ctx);
void OnDrawGui(Context ctx);
void OnUpdate(Context ctx);
void OnDestroy(Context ctx);

#endif