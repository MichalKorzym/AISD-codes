#include <iostream>
using namespace std;
struct zawodnik {
	int czas;
	string nazwisko;
};

struct RBTnode {
	RBTnode* up;
	RBTnode* left;
	RBTnode* right;
	zawodnik key;
	char color;
	
};

void Rot_R(RBTnode* A, RBTnode* sentry, RBTnode*& root)
{
	RBTnode* B;
	RBTnode* pom;

	B = A->left;

	if (B != sentry)
	{
		pom = A->up;
		A->left = B->right;

		if (A->left != sentry) A->left->up = A;

		B->right = A;
		B->up = pom;
		A->up = B;

		if (pom != sentry)
		{
			if (pom->left == A) pom->left = B;
			else pom->right = B;
		}
		else root = B;
	}
}

void Rot_L(RBTnode* A, RBTnode* sentry, RBTnode*& root)
{
	RBTnode* B;
	RBTnode* pom;

	B = A->right;

	if (B != sentry)
	{
		pom = A->up;
		A->right = B->left;

		if (A->right != sentry) A->right->up = A;

		B->left = A;
		B->up = pom;
		A->up = B;

		if (pom != sentry)
		{
			if (pom->left == A) pom->left = B;
			else pom->right = B;
		}
		else root = B;
	}
}

//wypisywanie
void inorderRBT(RBTnode* root, RBTnode* sentry) {

	RBTnode* tmp2 = root;
	if (tmp2 != sentry) {

		inorderRBT(tmp2->left,sentry);
		cout << "Czas zawodnika: " << tmp2->key.czas << " Nazwisko: " << tmp2->key.nazwisko << " balance factory " << tmp2->color << endl;
		inorderRBT(tmp2->right,sentry);
	}

}

RBTnode* minRBTree(RBTnode* sentry, RBTnode* root)
{
	if (root != sentry)
		while (root->left != sentry) root = root->left;
	return root;
}

RBTnode* nextNODE(RBTnode* currentNode, RBTnode	* sentry, RBTnode* root)
{
	RBTnode* tmp;

	if (currentNode != sentry)
	{
		if (currentNode->right != sentry) return minRBTree(sentry, currentNode->right);
		else
		{
			tmp = currentNode->up;
			while ((tmp != sentry) && (currentNode == tmp->right))
			{
				currentNode = tmp;
				tmp = tmp->up;
			}
			return tmp;
		}
	}
	return sentry;
}




void insertRBT(RBTnode*& root, RBTnode* sentry, int value, string nazwisko)
{
	RBTnode* tmp = new RBTnode;
	tmp->key.czas = value;
	tmp->color = 'R';
	tmp->left = sentry;
	tmp->right = sentry;
	tmp->up = root;
	tmp->key.nazwisko = nazwisko;

	RBTnode* tmp2 = root;

	if (root == sentry)
	{
		root = tmp;
		root->color = 'B';
	}
	else
	{
		while (1)
		{
			if (value < tmp->up->key.czas)
			{
				if (tmp->up->left == sentry)
				{
					tmp->up->left= tmp;
					break;
				}
				tmp->up = tmp->up->left;
			}
			else
			{
				if (tmp->up->right == sentry)
				{
					tmp->up->right = tmp;
					break;
				}
				tmp->up =tmp->up->right;
			}
		}
	}

	while ((tmp != root) && (tmp->up->color == 'R'))
	{
		if (tmp->up == tmp->up->up->left)
		{
			tmp2 =tmp->up->up->right; 

			if (tmp2->color == 'R') // przypadek1 
			{
				tmp->up->color = 'B';
				tmp2->color = 'B';
				tmp->up->up->color = 'R';
				tmp = tmp->up->up;
				continue;
			}

			if (tmp == tmp->up->right) //przypadek 2
			{
				tmp = tmp->up;
				Rot_L(tmp, sentry, root);
			}

			tmp->up->color = 'B'; //przypadek 3
			tmp->up->up->color = 'R';
			Rot_R(tmp->up->up, sentry, root);
			break;
		}
		else
		{
			tmp2 = tmp->up->up->left; 

			if (tmp2->color == 'R') //przypadek 1
			{
				tmp->up->color = 'B';
				tmp2->color = 'B';
				tmp->up->up->color = 'R';
				tmp= tmp->up->up;
				continue;
			}

			if (tmp == tmp->up->left) //przypapek 2
			{
				tmp = tmp->up;
				Rot_R(tmp, sentry, root);
			}

			tmp->up->color = 'B';
			tmp->up->up->color = 'R';
			Rot_L(tmp->up->up, sentry, root);
			break;
		}
	}
	root->color = 'B';
}





//ZNAJDYWAMIE PO NAZWISKU
RBTnode* findSurname(RBTnode* root, RBTnode* sentry, string nazwisko_)
{
	bool tmp = false;

	while (root != sentry)
	{

		if (!tmp)
		{
			while (root->left != sentry)
				root = root->left;
		}

		if (root->key.nazwisko == nazwisko_) {
			return root;
		}

		tmp = true;

		if (root->right != sentry)
		{
			tmp = false;
			root = root->right;
		}
		else if (root->up != sentry)
		{
			while (root->up != sentry && root == root->up->right)
				root = root->up;
			if (!root->up )
				break;
			root = root->up;
		}
		else break;
	}
}

