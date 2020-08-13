#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "wordlist.h"
#define MAX_LENGTH_PER_LINE 1000
typedef struct listnode {
	char url[MAX_URL_LENGTH];
	struct listnode* next;
}ListNode,*llist;

typedef struct node {
	char url[MAX_URL_LENGTH];
	int cnt;
	float pr;
	struct node* next;
}PRNode,*prnode;
llist insert_list_node(llist head, char* url);
llist prnode_to_list(prnode head);
prnode make_prnode(float pr, char* url);
int check_existence_of_url(prnode head, char* url);
prnode find_prnode_by_url(prnode head, char* url);
prnode insert_prnode(prnode head, float pr, char* url);
prnode readpr(prnode phead);
prnode insert_prnode_without_pr(prnode head, prnode nhead, char* url);
int main01(int argc,char*argv[]) {
	char* word[3] = { "mars","design","to" };
	int i = 0;
	int j = 3;
	wlist head = NULL;
	for (i;i < j;i++) {
		head = append_wordnode(head, word[i]);
	}
	wlist temp = head;
	prnode phead = NULL;
	phead = readpr(phead);
	/*for (phead;phead != NULL;phead = phead->next) {
		printf("%s %f\n", phead->url,phead->pr);
	}*/

	FILE* inverted = fopen("C:/Users/amosl/Desktop/invertedIndex.txt", "r");
	char line[MAX_LENGTH_PER_LINE];
	llist list1 = NULL;
	prnode list2 = NULL;
	while (temp != NULL) {
		int flag = 0;
		while (fgets(line, MAX_LENGTH_PER_LINE, inverted) != NULL) {
			char word[MAX_WORD_LENGTH];
			char delim[2] = " ";
			char* token;
			line[strlen(line) - 1] = '\0';
			token = strtok(line, delim);
			if (strcmp(token, temp->word) == 0) {
				while (token != NULL) {
					token = strtok(NULL, delim);
					//insert url list
					if ((token != NULL)&& !flag) {
						list1 = insert_list_node(list1, token);
						printf("--------%s \n",token);
					}
					if ((token != NULL) && check_existence_of_url(list1, token)) {
						list2 = insert_prnode_without_pr(phead, list2, token);
						printf("---%s \n", token);
					}
				}
				flag++;
				list1 = NULL;
				list1 = prnode_to_list(list2);
				if(temp->next!=NULL) list2 = NULL;
				temp = temp->next;
			}
		}
		
		
		printf("######%s\n", list1->url);
	}
	printf("######%s", list1->url);
	return 0;
}

llist insert_list_node(llist head, char* url) {
	if (head == NULL) {
		head = (llist)malloc(sizeof(ListNode));
		head->next = NULL;
		strcpy(head->url, url);
		return head;
	}
	llist new = (llist)malloc(sizeof(ListNode));
	new->next = head;
	strcpy(new->url, url);
	return new;
}

llist prnode_to_list(prnode head) {
	llist lhead = NULL;
	prnode temp = head;
	if (temp == NULL) {
		return NULL;
	}
	while (temp != NULL) {
		lhead = insert_list_node(lhead, temp->url);
		printf("******%s", temp->url);
		temp = temp->next;
	}
	return lhead;

}
prnode make_prnode(float pr, char* url) {
	prnode new = (prnode)malloc(sizeof(PRNode));
	if (new == NULL) return NULL;
	new->pr = pr;
	new->next = NULL;
	strcpy(new->url, url);
	return new;
}

int check_existence_of_url(llist head, char* url) {
	llist temp = head;
	if (temp == NULL) {
		return 1;
	}
	while (temp != NULL) {
		if (strcmp(temp->url, url) == 0) {
			return 1;
		}
		temp = temp->next;
	}
	return 0;
}
prnode find_prnode_by_url(prnode head, char* url) {
	prnode temp = head;
	while (temp != NULL) {
		if (strcmp(url, temp->url) == 0) {
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

//phead is the list read from pageranklist --- nhead is the list we use for finding the url
prnode insert_prnode_without_pr(prnode head, prnode nhead,char* url) {
	if (nhead == NULL) {
		prnode temp1 = find_prnode_by_url(head, url);//依然使用的是head中的节点
		prnode new = (prnode)malloc(sizeof(PRNode));
		new->pr = temp1->pr;
		new->next = NULL;
		strcpy(new->url, temp1->url);
		return new;
	}
	prnode temp = nhead;
	prnode temp1 = NULL;
	prnode temp2 = NULL;
	prnode new = find_prnode_by_url(head, url);
	prnode insert = (prnode)malloc(sizeof(PRNode));
	insert->pr = new->pr;
	insert->next = NULL;
	strcpy(insert->url, new->url);
	while (temp->next != NULL) {
		if ((insert->pr > temp->pr)&&(temp==nhead)){
			insert->next = temp;
			return insert;
		}
		else if ((insert->pr > temp->pr) && (temp != nhead)) {
			temp1->next = insert;
			insert->next = temp;
			return nhead;
		}
		else if(insert->pr == temp->pr) {
			if (strcmp(insert->url, temp->url) < 0) {
				temp1->next = insert;
				insert->next = temp;
				return nhead;
			}
			else if (strcmp(insert->url, temp->url) > 0) {
				temp2 = temp->next;
				temp->next = insert;
				insert->next = temp2;
				return nhead;
			}
			else {
				return nhead;
			}
		}
		temp1 = temp;
		temp = temp->next;
	}
	if ((insert->pr > temp->pr) && (temp == nhead)) {
		insert->next = temp;
		return insert;
	}
	else if ((insert->pr > temp->pr) && (temp != nhead)) {
		temp1->next = insert;
		insert->next = temp;
		return nhead;
	}
	else if (insert->pr == temp->pr) {
		if (strcmp(insert->url, temp->url) < 0) {
			temp1->next = insert;
			insert->next = temp;
			return nhead;
		}
		else {
			temp->next = insert;
			insert->next = NULL;
			return nhead;
		}
	}
	temp->next = insert;
	insert->next = NULL;
	return nhead;
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
		phead = insert_prnode(phead,pr, url);
	}
	fclose(pagerank);
	return phead;
}























