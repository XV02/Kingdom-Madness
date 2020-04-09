//
// Created by alan2 on 30/03/2020.
//

#ifndef PROGRA_GAME_DATA_H
#define PROGRA_GAME_DATA_H

#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include "inventory.h"

typedef struct item_data_t
{
    item_resource_e item;
    uint8_t quantity;
} item_data_t;

typedef struct game_state_t
{
    struct
    {
        int boss1: 1;
        int boss2: 1;
        int boss3: 1;
        int boss4: 1;
    } boss_defeated;
    uint8_t health;
    uint8_t max_health;
    item_data_t items[2][3];
    time_t saved_time;
} game_state_t;


void save_game(game_state_t *state, uint8_t slot);

void fill_game_state_inventory_data(game_state_t *state, inventory_t *inventory);

void get_inventory_from_game_state(inventory_t *inventory, game_state_t *state);

game_state_t load_game(uint8_t slot);

#endif //PROGRA_GAME_DATA_H