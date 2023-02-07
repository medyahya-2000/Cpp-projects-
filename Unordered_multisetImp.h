//
//  unordered_setImpl.h
//  unordered_multiset
//
//  AUteur : Jean Goulet
//  Copyleft 2017
//
//  Modifie par : Vincent Ducharme, Automne 2022
//
//  Devoir fait par
//     Coéquipier 1 :
//     Coéquipier 2 :

#ifndef unordered_multisetImpl_h
#define unordered_multisetImpl_h

#include <vector>
#include <list>
#include <iostream>
using namespace std;


///////////////////////////////////////////
// avancer et reculer un iterateur

template <typename TYPE,typename classe_de_dispersion>
void unordered_multiset<TYPE, classe_de_dispersion>::iterator::avancer()
{
    if (++m_pos == (*m_alv)->end())
    {
        do {
            m_alv++;
        } while (*m_alv == nullptr);
        
        m_pos = (*m_alv)->begin();
    }
}

template <typename TYPE,typename classe_de_dispersion>
void unordered_multiset<TYPE, classe_de_dispersion>::iterator::reculer()
{
    if (m_pos == (*m_alv)->begin())
    {
        do {
            m_alv--;
        } while (*m_alv == nullptr);

        m_pos = --((*m_alv)->end());
    }
    else
        m_pos--;
}

/////////////////////////////////////////////////////////////////////
// fonctions generatrices

template <typename TYPE,typename classe_de_dispersion>
typename unordered_multiset<TYPE,classe_de_dispersion>::iterator
unordered_multiset<TYPE, classe_de_dispersion>::insert(const TYPE& val)
{
    // Temporary variables are avoided because of the possibility of a mid-function rehash
    // Size test
    if (m_size > (m_rep.size() - 1) * m_facteur_max)
        rehash(m_rep.size() * 2 - 1);

    // Insertion
    m_size++;
    size_t alv = disperseur(val) % (m_rep.size() - 1);
    if (m_rep[alv] == nullptr)
        m_rep[alv] = new list<TYPE>();
    m_rep[alv]->push_back(val);
    
    typename unordered_multiset<TYPE, classe_de_dispersion>::iterator retour(std::next(m_rep.begin(), alv), --(m_rep[alv]->end()));
    return retour;
}

template <typename TYPE,typename classe_de_dispersion>
size_t unordered_multiset<TYPE, classe_de_dispersion>::erase(const TYPE& val)
{
    if (m_size == 0)
        return 0;
    size_t deletionCount = count(val);
    if (!deletionCount)
        return 0;

    // Deletion
    size_t alv = disperseur(val) % (m_rep.size() - 1);
    m_rep[alv]->remove(val);
    if (m_rep[alv]->size() == 0)
    {
        delete m_rep[alv];
        m_rep[alv] = nullptr;
    }

    // Size test
    m_size = m_size - deletionCount;
    if (m_size < (m_rep.size() - 1) * m_facteur_min)
        rehash(m_rep.size() / 2 - 1);

    return deletionCount;
}

template <typename TYPE,typename classe_de_dispersion>
typename unordered_multiset<TYPE,classe_de_dispersion>::iterator
unordered_multiset<TYPE, classe_de_dispersion>::erase(typename unordered_multiset<TYPE, classe_de_dispersion>::iterator i)
{
    auto m_alv = i.m_alv;
    auto m_pos = i.m_pos;
    auto suivant = i;
    suivant.avancer();

    // Deletion
    (*m_alv)->erase(m_pos);
    if ((*m_alv)->size() == 0)
    {
        delete *m_alv;
        *m_alv = nullptr;
    }

    // Size test
    m_size--;

    return suivant;
}

#endif // unordered_multisetImpl_h
