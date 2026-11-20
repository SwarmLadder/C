#include "course.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#define CHECK(expr)                                                            \
  do {                                                                         \
    if (!(expr)) {                                                             \
      fprintf(stderr, "%s:%d: %s\n", __func__, __LINE__, #expr);               \
      exit(1);                                                                 \
    }                                                                          \
  } while (0)
static FILE *stream(const char *s) {
  FILE *f = tmpfile();
  CHECK(f);
  CHECK(fputs(s, f) != EOF);
  rewind(f);
  return f;
}
static bool above(int x, void *ctx) { return x > *(int *)ctx; }
static bool observe(int x, void *ctx) {
  ++*(int *)ctx;
  return x != 0;
}
static int positive(int x) { return x > 0; }

static void test_whole_minutes(void) {
  CHECK(whole_minutes(59) == 0 && whole_minutes(125) == 2);
}

static void test_clock_seconds(void) {
  CHECK(clock_seconds(60) == 0 && clock_seconds(125) == 5);
}

static void test_billed_hours(void) {
  CHECK(billed_hours(0) == 0 && billed_hours(61) == 2 &&
        billed_hours(UINT_MAX) == UINT_MAX / 60 + (UINT_MAX % 60 != 0));
}

static void test_tile_area(void) {
  CHECK(tile_area(65535, 65535) == UINT32_C(4294836225) &&
        tile_area(0, 4) == 0);
}

static void test_sign_of(void) {
  CHECK(sign_of(INT_MIN) == -1 && sign_of(0) == 0 && sign_of(4) == 1);
}

static void test_leap_year(void) {
  CHECK(!leap_year(1900) && leap_year(2000) && !leap_year(2025));
}

static void test_fare(void) {
  CHECK(fare(5) == 0 && fare(6) == 2 && fare(17) == 2 && fare(18) == 5 &&
        fare(65) == 3);
}

static void test_middle(void) {
  CHECK(middle(INT_MAX, INT_MIN, 0) == 0 && middle(2, 1, 2) == 2 &&
        middle(8, 2, 1) == 2);
}

static void test_digit_sum(void) {
  CHECK(digit_sum(709) == 16 && digit_sum(0) == 0);
}

static void test_digit_count(void) {
  CHECK(digit_count(0) == 1 && digit_count(1000) == 4);
}

static void test_gcd_of(void) {
  CHECK(gcd_of(18, 12) == 6 && gcd_of(0, 0) == 0 && gcd_of(0, 5) == 5);
}

static void test_is_prime(void) {
  CHECK(is_prime(2) && is_prime(97) && !is_prime(1) && !is_prime(49));
}

static void test_negatives(void) {
  int a[] = {-1, 0, -9};
  CHECK(negatives(a, 3) == 2 && negatives(NULL, 0) == 0);
}

static void test_rises(void) {
  int a[] = {3, 4, 4, 6};
  CHECK(rises(a, 4) == 2 && rises(NULL, 0) == 0);
}

static void test_first_index(void) {
  int a[] = {3, 4, 3};
  CHECK(first_index(a, 3, 3) == 0 && first_index(a, 3, 9) == 3);
}

static void test_longest_run(void) {
  int a[] = {2, 2, 0, 2, 2, 2};
  CHECK(longest_run(a, 6, 2) == 3 && longest_run(NULL, 0, 9) == 0);
}

static void test_ascii_digit(void) {
  CHECK(ascii_digit(48) && ascii_digit(57) && !ascii_digit(58));
}

static void test_ascii_lower(void) {
  CHECK(ascii_lower(65) == 97 && ascii_lower(33) == 33);
}

static void test_byte_length(void) {
  CHECK(byte_length("") == 0 && byte_length("ab\0cd") == 2);
}

static void test_words(void) {
  CHECK(words("  a\tb c ") == 3 && words("  ") == 0);
}

static void test_point_total(void) {
  CHECK(point_total((Point){32767, 32767}) == 65534L &&
        point_total((Point){-4, 1}) == -3);
}

static void test_on_axis(void) {
  CHECK(on_axis((Point){0, 2}) && !on_axis((Point){3, 2}));
}

static void test_best_point(void) {
  Point p[] = {{0, 1}, {3, 3}, {5, 1}};
  CHECK(best_point(p, 3) == 1 && best_point(NULL, 0) == 0);
}

static void test_enclosed(void) {
  Point p[] = {{-2, 2}, {3, 0}, {0, 0}};
  CHECK(enclosed(p, 3, 2) == 2 && enclosed(p, 3, -1) == 0);
}

static void test_trail_report(void) {
  int16_t a[] = {4, 8, 3, 8};
  Trail t = trail_report(a, 4);
  CHECK(t.ascent == 9 && t.peak == 1);
  t = trail_report(NULL, 0);
  CHECK(!t.ascent && !t.peak);
}

static void test_meter_bill(void) {
  uint16_t a[] = {0, 5, 6, 20, 21};
  CHECK(meter_bill(a, 5) == 12 && meter_bill(NULL, 0) == 0);
}

static void test_reading_streak(void) {
  uint16_t a[] = {1, 5, 5, 0, 7, 8};
  Span s = reading_streak(a, 6, 5);
  CHECK(s.start == 1 && s.len == 2);
  s = reading_streak(a, 6, 10);
  CHECK(!s.len && !s.start);
}

static void test_safe_add(void) {
  unsigned x = 7;
  CHECK(!safe_add(UINT_MAX, 1, &x) && x == 7);
  CHECK(safe_add(2, 3, &x) && x == 5);
}

static void test_safe_mul(void) {
  unsigned x = 6;
  CHECK(!safe_mul(UINT_MAX, 2, &x) && x == 6);
  CHECK(safe_mul(UINT_MAX, 0, &x) && x == 0);
}

static void test_range_of(void) {
  int a = 4, b = 9, v[] = {5, -1, 5};
  CHECK(!range_of(NULL, 0, &a, &b) && a == 4 && b == 9);
  CHECK(range_of(v, 3, &a, &b) && a == -1 && b == 5);
}

static void test_div_parts(void) {
  unsigned q = 4, r = 5;
  CHECK(!div_parts(3, 0, &q, &r) && q == 4 && r == 5);
  CHECK(div_parts(17, 5, &q, &r) && q == 3 && r == 2);
}

static void test_copy_text(void) {
  char d[4] = "xy";
  CHECK(!copy_text(d, 3, "abc") && strcmp(d, "xy") == 0);
  CHECK(copy_text(d, 4, "abc") && !strcmp(d, "abc"));
}

static void test_reverse_ints(void) {
  int a[] = {1, 2, 3};
  reverse_ints(a, 3);
  CHECK(a[0] == 3 && a[1] == 2 && a[2] == 1);
  reverse_ints(NULL, 0);
}

static void test_compact(void) {
  int v[] = {1, 0, 2, 0};
  CHECK(compact(v, 4, 0) == 2 && v[0] == 1 && v[1] == 2);
}

static void test_erase_at(void) {
  int v[] = {1, 2, 3};
  CHECK(!erase_at(v, 3, 3) && v[1] == 2);
  CHECK(erase_at(v, 3, 0) && v[0] == 2 && v[1] == 3);
}

static void test_decimal_byte(void) {
  uint8_t x = 7;
  CHECK(!decimal_byte("256", &x) && x == 7);
  CHECK(!decimal_byte("", &x) && !decimal_byte("+2", &x));
  CHECK(decimal_byte("0255", &x) && x == 255);
}

static void test_hex_digit(void) {
  CHECK(hex_digit(70) == 15 && hex_digit(97) == 10 && hex_digit(71) == -1);
}

static void test_columns(void) {
  CHECK(columns("\ta\t") == 3 && columns("") == 1);
}

static void test_key_span(void) {
  size_t n = 9;
  CHECK(!key_span("=x", &n) && n == 9);
  CHECK(key_span("ab=x=y", &n) && n == 2);
}

static void test_lower_slot(void) {
  int v[] = {2, 3, 3, 8};
  CHECK(lower_slot(v, 4, 3) == 1 && lower_slot(v, 4, 9) == 4 &&
        lower_slot(NULL, 0, 2) == 0);
}

static void test_upper_slot(void) {
  int v[] = {2, 3, 3, 8};
  CHECK(upper_slot(v, 4, 3) == 3 && upper_slot(v, 4, 1) == 0);
}

static void test_insertion_sort(void) {
  int a[] = {2, 1, 3, 1};
  insertion_sort(a, 4);
  CHECK(a[0] == 1 && a[1] == 1 && a[2] == 2 && a[3] == 3);
}

static void test_unique_sorted(void) {
  int a[] = {1, 1, 1, 4, 4, 9};
  CHECK(unique_sorted(a, 6) == 3 && a[0] == 1 && a[1] == 4 && a[2] == 9);
}

static void test_count_if(void) {
  int a[] = {1, 4, 3}, k = 2;
  CHECK(count_if(a, 3, above, &k) == 2 && count_if(NULL, 0, above, &k) == 0);
}

static void test_first_if(void) {
  int a[] = {0, 1, 2}, calls = 0;
  CHECK(first_if(a, 3, observe, &calls) == 1 && calls == 2);
}

static void test_apply_each(void) {
  int a[] = {-2, 0, 3};
  apply_each(a, 3, positive);
  CHECK(a[0] == 0 && a[1] == 0 && a[2] == 1);
}

static void test_take_while(void) {
  int k = 1, a[] = {3, 2, 0, 4};
  CHECK(take_while(a, 4, above, &k) == 2 &&
        take_while(NULL, 0, above, &k) == 0);
}

static void test_first_byte(void) {
  FILE *f = stream("A");
  CHECK(first_byte(f) == 65 && first_byte(f) == EOF);
  fclose(f);
}

static void test_newlines(void) {
  FILE *f = stream("a\n\nb");
  CHECK(newlines(f) == 2);
  fclose(f);
}

static void test_emit_line(void) {
  FILE *f = stream("");
  CHECK(emit_line(f, "ok"));
  rewind(f);
  char b[8];
  CHECK(fgets(b, 8, f) && !strcmp(b, "ok\n"));
  fclose(f);
}

static void test_copy_stream(void) {
  FILE *f = stream("ab"), *o = stream("");
  CHECK(copy_stream(f, o));
  rewind(o);
  CHECK(fgetc(o) == 97 && fgetc(o) == 98 && fgetc(o) == EOF);
  fclose(o);
  fclose(f);
}

static void test_room_usage(void) {
  Slot v[] = {{20, 40}, {0, 30}};
  unsigned k = 7;
  CHECK(room_usage(v, 2, &k) && k == 40);
  v[1].end = 1441;
  CHECK(!room_usage(v, 2, &k) && k == 40);
}

static void test_grade_bins(void) {
  unsigned v[] = {59, 60, 79, 89, 90, 100};
  size_t b[5];
  CHECK(grade_bins(v, 6, b) && b[0] == 1 && b[1] == 1 && b[2] == 1 &&
        b[3] == 1 && b[4] == 2);
  v[5] = 101;
  CHECK(!grade_bins(v, 6, b) && b[4] == 2);
}

static void test_transcript(void) {
  FILE *i = stream("a\n\nb"), *o = stream("");
  CHECK(transcript(i, o));
  rewind(o);
  char b[20] = {0};
  CHECK(fread(b, 1, sizeof b - 1, o) == 10 && !strcmp(b, "1 a\n2 \n3 b"));
  fclose(i);
  fclose(o);
}

static void test_clone_values(void) {
  int a[] = {2, 8};
  int *p = clone_values(a, 2);
  CHECK(p && p != a && p[1] == 8);
  p[0] = 9;
  CHECK(a[0] == 2);
  free(p);
  CHECK(!clone_values(NULL, 0));
}

static void test_reserve_values(void) {
  Vector v = {0};
  CHECK(reserve_values(&v, 2) && v.cap >= 2);
  v.data[0] = 8;
  v.len = 1;
  CHECK(reserve_values(&v, 7) && v.data[0] == 8 && v.len == 1);
  free(v.data);
}

static void test_push_value(void) {
  Vector v = {0};
  for (int i = 0; i < 17; i++)
    CHECK(push_value(&v, i));
  CHECK(v.len == 17 && v.cap >= 17 && v.data[16] == 16 && v.data[0] == 0);
  free(v.data);
}

static void test_release_values(void) {
  Vector v = {malloc(sizeof(int)), 1, 1};
  release_values(&v);
  CHECK(!v.data && !v.len && !v.cap);
  release_values(&v);
}

static void test_list_len(void) {
  Node b = {2, NULL}, a = {1, &b};
  CHECK(list_len(&a) == 2 && list_len(NULL) == 0);
}

static void test_reverse_list(void) {
  Node b = {2, NULL}, a = {1, &b};
  CHECK(reverse_list(&a) == &b && b.next == &a && !a.next);
}

static void test_detach(void) {
  Node c = {2, NULL}, b = {2, &c}, a = {1, &b}, *h = &a;
  CHECK(detach(&h, 2) == &b && !b.next && a.next == &c);
  CHECK(detach(&h, 1) == &a && h == &c);
}

static void test_has_cycle(void) {
  Node b = {2, NULL}, a = {1, &b};
  CHECK(!has_cycle(&a));
  b.next = &a;
  CHECK(has_cycle(&a));
}

static void test_read_be16(void) {
  uint8_t p[] = {0xfe, 1};
  CHECK(read_be16(p) == 65025);
}

static void test_write_le32(void) {
  uint8_t p[4];
  write_le32(p, UINT32_C(0xaabbccdd));
  CHECK(p[0] == 0xdd && p[1] == 0xcc && p[2] == 0xbb && p[3] == 0xaa);
}

static void test_next_frame(void) {
  uint8_t b[] = {0, 1, 42, 8};
  Slice in = {b, 4}, out = {NULL, 0};
  CHECK(next_frame(&in, &out) && out.len == 1 && out.data[0] == 42 &&
        in.len == 1);
  CHECK(!next_frame(&in, &out) && in.data == b + 3 && out.len == 1);
}

static void test_check_byte(void) {
  uint8_t p[] = {255, 2};
  CHECK(check_byte(p, 2) == 255 && check_byte(NULL, 0) == 0);
}

static void test_ring_put(void) {
  Ring r = {.head = 7};
  CHECK(ring_put(&r, 4) && ring_put(&r, 5) && r.data[7] == 4 && r.data[0] == 5);
  r.len = 8;
  CHECK(!ring_put(&r, 9) && r.len == 8);
}

static void test_ring_get(void) {
  Ring r = {.head = 7, .len = 1};
  r.data[7] = 8;
  int x = 0;
  CHECK(ring_get(&r, &x) && x == 8 && r.head == 0);
  CHECK(!ring_get(&r, &x) && x == 8);
}

static void test_ring_at(void) {
  Ring r = {.head = 7, .len = 2};
  r.data[0] = 9;
  int x = 3;
  CHECK(ring_at(&r, 1, &x) && x == 9 && r.len == 2);
  CHECK(!ring_at(&r, SIZE_MAX, &x) && x == 9);
}

static void test_ring_drop(void) {
  Ring r = {.head = 6, .len = 4};
  CHECK(ring_drop(&r, 3) == 3 && r.head == 1 && r.len == 1);
  CHECK(ring_drop(&r, 99) == 1 && !r.len);
}

static void test_bit_member(void) {
  CHECK(bit_member(UINT32_MAX, 31) && !bit_member(UINT32_MAX, 32) &&
        !bit_member(2, 0));
}

static void test_bit_toggle(void) {
  uint32_t x = 0;
  CHECK(bit_toggle(&x, 31) && x == UINT32_C(0x80000000));
  CHECK(!bit_toggle(&x, 32) && x == UINT32_C(0x80000000));
}

static void test_population(void) {
  CHECK(population(UINT32_MAX) == 32 && population(0) == 0 &&
        population(9) == 2);
}

static void test_rotate_left(void) {
  CHECK(rotate_left(UINT32_C(0x80000001), 1) == 3 && rotate_left(5, 32) == 5);
}

static void test_debit(void) {
  unsigned b = 3;
  CHECK(!debit(&b, 4) && b == 3);
  CHECK(debit(&b, 3) && b == 0);
}

static void test_credit(void) {
  unsigned b = UINT_MAX - 1;
  CHECK(!credit(&b, 2) && b == UINT_MAX - 1);
  CHECK(credit(&b, 1) && b == UINT_MAX);
}

static void test_move_funds(void) {
  unsigned a[] = {7, 0};
  CHECK(move_funds(a, 2, (Move){0, 1, 4}) && a[0] == 3 && a[1] == 4);
  CHECK(!move_funds(a, 2, (Move){0, 0, 1}) && a[0] == 3);
}

static void test_settle_four(void) {
  unsigned a[] = {5, 0, 0, 0};
  Move m[] = {{0, 1, 3}, {1, 2, 4}};
  CHECK(!settle_four(a, m, 2) && a[0] == 5 && a[1] == 0);
  m[1].amount = 2;
  CHECK(settle_four(a, m, 2) && a[0] == 2 && a[1] == 1 && a[2] == 2);
}

static void test_inspect_capture(void) {
  uint8_t a[] = {0, 0, 0, 2, 3, 4};
  size_t k = 7;
  CHECK(inspect_capture((Slice){a, 6}, &k) && k == 2);
  CHECK(!inspect_capture((Slice){a, 5}, &k) && k == 2);
}

static void test_replay_recent(void) {
  int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, o[8];
  CHECK(replay_recent(a, 10, o) == 8 && o[0] == 2 && o[7] == 9);
  CHECK(!replay_recent(NULL, 0, o));
}

static void test_audit_stock(void) {
  unsigned a[] = {9, 0, 0, 0};
  size_t bad = 9;
  Move v[] = {{0, 1, 3}, {1, 2, 4}};
  CHECK(!audit_stock(a, v, 2, &bad) && bad == 1 && a[0] == 9 && a[1] == 0);
  CHECK(audit_stock(a, v, 1, &bad) && bad == 1 && a[0] == 6 && a[1] == 3);
}

int main(int argc, char **argv) {
  struct Case {
    const char *name;
    const char *level;
    void (*run)(void);
  };
  const struct Case cases[] = {
      {"whole_minutes", "basics", test_whole_minutes},
      {"clock_seconds", "basics", test_clock_seconds},
      {"billed_hours", "basics", test_billed_hours},
      {"tile_area", "basics", test_tile_area},
      {"sign_of", "basics", test_sign_of},
      {"leap_year", "basics", test_leap_year},
      {"fare", "basics", test_fare},
      {"middle", "basics", test_middle},
      {"digit_sum", "basics", test_digit_sum},
      {"digit_count", "basics", test_digit_count},
      {"gcd_of", "basics", test_gcd_of},
      {"is_prime", "basics", test_is_prime},
      {"negatives", "basics", test_negatives},
      {"rises", "basics", test_rises},
      {"first_index", "basics", test_first_index},
      {"longest_run", "basics", test_longest_run},
      {"ascii_digit", "basics", test_ascii_digit},
      {"ascii_lower", "basics", test_ascii_lower},
      {"byte_length", "basics", test_byte_length},
      {"words", "basics", test_words},
      {"point_total", "basics", test_point_total},
      {"on_axis", "basics", test_on_axis},
      {"best_point", "basics", test_best_point},
      {"enclosed", "basics", test_enclosed},
      {"trail_report", "basics", test_trail_report},
      {"meter_bill", "basics", test_meter_bill},
      {"reading_streak", "basics", test_reading_streak},
      {"safe_add", "intermediate", test_safe_add},
      {"safe_mul", "intermediate", test_safe_mul},
      {"range_of", "intermediate", test_range_of},
      {"div_parts", "intermediate", test_div_parts},
      {"copy_text", "intermediate", test_copy_text},
      {"reverse_ints", "intermediate", test_reverse_ints},
      {"compact", "intermediate", test_compact},
      {"erase_at", "intermediate", test_erase_at},
      {"decimal_byte", "intermediate", test_decimal_byte},
      {"hex_digit", "intermediate", test_hex_digit},
      {"columns", "intermediate", test_columns},
      {"key_span", "intermediate", test_key_span},
      {"lower_slot", "intermediate", test_lower_slot},
      {"upper_slot", "intermediate", test_upper_slot},
      {"insertion_sort", "intermediate", test_insertion_sort},
      {"unique_sorted", "intermediate", test_unique_sorted},
      {"count_if", "intermediate", test_count_if},
      {"first_if", "intermediate", test_first_if},
      {"apply_each", "intermediate", test_apply_each},
      {"take_while", "intermediate", test_take_while},
      {"first_byte", "intermediate", test_first_byte},
      {"newlines", "intermediate", test_newlines},
      {"emit_line", "intermediate", test_emit_line},
      {"copy_stream", "intermediate", test_copy_stream},
      {"room_usage", "intermediate", test_room_usage},
      {"grade_bins", "intermediate", test_grade_bins},
      {"transcript", "intermediate", test_transcript},
      {"clone_values", "advanced", test_clone_values},
      {"reserve_values", "advanced", test_reserve_values},
      {"push_value", "advanced", test_push_value},
      {"release_values", "advanced", test_release_values},
      {"list_len", "advanced", test_list_len},
      {"reverse_list", "advanced", test_reverse_list},
      {"detach", "advanced", test_detach},
      {"has_cycle", "advanced", test_has_cycle},
      {"read_be16", "advanced", test_read_be16},
      {"write_le32", "advanced", test_write_le32},
      {"next_frame", "advanced", test_next_frame},
      {"check_byte", "advanced", test_check_byte},
      {"ring_put", "advanced", test_ring_put},
      {"ring_get", "advanced", test_ring_get},
      {"ring_at", "advanced", test_ring_at},
      {"ring_drop", "advanced", test_ring_drop},
      {"bit_member", "advanced", test_bit_member},
      {"bit_toggle", "advanced", test_bit_toggle},
      {"population", "advanced", test_population},
      {"rotate_left", "advanced", test_rotate_left},
      {"debit", "advanced", test_debit},
      {"credit", "advanced", test_credit},
      {"move_funds", "advanced", test_move_funds},
      {"settle_four", "advanced", test_settle_four},
      {"inspect_capture", "advanced", test_inspect_capture},
      {"replay_recent", "advanced", test_replay_recent},
      {"audit_stock", "advanced", test_audit_stock}};
  size_t count = 0;
  for (size_t i = 0; i < sizeof cases / sizeof cases[0]; ++i) {
    if (argc > 1 && argv[1][0] && strcmp(argv[1], cases[i].name))
      continue;
    if (argc > 2 && argv[2][0] && strcmp(argv[2], cases[i].level))
      continue;
    cases[i].run();
    ++count;
  }
  if (!count) {
    fputs("No matching exercise\n", stderr);
    return 2;
  }
  printf("%zu checks passed\n", count);
  return 0;
}
