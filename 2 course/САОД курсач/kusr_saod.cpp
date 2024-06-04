#include <fstream>
#include <iostream> 
#include <conio.h>
#include <Windows.h>
#include <iomanip>
#include <cstdio> 
#include <cstring> 
#include <cmath>
using namespace std;

const int N=4000;
const int M=256;
int sum=0;
int code[M][M];
float entropy = 0, lgm = 0;
int fcompression = 0, cfcompression = 0;
int *W;


struct base
{
	char FIO[30];
	short int Department;
	char Position[22];
	char Date[10];
	
};

struct list {
	base *data;
	list* next;
	list* prev;
};


struct Vertex {
	base *data;
    int w;
    int h;
	Vertex *Next;
	Vertex* Left;
	Vertex* Right;
};
Vertex *root = NULL;


struct Fano {
	float p;
	float q;
	int l;
	char a;
};
Fano A[M];

int Menu();

void Read_base(FILE *fp, list *base);
void copy_base(list*, list*);

void Print(list *Base);
void Print_sort_index_mas(list **mas);

void digital_sort(list*& head, int sort);
void digital(list* h1, list* t1, list* h2, list* t2, list*& hr, list*& tr, int sort);
int compare(char* a, char* b);
int compare_name(char* a, char* b);

int BSearch (list **A, int Number);









int med(int L, int R)
{
	float sl = 0, sr;
	for (int i = L; i < R; i++)
		sl += A[i].q;
	sr = A[R].q;
	int m = R;
	while (sl >= sr)
	{
		m--;
		sl -= A[m].q;
		sr += A[m].q;
	}
	return m;
}

void fano(int L, int R, int k)
{
	if (L < R)
	{
		k++;
		int m = med(L, R);
		for (int i = L; i <= R; i++)
		{
			if (i <= m)
				code[i][k] = 0;
			else
				code[i][k] = 1;
			A[i].l++;
		}
		fano(L, m, k);
		fano(m + 1, R, k);
	}
}

int Menu()
{
	system("cls");
	setlocale(LC_ALL, "Russian");
	FILE* fp;
	int search_start=0;
	int search=N-1;
	
	fp = fopen("testBase2.dat", "rb");
	list* OriginBase = new list;
	list* SortBase = new list;
	Read_base(fp,OriginBase);
	fclose(fp);
	copy_base(OriginBase, SortBase);
	digital_sort(SortBase,0);
	digital_sort(SortBase,1);
	list *mas[N];
	for(int i=0;i<N;i++){
		mas[i]=SortBase;
		SortBase=SortBase->next;
	}
	W = new int[N];

	
	int SoD;
	cout << "\t------------------------------Menu------------------------" << endl;
	cout << "\t1. View database" << endl;
	cout << "\t2. View sorted database (Digital Sort)" << endl;
	cout << "\t3. Bsearch" << endl;
	cout << "\t4. Exit" << endl;
	cout << "\t----------------------------------------------------------" << endl;
	cin >> SoD;
	switch (SoD)
	{
		case 1:
		{
			Print(OriginBase);
			break;
		}
		case 2:
		{
			Print_sort_index_mas(mas);
			break;
		}
		case 3:
		{	
			cout <<endl;
			cout << "Enter department"<<endl;
			int numb = 0;
			cin >> numb;
			if(numb>=0){
				search = BSearch(mas,numb);
				int fam_pos=0;
				if(search == -1){
					cout << "This department doesn't exists''" << endl;
				}
				else{	
					do{
						if(search==0){
							break;
						}
						else{
							search--;
						}
				    	if(mas[search]->data->Department!=numb){
				    		search++;
				    		break;
						}
					}
					while(true);
				    
					search_start=search;
					
					do{
						search++;
						if(search==N){
							search--;
							break;
						}
						if(mas[search]->data->Department!=numb){
				    		break;
						}
					}
					while(true);
					SetConsoleCP(1251);
					cout <<endl <<endl<<"Founded "<<search-search_start <<" pozitions ("<< search_start<< " - "<< search-1<<")"<<endl;
					for(int i=search_start;i<search;i++){
						cout <<i<<" "<< mas[i]->data->FIO << "\t" << mas[i]->data->Department << "\t" << mas[i]->data->Position << "\t"<< mas[i]->data->Date << endl;
				        W[i] = rand() % 99 + 1;
					}
					
				}
			}
			break;
		}
		case 4:
		{
			system("PAUSE");
			return 0;
		}
	}
	_getch();
	Menu();
	return 0;
}

