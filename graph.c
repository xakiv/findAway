#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

//Allouer la mémoire
Graphes *initgraph(int nbS, int typeO)
{
    int i;
    Graphes *newGraph =NULL;
	newGraph = malloc(1 * sizeof(Graphes));
    if (newGraph)
    {
    	newGraph->nbSommets=nbS;
    	newGraph->type=typeO;
    	newGraph->primKey=nbS;/*Pour palier au probleme d'attribution des idSommet.
                              /*primKey n'est pas décrémenter lorsque on supprime un sommet*/
    	newGraph->l_sommets=malloc(nbS * sizeof(ListeSommet));
        if (newGraph->l_sommets)
        {
            for(i=0; i<newGraph->nbSommets; i++)
            {
                newGraph->l_sommets[i].nbAdj=0;
                newGraph->l_sommets[i].head=NULL;
                newGraph->l_sommets[i].head=malloc(1 * sizeof(Sommet));
                if (newGraph->l_sommets[i].head)
                {
                    newGraph->l_sommets[i].head->id=i;
                    newGraph->l_sommets[i].head->dataS=0;
                    newGraph->l_sommets[i].head->adjacents=NULL;
                }
            }
        }
	}

	return newGraph;
}

//Liberer la mémoire
void freegraph(Graphes *graph)
{
	if(graph)
    {
        if(graph->l_sommets)
        {
            //Liberation des sommets
            int i;
            for (i=0; i<graph->nbSommets; i++)
            {
                printf("Sommet %d FREE \n",graph->l_sommets[i].head->id);
                free(graph->l_sommets[i].head);
            }
            //Liberation des listes d'adja
            free(graph->l_sommets);
        }
    }
    //Liberation graphe
    free(graph);
}

//teste s'il existe dans G un arc allant du sommet x vers y;
int is_adjacent(Graphes *G, int X_id, int Y_id)
{
    int is_adja=0; //0 pour FALSE, 1 pour TRUE
    int i;
    for (i=0; i<G->nbSommets; i++)
    {
        //verifie si x est dans le graph G
        if(G->l_sommets[i].head->id==X_id)
        {
            //printf("%d EsT dans le graphe \n", X_id);
            //initialise un pointeur de sommet temporaire
            Sommet *courant=NULL;
            courant=G->l_sommets[i].head;
            int j;
            for (j=0; j<G->l_sommets[i].nbAdj; j++)
            {
                //verifie si y est dans la liste d'adjacence de x
                if(courant->adjacents->id==Y_id)
                {
                    //printf("%d ET %d sont adjacents \n", X_id, Y_id);
                    is_adja=1;
                }
                else
                {
                    courant=courant->adjacents;
                }
            }
        }
    }
    return is_adja;
}

//liste tous les sommets de G pouvant etre atteint directement depuis un sommet d'indice S_id
void neighbours (Graphes *G, int S_id)
{
    int i;
    for (i=0; i<G->nbSommets; i++)
    {
        //verifie si x est dans le graph G
        if(G->l_sommets[i].head->id==S_id)
        {
            printf("S:%d-->", S_id);

            //initialise un pointeur de sommet temporaire
            Sommet *courant=NULL;
            courant=G->l_sommets[i].head;

            //Parcour la liste tant que l'arc ne pointe pas vers NULL
            while (courant->adjacents!=NULL)
            {
                courant=courant->adjacents;
                printf("Adj:%d-->", courant->id);
            }
            printf("NULL \n");
        }
    }
}

//Ajoute un sommet d'id égale à nbSommet puis incrémente le nbSommet.
void add_vertex(Graphes *G)
{
    G->l_sommets = realloc(G->l_sommets, (G->nbSommets+1) * sizeof(ListeSommet));
    if (G->l_sommets!=NULL){
        G->l_sommets[G->nbSommets].nbAdj=0;
        G->l_sommets[G->nbSommets].head=NULL;
        G->l_sommets[G->nbSommets].head=malloc(1 * sizeof(Sommet));
        if (G->l_sommets[G->nbSommets].head){
            G->l_sommets[G->nbSommets].head->id=G->primKey;
            G->l_sommets[G->nbSommets].head->dataS=0;
            G->l_sommets[G->nbSommets].head->adjacents=NULL;
        }
        printf("Id du nouveau sommet: %d\n", G->l_sommets[G->nbSommets].head->id);
        G->nbSommets++;
        G->primKey++;
        printf("Nombres de sommets: %d\n", G->nbSommets);
    }
}

