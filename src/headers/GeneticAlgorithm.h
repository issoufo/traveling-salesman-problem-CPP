//
// Created by imoussaousmane on 26/02/2019.
//

#ifndef TEST_CPP_GENETICALGORITHM_H
#define TEST_CPP_GENETICALGORITHM_H

#include <list>
#include "Boucle.h"
#include "Point.h"
#include "TwoOpt.h"

namespace genetic_algorithm {

    /**
     * Classe modélisant une population(liste de chemins)
     */
    class Population {

        private:
            std::unique_ptr<NearestNeighbour> _nearestNeighbour;
            std::list<std::list<Point>> _randomSolutions;
            std::list<Point> _bestSolution;
            double _bestSolutionLength = 0.0;
            int _populationSize;
            bool _buildPopulation;
            void generateRandomIndividus();

        public:
            explicit Population(std::list<Point> listVilles, Point depart, int populationSize = 20, bool buildPopulation = true);
            std::pair<std::list<Point>, double> meilleur_individu();
            void addIndividu(std::list<Point> individu);
            int getPopulationSize() const ;
            std::list<std::list<Point>> getIndividus() const;
            std::list<Point> getPath(int index) const ;
    };

    /**
     * Classe qui répresente l'implémentation de l'algorithme génétique.
     */
    class GeneticAlgorithm {
        private:
            std::unique_ptr<Population> _population;
            std::list<Point> _listVilles;
            Point _depart;
            const int _tailleTournoi = 5;
            /**
            * C’est la probabilité qu’un point d’un individu(chemin) subisse une mutation. Dans notre cas, cela correspond à l’inversion de la position
            * de deux points d'un individu(chemin). Le taux est assez faible car la probabilité d’obtenir une distance plus faible en inversant deux points
            * est peu élevée.
            */
            const double _tauxMutation = 0.015;

            /**
            * @description : fait affronter plusieurs individus(chemins) sélectionnés au hasard.
            * Dans notre cas nous organisons des tournois de 5 individus.Ainsi, dans le cas où nous faisons affronter 5 mauvais individus,
            * cela laisse tout de même une chance à un de ces (mauvais) individus de pouvoir se reproduire.
            * @return le meilleur individu(solution).
            */
            std::list<Point> selectionTournoi();

            /**
            * @description fait évoluer une population(ensemble de chemin) et renvoie une nouvelle population.
            * @return nouvelle population
            */
            Population evoluerPopulation();

            /**
             * @description créé un individu(chemin) fils à partir de 2 individus d'une population
             * @return individu fils créé.
             */
            std::list<Point> crossover(std::list<Point> parent1, std::list<Point> parent2);

            /**
             * @description Permute 2 élements d'un individu(chemin).
             */
            void muter(std::list<Point> path);

            /**
             *
             * @param nombreGeneration : nombre de génération sur lequel on veut faire évoluer la population. Par defaut on fait évoluer sur 10.
             * @return le meilleur individu de toutes les générations ainsi que sa longueur.
             */
            std::pair<std::list<Point>, double> generation(int nombreGeneration = 10);

        public:
            /**
             * @description : constructeur de l'algorithme génétique.
             * @param listVilles : liste des villes.
             * @param depart : point de départ.
             * @param populationSize : taille de la population initiale.
             * @param buildPopulation : indique si une population aléatoire doit être générée automatiquement.
             */
            explicit GeneticAlgorithm(std::list<Point> listVilles, Point depart, int populationSize = 20, bool buildPopulation = true);

            /**
            *
            * @param nombreGeneration : nombre de génération sur lequel on veut faire évoluer la population. Par defaut on fait évoluer sur 10.
            * @return le meilleur individu(en arrêtes) de toutes les générations ainsi que sa longueur.
            */
            std::pair<std::list<Edge<Point>>, double> meilleure_boucle(int nombreGeneration = 10);
    };
}

#endif //TEST_CPP_GENETICALGORITHM_H
