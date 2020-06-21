#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include "mylib.h"
#include "constants.h"

using namespace std;
bool checkInput = false;
bool checkUpdate = false;
bool checkE = false;
bool flag = false;
bool flagAE = false;
bool checkDelete = false;
bool dhAdd = false;
bool Tap = false;

char anE[] = "An Enter de chon tu           ";
char notF[] = "Khong co tu can tim kiem     ";
char ex[] = "Ban co muon thoat k (Y/N)     ";
string loai[] = {"Danh tu", "Tinh tu", "Dong tu", "Trang tu"};
//============================CTDL============================//
struct nodeMeanV {
	string mean;
	nodeMeanV* next;
};
typedef struct nodeMeanV* Mean;							//node Mean LKD

struct aWord {							
	string tu;
	string loai;
	string* vd[MAXVD];
	Mean tv;
};
struct nodeWord {							
	aWord info;
	nodeWord *left;
	nodeWord *right;
};
typedef struct nodeWord* Word;							//node Word LKK

struct listWord {										//list//Bang bam
	Word head = NULL;
	Word tail = NULL;
};

//============================Draw============================//
void loading(int Color) {
	setColor(Color);
	char l = 219;
	for (int i = xLoading; i <= xLoading + 100; i++) {
		gotoxy(i, yLoading);
		Sleep(15);
		cout << l;
	}
	gotoxy(xLoading, yLoading);
	Sleep(1000);
	cout<<"                                                                                                        ";//dung
}
string justifyStr(string style, int width) {		//can giua tu
	if (style.empty()) {
		return style;
	}else if (style.length() > width) {
		return style;
	}
	return string((width - style.length()) / 2, ' ') + style;
}
void ToMauHCN(int toadoX, int toadoY, int chieudai, int chieucao, int mauText) {
	setBGColor(BLACK_RED);
	for (int i = toadoY + 1; i < toadoY + chieucao; i++) {
		for (int j = toadoX + 1; j < chieudai + toadoX; j++) {
			gotoxy(j, i);
			cout << " ";
		}
	}
	setColor(63);
}
void XoaHCN(int toadoX, int toadoY, int chieudai, int chieucao, int mau) {
	normalBGColor();
	for (int j = toadoY + 1; j < toadoY + chieucao; j++) {
		for (int i = toadoX + 1; i < toadoX + chieudai; i++) {
			gotoxy(i, j);
			cout << " ";
		}
	}
}
void successAdd(string x) {
	ToMauHCN(wBoxMain + 10, 22, 50, 10, 95);
	gotoxy(wBoxMain + 12, 25);
	cout << justifyStr(x, 50);
	gotoxy(wBoxMain + 21, 28);
	system("pause");
	normalTextColor();
	normalBGColor();
	system("cls");
}
void introduce() {									//Intro
	system("color 1F");								//BG color system
	showCur(false);
	string a;
	ifstream fin("1.txt", ios::in);
	if (fin.good()) {
		while (!fin.eof()) {
			getline(fin, a);
			setColor(WHITE);
			Sleep(100);
			cout << a << endl;
		}
	}
	else { 		//Tra ve loi
		cout << "Lien ket voi File introduce khong thanh cong! " << "\n";
	}

	setColor(LIGHT_GREEN);
	gotoxy(xTen, yTen);
	cout << "HOTEN : PhamMinhQuang";
	gotoxy(xTen, yTen + 1);
	cout << "MSSV  : N18DCCN159";
	gotoxy(xTen, yTen + 2);
	cout << "LOP   : D18CQCN03-N";
	loading(LIGHT_YELLOW); 									//Loading
	showCur(false);
	
	gotoxy(55, 35);
	cout << "Hay an ENTER de tiep tuc!!!! ";
	normalBGColor();

	while (!kbhit()) {
		gotoxy(xLoading+18, yLoading);
		setColor(1 + rand() % 15);							//random
		Sleep(100);
		cout << "HOC VIEN CONG NGHE BUU CHINH VIEN THONG CO SO TP HO CHI MINH";
		showCur(false);
	}
	cin.ignore();
	normalBGColor();
	Beep(900, 900);											// am thanh
	return;
}

void under(int start, int end, int height) {
	gotoxy(start + 1, yBox + height);
	for(int i = 1 ; i < end; i++){
		cout<<"_";
	}
}
void drawBox(int x, int y,int width, int height){
	setBGColor(BLUE);
	char a = 201, 
		 b = 205, 
		 c = 187, 
		 d = 186, 
		 e = 200, 
		 f = 188;
	gotoxy(x, y);
	setColor(WHITE);
	cout << a;                
	for (int i = 1; i < width; i++) {										
		gotoxy(x + i, y);
		cout << b;
	}
	gotoxy(x + width, y);    
	cout << c;
	for (int i = 1; i < height; i++) {
		gotoxy(x, y + i);
		cout << d;
	}
	gotoxy(x, y + height);    
	cout << e;
	for (int i = 1; i < width; i++) {
		gotoxy(x + i, y + height);
		cout << b;
	}
	gotoxy(x + width, y + height);   
	cout << f;
	for (int i = 1; i < height; i++) {
		gotoxy(x + width, y + i);
		cout << d;
	}
}
void boxHelp(){
	setBGColor(BLUE);
	gotoxy(xHelp + 1, yHelp + 1);
	setColor(LIGHT_GREEN);
	cout << "\tInsert";
	setColor(WHITE);
	cout << " :Them tu   ";

	setColor(LIGHT_GREEN);
	cout << "Up / Down";
	setColor(WHITE);
	cout << " :Tim kiem tu   ";

	setColor(LIGHT_GREEN);
	cout << "Home";
	setColor(WHITE);
	cout << " :Ve dau DS tu dien   ";
	
	setColor(LIGHT_RED);
	cout << "Delete";
	setColor(WHITE);
	cout << " :Xoa tu   ";
	
	setColor(LIGHT_RED);
	cout << "Esc";
	setColor(WHITE);
	cout << " :Thoat chuong trinh   ";
}
void boxHelpInsert() {
	gotoxy(xHelp + 1, yHelp + 1);
	setColor(LIGHT_GREEN);
	cout << "\tF2";
	setColor(WHITE);
	cout << " :Luu tu    ";
	
	setColor(LIGHT_GREEN);
	cout << "F3";
	setColor(WHITE);
	cout << " :Chinh sua    ";
	
	setColor(LIGHT_GREEN);
	cout << "Right / Left";
	setColor(WHITE);
	cout << " :Chon loai tu   ";

	setColor(LIGHT_GREEN);
	cout << "Insert";
	setColor(WHITE);
	cout << " :Luu nghia cua tu   ";
	
	setColor(LIGHT_RED);
	cout << "Esc";
	setColor(WHITE);
	cout << " :Thoat chuong trinh   ";
}
void mainDraw(){
	char t = 3;
	drawBox(xBox, yBox, wBoxMain, hBoxMain);
	drawBox(xHelp, yHelp, wHelpMain, hHelpMain);
	drawBox(xBox + wBoxMain + 20, yBox, 40, 10);
	gotoxy(xBox + wBoxMain + 37, yBox + 2);
	setColor(LIGHT_YELLOW);
	cout<<t<<"Help"<<t;
	normalBGColor();
	under(xBox, wBoxMain, 4);
	under(xBox + wBoxMain + 20, 40, 4);
	boxHelp();
}

