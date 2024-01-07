#include <hashmap.h>


int main(void) {
    insert(32, "Aditya");
    insert(45, "Garima");
    insert(47, "Vinode");
    insert(48, "Supriya");
    insert(49, "Tarunika");
    insert(50, "Durga");

    char tmp[50]= "";
    get(47, tmp, 50);
    printf("Hashmap returned: %s\n", tmp);

    /* delete(32); */
    delete(47);
    insert(99, "Vijay");
    insert(100, "Sona");

    char tmp1[50]= "";
    get(50, tmp1, 50);
    printf("Hashmap returned: %s\n", tmp1);
    return 0;
}