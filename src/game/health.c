//
// Created by alan2 on 25/02/2020.
//

#include "game/health.h"
#include "utils/colors.h"
#include <curses.h>
#include <stdlib.h>
#include <utils/render_graph.h>

const uint8_t START_HEALTH = 80;

void draw_health(health_t *health)
{
    resize_window(health->window, 1, health->max_health);

    for (int i = 0; i < health->max_health; i+=10)
    {
        const uint16_t color = i < health->health ? HEART_POINT_COLOR_PAIR : HEART_LOST_COLOR_PAIR;
        wattron(health->window, COLOR_PAIR(color));
        mvwaddstr(health->window, 0, (int)i/10, "♥");
        wattroff(health->window, COLOR_PAIR(color));
    }

    wrefresh(health->window);
}

health_t *start_health(render_node_t * node)
{
    health_t *health = malloc(sizeof(health_t));
    health->window = newwin(1, 14, 0, 0);
    health->health = START_HEALTH;
    health->max_health = START_HEALTH;
    node->draw_callback = (draw_callback_c) draw_health;
    node->param = health;
    health->health_node = node;

    return health;
}

void delete_health(health_t *health)
{
    delwin(health->window);
    free(health);
}

void add_health(health_t *health, int16_t quantity)
{
    if ((int16_t) health->health + quantity < 0) // quantity < 0
    {
        health->health = 0;
    }
    else if (health->health > health->max_health)
    {
        health->health = health->max_health;
    }
    else
    {
        health->health += quantity;
    }
}
