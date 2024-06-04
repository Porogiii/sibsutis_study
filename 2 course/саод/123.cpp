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
const int alphabet_num=81;


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

struct GM_code {
	float p;
	float q;
	int l;
	char a;
};
GM_code A[M];
GM_code B[alphabet_num];


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

void Print(list *Base) {
    int i, g, N = 4000;
    char n;
    SetConsoleCP(1251);

    i = 0;
    g = 0;
    bool exitLoop = false;
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
    while (!exitLoop) {
        for (i = g; i < N && i < g + 20; i++) {
            if (Base != nullptr) {
                std::cout << i + 1 << "\t" << Base->data->FIO << "\t" << Base->data->Department << "\t" << Base->data->Position << "\t" << Base->data->Date << std::endl;
                Base = Base->next;
            }
        }

        if (i >= N) {
            std::cout << "Reached the end of data." << std::endl;
            std::cout << "Press 'f' for forward, 'b' for backward, 'e' to exit, 'n' to go to a specific record: " << endl;
            n = _getch(); // Используем _getch() для немедленного считывания символа
        } else {
            std::cout << "Press 'f' for forward, 'b' for backward, 'e' to exit, 'n' to go to a specific record: " << endl;
            n = _getch(); // Используем _getch() для немедленного считывания символа
        }

        if (n == 'f') {
            g += 20;
        } else if (n == 'b') {
            g -= 20;
            if (g < 0) {
                g = 0;
            }
        } else if (n == 'e') {
            exitLoop = true;
        } else if (n == 'n') {
            std::cout << "\nEnter record number: ";
            int recordNumber;
            std::cin >> recordNumber;

            if (recordNumber > 0 && recordNumber <= N) {
                g = ((recordNumber - 1) / 20) * 20;
            } else {
                std::cout << "Invalid record number. Press Enter to continue." << std::endl;
                while (_getch() != '\r') {} // Ожидаем нажатия Enter перед продолжением
            }
        } else {
            std::cout << "Invalid input. Exiting." << std::endl;
            return;
        }
    }
}





