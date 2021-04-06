#include <iostream>
using namespace std;
//struktura zawodnika
struct zawodnik {
	int czas;
	string nazwisko;
};
//struktura wezla
struct AVLnode {
	AVLnode* up;
	AVLnode* right;
	AVLnode* left;
	zawodnik key;
	int bf;
};
//rotacja RR
void RR(AVLnode*& root, AVLnode* A) {
	AVLnode* B = A->right;
	AVLnode* tmp = A->up;
	A->right = B->left;

	if (A->right) {
		A->right->up = A;
	}
	B->left = A;
	B->up = tmp;
	A->up = B;
	if (tmp) {
		if (tmp->left == A) {
			tmp->left = B;
		}
		else
		{
			tmp->right = B;
		}
	}
	else {
		root = B;
	}
	if (B->bf == -1) {
		A->bf = 0;
		B->bf = 0;
	}
	else {
		A->bf = -1;
		B->bf = 1;
	}
}
//rotacja LL
void LL(AVLnode*& root, AVLnode* A) {
	AVLnode* B = A->left;
	AVLnode* tmp = A->up;
	A->left = B->right;

	if (A->left) {
		A->left->up = A;
	}
	B->right = A;
	B->up = tmp;
	A->up = B;

	if (tmp) {
		if (tmp->left == A) {
			tmp->left = B;
		}
		else {
			tmp->right = B;
		}
	}
	else {
		root = B;
	}
	if (B->bf == 1) {
		A->bf = B->bf = 0;
	}
	else {
		A->bf = 1;
		B->bf = -1;
	}

}
//rotacja RL
void RL(AVLnode*& root, AVLnode* A) {
	AVLnode* B = A->right;
	AVLnode* C = B->left;
	AVLnode* tmp = A->up;

	B->left = C->right;
	if (B->left) {
		B->left->up = B;
	}
	A->right = C->left;
	if (A->right) {
		A->right->up = A;
	}
	C->left = A;
	C->right = B;
	A->up = B->up = C;
	C->up = tmp;

	if (tmp) {
		if (tmp->left == A) {
			tmp->left = C;

		}
		else {
			tmp->right = C;
		}

	}
	else {
		root = C;
	}
	if (C->bf == -1) {
		A->bf = 1;
	}
	else {
		A->bf = 0;
	}
	if (C->bf == 1) {
		B->bf = -1;

	}
	else {
		B->bf = 0;
	}
	C->bf = 0;
}
//rotacja LR
void LR(AVLnode*& root, AVLnode* A) {
	AVLnode* B = A->left;
	AVLnode* C = B->right;
	AVLnode* tmp = A->up;

	B->right = C->left;
	if (B->right) {
		B->right->up = B;
	}
	A->left = C->right;
	if (A->left) {
		A->left->up = A;
	}
	C->right = A;
	C->left = B;
	A->up = B->up = C;
	C->up = tmp;

	if (tmp) {
		if (tmp->left == A) {
			tmp->left = C;

		}
		else {
			tmp->right = C;
		}
	

	}
	else {
		root = C;
	}
	if (C->bf == 1) {
		A->bf = -1;
	}
	else {
		A->bf = 0;
	}
	if (C->bf == -1) {
		B->bf = 1;

	}
	else {
		B->bf = 0;
	}
	C->bf = 0;
}

 //dodawanie wezla
void AddNode(AVLnode*& root, int key_, string nazwisko_) {

	AVLnode* tmp = new AVLnode();
	AVLnode* tmp2 = root;
	tmp->left = NULL;
	tmp->up = NULL;
	tmp->right = NULL;
	tmp->key.czas = key_;
	tmp->key.nazwisko = nazwisko_;
	tmp->bf = 0;
	bool a;
	AVLnode* tmp3;

	if (!tmp2)

		root = tmp; //wêze³ jest korzeniem

	else {
		while (true) 
			if (key_ < (tmp2->key.czas))
			{
				if (tmp2->left == NULL) {
					tmp2->left = tmp;    //sprawdzanie lewego wêz³a
					break;
				}
				else
				{
					tmp2 = tmp2->left;
				}
			}
			else {
				if (tmp2->right == NULL) {
					tmp2->right = tmp;	//sprawdzanie prawego wêz³a
					break;
				}
				else {
					tmp2 = tmp2->right;
				}
			}
			tmp->up = tmp2;




			// rownowazenie drzewa AVL

			if (tmp2->bf)
				tmp2->bf = 0;

			else
			{
				if (tmp2->left == tmp)
					tmp2->bf = 1;

				else
					tmp2->bf = -1;


				tmp3 = tmp2->up;

				a = false;


				while (tmp3) {
					if (tmp3->bf) {
						a = true;
						break;

					}
					if (tmp3->left == tmp2)
						tmp3->bf = 1;
					else
						tmp3->bf = -1;

					tmp2 = tmp3;
					tmp3 = tmp3->up;
				}
				if (a) {
					if (tmp3->bf == 1) {
						if (tmp3->right == tmp2)
							tmp3->bf = 0;

						else if (tmp2->bf == -1)
							LR(root, tmp3);
						else
						LL(root, tmp3);


					}
					else {
						if (tmp3->left == tmp2)
							tmp3->bf = 0;

						else if (tmp2->bf == 1)
							RL(root, tmp3);
						else
							RR(root, tmp3);
					}
				}
			}

		
	}
}



