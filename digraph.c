#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "digraph.h"

Graph create_graph_node(int v) {
	Graph graphnode = malloc(sizeof(struct GraphNode));
	if (graphnode != NULL) {
		graphnode->vertice = v;
		graphnode->next = NULL;
		return graphnode;
	}
	return NULL;
}

Graph initialise_graph(int num) {
	int i = 2;
	Graph head = malloc(sizeof(struct GraphNode));
	Graph temp = head;
	head->next = NULL;
	head->vertice = 1;
	head->list = NULL;
	for (i;i <= num;i++) {

		Graph element = malloc(sizeof(struct GraphNode));
		element->vertice = i;
		element->list = NULL;
		element->next = NULL;
		temp->next = element;
		temp = temp->next;
	}
	return head;
}

Graph findGraphNodeByV(Graph graph, int v) {
	Graph temp = graph;
	while (graph->next != NULL) {
		if (temp->vertice == v) {
			return temp;
		}
		temp = temp->next;
	}
	//check whether v equals to last vertice
	if (temp->vertice == v) {
		return temp;
	}
	return NULL;
}

List insertList(List head, int w) {
	if (head == NULL) {
		List new = (struct node*)malloc(sizeof(struct node));
		new->data = w;
		new->next = NULL;
		return new;
	}
	List new = (struct node*)malloc(sizeof(struct node));
	new->data = w;
	new->next = head;
	return new;
}
void insert_edge(Graph head, int v, int w) {
	Graph target = findGraphNodeByV(head, v);
	// if(target==NULL){
	// 	return;
	// }
	if (target->list == NULL) {
		target->list = insertList(target->list, w);

		printf("				charuleyici    %d -- %d\n", w, v);

	}
	else {
		target->list = insertList(target->list, w);
		printf("				charuleyici    %d -- %d\n", w, v);

	}
}

void freegraph(Graph ghead) {
	while (ghead != NULL) {
		Graph temp = ghead;
		while (ghead->list != NULL) {
			List templ = ghead->list;
			ghead->list = ghead->list->next;
			free(templ);
		}
		ghead = ghead->next;
		free(temp);
	}
}
