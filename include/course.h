#ifndef SWARMLADDER_C_H
#define SWARMLADDER_C_H
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
typedef struct {
  int16_t x, y;
} Point;
typedef struct {
  int *data;
  size_t len, cap;
} Vector;
typedef struct Node {
  int value;
  struct Node *next;
} Node;
typedef struct {
  const uint8_t *data;
  size_t len;
} Slice;
typedef struct {
  int data[8];
  size_t head, len;
} Ring;
typedef struct {
  size_t from, to;
  unsigned amount;
} Move;
typedef struct {
  uint64_t ascent;
  size_t peak;
} Trail;
typedef struct {
  size_t start, len;
} Span;
typedef struct {
  unsigned begin, end;
} Slot;
typedef bool (*Predicate)(int, void *);
typedef int (*Transform)(int);
/** Return complete minutes. */
unsigned whole_minutes(unsigned s);
/** Return the seconds field of a timer. */
unsigned clock_seconds(unsigned s);
/** Round minutes up to full hours without overflowing. */
unsigned billed_hours(unsigned m);
/** Calculate area for any two 16-bit dimensions. */
uint32_t tile_area(uint16_t a, uint16_t b);
/** Map negative, zero, positive to -1, 0, 1. */
int sign_of(int x);
/** Apply Gregorian leap-year rules. */
bool leap_year(unsigned y);
/** Charge 0 below age 6, 2 up to 17, 3 from 65, otherwise 5. */
unsigned fare(unsigned age);
/** Return the median of three ints without adding them. */
int middle(int a, int b, int c);
/** Sum decimal digits. */
unsigned digit_sum(unsigned n);
/** Count digits, including the zero in 0. */
unsigned digit_count(unsigned n);
/** Use Euclidean remainder. Define gcd(0,0) as 0. */
unsigned gcd_of(unsigned a, unsigned b);
/** Recognize primes without multiplying candidate factors. */
bool is_prime(unsigned n);
/** Count strictly negative samples. */
size_t negatives(const int *v, size_t n);
/** Count strictly rising adjacent steps. */
size_t rises(const int *v, size_t n);
/** Return first matching index, or n. */
size_t first_index(const int *v, size_t n, int key);
/** Return longest consecutive run of key. */
size_t longest_run(const int *v, size_t n, int key);
/** Recognize decimal digits. */
bool ascii_digit(char c);
/** Lowercase ASCII A–Z only. */
char ascii_lower(char c);
/** Count bytes before the terminator. */
size_t byte_length(const char *s);
/** Count runs separated by ASCII spaces or tabs. */
size_t words(const char *s);
/** Sum the two int16_t coordinates in a long. */
long point_total(Point p);
/** Decide whether either coordinate is zero. */
bool on_axis(Point p);
/** Return index of first greatest coordinate sum, or n if empty. */
size_t best_point(const Point *p, size_t n);
/** Count points in the inclusive square from -limit to limit on both axes.
 * Negative limit means empty. */
size_t enclosed(const Point *p, size_t n, int16_t limit);
/** Return total ascent and first highest index. Empty input returns {0,0}.
 * Assume total ascent fits uint64_t. */
Trail trail_report(const int16_t *v, size_t n);
/** Each visit gets five free minutes. Charge 3 credits per started 15-minute
 * block thereafter. Assume the total fits. */
uint64_t meter_bill(const uint16_t *minutes, size_t n);
/** Return start and length. Ties favor earliest; no qualifying day returns
 * {0,0}. */
Span reading_streak(const uint16_t *v, size_t n, uint16_t target);
/** Store a+b only when representable. */
bool safe_add(unsigned a, unsigned b, unsigned *out);
/** Store a*b only when representable. */
bool safe_mul(unsigned a, unsigned b, unsigned *out);
/** Write min and max to distinct outputs. Leave both intact if empty. */
bool range_of(const int *v, size_t n, int *lo, int *hi);
/** Write quotient and remainder to distinct outputs only when d is nonzero. */
bool div_parts(unsigned n, unsigned d, unsigned *q, unsigned *r);
/** Copy a string between disjoint buffers including terminator. Preserve
 * destination on failure. */
bool copy_text(char *dst, size_t cap, const char *src);
/** Reverse elements in place. */
void reverse_ints(int *v, size_t n);
/** Remove skip values in place, keeping order. Return new logical length. */
size_t compact(int *v, size_t n, int skip);
/** Delete a valid element by shifting successors left. Ignore the final storage
 * slot. */
bool erase_at(int *v, size_t n, size_t i);
/** Parse one or more ASCII digits into 0–255. Reject signs and spaces. Preserve
 * output on failure. */
bool decimal_byte(const char *s, uint8_t *out);
/** Return value of one ASCII hex digit, or -1. */
int hex_digit(char c);
/** Count tab-separated fields. Even an empty line has one field. */
size_t columns(const char *s);
/** Find first equals sign. Require a nonempty preceding key; preserve output on
 * failure. */
bool key_span(const char *s, size_t *length);
/** Find first index at least key in sorted input in logarithmic time. */
size_t lower_slot(const int *v, size_t n, int key);
/** Find first index strictly greater than key in sorted input in logarithmic
 * time. */
