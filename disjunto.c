#include <stdio.h>

int find(int parent[], int i)
{
    while (parent [i] !=i)
        i=parent[i];
    return i;
}

void Union(int parent[], int i, int j)
{
    int x = find(parent,i);
    int y = find(parent,j);
    parent[y]=x;
}

int main(){
    int parent[8];
    for(int i=0; i<8; i++)
        parent[i]=i;
    Union(parent, 2,4);
    Union(parent,4,5);
    for(int i = 0; i<8;i++)
        printf("%d ", parent[i]);
    printf("\n");
}