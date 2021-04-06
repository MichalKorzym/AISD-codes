#include <iostream>
#include <fstream>
#include<string>
#include <cstdlib>
#include <string>
#include <chrono>

using tp = std::chrono::time_point<std::chrono::system_clock>;
using duration = std::chrono::duration<float>;
using namespace std;

struct ksiazka {
	string tytu³, nazwisko_autora, wydawnictwo;
	int rok_wydania, ilosc_stron;
};
   

struct node {
	node* next;
	ksiazka key;
};


node* hash_tab_list[20]; //tablica list
ksiazka* hash_tab[20]; //tablica struktur

void AddFront(node*& head, ksiazka*& value) {
	node* tmp = new node;
	tmp->key = *value;
	tmp->next = head;
	head = tmp;
}

int CountStringAscii(string str) { //funkcja liczaca wartosc stringa w ASCII
	int count = 0;
	for (int i = 0; i < str.length(); i++) {
		count = count + str[i];
	}
	return count;
}


void zerowanieTablicy()
{
	for (int i = 0; i < 20; i++)
		hash_tab[i] = NULL;
}


int GetHash(int value) { // przydzielanie indeksu
	return value % 21;
}

int GetHash1(ksiazka*& k1) { //hashowanie 1
	int hash = k1->ilosc_stron * k1->rok_wydania;
	return GetHash(hash);
}

int GetHash2(ksiazka*& k2) { //hashowanie 2
	int hash;
	int count_surname = CountStringAscii(k2->nazwisko_autora);
	int count_title = CountStringAscii(k2->tytu³);
	hash = GetHash((count_surname * count_title) + k2->rok_wydania);
	return hash;
}
int GetHash3(ksiazka*& k3) { //hashowanie 3
	int hash;
	hash = k3->ilosc_stron * (CountStringAscii(k3->wydawnictwo) %30);
	return GetHash(hash);
}


// nie modyfikowalem , poniewaz sprawdzalem wszystko liczac recznie nastepnie wyswietlajac indeks ktory mi wyszedl
int findElement(ksiazka*& k,int value)
{
	/*if (hash_tab[GetHash(value)]->ilosc_stron == value)
		return GetHash(value);*/
	if (hash_tab[GetHash2(k)]->ilosc_stron== value)
		return GetHash2(k);
	else
	{
		int i = GetHash2(k) + 1;
		
		while (i < 20) 
		{
			if (hash_tab[i]->ilosc_stron == value)
				return i;
			else i++;
		}
		return -1;
	}
}

void AddNewElement(ksiazka*& value) {
	//if (hash_tab[GetHash(value->ilosc_stron)] == NULL) {
		//hash_tab[GetHash(value->ilosc_stron)] = value;
	if (hash_tab[GetHash3(value)] == NULL) {
		hash_tab[GetHash3(value)] = value;
	}
	else
	{
		int i = GetHash3(value) + 1;
		//int i = GetHash(value->ilosc_stron) + 1;
		while (hash_tab[i] != NULL) {
			i++;
		}
		hash_tab[i] = value;
	}
}

// podobna sytuacja jak z tablica struktur

node* FindListElement(ksiazka*& value)
{
	node* tmp;
	tmp = hash_tab_list[GetHash1(value)];

	while (tmp != NULL)
	{
		if (tmp->key.ilosc_stron == value->ilosc_stron)
			return tmp;
		else tmp = tmp->next;
	}
	return NULL;
}

void AddNewListElement(ksiazka*& value) {
	//AddFront(hash_tab_list[GetHash(value->ilosc_stron)],value );
	AddFront(hash_tab_list[GetHash3(value)], value);
}

int main() {
	zerowanieTablicy();
	srand(time(NULL));
	node* HEAD = NULL;
	clock_t start, koniec;
	fstream plik;
	string wydanie, ilosc_str;
	
	float czas;
	cout.setf(ios::fixed);
	cout.precision(10);
	int a, b;
	plik.open("ksiazka.txt", ios::in);

	tp start1 = std::chrono::system_clock::now();
	while (!plik.eof()) {
		ksiazka* p = new ksiazka();
		getline(plik, p->tytu³, ',');
		getline(plik, p->nazwisko_autora, ',');
		getline(plik, wydanie, ',');
		getline(plik, ilosc_str, ',');
		a = atoi(wydanie.c_str());
		b= atoi(ilosc_str.c_str());
		 p->rok_wydania=a;
		 p->ilosc_stron=b;
		getline(plik, p->wydawnictwo);
		AddNewListElement( p);
	
	}
	plik.close();
	duration d = std::chrono::system_clock::now() - start1;
	cout <<"Czas GetHash3 dla list jednostronnych "<< d.count()<<endl;
	plik.open("ksiazka.txt", ios::in);
	
	tp start2 = std::chrono::system_clock::now();

	while (!plik.eof()) {
		ksiazka* p = new ksiazka();
		getline(plik, p->tytu³, ',');
		getline(plik, p->nazwisko_autora, ',');
		getline(plik, wydanie, ',');
		getline(plik, ilosc_str, ',');
		a = atoi(wydanie.c_str());
		b = atoi(ilosc_str.c_str());
		 p->rok_wydania=a;
		 p->ilosc_stron=b;
		getline(plik, p->wydawnictwo);
		AddNewElement(p);

	}
	plik.close();
	duration d2 = std::chrono::system_clock::now() - start2;
	cout <<"Czas GetHash3 dla probkowania liniowego " <<d2.count()<<endl;
	cout << hash_tab_list[5]->next->key.ilosc_stron << endl;

	system("pause");
	return 0;
}