int main()
{
	Menu();
	return 0;
}
















void Read_base(FILE *fp, list *rbase){
	base *struk = new base();
	fread((base *)struk, sizeof(base), 1, fp);
	rbase->data=struk;
	rbase->prev=NULL;
	rbase->next=NULL;
	
	for (int i = 1; i < N; i++) {
        struk = new base();
        list *rbase_prev;
        fread((base*)struk, sizeof(base), 1, fp);
        rbase_prev = rbase;
        rbase = rbase->next = new list();
        rbase->data = struk;
        rbase->prev = rbase_prev;
        rbase->next = NULL;
    }
}

int BSearch (list **A, int Number) {
	int l = 0, r = N, m = 0, fam_pos=0;
	//char buffer[10];
	while (l < r) {
		m=(l+r)/2;
		//strcpy(buffer, A[m]->data->Date);
		//cout << &buffer[6] << endl;
		if (A[m]->data->Department == Number) {
			return m;
		}
		if (A[m]->data->Department < Number) 
			l = m+1;
		else r = m-1;
	}
	return -1;
}

int compare_name(char* a, char* b) {
	char bufferA[30];
	char bufferB[30];
	strcpy(bufferA, a);
	strcpy(bufferB, b);

	int space_pos_a = strchr(a,' ') - a;
	int space_pos_b = strchr(b,' ') - b;
	

	int count =4;

	if(space_pos_a < space_pos_b){
		count = space_pos_a;
	}
	else{
		count = space_pos_b;
	}
	count -= 1;
	

	if(strncmp(bufferA, bufferB,count) > 0){
		return 1;
	}
	if(strncmp(bufferA, bufferB,count) < 0){
		return -1;
	}

	if(space_pos_a > space_pos_b){
		return 1;
	}
	if(space_pos_a < space_pos_b){
		return -1;
	}

	strcpy(bufferA, a);
	strcpy(bufferB, b);
	bufferA[space_pos_a]='a';
	bufferB[space_pos_b]='a';
	space_pos_a = strchr(bufferA,' ') - bufferA;
	space_pos_b = strchr(bufferB,' ') - bufferB;
	
	count = 4;

	if(space_pos_a < space_pos_b){
		count = space_pos_a;
	}
	else{
		count = space_pos_b;
	}
	count -= 1;
	

	if(strncmp(bufferA, bufferB,count) > 0){
		return 1;
	}
	if(strncmp(bufferA, bufferB,count) < 0){
		return -1;
	}

	if(space_pos_a > space_pos_b){
		return 1;
	}
	if(space_pos_a < space_pos_b){
		return -1;
	}
	
	
	bufferA[space_pos_a]='a';
	bufferB[space_pos_b]='a';
	space_pos_a = strchr(bufferA,' ') - bufferA;
	space_pos_b = strchr(bufferB,' ') - bufferB;
	
	count = 4;
	
	if(space_pos_a < space_pos_b){
		count = space_pos_a;
	}
	else{
		count = space_pos_b;
	}
	count -= 1;
	
	
	if(strncmp(bufferA, bufferB,count) > 0){
		return 1;
	}
	if(strncmp(bufferA, bufferB,count) < 0){
		return -1;
	}
	
	if(space_pos_a >= space_pos_b){
		return 1;
	}
	return -1;
}


