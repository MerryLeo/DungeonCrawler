#ifndef ITEM_H
#define ITEM_H

// Description of an item
typedef struct {
    char *general_description;
    char *specific_description;
} DESCRIPTION;

typedef struct {
    int light;
} TORCH;

typedef struct {
    DESCRIPTION info;
    TORCH *torch;
    int can_be_picked;
} ITEM;

typedef struct {
    ITEM *items;
} INVENTORY;

#endif