#ifndef __CW_RINGBUF_U8__
#define __CW_RINGBUF_U8__

#include <stdint.h>

// Size must be predefined, otherwise need dynamic memory alhead, which is
// not a good idea on an AVR. In this case we will use 256.
#ifndef RBU8_SIZE
#define RBU8_SIZE 256
#endif

typedef struct {
    uint8_t array[RBU8_SIZE];
    uint8_t head;
} ringbuf_u8_t;

/**
 * Create a new ringbuffer and clear it filling it with zeros and setting
 * the head to the appropriate position
 *
 * @return A fresh new, and zero-filled ring buffer.
 */
ringbuf_u8_t create_ringbuf_u8_t();

/**
 * Clear a ring buffer by filling it with zeros!
 *
 * @param  ringbuf_u8_t  *A  Pointer to the ring buffer structure that
 *                           will be zero filled. (`head' is also reset).
 */
void clear(ringbuf_u8_t *A);


/**
 * push_back a value (new_val) into the Ring Buffer A. Also repositions the
 * head position by incremening it by one (wrapped around RBU8_SIZE
 *
 * @param  ringbuf_u8_t  *A  Pointer to the ringbuffer structure that
 *                           will have a value added and its head position
 *                           moved.
 * @param  uint8_t  new_val  The value of what is being pushed back
 */
void push_back(ringbuf_u8_t *A, uint8_t new_val);


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
uint8_t get_value(ringbuf_u8_t *A, uint8_t index);

#endif
