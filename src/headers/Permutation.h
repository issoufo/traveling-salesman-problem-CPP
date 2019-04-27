//
// Created by imoussaousmane on 13/12/2018.
//

#ifndef TEST_CPP_PERMUTATION_H
#define TEST_CPP_PERMUTATION_H


#include <list>
#include <iostream>
#include "Point.h"

/**
 * @description génère toutes les permutations possibles d'une liste d'éléments. Elle correspond à la question 2 du sujet.
 * @tparam T type d'éléments
 */
template<typename T>
class Permutation {

    private:
        int _numberOfNodes;
        int _numberOfElements;
        std::list<T> _data;
        std::list<std::list<T>> _result = {};

        /*Au délà de 7 éléments, cette fonction prend énormement de temps à répondre(j'ai attendu plus d'une heure de temps sans réponse).
         * std::list<std::list<T>> getPermutations(int index){
            //std::cout << "Debut de la generation des permutations." << std::endl;
            for (int i = index; i < _data.size(); i++) {
                typename std::list<T>::iterator it1 = _data.begin();
                typename std::list<T>::iterator it2 = _data.begin();
                advance(it1, i);
                advance(it2, index);
                if(i != index){
                    std::swap(*it1, *it2);
                    _result.push_back(_data);
                }
                getPermutations(index + 1);
                //std::cout << "Fin de la generation des permutations." << std::endl;
                std::swap(*it1, *it2);
            }
            return _result;
        }*/

    public:
        /**
         * @description constructeur pour les types simples(des ints)
         * @param numberOfNodes nombre d'éléments
         */
        explicit Permutation(T numberOfNodes): _numberOfNodes(numberOfNodes), _numberOfElements(_numberOfNodes){
            if(_numberOfNodes <= 1){
                 throw std::invalid_argument("received negative value");
            }
            std::list<T> elements(_numberOfNodes);
            _data.merge(elements);

            int number = 0;
            std::generate(_data.begin(), _data.end(), [&number](){
                return number++;
            });

            _result.push_back(_data);
        }

        /**
         * @description constructeur pour les containeurs(list)
         * @param points liste des points
         */
        explicit Permutation(std::list<T> points): _data(points), _numberOfElements(points.size()){
            _result.push_back(points);
        }

        /**
         *
         * @return toutes les permutations
         */
        std::list<std::list<T>> genere_permutations(){
            if(_result.size() > _data.size()){
                return _result;
            }

            while (std::next_permutation(_data.begin(), _data.end())){
                _result.push_back(_data);
            }
            return genere_permutations();
        }

        virtual ~Permutation(){}
};


#endif //TEST_CPP_PERMUTATION_H
