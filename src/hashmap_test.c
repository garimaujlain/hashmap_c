#include <hashmap.h>

int main(void) {

    _hashmap_t tmp3;
    tmp3 = new(1);
    insert(tmp3, 32, "Aditya");
    insert(tmp3, 45, "Garima");
    insert(tmp3, 47, "Vinode");

    char tmp[50]= "";
    get(tmp3, 47, tmp, 50);
    printf("Hashmap returned: %s\n", tmp);

    delete(tmp3, 47);

    char tmp1[50]= "";
    int8_t ret = get(tmp3, 47, tmp1, 50);
    printf("[%d] Hashmap returned: %s\n", ret, tmp1);
    return 0;
}