void insertDraw() {
	char t = 3;
	drawBox(xBox, yBox, wBoxMain, hBoxMain);
	drawBox(xHelp, yHelp, wHelpMain, hHelpMain);
	drawBox(xBox + wBoxMain + 20, yBox, 40, 10);
	gotoxy(xBox + wBoxMain + 37, yBox + 2);
	setColor(LIGHT_YELLOW);
	cout<<t<<"Help"<<t;
	under(xBox, wBoxMain, 4);
	under(xBox + wBoxMain + 20, 40, 4);
	setColor(LIGHT_YELLOW);
	gotoxy(xBox + 2, yBox + 7);
	cout<<"*Loai tu:";
	normalBGColor();
	under(xBox, wBoxMain, 9);
	boxHelpInsert();
}
//========================Chuanhoadulieu========================//
void chuanHoaTu(string& style) {							//chuan hoa tu
	for (int i = 0; i < style.length(); i++) {
		if (style[i] >= 65 && style[i] <= 90) {
			style[i] += 32;
		}	
	}
	if (!style.empty()) {
		while (style[style.length() - 1] == '-')			//xoa cuoi
			style.erase(style.length() - 1, 1);
	}
	for (int i = 0; i < style.length(); i++) {				//khoang - giua
		if (style[i] == '-' && style[i + 1] == '-') {
			style.erase(style.begin() + i);
			i--;
		}
	}
}
void chuanHoaVD(string& style) {
	chuanHoaTu(style);
	while (style[0] == ' ') {								//Xoa khoang trang dau
		style.erase(style.begin() + 0);
	}
	if (!style.empty()) {
		while (style[style.length() - 1] == ' ')
			style.erase(style.length() - 1, 1);
	}
	for (int i = 0; i < style.length(); i++) {				//khoang trang giua
		if (style[i] == ' ' && style[i + 1] == ' ') {
			style.erase(style.begin() + i);
			i--;
		}
	}
	if (style[0] >= 97 && style[0] <= 122) {
		style[0] -= 32;
	}
	for (int i = 1; i < style.length(); i++) {
			if (style[i] >= 65 && style[i] <= 90) {
				style[i] += 32;
			}	
	}
}
//============================XuLyDe============================//
void notify(bool flag, string tb, int height) {					//Thong bao
	Nocursortype(true);
	gotoxy(xNotify + 23, yNotify - 3 + height);
	Nocursortype(false);
	if(flag) {
		setColor(LIGHT_RED);
		cout << justifyStr(tb, 30);
		defaultColor();
	}else {
		setColor(LIGHT_GREEN);
		cout << justifyStr(tb, 30);
		defaultColor();
	}
}
void clearNotify(int height) {
	gotoxy(xNotify + 23, yNotify - 3 + height);
	cout<<"                                 ";
}
int hashKey(string key){		
	return (int)key[0] - 97; 					  	 //bam key
}
void insertLastMean(Mean& First, string x) {//them mean LKD
	Mean me = new nodeMeanV;
	me->next = NULL;			
	me->mean = x;
	if (First == NULL) {
		First = me;
	}else {
		Mean Last = First;
		while (Last->next != NULL) {
			Last = Last->next;
		}
		Last->next = me;							//last->next = null
	}												// LKK -> LKD
}
void insertEditMean(string x, Word& p) {
	Mean me = new nodeMeanV;
	me->next = NULL;			
	me->mean = x;
	Mean Last = p->info.tv;
	while (Last->next != NULL) {
		Last = Last->next;
	}
	Last->next = me;							//last->next = null
}
Word openFile(ifstream& fin) { 						// doc 1 thang						//note
	Word p = new nodeWord;
	p->left = NULL;
	p->right = NULL;
	Mean First = NULL;
	getline(fin,p->info.tu,'|'); 					//Tach tu
	if(p->info.tu.size() == 0) {
		delete(p);
		return NULL;
	}
	getline(fin,p->info.loai,'|');					//Tach loai tu
	string temp = "";
	while(true){
		getline(fin,temp,'|');						//Tach nghia~ LKD
		if(temp == ".") 		
			break;									//xong
		else{
			insertLastMean(First, temp);				
		}
	}
	p->info.tv = First;									
	for(int i = 0; i < 5; i++) {  								//TachVidu VD MCT
		string temp = "";
		getline(fin, temp, '|');
		if(!temp.empty()) {
			p->info.vd[i] = new string;
			*(p->info.vd[i]) = temp; 
		}else {
			p->info.vd[i] = NULL;
		}
	}
	fin.ignore(1); 									//Xoa \n
	return p;
}

void addWord(listWord& k, Word p) {						
	if (k.head == NULL) {
		k.head = k.tail = p; 						//Truong hop NUll
	}	
	else {	
		k.tail->right = p;							//Da co
		p->left = k.tail;							//tao lk Word voi listWord				
		k.tail = p;
	}
}
 void addHashTable(listWord k[],ifstream& fin) {	//Chen bang bam
	fin.open("dictionary1.txt", ios::in);	
	if(fin.fail()) {								//Check file
		flag = true;
		notify(flag, "Mo file that bai            ", 0);
		return;
	}
	while (!fin.eof()) {							//doc file
		Word p = openFile(fin);
		if (!p) break;
		int index = hashKey(p->info.tu);				//xac dinh key add Table
		addWord(k[index],p);							//add word vao table		
	}
	fin.close();	
}
int countMean(Word now) {
	int i = 0;
	Mean p = now->info.tv;
	for(p; p != NULL; p = p->next) {
		i++;
	}
	return i;
}
//==========================XulySearch===================//
bool comparev(string input, Word p) {				//compare
	string check = p->info.tu;
	if(check.find(input) == 0) return true; 		//find input trong w p
	return false;
}

