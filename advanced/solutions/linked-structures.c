#include "course.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

size_t list_len(const Node *head) {
  size_t n = 0;
  for (; head; head = head->next)
    ++n;
  return n;
}

Node *reverse_list(Node *head) {
  Node *prev = NULL;
  while (head) {
    Node *next = head->next;
    head->next = prev;
    prev = head;
    head = next;
  }
  return prev;
}

Node *detach(Node **head, int key) {
  while (*head && (*head)->value != key)
    head = &(*head)->next;
  if (!*head)
    return NULL;
  Node *p = *head;
  *head = p->next;
  p->next = NULL;
  return p;
}

bool has_cycle(const Node *head) {
  const Node *slow = head, *fast = head;
  while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
    if (slow == fast)
      return true;
  }
  return false;
}
