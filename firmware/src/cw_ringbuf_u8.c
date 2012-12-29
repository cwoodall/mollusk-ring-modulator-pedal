#include "cw_ringbuf_u8.h"
#include <stdint.h>

/**
 * Create a new ringbuffer and clear it filling it with zeros and setting
 * the head to the appropriate position
 *
 * @return A fresh new, and zero-filled ring buffer.
 */
ringbuf_u8_t create_ringbuf_u8_t() {
    ringbuf_u8_t A;
    clear(&A);
    return A;
}

/**
 * Clear a ring buffer by filling it with zeros!
 *
 * @param  ringbuf_u8_t  *A  Pointer to the ring buffer structure that
 *                           will be zero filled. (`head' is also reset).
 */
void clear(ringbuf_u8_t *A) {
    A->head = 0;
    for (int i = 0; i < RBU8_SIZE; i++)
        A->array[i] = 0;
} 

/**
 * push_back a value (new_val) into the Ring Buffer A. Also repositions the
 * head position by incremening it by one (wrapped around RBU8_SIZE
 *
 * @param  ringbuf_u8_t  *A  Pointer to the ringbuffer structure that
 *                           will have a value added and its head position
 *                           moved.
 * @param  uint8_t  new_val  The value of what is being pushed back
 */
void push_back(ringbuf_u8_t *A, uint8_t new_val) {
    A->array[A->head] = new_val;

    if (A->head == (RBU8_SIZE-1))
        A->head = 0;   
    else
        A->head += 1;
}

/**
 * get_value returns the value of the ring buffer in relation to the current index
 * (head-1) of the ring buffer. Basic idea (head-1-index) % SIZE
 *
 * @param ringbuf_u8_t   *A   The uint8_t based array
 * @param uint8_t   index   The index from the current value (head-1). For example,
 *                          index=1 will look into the value at head-2 wrapped around
 *                          the size of the array.
 *
 * @return uint8_t value at the specified point
 */
uint8_t get_value(ringbuf_u8_t *A, uint8_t index) {
    // Calculate the wrap index. If RBU8_SIZE is 256 it will
    // wrap automatically because head is a uint8_t.
    uint8_t wrap_index = ((A->head)-1-index);
    // Otherwise calculate the proper index wrapped to RBU8_SIZE
#if RBU8_SIZE < 256
    if (wrap_index >= RBU8_SIZE) {
        wrap_index = RBU8_SIZE-(0xFF - wrap_index)-1;
    } 
#endif

    return A->array[wrap_index];
}

/* // Some test code */
/* int main() { */
/*     ringbuf_u8_t A; */

/*     A.array[0] = 1; */
/*     printf("%i\n", A.array[0]); */
    
/*     clear(&A); */
/*     printf("%i\n", A.array[0]); */
    
/*     for (int i = 0; i < RBU8_SIZE; i++) { */
/*         push_back(&A, i); */
/*         printf("[%i]: %i\n", A.head, A.array[i]); */
/*     } */
/*     push_back(&A, 22); */
/*     printf("[%i]: %i\n", A.head, A.array[A.head-1]); */

/*     printf("%i\n", get_value(&A, 0)); */
/*     printf("%i\n", get_value(&A, 1)); */
/*     printf("%i\n", get_value(&A, 3)); */
/*     return 0; */
/* } */
