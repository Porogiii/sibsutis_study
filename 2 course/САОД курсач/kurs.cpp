#include <fstream>
#include <iostream> 
#include <conio.h>
#include <Windows.h>
#include <iomanip>
#include <cstdio> 
#include <cstring> 
#include <cmath>
#include <iomanip>
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

int BSearch (list **A, int Department, list **queue);









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





/*------------------------Vertex----------------------------------*/

int Compare0(char* str1, char* str2) {
	int temp = 0;
	for (int i = 0; str1[i] != '\0'; i++) {
		if (str1[i] == '_')
			str1[i] = ' ';
		if (str1[i] > str2[i]) {
			temp = 1;
			break;
		}
		else if (str1[i] < str2[i]) {
			temp = -1;
			break;
		}
		else
			temp = 0;
	}
	return temp;
}

void addDOP(list* binList, Vertex*& p, int w) {
	//cout << "456";
	if (p == NULL) {
		p = new Vertex;
		p->data = binList->data;
		p->Left = NULL;
		p->Right = NULL;
		p->Next = NULL;
		p->w = w;
	//	cout << "789";
	}
	else if (Compare0(p->data->Position, binList->data->Position) == 0) {
		addDOP(binList, p->Next, w);
	}
	else if (Compare0(p->data->Position, binList->data->Position) > 0) {
		addDOP(binList, p->Left, w);
	}
	else if (Compare0(p->data->Position, binList->data->Position) < 0) {
		addDOP(binList, p->Right, w);
	}
}


void ObhodLeft(Vertex* p, int& count) {
	if (p != NULL) {
		ObhodLeft(p->Left, count);
		printf("%2d - %3d) %-32s %-5d %-24s %-10s\n", count + 1, p->w, p->data->FIO, p->data->Department, p->data->Position, p->data->Date);
		count++;
		ObhodLeft(p->Next, count);
		ObhodLeft(p->Right, count);
	}
}

void TreeSearch(char* str, Vertex*& p, int& count, bool& tree_find) {
	if (p) {
		int temp = Compare0(str, p->data->Position);                       // Ïîèñê â äåðåâå ïðîõîäèò ïî ýòîìó ïîëþ
		if (temp == 0) {
			tree_find = 1;
			printf("%2d - %3d) %-32s %-5d %-24s %-10s\n", count + 1, p->w, p->data->FIO, p->data->Department, p->data->Position, p->data->Date);
 			count++;
			TreeSearch(str, p->Next, count, tree_find);
		}
		else if (temp < 0)
			TreeSearch(str, p->Left, count, tree_find);
		else if (temp > 0)
			TreeSearch(str, p->Right, count, tree_find);
	}
}

void delete_tree(Vertex *&p) {
	if (p != NULL) {
		delete_tree(p->Next);
		delete_tree(p->Left);
		delete_tree(p->Right);
		delete p;
	}
}





void Sort(list **mas, int end)
{
    int i, j;
	list *buf;
    for (i = 0; i < end - 1; i++) {
        for (j = end - 1; j > i; j--) {
            if (Compare0(mas[j]->data->Position, mas[j-1]->data->Position) < 0) {
                buf = mas[j];
                mas[j] = mas[j - 1];
                mas[j - 1] = buf;
            }
        }
    }
}

void WeightSort(list **mas, int end)
{
    int i, j,v;
	list *buf;
    for (i = 0; i < end - 1; i++) {
        for (j = end - 1; j > i; j--) {
            if (W[j] > W[j - 1]) {
                v = W[j];
                W[j] = W[j - 1];
                W[j - 1] = v;
				buf = mas[j];
                mas[j] = mas[j - 1];
                mas[j - 1] = buf;
            }
        }
    }
}


/*------------------------Vertex----------------------------------*/






