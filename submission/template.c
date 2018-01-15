#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

#define maxTlen 105000
#define Snum 20000
#define Slen 25
#define RATE 1

int main_prg(int, char **);

int main(int argc, char **argv)
{

  struct rusage u;
  struct timeval start, end;

  getrusage(RUSAGE_SELF, &u);
  start = u.ru_utime;

  main_prg(argc, argv);

  getrusage(RUSAGE_SELF, &u);
  end = u.ru_utime;

  fprintf(stderr, "%lf\n", (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) * 1.0E-6);

  return (0);
}

int main_prg(int argc, char **argv)
{
  /** implement here  **/
  list *T = make_new_list();
  char Tstring[maxTlen + 1];
  list *S = make_new_list();
  char Sstring[Slen + 1];

  node *p;
  list *part = make_new_list();
  part->length = 20;

  scanf("%s", Tstring);

  const int Tlen = strlen(Tstring);
  T = insert_data(T, Tstring, -1);
  p = T->head;

  int i;
  int index = 0;

  for (i = 0; i < Snum / RATE; i++)
  {
    scanf("%s", Sstring);
    Sstring[20] = '\0';

    if (i == 0)
    {
      S = insert_data(S, Sstring, -1);
      S->length = 20;
    }
    else
    {
      S = replace_data(S, Sstring, 0);
    }

    for (index = 0; index < Tlen - Slen + 1; index++)
    {
      if (p == NULL)
        break;
      part->head = p;

      if (edit_distance(part, S, 2))
      {
        replace_data(T, Sstring, index);
        break;
      }
      p = p->next;
    }
    p = T->head;
  }
  show(T);

  struct rusage u;
  struct timeval start, end;
  struct timeval start_sys, end_sys;

  getrusage(RUSAGE_SELF, &u);
  start = u.ru_utime;
  start_sys = u.ru_stime;

  double limit = 1.0;
  double t = 0.0;

  end_sys = u.ru_stime;
  fprintf(stderr, "%lf\n", (end_sys.tv_sec - start_sys.tv_sec) + (end_sys.tv_usec - start_sys.tv_usec) * 1.0E-6);

  return (0);
}
