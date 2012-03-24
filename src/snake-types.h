#ifndef __SNAKE_TYPES_H
#define __SNAKE_TYPES_H

#include <stdint.h>

enum _Direction
{
    Left,
    Right,
    Up,
    Down
};

enum _CellType
{
    Empty,
    Fruit,
    Wall,
    Bone
};


typedef struct _Game Game;
typedef struct _Field Field;
typedef struct _Cell Cell;
typedef struct _Player Player;
typedef struct _SnakeSection SnakeSection;
typedef enum _CellType CellType;
typedef enum _Direction Direction;

#endif