void Print_sort_index_mas(list **mas) {
    int i, g, N = 4000; 
    char n;
    SetConsoleCP(1251);

    
    i = 0;
	g = 0;
	bool exitLoop = false;
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	while (!exitLoop) {
		for (i = g; i < N && i < g + 20; i++) {
			std::cout << i + 1 << "\t" << mas[i]->data->FIO << "\t" << mas[i]->data->Department << "\t" << mas[i]->data->Position << "\t" << mas[i]->data->Date << std::endl;
		}

		if (i >= N) {
			std::cout << "Reached the end of data." << std::endl;
			std::cout << "Press 'f' for forward, 'b' for backward, 'e' to exit,  'n' to go to a specific record: " << endl;
			n = _getch();
		} else {
			std::cout << "Press 'f' for forward, 'b' for backward, 'e' to exit,  'n' to go to a specific record: " << endl;
			n = _getch();
		}

		if (n == 'f') {
			g += 20;
		} else if (n == 'b') {
			g -= 20;
			if (g < 0) {
				g = 0;
			}
		} else if (n == 'e') {
			exitLoop = true;
		} else if (n == 'n') {
			std::cout << "\nEnter record number: ";
			int recordNumber;
			std::cin >> recordNumber;

			if (recordNumber > 0 && recordNumber <= N) {
                g = ((recordNumber - 1) / 20) * 20;
            } else {
                std::cout << "Invalid record number. Press Enter to continue." << std::endl;
                while (_getch() != '\r') {} 
            }
		} else if (n != 'y') {
			std::cout << "Invalid input. Exiting." << std::endl;
			return;
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


/////////////////////////////////////////////CODE/////////////////////////////////////////////

void CodePrint(){
	lgm=0;
	SetConsoleCP(866);
	printf("\n\nCode Gilbert-Moore: \n\n");
	printf("| ¹ | Symbol | Propability |     Code word    | Length |\n");
	SetConsoleCP(1251);
	for (int i = 0; i < alphabet_num; i++) {
        if (B[i].l > 0) {
            char currentChar = (i == 56 || i == 57) ? '-' : B[i].a;
            printf("| %2d |    %c   |  %2.6f   | ", i, currentChar, B[i].q);
            for (int j = 1; j <= B[i].l; j++)
                printf("%d", code[i][j]);
            for (int j = B[i].l + 1; j < 14; j++)
                printf(" ");
            printf("    |  %4d  |\n", B[i].l);
            lgm += B[i].p * B[i].l;
        } else {
            printf("| %2d |    -   |  %2.6f   |", i, B[i].q);
            for (int j = 0; j < 12; j++)  
                printf(" ");
            printf("|  %4d  |\n", B[i].l);
            lgm += B[i].p * B[i].l; 
        }
    }

	SetConsoleCP(866);
	printf("\nN = %d\n", alphabet_num);
	printf("\n   Entropy \t Average lenght\n");
	printf(" %10f      %10.5f    \n", entropy, lgm);
	
	cout << endl << endl << entropy+2 <<" > "<< lgm <<endl <<endl;
	
}


void GilbertMoorCode(){
	int i,j;
	FILE *fp;	
    fp = fopen("testBase2.dat", "rb");
	for (i = 0; i < M; i++) {
		A[i].p = 0;
		A[i].q = 0;
		A[i].l = 0;
		A[i].a = (char)(i-128);
	}
	while (!feof(fp)) {
		char c;
		fscanf(fp, "%c", &c);
		if (feof(fp))
			break;
		//printf("%c",c);
		//cout << c<<" - " << (int)c <<endl; 
		A[c+128].p +=1;
		A[c+128].a = c;
		sum++;
	}
	fclose(fp);	
	for (i = 0, j = 0; i < M; i++){
		if(A[i].p!=0){
			A[i].p /=sum;
			B[j]=A[i];
			entropy += A[i].p * abs(log(A[i].p) / log(2));
			j++;
		}
	}
	
	for (i = 0; i < alphabet_num; i++){
		B[i].q = B[i-1].q + B[i].p/2;
		B[i].l = ceil(-log(B[i].p) / log(2)) + 1;
	}
	
	for (i = 0; i < alphabet_num; i++)
	{
		for (j = 0; j <= B[i].l; j++)
		{
			B[i].q *= float(2);
			code[i][j] = floor(B[i].q);
			while (B[i].q >= 1)
				B[i].q -= 1;
		}
	}
}

/////////////////////////////////////////////CODE/////////////////////////////////////////////

/////////////////////////////////////////////TREE/////////////////////////////////////////////

int size(Vertex *x)
{
	if (x == NULL) {
		return 0;
	}
	else {
		return 1 + size(x->Left) + size(x->Right);
	}
}

int maxi(int x, int y)
{
	if (x > y) return x;
	return y;
}

int height(Vertex *x)
{
	if (x == NULL) {
		return 0;
	}
	else {
		return 1 + max(height(x->Left), height(x->Right));
	}
}

int sdp(Vertex *x, int l)
{
	if (x == NULL) {
		return 0;
	}
	else {
		return l + sdp(x->Left, l + 1) + sdp(x->Right, l + 1);
	}
}

void LR_print(Vertex* p, int& count) {
	if (p != NULL) {
		LR_print(p->Left, count);
		cout << count+1 << ") "<< p->data->FIO << "\t" << p->data->Department << "\t" << p->data->Position << "\t"<< p->data->Date << endl;
		count++;
		LR_print(p->Next, count);
		LR_print(p->Right, count);
	}
}

void add_vertex(Vertex *&p, list* mas, int w) {
	if (p == NULL) {
		p = new Vertex;
		p->data = mas->data;
        p->w = w;
		p->Next = NULL;
		p->Left = NULL;
		p->Right = NULL;
	}
	else if (strncmp(p->data->FIO,mas->data->FIO,3) == 0) {
		add_vertex(p->Next, mas, w);
	}
	else if (strncmp(p->data->FIO,mas->data->FIO,3)  > 0) {
		add_vertex(p->Left, mas, w);
	}
	else if (strncmp(p->data->FIO,mas->data->FIO,3)  < 0) {
		add_vertex(p->Right, mas, w);
	}
}

void A1(int L, int R, list **mas) {
	int wes = 0, sum = 0;
	int i;
	if (L <= R) {
		for (i = L; i <= R; i++) {
			wes = wes + W[i];
		}
		for (i = L; i < R; i++) {
			if ((sum < (wes / 2)) && (sum + W[i]) > (wes / 2)) {
				break;
			}
			sum = sum + W[i];
		}
		//cout << L << " - " << R << " - " << wes << " - " << i  << " - " << W[i] << endl;
		add_vertex(root, mas[i], W[i]);
		A1(L, i - 1,mas);
		A1(i + 1, R,mas);
	}
}



void TreeSearch (Vertex* p, char* name){
	if(p!=NULL)                 
    {
        if(strncmp(p->data->FIO,name,3)>0){
    	    TreeSearch(p->Left,name);
    	}else{
    		if(strncmp(p->data->FIO,name,3)<0){
            	TreeSearch(p->Right,name);
	        }else{
				if(strncmp(p->data->FIO,name,3)==0){
					cout << p->data->FIO << "\t" << p->data->Department << "\t" << p->data->Position << "\t"<< p->data->Date << endl;
	            	TreeSearch(p->Next,name);
	            }
			}
        }
    }
}

void seth(Vertex *p)
{
	if (p) {
		if (p->Next) {
			p->Next->h = p->h +1;
		}
		if (p->Left) {
			p->Left->h = p->h + 1;
		}
		if (p->Right) {
			p->Right->h = p->h + 1;
		}
		seth(p->Left);
		seth(p->Right);
		seth(p->Next);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////







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
    // Остальной код без изменений...
	system("cls");
	setlocale(LC_ALL, "Russian");
	FILE* fp;
	int search_start=0;
	int search=N-1;
	


	struct GM_code {
		float p;
		float q;
		int l;
		char a;
	};
	GM_code A[M];
	GM_code B[alphabet_num];



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
    char input; // Переменная для хранения введённого символа
	GilbertMoorCode();

		int enter = 0;
		char *spc = " ";


    std::cout << "\t------------------------------Menu------------------------" << std::endl;
    std::cout << "\t1. View database" << std::endl;
    std::cout << "\t2. View sorted database (Digital Sort)" << std::endl;
    std::cout << "\t3. Bsearch" << std::endl;
	std::cout << "\t4. Tree (A1)" << std::endl;
    std::cout << "\t5. Code" << std::endl;
	std::cout << "\t6. Exit" << std::endl;
    std::cout << "\t----------------------------------------------------------" << std::endl;

    input = _getch(); // Считываем символ с клавиатуры

    // Проверяем введенный символ
    switch (input)
    {
        case '1':
            SoD = 1;
            break;
        case '2':
            SoD = 2;
            break;
        case '3':
            SoD = 3;
            break;
		case '4':
			SoD = 4;
			break;
		case '5':
			SoD = 5;
			break;
        case '6':
            SoD = 6;
            break;
        default:
            // Если введен символ, отличный от 1, 2, 3 или 4, возвращаемся в меню
            Menu();
            return 0;
    }

    switch (SoD)
    {
        case 1:
            // Опция 1: View database
            Print(OriginBase);
            break;
        case 2:
            // Опция 2: View sorted database (Digital Sort)
            Print_sort_index_mas(mas);
            break;
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
					SetConsoleCP(866);
					A1(search_start, search,mas);
                    root->h = 1;
                    seth(root);
				}
			}
			break;
		}
		case 4:{
			int count =0;
			char street[18];
			SetConsoleCP(1251);
			printf("\n");
			printf("\n");
			LR_print(root, count);
			SetConsoleCP(866);
			cout<<endl;
			// printf("+------+----------+----------+----------------+\n");
			// printf("|%6d| UniqSize |  Height  |   Mid. height  |\n", N);
			// printf("+------+----------+----------+----------------+\n");
			// printf("|  A1  |%10d|%10d|%16.2f|\n", size(root),  height(root), (double)sdp(root, 1) / size(root));
			// printf("+------+----------+----------+----------------+\n");
			cout<<endl<< "Element find: "<< endl;
			SetConsoleCP(866);
			cin >> street;
			SetConsoleCP(1251);
			char *spc = " ";
			strcat(street, spc);
			if(strcmp(street,"0")!=0){
				TreeSearch(root,street);
			}
			break;
		}
		
		case 5:{
			CodePrint();
			break;
		}
        case 6:
            // Опция 4: Exit
            system("PAUSE");
            return 0;
        default:
            break;
    }

    _getch(); // Ждем нажатия любой клавиши перед повторным вызовом Menu()
    Menu();
    return 0;
}





int main()
{
	Menu();
	return 0;
}





