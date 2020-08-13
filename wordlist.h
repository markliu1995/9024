#ifndef _BSTREE_H
#define _BSTREE_H
#define MAX_WORD_LENGTH 100
#define MAX_URL_LENGTH  10

typedef struct WordList {
    char word[MAX_WORD_LENGTH];
    struct WordList* next;
}wordnode, * wlist;


wlist create_wordnode(char* word);
wlist append_wordnode(wlist whead, char* word);
void free_wordlist(wlist whead);
#endif