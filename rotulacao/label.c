/*-------------------------------------------------------------------------
 * Tranformação de intensidade
 * Por Luiz Eduardo da Silva.
 *-------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "imagelib.h"

int find(int parent[], int i)
{
    while (parent[i] != i)
        i = parent[i];
    return i;
}

void Union(int parent[], int i, int j)
{
    int x = find(parent, i);
    int y = find(parent, j);
    parent[y] = x;
}

image rotula (image in){
    image result = img_clone(img);
    int w = img->nc;
    int h= img->nr;
    int*in=img->px;
    int*out=result->px;
    int rotulo = 0;
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
        result->ml=rotulo;
    }return result;
}

void msg(char *s)
{
    printf("\nLabelling");
    printf("\n-------------------------------");
    printf("\nUso:  %s  nome-imagem[.pbm] \n\n", s);
    printf("    nome-imagem[.pbm] é o nome do arquivo da imagem \n");
    exit(1);
}

/*-------------------------------------------------------------------------
 * main function
 *-------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    int nc,nr,ml,tp;
    char nameIn[100], nameOut[100], cmd[110];
    image In, Out;
    if (argc < 2)
        msg(argv[0]);

    img_name(argv[1], nameIn, nameOut, BW, GRAY);

    //-- read image
    In = img_get(nameIn, BW);
    //-- transformation
    Out = rotula(In);
    //-- save image
    img_put(Out, nameOut, GRAY);

    sprintf(cmd, "%s %s &", VIEW, nameOut);
    pust(cmd);
    system(cmd);
    img_free(In);
    img_free(Out)
    return 0;
}
