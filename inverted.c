#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "strlist.h"

wlist create_word_url_list();
char* nomalise(char* word);
void write_inverted(wlist whead);

int main() {
	
	wlist head = create_word_url_list();
	/*while (head != NULL) {
		printf("%s\n", head->word);
		while (head->list != NULL) {
			printf("%s ", head->list->url);
			head->list = head->list->next;
		}
		printf("\n");
		head = head->next;
	}*/
	write_inverted(head);
	free_strlist(head);
}

char* nomalise(char* word) {
	int i = 0;
	while (word[i] != '\0') {
		word[i] = tolower(word[i]);
		i++;
	}
	i--;
	while ((word[i] == ',') || (word[i] == '.') || (word[i] == ';') || (word[i] == '?')) {
		word[i] = '\0';
		i--;
	}
	return word;
}

wlist create_word_url_list() {
	wlist whead = NULL;
	FILE* collection = fopen("C:/Users/amosl/Desktop/collection.txt", "r");
	char filename[MAX_URL_LENGTH];
	char* extension = ".txt";
	char word[MAX_WORD_LENGTH];
	while (fscanf(collection, "%s", filename) != EOF) {
		char temp[MAX_URL_LENGTH];
		strcpy(temp, filename);
		strcat(filename, extension);
		int hashcount = 0;
		FILE* url = fopen("C:/Users/amosl/Desktop/url11.txt", "r");
		
		while (fscanf(url, "%s", word) != EOF) {
			if (word[0] == '#') {
				hashcount++;
				if (hashcount == 3) {
					fscanf(url, "%s", word);
				}
				if (hashcount == 4) {
					break;
				}
			}
			else {
				if (hashcount == 3) {
					char* word_1 = nomalise(word);
					whead = append_wordnode(whead, word_1, temp);
				}
			}
		}
		fclose(url);
	}
	fclose(collection);
	return whead;
}

void write_inverted(wlist whead) {
	FILE* fp = fopen("C:/Users/amosl/Desktop/invertedIndex.txt", "w");
	wlist temp = whead;
	while (temp != NULL) {
		fprintf(fp, "%s ", temp->word);
		ulist temp1 = temp->list;
		while (temp1 != NULL) {
			fprintf(fp, "%s ", temp1->url);
			temp1 = temp1->next;
		}
		fprintf(fp, "\n");
		temp = temp->next;
	}
}