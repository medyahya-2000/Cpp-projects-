//
//  setImpl.h
//  SkipList
//
//  Jean Goulet 2017
//
//  Devoir fait par
//     Coéquipier 1 : Vincent Beaudoin
//     Coéquipier 2 : Mohamed Yahya
//

#ifndef SkipList_set2_h
#define SkipList_set2_h

/////////////////////////////////////////////////////////////////
// copieur et destructeur de liste

template <typename TYPE>
set<TYPE>::set(const set<TYPE>& src)
    : set()
{
	for (auto it = src.begin(); it != src.end(); it++)
	{
		insert(m_avant->m_prec[0], *it);
	}
}

template <typename TYPE>
set<TYPE>::~set()
{
	clear();
	delete m_avant->m_suiv[0];
	delete m_avant;
	m_avant = nullptr;
}

/////////////////////////////////////////////////////////////////
// find
// localise un élément, retourne la fin si absent

template <typename TYPE>
typename set<TYPE>::iterator set<TYPE>::find(const TYPE& x)
{
	iterator it = lower_bound(x);
	if (!(it == end() || *it < x || x < *it))
		return it;
	return end();
}

// lower_bound
// localise la premiere position ou l'element n'est
// pas plus petit que celui recu en parametre

template <typename TYPE>
typename set<TYPE>::iterator set<TYPE>::lower_bound(const TYPE& t)
{
	// RÉFÉRENCE: Notes de cours p.91 + Notes de cours personnelles
	cellule* c = m_avant;
	size_t i = c->m_suiv.size();
	while (i > 0)
	{
		i--;
		while (c->m_suiv[i] != m_avant->m_prec[0])
		{
			if (!(*c->m_suiv[i]->m_contenu < t))
				break;
			c = c->m_suiv[i];
		}
	}
	return iterator(c->m_suiv[0]);
}

template <typename TYPE>
typename set<TYPE>::iterator set<TYPE>::upper_bound(const TYPE& x)
{
	iterator it = lower_bound(x);
	if (!(it == end() || *it < x || x < *it))
		it++;
	return it;
}

/////////////////////////////////////////////////////////////////
// erase(VAL)
// elimine VAL de l'ensemble, si present

template <typename TYPE>
size_t set<TYPE>::erase(const TYPE& VAL)
{
	iterator it = find(VAL);
	if (it == end())
		return 0;
	erase(it);
	return 1;
}

// erase(it)
// elimine de l'ensemble l'element en position it

template <typename TYPE>
typename set<TYPE>::iterator set<TYPE>::erase(iterator it)
{
	cellule* c = it.m_pointeur;
	cellule* suivant = c->m_suiv[0];
	cellule* apres = m_avant->m_prec[0];
	size_t size = c->m_suiv.size();
	
	size_t i = size;
	while (i > 0)
	{
		i--;
		c->m_prec[i]->m_suiv[i] = c->m_suiv[i];
		c->m_suiv[i]->m_prec[i] = c->m_prec[i];
	}
	if (size > 1 && m_avant->m_suiv[size - 1] == apres)
	{
		m_avant->m_suiv.pop_back();
		apres->m_prec.pop_back();
	}
	delete c;
	m_size--;

	return iterator(suivant);
}

#endif
