#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wordlist.h"




wlist create_wordnode(char* word) {
    wlist new = (wlist)malloc(sizeof(struct WordList));

    new->next = NULL;
    strcpy(new->word, word);

    return new;
}


wlist append_wordnode(wlist whead, char* word) {
    wlist temp_1 = whead;
    //if wordlist is empty
    if (whead == NULL) {
        wlist whead = create_wordnode(word);
        whead->next = NULL;
        return whead;
    }
    //check the existence of this word
    wlist temp_2 = NULL;
    while (temp_1->next != NULL) {
        if ((strcmp(word, temp_1->word) < 0) && (temp_1 == whead)) {
            wlist m = create_wordnode(word);
            m->next = whead;
            return m;
        }
        else if ((strcmp(word, temp_1->word) < 0) && (temp_1 != whead)) {
            wlist m = create_wordnode(word);
            temp_2->next = m;
            m->next = temp_1;
            return whead;
        }
        //the word is already in wordlist
        else if (strcmp(word, temp_1->word) == 0) {
            return whead;
        }
        temp_2 = temp_1;
        temp_1 = temp_1->next;
    }
    if (strcmp(word, temp_1->word) < 0) {
        wlist m = create_wordnode(word);
        if (temp_1 == whead) {
            m->next = whead;
            return m;
        }
        temp_2->next = m;
        m->next = temp_1;
        return whead;
    }
    else if (strcmp(word, temp_1->word) > 0) {
        wlist m = create_wordnode(word);
        temp_1->next = m;
        return whead;
    }
    else {
        return whead;
    }
}

void free_wordlist(wlist whead) {
    while (whead != NULL) {
        wlist temp1 = whead;
        whead = whead->next;
        free(temp1);
    }
}
