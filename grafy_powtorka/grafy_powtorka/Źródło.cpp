#include <iostream>
#include <iomanip>

using namespace std; 

string tab_miasta[9] = { "Wilno","Uciana","Mariampol","Kowno","Poniewiez","Szawle","Taurogi","Klajpeda","Butynga" };
struct miasto {
	string nazwa;
	int numer;
};
 //KRUSKAL

//kolejka priorytetowa waga oraz wierzcholki
struct edge{
	miasto w1, w2;
	int waga;
	
};
class Queue
{
private:
	edge* heap;
	int position;
public:
	Queue(int n);
	~Queue();
	edge front();
	void push(edge w);
	void pop();
};

//zbiory rozlaczne 
struct nodeDS{
	int up;
	int rank;

};
// klasa ds 
class ds{
private:
	nodeDS* zb;
public:
	~ds();
	ds(int n);
	void MergeDS(edge w);
	void MakeSet(int v);
	int FindSet(int v);
};
// minimalne drzewo rozpinajace

struct s_list {
	s_list* next;
	miasto v;
	int weight;
};
//klasa drzewa
class Tree {
private:
	s_list** tab_list;
	int tree_weight;
	int index_count;
public:
	~Tree(); //destruktor
	Tree(int n);
	void AddEdge(edge w);
	s_list* GetList(int n);
	void printTree();

};
//obiekty klasy Queue

//destruktor
Queue::~Queue() {
	delete[] heap;
}
//konstruktor 
Queue::Queue(int n) {
	heap = new edge[n];
	position = 0;
}
//zwraca poczatek kopca

edge Queue::front()
{
	return heap[0];
}

//umieszczenie nowej kraweddzi 
void Queue::push(edge w)
{
	int  i = position++;
	int j = (i - 1) >> 1; //przesuniecie bitowe 


	while (i && (heap[j].waga> w.waga)) {
		heap[i] = heap[j];
		i = j;
		j = (i - 1) >> 1;
	}

	heap[i] = w; //wstawienie krawedzi do kopca
}
//usuniecie korzenia z kopca

void Queue::pop() {

	int i;
	int j;
	edge w;
	if (position)
	{
		w = heap[--position];
		i = 0;
		j = 1;

		while (j < position) {
			if ((j + 1 < position) && (heap[j + 1].waga < heap[j].waga))
				j++;
			if (w.waga <= heap[j].waga)
				break;
			heap[i] = heap[j];
			i = j;
			j = (j << 1) + 1;
		}
		heap[i] = w;



	}

}

//obiekty klasy ds
//destruktor
ds::~ds()
{
	delete[] zb;
}
//konstruktor 
ds::ds(int n) {
	zb = new nodeDS[n];
}
//dodanie elementu tablicy

void ds::MakeSet(int v)
{
	zb[v].up = v;
	zb[v].rank = 0;
}

//zwrotu indeksu zbioru
int ds::FindSet(int v)
{
	if (zb[v].up != v)
		zb[v].up = FindSet(zb[v].up);
	return zb[v].up;
}

//laczenie zbiorow
void ds::MergeDS(edge w) {
	int root_u;
	int root_v;
	root_u = FindSet(w.w1.numer);
	root_v = FindSet(w.w2.numer);

	if (root_u != root_v)
	{
		if (zb[root_u].rank > zb[root_v].rank)
			zb[root_v].up = root_u;
	
		else
		{
			zb[root_u].up = root_v;
			if (zb[root_u].rank == zb[root_v].rank)
				zb[root_v].rank++;
		}
	}//dd
}

// obiekty klasy tree

//konstruktor 
Tree::Tree(int n)
{
	tab_list = new s_list * [n];
	for (int i = 0; i < n; i++)
		tab_list[i] = NULL;
	index_count = n - 1;
	tree_weight = 0;
}
// destruktor

Tree::~Tree()
{
	s_list* tmp;
	s_list* tmp2;
	for (int i = 0; i <= index_count; i++) 
	{
		tmp = tab_list[i];
		while (tmp)
		{
			tmp2 = tmp;
			tmp = tmp->next;
			delete tmp2;
		}
	}

	delete[]tab_list;
}