Word searchInput(listWord k[], string input) {
	for(Word p = k[hashKey(input)].head; p != NULL; p = p->right) {
		if(comparev(input, p)) {
			return p;							//True
		}
	}
	return NULL;
}
Word searchHead(listWord k[], Word input) {		//Tim ve dau 
	if(input != NULL) {								
		Word head = input->left;					
		if(head != NULL) {
			return head;
		}else {							
			int index = hashKey(input->info.tu);				
			while(index > 0) {					// tra ve cuoi 
				--index;
				if(k[index].tail != NULL) {
					return k[index].tail;
				}
			}
		}
	}
	return NULL;
}
Word searchTail(listWord k[], Word input) {		//Tim ve cuoi
	if(input != NULL) {
		Word tail = input->right;					
		if(tail != NULL) {
			return tail;
		}else {
			int index = hashKey(input->info.tu);	//tra ve dau
			while(index < 25) {
				++index;
				if(k[index].head != NULL) 
					return k[index].head;          
			}
		}
	}
	return NULL;
}
Word searchEnd(listWord k[], string input, Word start) {	//Chan cuoi cat thang cuoi
	Word p = start;											//node can tim
	Word temp = NULL;
	for(int i = 0; i < sizeDp  && p; i++) {
		temp = searchTail(k, p);							//start
		if(temp && comparev(input, temp)) {				//tim kiem theo tu dien khong phai loc
			p = temp;									//2 cach
		}else {									
			return p;
		}					
	}
	return p;
}
void writeFile(listWord k[], ofstream& fout) {
	Word temp;
	for(int i = 0; i < 26; i++) {
		for(temp = k[i].head; temp != NULL; temp = temp->right) {
			fout << temp->info.tu << "|";
			fout << temp->info.loai << "|";
			Mean tempM = temp->info.tv;
			while(tempM != NULL) {
				fout << tempM->mean << "|";
				tempM = tempM->next;
			}
			fout << ".|";
			int j = 0;
			for(int i = 0; i < 5; i++) {
				if(temp->info.vd[i] != NULL) {
					fout<<*(temp->info.vd[i])<<"|";
				}else{
					fout<<"|";
				}
			}
			fout<<"\n";
		}
	}
}
/*Word searchDetail(listWord k[], string input) {
	Word p = searchInput(k, input);	
	if(p == NULL) {								 	//NULL
		flag = true;
		notify(flag, notF, 0);
	}else {
		flag = false;			
		notify(flag, anE, 0);						//thong bao tim thay
		int i = 1;	
		while(p != NULL){						
			gotoxy(xBox + 2, yBox + i + 4);
			if(p->info.tu == input) {		
				cout<< p->info.tu;
				break;
			}
			cout<<p->info.tu;
			cout<<endl;
			p = p->right;
			i++;
		}
	}
}*/

Word displayHead(listWord k[]) {			//hien thi thang dau tien neu k co input
	Word dpHead = NULL;			
	for(int i = 0; i < 26; i++) {
		if(k[i].head != NULL) {
			dpHead = k[i].head;
			return dpHead;
		}
	}
	return dpHead;
}
void clearDisplay(int start, int end) {
	for(int i = start; i < end; i++) {
		cout<<" ";
	}
}
void hightLight() {
	setColor(BLACK_PEN);
	setBGColor(LIGHT_BLUE);
}