size_t upper_slot(const int *v, size_t n, int key);
/** Sort ascending in place by inserting one element into a sorted prefix at a
 * time. */
void insertion_sort(int *v, size_t n);
/** Compact adjacent equal values of sorted input. Return distinct count. */
size_t unique_sorted(int *v, size_t n);
/** Count matching elements by invoking test once per element. */
size_t count_if(const int *v, size_t n, Predicate test, void *ctx);
/** Return index of first match or n. Stop testing after the first match. */
size_t first_if(const int *v, size_t n, Predicate test, void *ctx);
/** Replace each element with f(element). */
void apply_each(int *v, size_t n, Transform f);
/** Count the matching prefix only. */
size_t take_while(const int *v, size_t n, Predicate f, void *ctx);
/** Read and return one byte as int, or EOF. */
int first_byte(FILE *in);
/** Count newline bytes through EOF on a readable error-free input stream. */
size_t newlines(FILE *in);
/** Write a string followed by a newline. Report any immediate write failure. */
bool emit_line(FILE *out, const char *s);
/** Copy through EOF and detect read and immediate write errors. Flushing is the
 * caller’s responsibility. */
bool copy_stream(FILE *in, FILE *out);
/** Input spans are half-open minutes of one day. Reject empty, reversed or
 * out-of-day spans without changing output. Return unique occupied minutes. */
bool room_usage(const Slot *v, size_t n, unsigned *used);
/** Validate scores 0–100. Fill five counts for 0–59, 60–69, 70–79, 80–89 and
 * 90–100. Invalid input preserves all five outputs. */
bool grade_bins(const unsigned *v, size_t n, size_t *bins);
/** Prefix each logical line with its one-based number and a space. Preserve
 * existing newlines and final unterminated text. Empty input produces nothing.
 * Report read or immediate write errors. Assume line numbers fit size_t. */
bool transcript(FILE *in, FILE *out);
/** Allocate an independent copy. Return NULL on zero length, excessive size, or
 * allocation failure. */
int *clone_values(const int *v, size_t n);
/** Grow capacity to at least need, preserving length and contents. Keep all
 * fields intact on failure. */
bool reserve_values(Vector *v, size_t need);
/** Append one value. Grow geometrically where possible. Return false with
 * original state on allocation failure. */
bool push_value(Vector *v, int x);
/** Free owned storage and set all fields to zero so repeated release is valid.
 */
void release_values(Vector *v);
/** Count nodes in an acyclic list. */
size_t list_len(const Node *head);
/** Reverse links in place and return the new head. */
Node *reverse_list(Node *head);
/** Unlink the first matching node and clear its next link. Return NULL if
 * missing. */
Node *detach(Node **head, int key);
/** Detect a cycle using constant additional storage. */
bool has_cycle(const Node *head);
/** Read two big-endian bytes. */
uint16_t read_be16(const uint8_t *p);
/** Write four bytes least significant first. */
void write_le32(uint8_t *p, uint32_t x);
/** Consume a two-byte big-endian length and its payload. On truncation leave
 * both distinct slice descriptors unchanged. */
bool next_frame(Slice *input, Slice *payload);
/** Return the additive complement modulo 256. */
uint8_t check_byte(const uint8_t *p, size_t n);
/** Append to an eight-slot ring; reject a full queue. */
bool ring_put(Ring *r, int x);
/** Remove oldest value. On empty leave output unchanged. */
bool ring_get(Ring *r, int *out);
/** Read by logical index without consuming. Reject indices outside the live
 * range. */
bool ring_at(const Ring *r, size_t i, int *out);
/** Discard at most n oldest items, returning the number removed. */
size_t ring_drop(Ring *r, size_t n);
/** Test membership at indices 0–31; return false elsewhere. */
bool bit_member(uint32_t set, unsigned i);
/** Toggle a valid bit and report success. Invalid indices preserve the mask. */
bool bit_toggle(uint32_t *set, unsigned i);
/** Count set bits without a lookup table. */
unsigned population(uint32_t set);
/** Rotate bits left by n modulo 32. */
uint32_t rotate_left(uint32_t x, unsigned n);
/** Subtract only when funds suffice. */
bool debit(unsigned *balance, unsigned amount);
/** Add only when the new balance fits. */
bool credit(unsigned *balance, unsigned amount);
/** Reject invalid or equal indices, insufficient funds and destination
 * overflow. Preserve balances on failure. */
bool move_funds(unsigned *a, size_t n, Move m);
/** Stage n moves across four accounts. Commit only if every move is valid. */
bool settle_four(unsigned *accounts, const Move *moves, size_t n);
/** Walk two-byte big-endian length-prefixed frames without allocation. Count
 * empty frames. Reject trailing fragments and preserve count on error. */
bool inspect_capture(Slice input, size_t *count);
/** Write the latest at most eight readings, oldest first, to a disjoint
 * eight-slot output. Return their count. Model the incoming data as a stream
 * using a circular buffer. */
size_t replay_recent(const int *v, size_t n, int *out);
/** Stage four bins. Reject invalid or equal indices, insufficient stock or
 * recipient overflow. On failure record first bad index and preserve bins. On
 * success commit bins and set bad to n. */
bool audit_stock(unsigned *bins, const Move *v, size_t n, size_t *bad);
#endif
