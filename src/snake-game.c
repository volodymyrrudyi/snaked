#include "game.h"

Game*
game_create()
{
    return NULL;
}

void
game_add_player(Game *game, Player *player)
{
    game->player_count += 1;
    game->players = (Player*)realloc(game->players, sizeof(Player)*game->player_count);
    memcpy(&game->players[game->player_count - 1], player, sizeof(Player));
}

void
game_dispose(Game* game)
{
    for(int player = 0; player < game->player_count; player++)
    {
        player_dispose(&game->players[player]);
        field_dispose(game->field);
    }

    game_dispose(game);
}

void
game_process_player_action(Game *game, Player *player, Action* action)
{
    switch(action->type)
    {
        case Movement:
            break;
        case Exit:
            break;
        default:
            break;
    }
}
