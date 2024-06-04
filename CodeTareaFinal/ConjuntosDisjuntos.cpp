#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
 
// Una clase para representar un conjunto disjunto
class DisjointSet
{
    unordered_map<int, int> parent;
 
public:
 
    // realizar la operación MakeSet
    void makeSet(vector<int> const &universe)
    {
        // crear `n` conjuntos disjuntos (uno para cada elemento)
        for (int i: universe) {
            parent[i] = i;
        }
    }
 
    // Encuentra la raíz del conjunto al que pertenece el elemento `k`
    int Find(int k)
    {
        // si `k` es root
        if (parent[k] == k) {
            return k;
        }
 
        // recurre para el padre hasta que encontramos la raíz
        return Find(parent[k]);
    }
 
    // Realizar Unión de dos subconjuntos
    void Union(int a, int b)
    {
        // encontrar la raíz de los conjuntos a los que pertenecen los elementos `x` e `y`
        int x = Find(a);
        int y = Find(b);
 
        parent[x] = y;
    }
};
 
void printSets(vector<int> const &universe, DisjointSet &ds)
{
    for (int i: universe) {
        cout << ds.Find(i) << " ";
    }
    cout << endl;
}
 
// Estructura de datos Disjoint–Set (algoritmo Union–Find)
int main()
{
    // universo de elementos
    vector<int> universe = { 1, 2, 3, 4, 5 };
 
    // inicializa la clase `DisjointSet`
    DisjointSet ds;
 
    // crea un conjunto singleton para cada elemento del universo
    ds.makeSet(universe);
    printSets(universe, ds);
 
    ds.Union(4, 3);        // 4 y 3 están en el mismo conjunto
    printSets(universe, ds);
 
    ds.Union(2, 1);        // 1 y 2 están en el mismo conjunto
    printSets(universe, ds);
 
    ds.Union(1, 3);        // 1, 2, 3, 4 están en el mismo conjunto
    printSets(universe, ds);
 
    return 0;
}