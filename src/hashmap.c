#include <hashmap.h>


hashmap_t *hashmap_new(uint32_t num_buckets_initial) {
    hashmap_t *new_hashmap;

    if ((new_hashmap = malloc(sizeof(hashmap_t))) == NULL) {
        printf("Couldn't allocate memory. Fatal.\n");
        exit(1);
    }

    new_hashmap->buckets_arr = malloc(sizeof(_ll_node_t) * num_buckets_initial);

    if (new_hashmap->buckets_arr == NULL) {
        printf("Couldn't allocate memory. Fatal.\n");
        exit(1);
    }

    new_hashmap->num_buckets = num_buckets_initial;
    new_hashmap->num_elements = 0;

    for (uint32_t i = 0; i < num_buckets_initial; i++) {
      new_hashmap->buckets_arr[i] = NULL;
    }

    return new_hashmap;
}

/* insert
   Inputs: 
        key: the key to insert
        value: the string the key maps to
    Outputs:
        None
    Returns:
        0 on success. All other return codes imply failure.
*/
uint8_t hashmap_insert(hashmap_t *target, uint32_t key, const char *value) {
    // The hash will be used to index into the array of buckets.
    uint32_t index = _hash(target, key);
    uint32_t load_factor_after_insert = ((target->num_elements) + 1) / target->num_buckets;
    if (load_factor_after_insert > 0.8){
        _hashmap_resize(target, 1.5);
    }

    // If we don't have a valid linked list at the bucket,
    if (target->buckets_arr[index] == NULL) {
        target->buckets_arr[index] = _ll_new(key, value); // make a new one
        target->num_elements = target->num_elements + 1;
    } else {
        // Otherwise, chain onto the existing linked list.
        _ll_insert(target->buckets_arr[index], key, value);
        target->num_elements = target->num_elements + 1;
    }
    return 0;
}

uint8_t hashmap_delete(hashmap_t *target, uint32_t key) {
    uint32_t index = _hash(target, key);

    uint32_t load_factor_after_delete = ((target->num_elements) - 1) / target->num_buckets;
    if (load_factor_after_delete < 0.25){
        _hashmap_resize(target, 0.66);
    }

    _ll_node_t *head = target->buckets_arr[index];
    
    if (target->buckets_arr[index] == NULL) {
        return -1; //given key not in hashmap
    } else if (head->key == key){
        target->buckets_arr[index] = head->next;
        free(head->value);
        free(head);
    } else {
        _ll_delete(target->buckets_arr[index], key);
    }
    return 0;
}

uint8_t hashmap_destroy(hashmap_t *target) {
    if (target == NULL) {
        return -1; 
    }
 
    for (uint32_t i = 0; i < target->num_buckets; i++){
        if (target->buckets_arr[i] != NULL) {
            _ll_destroy(target->buckets_arr[i]);
        }
    }

    free(target->buckets_arr);
    free(target);
    return 0;

}

uint8_t hashmap_get(hashmap_t *target, uint32_t key, char *buffer, uint32_t nbytes) {
    uint32_t index = _hash(target, key);

    if (target->buckets_arr[index] == NULL) {
        return -1;
    } else {
       _ll_node_t *found = _ll_find(target->buckets_arr[index], key);
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

    while (curr->next != NULL && curr->key != key) {
        curr = curr->next;
    }

    if (curr->key == key){
        char *my_copy_new_value;
        if ((my_copy_new_value = malloc(strlen(value) + 1)) == NULL) {
            printf("Couldn't allocate memory. Fatal.\n");
            exit(1);
        }
        strcpy(my_copy_new_value, value);
        char *copy_overwritten_value = curr->value;
        curr->value = my_copy_new_value;
        free(copy_overwritten_value);
        
    } else {
        curr->next = _ll_new(key, value);
    }

    return 0;
}

uint8_t _ll_delete(_ll_node_t *head, uint32_t key) {
    _ll_node_t *curr = head;

    if (curr == NULL) {
        printf("_ll_delete called with NULL argument!.");
        exit(1);
    }

    _ll_node_t *prev = NULL;
    while (curr != NULL) {
        if (curr->key == key) {
            prev->next = curr->next;
            free(curr->value);
            free(curr);
            return 0;
        }
        prev = curr;
        curr = curr->next;
    }
    
    return -1;

}

uint8_t _ll_destroy(_ll_node_t *head) {
    _ll_node_t *curr = head;

    if (head == NULL) {
        printf("_ll_destroy called with NULL argument!.");
        return -1;
    }

    _ll_node_t *to_delete = NULL;

    while (curr != NULL) {
        to_delete = curr;
        curr = curr->next;
        free(to_delete->value);
        free(to_delete);
    }

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

uint32_t _hash(hashmap_t *target, uint32_t x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x % target->num_buckets; 
}

uint8_t _hashmap_resize(hashmap_t *target, uint32_t factor) {
   
    hashmap_t *my_copy_hashmap;

    if ((my_copy_hashmap = malloc(sizeof(hashmap_t))) == NULL) {
        printf("Couldn't allocate memory. Fatal.\n");
        exit(1);
    }

    my_copy_hashmap->buckets_arr = malloc(sizeof(_ll_node_t) * ((target->num_buckets) * factor));

    if (my_copy_hashmap->buckets_arr == NULL) {
        printf("Couldn't allocate memory. Fatal.\n");
        exit(1);
    }

    for (uint32_t i = 0; i < target->num_buckets; i++) {

       while (target->buckets_arr[i] != NULL) {
        _ll_node_t *curr = target->buckets_arr[i];
        char *my_copy_value_i;
        if ((my_copy_value_i = malloc(strlen(curr->value) + 1)) == NULL) {
        printf("Couldn't allocate memory. Fatal.\n");
        exit(1);
        }
        strcpy(my_copy_value_i, curr->value);
        hashmap_insert(my_copy_hashmap, curr->key, my_copy_value_i);

        target->buckets_arr[i] = curr->next;
        free(curr->value);
        free(curr);
       }
    }
    
    my_copy_hashmap->num_buckets = (target->num_buckets) * 1.5;
    my_copy_hashmap->num_elements = target->num_elements;

    hashmap_destroy(target);
    return 0;
}
