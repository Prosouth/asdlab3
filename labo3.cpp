/*
 * Algorithmes et Structures de données
 * 
 * Auteurs : Corazza Erick, Saez Sébastien et Cristi Kevin
 * Date : 09.04.2017
 * Source : labo3.cpp
 * 
 * Ce programme a pour but de tester empiriquement 3 différents tris:
 * - le selection sort
 * - le quick sort
 * - le tri par comptage (counting sort)
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <iomanip>
using namespace std;
using namespace std::chrono;

//##############COUNTING SORT##########################
// countingSort
//
// Effectue le tri comptage des éléments entre begin
// et end (non inclus). Les éléments pointés par ces
// itérateurs doivent être de type entier (char, short, int, long).
// Calcule les min et max des éléments pour déterminer
// le tableau de compteurs à allouer. Affiche dans l'ordre
// des éléments croissants et pour chaque élément de
// compte > 0 le nombre d'occurence sous la forme
// E: C
// où E est l'élément et C le compte.
template <typename RandomAccessIterator>
void countingSort(RandomAccessIterator begin,
                  RandomAccessIterator end);


//#####################################################

//################SELECTION SORT#######################

// selectionSort
//
// Effectue le tri par sélection des éléments entre begin
// et end (non inclus). Doit appeler display() après chaque
// échange.
template < typename RandomAccessIterator >
void selectionSort( RandomAccessIterator begin,
                   RandomAccessIterator end);

//########################################################

//#################QUICK SORT#############################

// selectPivot(begin,end)
//
// choisit un pivot pour le tri rapide parmi le tableau
// entre begin et end (non inclus). Calcule la médiane
// entre le premier, le dernier et l'élément central.
// retourne un iterateur du même type que begin et end
// pointant sur la valeur choisie.
template < typename RandomAccessIterator >
RandomAccessIterator selectPivot(const RandomAccessIterator begin,
                                 const RandomAccessIterator end);



// quickSort
//
// Effectue le tri rapide des éléments entre begin
// et end (non inclus). Doit appeler selectPivot(...)
// pour le choix du pivot, et display() après chaque
// partition
template <typename RandomAccessIterator>
void quickSort(RandomAccessIterator begin,
               RandomAccessIterator end);
//########################################################



//########################MAIN############################
int main()
{
    const int BORNE_SUPERIEURE = 100;
    const int NB_SIMULATION = 30;
    const int LARGEUR_COLONNE = 20;
    const unsigned int MAX_EXPOSANT = 6;
    const string TAILLE = "Taille";
    const string TEMPS_SEL = "Temps selection";
    const string TEMPS_QUICK = "Temps quick";
    const string TEMPS_COUNT = "Temps comptage";
    
   cout << "#######################################################################"
           "################" << endl; 
   cout << setw(LARGEUR_COLONNE) << TAILLE << setw(LARGEUR_COLONNE) << TEMPS_SEL 
        << setw(LARGEUR_COLONNE) << TEMPS_QUICK << setw(LARGEUR_COLONNE) <<TEMPS_COUNT 
        << endl;

   // Tableaux de 1 à 10⁶
   for (unsigned int exp = 1; exp <= MAX_EXPOSANT; exp++) 
   {
      const unsigned int NB_ELEM = pow(10, exp); // taille basée sur la boucle
      /* srand() only permits a limited range of seeds. Engines in <random> can 
       * be initialized using seed sequences which permit the maximum possible 
       * seed data. seed_seq also implements a common pRNG warm-up.
       
       * On voulait faire avec la librairie random mais on était pas sûr de l'utiliser
       * correctement*/
      srand(exp);
      chrono::high_resolution_clock::time_point t1;
      chrono::high_resolution_clock::time_point t2;

      // On initialise les moyennes à 0
      double averageTimeS = 0, averageTimeQ = 0, averageTimeC = 0;
      for (unsigned int i = 0; i < NB_SIMULATION; i++) 
      {
         //définition de la taille des vecteurs
         vector<int> vectSelect(exp);
         vector<int> vectQuick(exp);
         vector<int> vectCount(exp);

         // On remplit les vecteurs
         for (size_t j = 0; j < NB_ELEM; j++) 
         {
            int item = rand() % BORNE_SUPERIEURE + 1; // de manière aléatoire
            vectSelect.push_back(item); // vecteur pour selection sort
            vectQuick.push_back(item); // vecteur pour quick sort
            vectCount.push_back(item); // vecteur pour counting sort
         }

         // Tris
         // selectionSort         
         t1 = chrono::high_resolution_clock::now();
         selectionSort(vectSelect.begin(), vectSelect.end());
         t2 = chrono::high_resolution_clock::now();
         averageTimeS += chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();

         // Rapide
         t1 = chrono::high_resolution_clock::now();
         quickSort(vectQuick.begin(), vectQuick.end());
         t2 = chrono::high_resolution_clock::now();
         averageTimeQ += chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();

         // Test pour le counting sort en gardant le temps pour le calcul de la moyenne
         t1 = chrono::high_resolution_clock::now();
         countingSort(vectCount.begin(), vectCount.end());
         t2 = chrono::high_resolution_clock::now();
         averageTimeC += chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
      }
      // Affichage des résultats de manière soyeuse
      cout << setw(LARGEUR_COLONNE)<< NB_ELEM << setw(LARGEUR_COLONNE) 
           << averageTimeS / NB_SIMULATION << setw(LARGEUR_COLONNE) 
           << averageTimeQ / NB_SIMULATION << setw(LARGEUR_COLONNE) 
           << averageTimeC / NB_SIMULATION << endl;
      
      cout << "#######################################################################"
              "################" << endl; 
   }
   return EXIT_SUCCESS;
}

