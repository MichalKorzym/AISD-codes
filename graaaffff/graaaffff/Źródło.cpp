#include <iostream>
#include <limits.h>
using namespace std;
//tablica do wyswietlania 
string tab_miasta[9] = { "Wilno","Uciana","Mariampol","Kowno","Poniewiez","Szawle","Taurogi","Klajpeda","Butynga" };
int liczba_wierzcholkow, liczba_krawedzi;

struct s_list    //struktura z odwolaniem do nastepnika numerem wezla i waga krawedzi
{
    s_list* next;
    int numer, waga;
    string nazwa;

};

//FORD

long long* cost_tab_ford; // tablica kosztow dojscia do danego wierzcholka
int* prev_tab_ford; //tablica numerow poprzednikow 
s_list** graf_tab_ford; // dynamiczna tablica  list sasiedztwa 

bool relax(int start_ford) {
    int i, j; //iteratory
    s_list* tmp; //wezel listy
    bool a; 
    cost_tab_ford[start_ford] = 0; //ustawiamy dystans do poczatkowego wezla na 0 
    for (i = 0; i < liczba_wierzcholkow; i++) { //wykonanie relaksacji 
        a = true; // jesli zmienna boolowa jest prawdziwa oznacza to ze nie zostaly wprowadzone zmiany w koszcie i poprzednikach 
        for(j=0;j<liczba_wierzcholkow;j++) //przejscie wierzcholkow 
            for(tmp=graf_tab_ford[j];tmp;tmp=tmp->next) //przejscie listy sasiadow 
                if (cost_tab_ford[tmp->numer] > cost_tab_ford[j] + tmp->waga) //warunek relaksacji 
                {
                    a = false; //zaszla zmiana w koszcie i poprzedniku 
                    cost_tab_ford[tmp->numer] = cost_tab_ford[j] + tmp->waga; // relaksacja z x na sasiada 
                    prev_tab_ford[tmp->numer] = j; //poprzednik sasiada ustawiany jest na j 

                }

        if (a)
            return true; //nie dokonano zmian , konczymy 
    }

    for (j = 0; j < liczba_wierzcholkow; j++) //czy istnieje ujemny cykl , jesli tak zwracany jest falsz i wyswietlany komunikat 
        for (tmp = graf_tab_ford[j]; tmp; tmp = tmp->next)
            if (cost_tab_ford[tmp->numer] > cost_tab_ford[j] + tmp->waga)
                return false;


}

