//
// Created by imoussaousmane on 26/02/2019.
//

#include <time.h>
#include <fstream>
#include "../headers/GeneticAlgorithm.h"

using namespace genetic_algorithm;

/**
 * @description : constructeur de la population.
 * @param listVilles : liste des points à visiter.
 * @param depart : point de départ.
 * @param populationSize : taille de la population.
 */
Population::Population(std::list<Point> listVilles, Point depart, int populationSize, bool buildPopulation):_populationSize(populationSize), _buildPopulation(buildPopulation) {
    if(populationSize <= 0 || listVilles.size() == 0){
        throw std::invalid_argument("Not accep negative value and empty list of elements.");
    }
    _nearestNeighbour = std::make_unique<NearestNeighbour>(listVilles, depart);
    if(buildPopulation){
        generateRandomIndividus();
    }
}

/**
 * @description : génère une liste de solution aléatoire. Par défaut le nombre d'individus(solutions) générés est 20.
 * Permet aussi de calculer le chemin ayant la plus petite longueur.
 */
void Population::generateRandomIndividus() {
    srand(unsigned(time(0)));
    std::pair<std::list<Edge<Point>>, double> nnbPath = _nearestNeighbour->meilleure_boucle();
    std::list<Edge<Point>> edges = nnbPath.first;
    _bestSolutionLength = nnbPath.second;

    std::vector<Point> initialPath = {};
    for(const auto & edge : edges){
        initialPath.push_back(edge.getFirstNode());
        _bestSolution.push_back(edge.getFirstNode());
    }

    for(int i = 0; i < _populationSize; i++){
        std::random_shuffle(initialPath.begin(), initialPath.end());
        double distance = 0.0;
        int size = initialPath.size();
        for (int j = 0; j < size; j++) {
            if(j == size-1){
                Edge<Point> edge(initialPath[j], initialPath[0]);
                edge.setWeight();
                distance += edge.getWeight();
            }else{
                Edge<Point> edge(initialPath[j], initialPath[j+1]);
                edge.setWeight();
                distance += edge.getWeight();
            }
        }

        if(distance < _bestSolutionLength){
            _bestSolution.clear();
            _bestSolution.assign(initialPath.cbegin(), initialPath.cend());
            _bestSolutionLength = distance;
        }

        std::list<Point> path(initialPath.cbegin(), initialPath.cend());
        _randomSolutions.push_back(path);
    }
}

/**
 * @description : récupère tous les individus(solutions) d'une population(liste des solutions).
 * @param la liste de tous les individus(solutions).
 */
std::list<std::list<Point>> Population::getIndividus() const {
    return _randomSolutions;
}


/**
 * @description : ajoute un individu(solution) dans la population(liste des solutions).
 * @param individu(solution) à ajouter.
 */
void Population::addIndividu(std::list<Point> individu){
    _randomSolutions.push_back(individu);
}

/**
 * @description : permet de récupérer le meilleur individu (solution).
 * @return le meilleur individu(solution).
 */
std::pair<std::list<Point>, double> Population::meilleur_individu() {
    if(_buildPopulation){
        return std::make_pair(_bestSolution, _bestSolutionLength);
    }

    std::list<Point> bestPath = {};
    int size = _randomSolutions.size();
    for(int i = 0; i < size; i++){
        std::list<std::list<Point>>::const_iterator it = cbegin(_randomSolutions);
        std::advance(it, i);
        double distance = 0.0;
        int size = (*it).size();
        for (int j = 0; j < size; j++) {
            std::list<Point>::const_iterator it1 = cbegin(*it);
            std::list<Point>::const_iterator it2 = cbegin(*it);
            std::advance(it1, j);
            if(j == size-1){
                std::advance(it2, 0);
            }else{
                std::advance(it2, j+1);
            }
            Edge<Point> edge(*it1, *it2);
            edge.setWeight();
            distance += edge.getWeight();
        }

        if(i == 0){
            _bestSolutionLength = distance;
            bestPath = *it;
            continue;
        }
        if(distance < _bestSolutionLength){
            _bestSolutionLength = distance;
            bestPath = *it;
        }
    }
    return std::make_pair(bestPath, _bestSolutionLength);
}


/**
 * @description : permet de récupérer la population (solution) située à une position donnée.
 * @return la population(solution) situé à l'index indiqué.
 */
std::list<Point> Population::getPath(int index) const {
    std::list<std::list<Point>>::const_iterator it = cbegin(_randomSolutions);
    std::advance(it, index);
    return *it;
}

