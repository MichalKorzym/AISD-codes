#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <string>
#pragma warning(disable: 4996)
using namespace std;
struct BSTnode {
	BSTnode* up;
	BSTnode* right;
	BSTnode* left;
	int key;
};

void AddNode(BSTnode*& root, int key_) {

	BSTnode* tmp = new BSTnode();
	BSTnode* tmp2 = root;
	tmp->left = NULL;
	tmp->right = NULL;
	tmp->key = key_;

	if (tmp2 != NULL) {
		while (true) {
			if (key_ < (tmp2->key))
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

		}
	}else{root = tmp; //wêze³ jest korzeniem

	}
};
BSTnode* maxBST(BSTnode* root) {    //ZNAJDYWANIE NAJWIEKSZEGO WEZLA
	BSTnode* tmp2 = root;
	if (tmp2) {

		while (tmp2->right) {
			tmp2 = tmp2->right;
		}

	}

	return tmp2;

}
BSTnode* popFind(BSTnode* root) {

	BSTnode* tmp2 = root;
	BSTnode* tmp;
	if (tmp2) {
		if (tmp2->left) {
			return maxBST(tmp2->left);
		}
		else {
			tmp = tmp2->up;


			while (tmp != NULL && (tmp2 == tmp->left))
			{
				tmp2 = tmp;
				tmp = tmp->up;
			}
			return tmp;
		}


	}
	else
	{
		return tmp2;
	}
}

void inorderBST(BSTnode* root) {
	
	BSTnode* tmp2 = root;
	if (tmp2!=NULL) {
		
		inorderBST(tmp2->left);
		cout <<"wartosc wezla: " <<tmp2->key << endl;
		inorderBST(tmp2->right);
	}

}

BSTnode* findBST(BSTnode* root, int key_szuk) {
	BSTnode* tmp2 = root;
	while (tmp2 != NULL && tmp2->key != key_szuk) {
		tmp2 = (key_szuk < tmp2->key) ? tmp2->left : tmp2->right;
		
	}
	return tmp2;
}
BSTnode* minBST(BSTnode* root) {
	BSTnode* tmp2 = root;
	if (tmp2) {

		while(tmp2->left){
			tmp2 = tmp2->left;
		}
		
	}

	return tmp2;

}
BSTnode* nastFindM(BSTnode* szukany) { 
	BSTnode* tmp2 = szukany;
	BSTnode* tmp3;
	if (tmp2) {

		if (tmp2->left) {

			return minBST(tmp2->left);
		}
		else {
			tmp3 = tmp2->up;
			while (tmp3 && (tmp2 == tmp3->left))
			{
				tmp2 = tmp3;
				tmp3 = tmp3->up;
			}
			return tmp3;
		}

		return tmp2;
	}
}
BSTnode* nastFind(BSTnode* root) {
	BSTnode* tmp2 = root;
	BSTnode* tmp3;
	if (tmp2) {

		if (tmp2->right) {

			return minBST(tmp2->right);
		}
		else {
			tmp3 = tmp2->up;
			while (tmp3 && (tmp2 == tmp3->right))
			{
				tmp2 = tmp3;
				tmp3 = tmp3->up;
			}
			return tmp3;
		}

		return tmp2;
	}
}
void delBST(BSTnode*& root, BSTnode* szukana) {
	
	BSTnode* szukana_ = szukana;
	BSTnode* tmp3;
	BSTnode* tmp4;
	if (szukana) {
		tmp3 = !szukana_->left || !szukana_->right ? szukana_ : nastFind(szukana_);
		tmp4 = tmp3->left ? tmp3->left : tmp3->right;
		if (tmp4) {
			tmp4->up = tmp3->up;
		}
		if (!tmp3->up) {
			root = tmp4;
		}

		else if (tmp3 == tmp3->up->left) {
			tmp3->up->left = tmp4;
		}
		else {
			tmp3->up->right = tmp4;
		}
		if (tmp3 != szukana_) {
			szukana_->key = tmp3->key;
		}
		delete tmp3;
		}
	}




int main() {
	


	//char* data = asctime(ptr);
	
		//time_t my_time = time(NULL);
	//cout << ctime(&my_time) << endl;
	int key_;
	BSTnode* root = NULL;
	for (int i = 0; i < 6; i++) {
		tm* czas = new tm();
		cout << "podaj" << endl;
		cin >> key_;
		AddNode(root, key_);
		

	}
	int wartosc;
	int spr;
	cout << "nastepnik wartosc" << endl;
	cin >> spr;
	
	inorderBST(root);
	BSTnode* nastepnik;
	BSTnode* poprzednik;
	BSTnode* nastepnikM;
	nastepnik=nastFind(findBST(root, spr));
	cout << nastepnik->key<<endl;
	poprzednik = popFind(findBST(root, spr));
	cout << poprzednik->key << endl;
	nastepnikM = nastFindM(findBST(root, spr));
	cout << nastepnikM->key << endl;

	cout << "podaj wartosc klucza ktory chcesz usunac" << endl;
	cin >> wartosc;
	delBST(root, findBST(root,wartosc));
	inorderBST(root);
	system("pause");
	return 0;
}