void digital(list* h1, list* t1, list* h2, list* t2, list*& hr, list*& tr, int sort) {
	if(sort ==0){
		if (compare_name(h1->data->FIO, h2->data->FIO)>0) {
			hr = h1;
			h1 = h1->next;
		}
		else {
			hr = h2;
			h2 = h2->next;
		}
	}
	else{
		if (h1->data->Department < h2->data->Department) {
			hr = h1;
			h1 = h1->next;
		}
		else {
			hr = h2;
			h2 = h2->next;
		}
	}
	tr = hr;
	while (t1->next != h1 && t2->next != h2) {
		if(sort ==0){
			if (compare_name(h1->data->FIO, h2->data->FIO)>0) {
				tr->next = h1;
				h1 = h1->next;
				tr = tr->next;
			}
			else {
				tr->next = h2;
				h2 = h2->next;
				tr = tr->next;
			}
		}
		else{
			if (h1->data->Department < h2->data->Department) {
				tr->next = h1;
				h1 = h1->next;
				tr = tr->next;
			}
			else {
				tr->next = h2;
				h2 = h2->next;
				tr = tr->next;
			}
			
		}
	}
	if (t1->next != h1) {
		tr->next = h1;
		tr = t1;
	}
	else if (t2->next != h2) {
		tr->next = h2;
		tr = t2;
	}
	tr->next = NULL;
}

void digital_sort(list*& head, int sort) {
	list* t = new list;
	t->data = NULL;
	t->next = head;
	int k = 1;
	int e = 0;
	list* hp, * tp, * h1, * t1, * h2, * t2, * hr, * tr;
	while (k < 4000) {
		hp = t;
		while (hp != NULL) {
			if (hp->next == NULL) {
				break;
			}
			h1 = hp->next;
			t1 = h1;
			for (int i = 1; i < k; i++) {
				if (t1->next == NULL) {
					break;
				}
				t1 = t1->next;
			}
			if (t1->next == NULL) {
				break;
			}
			h2 = t1->next;
			t2 = h2;
			t1->next = NULL;
			for (int i = 1; i < k; i++) {
				if (t2->next == NULL) {
					break;
				}
				t2 = t2->next;
			}
			tp = t2->next;
			t1->next = NULL;
			t2->next = NULL;
			digital(h1, t1, h2, t2, hr, tr,sort);
			hp->next = hr;
			head = hr;
			tr->next = tp;
			hp = tr;
		}
		k *= 2;
	}
}

void Print(list *Base)
{
	int i;
	char n;
	SetConsoleCP(1251);
	cout << "\t----------------------"<< endl;
	cout << "\t1. For 4000 per click"<< endl;
	cout << "\t2. For 20 per click"<< endl;
	cout << "\t3. For 100 per click"<< endl;
	cout << "\t4. For 500 per click"<< endl;
	cout << "\t----------------------"<< endl;
    cin>>n;
	printf("\n");
    if(n=='1'){
    	i=0;
    	while(i<N){
			cout << i + 1 << "\t" << Base->data->FIO << "\t" << Base->data->Department << "\t" << Base->data->Position << "\t" << Base->data->Date << endl;
    		i++;
    		if(int result=_kbhit()){
   				printf( "\nKey '%c' was pressed. Press 'e' key to exit.\n", _getch());
   				char something;
    			cin>>something;
    			if(something=='e'){
    				return;
				}
			}
			Base = Base->next;
		}
	}
    if(n=='2'){
		i=0;	
		int g=0;
		for(int i=0;i<N;i=i+20){
			while((g++)<20)
			{
				cout << i + g << "\t" << Base->data->FIO << "\t" << Base->data->Department << "\t" << Base->data->Position << "\t" << Base->data->Date << endl;
				Base = Base->next;
			}
			if(g>=20){
		   		cout << "y for continue" << endl;
				printf("\n");
			cin >> n;
			if (n=='y')
		    g=0;
		    else
		    return;
		    }
		}
	}
    if(n=='3'){
		i=0;	
		int g=0;
		for(int i=0;i<N;i=i+100){
			while((g++)<100)
			{
				cout << i + g << "\t" << Base->data->FIO << "\t" << Base->data->Department << "\t" << Base->data->Position << "\t" << Base->data->Date << endl;
				Base = Base->next;
			}
			if(g>=100){
		   		cout << "y for continue" << endl;
				printf("\n");
			cin >> n;
			if (n=='y')
		    g=0;
		    else
		    return;
		    }
		}
	}
	if(n=='4'){
		i=0;	
		int g=0;
		for(int i=0;i<N;i=i+500){
			while((g++)<500)
			{
				cout << i + g << "\t" << Base->data->FIO << "\t" << Base->data->Department << "\t" << Base->data->Position << "\t" << Base->data->Date << endl;
				Base = Base->next;
			}
			if(g>=500){
		   		cout << "y for continue" << endl;
				printf("\n");
			cin >> n;
			if (n=='y')
		    g=0;
		    else
		    return;
		    }
		}
	}
}

