#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include<iomanip>
const int N=10000; 
using namespace std;
struct node {
    node* next;
    int  data;

};
struct bucket {
    node* headbucket;
};
struct bucketlist {
    int value;
    bucket* tab;

};
void printTAB(int tab[], int il) {
    for (int j =0; j <il ; ++j) {
        cout <<"Wartosc elementu tablicy  "<<tab[j];
        cout << endl;
    }
    cout << endl << endl;
}
void addTAB(int tab[],int il) {
    for (int i = 0; i <il; i++) {
        tab[i] = il - i;
    }
}
void addRandTab(int tab[], int il) {
    for (int i = 0; i < il; ++i) {
        tab[i] = rand();
    }
}
void deleteFront(node*& head) {
    node* tmp2 = head;
    while (tmp2) {

        tmp2 = tmp2->next;
        delete head;
        head = tmp2;
    }
};


void addFront(node*& head, int ilosc) {
    int value;
    for (int i = 0; i < ilosc; i++) {
        value = i + 1;
        node* tmp = new node();
        tmp->data = value;
        tmp->next = head;
        head = tmp;
    }
};
void addRandomFront(node*& head, int ilosc) {
    int value;
    for (int i = 0; i < ilosc; i++) {
        value = rand();
        node* tmp = new node();
        tmp->data = value;
        tmp->next = head;
        head = tmp;
    }
};
void printNode(node* head) {
    node* tmp2 = head;
    while (tmp2 != NULL) {
        cout << "Wartosc wezla:  " << tmp2->data << " ,adres wezla  " << tmp2 << endl;
        tmp2 = tmp2->next;


    }
    cout << endl << endl;
};
//insertion
void sortowanieINS(node** head, node* new_node)
{
	node* tmp;

	if (*head == NULL || (*head)->data >= new_node->data)
	{
		new_node->next = *head;
		*head = new_node;
	}
	else
	{
		tmp = *head;
		while (tmp->next != NULL && tmp->next->data < new_node->data)
		{
			tmp = tmp->next;
		}
		new_node->next = tmp->next;
		tmp->next = new_node;
	}
}
void insertionSort(node** head)
{

	node* newhead = NULL;
	node* tmp = *head;

	while (tmp != NULL)
	{
		node* next = tmp->next;
		sortowanieINS(&newhead, tmp);
		tmp = next;
	}

	*head = newhead;
}
//merge
node* scalanie(node* l1, node* l2) { //LACZENIE PODLIST
    node* newhead = NULL;
    if (l1 == NULL) {
        return l2;              //JEDNA Z LIST JEST PUSTA
    }
    if (l2 == NULL) {
        return l1;
    }
    if (l1->data < l2->data) {
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
//selection
void swapNodes(node** head, node* p, node* newhead, node* prev)  //ZAMIANA
{

    *head = newhead;


    prev->next = p;

    node* temp = newhead->next;
    newhead->next = p->next;
    p->next = temp;
}
node* sortowanieSEL(node* head)
{
    if (head == NULL) {
        return head;
    }
    node* min = head;
    node* prev = NULL;
    node* ptr;

    for (ptr = head; ptr->next != NULL; ptr = ptr->next) { //minimalny element 


        if (ptr->next->data < min->data) {
            min = ptr->next;
            prev = ptr;
        }
    }

    if (min != head)
        swapNodes(&head, head, min, prev);

    head->next = sortowanieSEL(head->next); //sprawdzanie kolejnych elementow
    return head;
}
void Selectionsort(node** head)
{
    if (*head == NULL) {
        return;
    }
    *head = sortowanieSEL(*head);
}

//QUICK SORT
node* findTail(node* tail) {
   
    while (tail != NULL && tail->next != NULL) {
      tail= tail->next;
    }
    return tail;
}
node* partycjowanie(node* head, node* end, node** newhead, node** newend) {
    node* pivot = end;
    node* tmp = head;
    node* tail = pivot;
    node* prev = NULL;
    while (tmp != pivot) {
        if (tmp->data < pivot->data) {

            if ((*newhead) == NULL) {
                *newhead = tmp;
            }
            prev = tmp;
            tmp = tmp->next;
        
            }
            else
            {
            if (prev != NULL) 
                prev->next = tmp->next;
                 node*   tmp2 = tmp->next;
                    tmp->next = NULL;
                    tail->next = tmp;
                    tail = tmp;
                    tmp = tmp2;
                
            }
        
    }
    if ((*newhead == NULL))  //JESLI PIVOT JEST NAJMNIEJSZA WARTOSCIA STAJE SIE GLOWA 
        (*newhead) = pivot;
    
    (*newend) = tail; //NOWY OGON
    return pivot;
}
node* SortowanieQuick(node* head, node* end) {
    if (!head || head==end) 
        return head;
    
    node* newhead = NULL;
    node* newend = NULL;
    node* pivot;
    pivot = partycjowanie(head, end, &newhead, &newend);
    
    if (newhead != pivot) {
        node* tmp = newhead;

        while (tmp->next != pivot) 
            tmp = tmp->next;
        
        tmp->next = NULL;

        newhead = SortowanieQuick(newhead, tmp);

        tmp = findTail(newhead);
        tmp->next = pivot;

    }
                    //ZA PIVOTEM 
    pivot->next = SortowanieQuick(pivot->next, newend);
    return newhead;

}
void quickSort(node** head) {
    *head = SortowanieQuick(*head, findTail((*head)));
    return; 
}
//HEAP SORT
void kopcowanie(int tab[], int il, int i) {
 
    int max = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left<il && tab[left]>tab[max])
        max = left;
    if (right<il&& tab[right]>tab[max])
        max = right;


    //ZAMIANA I SZUKANIE NAJWIEKSZEGO WEZLA
    if (max != i) {
        swap(tab[i], tab[max]);
        kopcowanie(tab, il, max);
    }
}
void heapSort(int tab[], int il) {
  
    //tworzenie kopca
    for (int i = (il / 2 )- 1; i >= 0; i--) 
        kopcowanie(tab, il, i);
     //sortowanie
    for (int i = il-1 ; i >=0; i--) {
        swap(tab[0], tab[i]);
        kopcowanie(tab, i, 0);
    }
    
}
//BUCKET SORT

node* new_bucket_node(int val) {
    node* newNode = new node;
    newNode->data = val;
    newNode->next = NULL;
    return newNode;
}
bucketlist* createbucketlist(int il_kub) {
    bucketlist* bl1 = new bucketlist();
    bl1->value = il_kub;
    bl1->tab = new bucket[il_kub];

    for (int i=0; i < il_kub; i++) 
        bl1->tab[i].headbucket = NULL;
    
    return bl1;
}

void bucketSort(bucketlist* bl, int bucket, int val) {
   
    node* newnode = new_bucket_node(val);
    node* tmp = new node;

    if (bl->tab[bucket].headbucket != NULL) {
        tmp = bl->tab[bucket].headbucket;

        //sortowanie
        if (tmp->data > newnode->data) {

            newnode->next = bl->tab[bucket].headbucket;
            bl->tab[bucket].headbucket = newnode;
        }
        else
        {
            while (tmp->next != NULL) {                 //szukanie elementu z wieksza wartoscia
                if ((tmp->next)->data > newnode->data)
                    break;
                
                tmp = tmp->next;
            }
            newnode->next = tmp->next;
            tmp->next = newnode;
        }
    }
    else
    {
        bl->tab[bucket].headbucket = newnode;


    }
}
void addNodeBucket(int tab[],bucketlist* bl1, int zasieg, int il) { // posortowane
    for (int i = 0; i < il; i++) {

        tab[i] = i+1;
     
        bucketSort(bl1, tab[i] / zasieg, tab[i]);

    }
}
void addNodeBucketODW(int tab[], bucketlist* bl1, int zasieg, int il) {  //posortowane odwrotnie
    for(int i = 0; i <il; i++) {

        tab[i] = il-i;

        bucketSort(bl1, tab[i] / zasieg, tab[i]);

    }
}
void addNodeBucketRAND(int tab[], bucketlist* bl1, int zasieg, int il) { //losowo
    for (int i = 0; i <il; i++) {

        tab[i] = rand() % (zasieg*10)+1;

        bucketSort(bl1, tab[i] / zasieg, tab[i]);

    }
}
void printBuckets(bucketlist* bl) {
    node* tmp = new node();

    for (int i = 0; i < bl->value; i++) {
        tmp = bl->tab[i].headbucket;
        while (tmp != NULL) {
            cout << "wartosc :  " << tmp->data;
            cout << endl;
            tmp = tmp->next;
        }
            
    }
}

int main() {
    srand(time(NULL));
    node* head = NULL;
    node* head_random = NULL;
    clock_t start, koniec;
    float czas_odwrotnie, czas_posortowane, czas_losowo;
    cout << "===============================================" << endl;
    cout << "         ALGORYTMY SORTOWANIA              " << endl;
    cout << "===============================================" << endl;
    cout << " Podaj ilosc elementow listy/tablicy " << endl;
    int il;
    cin >> il;
    addFront(head, il);
    cout << "           INSERTION SORT               " << endl;
    start = clock();
    insertionSort(&head);
    koniec = clock();
    czas_odwrotnie = (float)(koniec - start) / (float)CLOCKS_PER_SEC;
    cout << " Czas, dane posortowane odwrotnie:  "<<   czas_odwrotnie << endl;
   printNode(head);
    start = clock();
    insertionSort(&head);
    koniec = clock();
    czas_posortowane = (float)(koniec - start) / (float)CLOCKS_PER_SEC;
    cout << " Czas, dane posortowane :  " << czas_posortowane << endl;
    printNode(head);
    addRandomFront(head_random, il);
    start = clock();
    insertionSort(&head_random);
    koniec = clock();
    czas_losowo = (float)(koniec - start) / (float)CLOCKS_PER_SEC;
    cout << " Czas, dane posortowane losowo :  " << czas_losowo << endl;
    printNode(head_random);
    deleteFront(head);
    deleteFront(head_random);
    //SORTOWANIE SELECTION
    addFront(head, il);
    cout << "            SELECTION SORT            " << endl;
    start = clock();
    Selectionsort(&head);
    koniec = clock();
    czas_odwrotnie = (float)(koniec - start) / (float)CLOCKS_PER_SEC;
    cout << " Czas, dane posortowane odwrotnie:  " << czas_odwrotnie << endl;
    printNode(head);
    start = clock();
    Selectionsort(&head);
    koniec = clock();
    czas_posortowane = (float)(koniec - start) / (float)CLOCKS_PER_SEC;
    cout << " Czas, dane posortowane :  " << czas_posortowane << endl;
   printNode(head);
    addRandomFront(head_random, il);
    start = clock();
    Selectionsort(&head_random);
    koniec = clock();
    czas_losowo = (float)(koniec - start) / (float)CLOCKS_PER_SEC;
    cout << " Czas, dane posortowane losowo :  " << czas_losowo << endl;
    printNode(head_random);
    deleteFront(head);
    deleteFront(head_random);

    //SORTOWANIE MERGE
    addFront(head, il);
    cout << "            MERGE SORT              " << endl;
    start = clock();
    mergeSort(&head);
    koniec = clock();
    czas_odwrotnie = (float)(koniec - start) / (float)CLOCKS_PER_SEC;
    cout << " Czas, dane posortowane odwrotnie:  " << czas_odwrotnie << endl;
   printNode(head);
    start = clock();
    mergeSort(&head);
    koniec = clock();
    czas_posortowane = (float)(koniec - start) / (float)CLOCKS_PER_SEC;
    cout << " Czas, dane posortowane :  " << czas_posortowane << endl;
   printNode(head);
    addRandomFront(head_random, il);
    start = clock();
    mergeSort(&head_random);
    koniec = clock();
    czas_losowo = (float)(koniec - start) / (float)CLOCKS_PER_SEC;
    cout << " Czas, dane posortowane losowo :  " << czas_losowo << endl;
    printNode(head_random);
    deleteFront(head);
    deleteFront(head_random);

    //QUICK SORT
    addFront(head, il);
    cout << "            QUICK SORT             " << endl;
    start = clock();
    quickSort(&head);
    koniec = clock();
    czas_odwrotnie = (float)(koniec - start) / (float)CLOCKS_PER_SEC;
    cout << " Czas, dane posortowane odwrotnie:  " << czas_odwrotnie << endl;
      printNode(head);
    start = clock();
    quickSort(&head);
    koniec = clock();
    czas_posortowane = (float)(koniec - start) / (float)CLOCKS_PER_SEC;
    cout << " Czas, dane posortowane :  " << czas_posortowane << endl;
   printNode(head);
    addRandomFront(head_random, il);
    start = clock();
    quickSort(&head_random);
    koniec = clock();
    czas_losowo = (float)(koniec - start) / (float)CLOCKS_PER_SEC;
    cout << " Czas, dane posortowane losowo :  " << czas_losowo << endl;
     printNode(head_random);
    deleteFront(head);
    deleteFront(head_random);
    //HEAP SORT
    cout << "            HEAP SORT            " << endl;
    int tab[N];
    int tab2[N];
    addTAB(tab, il);
    start = clock();
    heapSort(tab, il);
    koniec = clock();
    czas_odwrotnie = (float)(koniec - start) / (float)CLOCKS_PER_SEC;
    cout << " Czas, dane posortowane odwrotnie:  " << czas_odwrotnie << endl;
    printTAB(tab, il);
    start = clock();
    heapSort(tab,il);
    koniec = clock();
    czas_posortowane = (float)(koniec - start) / (float)CLOCKS_PER_SEC;
    cout << " Czas, dane posortowane :  " << czas_posortowane << endl;
   printTAB(tab,il);
    addRandTab(tab2, il);
    start = clock();
    heapSort(tab2, il);
    koniec = clock();
    czas_losowo = (float)(koniec - start) / (float)CLOCKS_PER_SEC;
    cout << "Czas dane posortowane, losowo " << czas_losowo<<endl;
    printTAB(tab2, il);
    // BUCKET SORT
    cout << "        BUCKET SORT         " << endl;
    int il_kub = 100; 
    bucketlist* newbucketlist = createbucketlist(il_kub);
    bucketlist* newbucketlist_random= createbucketlist(il_kub);
    bucketlist* newbucketlist_odw = createbucketlist(il_kub);
   int zasieg;
    cout << "Podaj do jakiego zakresu maja byc liczby przkladowo 100,1000 itp." << endl;
    cin >> zasieg;
    zasieg = zasieg / 10;
    int tab_bucket[N];
    int tab_bucket_random[N];
    int tab_bucket_odw[N];
    start = clock();
    addNodeBucket(tab_bucket, newbucketlist, zasieg, il);
    koniec = clock();
    czas_odwrotnie = (float)(koniec - start) / (float)CLOCKS_PER_SEC;
    cout << " Czas, dane posortowane :  " << czas_odwrotnie << endl;
    printBuckets(newbucketlist);
    cout << endl;
    start = clock();
    addNodeBucketRAND(tab_bucket_random, newbucketlist_random, zasieg, il);
    koniec = clock();
    czas_losowo = (float)(koniec - start) / (float)CLOCKS_PER_SEC;
    cout << "Czas dane posortowane, losowo: " << czas_losowo << endl;
    printBuckets(newbucketlist_random);
    
    start = clock();
    addNodeBucketODW(tab_bucket_odw, newbucketlist_odw, zasieg, il);
    koniec = clock();
    czas_posortowane = (float)(koniec - start) / (float)CLOCKS_PER_SEC;
    cout << "Czas dane posortowane odwrotnie: " << czas_posortowane << endl;
    printBuckets(newbucketlist_odw);
    

    
    


    system("pause");
    return 0;

}