int main()
{
    int k, j ;//zmienne do iteracji 
    bool* tab_QS;           // zbiory z wierzcholkami 
    s_list** graf_tab;     //tablica przechowujaca listy sasiedztwa
    s_list* tmp, * tmp2; // wskazniki do tworzenia wezlow 

    int* cost_tab, * prev_tab; //kolejno tablica zawierajaca koszty przejscia trasy i numery poprzednikow 
    cout << "Podaj wierzcholek startowy ,liczbe wierzcholkow oraz liczbe krawedzi" << endl;
    int start; //wierzcholek startowy 

    cin >> start >> liczba_wierzcholkow >> liczba_krawedzi;

    // tworzenie tablic

    cost_tab = new int[liczba_wierzcholkow]; //tablica kosztow 
    prev_tab = new int[liczba_wierzcholkow];// tablica poprzendnikow
    tab_QS = new bool[liczba_wierzcholkow]; //tablica zbiorow 
    graf_tab = new s_list * [liczba_wierzcholkow]; //tablica list sasiedztwa
    int* stos = new int[liczba_wierzcholkow]; //stoos

    int stos_ptr = 0;  //wskaznik stosu 

    // Inicjujemy tablice dynamiczne 

    for (int i = 0; i < liczba_wierzcholkow; i++)
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
    for (int i = 0; i < liczba_krawedzi; i++)
    {
        cout << "Podaj numer i nazwe miasta 1 ,nastepnie 2 oraz wage krawedzi " << endl;
        cin >> nazwa1 >> numer1 >> nazwa2 >> numer2 >> waga; //numery krawedzi nazwy miast i waga krawedzi 
      /*  tmp = new s_list;
        tmp->nazwa = nazwa2;
        tmp->numer = numer2;
        tmp->waga = waga;
        tmp->next = graf_tab[numer1];
        graf_tab[numer1] = tmp;
        */
        tmp = new s_list; //tworzenie elementu listy sasiedztwa 
        tmp->numer = numer2; // wiecholek destynacji
        tmp->nazwa = nazwa2; //przypisanie nazwy
        tmp->waga =waga; // przypisanie wagi 
        tmp->next = graf_tab[numer1];
        graf_tab[numer1] = tmp; //dolaczenie elementu do listy

        tmp = new s_list;
        tmp->numer = numer1;
        tmp->nazwa = nazwa1;
        tmp->waga = waga;
        tmp->next = graf_tab[numer2];
        graf_tab[numer2] = tmp;
    }

    cout << endl;

    cost_tab[start] = 0; // ustalamy ze koszt dojscia do startowego wierzchloka wynosi 0 

    for (int i = 0; i < liczba_wierzcholkow; i++) //szukamy w zbiorze Q wierzcholka o najmniejszej wadze a nastepnie przenosimy go do zbioru S 
    {


        for (j = 0; tab_QS[j]; j++);
        for (k = j++; j < liczba_wierzcholkow; j++)
            if (!tab_QS[j] && (cost_tab[j] < cost_tab[k]))
                k = j;



        tab_QS[k] = true;


        //uaktualnianie sasiadow 
        for (tmp = graf_tab[k]; tmp; tmp = tmp->next)
            if (!tab_QS[tmp->numer] && (cost_tab[tmp->numer] > cost_tab[k] + tmp->waga))
            {
                cost_tab[tmp->numer] = cost_tab[k] + tmp->waga;
                prev_tab[tmp->numer] = k;
            }
    }
    //wyswietlenie wynikow 
    cout << "Szukamy najkrotszych drog od wierzcholka  " << tab_miasta[start] << endl;

    for (int i = 0; i < liczba_wierzcholkow; i++)
    {
        cout << tab_miasta[i] << ": ";



        for (j = i; j > -1; j = prev_tab[j]) stos[stos_ptr++] = j; //zapisujemy poprzednikow z tablicy prev_tab na stosie a nastepnie wypisujemy kolejne numery wierzcholkow sciagajac je ze stosu
        while (stos_ptr)
            cout << stos[--stos_ptr] << " ";

        // Na koñcu œcie¿ki wypisujemy jej koszt

        cout << "$waga$" << cost_tab[i] << endl; // wyswietlenie wagi sciezki
    }

    // Usuwamy tablice dynamiczne
    cout << endl << endl;
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
    prev_tab_ford = new int[liczba_wierzcholkow]; //tablica przechowujaca poprzendnikow
    graf_tab_ford = new s_list * [liczba_wierzcholkow]; //tablica list sasiedztwa
    cost_tab_ford = new long long [liczba_wierzcholkow]; //tablica kosztow przejscia
    s_list* tmp3, * tmp4; //zmienne pomocnicze wezlow 
    //inicjacja tablic
    for (int i = 0; i < liczba_wierzcholkow; i++) {
        prev_tab_ford[i] = -1;
        graf_tab_ford[i] = NULL;
        cost_tab_ford[i] = INT_MAX;
    }
    
    for (int i = 0; i < liczba_krawedzi; i++) {

        cout << "Podaj numer i nazwe miasta 1 ,nastepnie 2 oraz wage krawedzi " << endl;
        cin >> nazwa1 >> numer1 >> nazwa2 >> numer2 >> waga;
      /*  tmp3 = new s_list;
        tmp3->nazwa = nazwa2;
        tmp3->numer = numer2;
        tmp3->waga = waga;
        tmp3->next = graf_tab_ford[numer1];
        graf_tab_ford[numer1] = tmp3;
        */
        tmp3 = new s_list;
        tmp3->numer = numer2;
        tmp3->nazwa = nazwa2;
        tmp3->waga = waga;
        tmp3->next = graf_tab_ford[numer1];
        graf_tab_ford[numer1] = tmp3;

        tmp3 = new s_list;
        tmp3->numer = numer1;
        tmp3->nazwa = nazwa1;
        tmp3->waga = waga;
        tmp3->next = graf_tab_ford[numer2];
        graf_tab_ford[numer2] = tmp3;

    }
   
    cout << endl;
    int* stos_ford;
    int s_ford_ptr;
    cout << "Szukamy najkrotszych drog od wierzcholka  " << tab_miasta[start] << endl;
    if (relax(start))
    {
        stos_ford = new int[liczba_wierzcholkow]; // tworzenie stosu
        s_ford_ptr = 0;

        for (int i = 0; i < liczba_wierzcholkow; i++) {
            cout << tab_miasta[i] << ": ";

            for (int j = i; j != -1; j = prev_tab_ford[j]) //umieszczenie wierzcholkow ze sciezki na stosie (kolejnosc od ostatniego do pierwszego)
                stos_ford[s_ford_ptr++] = j;
            while (s_ford_ptr)
                cout << stos_ford[--s_ford_ptr] << "  "; //wyswietlanie wierzcholkoow od 1 do ostatniego 
            cout << "$waga$" << cost_tab_ford[i] << endl; //wyswietlenie kosztow 



        }
        delete[]stos_ford; //usuniecie stosu 
    }
    else
        cout << "SCIEZKA MA UJEMNA WAGE !!!" << endl; //wyswietlenie informacji o tym ze ktoras ze sciezek ma ujemna wage 

    // usuniecie struktur dynamicznych
    for (int i = 0; i < liczba_wierzcholkow; i++)
    {
        tmp3 = graf_tab_ford[i];
        while (tmp3)
        {
            tmp4 = tmp3;
            tmp3 = tmp3->next;
            delete tmp4;
        }
    }

    delete[] graf_tab_ford;
    delete[] prev_tab_ford;
    delete[] cost_tab_ford;



    system("pause");
    return 0;
}