void removeRBT(RBTnode* root, RBTnode* sentry, RBTnode* ptr) {
	RBTnode* tmp, * tmp2, * tmp3;

	if ((ptr->left == sentry) || (ptr->right == sentry))
		tmp = ptr;
	else
		tmp = nextNODE(ptr, sentry, root);

	if (tmp->left != sentry)
		tmp2 = tmp->left;
	else
		tmp2 = tmp->right;


	tmp2->up = tmp->up;

	if (tmp->up == sentry)
		root = tmp2;
	else if (tmp == tmp->up->left)
		tmp->up->left = tmp2;
	else
		tmp->up->right = tmp2;


	if (tmp != ptr)
		ptr->key = tmp->key;

	if (tmp->color == 'B')
		while ((tmp2 != root) && (tmp2->color == 'B'))
			if (tmp2 == tmp2->up->left)
			{
				tmp3 = tmp2->up->right;

				if (tmp3->color == 'R')
				{
					tmp3->color = 'B';
					tmp2->up->color = 'R';
					Rot_L(tmp2->up, sentry, root);
					tmp3 = tmp2->up->right;
				}


				if ((tmp3->left->color == 'B') && (tmp3->right->color) == 'B') {

					tmp3->color = 'R';
					tmp2 = tmp2->up;
					continue;
				}

				if (tmp3->right->color == 'B')
				{
					tmp3->left->color = 'B';
					tmp3->color = 'R';
					Rot_R(tmp3, sentry, root);
					tmp3 = tmp2->up->right;
				}

				tmp3->color = tmp2->up->color;
				tmp2->up->color = 'B';
				tmp3->right->color = 'B';
				Rot_L(tmp2->up, sentry, root);
				tmp2 = root;
			}
			else
			{
				tmp3 = tmp2->up->left;

				if (tmp3->color == 'R')
				{
					tmp3->color = 'B';
					tmp2->up->color = 'R';
					Rot_R(tmp2->up, sentry, root);
					tmp3 = tmp2->up->left;
				}

				if ((tmp3->left->color == 'B') && (tmp3->right->color == 'B'))
				{
					tmp3->color = 'R';
					tmp2 = tmp2->up;
					continue;
				}

				if (tmp3->left->color == 'B')
				{
					tmp3->right->color = 'B';
					tmp3->color = 'R';
					Rot_L(tmp3, sentry, root);
					tmp3 = tmp2->up->left;
				}

				tmp3->color = tmp2->up->color;
				tmp2->up->color = 'B';
				tmp3->left->color = 'B';
				Rot_R(tmp2->up, sentry, root);
				tmp2 = root;
			}

	tmp2->color = 'B';
	delete tmp;
			}




int main() {

	RBTnode* sentry = new RBTnode;
	sentry->color = 'B';
	RBTnode* root = sentry;


	

	int wybor;
	while (true) {
		cout << "======================================== " << endl;
		cout << "JAKA CZYNNOSC CHCESZ WYKONAC ?????" << endl;
		cout << "======================================== " << endl;
		cout << "1.Wyswietlenie wynikow " << endl;
		cout << "2.Wyszukanie wyniku " << endl;
		cout << "3.Zamiana wyniku " << endl;
		cout << "4.Dodanie nowego wyniku " << endl;
		cout << "5.Usuniecie zawodnika" << endl;
		cin >> wybor;
		string nazwisko;
		int wartosc = 0;
		switch (wybor)
		{
		case 1:
			inorderRBT(root,sentry);
			break;
		case 2:
			cout << "Podaj nazwisko  " << endl;
			cin >> nazwisko;
			cout << "Zawodnik ten osiagnal wynik " << findSurname(root,sentry, nazwisko)->key.czas << " sekund" << endl;
			break;
		case 3:
			cout << "Podaj nazwisko zawodnika ktorego wynik chcesz zmienic " << endl;
			cin >> nazwisko;
			removeRBT(root,sentry, findSurname(root,sentry, nazwisko));
			cout << "Podaj nowy wynik jaki osiagnal ten zawdonik " << endl;
			cin >> wartosc;
		insertRBT(root,sentry, wartosc, nazwisko);
			break;
		case 4:
			cout << "Podaj czas jaki osiagnal zawodnik " << endl;
			cin >> wartosc;
			cout << "Podaj nazwisko zawodnika" << endl;
			cin >> nazwisko;
			insertRBT(root, sentry, wartosc, nazwisko);
			break;
		case 5:
			cout << "Podaj zawodnika ktorego wynik chcesz usunac" << endl;
			cin >> nazwisko;
			removeRBT(root, sentry, findSurname(root, sentry, nazwisko));
		case 6:
		cout<<"Minimalny wezel to "<<	minRBTree(sentry, root)->key.czas<<endl;
		}
	}


	system("pause");
	return 0;
}