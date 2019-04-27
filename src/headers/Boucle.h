//
// Created by imoussaousmane on 27/12/2018.
//

#ifndef TEST_CPP_DISTANCEBOUCLE_H
#define TEST_CPP_DISTANCEBOUCLE_H

#include <list>
#include "Edge.h"
#include "PvcNameSpace.h"

/**
 * @description réprésente une boucle(un chemin)
 * @tparam T type d'éléments de la boucle
 */
template<typename T>
class Boucle {

    private:
        std::list<T> _boucle;
        double _distance = 0.0;

    public:
        /**
         * @description calcul la distance d'une boucle
         * @param boucle liste d'éléments
         * @param matrix matrice des poids
         */
        Boucle(std::list<T> boucle, std::list<Edge<T>> matrix): _boucle(boucle){
            for(int i = 0; i < boucle.size(); i++){
                typename std::list<T>::const_iterator it1 = cbegin(_boucle);
                typename std::list<T>::const_iterator it2 = cbegin(_boucle);
                std::advance(it1, i);
                std::advance(it2, i+1);
                Edge<T> edge(*it1, *it2);
                typename std::list<Edge<T>>::const_iterator edgeFound = std::find(matrix.cbegin(), matrix.cend(), edge);
                if(edgeFound != matrix.cend()){
                    _distance += (*edgeFound).getWeight();
                }
            }
        }

        double getDistance() const {
            return _distance;
        }

        std::list<T> getElements() const {
            return _boucle;
        }

        bool operator<(const Boucle & boucle) const {
            return _distance <= boucle._distance;
        }

        friend std::ostream & operator<<(std::ostream & os, const Boucle & boucle) {
            pvc_name_space::showList(boucle._boucle);
            os << " : " << boucle._distance << std::endl;
            return os;
        }
};


#endif //TEST_CPP_DISTANCEBOUCLE_H
