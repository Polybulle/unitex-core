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
#include <string.h>
#include <stdlib.h>
#include "IOBuffer.h"
#include "Pattern.h"
#include "PatternTree.h"
#include "Unicode.h"
#include "String_hash.h"
#include "DELA.h"
#include "List_pointer.h"
#include "StringParsing.h"
#include "Copyright.h"
#include "Fst2.h"
#include "Error.h"
#include "Tfst.h"

/**
 * This program is designed for test purpose only.
 */
int main(int argc,char *argv[]) {
setBufferMode();

Tfst* t=open_text_automaton("D:\\My Unitex\\French\\Corpus\\test_snt\\text.tfst");
load_sentence(t,2);
close_text_automaton(t);

return 0;
}



