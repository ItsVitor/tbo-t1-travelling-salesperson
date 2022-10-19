typedef struct stUF tUF;

// Initialize Union
tUF * InitUnionFind(int size);

// Free memory allocated for the UF
void freeUnionFind(tUF * u);

// Check wether p and q are in the same component
int IsConnected(tUF * u, int p, int q);

// Check wether the UF is spanning (all connected)
int isSpanning(tUF * u);

// Chase parent pointers until reach root
int GetRoot(tUF * u, int i);

// Change all entries with vec[p] to vec[q]
void Union(tUF * u, int p, int q);

// Print the UnionFind
void PrintUF(tUF * u);