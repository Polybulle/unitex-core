 /*
  * Unitex
  *
  * Copyright (C) 2001-2005 Universit� de Marne-la-Vall�e <unitex@univ-mlv.fr>
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

//---------------------------------------------------------------------------
#ifndef DictionaryTreeH
#define DictionaryTreeH
//---------------------------------------------------------------------------

#include "unicode.h"
#include "String_hash.h"
#include "Liste_nombres.h"


/**
 * This structure represents a node of a DELAF dictionary being loaded before
 * being compressed. In the first step, the dictionary is represented as a tree,
 * and then it is compressed into an acylic minimal automaton, using
 * Dominique Revuz's algorithm.
 */
struct dictionary_node {
	/*
	 * 'trans' is the list of the transitions outgoing from this node.
	 */
	struct dictionary_node_transition* trans;
	/*
	 * 'n_trans' stands for the number of transitions outgoing from this node. It is
	 * equivalent the size of the list 'trans', but it is cached for efficiency
	 * reasons.
	 */
	int n_trans;
	/*
	 * 'single_INF_code_list' is a list that contains the numbers of all the single
	 * INF codes that are associated with this node.
	 */
	struct liste_nombres* single_INF_code_list;
	/*
	 * 'INF_code' is a value representing the final INF line number associated
	 * with this dictionary node. This INF code correspond to the union of all
	 * the single INF codes of this node, separated with commas:
	 * 
	 * .DET:ms,.A:ms
	 */
	int INF_code;
	/*
	 * 'offset' is used to give to this node an adress in the .BIN file
	 */
	int offset;
};


/*
 * 
 */
struct dictionary_node_transition {
       unichar letter;
       struct dictionary_node* node;
       struct dictionary_node_transition* next;
};


void free_arbre_dico(struct dictionary_node*);
void free_arbre_dico_non_rec(struct dictionary_node*);
void free_arbre_dico_trans(struct dictionary_node_transition*);
void inserer_entree(unichar*,unichar*,struct dictionary_node*,struct string_hash*);
struct dictionary_node* new_arbre_dico();

#endif
