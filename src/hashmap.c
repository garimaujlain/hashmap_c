#include <hashmap.h>

#define NUM_BUCKETS 2

_ll_node_t *buckets[NUM_BUCKETS];

/* insert
   Inputs: 
        key: the key to insert
        value: the string the key maps to
    Outputs:
        None
    Returns:
        0 on success.
*/
uint8_t insert(uint32_t key, const char *value) {
    // The hash will be used to index into the array of buckets.
    uint32_t index = _hash(key);

    // If we don't have a valid linked list at the bucket,
    if (buckets[index] == NULL) {
        buckets[index] = _ll_new(key, value); // make a new one
    } else {
        // Otherwise, chain onto the existing linked list.
        _ll_insert(buckets[index], key, value);
    }
    return 0;
}

uint8_t delete(uint32_t key) {
    uint32_t index = _hash(key);
    if (buckets[index] == NULL) {
        return -1; //given key not in hashmap
    } else {
        
        _ll_delete(buckets[index], key);
    }
    return 0;


}

uint8_t get(uint32_t key, char *buffer, uint32_t nbytes) {
    uint32_t index = _hash(key);

    if (buckets[index] == NULL) {
        return -1;
    } else {

       _ll_node_t *found = _ll_find(buckets[index], key);
       if (found == NULL) {
            return -1;
       }
       strncpy(buffer, found->value, nbytes);
    }
    return 0;
}

_ll_node_t *_ll_new(uint32_t key, const char *value) {
     _ll_node_t *new_node;

    if ((new_node = malloc(sizeof(_ll_node_t))) == NULL) {
        printf("Couldn't allocate memory. Fatal.\n");
        exit(1);
    }

    // Key
    (*new_node).key = key;
    
    // Value
    char *my_copy_value;
    if ((my_copy_value = malloc(strlen(value) + 1)) == NULL) {
        printf("Couldn't allocate memory. Fatal.\n");
        exit(1);
    }
    strcpy(my_copy_value, value);
    (*new_node).value = my_copy_value;

    // Next
    new_node->next = NULL;

    return new_node;
}


uint8_t _ll_insert(_ll_node_t *head, uint32_t key, const char *value) {
    _ll_node_t *curr = head;

    if (curr == NULL) {
        printf("_ll_insert called with NULL argument! Make a linked list first with _ll_new.");
        exit(1);
    }

    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = _ll_new(key, value);
    return 0;
}

uint8_t _ll_delete(_ll_node_t *head, uint32_t key) {
    _ll_node_t *curr = head;

    if (curr == NULL) {
        printf("_ll_delete called with NULL argument!.");
        exit(1);
    }

    while (curr->key != key) {
        curr = curr->next;
    }
    free(curr);
    return 0;

}


_ll_node_t *_ll_find(_ll_node_t *head, uint32_t key) {
    _ll_node_t *curr = head;

    if (curr == NULL) {
        printf("_ll_find called with NULL argument!");
        exit(1);
    }

    for (curr = head; curr != NULL; curr = curr->next) {
        if (curr->key == key) {
            return curr;
        }
    }

    return NULL;
}

uint32_t _hash(uint32_t x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x % NUM_BUCKETS; 
}