//########################################################

template <typename RandomAccessIterator>
void countingSort(RandomAccessIterator begin,
                  RandomAccessIterator end)
{
    int min = *(min_element(begin, end));
    int max = *(max_element(begin, end));    
    const size_t TAILLE_TAB = max - min + 1;
    size_t x = 0;//permettra d'itérer sur le vector
    
    vector<int> tabValeurATrier(begin, end);//tableau des valeurs à trier

    vector<int> tabTrie(tabValeurATrier.size(), 0);//vector de 0 rempli 
    
    vector<int> tabComptage(max-min+1);//remplissage du tableau de comptage de 0    
    
    //remplissage du nombre d'occurences
    for (auto i = begin; i != end; i++) 
    {
        tabComptage.at(*i - min)++;
    }

    for (size_t i = 0; i < TAILLE_TAB; i++) 
    {
        for (size_t j = 0; j < tabComptage.at(i); j++)
        {
            *(begin + x++) = i + min;
        }
    }
}

template <typename RandomAccessIterator>
void selectionSort(RandomAccessIterator begin,
                   RandomAccessIterator end)
{
    for (auto i = begin; i != (end - 1); ++i) 
    {
        auto iMin = i;
        auto j = i + 1;
        while (j != end) 
        {
            if (*j < *iMin) 
            {
                iMin = j;
            }
            ++j;
        }
        swap(*i, *iMin);
    }
}


template < typename RandomAccessIterator >
RandomAccessIterator selectPivot(const RandomAccessIterator begin,
                                 const RandomAccessIterator end)
{
    RandomAccessIterator p1 = begin;
    RandomAccessIterator p2 = begin + ( end-begin ) / 2;
    RandomAccessIterator p3 = end-1;
    
    if(*p1 < *p2) {
        if( *p2 < *p3 ) return p2;
        else if(*p1 < *p3) return p3;
        return p1;
    } 
    else 
    {
        if( *p1 < *p3 ) return p1;
        else if(*p2 < *p3) return p3;
        return p2;
    }
}


template <typename RandomAccessIterator>
void quickSort(RandomAccessIterator begin,
        RandomAccessIterator end)
{
    RandomAccessIterator i;
    RandomAccessIterator j;
    RandomAccessIterator hi = end - 1;

    // Arrêt de la récursivité
    if (end <= begin) 
    {
        return;
    }

    RandomAccessIterator pivot = selectPivot(begin, end); // on sélectionne le pivot
    swap(*pivot, *hi); // on met le pivot à la fin

    i = begin - 1;
    j = hi;
    while (true) // boucle infinie
    {
        do 
        {
            ++i;
        } while (*i < *hi); // éléments à gauche du pivot < à val de i

        do 
        {
            --j;
        } while (j > begin && *j > *hi); // éléments à droite du pivot > à val de j

        if (i >= j) // nécessaire pour ne pas effectuer le dernier swap
        {
            break;
        }
        swap(*i, *j);
    }

    swap(*i, *hi); // on échange i et la valeur tout à droite
    quickSort(begin, i);
    quickSort(i + 1, end);
}