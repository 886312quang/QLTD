#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include "mylib.h"
#include "constants.h"

using namespace std;

bool checkUpdate = false;
bool checkE = false;
bool flag = false;
bool flagAE = false;
bool checkDelete = false;

const string loai[] = {"Danh tu", "Tinh tu", "Dong tu", "Trang tu"};
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

struct listWord {										//list //Bang bam
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
string justifyStr(string style, int width) {		//can giua tu dh
	if (style.empty()) {
		return style;
	}else if (style.length() > width) {
		return style;
	}
	return string((width - style.length()) / 2, ' ') + style;
}
void ToMauHCN(int toadoX, int toadoY, int chieudai, int chieucao, int mauText) {
	setBGColor(255);
	for (int i = toadoY + 1; i < toadoY + chieucao; i++) {
		for (int j = toadoX + 1; j < chieudai + toadoX; j++) {
			gotoxy(j, i);
			cout << " ";
		}
	}
	setColor(BLACK);
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
	ifstream fin("1.bin", ios::in);
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
	const char  a = 201, 
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
	cout << "   CTRL + N";
	setColor(WHITE);
	cout << " :Them tu  ";
	
	setColor(LIGHT_GREEN);
	cout << "F4";
	setColor(WHITE);
	cout << " :Chi sua  ";
	
	setColor(LIGHT_GREEN);
	cout << "Up / Down";
	setColor(WHITE);
	cout << " :Tim kiem tu  ";

	setColor(LIGHT_GREEN);
	cout << "Home";
	setColor(WHITE);
	cout << " :Ve dau DS tu dien  ";
	
	setColor(LIGHT_RED);
	cout << "Delete";
	setColor(WHITE);
	cout << " :Xoa tu  ";
	
	setColor(LIGHT_RED);
	cout << "Esc";
	setColor(WHITE);
	cout << " :Thoat chuong trinh  ";
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
	cout << " :Chinh sua   ";
	
	setColor(LIGHT_GREEN);
	cout << "Right / Left";
	setColor(WHITE);
	cout << " :Chon loai tu   ";

	setColor(LIGHT_GREEN);
	cout << "Up / Down";
	setColor(WHITE);
	cout << " :Di chuyen giua cac khung  ";
	
	setColor(LIGHT_RED);
	cout << "Esc";
	setColor(WHITE);
	cout << " :Thoat chuong trinh";
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
	Nocursortype(false);
	gotoxy(xNotify + 23, yNotify - 3 + height);
	cout<<"                                 ";
	gotoxy(xNotify + 23, yNotify - 3 + height);
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
int hashKey(string key){		
	return (int)key[0] - 97; 					  	 //dinh khoa
}
void insertMean(Mean& First, string x) {			 //them mean LKD
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
	Last->next = me;								//last->next = null
}
void readExample(Word& p, ifstream& fin) {								
	for(int i = 0; i < 5; i++) {  					//TachVidu VD MCT
		string temp = "";
		getline(fin, temp, '.');
		if(!temp.empty()) {
			p->info.vd[i] = new string;
			*(p->info.vd[i]) = temp; 
		}else {
			p->info.vd[i] = NULL;
		}
	}
}
Word openFile(ifstream& fin) { 						// doc 1 thang	//note
	Word p = new nodeWord;
	p->left = NULL;
	p->right = NULL;
	Mean First = NULL;
	getline(fin, p->info.tu, '.'); 					//Tach tu
	if(p->info.tu.size() == 0) {
		delete(p);
		return NULL;
	}
	getline(fin, p->info.loai, '.');				//Tach loai tu
	string temp = "";
	while(true){
		getline(fin, temp, '.');					//Tach nghia~ LKD
		if(temp == "#") 		
			break;									//xong
		else{
			insertMean(First, temp);				
		}
	}
	p->info.tv = First;
	readExample(p, fin);
	fin.ignore(1); 									//Xoa \n
	return p;
}
void addWord(listWord& k, Word newW) {						
	if (k.head == NULL) {
		k.head = k.tail = newW; 						
	}else {
		k.head->left = newW;
		newW->right = k.head;
		k.head = newW;
	}
}
void addA(listWord& k, Word q) {
	if (k.head == NULL) {
		k.head = k.tail = q; 						
	}else if (q->info.tu < k.head->info.tu) {
		k.head->left = q;
		q->right = k.head;	
		k.head = q;
	}
	else {
		for (Word r = k.head; r != NULL; r = r->right) {
			if (q->info.tu < r->info.tu) {
				Word p = r->left;
				r->left = q;	q->right = r;
				p->right = q;	q->left = p;
				break;
			}
			if (r->right == NULL) {
				r->right = q;	q->left = r;
				k.tail = q;
				break;
			}
		}
	}
}
void quickSort(Word head);
void addHashTable(listWord k[],ifstream& fin) {	//Chen bang bam
	fin.open("dictionary.bin", ios::in);	
	if(!fin.good()) {								//Check file
		flag = true;
		notify(flag, "Mo file that bai", 0);
		return;
	}
	while (!fin.eof()) {							//doc file
		Word p = openFile(fin);
		if (!p) break;
		int index = hashKey(p->info.tu);			//xac dinh key add Table
		addA(k[index], p);						//add word vao table		
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
	Word p = k[hashKey(input)].head;
	for(p; p != NULL; p = p->right) {
		if(comparev(input, p)) {
			return p;							
		}
	}
	return NULL;
}
Word searchHead(listWord k[], Word input) {			//Tim ve dau 
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
	if (input != NULL) {
		Word tail = input->right;					
		if (tail != NULL) {
			return tail;
		}else {
			int index = hashKey(input->info.tu);	//tra ve dau
			while (index < MAXKEY - 1) {
				++index;
				if(k[index].head != NULL) {	
					return k[index].head;
				}        
			}
		}
	}
	return NULL;
}
Word searchEnd(listWord k[], string input, Word start) {	//Chan cuoi cat thang cuoi
	Word p = start;											//node can tim
	Word temp = NULL;										//start
	int i = 0;										
	for(i; i < sizeDp  && p; i++) {
		temp = searchTail(k, p);				
		if(temp && comparev(input, temp)) {					//tim kiem theo tu dien khong phai loc
			p = temp;										//2 cach
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
			fout << temp->info.tu << ".";
			fout << temp->info.loai << ".";
			Mean tempM = temp->info.tv;
			while(tempM != NULL) {
				fout << tempM->mean << ".";
				tempM = tempM->next;
			}
			fout << "#.";
			int j = 0;
			for(int i = 0; i < 5; i++) {
				if(temp->info.vd[i] != NULL) {
					fout<<*(temp->info.vd[i])<<".";
				}else{
					fout<<".";
				}
			}
			fout<<"\n";
		}
	}
}
void checkUPD(listWord k[],ofstream &fout) {
	if(checkUpdate) {
		fout.open("dictionary.bin", ios::out);
		writeFile(k, fout);
		fout.close();
	}
}
Word displayHead(listWord k[]) {			//hien thi thang dau tien neu k co input
	Word dpHead = NULL;	
	int i = 0;		
	for(i; i < 26; i++) {
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
	Word temp = searchTail(k, tail);
	Word check = head;
	for (check; check != temp; check = searchTail(k,check)) {
		gotoxy(xBox + 1, yBox + 5 + i);
		if(check == now) {
			hightLight();								  	   //tu hien tai hightlight
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
		gotoxy(xBox + 1, j);								//dh
		cout<<"                                                 ";   //clearDisplay
	}
}
bool checkImport(char import, string input) {
	if(((import >= 'a' && import <= 'z') ||
		(import >= 'A' && import <= 'Z'  ||
		(import == '-') && input.size() > 0)) 
		&& input.size() < 40 && import != DELE && import != ENTER)
		return true;
	return false;
}
bool checkImportS(char import, string input) {
	if((import == '.'  || 
	    import == '?'  || 
	    import == '"'  || 
	    import == '/'  ||
	    import == '|'  ||
	    import == '-'  ||
	    import == '!'
		) && input.size() > 0 && input.size() < 40)
	return true;
	return false;
}
//==========================nodeMeanPointrer===========================//
Mean nodePointer(int index, Word a) {					//tra ve (p) o vt index
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
void editMean(Word& a, int start, int& pos, Mean& First);
void showShowMean(Word now, int& pos, Mean &First) {
	int i = pos - 3;
	int t = 0;
	int k = 0;
	int eW = countMean(now);
	gotoxy(xBox + 26, yBox + 11);
	setBGColor(LIGHT_YELLOW);
	setColor(BLACK);
	cout<<"^";
	normalBGColor();
	char import;
	showM(i, pos, now);
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
		notify(flag, "Loi", 0);
	}else {
		flag = false;
		notify(flag, "An F4 de chinh sua tu", 0);
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
		notify(flag, "Tu nay khong co vi du", 0);
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
		notify(flag,"DOWN", 0);		
	}
}
void keyDownSearch(Word& headSearch, Word& tailSearch, Word& nowSearch, listWord k[], string input) {   
	Word temp = searchTail(k, nowSearch);
	if (temp != NULL && comparev(input, temp)) {				//chan
		if(nowSearch == tailSearch) {
			headSearch = searchTail(k, headSearch);				//DOWN => +1
			tailSearch = searchTail(k, tailSearch);				//DOWN => +1
		}
		nowSearch = searchTail(k, nowSearch);
	}else {
		flag = true;
		notify(flag,"Up", 0);		
	}
}
//============================CheckExist================================//
Word midd(Word bd, Word kt) {
	if(bd == NULL) return NULL;
	Word b = bd;
	Word chay = bd->right;
	while(chay != kt) {
		chay = chay->right;
		if(chay != kt) {
			b = b->right;
			chay = chay->right;
		}
	}
	return b;
}
bool checkWordExist(listWord k[], string input) {
	int index = hashKey(input);
	Word f = k[index].head;
	if(f == NULL) return false;
	Word start = f;
	Word tail = NULL;
	do {
		Word mid = midd(start, tail);
		if (mid == NULL) return false;
		if(mid->info.tu == input) {
			return true;
		}else if(mid->info.tu < input) {
			start = mid->right;
		}else if(mid->info.tu > input) {
			tail = mid;
		}
	}while(tail == NULL || tail != start);
	return false;
}
bool checkMeanExist(Mean First, string mean) {
	Mean p = First;
	for (p;  p != NULL ; p = p->next) 
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
void dhAddWord(int i, string& input, char import, int chon, int& pos, int &d, int& j, Word now, bool& checkDelete, bool& flagAE) {
	int k = 0;
	if (checkDelete == true || flagAE) {
		bool check = false;
		pos = 0;
		j = 0;
		if(pos < 4 || checkDelete) {
			int t = 0;
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
		if(d > 4) {
			gotoxy(xBox + 26, yBox + 17);
			setBGColor(LIGHT_YELLOW);
			setColor(BLACK);
			cout<<"v";
			normalBGColor();
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
			notify(flag, "An Right/Left de chon loai tu", 0);
		}else {
			flag = false;
			notify(flag, "An Enter de chon loai tu", 0);
		}
		gotoxy(xBox + 14, yBox + 7);
	}
	if(i == 3) 	{
		flag = false;
		notify(flag, "Them nghia cua tu", 0);
		gotoxy(xBox + 3, yBox + 12);
		cout<<"Nghia:";
		gotoxy(xBox + 9 + input.size(), yBox + 12);	
	}
	if(i == 4) {
		flag = false;
		notify(flag, "Them vi du/F2 de luu", 0);
		if(j == 5) {
			notify(flag, "Da co du vi du", 1);
		}else {
			notify(flag, "				", 1);
		}
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
		}else {
			flag = true;
			notify(flag, "Can it nhat 1 nghia", 1);
		}
	}else {
		if(del == NULL)  return;
		notify(flag, "Nhan Enter de xoa nghia", 0);
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
			Word nowR = now->right;				//es
			nowR->left = nowL;
			nowL->right = nowR;
		}
		k[index].head = head;					//Cap nhat lai bang bam
		k[index].tail = tail;
		deleteContent(now);						//Xoa toan bo tu
	}
}
//=========================VitriDH=======================//
void indexEdit(int index, int pos ,int x, string temp) {		//dh
	gotoxy(xBox + wBoxMain - 1, yBox + pos + index + 1);
	cout<< " ";
	gotoxy(xBox + wBoxMain - 1, yBox + pos + index - 1);
	cout<< " ";
	gotoxy(xBox + wBoxMain - 1, yBox + pos + index);
	setBGColor(LIGHT_AQUA);
	cout<< " ";
	normalBGColor();
	gotoxy(xBox + x + temp.size(), yBox + pos + index);
}
//============================EditMean==================================//
void editMean(Word& a, int start, int& pos, Mean& First) {
	int i = start;
	int index = 0;
	int vtShow = 0;
	int vtDelete = 0;
	int d = 1;
	Mean p = NULL;
	Mean del = NULL;
	string temp = "";
	if(pos > 4)	{
		gotoxy(xBox + 26, yBox + 11);
		cout<<" ";
		showM(0, pos, a);
		gotoxy(xBox + 26, yBox + 17);
		setBGColor(LIGHT_YELLOW);
		setColor(BLACK);
		cout<<"v";
		normalBGColor();
	}
	p = nodePointer(index, a);
	temp = p->mean;
	indexEdit(index, 13, 9, temp); 
	char import;
	while(true) {
		Nocursortype(true);
		import = _getch();
		Nocursortype(false);
		if (import == 0 || import == -32) {
			import = _getch();
			if (import == KEY_UP) {
				index--;
				if(index == -1 && pos > 4 && vtShow > 0) {
					gotoxy(xBox + 26, yBox + 11);			//dh
					cout<<" ";
					gotoxy(xBox + 26, yBox + 17);
					setBGColor(LIGHT_YELLOW);
					setColor(BLACK);
					cout<<"v";
					normalBGColor();
					vtShow--;
					index++;
				}else if(index == -1) index++;
			}
			if (import == KEY_DOWN) {
				if(index < pos - 1) {
					index++;
				}else if(pos > 4) index++;
				if(index == 4 && pos > 4 && vtShow < pos - 4) {
					vtShow++;
					index--;
					gotoxy(xBox + 26, yBox + 17);
					setBGColor(LIGHT_YELLOW);
					setColor(BLACK);
					cout<<"v";
					normalBGColor();
				}
				if(index == 4) {
					index--;
				}
				if(vtShow == pos - 4) {					//dh
					gotoxy(xBox + 26, yBox + 17);
					cout<<" ";
				}
			}
			if((vtShow <= pos - 4) && pos > 4) {	//>4
				showM(vtShow, pos, a);
				if(vtShow >= 1) {					//dh
					gotoxy(xBox + 26, yBox + 11);
					setBGColor(LIGHT_YELLOW);
					setColor(BLACK);
					cout<<"^";
					normalBGColor();
				}
				p = nodePointer(index + vtShow, a);
				temp = p->mean;
				vtDelete = index + vtShow;
				indexEdit(index, 13, 9, temp);
			}else if(vtShow < 1) {					//<4mean						
				p = nodePointer(index, a);
				temp = p->mean;
				vtDelete = index;
				indexEdit(index, 13, 9, temp);
			}
			if(import == DELE){
				notify(flag, "Nhan Enter de xoa", 1);
				import = _getch();
				if(import == ENTER) {	
					deleteMean(a, p, vtDelete, pos, First);			//xoa	
					gotoxy(xBox + wBoxMain - 1, yBox + 12 + index); //dh
					cout<< " ";
					gotoxy(xBox + 26, yBox + 11);
					cout<<" ";
					notify(flag, "                            ", 1);
					flag = true;
					return;
				}
			}	
		}else if ((checkImport(import, temp))
				 && import != ENTER && import != DELE){
			temp += import;
			cout<<import;
		}else if(import == SPACE) {
			temp += " ";
			cout<<import;
		}else if (import == BACKSPACE && !temp.empty()) {   		//Xoa
			temp.erase(temp.size() - 1, 1);
			cout << "\b \b";								 		// \b\b Backspace
		}else if (import == ENTER && temp.size() > 0) {
			chuanHoaVD(temp);
			if(checkMeanExistEdit(a, temp)) {
				flag = true;										//Notify
				notify(flag, "Da ton tai nghia nay", 1);
				gotoxy(xBox + 9, yBox + 13 + index);
				cout<<temp;
			}else {
				p->mean = temp;
				gotoxy(xBox + 9, yBox + 13 + index);
				cout<<temp;
				temp = "";
				gotoxy(xBox + wBoxMain - 1, yBox + 13 + index);
				cout<< " ";
				notify(flag, "    					      ", 1);
				return;
			}
		}else if(import == ESC) {
			gotoxy(xBox + wBoxMain - 1, yBox + 13 + index);
			normalBGColor();
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
				notify(flag, "An Enter de xoa vi du", 0);
				import = _getch();
				if (import == ENTER) {
					deleteExample(a->info.vd, i , n);
					gotoxy(xBox + wBoxMain - 1, yBox + 19 + pos + i);
					cout<< " ";
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
				gotoxy(xBox + wBoxMain - 1, yBox + 19 + pos + i);
				cout<< " ";
				break;
			}else {
				flag = true;
				notify(flag, "Da ton tai vi du nay", 1);
			}
		}else if(import == ESC) {
			gotoxy(xBox + wBoxMain - 1, yBox + 19 + pos + i);
			cout<< " ";
			gotoxy(xBox + 4, yBox + 19 + pos + i);
			string temp = *a->info.vd[i];
			cout<<temp;
			clearDisplay(temp.size(), wBoxMain - 5);
			break;
		} 
	}
}
//============================XulyInsertWord============================//
void xuLyNhapTu(listWord k[], char import, string& input, Word& now, int& i) {
	if (import == ENTER && !input.empty()) {
		chuanHoaTu(input);
		if (!checkWordExist(k, input)) {
			setColor(LIGHT_GREEN);
			gotoxy(xBox + 2, yBox + 2);
			now->info.tu = input;
			cout<<justifyStr(input, wBoxMain - 4);
			input = "";			
			i++;
			setColor(WHITE);
		}else {
			flag = true;
			notify(flag, "Da ton tai tu dang them", 0);	
		}
	}
}
void xuLyNhapVD(Word& now, int &j, string& input, char import, int pos) {
	if(import == ENTER && j < 5 && !input.empty()) {
		chuanHoaVD(input);
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
			notify(flag, "Da ton tai vi du nay", 1);
		}
	}else if(import == SPACE && input.size() > 0 && input.size() < 40) {
		input += " ";
	}
}
Word addW(listWord k[], Word now) {
	system("cls");
	insertDraw();                                                // Ve khung insert
	string input = "";
	int i = 1;
	int chon = 0;
	int j = 0;
	int pos = 0;
	int d = 0;
	if(now == NULL) now = new nodeWord;
	Mean First = NULL;
	now->info.tv = First;
	for (int i = 0; i < 5; i++) {
		now->info.vd[i] = NULL;
	}
	flagAE = false;
	char import;
	while(true) {
		dhAddWord(i, input, import, chon , pos, d, j, now, checkDelete, flagAE);
		Nocursortype(true);
		import = _getch();
		Nocursortype(false);
		switch(i) {
			case 1: {
				xuLyNhapTu(k, import, input, now, i);
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
						insertMean(First, input);	
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
							showShowMean(now, d, First);
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
				xuLyNhapVD(now, j, input, import, pos);
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
				case KEY_F3: {
					if (i == 3 && now->info.tv != NULL) {
						if(pos < 4) {
							int start = 0;
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
			}
		}else if((checkImport(import, input) && i != 2) || (checkImportS(import, input) && i == 4)) {
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
		}else if(import == CTRLS) {
			flag = true;
			if(i == 1 && now->info.tu.empty()) notify(flag, "Ban chua nhap tu", 1);
			if(i == 3 && now->info.tv == NULL) notify(flag, "Tu can co it nhat 1 nghia", 1);
			if(!now->info.tu.empty() && !now->info.loai.empty() && now->info.tv != NULL){
				gotoxy(15,1);
				i = 5;
				if(flagAE) {
					successAdd("Thay doi thanh cong");
				}else{
					successAdd("Them tu thanh cong");
				}
				checkUpdate = true;
				notify(flag,"                            ",1);
			}	
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
//=============================Edit====================================//
void editWord(listWord k[], Word& now, bool falgAE) {
	system("cls");
	insertDraw();                                                // Ve khung insert
	string input = "";
	int i = 2;
	int chon = 0;
	int j = 0;
	int pos = 0;
	int d = 0;
	Mean First;
	if(flagAE) {
		gotoxy(xBox + 2, yBox + 2);
		clearDisplay(0, wBoxMain - 3);
		gotoxy(xBox + 2, yBox + 2);
		string temp = now->info.tu;
		cout<<justifyStr(temp, wBoxMain - 4);
		d = countMean(now);
		First = now->info.tv;
	}
	char import;
	while(true) {
		dhAddWord(i, input, import, chon , pos, d, j, now, checkDelete, flagAE);
		Nocursortype(true);
		import = _getch();
		Nocursortype(false);
		switch(i) {
			case 1: {
				xuLyNhapTu(k, import, input, now, i);
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
							showShowMean(now, d, First);
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
						notify(flag, "Da ton tai nghia nay", 1);	
					}
				}
				if(import == SPACE && input.size() > 0 && input.size() < 24) {
					input += " ";
				}
				break;
			}
			case 4: {		
				xuLyNhapVD(now, j ,input ,import, pos);
				break;
			}
		}
		if(import == 0 || import == -32) {
			import = _getch();
			switch(import) {
				case KEY_UP: {
					if(i > 2) i--;
					break;
				}
				case KEY_DOWN: {
					if(i == 1 && !now->info.tu.empty()) {
						i++;
					}else if(i == 2 && !now->info.loai.empty()) {
						i++;
					}else if(i == 3 && pos != 0) {
						i++;
					}
					input = "";
					break;
				}
				case KEY_F3: {
					if (i == 3 && now->info.tv != NULL) {
						if(pos < 4) {
							int start = 0;
							editMean(now, start, pos, First);
						}else{
							int start = d - 4;
							editMean(now, start, d, First);
						}
					}
					if (i == 4 && now->info.vd[0] != NULL) 
						editExample(j, now, pos);
					break;
				}
			}
		}else if(((checkImport(import, input) && i != 2) || 
				  checkImportS(import, input) && i == 4)) {
			if(j == 5 && i == 4) {
			}else {
				input +=import;
				cout<<import;
				clearDisplay(input.size(), 40);
			}
			notify(flag, "                            ", 0);
			notify(flag, "                            ", 1);
		}else if (import == BACKSPACE && !input.empty()) {   				 //Xoa
			input.erase(input.size() - 1, 1);
			cout << "\b";
			cout << " ";
			cout << "\b";
			notify(flag, "                              ", 1);						 				 //\b \b xoa chu
		}else if(import == CTRLS) {
			flag = true;
			if(i == 1 && now->info.tu.empty()) notify(flag, "Ban chua nhap tu", 1);
			if(i == 3 && now->info.tv == NULL) notify(flag, "Tu can co it nhat 1 nghia", 1);
			if(!now->info.tu.empty() && !now->info.loai.empty() && now->info.tv != NULL){
				gotoxy(15,1);
				i = 5;
				if(flagAE) {
					successAdd("Thay doi thanh cong");
				}else{
					successAdd("Them tu thanh cong");
				}
				checkUpdate = true;
				notify(flag,"                            ",1);
			}	
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
			notify(flag, "Ban muon thoat khoi che do them", 0);
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
					notify(flag, "  							   ", 0);
					break;	
				}													//check dk 
			}
		}
	}
}
void swap(aWord *a, aWord *b) {
	aWord temp = *a;
	*a = *b;
	*b = temp;
}
Word lastWord(Word root) {
	while(root && root->right)
		root = root->right;
	return root;
}
Word mid(Word bd, Word kt) {
	if (bd == NULL) return NULL;
	Word b = bd;
	Word chay = bd->right;
	while (chay != kt) {
		chay = chay->right;
		if (chay != kt) {
			b = b->right;
			chay = chay->right;
		}
	}
	return b;
}
Word partition(Word l, Word h) {
	string temp = h->info.tu;
	Word i = l->left;			//pt left - 1 bo qua thang pivot giam sat qua trinh
	for(Word j = l; j != h; j = j->right) { //right - 1 
		if(j->info.tu < temp) {
			i = (i == NULL) ? l : i->right;	
			swap(&(i->info), &(j->info));
		}
	}
	//vi tri chinh xac
	i = (i == NULL) ? l : i->right;
	swap(&(i->info), &(h->info));
	return i;
}
void _quickSort(Word l, Word h) {
	if(h != NULL && l != h && l != h->right) { //l<h
		Word temp = partition(l, h);
		_quickSort(l, temp->left);
		_quickSort(temp->right, h);
	}
}
void quickSort(Word head) {
	Word tail = lastWord(head);
	_quickSort(head, tail);
}
void insertWord(listWord k[], Word p) {
	p = NULL;
	p = addW(k , p);
	if(p != NULL) {										//kt nAdd co ton tai khong
		int key = hashKey(p->info.tu);
		p->left = NULL;
		p->right = NULL;
		addA(k[key], p);
	}
	checkUpdate = true;
}
	
//============================mainSearch============================//
void mainSearch(listWord k[]) {
	setBGColor(LIGHT_AQUA);
	char import;													//import key
	string input = "";										
	Word dpHead = NULL;										
	Word headSearch = NULL;											//dau
	Word tailSearch = NULL;											//cuoi
	Word nowSearch = NULL;											//hien tai
	bool checkInput = false;
	mainDraw();	
	while(true){	
		if(!checkInput) {											//check false
			if(input.empty()) {
				flag = false;
				notify(flag, "Nhan Up/Down de tim tu", 0);						
				dpHead = displayHead(k);							//hien thi dau
				headSearch = nowSearch = dpHead;
				tailSearch = searchEnd(k, input, headSearch);		
			}else {					
				headSearch = searchInput(k ,input);
				if(headSearch == NULL) {
					flag = true;
					notify(flag, "Khong co tu can tim kiem", 0);
				}else {
					flag = false;
					notify(flag, "An Enter de chon tu", 0);
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
			flag = false;
			notify(flag, "An Enter de chon tu", 0);
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
					notify(flag, "Nhan Up/Down de tim tu", 0);
					dpHead = displayHead(k);
					nowSearch = headSearch = dpHead;
					tailSearch = searchEnd(k,input,headSearch);
					input = "";			
					break;
				}
				case KEY_F4: {
					if(nowSearch != NULL) {
						string temp = nowSearch->info.tu;
						flagAE = true;
						editWord(k, nowSearch, flagAE);
						if(nowSearch->info.tu != temp) {
							int index = hashKey(nowSearch->info.tu);
							Word t = k[index].head;
							quickSort(t);
						}	
						mainDraw();
					}
					break;
				}
				case DELE: {
					if (nowSearch) {
						flag = true;
						notify(flag, "An Enter de xac nhan xoa", 0);
						import = _getch();
						notify(flag, "						    ", 0);
						if(import == ENTER) {
							deleteWord(k, nowSearch);
							checkUpdate = true;
							checkInput = false;
						}else break;
					}
					break;
				}
			}  
		}else if (checkImport(import, input) && input.size() < 24) {
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
				showNowWord(nowSearch);
				while(true) {
					char kt= _getch();
					if(kt == ESC) {
						system("cls");
						break;
					}
					if(kt == KEY_F4) {
						flagAE = true;
						editWord(k, nowSearch, flagAE);
						break;
					}	
				}
			mainDraw();
		}else if (import == CTRLN) {
			Word p = NULL;									//Nhap
			insertWord(k, p);
			input = "";
			dpHead = displayHead(k);						//hien thi dau
			headSearch = nowSearch = dpHead;
			tailSearch = searchEnd(k, input, headSearch);	//chen vao Word
			mainDraw();
		}else if (import == ESC) {
			flag = true;
			notify(flag, "Ban co muon thoat k (Enter)", 0);
			while(true) {
				char kt = _getch();
				if(kt == ENTER) {
					system("cls");
					return;
				}else if(kt != ENTER && kt != 0 && kt != -32) {
					checkInput = false;
					break;
				}
			}
		}
	}
}
void freeMemory(listWord k[]) {
	for (int i = 0; i < MAXKEY; i++) {
		if (k[i].head != NULL) {
			Word delWord = NULL;
			Mean delMean = NULL;
			while (k[i].head != NULL) {
				delWord = k[i].head;
				Mean First = delWord->info.tv;
				deleteFMean(delWord, First);
				for (int j = 0; j < MAXVD; j++)
					delete k[i].head->info.vd[j];
				k[i].head = k[i].head->right;
				delete delWord;
			}
		}
	}
}
int main() {
	resizeConsole(CSWIDTH, CSHEIGHT);
	setConsoleTitle("PHAM MINH QUANG - N18DCCN159 - DICTIONARY");
	listWord *k = new listWord[MAXKEY];
	ifstream fin;
	ofstream fout;
	//introduce();
	system("cls");
	addHashTable(k, fin);
	/*for(int i = 0; i < MAXKEY; i++) {
		Word temp = k[i].head;
		quickSort(temp);
	}*/
	mainSearch(k);
	checkUPD(k, fout);
	freeMemory(k);
	cout<<endl;
	system("pause");
	return 1;
}
