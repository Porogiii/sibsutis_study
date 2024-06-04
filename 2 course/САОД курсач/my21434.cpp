#include <fstream>
#include <iostream> 
#include <conio.h>
#include <Windows.h>
#include <iomanip>
#include <cstdio> 
#include <cstring> 
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <algorithm>
using namespace std;

const int N = 4000;
const int M = 256;
int sum = 0;
int sym_count = 0;
int code[M][M];
float entropy = 0, lgm = 0;
int fcompression = 0, cfcompression = 0;

struct record
{
	char FIO[30];
	short int Department;
	char Position[22];
	char Date[10];
};

struct list
{
	record *data;
	list* prev;
	list* next;	
};

struct vertex
{
	record *data;
	vertex *next;
	int bal;
	vertex *left;
	vertex *right;
};
vertex *root = NULL;
bool up = false;

struct HF_code {
	float p; 
	float q; 
	char a; 
	int l;
};
HF_code A[M];

void Read_base(FILE *fp, list *base);
void copy_base(list*, list*);
void Print_base(list *base);

int compare_deposit(int a, int b);
int compare_name(char a[], char b[]);
int compare_date(char a[], char b[]);
int BSearch (list **A, int Number);

void DigitalBuild (list **A, int l, int r);
void DigitalBuild2 (list **A, int l, int r, int offset);
void DigitalSort (int n, list **A);
void Print_sort_index_mas(list **mas);



int main()
{
	system("chcp 866 > nul");
	setlocale(LC_ALL, "Russian");
	FILE *f;
	
	f=fopen("testBase2.dat", "rb");
	list *base = new list;
	list *base_index =new list;
	Read_base(f,base);
	fclose(f);
	copy_base(base, base_index);
	list *mas[N];
	for(int i=0;i<N;i++){
		mas[i]=base_index;
		base_index=base_index->next;
	}
	DigitalSort(N, mas);

	
	int enter = 0;
	while (true) {
		system("CLS");
		enter = 0;
		int search_start=0;
		int search=N-1;
		int j=0;
		int dep_num = 0;
		
		SetConsoleCP(866);
		cout << "\t------------------------------МЕНЮ------------------------" << endl;
		cout << "\t1. Посмотреть базу данных" << endl;
		cout << "\t2. Просмотр отсортированной базы данных (Digital Sort)" << endl;
		cout << "\t----------------------------------------------------------" << endl;
		while ((enter != 27) && (enter != 49) && (enter != 50) && (enter != 51) && (enter != 52) && (enter != 53)) {
			if (_kbhit()) {
				enter = _getch();
			}
		}
		switch (enter) {
			case 27: return 0;
			case 49:
				Print_base(base);
				break;
			case 50:
				Print_sort_index_mas(mas);
				break;
		}
		_getch();
	}
	system ("Pause");
	return 0;
}


int compare_department(int a, int b) {
	if(a>=b){
		return 1;
	}
	else{
		return -1;
	}
}

int compare_name(char* a, char* b) {
	
	if (strcmp(a,b) == 0)
		return 0;
		
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
	if(space_pos_a < space_pos_b){
		return -1;
	}
	return 0;
}

int compare_date(char a1[], char b1[]) {	
	char a[30];
	char b[30];
	strcpy(a, a1);
	strcpy(b, b1);
	
	if (strcmp(a, b) == 0) {
		return strcmp(a, b);
	}
	else if (a[6] - b[6] != 0) {
		return a[6] - b[6];
	}
	else if (a[7] - b[7] != 0) {
		return a[7] - b[7];
	}
	else if (a[3] - b[3] != 0) {
		return a[3] - b[3];
	}
	else if (a[4] - b[4] != 0) {
		return a[4] - b[4];
	}
	else if (a[0] - b[0] != 0) {
		return a[0] - b[0];
	}
	else if (a[1] - b[1] != 0) {
		return a[1] - b[1];
	}
	return 0; 
}

void DigitalBuild (list **A, int l, int r) {
	int i=l, j;
	list *x=A[l];
	
	while (1) {
		j=2*i;
		if (j+1>=r) break;
		int result = 0;
		if(j<r){
			result = compare_department(A[j+1]->data->Department, A[j]->data->Department);
			if(result > -1){
				j++;
			}
		}
		
		result = compare_department(x->data->Department, A[j]->data->Department);
		if(result > -1){
			break;
		}
		
		A[i]=A[j];
		i=j;
	}
	A[i]=x;
}

