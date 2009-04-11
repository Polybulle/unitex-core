 /*
  * Unitex
  *
  * Copyright (C) 2001-2009 Universit� Paris-Est Marne-la-Vall�e <unitex@univ-mlv.fr>
  *
  * This library is free software; you can redistribute it and/or
  * modify it under the terms of the GNU Lesser General Public
  * License as published by the Free Software Foundation; either
  * version 2.1 of the License, or (at your option) any later version.
  *
  * This library is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  * Lesser General Public License for more details.
  * 
  * You should have received a copy of the GNU Lesser General Public
  * License along with this library; if not, write to the Free Software
  * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
  *
  */

#include <stdio.h>
#include <stdlib.h>
#include "IOBuffer.h"
#include "Unicode.h"
#include "Reg2Grf.h"
#include "Locate.h"
#include "ProgramInvoker.h"
#include "regex.h"

/**
 * This program is an example of compilation using the unitex library (unitex.dll/libunitex.so).
 * It prints the .grf file corresponding to "a+(b.c)".
 */
int main(int argc,char *argv[]) {
setBufferMode();

char* name="biniou";
FILE* f=u_fopen("biniou",U_WRITE);
if (f==NULL) {
   fatal_error("Cannot open %s\n",name);
}
u_fprintf(f,"a+(b.c)");
u_fclose(f);
char* grf="regexp.grf";
ProgramInvoker* invoker=new_ProgramInvoker(main_Reg2Grf,"main_Reg2Grf");
add_argument(invoker,name);
int ret=invoke(invoker);
free_ProgramInvoker(invoker);
u_printf("Reg2Grf exit code: %d\n\n",ret);

f=u_fopen(grf,U_READ);
int c;
while ((c=u_fgetc(f))!=-1) {
   u_printf("%C",c);
}
u_fclose(f);
remove(name);
remove(grf);

/* These lines are just here to test if the TRE library was correctly linked. */
wchar_t warray[512];
regex_t matcher;
regwcomp(&matcher,warray,REG_NOSUB);
return 0;
}



