#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strlist.h"


//in ascending order
ulist add_listnode(ulist uhead,char*url) {
    ulist temp = uhead;
    if (temp == NULL) {
        ulist uhead = (ulist)malloc(sizeof(struct UrlList));
        uhead->next = NULL;
        strcpy(uhead->url, url);
        return uhead;
    }
    else {
        ulist utemp = (ulist)malloc(sizeof(struct UrlList));
        ulist temp_1 = NULL;
        while (temp->next != NULL) {
            if ((strcmp(url, temp->url) < 0) && (temp == uhead)) {
                strcpy(utemp->url, url);
                utemp->next = uhead;
                return utemp;
            }
            else if ((strcmp(url, temp->url) < 0) && (temp != uhead)) {
                strcpy(utemp->url, url);
                temp_1->next = utemp;
                utemp->next = temp;
                return uhead;
            }
            else if (strcmp(url, temp->url) == 0) {
                return uhead;
            }
            temp_1 = temp;
            temp = temp->next;
        }
        if (strcmp(url, temp->url) < 0) {
            strcpy(utemp->url, url);
            if (temp == uhead) {
                utemp->next = uhead;
                return utemp;
            }
            temp_1->next = utemp;
            utemp->next = temp;
            return uhead;
        }
        else if (strcmp(url, temp->url) == 0) {
            return uhead;
        }
        else {
            strcpy(utemp->url, url);
            temp->next = utemp;
            utemp->next = NULL;
            return uhead;
        }
    }
}

wlist create_wordnode(char*word,char*url) {
    wlist new = (wlist)malloc(sizeof(struct WordList));
    new->list = (ulist)malloc(sizeof(struct UrlList));
    new->list->next = NULL;
    new->next = NULL;
    strcpy(new->word, word);
    strcpy(new->list->url, url);
    return new;
}

// in ascending order
wlist append_wordnode(wlist whead,char*word,char*url) {
    wlist temp_1 = whead;
    //if wordlist is empty
    if (whead == NULL) {
        wlist whead = create_wordnode(word, url);
        whead->next = NULL;
        return whead;
    }
    //check the existence of this word
    wlist temp_2 = NULL;
    while (temp_1->next != NULL) {
        if ((strcmp(word, temp_1->word) < 0)&&(temp_1 == whead)) {
            wlist m = create_wordnode(word, url);
            m->next = whead;
            return m;
        }
        else if ((strcmp(word, temp_1->word) < 0) && (temp_1 != whead)) {
            wlist m = create_wordnode(word, url);
            temp_2->next = m;
            m->next = temp_1;
            return whead;
        }
        //the word is already in wordlist
        else if (strcmp(word, temp_1->word) == 0) {
            add_listnode(temp_1->list, url);
            return whead;
        }
        temp_2 = temp_1;
        temp_1 = temp_1->next;
    }
    if (strcmp(word, temp_1->word) < 0) {
        wlist m = create_wordnode(word, url);
        if (temp_1 == whead) {
            m->next = whead;
            return m;
        }
        temp_2->next = m;
        m->next = temp_1;
        return whead;
    }
    else if (strcmp(word, temp_1->word) > 0) {
        wlist m = create_wordnode(word, url);
        temp_1->next = m;
        return whead;
    }
    else {
        add_listnode(temp_1->list, url);
        return whead;
    }     
}
    
void free_strlist(wlist whead) {
    while (whead != NULL) {
        wlist temp1 = whead;
        while (whead->list != NULL) {
            ulist temp2 = whead->list;
            whead->list = whead->list->next;
            free(temp2);
        }
        whead = whead->next;
        free(temp1);
    }
}








