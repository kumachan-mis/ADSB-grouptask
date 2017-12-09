#include<stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

int main_prg(int, char**);

int main(int argc, char** argv){

  struct rusage u;
  struct timeval start, end;
  
  getrusage(RUSAGE_SELF, &u);
  start = u.ru_utime;
  
  main_prg(argc, argv);
  
  getrusage(RUSAGE_SELF, &u );
  end = u.ru_utime;
  
  fprintf(stderr, "%lf\n", (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)*1.0E-6);
    
  return(0);
}

int main_prg(int argc, char** argv){

  /** implement here  **/

  struct rusage u;
  struct timeval start, end;
  struct timeval start_sys, end_sys;
  
  getrusage(RUSAGE_SELF, &u);
  start = u.ru_utime;
  start_sys = u.ru_stime;

  double limit = 1.0;
  double t = 0.0;
  
  end_sys = u.ru_stime;
  fprintf(stderr, "%lf\n", (end_sys.tv_sec - start_sys.tv_sec) + (end_sys.tv_usec - start_sys.tv_usec)*1.0E-6);
  
  return(0);
}

