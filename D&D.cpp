/**
 * \file main.cpp
 * \brief  Ce fichier contient un programme de calcul d'attaques pour le jeu Donjons et Dragons
 * \author Vincent Ducharme
 * \author Marie-Flavie Auclair-Fortier
 * \author MOHAMED YAHYA YAHM1101
 * \author Mohamed El Boudrari ELBM1102
 * \date 02/09/2022
*/

#include "generer.h" // fichier contenant la fonction generer

#include <iostream> // Permet de faire les entrees/sorties

using namespace std;

int calculdommagepersonnage(int forcePersonnage, int nbCoupsPersonnage);
int calculdegatspersonnereel(int calculdommagepersonnage, int resistanceMonstre);
int calculpointsviemonsterreel(int pointviemonster, int calculdegatspersonnereel);

int calculdommagemonster(int frocemonster, int maxCoupsMonstre);
int cacluldegatsmonsterreel(int calculdommagemonster, int resistancePersonnage);
int calculpointviepersonnagereel(int pointviepersonnage, int cacluldegatsmonsterreel);

int main()
{
    // declaration des variables

    // Le type de monstre est genere au hasard (entre 1 et 4)
    int typeMonstre{ generer(4) };
    int dommage;
    int forceMonstre;
    int resistanceMonstre;
    int maxCoupsMonstre;
    int degatsreelpersonne;
    int nbCoupsPersonnage;
    int forcePersonnage;
    int resistancePersonnage;
    int degatsreel;
    int dommagepersonne;
    switch (typeMonstre) {
    case 1:
        std::cout << "Vous affrontez la bete" << endl;
        maxCoupsMonstre = 5;
        forceMonstre = 2;
        resistanceMonstre = 3;
        break;

    case 2:
        std::cout << "Vous affrontez le dragon" << endl;
        maxCoupsMonstre = 9;
        forceMonstre = 4;
        resistanceMonstre = 8;
        break;

    case 3:
        std::cout << "Vous affrontez le geant" << endl;
        maxCoupsMonstre = 11;
        forceMonstre = 6;
        resistanceMonstre = 12;
        break;

    case 4:
        std::cout << "Vous affrontez le mort-vivant" << endl;
        maxCoupsMonstre = 3;
        forceMonstre = 15;
        resistanceMonstre = 2;
        break;

    default: // pas suppose arriver
        std::cout << "Il y a erreur" << endl;
        maxCoupsMonstre = 0;
        forceMonstre = 0;
        resistanceMonstre = 0;

        break;
    }

    // 1. Lecture des entrees de la personne qui joue
    std::cout << "********** Personnage **************" << endl;

    // 2. Lecture du nombre de DE d'attaque
    std::cout << endl << "Entrez le nombre de coups (DES pour calculer l'attaque) => ";
    std::cin >> nbCoupsPersonnage;

    // 3. Lecture du nombre de faces du DE d'attaque
    std::cout << endl << "Entrez la force (le nombre de faces des DES d'attaque) => ";
    std::cin >> forcePersonnage;

    // 4. Lecture du nombre de faces du DE d'armure
    std::cout << endl << "Entrez la resistance (le nombre de faces du DE) de l'armure => ";
    std::cin >> resistancePersonnage;

    // *****************************
    // Completez le code ici
    // *****************************


    int pointviepersonnage = 100;
    int pointviemonster = 100;
    int tour = 0;
    

    while (pointviepersonnage > 0 && pointviemonster > 0) {
        tour++; 
        dommagepersonne = calculdommagepersonnage(forcePersonnage, nbCoupsPersonnage);
        dommage = calculdommagemonster(forceMonstre, maxCoupsMonstre);
        degatsreel = cacluldegatsmonsterreel(dommage, resistancePersonnage);
        degatsreelpersonne = calculdegatspersonnereel(dommagepersonne, resistanceMonstre);
        pointviepersonnage = calculpointviepersonnagereel(pointviepersonnage, degatsreel);
        pointviemonster = calculpointsviemonsterreel(pointviemonster, degatsreelpersonne);

        std::cout << endl << "vos points de vie  apres l'attaque: ==>  " << pointviepersonnage;
        std::cout << endl << "points de vie du monster apres l'attaque:==>   " << pointviemonster;
        std::cout << endl << "nombre de tours  : ==> "<<tour;
    }

  
    return 0;
}

int calculdommagepersonnage(int forcePersonnage, int nbCoupsPersonnage) {

    return forcePersonnage * nbCoupsPersonnage;
}

int calculdegatspersonnereel(int dommagepersonne, int resistanceMonstre) {

    return max(0, dommagepersonne - resistanceMonstre);

}

int calculpointsviemonsterreel(int pointviemonster, int calculdegatspersonnereel) {

    return max(0, pointviemonster - calculdegatspersonnereel);

}

int calculdommagemonster(int frocemonster, int maxCoupsMonstre) {

    return  frocemonster * maxCoupsMonstre;

}

int cacluldegatsmonsterreel(int dommage, int resistancePersonnage) {

    return max(0, dommage - resistancePersonnage);
}

int calculpointviepersonnagereel(int pointviepersonnage, int cacluldegatsmonsterreel) {

    return max(0, pointviepersonnage - cacluldegatsmonsterreel);
}