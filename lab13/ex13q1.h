typedef struct {
    int *parent;
    int *rank;
    int size;
} DisjointSets;

void handle_file(char* f);
DisjointSets* createDisjointSets(int size);
int find(DisjointSets *ds, int i);
void unionSets(DisjointSets *ds, int i, int j);
void destroyDisjointSets(DisjointSets *ds);