void Tree::AddEdge(edge w)
{
	s_list* tmp;
	tree_weight += w.waga;
	tmp = new s_list;
	tmp->v.numer = w.w2.numer;
	tmp->v.nazwa = w.w2.nazwa;
	tmp->weight = w.waga;
	tmp->next = tab_list[w.w1.numer];
	tab_list[w.w1.numer] = tmp;

	tmp = new s_list;
	tmp->v.numer = w.w1.numer;
	tmp->v.nazwa = w.w1.nazwa;
	tmp->weight = w.waga;
	tmp->next = tab_list[w.w2.numer];
	tab_list[w.w2.numer] = tmp;
}

s_list* Tree::GetList(int n)
{
	return tab_list[n];
}


//wyswietlanie drzewa
void Tree::printTree()
{
	s_list* tmp;
	for (int i = 0; i <= index_count; i++)
	{
		cout << " Miasto " << tab_miasta[i] << " - ";
		for (tmp = tab_list[i]; tmp; tmp = tmp->next)
			cout <<"Miasto "<< tmp->v.nazwa << ":" << tmp->weight << "   ";
		cout << endl;
	}
	cout << "Wartosc minimalnego drzewa wynosi = " << tree_weight << endl;
}

int main() {
	
	int liczba_wierzcholkow = 9;
	int liczba_krawedzi = 12;
	edge w;
	int i;

	



	Queue Q(liczba_krawedzi);
	ds zb(liczba_wierzcholkow);
	Tree T(liczba_wierzcholkow);

	//tworzenie zbioru dla kazdego wierzcholka
	for (i = 0; i < liczba_wierzcholkow; i++)
		zb.MakeSet(i);

	//umieszczanie krawedzi w kolejce
	for (i = 0; i < liczba_krawedzi; i++)
	{
		cout << "Podaj nazwe oraz numer 1 miasta ,nastepnie 2 a na koniec wage trasy miêdzy nimi " << endl;
		cin >> w.w1.nazwa >> w.w1.numer >> w.w2.nazwa>> w.w2.numer >> w.waga;
		Q.push(w);
	}

	for (i = 1; i < liczba_wierzcholkow; i++)
	{
		do
		{
			w = Q.front();
			Q.pop();

		} while (zb.FindSet(w.w1.numer) == zb.FindSet(w.w2.numer));
		T.AddEdge(w);
		zb.MergeDS(w);


	}

	cout << " ALGORYTM KRUSKALA " << endl;
	T.printTree();

	// algorytm prima 

	s_list* tmp;
	edge w_2;
	miasto start;


	Tree T2(liczba_wierzcholkow);
	Tree T3(liczba_wierzcholkow);
	Queue Q2(liczba_krawedzi);

	bool* visited = new bool[liczba_wierzcholkow]; //sprawdzamy czy odwiedzilismy wezel
	for (i = 0; i < liczba_wierzcholkow; i++)
		visited[i] = false;


	for (i = 0; i < liczba_krawedzi; i++)
	{
		cout << "Podaj kolejno 1 i 2  wierzcholek oraz wage krawedzi" << endl;
		cin >> w_2.w1.nazwa >> w_2.w1.numer >> w_2.w2.nazwa >> w_2.w2.numer >> w_2.waga;
		T2.AddEdge(w_2);
	}
	start.numer = 0; //wierzcholkiem startowym jest WILNO
	visited[start.numer] = true;
	for (i = 1; i < liczba_wierzcholkow; i++)
	{
		for(tmp=T2.GetList(start.numer);tmp;tmp=tmp->next)
			if (!visited[tmp->v.numer])
			{
				w_2.w1.numer = start.numer;
				w_2.w1.nazwa = start.nazwa;
				w_2.w2.numer = tmp->v.numer;
				w_2.w2.nazwa = tmp->v.nazwa;
				w_2.waga = tmp->weight;
				Q2.push(w_2);
			}
		do
		{
			w_2 = Q2.front();
			Q2.pop();
		} while (visited[w_2.w2.numer]);

		T3.AddEdge(w_2);
		visited[w_2.w2.numer] = true;
		start.numer = w_2.w2.numer;
		start.nazwa = w_2.w2.nazwa;
	}
	cout << endl << endl;
	cout << " ALGORYTM PRIMA " << endl;
	T3.printTree();
	delete[] visited;



	system("pause");
	return 0;
}