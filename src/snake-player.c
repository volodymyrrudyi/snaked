#include "snake-player.h"

Player*
create_player(const char* nickname, uint16_t color, uint16_t x,  uint16_t y,
        Direction direction)
{
    Player *player = (Player*)malloc(sizeof(Player));

    if (player == NULL)
    {
        SNAKE_ERROR("Can't allocate memory for new player");
        return NULL;
    }

    player->snake_head = snake_create(x, y, direction);
    if (player->snake_head == NULL)
    {
        SNAKE_ERROR("Can't create snake for player");
        free(player);
        return NULL;
    }

    return player;
}

void
player_change_direction(Player* player, Direction direction)
{
    player->snake_head->direction = direction;
}

void
player_dispose(Player *player)
{
    snake_dispose(player->snake_head);
    free(player->nickname);
    free(player);
}
