#include <iostream>
#include <utility>
#include <climits>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
using namespace std;

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

// display counting sort
//
// Affiche les valeur entre begin et end (non inclus)
// utilisé uniquement par main, pas par vous.
template <typename RandomAccessIterator>
void display(const RandomAccessIterator begin,
             const RandomAccessIterator end);


//#####################################################

//################SELECTION SORT#######################
// Simple fonction swap générique
template <typename T>
void ourSwap(T& elem1, T& elem2);

// selectionSort
//
// Effectue le tri par sélection des éléments entre begin
// et end (non inclus). Doit appeler display() après chaque
// échange.
template < typename RandomAccessIterator >
void selectionSort( RandomAccessIterator begin,
                   RandomAccessIterator end);

// display
//
// Affiche les valeur entre begin et end (non inclus)
// en entourant de [] les valeurs pointées par it1 et
// it2 (it1<=it2) pour souligner les valeurs échangées
// par le tri par sélection
template <typename RandomAccessIterator>
void display(const RandomAccessIterator begin,
             const RandomAccessIterator it1,
             const RandomAccessIterator it2,
             const RandomAccessIterator end);

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

// display
//
// Affiche les valeur entre begin et end (non inclus)
// en entourant de [] la valeur du pivot située entre
// begin et end.
template <typename RandomAccessIterator>
void display(const RandomAccessIterator begin,
             const RandomAccessIterator pivot,
             const RandomAccessIterator end);


//########################################################

//########################MAIN############################
int main()
{
   

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
        if(tabComptage.at(i) > 0)
        {
            cout << *(begin + x - 1) << ": " << tabComptage.at(i) << endl;
        }
    }
}


template <typename T>
void ourSwap(T& elem1, T& elem2)
{
    T temp = elem1;
    elem1 = elem2;
    elem2 = temp;
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
        ourSwap(*i, *iMin);
        display(begin, i, iMin, end);
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
    } else {
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
        } while (j > begin and *j > *hi); // éléments à droite du pivot > à val de j

        if (i >= j) // nécessaire pour ne pas effectuer le dernier swap
        {
            break;
        }
        swap(*i, *j);
    }

    swap(*i, *hi); // on échange i et la valeur tout à droite

    if (begin != end - 1) 
    {
        display(begin, i, end); // on fait l'affichage
    }

    quickSort(begin, i);
    quickSort(i + 1, end);
}




// Display de counting sort
template <typename RandomAccessIterator>
void display(const RandomAccessIterator begin,
             const RandomAccessIterator end)
{
    for(auto it = begin; it<end; ++it) cout << *it << " ";
    cout << endl;
}

// Display de selection sort
template < typename RandomAccessIterator >
void display(const RandomAccessIterator begin,
             const RandomAccessIterator it1,
             const RandomAccessIterator it2,
             const RandomAccessIterator end)
{
    for(auto it = begin; it<it1; ++it) cout << " " << *it << " ";
    if(it1<end) cout << "[" << *it1 << "]";
    for(auto it = it1+1; it<it2; ++it) cout << " " << *it << " ";
    if(it2<end && it1!=it2) cout << "[" << *it2 << "]";
    for(auto it = it2+1; it<end; ++it) cout << " " << *it << " ";
    cout << endl;
}


// Display de quick sort
template <typename RandomAccessIterator>
void display(const RandomAccessIterator begin,
             const RandomAccessIterator pivot,
             const RandomAccessIterator end)
{
    for(auto it = begin; it<pivot; ++it) cout << *it << " ";
    cout << "[" << *pivot << "] ";
    for(auto it = pivot+1; it<end; ++it) cout << *it << " ";
    cout << endl;
}