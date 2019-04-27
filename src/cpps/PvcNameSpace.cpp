//
// Created by imoussaousmane on 05/12/2018.
//

#include <vector>
#include <random>
#include <iostream>
#include <list>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "../headers/PvcNameSpace.h"
#include "../headers/Edge.h"

using namespace pvc_name_space;

File::~File() {}

File::File(int numberOfNodes): _numberOfNodes(numberOfNodes), _weightList({}), _listEdges({}){
    randomNumbersGenerated();
}

int File::getNumberOfNodes() const {
    return _numberOfNodes;
}

/**
 * Génère aléatoirement des entiers compris entre 0 et WEIGHT_LIMIT.
 */
void File::randomNumbersGenerated() {
    int edgesNumber = ((_numberOfNodes - 1) * _numberOfNodes) / 2;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, pvc_name_space::WEIGHT_LIMIT - 1);

    for (int i = 0; i < edgesNumber; ++i){
        _weightList.push_back(dist(mt));
    }

    // Call to the method witch write the tuples of node in file
    writeInFile();
}

/**
 * Ecrit des tuples des noeuds dans le fichier(exemple (0,1); (1,0) etc) et affecte un poids à chaque tuple.
 */
void File::writeInFile() {
    std::ofstream fileGenerated(PATH);
    if (fileGenerated){
        // Call to the method witch create the tuples of node and return it
        getListTuples();
        std::list<int>::const_iterator weight;
        fileGenerated << _weightList.size() << std::endl;
        int i = 0;
        for (auto& weight : _weightList) {
            std::array<int, 2> nodes = _listTuples[i];
            fileGenerated <<  nodes[0] << " " << nodes[1] << " " << weight << std::endl;
            i++;
        }
        fileGenerated.close();
        // Call to the method witch create the edges of graph
        createEdges();
        return;
    }

    std::cout << "ERROR: Impossible to open file." << std::endl;
    fileGenerated.close();
}

// Create the tuples of node
/**
 * créé les tuples
 * @return la liste des tuples
 */
std::vector<std::array<int, 2>> File::getListTuples(){
    for(int i = 0; i < _numberOfNodes; i++){
        for(int j = 0 ; j < _numberOfNodes; j++){
            if(i != j){
                std::array<int, 2> tab = {i, j};
                if(contains(_listTuples, tab)){
                    continue;
                }
                _listTuples.push_back(tab);
            }
        }
    }

    return _listTuples;
}

/**
 * Créé les arrêtes à partir des données du fichier.
 */
void File::createEdges(){
    std::ifstream readFile;
    readFile.open(PATH);
    if(readFile){
        std::string line;
        int i = 0;
        while(std::getline(readFile, line)){
            if(i > _weightList.size()){
                std::cout << "PROBLEM : the number of edges want be superior to list of weight." << i << std::endl;
                return;
            }
            std::array<std::string, 3> edgeShape = stringSplit(line);
            if(edgeShape.size() == 3){
                std::string firstNode = edgeShape[0];
                std::string secondNode = edgeShape[1];
                std::string weight = edgeShape[2];

                if(is_number(firstNode) && is_number(secondNode) && is_number(weight)){
                    Edge<int> edge = Edge<int>(std::stoi(firstNode), std::stoi(secondNode), std::stoi(weight));
                    _listEdges.push_back(edge);
                }
            }
            i++;
        }
        // Call to the method witch create the matrix of node
        createMatrix();
    }
}

/**
 *
 * @return la liste des arrêtes.
 */
std::list<Edge<int>> File::getListEdges() const {
    return _listEdges;
}

/**
 * Créé la matrice des poids(les arrêtes). S'il n'y a pas d'arrêtes entre les noeuds le poids est -1
 */
void File::createMatrix() {
    for(int i = 0; i < _numberOfNodes; i++){
        for(int j = 0; j < _numberOfNodes; j++){
            Edge<int> edge = Edge<int>(i,j);
            std::vector<Edge<int>> edges = search(_listEdges, edge);
            std::vector<int > matrix;
            if(!edges.empty() && edges.size() == 1){
                matrix.push_back(i);
                matrix.push_back(j);
                matrix.push_back(edges[0].getWeight());
                _matrix.push_back(matrix);
                continue;
            }

            matrix.push_back(i);
            matrix.push_back(j);
            matrix.push_back(-1);
            _matrix.push_back(matrix);
        }
    }
}

/**
 *
 * @return la matrice des points.
 */
std::vector<std::vector<int>> File::getMatrix() const {
    return _matrix;
}

/**
 * @description recherche un élement dans un containeur
 * @tparam T type de l'élément à rechercher
 * @tparam Container type du containeur dans lequel on cherche l'élément
 * @param containers le containeur dans lequel on cherche l'élément
 * @param t l'élément à rechercher
 * @return la liste des éléments égaux à l'élément recherché.
 */
template<typename T,template <typename, typename = std::allocator<T>> class Container>
std::vector<T> pvc_name_space::search(const Container<T> & containers, const T &t){
    std::vector<T> elements = {};
    for(const auto& element : containers){
        if(element == t){
            elements.push_back(element);
        }
    }
    return elements;
}

/**
 * @description recherche un élement dans un containeur
 * @tparam T type de l'élément à rechercher
 * @tparam Container type du containeur dans lequel on cherche l'élément
 * @param containers le containeur dans lequel on cherche l'élément
 * @param t l'élément à rechercher
 * @return vrai si l'élément existe dans la collection. La comparaison est bidirectionnelle((0,1) == (1,0))
 */
template<typename T,template <typename, typename = std::allocator<T>> class Container>
bool pvc_name_space::contains(const Container<T> & containers, const T & t){
    for (auto& element : containers){
        if ((element[0] == t[0] && element[1] == t[1]) || (element[0] == t[1] && element[1] == t[0]))
            return true;
    }
    return false;
}

/**
 * @description vérifie si une string peut être convertie en valeur numérique
 * @param value valeur à vérifier
 * @return vrai si la chaine est convertible en entier
 */
bool pvc_name_space::is_number(const std::string& value){
    return !value.empty() && std::find_if(value.begin(),value.end(), [](char c) {
        return !std::isdigit(c);
    }) == value.end();
}
/**
 * @description split une string
 * @param value valeur à spliter
 * @return un tableau vide si la taille du split est supérieur à 2
 */
std::array<std::string, 3> pvc_name_space::stringSplit(std::string value){
    std::istringstream stream(value);
    std::array<std::string, 3> result;
    int i = 0;
    std::string line;
    while(std::getline(stream, line, ' ')){
        if(i > 2){
            std::cout << "A line don't respect the file format.";
            return result;
        }
        result[i] = line;
        i++;
    }

    return result;
}

/**
 * @description calcul la distance entre 2 points
 * @param point1
 * @param point2
 * @return la distance entre 2 points
 */
double pvc_name_space::computeDistance(const Point & point1, const Point & point2){
    double computeDistance = std::pow((point2.getX() - point1.getX()), 2) + std::pow((point2.getY() - point1.getY()), 2);
    return std::sqrt(computeDistance);
}

