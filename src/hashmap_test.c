#include <hashmap.h>

int main(void) {
    insert(32, "Aditya");
    insert(45, "Garima");
    insert(47, "Vinode");
    char tmp[50]= "";
    get(47, tmp, 50);
    printf("Hashmap returned: %s\n", tmp);
    return 0;
}