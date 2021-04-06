#include <iostream>
#include <limits.h>
using namespace std;
string tab_miasta[9] = { "Wilno","Uciana","Mariampol","Kowno","Poniewiez","Szawle","Taurogi","Klajpeda","Butynga" };

struct s_list
{
    s_list* next;
    int numer, waga;
    string nazwa
};


//FORD

struct edge {
    int source;
    int destination;

};



int main()
{
    int k,j;
    bool* tab_QS;           // Zbiory Q i S
    s_list** graf_tab;     // Tablica list s¹siedztwa
    s_list* tmp, *tmp2;

    int* cost_tab, * prev_tab;
    cout << "Podaj wierzcholek startowy ,liczbe wierzcholkow oraz liczbe krawedzi" << endl;
    int start;
    int liczba_wierzcholkow, liczba_krawedzi;
    cin >> start >>liczba_wierzcholkow >> liczba_krawedzi; 

    // tworzenie tablic

   cost_tab = new int[liczba_wierzcholkow];         
    prev_tab = new int[liczba_wierzcholkow];          
    tab_QS = new bool[liczba_wierzcholkow];        
    graf_tab = new s_list * [liczba_wierzcholkow]; 
    int* stos = new int[n];     

    int stos_ptr= 0;             

    // Inicjujemy tablice dynamiczne

    for (int  i = 0; i < n; i++)
    {

        tab_QS[i] = false;
        graf_tab[i] = NULL;
        cost_tab[i] = INT_MAX;
        prev_tab[i] = -1;
        
    }

    // Odczytujemy dane wejœciowe
    string nazwa1, nazwa2;
    int numer1, numer2;
    int waga;
    for (i = 0; i < m; i++)
    {
        cout << "Podaj numer i nazwe miasta 1 ,nastepnie 2 oraz wage krawedzi " << endl;
        cin >> numer1 >> nazwa1 >> numer2 > nazwa2 >> waga;    
        tmp = new s_list;
        tmp->nazwa = nazwa2;
        tmp->numer = numer2;             
        tmp->waga = waga;            
        tmp->next = graf_tab[numer1];
        tmp->next->nazwa = nazwa2;
        graf[numer1] = tmp;      
    }
    cout << endl;

    cost_tab[start] = 0;

   

    for (int i = 0; i < liczba_wierzcholkow; i++)
    {


        for (j = 0; tab_QS[j]; j++);
        for (k = j++; j < liczba_wierzcholkow; j++)
            if (!tab_QS[j] && (cost_tab[j] < cost_tab[k]))
                k = j;

      

        tab_QS[u] = true;



        for (tmp = graf_tab[k]; tmp; tmp = tmp->next)
            if (!tab_QS[tmp->numer]&& (cost_tab[tmp->numer] > cost_tab[k] + tmp->waga))
            {
                cost_tab[tmp->numer] = cost_tab[k] + tmp->waga;
                prev_tab[tmp->numer] = k;
            }
    }



    for (int i = 0; i < liczba_wierzcholkow; i++)
    {
        cout << tab_miasta[i] << ": ";

        

        for (j = i; j > -1; j = prev_tab[j]) stos[stos_ptr++] = j;
        while (stos_ptr) 
            cout << stos[--stos_ptr] << " ";

        // Na koñcu œcie¿ki wypisujemy jej koszt

        cout << "$" << cost_tab[i] << endl;
    }

    // Usuwamy tablice dynamiczne

    delete[] cost_tab;
    delete[] prev_tab;
    delete[] tab_QS;
    delete[] stos;

    for (int i = 0; i < liczba_wierzcholkow; i++)
    {
        tmp = graf_tab[i];
        while (tmp)
        {
            tmp2 = tmp;
            tmp = tmp->next;
            delete tmp2;
        }
    }

    delete[] graf_tab;



    //FORD



    return 0;
}
