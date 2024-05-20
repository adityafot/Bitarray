#include <stdio.h>
#include<stdlib.h>
typedef struct {
    int size;
    unsigned char *data;
} BitArray;

BitArray *create(int size) {
    if (size <= 0) return NULL;
    int bytes = (size + 7) / 8;
    BitArray *array = malloc(sizeof(BitArray) + bytes);
    if (array == NULL) return NULL;
    array->size = size;
    array->data = (unsigned char *)(array + 1);
    for (int i = 0; i < bytes; i++) array->data[i] = 0;
    return array;
}

void set(BitArray *array, int position) {
    int p = position / 8;
    array->data[p] = 1;
}

int get(BitArray *array, int position) {
    if (position < 0 || position >= array->size) return -1;
    int p = position / 8;
    int bitpos = position % 8;
    return (array->data[p] >> bitpos) & 1;
}

int toggle(BitArray *array, int position) {
    if (position < 0 || position >= array->size) {
        return -1;
    }

    int p = position / 8;
    int bipos = position % 8;

    array->data[p] ^=(1 << bipos);

    return 0;
}
int get_size(BitArray *array) {
    return array->size;
}

int count_set_bits(BitArray *array) {
    int count = 0;
    for (int i = 0; i < (array->size + 7) / 8; i++) {
        unsigned char byte = array->data[i];
        count ++;
    }
    return count;
}

int main() {
    BitArray *array = create(10);
    set(array, 3);
    set(array, 7);
    printf("Bit at index 3: %d\n", get(array, 3));
    printf("Bit at index 7: %d\n", get(array, 7));
    printf("Number of set bits: %d\n", count_set_bits(array));
    free(array);
    return 0;
}
