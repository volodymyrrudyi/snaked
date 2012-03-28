#include "snake-game.h"

Game*
game_create(uint16_t width, uint16_t height)
{
    Game* new_game = (Game*)malloc(sizeof(Game));
    new_game->player_count = 0;
    new_game->players = NULL;
    new_game->field = field_create(width, height);
    return new_game;
}

Player*
game_add_player(Game *game, const char *nickname)
{
    game->player_count += 1;
    game->players = (Player**)realloc(game->players, sizeof(Player*)*game->player_count);

    game->players[game->player_count - 1] = (Player*)malloc(sizeof(Player));
    game->players[game->player_count - 1]->nickname = (char*)malloc(sizeof(char) * strlen(nickname) + 1);
    strcpy(game->players[game->player_count - 1]->nickname, nickname);

    return game->players[game->player_count - 1];
}

void
game_dispose(Game* game)
{
    for(int player = 0; player < game->player_count; player++)
    {
        player_dispose(game->players[player]);
        field_dispose(game->field);
    }

    free(game->players);
    free(game);
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
