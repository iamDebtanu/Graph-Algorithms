/*
Problem:
Implement Prim's algorithm using minheap for edge selection by storing the graph in adjacency matrix.
*/

#include<iostream>
using namespace std;
#define Inf 32767
#define V 100

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

void PrimsMST (int adjacency_Mat[V][V], int v_no, int e_no, int st_v, int Prims_MST[3][V]) 
{
    int i,k,mst=0,current=st_v,new_v,vtx,visited[v_no+1],heapSize=0;

    struct Min_Heap_Node var,var2;
    struct Min_Heap_Node min_heap[2*e_no];

    for (i=1;i<=v_no;i++) visited[i] = 0;

    i=0;
   	visited[current]=1;
    i++;

    for(vtx=1;vtx<=v_no;vtx++){
        if(adjacency_Mat[current][vtx] != Inf){
            var.sou = current;
            var.dest = vtx;
            var.weight = adjacency_Mat[current][vtx];
            Insert_Heap(min_heap, heapSize, var);
            heapSize++;
        }
    }

    while ((i <= v_no-1) && (heapSize != 0)) {

    	var = Delete_Min(min_heap, heapSize);
    	heapSize--;
 
        current = var.sou;
 		new_v = var.dest;

 		if (visited[new_v] == 0) {

            Prims_MST[0][mst]=current;
            Prims_MST[1][mst]=new_v;
            Prims_MST[2][mst]=var.weight;
            mst++;
            visited[new_v]=1;
            i++;

            for(vtx=1;vtx<=v_no;vtx++){
                if(visited[vtx]==0){
                    if(adjacency_Mat[new_v][vtx]!=Inf){
                        var2.sou = new_v;
                        var2.dest = vtx;
                        var2.weight = adjacency_Mat[new_v][vtx];   
                        Insert_Heap(min_heap, heapSize, var2);
                        heapSize++;
                    }
                }
            }
        }
    }

    if(i < v_no) printf("\nGiven Graph is not connected!\n");
}

int main() {

    int v_no,e_no,i,j,s,d,w,st_v,cost=0;

    int adjacency_Mat[V][V], Prims_MST[3][V];

    printf("\nPlease enter the number of Vertices : ");
    scanf("%d", &v_no);

    printf("Please enter the number of Edges : ");
    scanf("%d", &e_no);

    for(i=1;i<=v_no;i++){
        for(j=i;j<=v_no;j++){
            adjacency_Mat[i][j]=Inf;
            adjacency_Mat[j][i]=Inf;
        }
    }

    printf("\nPlease create the graph by entering the cost of edges of the graph : \n");

    for (i=1;i<=e_no;i++) {
        printf("Please enter edge-%d [as source,destination,weight] : ",i);
        scanf("%d %d %d",&s,&d,&w);
        adjacency_Mat[s][d]=w;
        adjacency_Mat[d][s]=w;
    }

    printf("\nThe Given Graph [by Cost Adjacency matrix] :\n\n");

    for(i=1;i<=v_no;i++){
        for(j=i;j<=v_no;j++){
            if(adjacency_Mat[i][j] != Inf){
                printf("The cost between edge-%d and edge-%d is : %d \n",i,j,adjacency_Mat[i][j]);
            }
        }
    }
 
    printf("\nEnter a Start Vertex to get Minimum Spanning Tree by Prim's Algorithm : ");
    scanf("%d", &st_v);

    PrimsMST(adjacency_Mat,v_no,e_no,st_v,Prims_MST);
 
    printf("\nThe resultant Minimum Spanning Tree by Prim's Algorithm is [by Cost Adjacency matrix] :\n\n");

    for(i=0;i<v_no-1;i++){
            printf("The cost between edge-%d and edge-%d is : %d \n",Prims_MST[0][i],Prims_MST[1][i],Prims_MST[2][i]);
            cost+=Prims_MST[2][i];
    }

    printf("\nCost of Minimum Spanning Tree produced by Prim's Algorithm is : %d\n\n",cost);
    return 0;
}