//ote le sommet x de G, s'il existe;
void remove_vertex(Graphes *G, int S_id)
{
    int i;
    int bool_s=0; //Test si le sommet S existe
    for (i=0; i<G->nbSommets; i++)
    {
        //verifie si x est dans le graph G
        if(G->l_sommets[i].head->id==S_id)
        {
            printf("S:%d will be killed\n", S_id);
            bool_s=1;
            int j=S_id;
            //décremente l'indice des sommets suivant dans l_sommets[]
            while (j<G->nbSommets-1)
            {
                //Remplacer le sommet courant par le sommet suivant Tq il existe un dernier sommet
                G->l_sommets[j].head=G->l_sommets[j+1].head;
                j++;
            }
            free(G->l_sommets[G->nbSommets].head);
            G->nbSommets--;
            //G->l_sommets = realloc(G->l_sommets, (G->nbSommets) * sizeof(ListeSommet));
        }
    }
    if (bool_s=0)printf("S:%d n'existe pas dans le graphe\n", S_id);
}

//ajoute l'arc x vers y, s'il n'existe pas déja dans G;
void add_edge(Graphes *G, int x_id, int y_id)
{
    //verifie si l'arc n'existe pas deja
    if(is_adjacent(G,x_id,y_id)==0)
    {
        Sommet *courantX=NULL;
        Sommet *courantY=NULL;
        Sommet *courantX2=NULL;
        Sommet *courantY2=NULL;
        int y_bool=0; //Test la presence dans le graphe G d'un sommet Y.
        int x_bool=0; //Test la presence dans le graphe G d'un sommet X.

        int i;
        for (i=0; i<G->nbSommets; i++)
        {
            //Recuperer l'indice de x dans l_sommets[]
            //initialiser un pointeur de sommet sur la tete de liste correspondant a cet indice
            //incrementer le nombre de sommets adjacents a la tete
            if(G->l_sommets[i].head->id==x_id)
            {
                courantX=G->l_sommets[i].head;
                G->l_sommets[i].nbAdj++;
            }
            //Test la presence dans le graphe G d'un sommet Y.
            if(G->l_sommets[i].head->id==y_id)
            {
               y_bool=1;
            }
        }
        if(y_bool==1){
            //Crée une copie du sommet Y
            courantY=malloc(1 * sizeof(Sommet));
            courantY->id=y_id;
            courantY->dataE=0;
            //Se deplacer jusqu'a la fin de la liste des adjacent de X
            while (courantX->adjacents!=NULL)
            {
                courantX=courantX->adjacents;
            }
            //Faire pointer le dernier sur la copie du sommet Y
            courantX->adjacents=courantY;
            //Signaler la fin de la liste chainée concernant les adjacent de X
            courantY->adjacents=NULL;
        }
        if (G->type==1)
        {
            int j;
            for (j=0; j<G->nbSommets; j++)
            {
                //Recuperer l'indice de y dans l_sommets[]
                //initialiser un pointeur de sommet sur la tete de liste correspondant a cet indice
                //incrementer le nombre de sommets adjacents a la tete
                if(G->l_sommets[j].head->id==y_id)
                {
                   courantY2=G->l_sommets[j].head;
                   G->l_sommets[j].nbAdj++;
                }
                //Test la presence dans le graphe G d'un sommet X.
                if(G->l_sommets[j].head->id==x_id)
                {
                   x_bool=1;
                }
            }
            if(x_bool==1){
                //Crée une copie du sommet X
                courantX2=malloc(1 * sizeof(Sommet));
                courantX2->id=x_id;
                courantX2->dataE=0;
                //Se deplacer jusqu'a la fin de la liste des adjacent de Y
                while (courantY2->adjacents!=NULL)
                {
                   courantY2=courantY2->adjacents;
                }
                //Faire pointer le dernier sur la copie du sommet X
                courantY2->adjacents=courantX2;
                //Signaler la fin de la liste chainée concernant les adjacent de X
                courantX2->adjacents=NULL;
            }
        }
    }else{
        printf("Un arc existe deja entre %d et %d\n",x_id,y_id);
    }
}

//ote l'arc x vers y, s'il existe dans G;
void remove_edge(Graphes *G, int x_id, int y_id)
{
    //verifie si l'arc existe deja
    if(is_adjacent(G,x_id,y_id)==1)
    {
        Sommet *courantX=NULL;
        Sommet *courantY=NULL;
        int i;
        for (i=0; i<G->nbSommets; i++)
        {
            //Recuperer l'indice de x dans l_sommets[]
            //initialiser un pointeur de sommet sur la tete de liste correspondant a cet indice
            //decrementer le nombre de sommets adjacents a la tete
            if(G->l_sommets[i].head->id==x_id)
            {
                courantX=G->l_sommets[i].head;
                G->l_sommets[i].nbAdj--;
            }
            //Recuperer l'indice de y dans l_sommets[]
            //initialiser un pointeur de sommet sur la tete de liste correspondant a cet indice
            if(G->l_sommets[i].head->id==y_id)
            {
                courantY=G->l_sommets[i].head;
            }
        }
        //Se deplacer jusqu'a la fin de la liste des adjacents de X
        while (courantX->adjacents!=courantY)
        {
            courantX=courantX->adjacents;
        }
        //Faire pointer le dernier sur un pointeur de Y
        courantX->adjacents=courantY->adjacents;
    }else{
        printf("Aucun arc entre %d et %d\n",x_id,y_id);
    }
}