void showListWord(listWord k[], Word head, Word tail, Word now) {
	int i = 0;
	for (Word check = head; check != searchTail(k,tail); check = searchTail(k,check)) {
		gotoxy(xBox + 1, yBox + 5 + i);
		if(check == now) {
			hightLight();								  	//tu hien tai hightlight
			cout<< check->info.tu;
			clearDisplay(check->info.tu.size(),wBoxMain - 1); //clear man hinh
			normalBGColor();
		}else {
			cout<< check->info.tu;
			clearDisplay(check->info.tu.size(),wBoxMain - 1);
		}
		i++;
	}
	for (int j = yBox + i + 5; j < hBoxMain + 10; j++) {	//clear nhung thang k can tim
		gotoxy(xBox + 1, j);
		cout<<"                                                 ";   //clearDisplay
	}
}
bool checkImport(char import, string input) {
	if(((import >= 'a' && import <= 'z') ||
		(import >= 'A' && import <= 'Z'  ||
		(import == '-') && input.size() > 0)) && input.size() < 40)
		return true;
	return false;
}
bool checkImportS(char import, string input) {
	if((import == '.' || 
	   import == '?'  || 
	   import == '"'  || 
	   import == '/'  ||
	   import == '|'  ||
	   import == '-' 
		) && input.size() > 0)
	return true;
	return false;
}
//==========================nodeMeanPointrer===========================//
Mean nodePointer(int index, Word a) {				//tra ve (p) o vt index
	Mean p = a->info.tv;
	int i = 0;
	while(p != NULL && i < index) {
		p = p->next;
		i++;
	}
	return(p);
}
//=========================ShowIFo=====================//
void showM(int i, int pos, Word now) {
	int index = 0;
	while(i <= pos && index < 4) {
		Mean temp =	nodePointer(i, now);
		gotoxy(xBox + 9, yBox + 13 + index);
		cout<<temp->mean;
		clearDisplay(temp->mean.size(), wBoxMain - 9);
		index++;
		i++;
	}	
}
void showShowMean(Word now, int pos, bool Tap) {
	int i = pos - 3;
	int t = 0;
	int k = 0;
	int eW = countMean(now);
	char import;
	if(Tap) {
		while(true) {
			import = _getch();
			if(import == KEY_UP && t > 0)  {
				t--;
				showM(t, pos, now);
			}else if(import == KEY_DOWN && t < pos - 4) {
				t++;
				showM(t, pos, now);
			}else if(import == ESC) {
				return;
			}else if(import != KEY_UP && t > 0) {
				eW = pos - 4;
				showM(eW, pos, now);
			}
		}
	}
	showM(i, pos, now);
	Tap = false;
}
void showMean(Word now, int& j) {
	Mean p = now->info.tv;
	while(p != NULL) {
		gotoxy(xBox + 2, yBox + 8 + j);
		cout<<"- "<< p->mean;
		j++;
		p = p->next;
	}
}
void showNowWord(Word now) {
	system("cls");
	char import;
	Nocursortype(true);
	if(now == NULL) {
		flag = true;
		notify(flag, "Loi                 ", 0);
	}else {
		flag = false;
		notify(flag, "An F4 de chinh sua tu          ", 0);
	}
	mainDraw();
	string tu = now->info.tu;
	gotoxy(xBox + 2, yBox + 2);
	cout<<justifyStr(tu, wBoxMain - 4)<<endl;
	gotoxy(xBox + 2, yBox + 6);
	cout<<"_____"<<now->info.loai<<endl;
	int j = 0;
	gotoxy(xBox + 2, yBox + 7);
	cout<<"************Nghia: ";
	showMean(now, j);
	gotoxy(xBox + 2, yBox + 9 + j);
	cout<<"Example:";
	if(now->info.vd[0] == NULL) {
		flag = true;
		notify(flag, "    Tu nay khong co vi du       ", 0);
	}else {
		int i = 0;
		while(i <= 4) {	
			if(now->info.vd[i] != NULL){
				gotoxy(xBox + 2, yBox + 11  + i + j);
				string temp = *(now->info.vd[i]);
				chuanHoaVD(temp);
				cout<<"- "<<temp;
			}else {
				break;
			}
			i++;
		}
	}
}
//============================Xuly UP/DOWN Search==========================//
void keyUpSearch(Word& headSearch, Word& tailSearch, Word& nowSearch, listWord k[], string input) {
	Word temp = searchHead(k, nowSearch);
	if(temp != NULL && comparev(input, temp)) {					//chan
		if(nowSearch == headSearch) {
			headSearch = searchHead(k, headSearch);				//UP => -1 
			tailSearch = searchHead(k, tailSearch);				//UP => -1
		}
		nowSearch = searchHead(k,nowSearch);
	}else {
		flag = true;
		notify(flag,"DOWN                  ", 0);		
	}
}
void keyDownSearch(Word& headSearch, Word& tailSearch, Word& nowSearch, listWord k[], string input) {   
	Word temp = searchTail(k, nowSearch);
	if(temp != NULL && comparev(input, temp) ) {				//chan
		if(nowSearch == tailSearch) {
			headSearch = searchTail(k, headSearch);				//DOWN => +1
			tailSearch = searchTail(k, tailSearch);				//DOWN => +1
		}
		nowSearch = searchTail(k, nowSearch);
	}else {
		flag = true;
		notify(flag,"Up                    ", 0);		
	}
}
//============================CheckExist================================//
bool checkWordExist(listWord k[], string word) {
	int index = hashKey(word);
	Word p = k[index].head;
	while(p != NULL) {
		if(p->info.tu == word) return true;
		p = p->right;
	}
	return false;
}
bool checkMeanExist(Mean First, string mean) {
	for (Mean p = First;  p != NULL ; p = p->next) 
        if (p->mean == mean){
        	return true;
		}
	return false;
}
bool checkMeanExistEdit(Word now, string mean) {
	for (Mean p =  now->info.tv;  p != NULL ; p = p->next) 
        if (p->mean == mean){
        	return true;
		}
	return false;
}
bool checkExampleExist(int i, int n, Word p, string input) {
	int dem = 0;
	string temp = input;
	for(int j = 0; j < n; j++) {
		if(j != i){
			if(temp == *p->info.vd[j]) dem++;
		}
	}
	if (dem == 1) {
		return true;
	}else return false;
}
void dhAddWord(int i, string& input, char import, int chon, int& pos, int &d, int& j, Word now, bool& checkDelete) {
	int k = 0;
	if (now == NULL && dhAdd == true || checkDelete == true || flagAE == true) {
		bool check = false;
		pos = 0;
		j = 0;
		int t = 0;
		if(pos < 4 || checkDelete) {
			Mean p = now->info.tv;
			while (p != NULL && pos < 4) {
				gotoxy(xBox + 3, yBox + 12);
				cout<<"Nghia:";
				pos++;
				gotoxy(xBox + 9, yBox + 12 + pos);
				cout<<p->mean;
				clearDisplay(p->mean.size(), wBoxMain - 9);
				gotoxy(xBox + 9, yBox + 12 + pos + 1);
				clearDisplay(0, wBoxMain - 9);
				t = pos;
				p = p->next;
			}
			while (t < 4) {
				gotoxy(xBox + 9, yBox + 12 + t + 1);
				cout<<"                                      ";	
				t++;
			}
			under(xBox, wBoxMain, yBox + 4 + pos);
			gotoxy(xBox + 1, 2 * yBox + 4 + pos + 1);
			clearDisplay(xBox + 1, wBoxMain + 20);
		}else if(d > 4 && checkDelete) {
			Mean p = now->info.tv;
			int i = 0;
			int kt = d - 3;
			int index = 0;
			for(p; p != NULL; p = p->next) {
				if(i >= kt - 1) {
					gotoxy(xBox + 9, yBox + 13 + index);
					cout<<p->mean;
					clearDisplay(p->mean.size(), wBoxMain - 9);
					index++;
				}
				pos++;
				i++;
			}
			checkDelete = false;
		}
		while (j < 5) {
			bool check = false;
			if(now->info.vd[j] != NULL) {
				gotoxy(xBox + 3, yBox + 17 + pos - 1);
				cout<<"                               ";
				gotoxy(xBox + 3, yBox + 17 + pos);
				if(j == 0 && check == false) cout<<"Vidu:";
				if(checkDelete == true) {
					gotoxy(xBox + 3, yBox + 17 + pos + 1);
					cout<<"                               ";
				}	
				gotoxy(xBox + 4, yBox + 19 + pos + j);
				cout<<*now->info.vd[j];
				string temp = *now->info.vd[j];
				clearDisplay(temp.size(), wBoxMain - 5);
				j++;
				check = true;
			}else {
				break;
			}
		}
		gotoxy(xBox + 4, yBox + 19 + pos + j);
		clearDisplay(0, wBoxMain - 4);
		check = true;
		dhAdd = false;
		flagAE = false;
		checkDelete = false;
	}	
	if (!now->info.loai.empty() && pos == 0){
		gotoxy(xBox + 14, yBox + 7);
		cout<<now->info.loai;
	}else {
		gotoxy(xBox + 14, yBox + 7);
		cout<<loai[chon];
	}
	if (j == 0 && k == 0) {
		gotoxy(xBox + 3, yBox + 17 + pos);
		cout<<"Vidu:";
		setColor(LIGHT_RED);
		cout<<"  Chua co vi du";
		if(input.size() == 0) {
			gotoxy(xBox + 3, yBox + 17 + pos + 1);
			cout<<"                               ";
		}
		normalTextColor();
	}else {
		gotoxy(xBox + 3, yBox + 17 + pos);
		cout<<"Vidu:";
		setColor(LIGHT_RED);
		cout<<"                                   ";
		normalBGColor();	
	}
	gotoxy(xBox + 2 + input.size(), yBox + 2);
	if (now->info.tu.empty() && input.empty() && i == 1) {	
		cout<<"Nhap tu moi:";
		clearDisplay(12, wBoxMain - 2);
		gotoxy(xBox + 2, yBox + 2);
	}else if(!now->info.tu.empty() && i == 1 && input.empty()) {
		gotoxy(xBox + 2, yBox + 2);
		clearDisplay(0, wBoxMain - 3);
		gotoxy(xBox + 2, yBox + 2);
		cout<<now->info.tu;
		input = now->info.tu;
	}
	if(i == 2) 	{
		if(import == ENTER) {
			flag = false;
			notify(flag, "An Right/Left de chon loai tu  ", 0);
		}else {
			flag = false;
			notify(flag, "An Enter de chon loai tu       ", 0);
		}
		gotoxy(xBox + 14, yBox + 7);
	}
	if(i == 3) 	{
		flag = false;
		if(pos > 0) {
			notify(flag, "An Insert de luu nghia         ", 0);
		}else {
			notify(flag, "Them nghia cua tu				 ", 0);
		}
		gotoxy(xBox + 3, yBox + 12);
		cout<<"Nghia:";
		gotoxy(xBox + 9 + input.size(), yBox + 12);	
	}
	if(i == 4) {
		flag = false;
		notify(flag, "Them vi du/F2 de luu				  ", 0);
		if(j == 5 && !input.empty()) notify(flag, "Da co du vi du				", 1);
		gotoxy(xBox + 9 + input.size(), yBox + 18 + pos);
	}
}
//=========================Delete=======================//
void deleteFMean(Word& a, Mean &First) { 	
	Mean p = NULL;
	p =	a->info.tv;
	if(p == NULL) {
		return;
	}
	First = p->next;
	delete p;
	return;
}
void deleteMean(Word& a, Mean& p ,int index, int& pos, Mean& First) {
    Mean del;
    del = nodePointer(index - 1, a);
	if(index == 0) {
		if(pos != 1) {
			deleteFMean(a, First);
			a->info.tv = First;
			checkDelete = true;
			pos--;
			return;
		}else{
			Nocursortype(TRUE);
			notify(flag, "Can it nhat 1 nghia cua tu	", 1);
		}
	}else {
		if((del == NULL) || (del->next == NULL))  return;
		notify(flag, "Nhan Enter de xoa nghia			", 0);
	    del->next = p->next;
	    delete p;
	    checkUpdate = true;
	    checkDelete = true;
	    pos--;	 
	    return;
	}
}
void deleteExample(string* ex[],int index, int& j) {
	string* temp = ex[index];
	for (int i = index + 1; i < j; i++)
		ex[i - 1] = ex[i];
	ex[j - 1] = NULL;
	j--;
	delete temp;
}
void deleteContent(Word& now) {
	Mean First = now->info.tv;
	while (First != NULL) {
		deleteFMean(now, First);
		now->info.tv = First;
	}
	for (int i = 0; i < 5 && now->info.vd[i] != NULL; i++)
	delete now->info.vd[i];
	delete now;
}
void deleteWord(listWord k[], Word& now) {
	if (now) {
		int index = hashKey(now->info.tu);
		Word head = k[index].head;
		Word tail = k[index].tail;
		if (head == now) {						 //Dau
			if(!head->right) {
				head = tail = NULL;
			}else {
				head = head->right;
				head->left = NULL;
			}
		}else if (tail == now) {				//cuoi
			tail = tail->left;
			tail->right = NULL;
		}else {									//giua
			Word nowL = now->left; 
			Word nowR = now->right;		//es
			nowR->left = nowL;
			nowL->right = nowR;
		}
		k[index].head = head;			//Cap nhat lai bang bam
		k[index].tail = tail;
		deleteContent(now);				//Xoa toan bo tu
	}
}
//=========================VitriDH=======================//
void indexEdit(int index, int pos ,int x, string temp) {
	gotoxy(xBox + wBoxMain - 2, yBox + pos + index + 1);
	cout<< " ";
	gotoxy(xBox + wBoxMain - 2, yBox + pos + index - 1);
	cout<< " ";
	gotoxy(xBox + wBoxMain - 2, yBox + pos + index);
	setBGColor(WHITE);
	cout<< " ";
	normalBGColor();
	gotoxy(xBox + x + temp.size(), yBox + pos + index);
}
//============================EditMean==================================//
void editMean(Word& a, int start, int& pos, Mean& First) {
	int i = start;
	int index = 0;
	int d = 1;
	Mean p = NULL;
	Mean del = NULL;
	string temp = "";
	if(i == start) {
		p = nodePointer(i, a);
		temp = p->mean;
		indexEdit(index, 13, 9, temp);                   //nhan vi tri thanh sang dau tien
	}
	char import;
	while(true) {
		Nocursortype(true);
		import = _getch();
		Nocursortype(false);
		if (import == 0 || import == -32) {
			import = _getch();
			if (import == KEY_UP) {
				if(i > start) {
					i--;
					index--;
				} 
			}
			if (import == KEY_DOWN) {
				if(i < pos - d) {
					i++;
					index++;
				}
			}
			p = nodePointer(i, a);
			temp = p->mean;
			indexEdit(index, 13, 9, temp);
			if(import == DELE){
				notify(flag, "Nhan Enter de xoa", 1);
				import = _getch();
				if(import == ENTER) {	
					deleteMean(a, p, i, pos, First);
					gotoxy(xBox + wBoxMain - 2, yBox + 13 + index);
					cout<< " ";
					flag = true;
					return;
				}
			}	
		}else if ((checkImport(import, temp) || checkImportS(import, temp))
				 && import != ENTER && import != DELE){
			temp += import;
			cout<<import;
		}else if(import == SPACE) {
				temp += " ";
		}else if (import == BACKSPACE && !temp.empty()) {   		//Xoa
			temp.erase(temp.size() - 1, 1);
			cout << "\b \b";								 		// \b\b Backspace
		}else if (import == ENTER && temp.size() > 0) {
			chuanHoaVD(temp);
			if(checkMeanExistEdit(a, temp)) {
				flag = true;										//Notify
				notify(flag, "Da ton tai nghia nay", 1);
				gotoxy(xBox + 9, yBox + 13 + i);
				cout<<temp;
			}else {
				p->mean = temp;
				gotoxy(xBox + 9, yBox + 13 + i);
				cout<<temp;
				temp = "";
				gotoxy(xBox + wBoxMain - 2, yBox + 13 + i);
				cout<< " ";
				notify(flag, "    					      ", 1);
				return;
			}
		}else if(import == ESC) {
			gotoxy(xBox + wBoxMain - 2, yBox + 13 + index);
			cout<< " ";
			gotoxy(xBox + 9, yBox + 13 + index);
			cout<<p->mean;
			return;
		}
	}
}
//============================EditExample===============================//
void editExample(int n, Word& a, int pos) {
	int i = 0;
	string temp = "";
	if(i == 0) {
		temp = *a->info.vd[0];
		indexEdit(i, pos + 19, 4 , temp);
	}
	char import;
	while(true) {
		indexEdit(i, pos + 19, 4, temp);
		Nocursortype(true);
		import = _getch();
		Nocursortype(false);
		if (import == 0 || import == -32) {
			import = _getch();
			if (import == KEY_UP) {
				if(i > 0) i--;
			}	
			if (import == KEY_DOWN) {
				if(i < n-1) i++;
			}
			temp = *a->info.vd[i];
			indexEdit(i, pos + 19, 4 , temp);
			if (import == DELE) {
				notify(flag, "An Enter de xoa vi du ", 0);
				import = _getch();
				if (import == ENTER) {
					deleteExample(a->info.vd, i , n);
					checkDelete = true;
					return;
				}
				notify(flag, "							", 0);
			}
		}else if ((checkImport(import, temp) || checkImportS(import, temp))
				  && import != ENTER && import != DELE) {
			temp += import;
			cout<<import;
			clearDisplay(temp.size(), wBoxMain - 4);
		}else if(import == SPACE) {
				temp += " ";
		}else if (import == BACKSPACE && !temp.empty()) {   		//Xoa
			temp.erase(temp.size() - 1, 1);
			cout << "\b \b";								 		// \b \b Backspace
		}else if (import == ENTER && temp.size() > 0) {
			chuanHoaVD(temp);
			if(!checkExampleExist(i, n, a, temp)) {
				*(a->info.vd[i]) = temp;
				gotoxy(xBox + 4, yBox + 19 + pos + i);
				cout<<temp;
				temp = "";
				gotoxy(xBox + wBoxMain - 2, yBox + 19 + pos + i);
				cout<< " ";
				clearNotify(1);
				break;
			}else {
				flag = true;
				notify(flag, "Da ton tai vi du nay", 1);
			}
		}else if(import == ESC) {
			gotoxy(xBox + wBoxMain - 2, yBox + 19 + pos + i);
			cout<< " ";
			gotoxy(xBox + 4, yBox + 19 + pos + i);
			string temp = *a->info.vd[i];
			cout<<temp;
			clearDisplay(temp.size(), wBoxMain - 5);
			break;
		} 
	}
}
Word addW(listWord k[], Word now, bool flagAE);
void editWord(listWord k[], Word& now) {
	system("cls");
	insertDraw();                                                // Ve khung insert
	string input = "";
	int i = 1;
	int chon = 0;
	int j = 0;
	int pos = 0;
	int tempPos = 0;
	int d = countMean(now);
	cout<<d;
	dhAdd = true;
	flagAE = true;
	Mean First = NULL;
	char import;
	while(true) {
		dhAddWord(i, input, import, chon , pos, d, j, now, checkDelete);
		Nocursortype(true);
		import = _getch();
		Nocursortype(false);
		switch(i) {
			case 1: {
				if(import == ENTER && !input.empty()) {
					chuanHoaTu(input);
					if(!checkWordExist(k,input)) {
						setColor(LIGHT_GREEN);
						gotoxy(xBox + 2, yBox + 2);
						now->info.tu = input;
						cout<<justifyStr(input, wBoxMain - 4);
						input = "";			
						i++;
						setColor(WHITE);
					}else {
						flag = true;
						notify(flag, "Da ton tai tu dang them         ", 0);	
					}
				}
				break;
			}
			case 2: {
				if(now->info.loai.empty() && (import == 0 || import == -32)) {
				    import = _getch();
				    gotoxy(xBox + 14, yBox + 7);
				    char l = 16;
				    char r = 17;
				    switch (import) {
				   		case LEFT: if (chon > 0) {
					                chon --;
					                cout<< loai[chon]<<"      ";		
				  			    }  
				  			break;
				  		case RIGHT: if (chon < 3){
					                chon ++;
					                cout<< loai[chon] <<"      ";		
				  			    }
				  			break;
				    }	  
			    }else if(!now->info.loai.empty()) {
			    	if(import == KEY_UP)	i--;
				}
			    if(import == ENTER && now->info.loai.empty()) {
			    	now->info.loai = loai[chon];
			    	i++;
				}else if(import == ENTER && !now->info.loai.empty()){
					now->info.loai = "";
				}
				break;
			}
			case 3: {
				if(import == ENTER && !input.empty()) {
					chuanHoaVD(input);
					if(!checkMeanExist(First, input)) {
						insertEditMean(input, now);
						if(pos < 4){
							gotoxy(xBox + 9, yBox + 13 + pos);
							cout<<input;
							gotoxy(xBox + 1, 2 * yBox + 4 + pos);
							clearDisplay(xBox + 1, wBoxMain + 20);
							pos++;
							d = pos;
							under(xBox, wBoxMain, yBox + 4 + pos);
						}else {
							showShowMean(now, d, Tap);
							d++;
						}
						input = "";
						gotoxy(xBox + 9 + input.size(), yBox + 12);
						cout<<"                                         ";
						gotoxy(xBox + 9 + input.size(), yBox + 12);
						notify(flag, "   					       ", 1);
						gotoxy(xBox + 3, yBox + 16 + pos );
						cout<<"                        ";
						gotoxy(xBox + 3, yBox + 17 + pos);
						if(j == 0) cout<<"Vidu:";
						gotoxy(xBox + 3, yBox + 18 + pos);
						clearDisplay(4, wBoxMain - 4);
						int k = 0;
						while(k < j && pos <= 4 && j > 0) {
							gotoxy(xBox + 4, yBox + 19 + pos + k);
							clearDisplay(4, wBoxMain - 4);
							gotoxy(xBox + 4, yBox + 19 + pos + k);
							cout<< *(now->info.vd[k]);
							k++;
						}
					}else {
						flag = true;
						notify(flag, "Da ton tai nghia nay        ", 1);	
					}
				}
				if(import == SPACE && input.size() > 0) {
					input += " ";
				}
				break;
			}
			case 4: {		
				if(import == ENTER && j < 5 && !input.empty()) {
					chuanHoaVD(input);
					tempPos = pos;
					if(!checkExampleExist(100 ,j, now, input)) {
						now->info.vd[j] = new string;
						*(now->info.vd[j]) = input;
						gotoxy(xBox + 4, yBox + 19 + pos + j);
						cout<<input;
						input = "";
						gotoxy(xBox + 4 + input.size(), yBox + 18 + pos);
						cout<<"                                              ";
						gotoxy(xBox + 4 + input.size(), yBox + 18 + pos);
						j++;
					}else {
						flag = true;
						notify(flag, "Da ton tai vi du nay         ", 1);
					}
				}else if(import == SPACE && input.size() > 0) {
					input += " ";
				}
				break;
			}
		}
		if(import == 0 || import == -32) {
			import = _getch();
			switch(import) {
				case KEY_UP: {
					if(i > 1) i--;
					break;
				}
				case KEY_DOWN: {
					if(i == 1 && !now->info.tu.empty()) {
						i++;
					}				
					if(i == 2 && !now->info.loai.empty()) {
						i++;
					}
					if(i == 3 && pos != 0) {
						i++;
					}
					input = "";
					break;
				}
				case KEY_F2: {
					flag = true;
					if(i == 1 && now->info.tu.empty()) notify(flag, "Ban chua nhap tu           ", 1);
					if(i == 3 && now->info.tv == NULL) notify(flag, "Tu can co it nhat 1 nghia  ", 1);
					if(!now->info.tu.empty() && !now->info.loai.empty() && now->info.tv != NULL){
						gotoxy(15,1);
						i = 5;
						successAdd("Dang ky thanh cong");
						checkUpdate = true;
						notify(flag,"                            ",1);
					}
					break;
				}
				case KEY_F3: {
					if (i == 3 && now->info.tv != NULL) {
						int start = 0;
						editMean(now, start, pos, First);
					}else if (i == 3 && now->info.tv != NULL) {
						flag = true;
						notify(flag, "Chua co nghia de chinh sua", 0);
					}	
					if (i == 4 && now->info.vd[0] != NULL) 
						editExample(j, now, pos);
					break;
				}
				case KEY_INSERT:{
					if(i == 3) {
						i++;
					}
					break;
				}
			}
		}else if(import == TAB && i == 3 && d > 4) {
			Tap = true;
			showShowMean(now, d, Tap);
		}else if((checkImport(import, input) && i != 2)) {
			input +=import;
			cout<<import;
			clearDisplay(input.size(), 40);
			notify(flag, "                            ", 0);
			notify(flag, "                            ", 1);
		}else if (import == BACKSPACE && !input.empty()) {   				 //Xoa
			input.erase(input.size() - 1, 1);
			cout << "\b";
			cout << " ";
			cout << "\b";
			notify(flag, "                              ", 1);						 				 //\b \b xoa chu
		}
		if (i == 5) {
			while(j < 5) {
				now->info.vd[j] = NULL;
				j++;
			}
			break;
		}
		if (import == ESC) {
			flag = true;
			notify(flag, " Ban muon thoat khoi che do them ", 0);
			while(true) {
				import = _getch();
				if(import == ENTER && checkUpdate != false) {
					flag = true;
					notify(flag, "Da co su thay doi cua tu", 1);
				}else{
					notify(flag, "                        ", 1);
				}
				if(import == ENTER && checkUpdate == false) {
					gotoxy(xBox + 2 + input.size(), yBox + 2);
					cout<<"                                        ";
					//delete(now);
					break;
				}else if(import == ESC && (import != ENTER || import != -32 || import != 0)) {
					notify(flag, "  							  ", 0);
					break;	
				}													//check dk 
			}
		}
	}
}
//============================XulyInsertWord============================//
Word addW(listWord k[], Word now) {
	system("cls");
	insertDraw();                                                // Ve khung insert
	string input = "";
	int i = 1;
	int chon = 0;
	int j = 0;
	int pos = 0;
	int tempPos = 0;
	int d = 0;
	dhAdd = true;
	if(now == NULL) now = new nodeWord;
	Mean First = NULL;
	for (int i = 0; i < 5; i++) {
		now->info.vd[i] = NULL;
	}
	char import;
	while(true) {
		dhAddWord(i, input, import, chon , pos, d, j, now, checkDelete);
		Nocursortype(true);
		import = _getch();
		Nocursortype(false);
		switch(i) {
			case 1: {
				if(import == ENTER && !input.empty()) {
					chuanHoaTu(input);
					if(!checkWordExist(k,input)) {
						setColor(LIGHT_GREEN);
						gotoxy(xBox + 2, yBox + 2);
						now->info.tu = input;
						cout<<justifyStr(input, wBoxMain - 4);
						input = "";			
						i++;
						setColor(WHITE);
					}else {
						flag = true;
						notify(flag, "Da ton tai tu dang them          ", 0);	
					}
				}
				break;
			}
			case 2: {
				if(now->info.loai.empty() && (import == 0 || import == -32)) {
				    import = _getch();
				    gotoxy(xBox + 14, yBox + 7);
				    switch (import) {
				   		case LEFT: if (chon > 0) {
					                chon --;
					                cout<< loai[chon]<<"      ";		
				  			    }  
				  			break;
				  		case RIGHT: if (chon < 3){
					                chon ++;
					                cout<< loai[chon] <<"      ";		
				  			    }
				  			break;
				    }	  
			    }else if(!now->info.loai.empty()) {
			    	if(import == KEY_UP)	i--;
				}
			    if(import == ENTER && now->info.loai.empty()) {
			    	now->info.loai = loai[chon];
			    	i++;
				}else if(import == ENTER && !now->info.loai.empty()){
					now->info.loai = "";
				}
				break;
			}
			case 3: {
				if(import == ENTER && !input.empty()) {
					chuanHoaVD(input);
					if(!checkMeanExist(First, input)) {
						insertLastMean(First, input);	
						now->info.tv = First;
					    if(pos < 4){
							gotoxy(xBox + 9, yBox + 13 + pos);
							cout<<input;
							gotoxy(xBox + 1, 2 * yBox + 4 + pos);
							clearDisplay(xBox + 1, wBoxMain + 20);
							pos++;
							d = pos;
							under(xBox, wBoxMain, yBox + 4 + pos);
						}else {
							showShowMean(now, d, Tap);
							d++;
						}
						input = "";
						gotoxy(xBox + 9 + input.size(), yBox + 12);
						cout<<"                                         ";
						gotoxy(xBox + 9 + input.size(), yBox + 12);
						notify(flag, "   					       ", 1);
						gotoxy(xBox + 3, yBox + 16 + pos );
						cout<<"                        ";
						gotoxy(xBox + 3, yBox + 17 + pos);
						if(j == 0) cout<<"Vidu:";
						gotoxy(xBox + 3, yBox + 18 + pos);
						clearDisplay(4, wBoxMain - 4);
						int k = 0;
						while(k < j && pos <= 4 && j > 0) {
							gotoxy(xBox + 4, yBox + 19 + pos + k);
							clearDisplay(4, wBoxMain - 4);
							gotoxy(xBox + 4, yBox + 19 + pos + k);
							cout<< *(now->info.vd[k]);
							k++;
						}
					}else {
						flag = true;
						notify(flag, "Da ton tai nghia nay       ", 1);	
					}
				}
				if(import == SPACE && input.size() > 0) {
					input += " ";
				}
				break;
			}
			case 4: {
				if(import == ENTER && j < 5 && !input.empty()) {
					chuanHoaVD(input);
					tempPos = pos;
					if(!checkExampleExist(100 ,j, now, input)) {
						now->info.vd[j] = new string;
						*(now->info.vd[j]) = input;
						gotoxy(xBox + 4, yBox + 19 + pos + j);
						cout<<input;
						input = "";
						gotoxy(xBox + 4 + input.size(), yBox + 18 + pos);
						cout<<"                                              ";
						gotoxy(xBox + 4 + input.size(), yBox + 18 + pos);
						j++;
					}else {
						flag = true;
						notify(flag, "    Da ton tai vi du nay        ", 1);
					}
				}else if(import == SPACE && input.size() > 0) {
					input += " ";
				}
				break;
			}
		}
		if(import == 0 || import == -32) {
			import = _getch();
			switch(import) {
				case KEY_UP: {
					if(i > 1) i--;
					break;
				}
				case KEY_DOWN: {
					if(i == 1 && !now->info.tu.empty()) {
						i++;
					}				
					if(i == 2 && !now->info.loai.empty()) {
						i++;
					}
					if(i == 3 && pos != 0) {
						i++;
					}
					input = "";
					break;
				}
				case KEY_F2: {
					flag = true;
					if(i == 1 && now->info.tu.empty()) notify(flag, "Ban chua nhap tu", 1);
					if(i == 3 && First == NULL)  notify(flag, "Tu can co it nhat 1 nghia", 1);
					if(!now->info.tu.empty() && !now->info.loai.empty() && First != NULL){
						gotoxy(15,1);
						i = 5;
						successAdd("Dang ky thanh cong");
						checkUpdate = true;
						notify(flag,"                            ",1);
					}
					break;
				}
				case KEY_F3: {
					if (i == 3 && now->info.tv != NULL) {
						if(pos < 4) {
							int start = 0;
							if(pos  < 4) {
								start = 0;
							}else {
							    start = pos - 3;	
							}
							editMean(now, start, pos, First);
						}else{
							int start = d - 4;
							editMean(now, start, d, First);
						}
					}else if (i == 3 && now->info.tv != NULL) {
						flag = true;
						notify(flag, "Chua co nghia de chinh sua", 0);
					}	
					if (i == 4 && now->info.vd[0] != NULL) 
						editExample(j, now, pos);
					break;
				}
				case KEY_INSERT:{
					if(i == 3) {
						i++;
					}
					break;
				}
			}
		}else if((checkImport(import, input) && i != 2)) {
			input +=import;
			cout<<import;
			clearDisplay(input.size(), 40);
			notify(flag, "                            ", 0);
			notify(flag, "                            ", 1);
		}else if (import == BACKSPACE && !input.empty()) {   				 //Xoa
			input.erase(input.size() - 1, 1);
			cout << "\b";
			cout << " ";
			cout << "\b";
			notify(flag, "                              ", 1);						 				 //\b \b xoa chu
		}
		if (i == 5) {
			break;
		}
		if (import == ESC) {
			flag = true;
			while(true) {
				import = _getch();
				if(import == ENTER && checkUpdate != false) {
					flag = true;
					notify(flag, "Da co su thay doi cua tu", 1);
				}else{
					notify(flag, "                        ", 1);
				}
				if(import == ENTER && checkUpdate == false) {
					gotoxy(xBox + 2 + input.size(), yBox + 2);
					cout<<"                                        ";
					break;
				}else if(import == ESC && (import != ENTER || import != -32 || import != 0)) {
					notify(flag, "  							  ", 0);
					break;	
				}													//check dk 
			}
		}
	}
	return now;
}
int position(Word F, Word p) {
	int pos;
    Word q;
	q = F;
	pos = 0;
	while(q != NULL && q != p)
	{
		q = q->right;
		pos++;
	}
   if(q == NULL)
      return(-1);
	return(pos);
}
void selectionSortWord(listWord k[], Word now) {
	int key = hashKey(now->info.tu);
	Word q = k[key].tail;
	if(q != NULL) {
		Word c, qmin;
		aWord min;
		for(q; q->left != NULL; q = q->left) {
			min = q->info;                     				//selection sort
			qmin = q;
			for(c = q->left ; c != NULL; c = c->left) {
				if(c->info.tu.compare(min.tu) > 0) {
					min = c->info;
					qmin = c;
				}
			}
			qmin->info = q->info;
			q->info = min;	
		}
	}
}
void insertWord(listWord k[], Word p) {  					//con cach khac hay hon
	p = NULL;
	p = addW(k, p);
	if(p != NULL) {										//kt nAdd co ton tai khong
		int key = hashKey(p->info.tu);
		p->left = NULL;
		p->right = NULL;
		addWord(k[key], p);
		Word q = k[key].tail;
		if(q != NULL) {
			selectionSortWord(k, q);					//ss
		}
	}
	checkUpdate = true;
}
	
