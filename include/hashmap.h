#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// HashMap user-facing API
extern uint8_t insert(uint32_t key, const char *value);
extern uint8_t get(uint32_t key, char *buffer, uint32_t nbytes);
extern uint8_t delete(uint32_t key);

// Functions/structs for internal use.

typedef struct _ll_node {
    uint32_t key;
    char *value;
    struct _ll_node *next;
} _ll_node_t;

extern uint32_t _hash(uint32_t x);

// Chaining/linked list internal API.
extern _ll_node_t *_ll_new(uint32_t key, const char *value);
extern uint8_t _ll_insert(_ll_node_t *head, uint32_t key, const char *value);
extern uint8_t _ll_delete(_ll_node_t *head, uint32_t key);
extern _ll_node_t *_ll_find(_ll_node_t *head, uint32_t key);
