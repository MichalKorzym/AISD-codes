#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <time.h>
const int N = 100;

using namespace std;
struct przelewy { //struktura zadanie 4
	int kwota;
	string tytul;
	int z_rach;
	int na_rach;
};
struct skoczek { //struktura zadanie 2
	string nazwisko;
	string czas;

};


struct node {   
	node* next;
	float value;
};

//zadanie 1
void swap(int* i1, int* i2) //SWAP WYKORZYSTANY W  ZADANIU 1
{
	int tmp = *i1;
	*i1 = *i2;
	*i2 = tmp;
}
int partition(int tab[], int min, int max)
{
	int pivot = tab[max];
	int i = (min - 1);

	for (int j = min; j <= max - 1; j++)
	{
		if (tab[j] < pivot)
		{
			i++;
			swap(&tab[i], &tab[j]);
		}
	}
	swap(&tab[i + 1], &tab[max]);
	return (i + 1);
}
void quickSort(int tab[], int min, int max)
{
	if (min < max)
	{
		int part = partition(tab, min, max);
		quickSort(tab, min, part - 1);
		quickSort(tab, part + 1, max);
	}
}

int findMinDiff(int tab[], int size, int dzieci)
{


	int min_difference = INT_MAX;

	int first = 0, last = 0;
	for (int i = 0; i + dzieci - 1 < size; i++)
	{
		int difference = tab[i + dzieci - 1] - tab[i];
		if (difference < min_difference)
		{
			min_difference = difference;
			first = i;
			last = i + dzieci - 1;
		}
	}
	return (tab[last] - tab[first]);
}
//zadanie2
void addTab(skoczek tab[], skoczek*& s, int i) {

	tab[i].czas = s->czas;
	tab[i].nazwisko = s->nazwisko;


}

int partition(skoczek tab[], int low, int high)
{
	float pivot = atoi(tab[high].czas.c_str());
	int i = (low - 1);
	for (int j = low; j <= high - 1; j++) {
		if (atoi(tab[j].czas.c_str()) >= pivot) {
			i++;
			swap(tab[i], tab[j]);
		}
	}
	swap(tab[i + 1], tab[high]);
	return (i + 1);
}

int FindEl(skoczek tab[], int left, int right, int szukana)
{

	while (left <= right) {


		int pivotIndeks = partition(tab, left, right);

		if (pivotIndeks == szukana - 1)
			return pivotIndeks;


		else if (pivotIndeks > szukana - 1)
			right = pivotIndeks - 1;


		else
			left = pivotIndeks + 1;
	}
	return -1;
}
//zadanie 3
void addNode3(node*& HEAD, int A, int B, int C) {
	cout << "Podaj ilosc argumentow x" << endl;
	cout << "Argumenty podawaj w porzadku rosnacym!" << endl;
	int il;
	cin >> il;
	int x;
	for (int i = 0; i < il; i++) {
		cout << "Podaj wartosc argumentu x" << endl;
		cin >> x;
		node* tmp = new node();
		tmp->value = (A * (x * x)) + B * x + C;
		tmp->next = HEAD;
		HEAD = tmp;
	}



}

void printNode3(node* head) {
	node* tmp = head;
	while (tmp) {
		cout << tmp->value << "  ";
		tmp = tmp->next;
	}
}


//zadanie 4
void addTAB4(przelewy tab[]) {
	string nazwa;
	int p = 1000000;
	int k = 1000000;
	for (int i = 0; i < 10000; i++) {
		tab[i].kwota = rand() % 10001;
		tab[i].na_rach = (rand() % p) + k;
		tab[i].z_rach = (rand() % p) + k;
		for (int i = 0; i < 10; i++) {
			string tyt;
			tyt = ((rand() % ('z' + 1 - 'a')) + 'a');
			nazwa = tyt + nazwa;
		}
		tab[i].tytul = nazwa;
		nazwa = ' ';
	}
}
int partition4(przelewy tab[], int low, int high)
{
	int pivot = tab[high].kwota;
	int i = (low - 1);
	for (int j = low; j <= high - 1; j++) {
		if (tab[j].kwota >= pivot) {
			i++;
			swap(tab[i], tab[j]);
		}
	}
	swap(tab[i + 1], tab[high]);
	return (i + 1);
}

int FindEl4(przelewy tab[], int left, int right, int szukana)
{

	while (left <= right) {


		int pivotIndeks = partition4(tab, left, right);

		if (pivotIndeks == szukana - 1)
			return pivotIndeks;


		else if (pivotIndeks > szukana - 1)
			right = pivotIndeks - 1;


		else
			left = pivotIndeks + 1;
	}
	return -1;
}



