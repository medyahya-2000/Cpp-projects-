//
//  listImpl.h
//
//  Auteur : Jean Goulet
//  Copyleft  2017 UdeS
//
//  Modifie par : Vincent Ducharme, Automne 2022
//
//  Devoir fait par
//     Coéquipier 1 : Vincent Beaudoin
//     Coéquipier 2 : Mohamed Yahya

#ifndef listImpl_h
#define listImpl_h

//////////////////////////////////////////////////////////////
//fonctions generatrices privees
//////////////////////////////////////////////////////////////

template <typename TYPE>
typename list<TYPE>::cellule* list<TYPE>::insert(cellule* c, const TYPE& VAL)
{  
    cellule* prec = c->m_prec;
    cellule* newCell = c->m_prec = new cellule(VAL, c, prec);
    newCell->m_suiv = c;
    if (prec == nullptr)
    {
        m_debut = newCell;
    }
    else
    {
        prec->m_suiv = newCell;
        newCell->m_prec = prec;
    }
    m_size++;
    return newCell;
}
template <typename TYPE>
typename list<TYPE>::cellule* list<TYPE>::erase(cellule* c)
{
    if (c == &m_apres)
        return c;

    cellule* avant = c->m_prec;
    cellule* apres = c->m_suiv;

    if  (c == m_debut)
    {
        m_debut = apres;
        apres->m_prec = nullptr;
    }
    else
    { 
        avant->m_suiv = apres;
        apres->m_prec = avant;
    }

    delete c;
    m_size--;
    return apres;
}


//////////////////////////////////////////////////////////////
//reverse_iterator
//////////////////////////////////////////////////////////////

template <typename TYPE>
class list<TYPE>::reverse_iterator
{
    friend class list<TYPE>;
    cellule* m_pointeur = nullptr;
    reverse_iterator() = default;
    reverse_iterator(cellule* c) :m_pointeur(c) {}
public:
    TYPE& operator*()const { return m_pointeur->m_prec->m_contenu; }
    TYPE* operator->()const { return &(m_pointeur->m_prec->m_contenu); }
    reverse_iterator& operator++()
    {
        m_pointeur = m_pointeur->m_prec;
        return *this;
    } //++i
    reverse_iterator operator++(int)
    {
        reverse_iterator ri(*this);
        operator++();
        return ri;
    } //i++

    reverse_iterator& operator--()
    {
        m_pointeur = m_pointeur->m_suiv;
        return *this;
    }

    reverse_iterator operator--(int)
    {
        reverse_iterator ri(*this);
        operator--();
        return ri;
    } // i--

    bool operator==(const reverse_iterator& droite)const
    {
        return m_pointeur == droite.m_pointeur;
    }
    bool operator!=(const reverse_iterator& droite)const
    {
        return !(*this == droite);
    }
};

template <typename TYPE>
typename list<TYPE>::reverse_iterator list<TYPE>::rbegin()
{
    return reverse_iterator(&m_apres);
}


template <typename TYPE>
typename list<TYPE>::reverse_iterator list<TYPE>::rend()
{
    return reverse_iterator(m_debut);
}

///////////////////////////////////////////////////////////
//affectateur
///////////////////////////////////////////////////////////

template <typename TYPE>
list<TYPE>& list<TYPE>::operator=(const list<TYPE>& droite)
{
    clear();
    for(const_iterator i = droite.cbegin(); i != droite.cend(); i++)
    {
        push_back(*i);
    }
    return *this;
}


///////////////////////////////////////////////////////////
//algorithme reverse
///////////////////////////////////////////////////////////

template <typename TYPE>
void list<TYPE>::reverse()
{
    cellule* temp = m_debut;
    while (temp != &m_apres) {
        std::swap(temp->m_suiv, temp->m_prec);
        // On veut aller vers le suivant, mais on vient d'inverser les pointeurs
        temp = temp->m_prec;
    }

    m_apres.m_prec->m_suiv == nullptr;
    m_debut->m_suiv = &m_apres;
    std::swap(m_debut, m_apres.m_prec);
}



#endif // listImpl_h
