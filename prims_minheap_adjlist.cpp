/*
Problem:
Implementation of Prim's algorithm using minheap for edge selection by storing the graph in adjacency list.
*/

#include<iostream>
using namespace std;

struct adj_list_node {
    int value;
    int weight;
    struct adj_list_node* next;
};

struct adj_list_node* New_adj_list_node (int v,int w) {
	struct adj_list_node* new_node = (struct adj_list_node*) malloc(sizeof(adj_list_node));
	new_node->value=v;
	new_node->weight=w;
	new_node->next=NULL;
	return new_node;
}

struct adj_list_node* add_edge (struct adj_list_node* head,int val, int w) {
    struct adj_list_node* new_node = New_adj_list_node(val,w); 
    new_node->next = head;
    head = new_node;
    return new_node;
}

struct Min_Heap_Node {
    int sou,dest;     
    int weight;
};

struct Min_Heap_Node* New_Min_Heap_Node (int s,int d,int w) {
	struct Min_Heap_Node* min_heap_node = (struct Min_Heap_Node*) malloc(sizeof(struct Min_Heap_Node));
	min_heap_node->sou=s;
	min_heap_node->dest=d;
	min_heap_node->weight=w;
	return min_heap_node;
}

void Swap_Min_Heap_Nodes (struct Min_Heap_Node* p, struct Min_Heap_Node* q) {
	struct Min_Heap_Node tmp = *p;
	*p=*q;
	*q=tmp;
}

void Min_Heapify (struct Min_Heap_Node min_heap[],int size,int i) {
    int min=i,left=2*i+1,right=2*i+2;
    if(left<size && min_heap[i].weight>min_heap[left].weight) min=left;
    if(right<size && min_heap[min].weight>min_heap[right].weight) min=right;
    if(min!=i){
        Swap_Min_Heap_Nodes(&min_heap[min],&min_heap[i]);
        Min_Heapify(min_heap,size,min);
    }
}

struct Min_Heap_Node Delete_Min (struct Min_Heap_Node min_heap[], int size) {
    struct Min_Heap_Node min_node = min_heap[0];
    Swap_Min_Heap_Nodes(&min_heap[0],&min_heap[size-1]);
    size--;
    Min_Heapify(min_heap, size, 0);
    return min_node;
}

void Insert_Heap (struct Min_Heap_Node min_heap[],int size,struct Min_Heap_Node node) {
    min_heap[size] = node;
    int i = size;
    struct Min_Heap_Node temp;
    while (i >= 1) {
        if (min_heap[i/2].weight > min_heap[i].weight) {
 			Swap_Min_Heap_Nodes(&min_heap[i/2],&min_heap[i]);
            i = i / 2;
        } 
        else break;
    }
}

void PrimsMST (struct adj_list_node* adjacency_List[], int v_no, int e_no, int st_v, struct adj_list_node* Prims_MST[]) 
{
    int i,k,current = st_v, new_v;
    int visited[v_no + 1];

    struct adj_list_node* temp;
    struct Min_Heap_Node var,var2;
    struct Min_Heap_Node min_heap[2*e_no];
    int heapSize = 0;

    for (i=0;i<=v_no;i++) visited[i] = 0;
    i=0;
   	visited[current]=1;
    i++;

    temp = adjacency_List[current]; 

    while (temp != NULL) {
        var.sou = current;
        var.dest = temp->value;
        var.weight = temp->weight;   

        Insert_Heap(min_heap, heapSize, var);
        heapSize++;
        temp = temp->next;
    }

    while ((i <= v_no-1) && (heapSize != 0)) {

    	var = Delete_Min(min_heap, heapSize);
    	heapSize--;
 
        current = var.sou;
 		new_v = var.dest;

 		if (visited[new_v] == 0) {

            Prims_MST[current] = add_edge(Prims_MST[current], new_v, var.weight);
            Prims_MST[new_v] = add_edge(Prims_MST[new_v], current, var.weight);
            visited[new_v]=1;
            i++;
            temp = adjacency_List[new_v];
		    while ((temp != NULL)) {
		    	if(visited[temp->value] == 0){
		    		var2.sou = new_v;
        			var2.dest = temp->value;
        			var2.weight = temp->weight;   
        			Insert_Heap(min_heap, heapSize, var2);
        			heapSize++;
		    	}
		    	temp = temp->next;
    		}
        }
    }

    if(i < v_no) printf("Given Graph is not connected!\n");
}

int main() {
    
    int v_no,e_no,i,j,s,d,w,st_v,cost=0;

    printf("\nPlease enter the number of Vertices : ");
    scanf("%d", &v_no);
 
    printf("Please enter the number of Edges : ");
    scanf("%d", &e_no);

    struct adj_list_node* adjacency_List[v_no+1];
    struct adj_list_node* Prims_MST[v_no + 1];
 
    for (i=0;i<=v_no;i++) {
        adjacency_List[i] = NULL;
        Prims_MST[i] = NULL;
    }

    printf("\nPlease create the graph by entering the cost of edges of the graph : \n");

    for (i=1;i<=e_no;i++) {
    	printf("Please enter edge-%d [as source,destination,weight] : ",i);
        scanf("%d %d %d",&s,&d,&w);
        adjacency_List[s] = add_edge(adjacency_List[s],d,w);
        adjacency_List[d] = add_edge(adjacency_List[d],s,w);
    }

    printf("\nThe Given Graph [by Adjacency List] :\n\n");

    for (i=1;i<=v_no;i++) {
        printf("adjacency_List[%d] : ", i); 
        struct adj_list_node* node = adjacency_List[i]; 
        while (node != NULL) {
            printf("(Vertex-%d,weight-%d) -> ",node->value, node->weight);
            node = node->next;
        } 
        printf("NULL\n");
    }
 
    printf("\nEnter a Start Vertex to get Minimum Spanning Tree by Prim's Algorithm : ");
    scanf("%d", &st_v);

    PrimsMST(adjacency_List,v_no,e_no,st_v,Prims_MST);
 
    printf("\nThe resultant Minimum Spanning Tree by Prim's Algorithm is [by Adjacency List] :\n\n");

    for (i=1;i<=v_no;i++) {
        printf("Prims_MST[%d] : ", i); 
        struct adj_list_node* node = Prims_MST[i]; 
        while (node != NULL) {
            printf("(Vertex-%d,weight-%d) -> ",node->value, node->weight);
            cost+=node->weight;
            node = node->next;
        }
        printf("NULL\n");
    }

    printf("\nCost of Minimum Spanning Tree produced by Prim's Algorithm is : %d\n\n",cost/2);
    return 0;
}
