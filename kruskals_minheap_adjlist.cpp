/*
Problem:
Implementation of Krushkal's algorithm using minheap for edge selection by storing the graph in adjacency list.
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

void Create_Heap(struct Min_Heap_Node min_heap[], int size) {
    int i;
    for(i=(size/2)-1;i>=0;i--)
        Min_Heapify(min_heap,size,i);
}

int SetFind(int u, int s[]){
    int x=u,temp=0; 
    while (s[x] > 0){
        x = s[x];
    }

    while (u != x){
        temp = s[u];
        s[u] = x;
        u = temp;
    }
    return x;
}

void SetUnion(int u, int v, int s[]){
    if (s[u] < s[v]){
        s[u] += s[v];
        s[v] = u;
    } 
    else {
        s[v] += s[u];
        s[u] = v;
    }
}

void KruskalsMST (struct adj_list_node* adjacency_List[], int v_no, int e_no, struct adj_list_node* Kruskals_MST[]) 
{
    
    struct Min_Heap_Node min_heap[e_no];
    struct Min_Heap_Node var;
    struct adj_list_node* temp;
    int visited[v_no+1][v_no+1]={0};
    int parent[v_no+1];

    for(int t=0;t<v_no+1;t++) parent[t]=-1;

    for(int t=0;t<v_no+1;t++)
        for(int z=0;z<v_no+1;z++)
            visited[t][z]=0;

    int current,j,i,k,new_v;
    int heapSize=e_no;

    current=1;

    j=0;
    while(j < e_no){
        temp = adjacency_List[current];
        while (temp != NULL) {
            var.sou = current;
            var.dest = temp->value;
            var.weight = temp->weight;
            if(visited[var.sou][var.dest]==0){
                min_heap[j]=var;
                j++;
                visited[var.sou][var.dest]=1;
                visited[var.dest][var.sou]=1;
            }
            temp = temp->next;
        }
        current++;
    }

    Create_Heap(min_heap,e_no);

    i=0;
    heapSize = e_no;

    while ((i < v_no-1) && (heapSize != 0)) {

    	var = Delete_Min(min_heap, heapSize);
    	heapSize--;

        current = var.sou;
        new_v = var.dest;

        if (SetFind(current, parent) != SetFind(new_v, parent)) {
            i++;
            Kruskals_MST[current] = add_edge(Kruskals_MST[current], new_v, var.weight);
            Kruskals_MST[new_v] = add_edge(Kruskals_MST[new_v], current, var.weight);
            SetUnion(SetFind(current, parent), SetFind(new_v, parent), parent);
        }
    }

    if(i != v_no-1) printf("Given Graph is not connected!\n");
}

int main() {
    
    int v_no,e_no,i,j,s,d,w,st_v,cost=0;

    printf("\nPlease enter the number of Vertices : ");
    scanf("%d", &v_no);
 
    printf("Please enter the number of Edges : ");
    scanf("%d", &e_no);

    struct adj_list_node* adjacency_List[v_no+1];
    struct adj_list_node* Kruskals_MST[v_no + 1];
 
    for (i=0;i<=v_no;i++) {
        adjacency_List[i] = NULL;
        Kruskals_MST[i] = NULL;
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

    KruskalsMST(adjacency_List,v_no,e_no,Kruskals_MST);
 
    printf("\nThe resultant Minimum Spanning Tree by Kruskal's Algorithm is [by Adjacency List] :\n\n");

    for (i=1;i<=v_no;i++) {
        printf("Kruskals_MST[%d] : ", i); 
        struct adj_list_node* node = Kruskals_MST[i]; 
        while (node != NULL) {
            printf("(Vertex-%d,weight-%d) -> ",node->value, node->weight);
            cost+=node->weight;
            node = node->next;
        }
        printf("NULL\n");
    }

    printf("\nCost of Minimum Spanning Tree produced by Kruskal's Algorithm is : %d\n\n",cost/2);
    return 0;
}
