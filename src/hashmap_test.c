#include <hashmap.h>

int main(void) {

    hashmap_t *tmp3;
    tmp3 = hashmap_new(2);
    printf("Hashmap num buckets: %d\n", tmp3->num_buckets);
    tmp3 = hashmap_insert(tmp3, 32, "Adityaa");
    printf("Hashmap num buckets: %d\n", tmp3->num_buckets);
    tmp3 = hashmap_insert(tmp3, 45, "Garima");
    tmp3 = hashmap_insert(tmp3, 47, "Vinode");
    printf("Hashmap num buckets: %d\n", tmp3->num_buckets);
    tmp3 = hashmap_insert(tmp3, 47, "Vijay");
    tmp3 = hashmap_delete(tmp3, 45);
    printf("Hashmap num buckets: %d\n", tmp3->num_buckets);
   
    char tmp[50]= "";
    hashmap_get(tmp3, 32, tmp, 50);
    printf("Hashmap returned: %s\n", tmp);
    
    hashmap_get(tmp3, 47, tmp, 50);
    printf("Hashmap returned: %s\n", tmp);
   

    tmp3 = hashmap_delete(tmp3, 32);
    printf("Hashmap num buckets: %d\n", tmp3->num_buckets);

    char tmp1[50]= "";
    int8_t ret = hashmap_get(tmp3, 47, tmp1, 50);
    printf("[%d] Hashmap returned: %s\n", ret, tmp1);
    hashmap_destroy(tmp3);
    return 0;
}