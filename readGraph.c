#include "readGraph.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Lecture de fichier decrivant un graphe
Graphes *readGraph(char *dbFileName)
{
    //initialiser un graphe non orienté
    Graphes *newGraph = NULL;
    if (newGraph == NULL){
        //Sortie de la fonction
        printf("L'allocation a échouée");
        exit(EXIT_FAILURE);
    }
    //fopen file
    FILE* file = fopen(dbFileName, "r");
    if(!file)
    {
        printf("L'argument doit être un nom de fichier.");
        return -2;
    }
    //Initialisation des variables de parcours des ligne du fichier DB
    char line[256];  // contiendra la chaine de caractères d'une ligne
    char *substr;    // contiendra la chaine de caractères extraite de la ligne
    int nbSommets;
    int nbEdges;
    int i = 1;
    //Tant qu'il y'a une ligne a lire
    while (fgets(line, sizeof(line), file))
    {
        // affichage de la ligne courante
        // printf("%s", line);

        //lire le nombre de sommets
        if (i==1)
        {
            printf("Nombre de sommets = %s\n", substr);// afficher la première valeur lue (un entier).
            nbSommets=atoi(substr);
            //initialiser le graphe en fonction de nbSommets
            newGraph=initgraph(nbSommets,1);
            i++;
        }

        //lire le nombre d'arrete
        else if (i==2)
        {
            printf("Nombre d' arrêtes = %s\n", substr);// afficher la première valeur lue (un entier).
            nbEdges=atoi(substr);;
            i++;
        }

        //lire les coordonnees de chaque sommet des lignes 3 à nbSommets+2
        while (i>2 && i<nbSommets+3)
        {
            substr = (char*) strtok (line, ",");
            int j=0;
            int id_S_Courant;
            while(substr != NULL)
            {
                j++;
                if (j==1)
                {
                   printf("S:%d(",atoi(substr));
                   id_S_Courant=atoi(substr);
                }
                else if (j==2)
                {
                    printf("%d;",atoi(substr));
                    int coordX=atoi(substr);
                    set_vertex_coordX(newGraph,id_S_Courant,coordX);
                }
                else if (j==3)
                {
                    printf("%d)\n",atoi(substr));
                    int coordY=atoi(substr);
                    set_vertex_coordY(newGraph,id_S_Courant,coordY);
                    j==0;
                }
                substr = (char*)strtok (NULL, ",");
            }
            i++;
        }

        //lire les sommets adjacents, ajouter les arcs correspondants
        int k;
        int id_S_Courant,id_Y;
        while (i>nbSommets+2)
        {
            substr = (char*) strtok (line, ":");
            k=0;
            while(substr != NULL)
            {
                k++;
                if (k==1)
                {
                   id_S_Courant=atoi(substr);
                }
                else if (k>1)
                {
                    substr = (char*) strtok (line, ",");
                    while(substr != NULL)
                    {
                        id_Y=atoi(substr);
                        add_edge(newGraph,id_S_Courant,id_Y);
                    }
                    substr = (char*)strtok (NULL, ",");
                }
                substr = (char*)strtok (NULL, ":");
            }
            i++;
        }
    }
    // fermeture du fichier
    fclose(file);
    return newGraph;
}
