#ifndef _ALIGNMENT_H_
#define _ALIGNMENT_H_
#include "linkedlist.h"
void SW_alignment(list *list1, list *list2, int (*score)(char, char), int gap);
void bitap(list *list1, list *list2, int d, int ret[], int len);
#endif