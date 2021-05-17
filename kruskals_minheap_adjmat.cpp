/*
Problem:
Implementation of Krushkal's algorithm using minheap for edge selection by storing the graph in adjacency matrix.
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

void KruskalsMST (int adjacency_Mat[V][V], int v_no, int e_no, int Kruskals_MST[3][V]) 
{
    
    struct Min_Heap_Node min_heap[e_no];
    struct Min_Heap_Node var;
    struct adj_list_node* temp;
    int visited[v_no+1][v_no+1];
    int parent[v_no+1];

    for(int t=0;t<v_no+1;t++) parent[t]=-1;

    for(int t=0;t<v_no+1;t++)
        for(int z=0;z<v_no+1;z++)
            visited[t][z]=0;

    int current,j,i,k,new_v,mst=0,t,z;
    int heapSize=e_no;

    j=0;
    while(j < e_no){
        for(t=1;t<=v_no;t++){
            for(z=1;z<=v_no;z++){
                if(adjacency_Mat[t][z] != Inf){
                    var.sou = t;
                    var.dest = z;
                    var.weight = adjacency_Mat[t][z];
                    if(visited[var.sou][var.dest]==0){
                        min_heap[j]=var;
                        j++;
                        visited[var.sou][var.dest]=1;
                        visited[var.dest][var.sou]=1;
                    }
                }
            }
        }
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
            Kruskals_MST[0][mst]=current;
            Kruskals_MST[1][mst]=new_v;
            Kruskals_MST[2][mst]=var.weight;
            mst++;
            SetUnion(SetFind(current, parent), SetFind(new_v, parent), parent);
        }
    }

    if(i != v_no-1) printf("Given Graph is not connected!\n");
}

int main() {
    
    int v_no,e_no,i,j,s,d,w,st_v,cost=0;

    int adjacency_Mat[V][V], Kruskals_MST[3][V];

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

    KruskalsMST(adjacency_Mat,v_no,e_no,Kruskals_MST);

    printf("\nThe resultant Minimum Spanning Tree by Kruskal's Algorithm is [by Cost Adjacency matrix] :\n\n");

    for(i=0;i<v_no-1;i++){
            printf("The cost between edge-%d and edge-%d is : %d \n",Kruskals_MST[0][i],Kruskals_MST[1][i],Kruskals_MST[2][i]);
            cost+=Kruskals_MST[2][i];
    }

    printf("\nCost of Minimum Spanning Tree produced by Kruskal's Algorithm is : %d\n\n",cost);
    return 0;
}
