#ifndef _BSTREE_H
#define _BSTREE_H
#define MAX_WORD_LENGTH 20
#define MAX_URL_LENGTH  10


typedef struct UrlList {
    char url[MAX_URL_LENGTH];
    struct UrlList* next;
}listnode, *ulist;


typedef struct WordList {
    ulist list;
    char word[MAX_WORD_LENGTH];
    struct WordList* next;

}wordnode,*wlist;

ulist add_listnode(ulist uhead, char* url);
wlist create_wordnode(char* word, char* url);
//wlist initialise_wlist();
//wlist check_word(wlist whead, char* word);
wlist append_wordnode(wlist whead, char* word, char* url);
void free_strlist(wlist whead);
#endif
