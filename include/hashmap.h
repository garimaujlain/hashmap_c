#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct _ll_node {
    uint32_t key;
    char *value;
    struct _ll_node *next;
} _ll_node_t;

typedef struct {
    _ll_node_t **buckets_arr;
    uint32_t num_elements;
    uint32_t num_buckets;
} hashmap_t;

// HashMap user-facing API
extern uint8_t hashmap_insert(hashmap_t *target, uint32_t key, const char *value);
extern uint8_t hashmap_get(hashmap_t *target, uint32_t key, char *buffer, uint32_t nbytes);
extern uint8_t hashmap_delete(hashmap_t *target, uint32_t key);
extern hashmap_t *hashmap_new(uint32_t num_buckets_initial);
extern uint8_t hashmap_destroy(hashmap_t *target);


// Functions/structs for internal use.
extern uint32_t _hash(hashmap_t *target, uint32_t x);

// Chaining/linked list internal API.
extern _ll_node_t *_ll_new(uint32_t key, const char *value);
extern uint8_t _ll_insert(_ll_node_t *head, uint32_t key, const char *value);
extern uint8_t _ll_delete(_ll_node_t *head, uint32_t key);
extern _ll_node_t *_ll_find(_ll_node_t *head, uint32_t key);
extern uint8_t _ll_destroy(_ll_node_t *head);
extern hashmap_t *_hashmap_resize(hashmap_t *target, double factor);