void DigitalBuild2 (list **A, int l, int r, int offset) {
	int i = l, j = 2 * i;
	list *x=A[offset+l];
	
	while (1) {
		j=2*i;
		if (j+1>=r) break;
		int result = 0;
		if(j<r){
			result = compare_name(A[offset+j+1]->data->FIO, A[offset+j]->data->FIO);
			if(result > -1){
				j++;
			}
		}
		
		result = compare_name(x->data->FIO, A[offset+j]->data->FIO);		
		if(result > -1){
			break;
		}
		A[offset+i] = A[offset+j];
		i = j;
	}
	A[offset+i]=x;
}

void DigitalSort (int n, list **A) {

	
	int l=n/2, r=n;
	while (l+1>0) {
		DigitalBuild (A, l, r);
		l--;
	}
	while (r>1) {
		list* t=A[0];
		A[0]=A[r-1];
		A[r-1]=t;
		r--;
		DigitalBuild (A, 0, r-1);
	}
	
	
	int offset = 0;
	int counter_max = 0;
	while (offset + counter_max < n-1){
		if(A[offset+counter_max]->data->Department != A[offset+counter_max+1]->data->Department){
			l = counter_max / 2;
			r = counter_max+1;
			
			while (l + 1 > 0) {
				DigitalBuild2 (A, l, r, offset);
				l--;
			}
			while (r > 1) {
				list* t = A[offset];
				A[offset]=A[offset+r-1];
				A[offset+r-1]=t;
				r--;
				DigitalBuild2 (A, 0, r-1, offset);
			}
			offset = offset + counter_max + 1;
			counter_max = 0;		
		}
		else{
			counter_max += 1;
		}
	}
	
	
	l = counter_max / 2;
	r = counter_max + 1;
	while (l + 1 > 0) {
		DigitalBuild2 (A, l, r, offset);
		l--;
	}
	while (r > 1) {
		list* t = A[offset];
		A[offset]=A[offset+r-1];
		A[offset+r-1]=t;
		r--;
		DigitalBuild2 (A, 0, r-1, offset);
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

void Read_base(FILE *fp, list *base){
	record *mas = new record();
	fread((record *)mas, sizeof(record), 1, fp);
	base->data=mas;
	base->prev=NULL;
	base->next=NULL;
	
	for (int i = 1; i < N; i++) {
        mas = new record();
        list *base_prev;
        fread((record*)mas, sizeof(record), 1, fp);
        base_prev = base;
        base = base->next = new list();
        base->data = mas;
        base->prev = base_prev;
        base->next = NULL;
    }
}


void Print_base(list *base){
	int i;
	char n;
	SetConsoleCP(1251);
	cout << "1 for 4000 / 2 for 20 per click/ 3 for nothing"<< endl;
    cin>>n;
    if(n=='1'){
    	i=0;
    	while(i<N){
    		cout<<i+1<<"\t"<<base->data->Date<<"\t"<<base->data->FIO<<"\t"<<base->data->Department<<"\t"<<base->data->Position <<endl;
    		i++;
    		if(int result=_kbhit()){
   				printf( "\nKey '%c' was pressed. Press 'e' key to exit.\n", _getch());
   				char something;
    			cin>>something;
    			if(something=='e'){
    				return;
				}
			}
			base=base->next;
		}
	}
    if(n=='2'){
		i=0;	
		int g=0;
		for(int i=0;i<N;i=i+20){
			while((g++)<20)
			{
	    		cout<<i+g<<"\t"<<base->data->Date<<"\t"<<base->data->FIO<<"\t"<<base->data->Department<<"\t"<<base->data->Position <<endl;
    			base=base->next;
			}
			if(g>=20){
		   		cout << "y for continue" << endl;
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
	cout << "1 for 4000 / 2 for 20 per click/ 3 for nothing"<< endl;
    cin>>n;
    if(n=='1'){
    	i=0;
    	while(i<N){
    		cout<<i+1<<"\t"<<mas[i]->data->Date<<"\t"<<mas[i]->data->FIO<<"\t"<<mas[i]->data->Department<<"\t"<<mas[i]->data->Position <<endl;
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
		int g=0;
		for(int i=0;i<N;i=i+20){
			while((g++)<20)
			{
	    		cout<<i+g<<"\t"<<mas[i+g]->data->Date<<"\t"<<mas[i+g]->data->FIO<<"\t"<<mas[i+g]->data->Department<<"\t"<<mas[i+g]->data->Position <<endl;
    		}
			if(g>=20){
		   		cout << "y for continue" << endl;
			cin >> n;
			if (n=='y')
		    g=0;
		    else
		    return;
		    }
		}
	}
	
		
}