//retourne la valeur associee au sommet d'indice S_id dans G;
int get_vertex_value(Graphes *G, int S_id){
    int i;
    int data=0;
    for (i=0; i<G->nbSommets; i++)
    {
        //verifie si x est dans le graph G
        if(G->l_sommets[i].head->id==S_id)
        {
           data=G->l_sommets[i].head->dataS;
        }
    }
    if (data=0)exit(EXIT_FAILURE);
    else return data;
}

//definit la valeur data associee au sommet d'indice S_id dans G;
void set_vertex_value(Graphes *G, int S_id, int data){
    int i;
    for (i=0; i<G->nbSommets; i++)
    {
        //verifie si x est dans le graph G
        if(G->l_sommets[i].head->id==S_id)
        {
           G->l_sommets[i].head->dataS=data;
           printf("S:%d->ValS:%d\n",S_id,G->l_sommets[i].head->dataS);
        }
    }
}

//definit la valeur coordX associee au sommet d'indice S_id dans G;
void set_vertex_coordX(Graphes *G, int S_id, int coordX){
    int i;
    for (i=0; i<G->nbSommets; i++)
    {
        //verifie si x est dans le graph G
        if(G->l_sommets[i].head->id==S_id)
        {
           G->l_sommets[i].head->x=coordX;
        }
    }
}

//definit la valeur coordY associee au sommet d'indice S_id dans G;
void set_vertex_coordY(Graphes *G, int S_id, int coordY){
    int i;
    for (i=0; i<G->nbSommets; i++)
    {
        //verifie si x est dans le graph G
        if(G->l_sommets[i].head->id==S_id)
        {
           G->l_sommets[i].head->y=coordY;
        }
    }
}

//retourne la valeur associee a l'arc (x,y);
int get_edge_value(Graphes *G, int x_id, int y_id){
    //verifie si l'arc existe
    if(is_adjacent(G,x_id,y_id)==1)
    {
        Sommet *courantX=NULL;
        Sommet *courantY=NULL;
        int i;
        for (i=0; i<G->nbSommets; i++)
        {
            //Recuperer l'indice de x dans l_sommets[]
            //initialiser un pointeur de sommet sur la tete de liste correspondant a cet indice
            if(G->l_sommets[i].head->id==x_id)
            {
                courantX=G->l_sommets[i].head;
            }
        }
        //Se deplacer jusqu'a ce que l'arc de X pointe sur Y
        while (courantX->adjacents->id!=y_id)
        {
            courantX=courantX->adjacents;
        }
        //retourner la valeur associé a l'arc qui pointe sur Y
        return courantX->adjacents->dataE;

    }else{
        printf("Aucun arc entre %d et %d\n",x_id,y_id);
        exit(EXIT_FAILURE);
    }
}

//definit la valeur associee a l'arc (x,y);
void set_edge_value(Graphes *G, int x_id, int y_id, int data){
    //verifie si l'arc existe
    if(is_adjacent(G,x_id,y_id)==1)
    {
        Sommet *courantX=NULL;
        Sommet *courantY=NULL;
        int i;
        for (i=0; i<G->nbSommets; i++)
        {
            //Recuperer l'indice de x dans l_sommets[]
            //initialiser un pointeur de sommet sur la tete de liste correspondant a cet indice
            if(G->l_sommets[i].head->id==x_id)
            {
                courantX=G->l_sommets[i].head;
            }
        }
        //Se deplacer jusqu'a ce que l'arc de X pointe sur Y
        while (courantX->adjacents->id!=y_id)
        {
            courantX=courantX->adjacents;
        }
        //Definit la valeur associé a l'arc qui pointe sur Y
        courantX->adjacents->dataE=data;

    }else{
        printf("Aucun arc entre %d et %d\n",x_id,y_id);
        exit(EXIT_FAILURE);
    }
}
//bac a sable
void dispHead(Graphes *graph)
{
    int i;
    int S_id;
    Sommet *courant=NULL;
    int arc;
    int Sadja;
    if(graph)
    {
        for (i=0; i<graph->nbSommets; i++)
        {
            S_id=graph->l_sommets[i].head->id;
            courant=graph->l_sommets[i].head;
            neighbours(graph,S_id);
            printf("S:%d->ValS:%d\n",S_id,courant->dataS);
            while(courant->adjacents!=NULL)
            {
                arc=courant->adjacents->dataE;
                Sadja=courant->adjacents->id;
                printf("S:%d---Arc=%d--->S:%d\n",S_id,arc,Sadja);
                courant=courant->adjacents;
            }
            printf("~~~~~~~~~~~~~~~~~~~~~~\n");
        }
    }
}



