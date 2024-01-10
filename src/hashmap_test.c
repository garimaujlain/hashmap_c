#include <hashmap.h>

int main(void) {

    hashmap_t *tmp3;
    tmp3 = hashmap_new(64);
    hashmap_insert(tmp3, 32, "Adityaa");
    hashmap_insert(tmp3, 45, "Garima");
    hashmap_insert(tmp3, 47, "Vinode");
    hashmap_insert(tmp3, 47, "Vijay");
    printf("Hashmap num buckets: %d\n", tmp3->num_buckets);
   
    
    char tmp[50]= "";
    hashmap_get(tmp3, 32, tmp, 50);
    printf("Hashmap returned: %s\n", tmp);
    hashmap_get(tmp3, 45, tmp, 50);
    printf("Hashmap returned: %s\n", tmp);
    hashmap_get(tmp3, 47, tmp, 50);
    printf("Hashmap returned: %s\n", tmp);
   

    hashmap_delete(tmp3, 32);

    char tmp1[50]= "";
    int8_t ret = hashmap_get(tmp3, 47, tmp1, 50);
    printf("[%d] Hashmap returned: %s\n", ret, tmp1);
    hashmap_destroy(tmp3);
    return 0;
}