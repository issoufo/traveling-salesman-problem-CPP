//
// Created by imoussaousmane on 26/12/2018.
//

#ifndef TEST_CPP_LOOPGENERATOR_H
#define TEST_CPP_LOOPGENERATOR_H

#include <memory>
#include <list>
#include <algorithm>
#include <iostream>
#include "Permutation.h"

/**
 * @description génère toutes les boucles hamiltoniennes possibles d'origine et d'arrivé depart. Elle correspond à la question 3 du sujet.
 * @tparam T type d'éléments
 */
template<typename T>
class LoopGenerator {

    private:
        std::unique_ptr<Permutation<T>> _permutation = nullptr;
        T _depart;

        std::list<T> loop(std::list<T> list1, std::list<T> list2, T depart){
            ptrdiff_t position = distance(list1.begin(), find(list1.begin(), list1.end(), depart));
            std::list<T> boucle = {};
            boucle.assign(std::next(list1.begin(), position), list1.end());
            for(const auto& element : list2){
                typename std::list<T>::const_iterator it = std::find(boucle.cbegin(), boucle.cend(), element);
                if(it == boucle.cend() && element != depart){
                    boucle.push_back(element);
                }
            }
            boucle.push_back(depart);
            return boucle;
        }

    public:

        /**
         * @description constructeurs pour les élements simples(int par exemple)
         * @param n nombre d'éléments
         * @param depart point de depart
         */
        explicit LoopGenerator(T n, T depart): _permutation(std::make_unique<Permutation<T>>(n)), _depart(depart){
            if(depart >= n){
                throw std::invalid_argument("Departure can't be superior or equals to number of nodes.");
            }
        }

        /**
        * @description constructeurs pour les conteneurs d'éléments (list)
        * @param n nombre d'éléments
        * @param depart point de depart
        */
        explicit LoopGenerator(std::list<T> elements, T depart): _permutation(new Permutation<T>(elements)), _depart(depart){
            typename std::list<T>::const_iterator it = std::find(elements.cbegin(), elements.cend(), depart);
            if(it == elements.cend()){
                throw std::invalid_argument("Departure must exist in list of nodes.");
            }
        }

        /**
         *
         * @return toutes les boucles hamiltoniennes possibles.
         */
        std::list<std::list<T>> genere_boucle() {
            auto elements = _permutation -> genere_permutations();
            std::list<std::list<T>> boubles = {};
            int size = elements.size();

            for(int i = 0; i < size; i++){
                typename std::list<std::list<T>>::const_iterator it1 = elements.cbegin();
                typename std::list<std::list<T>>::const_iterator it2 = elements.cbegin();
                int it2Position = i+1;
                if(it2Position < size){
                    std::advance(it1, i);
                    std::advance(it2, it2Position);
                    std::list<T> aLoop = loop(*it1, *it2, _depart);
                    typename std::list<std::list<T>>::const_iterator it = std::find(boubles.cbegin(), boubles.cend(), aLoop);
                    if(it == boubles.cend()){
                        boubles.push_back(aLoop);
                    }
                }
            }
            return boubles;
        }

        /**
         *
         * @return toutes les permutations possibles
         */
        std::list<std::list<T>> genere_permutations(){
            return _permutation -> genere_permutations();
        }

        virtual ~LoopGenerator(){}
};

#endif //TEST_CPP_LOOPGENERATOR_H
