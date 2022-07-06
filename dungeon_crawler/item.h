#ifndef ITEM_H
#define ITEM_H

typedef struct description {
    char *text;
} DESCRIPTION;

typedef struct item {
    DESCRIPTION info;
} ITEM;

typedef struct inventory {
    ITEM *items;
} INVENTORY;

#endif