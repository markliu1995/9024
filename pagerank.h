#ifndef _PAGERANK_H
#define _PAGERANK_H
#define MAX_LENGTH 15

//each Url correspond to a vertice  
struct PRnode {
	char url[MAX_LENGTH];
	int vertice;
	struct PRnode* next;
	int outdegree;
	float PR;
	float prepr;
};
typedef struct PRnode* prnode;

int count_url_num();

// assign initial value :
//		PR=0.0
//		outdegree = 0
prnode initialise_prList(int num);

/*
	function: write PR,outdegree,Url 
	parameter: prnode phead
	return: success: 1
*/
int write_prlist(prnode phead);

/*
	function: get_prnode_by_vertice
	parameter: prnode phead, vertice
	return: prnode whose vertive equals to v
*/
prnode get_prnode_by_vertice(prnode phead, int v);

/*
	function: get_PR_vertice_by_url
	parameter: prnode phead, url
	return: vertice
*/
int get_PR_vertice_by_url(prnode phead, char* url_2);

/*
	function: create a graph through FILES
	parameter: number of vertice, prnode phead(prlist)
	return: graph
*/
Graph create_graph(int num, prnode phead);

/*
	function: calculate pagerank 
	parameter: 
	return: 
*/
void calculate_pr(prnode phead, Graph ghead, float d, float diffPR, int maxiterations, int num);

/*
	function: calculate pagerank
	parameter:
	return:
*/
//prnode mergeTwoLists(prnode l1, prnode l2);
//prnode mergeSortPrlist(prnode head);

/*
	function: free
	parameter:
	return:
*/
void free_prlist(prnode phead);

prnode sortPrList(prnode head);
//prnode sortList(prnode head);
//prnode merge(prnode l, prnode r);
#endif 