void Print_sort_index_mas(list **mas){
	int i;
	char n;
	SetConsoleCP(1251);
	cout << "\t----------------------"<< endl;
	cout << "\t1. For 4000 per click"<< endl;
	cout << "\t2. For 20 per click"<< endl;
	cout << "\t3. For 100 per click"<< endl;
	cout << "\t4. For 500 per click"<< endl;
	cout << "\t----------------------"<< endl;
	printf("\n");
    cin>>n;
    if(n=='1'){
    	i=0;
    	while(i<N){
			cout << i + 1 << "\t" << mas[i]->data->FIO << "\t" << mas[i]->data->Department << "\t" << mas[i]->data->Position << "\t" << mas[i]->data->Date << endl;
    		i++;
    		if(int result=_kbhit()){
   				printf( "\nKey '%c' was pressed. Press 'e' key to exit.\n", _getch());
   				char something;
    			cin>>something;
    			if(something=='e'){
    				return;
				}
			}
		}
	}
    if(n=='2'){
		i=0;	
		int g=-1;
		for(int i=0;i<N;i=i+20){
			while((g++)<20)
			{
				cout << i + g << "\t" << mas[i+g]->data->FIO << "\t" << mas[i+g]->data->Department << "\t" << mas[i+g]->data->Position << "\t" << mas[i+g]->data->Date << endl;
			}
			if(g>=20){
		   		cout << "y for continue" << endl;
				printf("\n");
			cin >> n;
			if (n=='y')
		    g=0;
		    else
		    return;
		    }
		}
	}
    if(n=='3'){
		i=0;	
		int g=-1;
		for(int i=0;i<N;i=i+100){
			while((g++)<100)
			{
				cout << i + g << "\t" << mas[i+g]->data->FIO << "\t" << mas[i+g]->data->Department << "\t" << mas[i+g]->data->Position << "\t" << mas[i+g]->data->Date << endl;
			}
			if(g>=100){
		   		cout << "y for continue" << endl;
				printf("\n");
			cin >> n;
			if (n=='y')
		    g=0;
		    else
		    return;
		    }
		}
	}	
	if(n=='4'){
		i=0;	
		int g=-1;
		for(int i=0;i<N;i=i+500){
			while((g++)<500)
			{
				cout << i + g << "\t" << mas[i+g]->data->FIO << "\t" << mas[i+g]->data->Department << "\t" << mas[i+g]->data->Position << "\t" << mas[i+g]->data->Date << endl;
			}
			if(g>=500){
		   		cout << "y for continue" << endl;
				printf("\n");
			cin >> n;
			if (n=='y')
		    g=0;
		    else
		    return;
		    }
		}
	}	
}

void copy_base(list *a, list *b) {
	b->prev = NULL;
	b->data = a->data;
	for (int i = 1; i < N; i++) {
		a = a->next;
		b->next = new list;
		b->next->prev = b;
		b = b->next;
		b->data = a->data;
	}
	b->next = NULL;
}
