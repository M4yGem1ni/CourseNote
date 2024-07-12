#include <stdio.h>

struct Aligned {
    int a;     // 4字节
    char b[3]; // 3字节
    char c;    // 1字节
    double d;  // 8字节
};

struct Unaligned {  //（未对齐）
    int a;          // 4字节
    double d;       // 8字节
    char c;         // 1字节
    char b[3];      // 3字节
};

struct Unaligned_4byte {
    int a;          // 4字节
    char b;         // 1字节
    int c;          // 4字节
};

int main() {
    printf("Size of Aligned: %d\n", sizeof(struct Aligned));
    printf("Size of Unaligned: %d\n", sizeof(struct Unaligned));
    printf("Size of Unaligned_4byte: %d\n", sizeof(struct Unaligned_4byte));
    return 0;
}
