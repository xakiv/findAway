float getDistance(Poi a, Poi b){
	//cast: (double)( n * m + l...) avec n m et l int, le résultat de l'expression convertit en double
	double exp1 = pow((b.xCoord - a.xCoord),2);
	double exp2 = pow((b.yCoord - a.yCoord),2);
	return sqrt(exp1+exp2);
}

//#include <stdio.h>
//#include <stdlib.h>
//#include "graph.h"
//int main(int argc, char* argv[])
//{
//    //Declaration des variables
//    int nbSom=5; //Ids sommet: 0..nbSom-1
//    printf("--------------Allouer la mémoire pour %d sommets:\n",nbSom);
//	Graphes *mongraphe=NULL;
//    mongraphe=initgraph(nbSom,0);
//
//    printf("--------------Afficher les sommet initialises:\n");
//    dispHead(mongraphe);
//
//
//    printf("--------------Ajouter les nouveau sommets au graph:\n");
//	add_vertex(mongraphe);
//	remove_vertex(mongraphe,4); /*teste de la bonne reatribution des idSommet en cas de*/
//	add_vertex(mongraphe);      /*Suppression suivit de Creation de sommet*/
//	dispHead(mongraphe);
//
//	printf("--------------Ajouter un arc (X;Y):\n");
//	add_edge(mongraphe,0,1);
//	add_edge(mongraphe,0,2);
//	add_edge(mongraphe,1,2);
//
//
////    printf("--------------Oter un arc de X:\n");
////    remove_edge(mongraphe,0,1);
////    remove_edge(mongraphe,0,1);
//
//    printf("--------------Definir et retourner la valeur associee a un sommet:\n");
//    set_vertex_value(mongraphe,0,15);
//    set_vertex_value(mongraphe,1,30);
//    set_vertex_value(mongraphe,2,33);
//
//	printf("--------------Definir et retourner la valeur associee a l'arc (X;Y):\n");
//	set_edge_value(mongraphe,0,1,25);
//	printf("S:0-->Arc=%d-->S:1\n",get_edge_value(mongraphe,0,1));
//	printf("--------------\n");
//    set_edge_value(mongraphe,0,2,50);
//	printf("S:0-->Arc=%d-->S:2\n",get_edge_value(mongraphe,0,2));
//	printf("--------------\n");
//    set_edge_value(mongraphe,1,2,100);
//	printf("S:1-->Arc=%d-->S:2\n",get_edge_value(mongraphe,1,2));
//	printf("--------------\n");
//    set_edge_value(mongraphe,0,2,150);
//	printf("S:0-->Arc=%d-->S:2\n",get_edge_value(mongraphe,0,2));
//	printf("--------------\n");
//	printf("------- TESTE ARC 1-2 -------\n");
//	printf("S:1-->Arc=%d-->S:2\n",get_edge_value(mongraphe,1,2));
//
//    printf("--------------Affiche liste des adjacent de 0:\n");
//    neighbours(mongraphe,0);
//
//    printf("--------------Affiche les sommets et adjacents puis les arcs si ils existent:\n");
//    dispHead(mongraphe);
//
//    printf("--------------Mouvement de Liberation des Graphes:\n");
//	freegraph(mongraphe);
//
//	printf("----------------------------------------------------:\n");
//	printf("--------------TEST GRAPH ORIENTE--------------------:\n");
//	printf("----------------------------------------------------:\n");
//    int nbSom2=10; //Ids sommet: 0..nbSom-1
//    printf("--------------Allouer la mémoire pour %d sommets:\n",nbSom2);
//	Graphes *grapheO=NULL;
//    grapheO=initgraph(nbSom2,1);
//
//    printf("--------------Afficher les sommet initialises:\n");
//    dispHead(grapheO);
//
//	printf("--------------Ajouter un arc (X;Y):\n");
//	add_edge(grapheO,0,1);
//	add_edge(grapheO,0,2);
//	add_edge(grapheO,1,2);
//	dispHead(grapheO);
//
//
//    printf("--------------Definir et retourner la valeur associee a un sommet:\n");
//    set_vertex_value(grapheO,0,200);
//    set_vertex_value(grapheO,1,210);
//    set_vertex_value(grapheO,2,220);
//
//	printf("--------------Definir et retourner la valeur associee a l'arc (X;Y):\n");
//	set_edge_value(grapheO,0,1,125);
//	printf("S:0-->Arc=%d-->S:1\n",get_edge_value(grapheO,0,1));
//	printf("--------------\n");
//    set_edge_value(grapheO,0,2,150);
//	printf("S:0-->Arc=%d-->S:2\n",get_edge_value(grapheO,0,2));
//	printf("--------------\n");
//    set_edge_value(grapheO,1,2,100);
//	printf("S:1-->Arc=%d-->S:2\n",get_edge_value(grapheO,1,2));
//	printf("--------------\n");
//    set_edge_value(grapheO,0,2,110);
//	printf("S:0-->Arc=%d-->S:2\n",get_edge_value(grapheO,0,2));
//	printf("--------------\n");
//	printf("------- TESTE ARC 1-2 -------\n");
//	printf("S:1-->Arc=%d-->S:2\n",get_edge_value(grapheO,1,2));
//
//    printf("--------------Affiche liste des adjacent de 0:\n");
//    neighbours(grapheO,0);
//
//    printf("--------------Affiche les sommets et adjacents puis les arcs si ils existent:\n");
//    dispHead(grapheO);
//
//    printf("--------------Mouvement de Liberation des Graphes:\n");
//	freegraph(grapheO);
//
//
//	return 0;
//}
