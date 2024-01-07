#include <hashmap.h>


int main(void) {
    insert(32, "Aditya");
    insert(45, "Garima");
    insert(47, "Vinode");

    char tmp[50]= "";
    get(47, tmp, 50);
    printf("Hashmap returned: %s\n", tmp);

    delete(47);

    char tmp1[50]= "";
    int8_t ret = get(47, tmp1, 50);
    printf("[%d] Hashmap returned: %s\n", ret, tmp1);
    return 0;
}