//============================mainSearch============================//
void mainSearch(listWord k[]) {
	setBGColor(LIGHT_AQUA);
	bool check = false;
	char import;													//import key
	string input = "";										
	Word dpHead = NULL;										
	Word headSearch = NULL;											//dau
	Word tailSearch = NULL;											//cuoi
	Word nowSearch = NULL;											//hien tai
	while(true){		
		mainDraw();
		if(!checkInput) {											//check false
			if(input.empty()) {
				flag = false;
				notify(flag, "Nhan Up/Down de tim tu       ", 0);						
				dpHead = displayHead(k);							//hien thi dau
				headSearch = nowSearch = dpHead;
				tailSearch = searchEnd(k, input, headSearch);
			}else {										
				headSearch = searchInput(k,input);
				if(headSearch == NULL) {
					flag = true;
					notify(flag, notF, 0);
				}else {
					flag = false;
					notify(flag, anE, 0);
				}
				nowSearch = headSearch;
				tailSearch = searchEnd(k, input, headSearch);
			}
		}
		showListWord(k, headSearch, tailSearch, nowSearch);
		gotoxy(xBox + 2 + input.size(), yBox + 2);
		if(input.empty()) {
			cout<<"Anh-viet:";
			gotoxy(xBox + 2, yBox + 2);
		}else {
			gotoxy(xBox + 2, yBox + 2);
			cout<<input;
			clearDisplay(input.size(), 40);
			gotoxy(xBox + 2 + input.size(), yBox + 2);
		}
		Nocursortype(true);
		import = _getch();
		Nocursortype(false);
		if(import == 0 || import == -32) {
			check = true;
			if(check) {
				flag = false;
				notify(flag, anE, 0);
			}
			import = _getch();
			switch(import) {
				case KEY_UP: {
					keyUpSearch(headSearch, tailSearch, nowSearch, k, input);	
					checkInput = true;
					break;
				}
				case KEY_DOWN: {										//es
					keyDownSearch(headSearch , tailSearch, nowSearch, k, input);
					checkInput = true;
					break;
				}
				case KEY_HOME: {
					flag = false;
					notify(flag, "Nhan Up/Down de tim tu         ", 0);
					dpHead = displayHead(k);
					nowSearch = headSearch = dpHead;
					tailSearch = searchEnd(k,input,headSearch);
					input = "";			
					break;
				}
				case KEY_INSERT: {
					Word p = NULL;								//Nhap
					insertWord(k, p);
					input = "";
					dpHead = displayHead(k);						//hien thi dau
					headSearch = nowSearch = dpHead;
					tailSearch = searchEnd(k, input, headSearch);									//chen vao Word
					break;
				}
				case KEY_F4: {
					if(nowSearch != NULL)
					editWord(k, nowSearch);
					selectionSortWord(k, nowSearch);
					break;
				}
				case DELE: {
					if (nowSearch) {
						flag = true;
						notify(flag, "An Enter de xac nhan xoa       ", 0);
						import = _getch();
						notify(flag, "						         ", 0);
						if(import == ENTER) {
							deleteWord(k, nowSearch);
							checkUpdate = true;
							nowSearch = headSearch = displayHead(k);
							tailSearch = searchEnd(k, input, headSearch);
						}else break;
					}
					break;
				}
			}  
		}else if (checkImport(import, input)) {
			input += import;
			chuanHoaTu(input);
			clearDisplay(input.size(), 30);
			checkInput = false;
		}else if (import == BACKSPACE && !input.empty()) {   		//Xoa
			input.erase(input.size() - 1, 1);
			cout << "\b";
			cout << " ";
			cout << "\b";
			checkInput = false;								 		// \b \b Backspace
		}else if (import == ENTER && nowSearch) {
				Nocursortype(true);
				showNowWord(nowSearch);
				Nocursortype(false);
				while(true) {
					char kt= _getch();
					if(kt == ESC) {
						system("cls");
						break;
					}
					if(kt == KEY_F4) {
						editWord(k, nowSearch);
						break;
					}	
				}
			checkInput = false;
			input = "";
		}else if (import == ESC) {
			flag = true;
			notify(flag, ex, 0);
			while(true) {
				char kt = _getch();
				if(kt == ENTER) {
					system("cls");
					break;
				}else if(kt != ENTER && kt != 0 && kt != -32) {
					checkInput = false;
					break;
				}
			}
			break;	
		}
	}
}
int main() {
	resizeConsole(CSWIDTH, CSHEIGHT);
	setConsoleTitle("PHAM MINH QUANG - N18DCCN159 - DICTIONARY");
	listWord k[MAXKEY]; 
	ifstream fin;
	ofstream fout;
	//introduce();
	system("cls");
	addHashTable(k,fin);
	mainSearch(k);
	if(checkUpdate) {
		fout.open("dictionary1.txt", ios::out);
		writeFile(k, fout);
		fout.close();
	}
	cout<<endl;
	system("pause");
	return 1;
}
