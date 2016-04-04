#ifndef H_GRAPH
#define H_GRAPH

//Structures de donnée
typedef struct Sommet
{
    int id; //id unique pour chaque nouveau sommet
    int dataS;//valeur associer au sommet
    int x;
    int y;
    int dataE;//valeur associer a l'arc
    struct Sommet *adjacents;//Pointe sur des copies de sommets
} Sommet;

typedef struct ListeSommet
{
    int nbAdj; //Nombre  de sommets adjacents a la tete
    Sommet *head; //tete de la liste d'adjacence
}ListeSommet;

typedef struct Graphes
{
    int nbSommets; //Nombre  de sommets dans le graphe
    int primKey; //Pour palier au probleme d'attribution des idSommet. primKey n'est pas décrémenter lorsque on supprime un sommet
    int type; //Reste a implementer le type (orienté=0; non-orienté=1)
    ListeSommet *l_sommets; /*Pointe sur un tableau de listes d'adjacence,*/
                            /*chaque case pointant sur une tete de liste qui elle meme*/
                            /*pointera sur des copie de sommets adjacents*/
} Graphes;


//Opérations
//teste s'il existe dans G un arc allant du sommet x vers y;
int is_adjacent(Graphes *G, int X_id, int Y_id);

//liste tous les sommets de G pouvant etre atteint directement depuis x
void neighbours (Graphes *G, int S_id);

//ajoute le sommet x a G s'il n'existe pas déja;
void add_vertex(Graphes *G);

//ote le sommet x de G, s'il existe;
void remove_vertex(Graphes *G, int S_id);

//ajoute l'arc x vers y, s'il n'existe pas déja dans G;
void add_edge(Graphes *G, int x_id, int y_id);

//ote l'arc x vers y, s'il existe dans G;
void remove_edge(Graphes *G, int x_id, int y_id);

//retourne la valeur associee au sommet x dans G;
int get_vertex_value(Graphes *G, int S_id);

//definit la valeur v associee au sommet x dans G;
void set_vertex_value(Graphes *G, int S_id, int data);

//retourne la valeur associee a l'arc (x,y);
int get_edge_value(Graphes *G, int x_id, int y_id);

//definit la valeur associee a l'arc (x,y);
void set_edge_value(Graphes *G, int x_id, int y_id, int data);

//Allouer la mémoire
Graphes *initgraph(int nbS, int typeO);

//Liberer la mémoire
void freegraph(Graphes *graph);

//bac a sable
void dispHead(Graphes *graph);

#endif