/**
 * @return la taille de la population(nombre de solutions).
 */
int Population::getPopulationSize() const {
    return _populationSize;
}

GeneticAlgorithm::GeneticAlgorithm(std::list<Point> listVilles, Point depart, int populationSize, bool buildPopulation): _listVilles(listVilles), _depart(depart){
    if(populationSize <= 0 || listVilles.size() == 0){
        throw std::invalid_argument("Not accep negative value and empty list of elements.");
    }

    _population = std::make_unique<Population>(listVilles, depart, populationSize, buildPopulation);
}

Population GeneticAlgorithm::evoluerPopulation() {
    Population newPopulation(_listVilles, _depart, _population -> getPopulationSize(), false);
    int size = newPopulation.getPopulationSize();
    for (int i = 0; i < size; i++) {
        std::list<Point> parent1 = selectionTournoi();
        std::list<Point> parent2 = selectionTournoi();
        std::list<Point> enfant = crossover(parent1, parent2);
        newPopulation.addIndividu(enfant);
    }

    for(const auto & path : newPopulation.getIndividus()){
        muter(path);
    }

    return newPopulation;
}

std::list<Point> GeneticAlgorithm::crossover(std::list<Point> parent1, std::list<Point> parent2) {
    std::list<Point> enfant = parent1;
    for(const auto & point : parent2){
        const auto result = std::find(cbegin(enfant), cend(enfant), point);
        if(result == cend(enfant)){
            enfant.push_back(point);
        }
    }

    return enfant;
}

void GeneticAlgorithm::muter(std::list<Point> path) {
    int size = path.size();
    for (int i = 0; i < size; ++i) {
        srand(unsigned(time(0)));
        double randomNumber = rand() % 1;
        if(randomNumber < _tauxMutation){
            int randomIndex = rand() % size;
            std::list<Point>::iterator it1 = begin(path);
            std::list<Point>::iterator it2 = begin(path);
            std::advance(it1, i);
            std::advance(it2, randomIndex);

            Point point1 = *it1;
            Point point2 = *it2;

            *it1 = point2;
            *it2 = point1;
        }
    }
}

std::list<Point> GeneticAlgorithm::selectionTournoi() {
    Population tournoi = Population(_listVilles, _depart, _tailleTournoi, false);
    srand(unsigned(time(0)));
    int popSize = _population -> getPopulationSize();
    for(int i = 0; i < _tailleTournoi; i++){
        int randomIndex = rand() % popSize;
        tournoi.addIndividu(_population->getPath(randomIndex));
    }

    return tournoi.meilleur_individu().first;
}

std::pair<std::list<Point>, double> GeneticAlgorithm::generation(int nombreGeneration) {
    std::pair<std::list<Point>, double> bestIndividu;
    Population population = evoluerPopulation();

    bestIndividu = population.meilleur_individu();
    double bestDistance = bestIndividu.second;

    const std::string PATH = "../genetic_solutions.txt";
    std::ofstream file(PATH);
    if(file){
        for (int i = 0; i < nombreGeneration; i++) {
            Population pop = evoluerPopulation();
            std::pair<std::list<Point>, double> individu = pop.meilleur_individu();
            std::list<Point> path = individu.first;
            double distance = individu.second;

            for (const auto & point : path){
                file << point;
            }
            file << " : " << distance << std::endl;

            if(bestDistance < distance){
                bestIndividu = individu;
                bestDistance = distance;
            }
        }
    }
    file.close();
    return bestIndividu;
}

std::pair<std::list<Edge<Point>>, double> GeneticAlgorithm::meilleure_boucle(int nombreGeneration) {
    std::list<Edge<Point>> bestPath;
    if(nombreGeneration <= 0){
        return std::make_pair(bestPath, 0.0);
    }
    std::pair<std::list<Point>, double> individu = generation(nombreGeneration);
    std::list<Point> path = individu.first;
    int index = 0;
    std::cout << "[";
    for (const auto & point : path){
        std::list<Point>::const_iterator it1 = cbegin(path);
        std::list<Point>::const_iterator it2 = cbegin(path);
        std::cout << point << ",";

        std::advance(it1, index);
        if(index == path.size() - 1){
            std::advance(it2, 0);
            std::cout << *it2;
        } else{
            std::advance(it2, index+1);
        }
        Edge<Point> edge(*it1, *it2);
        edge.setWeight();
        bestPath.push_back(edge);
        index++;
    }

    std::cout << "] : " << individu.second;

    return std::make_pair(bestPath, individu.second);
}