int Menu()
{
    // Остальной код без изменений...
	system("cls");
	setlocale(LC_ALL, "Russian");
	FILE* fp;
	int search_start=0;
	int search=N-1;
	
	list** queue = new list*[N];
	int count = 0;
	int flag = 0;
	bool tree_find = 0;
	Vertex* Root = NULL;	

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

    std::cout << "\t------------------------------Menu------------------------" << std::endl;
    std::cout << "\t1. View database" << std::endl;
    std::cout << "\t2. View sorted database (Digital Sort)" << std::endl;
    std::cout << "\t3. Bsearch" << std::endl;
    std::cout << "\t4. Exit" << std::endl;
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
        default:
            // Если введен символ, отличный от 1, 2, 3 или 4, возвращаемся в меню
            Menu();
            return 0;
    }

    switch (SoD)
    {
		int k;
		int counter, start, end;
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
				search = BSearch(mas,numb, queue);
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
		case 5: {
			if(flag == 0){
				cout << "First of all find something with B-Search \n";
				system("PAUSE");
				break;
			}
			if (Root != NULL) {
				delete_tree(Root);
				Root = NULL;
			}
			W = new int[4000];
            counter = 0;
            start = 0;
            end = 0;
			for (list *k = queue->next; k != NULL; k = k->next)
			{
				mas[counter] = k;
				counter++;
			}
			//ñîðòèðóåì âñå íàéäåííûå çàïèñè ïî äîëæíîñòè
        	Sort(mas, counter);	
            for (int i = 0; i < counter-1; i++) {
            	cout << mas[i]->data->Position << endl;
            	if(strcmp(mas[i]->data->Position, mas[i+1]->data->Position) != 0){
            		end = i;
            		cout << start << " - " << end << endl;
            		for(int j = start; j <= end; j++){
            			W[j] = end-start+1;
					}
					start = i+1;
				}
            }
			cout << start << " - " << counter-1 << endl;
			
            for(int j = start; j < counter; j++){
            	W[j] = counter-start;
			}
            //ñîðòèðîâêà çàïèñåé â ìàññèâå ïî âåñàì
        	WeightSort(mas, counter);
			for (int i =0; i < counter; i++)
			{
            //	cout << mas[i]->data->Position << endl;
				addDOP(mas[i], Root, W[i]);
			}
			ObhodLeft(Root, count);
			cout << endl << "Input key: ";
			char S[30];
			cin >> S;
			cout << endl;
			count = 0;
			TreeSearch(S, Root, count, tree_find);
			if (!tree_find) {
				cout << "Element was not find\n";
			}
			count = 0;
			system("Pause");
			Root = NULL;
			break;
		}

        case 4:
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

int BSearch(list **A, int Department, list** queue) {
    int l = 0, r = N, m = 0, fam_pos = 0;

    while (l < r) {
        m = (l + r) / 2;

        if (A[m]->data->Department == Department) {
            // Найден элемент, сохраняем его в очередь
            queue[fam_pos] = A[m];
            fam_pos++;
            return m;
        }
        if (A[m]->data->Department < Department)
            l = m + 1;
        else
            r = m - 1;
    }

    // Здесь можно добавить код для сохранения последнего элемента, если он не найден

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
    int i, g, N = 4000; // Просто для примера, замените на реальное значение N
    char n;
    SetConsoleCP(1251);

    i = 0;
    g = 0;
    bool exitLoop = false;

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
            std::cout << "\nEnter record Department: ";
            int recordDepartment;
            std::cin >> recordDepartment;

            if (recordDepartment > 0 && recordDepartment <= N) {
                g = ((recordDepartment - 1) / 20) * 20;
            } else {
                std::cout << "Invalid record Department. Press Enter to continue." << std::endl;
                while (_getch() != '\r') {} // Ожидаем нажатия Enter перед продолжением
            }
        } else {
            std::cout << "Invalid input. Exiting." << std::endl;
            return;
        }
    }
}





void Print_sort_index_mas(list **mas) {
    int i, g, N = 4000; // Просто для примера, замените на реальное значение N
    char n;
    SetConsoleCP(1251);

    // cout << "\t----------------------" << endl;
    // cout << "\t2. For 20 per click" << endl;
    // cout << "\t----------------------" << endl;

	// Используем _getch() для немедленного считывания символа

    
    i = 0;
	g = 0;
	bool exitLoop = false;

	while (!exitLoop) {
		for (i = g; i < N && i < g + 20; i++) {
			std::cout << i + 1 << "\t" << mas[i]->data->FIO << "\t" << mas[i]->data->Department << "\t" << mas[i]->data->Position << "\t" << mas[i]->data->Date << std::endl;
		}

		if (i >= N) {
			std::cout << "Reached the end of data." << std::endl;
			std::cout << "Press 'f' for forward, 'b' for backward, 'e' to exit, 'y' to continue, 'n' to go to a specific record: " << endl;
			n = _getch();
		} else {
			std::cout << "Press 'f' for forward, 'b' for backward, 'e' to exit, 'y' to continue, 'n' to go to a specific record: " << endl;
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
			std::cout << "\nEnter record Department: ";
			int recordDepartment;
			std::cin >> recordDepartment;

			if (recordDepartment > 0 && recordDepartment <= N) {
                g = ((recordDepartment - 1) / 20) * 20;
            } else {
                std::cout << "Invalid record Department. Press Enter to continue." << std::endl;
                while (_getch() != '\r') {} // Ожидаем нажатия Enter перед продолжением
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