//zadanie 5
void printNode(node* head) {
	node* tmp = head;
	while (tmp) {
		cout << tmp->value << "  ";
		tmp = tmp->next;
	}
}
void addNode(node*& head) {
	cout << "PODAJ WARTOSCI ELEMENTOW LISTY, DO POLOWY WARTOSCI ROSNACE A NASTEPNIE MALEJACE" << endl;
	cout << "ilosc elementow listy " << endl;
	int il;
	int x;
	cin >> il;
	for (int i = 0; i < il; i++) {
		cout << "Wartosc elementu listy" << endl;
		cin >> x;
		node* tmp = new node();
		tmp->value = x;
		tmp->next = head;
		head = tmp;
	}
}
void dzielenie(node* head, node** l1, node** l2) {
	node* lewa = head;
	node* prawa = head->next;
	while (prawa != NULL) {
		prawa = prawa->next;
		if (prawa) {
			lewa = lewa->next;
			prawa = prawa->next;
		}
	}
	*l1 = head;
	*l2 = lewa->next;
	lewa->next = NULL; //odlaczanie

}
node* scalanie(node* l1, node* l2) { //LACZENIE PODLIST
	node* newhead = NULL;
	if (l1 == NULL) {
		return l2;              //JEDNA Z LIST JEST PUSTA
	}
	if (l2 == NULL) {
		return l1;
	}
	if (l1->value < l2->value) {
		newhead = l1;
		newhead->next = scalanie(l1->next, l2);
	}
	else
	{
		newhead = l2;
		newhead->next = scalanie(l1, l2->next);
	}
	return newhead;
};
node* reverseNode(node* ptr)
{
	node* temp;
	node* previous = NULL;
	while (ptr != NULL) {
		temp = ptr->next;
		ptr->next = previous;
		previous = ptr;
		ptr = temp;
	}
	return previous;
}

//zadanie 3 
void mergeSort(node** head) {
	node* HEAD = *head;
	node* l1;
	node* l2;
	if (HEAD == NULL || HEAD->next == NULL) { // 0 /1 element
		return;
	}

	dzielenie(HEAD, &l1, &l2); //dzielenie na polowki
	// sortowanie polowek 
	mergeSort(&l1);
	mergeSort(&l2);
	// laczenie tych polowek 
	*head = scalanie(l1, l2);
	return;
}

int main() {
	srand(time(NULL));

	//zadanie 1
	int dzieci;
	cout << "Podaj liczbe dzieci wsrod ktorych maja byc rozdzielone pudelka czekoladek" << endl;
	cin >> dzieci;
	cout << "Podaj ilosc paczek czekoladek do rozdysponowania " << endl;
	int il_paczek;
	cin >> il_paczek;
	int tab_packets[N];
	int czekoladki;
	for (int i = 0; i < il_paczek; i++) {
		cout << "Podaj ilosc czekoladek w paczce" << endl;
		cin >> czekoladki;
		tab_packets[i] = czekoladki;
	}

	quickSort(tab_packets, 0, il_paczek - 1);
	cout << "Minimalna roznica miedzy paczka z najwieksza iloscia czekoladek , a paczka z najmniejsza iloscia czekoladek wynosi:  " << findMinDiff(tab_packets, il_paczek, dzieci) << endl;
	//zadanie2

	skoczek tab[30];
	int i = 0;
	fstream plik;
	string linia;
	plik.open("skiing.txt", ios::in);
	while (!plik.eof()) {

		skoczek* sk = new skoczek();
		getline(plik, sk->nazwisko, ' ');
		getline(plik, sk->czas);
		addTab(tab, sk, i);
		i++;
	}
	plik.close();
	int n = sizeof(tab) / sizeof(tab[0]);
	cout << "Podaj pozycje skoczka " << endl;
	int k;
	cin >> k;
	if (k > 27) {
		cout << "Podales za daleka pozycje " << endl;
	}
	else {

		cout << tab[FindEl(tab, 0, n - 1, k)].czas << " " << tab[FindEl(tab, 0, n - 1, k)].nazwisko << endl;
	}

	//zadanie 3
	node* HEAD3 = NULL;
	int a, b, c;
	cout << "Podaj parametry funkcji kwadratowej a,b oraz c" << endl;
	cin >> a >> b >> c;
	addNode3(HEAD3, a, b, c);
	cout << "Lista podana na wejsciu " << endl;
	printNode3(HEAD3);
	cout << endl;
	cout << "Lista posortowana" << endl;
	mergeSort(&HEAD3);
	printNode3(HEAD3);
	cout << endl;

	//ZADANIE 4
	przelewy tab4[10000];
	addTAB4(tab4);
	int n4 = sizeof(tab4) / sizeof(tab4[0]);



	int granica = tab4[FindEl4(tab4, 0, n4 - 1, 1000)].kwota;
	cout << "1000 PRZELEWOW O NAJWIEKSZEJ KWOCIE " << endl;
	int j = 0;
	for (int i = 0; i < 10000; i++) {
		if (tab4[i].kwota >= granica) {
			cout << "Tytul przelewu " << tab4[i].tytul << " kwotwa przelewu " << tab4[i].kwota <<" z rachunku "<< tab4[i].z_rach<<" na rachunek "<< tab4[i].na_rach<< endl;
			j++;
		}
	}


	//zadanie 5
	node* HEAD5 = NULL;
	addNode(HEAD5);
	node* p1;
	node* p2;
	cout << "Lista przed odwroceniem i z mergowaniem " << endl;
	printNode(HEAD5);
	dzielenie(HEAD5, &p1, &p2);
	node* revp2 = reverseNode(p2);
	cout << endl;
	node* newhead5 = scalanie(p1, revp2);
	cout << "Po posortowaniu" << endl;
	printNode(newhead5);



	system("pause");
	return 0;
}