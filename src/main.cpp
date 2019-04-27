#include <iostream>
#include <algorithm>
#include <functional>
#include <cstring>
#include <iomanip>
#include "headers/Graph.h"
#include "headers/GeneticAlgorithm.h"

using namespace std;
using namespace genetic_algorithm;

int main() {

    clock_t start, end;
    start = clock();

/*cout << "**************************************************** graphe des ints ***************************************************" << endl;
    Graph<int> graphDesInts(9,0);
    cout << graphDesInts << endl;*/

/*cout << "******************************************** Meilleur chemin graphe des ints *******************************************" << endl;
    graphDesInts.showBestPath();*/

cout << "*************************************************** graphe des points **************************************************" << endl;
    Point A(0, 0), B(1, 1), C(2, 4), D(1, -3), E(0, -5), F(0, 4), G(-1, -5), H(-2, 3), I(-3, 0);
    list<Point> points = {A, B, C, D, E, F, G, H, I};
    /*Graph<Point> graphDesPoints(points, A);
    cout << graphDesPoints << endl;


cout << "******************************************* Meilleur chemin graphe des points ******************************************" << endl;
    graphDesPoints.showBestPath();*/

cout << "*************************************************** Plus proche voisin *************************************************" << endl;
    NearestNeighbour nearestNeighbour(points, A);
    nearestNeighbour.showBestPath();
    cout << endl << endl;

cout << "********************************************************** 2-OPT *******************************************************" << endl;

    TwoOpt twoOpt(points, A);
    twoOpt.showBestPath();
    cout << endl << endl;

cout << "*************************************************** Algorithme genetique ***********************************************" << endl;
    GeneticAlgorithm geneticAlgorithm(points, A);
    std::pair<std::list<Edge<Point>>, double> population = geneticAlgorithm.meilleure_boucle();

    cout << endl << endl;
    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << " Temps d'execution = " << fixed << time_taken << setprecision(5) << " Secondes" << endl;
    return 0;
}