//
// Created by imoussaousmane on 27/12/2018.
//

#ifndef TEST_CPP_DISTANCEGENERATOR_H
#define TEST_CPP_DISTANCEGENERATOR_H

#include <memory>
#include <set>
#include "Boucle.h"
#include "LoopGenerator.h"

/**
 * @description calcule la distance de chaque boucle et donne la meilleur boucle. Elle correspond à la question 4 et 5 du sujet.
 * @tparam T type d'éléments de la boucle
 */
template<typename T>
class DistanceGenerator {

    private:
        std::unique_ptr<LoopGenerator<T>> _loopGenerator = nullptr;
        std::set<Boucle<T>> _boucles;

    public:

        /**
         * @description constructeur pour les simples éléments(par exemple des ints)
         * @param n nombre d'éléments
         * @param depart point de depart
         * @param matrix liste des arrêtes du graph.
         */
        explicit DistanceGenerator(T n, T depart, std::list<Edge<T>> matrix): _loopGenerator(std::make_unique<LoopGenerator<T>>(n, depart)){
            auto boucles = _loopGenerator -> genere_boucle();
            for(const auto & element : boucles){
                Boucle<T> boucle(element, matrix);
                _boucles.insert(boucle);
            }
        }

        /**
         * @description constructeur pour les containeurs(list) éléments(par exemple des ints)
         * @param elements liste d'éléments
         * @param depart point de depart
         * @param matrix liste des arrêtes du graph.
         */
        explicit DistanceGenerator(std::list<T> elements, T depart, std::list<Edge<T>> matrix): _loopGenerator(std::make_unique<LoopGenerator<T>>(elements, depart)){
            auto boucles = _loopGenerator -> genere_boucle();
            for(const auto & element : boucles){
                Boucle<T> boucle(element, matrix);
                _boucles.insert(boucle);
            }
        }

        /**
         *
         * @return la liste des permutations
         */
        std::list<std::list<T>> genere_permutations(){
            return _loopGenerator -> genere_permutations();
        }

        /**
         *
         * @return la liste des boucles
         */
        std::list<std::list<T>> genere_boucle(){
            return _loopGenerator ->genere_boucle();
        }

        /**
         *
         * @return l'ensemble des boucles chacune associée à son poids.
         */
        std::set<Boucle<T>> distances_boucles(){
            return _boucles;
        }

        /**
         *
         * @return la boucle ayant la plus petite distance(meilleur chemin). Elle correspond à la question 5 du sujet.
         */
        Boucle<T> meilleure_boucle(){
            typename std::set<Boucle<T>>::const_iterator it = _boucles.cbegin();
            std::advance(it, 0);
            return *it;
        }

        virtual ~DistanceGenerator(){}
};

#endif //TEST_CPP_DISTANCEGENERATOR_H
