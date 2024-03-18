#include <stdio.h>
#include <stdlib.h>

typedef int * image;

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

int in[] = {
    0,0,0,0,0,0,0,0,
    0,1,1,1,0,0,0,0,
    0,1,1,1,0,0,0,0,
    0,0,1,0,0,1,0,0,
    0,0,0,0,1,1,1,0,
    0,0,0,0,0,1,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
};

image rotula (image in){
    int w = 8, h=8;
    int rotulo = 0;
    image out = (image)malloc(64*sizeof(int));
    int parent[1000];
    for(int i = 0; i<1000; i++)
        parent[i] = i;
    for (int i = 1; i<h-1;i++)
        for(int j = 1; j<w;j++)
    {
        int r = in[(i-1)*w+j];
        int t = in[i*w+j-1];
        int p = in[i*w+j];
        if (p ==1){
            if(r==0 && t==0) out[i*w+j]= ++rotulo;
            if(r==1 && t==0) out[i*w+j]= out[(i-1)*w+j];
            if(r==0 && t==1) out[i*w+j]= out[(i*w+j-1)];
            if(r==1 && t==1){ 
                if (out[(i-1)*w+j] != out[i*w+j-1]){
                    out[i*w+j]= out[i*w+j-1];
                    printf("Rotulos equivalentes: %d, %d\n", out[(i-1)*w+j], out[i*w+j-1]);
                    Union(parent,out[(i-1)*w+j], out[i*w+j-1]);
                }
                else
                    out[i*w+j]=out[i*w+j-1];
            }
        }
        for(int i =0;i<w*h;i++)
            out[i]=find(parent,out[i]);
    }return out;
}

void mostra(image img){
    for (int i = 0; i < 8; i++)
        for(int j=0;j<8;j++)
            printf("%4d ",img[i*8+j]);
        printf("\n");
}

int main(){
    image out = rotula(in);
    mostra(out);
}