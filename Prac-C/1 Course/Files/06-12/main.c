#include <stdio.h>
#include <stdlib.h>

struct bohr_vrtx{
   int next_vrtx[k],pat_num;
   bool flag;
};

bohr_vrtx make_bohr_vrtx(){
   bohr_vrtx v;
   memset(v.next_vrtx, 255, sizeof(v.next_vrtx));
   v.flag=false;
   return v;
}
