#include <stdio.h>

int cb_pushback(int *buf, int **head, int *buf_end, int sz, int a) {
    **head = a;
    if ((*head) + 1 == buf_end) {
        *head = buf;
    } else {
        (*head)++;
    }
    return 0;
}

typedef struct {
    int *buf;
    int *head;
    int *buf_end;
} intRingBuf_t;

int main() {
    const int sz = 10;
    int buf[sz];
    int *head = buf;
    int *buf_end = buf + (sizeof(buf)/sizeof(buf[0]));

    printf("start:%i | head: %i | end: %i\n", (int)buf, (int)head, (int)buf_end);
    cb_pushback(buf, &head, buf_end, sz, 1);
    printf("start:%i | head: %i | end: %i\n", (int)buf, (int)head, (int)buf_end);
    cb_pushback(buf, &head, buf_end, sz, 2);    
    printf("start:%i | head: %i | end: %i\n", (int)buf, (int)head, (int)buf_end);
    cb_pushback(buf, &head, buf_end, sz, 3);
    printf("start:%i | head: %i | end: %i\n", (int)buf, (int)head, (int)buf_end);
    cb_pushback(buf, &head, buf_end, sz, 4);    
    printf("start:%i | head: %i | end: %i\n", (int)buf, (int)head, (int)buf_end);
    cb_pushback(buf, &head, buf_end, sz, 5);
    printf("start:%i | head: %i | end: %i\n", (int)buf, (int)head, (int)buf_end);
    cb_pushback(buf, &head, buf_end, sz, 6);    
    printf("start:%i | head: %i | end: %i\n", (int)buf, (int)head, (int)buf_end);
    cb_pushback(buf, &head, buf_end, sz, 7);
    printf("start:%i | head: %i | end: %i\n", (int)buf, (int)head, (int)buf_end);
    cb_pushback(buf, &head, buf_end, sz, 8);    
    printf("start:%i | head: %i | end: %i\n", (int)buf, (int)head, (int)buf_end);
    cb_pushback(buf, &head, buf_end, sz, 9);
    printf("start:%i | head: %i | end: %i\n", (int)buf, (int)head, (int)buf_end);
    cb_pushback(buf, &head, buf_end, sz, 10);    
    printf("start:%i | head: %i | end: %i\n", (int)buf, (int)head, (int)buf_end);
    cb_pushback(buf, &head, buf_end, sz, 11);
    printf("start:%i | head: %i | end: %i\n", (int)buf, (int)head, (int)buf_end);
    cb_pushback(buf, &head, buf_end, sz, 12);    
    printf("start:%i | head: %i | end: %i\n", (int)buf, (int)head, (int)buf_end);
    cb_pushback(buf, &head, buf_end, sz, 13);
    printf("start:%i | head: %i | end: %i\n", (int)buf, (int)head, (int)buf_end);
    cb_pushback(buf, &head, buf_end, sz, 14);    
    printf("start:%i | head: %i | end: %i\n", (int)buf, (int)head, (int)buf_end);

    for (int i = 0; i < sz; i++) {
        printf("%i\n", buf[i]);

    }

    return 0;
}