//wypisywanie
void inorderAVL(AVLnode* root) {

	AVLnode* tmp2 = root;
	if (tmp2 != NULL) {

		inorderAVL(tmp2->left);
		cout << "Czas zawodnika: " << tmp2->key.czas << " Nazwisko: " << tmp2->key.nazwisko <<" balance factory "<<tmp2->bf <<endl;
		inorderAVL(tmp2->right);
	}

}
//szukanie najmniejszego wezla
AVLnode* minAVL(AVLnode* root)
{
	if (root) while (root->left) root = root->left;
	return root;
}

//funkcja szukajaca poprzednika 
AVLnode* predAVL(AVLnode* ptr) {
	AVLnode* tmp;
	if (ptr) {
		if (ptr->left) {
			ptr = ptr->left;
			while (ptr->right) ptr = ptr->right;
		}
	
	else 
		do {
			tmp = ptr;
			ptr = ptr->up;
		} while (ptr && ptr->right != tmp);
	}
	return ptr;
}
//szukanie wezla o zadanym kluczu 
AVLnode* findAVL(AVLnode* ptr, int key) {
	while (ptr && ptr->key.czas != key) {
		ptr = (key < ptr->key.czas) ? ptr-> left : ptr->right;
	}
	return ptr;
}
//usuwanie wezla
AVLnode* delAVL(AVLnode*& root, AVLnode* ptr) {
	AVLnode* tmp, *tmp2, *tmp3;
	bool a;

	if (ptr->left && ptr->right) {
		tmp = delAVL(root, predAVL(ptr));
		a = false;
	}
	else {
		if (ptr->left)
		{
			tmp = ptr->left;
			ptr->left = NULL;
		}
		else {
			tmp = ptr->right;
			ptr->right = NULL;
		}
		ptr->bf = 0;
		a = true;
	}
	if (tmp) {
		tmp->up = ptr->up;
		tmp->left = ptr->left;
		if (tmp->left) tmp->left->up = tmp;
		tmp->right = ptr->right;
		if (tmp->right) tmp->right->up = tmp;
		tmp->bf = ptr->bf;
	}
	if (ptr->up) {
		if (ptr->up->left == ptr) {
			ptr->up->left = tmp;
		}
		else {
			ptr->up->right = tmp;
		}
	}
	else {
		root = tmp;
	}
	if (a) {
		tmp2 = tmp;
		tmp = ptr->up;
		while (tmp) {
			if (!tmp->bf) {
				if (tmp->left == tmp2) tmp->bf = -1;
				else tmp->bf = 1;
				break;
			}
			else {
				if (((tmp->bf == 1) && (tmp->left == tmp2)) || ((tmp->bf == -1) && (tmp->right == tmp2))) {
					tmp->bf = 0;
					tmp2 = tmp;
					tmp = tmp->up;
				}
				else {
					if (tmp->left == tmp2) 
						tmp3 = tmp->right;
					else
						tmp3 = tmp->left;
					if (!tmp3->bf)
					{
						if (tmp->bf == 1) LL(root, tmp);
						else
							RR(root, tmp);
						break;
					}
					else if (tmp->bf == tmp3->bf) {
						if (tmp->bf == 1) LL(root, tmp);
						else RR(root, tmp);
						tmp2 = tmp3;
						tmp = tmp3->up;
					}
					else {
						if (tmp->bf == 1)
							LR(root, tmp);
						else RL(root,tmp);
						tmp3 = tmp->up;
						tmp = tmp3->up;
					}







				}
			}
		}

	}
	return ptr;
}
//ZNAJDYWAMIE PO NAZWISKU
AVLnode* findSurname(AVLnode* root, string nazwisko_)
{
	bool tmp = false;

	while (root)
	{

		if (!tmp)
		{
			while (root->left)
				root = root->left;
		}

		if (root->key.nazwisko == nazwisko_) {
			return root;
		}

		tmp = true;

		if (root->right)
		{
			tmp = false;
			root = root->right;
		}
		else if (root->up)
		{
			while (root->up &&
				root == root->up->right)
				root = root->up;
			if (!root->up)
				break;
			root = root->up;
		}
		else break;
	}
}

int main() {

	int czas_zaw;
	string nazw_zawodnika;
	AVLnode* root = NULL;

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
			inorderAVL(root);
			break;
		case 2:
			cout << "Podaj nazwisko  " << endl;
			cin >> nazwisko;
			cout << "Zawodnik ten osiagnal wynik " << findSurname(root, nazwisko)->key.czas << " sekund" << endl;
			break;
		case 3:
			cout << "Podaj nazwisko zawodnika ktorego wynik chcesz zmienic " << endl;
			cin >> nazwisko;
			delAVL(root, findSurname(root, nazwisko));
			cout << "Podaj nowy wynik jaki osiagnal ten zawdonik " << endl;
			cin >> wartosc;
			AddNode(root, wartosc, nazwisko);
			break;
		case 4:
			cout << "Podaj czas jaki osiagnal zawodnik " << endl;
			cin >> wartosc;
			cout << "Podaj nazwisko zawodnika" << endl;
			cin >> nazwisko;
			AddNode(root, wartosc, nazwisko);
			break;
		case 5:
			cout << "Podaj zawodnika ktorego wynik chcesz usunac" << endl;
			cin >> nazwisko;
			delAVL(root, findSurname(root, nazwisko));
		}
	}
	system("pause");
	return 0;
}