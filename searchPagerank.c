#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "wordlist.h"
#define MAX_LENGTH_PER_LINE 1000

typedef struct node {
	char url[MAX_URL_LENGTH];
	int cnt;
	float pr;
	struct node* next;
}PRNode, * prnode;
prnode make_prnode(float pr, char* url);
prnode insert_prnode(prnode head, float pr, char* url);
prnode readpr(prnode phead);
prnode find_prnode_by_url(prnode head, char* url);
prnode insert_prnode_to_list(prnode head, prnode nhead, char* url);
prnode sort_pr_list(prnode head);
void print_list(prnode head);
void free_list(prnode head);
int main(int argc, char* argv[]) {
	char* word[3] = { "mars","design","to" };
	int i = 0;
	int j = 3;

	wlist head = NULL;
	for (i;i < j;i++) {
		head = append_wordnode(head, word[i]);
	}
	wlist temp = head;
	prnode phead = readpr(head);
	prnode list = NULL;
	prnode exist  = NULL;
	FILE* inverted = fopen("C:/Users/amosl/Desktop/invertedIndex.txt", "r");
	char line[MAX_LENGTH_PER_LINE];
	while (temp != NULL) {
		int flag = 0;
		while (fgets(line, MAX_LENGTH_PER_LINE, inverted) != NULL) {
			char word[MAX_WORD_LENGTH];
			char delim[2] = " ";
			char* token;
			line[strlen(line) - 1] = '\0';
			token = strtok(line, delim);
			if (temp == NULL) break;
			if (strcmp(token, temp->word) == 0) {
				while (token != NULL) {
					token = strtok(NULL, delim);
					//insert url list
					exist = find_prnode_by_url(list, token);
					if ((token!=NULL)&&(exist!= NULL)) {
						exist->cnt++;
					}
					else if((token != NULL) && (exist == NULL)){
						list = insert_prnode_to_list(phead, list, token);
					}
				}
				temp = temp->next;
			}
		}
	}
	list = sort_pr_list(list);
	print_list(list);
	free_list(head);
	free_list(phead);
}


prnode find_prnode_by_url(prnode head, char* url) {
	if (head == NULL) return NULL;
	if (url == NULL) return NULL;
	prnode temp = head;
	while (temp != NULL) {
		if (strcmp(url, temp->url) == 0) {
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}


prnode insert_prnode_to_list(prnode head, prnode nhead, char* url) {
	prnode m = nhead;
	if (nhead == NULL) {
		prnode temp1 = find_prnode_by_url(head, url);//依然使用的是head中的节点
		prnode new = (prnode)malloc(sizeof(PRNode));
		new->pr = temp1->pr;
		new->next = NULL;
		new->cnt = 0;
		strcpy(new->url, temp1->url);
		return new;
	}
	prnode new = find_prnode_by_url(head, url);
	prnode insert = (prnode)malloc(sizeof(PRNode));
	insert->pr = new->pr;
	insert->cnt = 0;
	insert->next = NULL;
	strcpy(insert->url, new->url);
	while (m->next != NULL) {
		m = m->next;
	}
	m->next = insert;
	return nhead;
}

prnode make_prnode(float pr, char* url) {
	prnode new = (prnode)malloc(sizeof(PRNode));
	if (new == NULL) return NULL;
	new->pr = pr;
	new->next = NULL;
	strcpy(new->url, url);
	new->cnt = 0;
	return new;
}
prnode insert_prnode(prnode head, float pr, char* url) {
	if (head == NULL) {
		prnode head = make_prnode(pr, url);
		return head;
	}
	prnode new = make_prnode(pr, url);
	new->next = head;
	return new;
}

prnode readpr(prnode phead) {
	char* line[MAX_LENGTH_PER_LINE];
	char* token;
	char delim[3] = ", ";
	FILE* pagerank = fopen("C:/Users/amosl/Desktop/pagerankList.txt", "r");
	while (fgets(line, MAX_LENGTH_PER_LINE, pagerank) != NULL) {
		token = strtok(line, delim);
		int cnt = 0;
		float pr = 0.0;
		char url[MAX_URL_LENGTH];
		while (token != NULL) {
			cnt++;
			if (cnt == 1) {
				strcpy(url, token);
			}
			else if (cnt == 3) {
				pr = atof(token);
			}
			token = strtok(NULL, delim);
		}
		phead = insert_prnode(phead, pr, url);
	}
	fclose(pagerank);
	return phead;
}

prnode sort_pr_list(prnode head) {
	int flag = 1;
	prnode temp = head;
	while (flag) {
		flag = 0;
		for (temp;temp->next != NULL;temp = temp->next) {
			if (temp->cnt < temp->next->cnt) {
				flag = 1;
				float pr_temp = temp->pr;
				temp->pr = temp->next->pr;
				temp->next->pr = pr_temp;
				int outdegree_temp = temp->cnt;
				temp->cnt = temp->next->cnt;
				temp->next->cnt = outdegree_temp;
				char url_1[MAX_URL_LENGTH];
				strcpy(url_1, temp->url);
				strcpy(temp->url, temp->next->url);
				strcpy(temp->next->url, url_1);
			}
			if ((temp->cnt == temp->next->cnt) && (temp->pr < temp->next->pr)) {
				flag = 1;
				float pr_temp = temp->pr;
				temp->pr = temp->next->pr;
				temp->next->pr = pr_temp;
				int outdegree_temp = temp->cnt;
				temp->cnt = temp->next->cnt;
				temp->next->cnt = outdegree_temp;
				char url_1[MAX_URL_LENGTH];
				strcpy(url_1, temp->url);
				strcpy(temp->url, temp->next->url);
				strcpy(temp->next->url, url_1);
			}
		}
		temp = head;
	}
	return head;
}
void print_list(prnode head) {
	prnode temp = head;
	while (temp != NULL) {
		printf("%s\n", temp->url);
		temp = temp->next;
	}
}

void free_list(prnode head) {
	while (head->next != NULL) {
		prnode temp = head;
		head = head->next;
		free(temp);
	}
	free(head);


}