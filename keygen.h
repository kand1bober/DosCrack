#ifndef KEYGEN_HEADER
#define KEYGEN_HEADER

#include <sys/stat.h>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Audio/Music.hpp>

#include <sys/stat.h>
#include <math.h>

typedef struct point
{
    float x;
    float y;
}
Point;

typedef struct PicturePosition
{
    int width;
    int height;
    point UL;
    float delta_x;
    float delta_y;
    bool move_to_right;
    bool move_down;
}
PicPos;

void MakeVideoAndPatch();
void ChangeDirection( PicPos *position );
void patcher();

#endif
