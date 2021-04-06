#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <fstream>
//ZADANIE 4
using namespace std;
struct materials {
	string name;
	string conductivity, density, specific_heat;

};

// do 1 i 3
void MPfindName(string word, string temp) {

	int  i, b, pp;
	int N, M;
	N = word.length();
	M = temp.length();
	int* PI = new int[M + 1];

	// dla wzorca obliczamy tablicê PI [ ] 

	PI[0] = b = -1;
	for (i = 1; i <= M; i++)
	{
		while ((b > -1) && (temp[b] != temp[i - 1])) b = PI[b];
		PI[i] = ++b;
	}



	pp = b = 0;
	int licznik = 0;
	string find;
	bool a = false;
	for (i = 0; i < N; i++)
	{
		while ((b > -1) && (temp[b] != word[i])) b = PI[b];
		if (++b == M)
		{
			while (pp < i - b + 1)
			{
				licznik++;
				pp++;
			}
			//cout << licznik;
			find = word.substr(licznik + M, N); pp++;
			a = true;
			b = PI[b];
		}
	}
	if (a) {
		cout << "znaleziona nazwa" << endl;
		cout << find;
		cout << endl;
	}
	delete[] PI;

}
//zadanie 2
void ELSET_NSET(string word) {

	int  i, a, b, pp, pp2;
	int N, M, K;
	string temp1 = "*Elset, elset=";
	string temp2 = "*Nset, nset=";
	N = word.length();
	M = temp1.length();
	K = temp2.length();
	int* PI = new int[M + 1];
	int* PI2 = new int[K + 1];
	// dla wzorca obliczamy tablicê PI [ ] 
	PI2[0] = a = -1;
	PI[0] = b = -1;
	//dla elsetow

	for (i = 1; i <= M; i++)
	{
		while ((b > -1) && (temp1[b] != temp1[i - 1])) b = PI[b];
		PI[i] = ++b;
	}
	//dla nsetow


	for (i = 1; i <= K; i++)
	{
		while ((a > -1) && (temp2[a] != temp2[i - 1])) a = PI2[a];
		PI2[i] = ++a;
	}



	pp = b = 0;
	pp2 = a = 0;
	int licznik = 0;
	int licznik2 = 0;
	string elsets;
	string nsets;
	bool c = false;
	bool d = false;
	for (i = 0; i < N; i++)
	{
		while ((b > -1) && (temp1[b] != word[i]))
			b = PI[b];
		if (++b == M)
		{
			while (pp < i - b + 1)
			{
				licznik++;
				pp++;
			}
			//cout << licznik;
			elsets = word.substr(licznik + M, N); pp++;
			c = true;
			b = PI[b];
		}


	}
	for (i = 0; i < N; i++) {
		while ((a > -1) && (temp2[a] != word[i]))
			a = PI2[a];
		if (++a == K)
		{
			while (pp2 > i - a + 1)
			{
				licznik2++;
				pp2++;
			}
			nsets = word.substr(licznik + K, N); pp2++;
			d = true;
			a = PI2[a];

		}
	}

	if (c) {
		cout << "ELSETY" << endl;
		cout << elsets;
		cout << endl;
	}
	else if (d) {
		cout << "NSETY" << endl;
		cout << nsets;
		cout << endl;
	}
	delete[] PI, PI2;
}

int navie_pattern(string s, string w)
{
	bool found = false;
	for (int i = 0; i < s.length(); i++)
	{
		found = true;
		for (int j = 0; j < w.length(); j++)
		{
			if (s[j + i] != w[j])
			{
				found = false;
				break;
			}
		}
		if (found == true)
		{
			return i;
		}
	}

	return -1;
}



materials findStructMP() {
	fstream plik2;
	materials* tab = new materials[10];
	plik2.open("Job-case1.inp", ios::in);
	int i = 0;
	if (plik2.good() == true) {

		string zdanie;
		string templatee = "*Material, name=";
		int count = templatee.length();
		while (getline(plik2, zdanie)) {
			if (navie_pattern(zdanie, "*Material, name=") != -1) {
				//uzupelnianie tablicy
				tab[i].name = zdanie.substr(count, ' ');
				getline(plik2, zdanie);
				getline(plik2, zdanie);
				tab[i].conductivity = zdanie;

				getline(plik2, zdanie);
				getline(plik2, zdanie);
				tab[i].density = zdanie;

				getline(plik2, zdanie);
				getline(plik2, zdanie);
				tab[i].specific_heat = zdanie;
				i++;
			}

		}

	}
	cout << "Podpunkt 4 " << endl;
	for (int j = 0; j < i; j++) {
		cout << tab[j].name << " " << tab[j].conductivity << " " << tab[j].density << " " << tab[j].specific_heat << endl;
	}
	plik2.close();
	return *tab;
}
//podpunkt 5

void ifSTEPcorrect() {
	fstream plik3;
	string zdanie;
	bool a = false;
	bool b = false;
	bool c = false;
	bool d = false;
	plik3.open("Job-case1.inp", ios::in);
	cout << "zadanie 5 " << endl;
	if (plik3.good() == true) {
		while (getline(plik3, zdanie)) {
			//cout << zdanie << endl;
			if ((navie_pattern(zdanie, "** STEP:") != -1)) {

				while ((navie_pattern(zdanie, "*End Step") == -1)) {
					getline(plik3, zdanie);

					if ((navie_pattern(zdanie, "** INTERACTIONS") != -1))
						a = true;


					if ((navie_pattern(zdanie, "** OUTPUT REQUESTS") != -1))
						b = true;


					if ((navie_pattern(zdanie, "** FIELD OUTPUT") != -1))
						c = true;

					if ((navie_pattern(zdanie, "** HISTORY OUTPUT") != -1))
						d = true;



				}

			}
		}
	}

	if (a && b && c && d) {
		cout << "STEP ZOSTAL ZDEFINIOWANY POPRAWNIE !!" << endl;
	}
	else {
		cout << "STEP ZDEFINIOWANY NIEPOPRAWNIE !!" << endl;
	}
	plik3.close();
}


int main() {

	fstream plik;
	plik.open("Job-case1.inp", ios::in);
	string liczba;
	if (plik.good() == true)
	{
		while (getline(plik, liczba)) {
			MPfindName(liczba, "Part, name="); //podpunkt 1
			ELSET_NSET(liczba);
			MPfindName(liczba, "*Element, type=");
		}

	}

	plik.close();
	findStructMP();

	ifSTEPcorrect();
	system("pause");
	return 0;


}