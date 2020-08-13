#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "digraph.h"
#include "pagerank.h"
Graph create_graph(int num, prnode phead);
void calculate_pr(prnode phead, Graph ghead, float d, float diffPR, int maxiterations, int num);

int main(int argc, char* argv[]) {
	//assert(argc == 4);
	float d = 0.8; //atof(argv[1]); // damping factor
	float diffPR = 0.1; //atof(argv[2]); //- difference in PageRank sum
	int maxiterations = 100; //atoi(argv[3]); //maximum iterations
	int num = count_url_num();
	prnode pr = initialise_prList(num);

	Graph graph = create_graph(num, pr);
	while (graph != NULL) {
		printf("-------------\n");
		while (graph->list != NULL) {
			printf("jiedian %d\n", graph->list->data);
			graph->list = graph->list->next;
		}
		graph = graph->next;
	}
	calculate_pr(pr, graph, d, diffPR, maxiterations, num);
	sortPrList(pr);
	write_prlist(pr);

	freegraph(graph);
	free_prlist(pr);
	return 0;
}

//callculate the total number of Urls
int count_url_num() {
	int num = 0;
	char url[MAX_LENGTH];
	FILE* fp = fopen("C:/Users/amosl/Desktop/collection.txt", "r");
	while (fscanf(fp, "%s", url) != EOF) {
		num++;
	}
	fclose(fp);
	return num;
}

prnode initialise_prList(int num) {
	char url_1[MAX_LENGTH];
	int i = 2;
	prnode phead = (prnode)malloc(sizeof(struct PRnode));
	prnode temp = phead;
	FILE* fp = fopen("C:/Users/amosl/Desktop/collection.txt", "r");
	fscanf(fp, "%s", url_1);
	phead->next = NULL;
	phead->vertice = 1;
	phead->PR = 0.0;
	phead->prepr = 1.0 / num;
	phead->outdegree = 0;
	strcpy(phead->url, url_1);
	for (i;fscanf(fp, "%s", url_1) != EOF; i++) {
		prnode element = (prnode)malloc(sizeof(struct PRnode));
		element->vertice = i;
		element->outdegree = 0;
		phead->PR = 0.0;
		phead->prepr = 1.0 / num;
		strcpy(element->url, url_1);
		element->next = NULL;
		temp->next = element;
		temp = temp->next;
	}
	fclose(fp);
	return phead;
}

prnode get_prnode_by_vertice(prnode phead, int v) {
	prnode temp = phead;
	for (temp;temp != NULL;temp = temp->next) {
		if (temp->vertice == v) {
			return temp;
		}
	}
	return NULL;
}
int get_PR_vertice_by_url(prnode phead, char* url_2) {
	prnode temp = phead;
	for (temp;temp != NULL;temp = temp->next) {
		if (strcmp(temp->url, url_2) == 0) {
			return temp->vertice;
		}
	}
	return 0;
}

Graph create_graph(int num, prnode phead) {
	int i;
	Graph ghead = initialise_graph(num);
	prnode temp = phead;
	char path[15];
	char url[30];
	char* extension_name = ".txt";
	FILE* fp;
	int hash_count;
	for (temp;temp != NULL;temp = temp->next) {
		strcpy(path, temp->url);
		printf("@@diyihang %d  \n", temp->vertice);
		//strcat("C:/Users/amosl/Desktop/url11.txt" , extension_name);
		fp = fopen("C:/Users/amosl/Desktop/url11.txt", "r");
		hash_count = 0;
		while (fscanf(fp, "%s", url) != EOF) {
			if (url[0] == '#') {
				hash_count++;
				if (hash_count == 1) {
					fscanf(fp, "%s", url);
				}
				else {
					break;
				}
			}
			else {

				temp->outdegree++;
				i = get_PR_vertice_by_url(phead, url);
				printf("@@cunrude  %d \n ", i);
				insert_edge(ghead, i, temp->vertice);
			}
		}
		fclose(fp);
	}
	return ghead;
}

List find_graph_list_by_vertice(Graph head, int v) {
	Graph temp = head;
	while (temp != NULL) {
		if (temp->vertice == v) {
			return temp->list;
		}
		temp = temp->next;
	}
	return NULL;
}
void calculate_pr(prnode phead, Graph ghead, float d, float diffPR, int maxiterations, int num) {


	int iteration = 0;
	float diff = 0;
	float togetdiff;
	float pre_diff;
	while (iteration < maxiterations) {
		diff = 0;
		// temp -> prnode ||| temp_g -> Graph ||| templ->List
		prnode temp = phead;
		for (temp;temp != NULL;temp = temp->next) {
			temp->PR = 0;
			printf("__________________________vertice  %d\n", temp->vertice);
			List templ = find_graph_list_by_vertice(ghead, temp->vertice);
			while (templ != NULL) {
				// calculate PR
				printf("*************vertice  %d\n", templ->data);
				prnode transit = NULL;
				transit = get_prnode_by_vertice(phead, templ->data);
				temp->PR = temp->PR + d * (transit->prepr / transit->outdegree);
				printf("PR = %f\n", temp->PR);
				templ = templ->next;
			}
			temp->PR = temp->PR + (1 - d) / num;
			diff = diff + fabsf(temp->PR - temp->prepr);
			temp->prepr = temp->PR;

		}
		printf("iteration = %d\n", iteration);
		if (diff < diffPR) {
			break;
		}
		iteration++;
	}
}

prnode sortPrList(prnode head) {
	int flag = 1;
	prnode temp = head;
	while (flag) {
		flag = 0;
		for (temp;temp->next != NULL;temp = temp->next) {
			if (temp->PR < temp->next->PR) {
				flag = 1;
				float pr_temp = temp->PR;
				temp->PR = temp->next->PR;
				temp->next->PR = pr_temp;
				int outdegree_temp = temp->outdegree;
				temp->outdegree = temp->next->outdegree;
				temp->next->outdegree = outdegree_temp;
				char url_1[MAX_LENGTH];
				strcpy(url_1, temp->url);
				strcpy(temp->url, temp->next->url);
				strcpy(temp->next->url, url_1);


			}
		}
		temp = head;
	}
	return head;
}



int write_prlist(prnode phead) {
	prnode temp = phead;
	FILE* fp = fopen("C:/Users/amosl/Desktop/pagerankList.txt", "w");
	while (temp != NULL) {
		fprintf(fp, "%s, %d, %.7f\n", temp->url, temp->outdegree, temp->PR);
		temp = temp->next;
	}
	fclose(fp);
	return 1;
}

void free_prlist(prnode phead) {
	while (phead != NULL) {
		prnode temp = phead;
		phead = phead->next;
		free(temp);
	}
}