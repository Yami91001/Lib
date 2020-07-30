#include"Function.h"

//Utility functions for projects and Function 1

int maxDay(int y, int m)
{
	if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
		return 31;
	else if (m == 4 || m == 6 || m == 9 || m == 11)
		return 30;
	else if (m == 2)
	{
		if (isLeapY(y) == true)
			return 29;
		else
			return 28;
	}
	else return 0;
}

bool execLib(char* argv[])
{
	if (_stricmp(argv[1], "open") == 0)
	{
		cout << "-----Phan mem quan ly thu vien-----" << endl;
		return true;
	}
	cout << "Vui long mo lai command prompt va nhap vao 'Open' hoac 'open' de vao app" << endl;
	return false;
}

bool isLeapY(int n)
{
	if (n % 4 == 0 && n % 400 == 0)
		return true;
	else if (n % 4 == 0 && n % 100 != 0)
		return true;
	return false;
}

void inputDate(Date& date)
{
	cout << "Nhap vao theo thu tu nam,thang,ngay:" << endl;
	system("pause");
	cout << "Nhap vao nam:";
	cin >> date.year;
	do
	{
		cout << "Nhap vao thang:";
		cin >> date.month;
	} while (date.month > 12 || date.month < 1);
	int maxday = maxDay(date.year, date.month);
	do
	{
		cout << "Nhap vao ngay:";
		cin >> date.day;
	} while (date.day<0 || date.day>maxday);

}

void newLogin(User& user)
{
	cout << "Nhap vao username:";
	cin.get(user.username, 50);
	cin.ignore();
	char temp[50];
	do
	{
		cout << "Nhap vao password:";
		pass(user.password);
		cout << "Nhap lai password:";
		pass(temp);
	} while (strcmp(user.password, temp) != 0);
}

bool checkAvailability(User user, const char* filename)
{
	User temp;
	FILE* f1 = fopen(filename, "rb");
	if (f1 == NULL)
	{
		cout << 1;
		return 0;
	}

	fseek(f1, 0, SEEK_END);
	int n = ftell(f1) / sizeof(User);
	rewind(f1);
	for (int i = 0; i < n; i++)
	{
		fread(&temp, sizeof(User), 1, f1);
		if (strcmp(temp.username, user.username) == 0)
		{
			fclose(f1);
			return false;
		}
	}
	fclose(f1);
	return true;
}

void generalInfo(User& user)
{
	cout << "Nhap vao ho va ten:";
	cin.get(user.name, 50);
	cin.ignore();
	cout << "Nhap vao ngay sinh:" << endl;
	inputDate(user.birthday);
	cin.ignore();
	cout << "Nhap vao CMND:";
	cin.get(user.ID, 10);
	cin.ignore();
	cout << "Nhap vao dia chi:";
	cin.get(user.address, 50);
	cin.ignore();
	cout << "Nhap vao gioi tinh (Nam/Nu):";
	cin.get(user.gender, 7);
	cin.ignore();
	do
	{
		cout << "Nhap vao tinh trang (1:Activated,0:Blocked):";
		cin >> user.status;
	} while (user.status != 1 && user.status != 0);
	do
	{
		cout << "Nhap vao chuc vu (1:Manager,0:Executive):";
		cin >> user.type;
	} while (user.type != 1 && user.type != 0);
}

void generalInfoUpdated(User& user)
{
	cout << "Nhap vao ho va ten:";
	cin.get(user.name, 50);
	cin.ignore();
	cout << "Nhap vao ngay sinh:" << endl;
	inputDate(user.birthday);
	cin.ignore();
	cout << "Nhap vao CMND:";
	cin.get(user.ID, 10);
	cin.ignore();
	cout << "Nhap vao dia chi:";
	cin.get(user.address, 50);
	cin.ignore();
	cout << "Nhap vao gioi tinh (Nam/Nu):";
	cin.get(user.gender, 7);
	cin.ignore();
}

void pass(char mk[])
{
	char x;
	int size = 0;
	x = _getch();
	while (x != 13)
	{
		if (x == 8 && size > 0)
		{
			mk[size] = '\0';
			size--;
			cout << "\b \b";
		}
		else if (x == 8 && size == 0)
		{
			x = _getch();
			continue;
		}
		else
		{
			cout << x;
			cout << "\b \b*";
			mk[size] = x;
			size++;
		}
		x = _getch();

	}
	mk[size] = '\0';
	cout << endl;
}


//Function 1

//Function 1.1 Login
bool login(User& user, const char* filename, bool& isAdmin,
	bool& isManager, bool& isExecutive, char curUser[], char curPass[])
{
	cout << "Username:";
	cin.get(curUser, 50);
	cin.ignore();
	cout << "Password:";
	pass(curPass);
	if (strcmp("admin", curUser) == 0 && strcmp("admin", curPass) == 0)
	{
		isAdmin = true;
		return true;
	}
	FILE* f1 = fopen(filename, "rb");
	if (f1 == NULL)
		return false;
	fseek(f1, 0, SEEK_END);
	int n = ftell(f1) / sizeof(User);
	// Tim ra so luong nguoi dung can phai doc 
	rewind(f1);
	for (int i = 0; i < n; i++)
	{
		fread(&user, sizeof(User), 1, f1);
		if (strcmp(curUser, user.username) == 0 && strcmp(curPass, user.password) == 0)
		{
			location = ftell(f1) - sizeof(User);
			if (user.type == 1)
				isManager = true;
			else
				isExecutive = true;
			fclose(f1);
			return true;
		}
	}
	fclose(f1);
	return false;
}

//Function 1.2 Logout không cần hàm vì chỉ cần thoát ra lại màn hình menu chính

//Function 1.3 change password
void changePassword(User& user, const char* filename)
{
	User temp;
	FILE* f1 = fopen(filename, "rb+");
	if (f1 == NULL)
		return;
	int k = 0;
	char curPas[50];
	char newPas[50];
	bool correct = false;
	do
	{
		cout << "Nhap vao mat khau hien tai:";
		pass(curPas);
		fseek(f1, location, SEEK_SET);
		fread(&user, sizeof(User), 1, f1);
		if (strcmp(curPas, user.password) == 0)
		{
			temp = user;
			correct = true;
			break;
		}
	} while (correct == false);
	cout << "Nhap mat khau moi:";
	pass(newPas);
	strcpy(temp.password, newPas);
	fseek(f1, location, SEEK_SET);
	fwrite(&temp, sizeof(User), 1, f1);
	fclose(f1);
}

//Function 1.4 update info & show info

void updateInfo(User& user, const char* filename, char curUser[], char curPass[])
{
	int k = 0;
	FILE* f1 = fopen(filename, "rb+");
	if (f1 == NULL)
		return;
	fseek(f1, location, SEEK_SET);
	generalInfoUpdated(user);
	fwrite(&user, sizeof(User), 1, f1);
	fclose(f1);
}

void showInfo(User user, const char* filename, char curUser[], char Pass[])
{
	cout << "Ho va ten:" << user.name << endl;
	cout << "Ngay sinh:" << user.birthday.day << "/" << user.birthday.month
		<< "/" << user.birthday.year << endl;
	cout << "CMND:" << user.ID << endl;
	cout << "Dia chi:" << user.address << endl;
	cout << "Gioi tinh:" << user.gender << endl;
	cout << "Tinh trang:";
	if (user.status == 0)
		cout << "Blocked" << endl;
	else
		cout << "Activated" << endl;
	cout << "Chuc vu:";
	if (user.type == 0)
		cout << "Executive" << endl;
	else
		cout << "Manager" << endl;
}

//Function 1.5 add users

void addUser(User& user, const char* filename)
{
	FILE* f1 = fopen(filename, "rb+");
	if (f1 == NULL)
	{
		FILE* f1 = fopen(filename, "wb");
		fclose(f1);
		addUser(user, filename);
		return;
	}
	//Mở file ở dạng wb để tạo file nếu chưa có thì gọi lại 
	//hàm addUser mở ở dạng rb+ để đọc ghi
	fseek(f1, 0, SEEK_END);
	newLogin(user);
	if (checkAvailability(user, filename) == false)
	{
		cout << "Tai khoan da ton tai";
		return;
	}
	generalInfo(user);
	fseek(f1, 0, SEEK_END);
	fwrite(&user, sizeof(User), 1, f1);
	fclose(f1);
	cout << "Nguoi dung duoc tao thanh cong" << endl;
}

//Function 1.6 define type of user

void showList(User user, const char* filename)
{
	FILE* f1 = fopen(filename, "rb");
	if (f1 == NULL)
		return;
	fseek(f1, 0, SEEK_END);
	int n = ftell(f1) / sizeof(User);
	rewind(f1);
	for (int i = 0; i < n; i++)
	{
		fread(&user, sizeof(User), 1, f1);
		cout << "User no." << i + 1 << ":" << endl;
		cout << "Username:" << user.username << endl;
		cout << "Chuc vu hien tai cua nguoi dung:";
		if (user.type == 1)
			cout << "Manager" << endl;
		else
			cout << "Executive" << endl;
		cout << "-------------------------------------------" << endl;
	}
	fclose(f1);
}

void typeUser(User& user, const char* filename, int index)
{
	index--;
	FILE* f1 = fopen(filename, "rb+");
	if (f1 == NULL)
		return;
	int k = 0;
	fseek(f1, 0, SEEK_END);
	int n = ftell(f1) / sizeof(User);
	rewind(f1);
	for (int i = 0; i < n; i++)
	{
		fread(&user, sizeof(User), 1, f1);
		if (i == index)
		{
			cout << "Cap nhat chuc nang cua nguoi dung:" << endl;
			cout << "Nhap vao 1:Manager" << endl;
			cout << "Nhap vao 0:Executive" << endl;
			cin >> user.type;
			k = ftell(f1);
			break;
		}
	}
	rewind(f1);
	fseek(f1, k - sizeof(User), SEEK_SET);
	fwrite(&user, sizeof(User), 1, f1);
	fclose(f1);
}

//Utility functions for Function 2

bool checkReader(Reader reader, const char* filename)
{
	Reader temp;
	FILE* f1 = fopen(filename, "rb");
	if (f1 == NULL)
	{
		return 0;
	}
	fseek(f1, 0, SEEK_END);
	int n = ftell(f1) / sizeof(Reader);
	rewind(f1);
	for (int i = 0; i < n; i++)
	{
		fread(&temp, sizeof(Reader), 1, f1);
		if (strcmp(temp.readerID, reader.readerID) == 0)
		{
			fclose(f1);
			return false;
		}
	}
	fclose(f1);
	return true;
}

void newReader(Reader& reader)
{
	cout << "Nhap vao ma doc gia:";
	cin.get(reader.readerID, 10);
	cin.ignore();
}

void readerInfo(Reader& reader)
{
	cout << "Nhap vao ho va ten:";
	cin.get(reader.name, 50);
	cin.ignore();
	cout << "Nhap vao CMND:";
	cin.get(reader.ID, 10);
	cin.ignore();
	cout << "Nhap vao ngay sinh:" << endl;
	inputDate(reader.birthday);
	cout << "Nhap vao gioi tinh:";
	cin.ignore();
	cin.get(reader.gender, 7);
	cin.ignore();
	cout << "Nhap vao email:";
	cin.get(reader.email, 50);
	cin.ignore();
	cout << "Nhap vao dia chi:";
	cin.get(reader.address, 50);
	cin.ignore();
	cout << "Nhap vao ngay lap the" << endl;
	inputDate(reader.cardCreate);
	cin.ignore();
	cout << "Ngay the het han:" << endl;
	reader.cardExpire = reader.cardCreate;
	reader.cardExpire.year = reader.cardCreate.year + 4;
	cout << reader.cardExpire.day << "/" << reader.cardExpire.month
		<< "/" << reader.cardExpire.year << endl;
}

void CopyFile(const char* filename1, const char* filename2)
{
	FILE* f1 = fopen(filename1, "rb");
	if (f1 == NULL)
		return;
	FILE* f2 = fopen(filename2, "wb");
	if (f2 == NULL)
		return;
	char buf[BUF_SIZE];
	int count;
	do
	{
		count = fread(buf, 1, BUF_SIZE, f1);
		fwrite(buf, 1, count, f2);
	} while (count == BUF_SIZE);
}
//Hàm copy file từ file temp.bin sang reader.bin để xóa phần tử cuối

void moveRBottom(Reader& reader, const char* filename, int index)
{
	int k = 0;
	index--;
	Reader temp;
	FILE* f1 = fopen(filename, "rb+");
	if (f1 == NULL)
		return;
	fseek(f1, 0, SEEK_END);
	int n = ftell(f1) / sizeof(Reader);
	rewind(f1);
	for (int i = 0; i < n; i++)
	{
		fread(&reader, sizeof(Reader), 1, f1);
		if (i == index)
		{
			temp = reader;
			k = ftell(f1);
			for (int j = i; j < n - 1; j++)
			{
				fread(&reader, sizeof(Reader), 1, f1);
				rewind(f1);
				fseek(f1, k - sizeof(Reader), SEEK_SET);
				fwrite(&reader, sizeof(Reader), 1, f1);
				k = ftell(f1) + sizeof(Reader);
				rewind(f1);
				fseek(f1, k, SEEK_SET);
			}
			fseek(f1, k - sizeof(Reader), SEEK_SET);
			fwrite(&temp, sizeof(Reader), 1, f1);
			break;
		}
	}
	fclose(f1);
}
//Hàm chuyển phần tử cần xóa xuống cuối để có thể dễ dàng xóa 

void generalReaderInfo(Reader& reader)
{
	cout << "Ma doc gia:" << reader.readerID << endl;
	cout << "Ho va ten:" << reader.name << endl;
	cout << "CMND:" << reader.ID << endl;
	cout << "Ngay sinh:" << reader.birthday.day << "/" << reader.birthday.month
		<< "/" << reader.birthday.year << endl;
	cout << "Gioi tinh:" << reader.gender << endl;
	cout << "Email:" << reader.email << endl;
	cout << "Dia chi:" << reader.address << endl;
	cout << "Ngay mo the:" << reader.cardCreate.day << "/" << reader.cardCreate.month
		<< "/" << reader.cardCreate.year << endl;
	cout << "Ngay het han:" << reader.cardExpire.day << "/" << reader.cardExpire.month
		<< "/" << reader.cardExpire.year << endl;
	cout << "-------------------------------------------" << endl;
}

//Function 2

//Function 2.1 list of readers

void listReader(Reader& reader, const char* filename)
{
	FILE* f1 = fopen(filename, "rb");
	if (f1 == NULL)
		return;
	fseek(f1, 0, SEEK_END);
	int n = ftell(f1) / sizeof(Reader);
	rewind(f1);
	for (int i = 0; i < n; i++)
	{
		cout << "Reader no." << i + 1 << endl;
		fread(&reader, sizeof(Reader), 1, f1);
		generalReaderInfo(reader);
	}
	fclose(f1);
}

//Function 2.2 add reader

void addReader(Reader& reader, const char* filename)
{
	FILE* f1 = fopen(filename, "rb+");
	if (f1 == NULL)
	{
		FILE* f1 = fopen(filename, "wb");
		fclose(f1);
		addReader(reader, filename);
		return;
	}
	fseek(f1, 0, SEEK_END);
	newReader(reader);
	if (checkReader(reader, filename) == false)
	{
		cout << "Ma so doc gia da bi lay vui long nhap ma so moi" << endl;
		return;
	}
	readerInfo(reader);
	fseek(f1, 0, SEEK_END);
	fwrite(&reader, sizeof(Reader), 1, f1);
	fclose(f1);
}

//Function 2.3 update reader info

void updateReaderInfo(Reader& reader, const char* filename, int index)
{
	int k = 0;
	index--;
	FILE* f1 = fopen(filename, "rb+");
	if (f1 == NULL)
		return;
	fseek(f1, 0, SEEK_END);
	int n = ftell(f1) / sizeof(Reader);
	rewind(f1);
	for (int i = 0; i < n; i++)
	{
		fread(&reader, sizeof(Reader), 1, f1);
		if (i == index)
		{
			cout << "Cap nhat thong tin cua doc gia:" << endl;
			readerInfo(reader);
			k = ftell(f1);
			break;
		}
	}
	rewind(f1);
	fseek(f1, k - sizeof(Reader), SEEK_SET);
	fwrite(&reader, sizeof(Reader), 1, f1);
	fclose(f1);
}

//Function 2.4 delete reader info

void deleteReader(Reader& reader, const char* filename1, const char* filename2, int index)
{
	moveRBottom(reader, filename1, index);
	int k = 0;
	FILE* f1 = fopen(filename1, "rb+");
	if (f1 == NULL)
		return;
	FILE* f2 = fopen(filename2, "wb");
	if (f2 == NULL)
		return;
	fseek(f1, 0, SEEK_END);
	int n = ftell(f1) / sizeof(Reader);
	rewind(f1);
	for (int i = 0; i < n - 1; i++)
	{
		fread(&reader, sizeof(Reader), 1, f1);
		fwrite(&reader, sizeof(Reader), 1, f2);
	}
	fclose(f1);
	fclose(f2);
	CopyFile(filename2, filename1);
	fclose(f1);
	fclose(f2);
}
//Hàm delete hoạt động bằng cách sử dụng hàm moveRBottom và tiến hành viết
// n-1 phần tử từ reader.bin vào temp.bin rồi copy từ temp qua lại reader để xóa độc giả 

//Function 2.5 find id

void findReaderID(Reader& reader, const char* filename, char curID[])
{
	int count = 0;
	FILE* f1 = fopen(filename, "rb");
	if (f1 == NULL)
		return;
	fseek(f1, 0, SEEK_END);
	int n = ftell(f1) / sizeof(Reader);
	rewind(f1);
	for (int i = 0; i < n; i++)
	{
		fread(&reader, sizeof(Reader), 1, f1);
		if (strcmp(curID, reader.ID) == 0)
		{
			cout << "Thong tin cua doc gia can tim:" << endl;
			generalReaderInfo(reader);
			count++;
		}
	}
	if (count == 0)
	{
		cout << "Khong co doc gia voi ID can tim" << endl;
	}
	fclose(f1);
}

//Function 2.6 find name

void findReaderName(Reader& reader, const char* filename, char curName[])
{
	int count = 0;
	FILE* f1 = fopen(filename, "rb");
	if (f1 == NULL)
		return;
	fseek(f1, 0, SEEK_END);
	int n = ftell(f1) / sizeof(Reader);
	rewind(f1);
	for (int i = 0; i < n; i++)
	{
		fread(&reader, sizeof(Reader), 1, f1);
		if (_stricmp(curName, reader.name) == 0)
		{
			cout << "Thong tin doc gia voi ten can tim:" << endl;
			generalReaderInfo(reader);
			count++;
		}
	}
	if (count == 0)
	{
		cout << "Khong co doc gia voi ten can tim" << endl;
	}
	fclose(f1);
}

//Utility function for function 3

void newBook(Book& book)
{
	cout << "Nhap vao ma ISBN cua sach: ";
	cin.get(book.ISBN, 20);
	cin.ignore();
}

bool checkBook(Book& book, const char* filename)
{
	Book temp;
	FILE* f1 = fopen(filename, "rb");
	if (f1 == NULL)
	{
		return 0;
	}
	fseek(f1, 0, SEEK_END);
	int n = ftell(f1) / sizeof(Book);
	rewind(f1);
	for (int i = 0; i < n; i++)
	{
		fread(&temp, sizeof(Book), 1, f1);
		if (strcmp(temp.ISBN, book.ISBN) == 0)
		{
			fclose(f1);
			return false;
		}
	}
	fclose(f1);
	return true;
}

void bookInfo(Book& book)
{
	cout << "Nhap vao ten sach: ";
	cin.get(book.bName, 50);
	cin.ignore();
	cout << "Nhap vao ten tac gia: ";
	cin.get(book.author, 50);
	cin.ignore();
	cout << "Nhap vao nha xuat ban: ";
	cin.get(book.publisher, 50);
	cin.ignore();
	cout << "Nhap vao nam xuat ban: ";
	cin >> book.publishY;
	cin.ignore();
	cout << "Nhap vao the loai: ";
	cin.get(book.genre, 20);
	cout << "Nhap gia sach: ";
	cin >> book.price;
	cin.ignore();
	cout << "Nhap vao so luong quyen sach: ";
	cin >> book.quantity;
	book.borrowed = 0;
}

//Function 3

//Function 3.1 list book
void showBookInfo(Book book)
{
	cout << "ISBN: " << book.ISBN << endl;
	cout << "Ten: " << book.bName << endl;
	cout << "Tac gia: " << book.author << endl;
	cout << "Nha xuat ban: " << book.publisher << endl;
	cout << "Nam xuat ban: " << book.publishY << endl;
	cout << "The loai: " << book.genre << endl;
	cout << "Gia sach: " << book.price << endl;
	cout << "So luong: " << book.quantity << endl;
	cout << "-------------------------------------------" << endl;
}

void showBookList(const char* filename)
{
	Book book;
	int a = 1;
	FILE* f = fopen(filename, "rb");
	if (f == NULL)
	{
		cout << "Khong mo duoc file" << endl;
		return;
	}

	fseek(f, 0, SEEK_END);
	int n = ftell(f);
	rewind(f);
	for (int i = 0; i < n / sizeof(Book); i++)
	{
		fread(&book, sizeof(Book), 1, f);
		cout << "Quyen sach thu " << a << ": " << endl;
		showBookInfo(book);
		a++;
	}

	fclose(f);
}

//Function 3.2 add book

void addBook(Book& book, const char* filename)
{
	FILE* f1 = fopen(filename, "rb+");
	if (f1 == NULL)
	{
		FILE* f1 = fopen(filename, "wb");
		fclose(f1);
		addBook(book, filename);
		return;
	}
	fseek(f1, 0, SEEK_END);
	newBook(book);
	if (checkBook(book, filename) == false)
	{
		cout << "Sach can them vao da ton tai" << endl;
		fclose(f1);
		return;
	}
	bookInfo(book);
	fwrite(&book, sizeof(book), 1, f1);
	fclose(f1);
}

//Function 3.3 change book information

int findBook(const char* filename, const char* ISBN, const char* bName, int order)
{
	int seek = -1;
	Book book;
	FILE* f = fopen(filename, "rb");


	if (f == NULL)
	{
		cout << "Khong mo duoc file" << endl;
		return -1;//Khong mo duoc file
	}

	fseek(f, 0, SEEK_END);
	int n = ftell(f) / sizeof(Book);
	rewind(f);

	for (int i = 0; i < n; i++)
	{
		fread(&book, sizeof(Book), 1, f);
		seek++;
		if (seek == order - 1 || strcmp(book.ISBN, ISBN) == 0 || strcmp(book.bName, bName) == 0)
		{
			fclose(f);
			return seek;
		}
	}
	fclose(f);
	return -1;

}//Ham nay se tra ve vi tri quyen sach trong thu vien, tra ve -1 neu khong co sach
//Thu tu uu tien: ISBN > bName > order

void findAndShowBookInfo(const char* filename, const char* ISBN, const char* bName, int order)
{
	Book book;
	int pos1 = findBook(filename, ISBN, "", 0);
	int pos2 = findBook(filename, "", bName, 0);
	int pos3 = findBook(filename, "", "", order);
	//Kiem tra truong hop trung
	if (pos1 == pos2 == pos3 == -1)
	{
		cout << "Khong co sach can tim" << endl;
		return;
	}

	FILE* f = fopen(filename, "rb");
	if (f == NULL)
		return;



	int a[] = { pos1,pos2,pos3 };
	for (int i = 0; i < 2; i++)
	{
		for (int j = i + 1; j < 3; j++)
		{
			if (a[j] == a[i])
			{
				a[j] = -1;
			}
		}
	}
	for (int i = 0; i < 3; i++)
	{
		if (a[i] != -1)
		{
			fseek(f, a[i] * sizeof(Book), SEEK_SET);
			fread(&book, sizeof(Book), 1, f);

			cout << "Quyen sach thu " << a[i] + 1 << endl;
			showBookInfo(book);
			cout << endl;

			rewind(f);
		}
	}
	fclose(f);
}//Vét cạn tất cả kết quả có thể có

void changeBookInfo(const char* filename, const char* ISBN, const char* bName, int order)
{
	int pos = findBook(filename, ISBN, bName, order);
	if (pos == NULL)
	{
		cout << "Khong mo duoc file" << endl;
		return;
	}
	if (pos == -1)
	{
		cout << "Khong co sach can tim" << endl;
		return;
	}

	FILE* f = fopen(filename, "rb+");
	if (f == NULL)
	{
		cout << "Khong mo duoc file" << endl;
		return;
	}

	Book book;
	fseek(f, pos * sizeof(Book), SEEK_SET);
	newBook(book);
	bookInfo(book);

	/*if (checkBook(book, filename) == false)
	{
		cout << "Sach da ton tai" << endl;
		fclose(f);
		return;//Sach da ton tai
	}
	*/

	fwrite(&book, sizeof(Book), 1, f);

	fclose(f);


}

//Function 3.4 delete book

void moveBBottom(Book& book, const char* filename, int index)
{
	int k = 0;
	index--;
	Book temp;
	FILE* f1 = fopen(filename, "rb+");
	if (f1 == NULL)
		return;
	fseek(f1, 0, SEEK_END);
	int n = ftell(f1) / sizeof(Book);
	rewind(f1);
	for (int i = 0; i < n; i++)
	{
		fread(&book, sizeof(Book), 1, f1);
		if (i == index)
		{
			temp = book;
			k = ftell(f1);
			for (int j = i; j < n - 1; j++)
			{
				fread(&book, sizeof(Book), 1, f1);
				rewind(f1);
				fseek(f1, k - sizeof(Book), SEEK_SET);
				fwrite(&book, sizeof(Book), 1, f1);
				k = ftell(f1) + sizeof(Book);
				rewind(f1);
				fseek(f1, k, SEEK_SET);
			}
			fseek(f1, k - sizeof(Book), SEEK_SET);
			fwrite(&temp, sizeof(Book), 1, f1);
			break;
		}
	}
	fclose(f1);
}

void deleteBook(Book& book, const char* filename1, int index)
{
	//filename1 = "temp.bin", filename2 = "book.bin"
	const char* filename2 = "temp.bin";
	moveBBottom(book, filename1, index);

	int k = 0;

	FILE* f1 = fopen(filename1, "rb+");
	if (f1 == NULL)
		return;
	FILE* f2 = fopen(filename2, "wb");
	if (f2 == NULL)
		return;
	fseek(f1, 0, SEEK_END);
	int n = ftell(f1) / sizeof(Book);
	rewind(f1);
	for (int i = 0; i < n - 1; i++)
	{
		fread(&book, sizeof(Book), 1, f1);
		fwrite(&book, sizeof(Book), 1, f2);
	}
	fclose(f1);
	fclose(f2);
	CopyFile(filename2, filename1);
	fclose(f1);
	fclose(f2);
}

void findBookISBN(const char* filename, char curID[])
{
	Book book;
	int count = 0;
	FILE* f1 = fopen(filename, "rb");
	if (f1 == NULL)
		return;
	fseek(f1, 0, SEEK_END);
	int n = ftell(f1) / sizeof(Book);
	rewind(f1);
	for (int i = 0; i < n; i++)
	{
		fread(&book, sizeof(Book), 1, f1);
		if (strcmp(curID, book.ISBN) == 0)
		{
			cout << "Thong tin cua sach can tim:" << endl;
			showBookInfo(book);
			count++;
		}
	}
	if (count == 0)
	{
		cout << "Khong co sach voi ISBN can tim" << endl;
	}
	fclose(f1);
}

void findBookName(const char* filename, char curName[])
{
	Book book;
	int count = 0;
	FILE* f1 = fopen(filename, "rb");
	if (f1 == NULL)
		return;
	fseek(f1, 0, SEEK_END);
	int n = ftell(f1) / sizeof(Book);
	rewind(f1);
	for (int i = 0; i < n; i++)
	{
		fread(&book, sizeof(Book), 1, f1);
		if (_stricmp(curName, book.bName) == 0)
		{
			cout << "Thong tin sach voi ten can tim:" << endl;
			showBookInfo(book);
			count++;
		}
	}
	if (count == 0)
	{
		cout << "Khong co sach voi ten can tim" << endl;
	}
	fclose(f1);
}

//Utility functions for function 4

Date returnDate(Date date)
{
	Date temp = date;
	int maxday = maxDay(date.year, date.month);
	if (temp.day + 7 > maxday)
	{
		temp.day = date.day + 7 - maxday;
		temp.month = temp.month + 1;
		if (temp.month > 12)
		{
			temp.month = 1;
			temp.year++;
		}
	}
	else
		temp.day = temp.day + 7;
	return temp;
}

bool validReader(Card card, const char* filename)
{
	Reader temp;
	FILE* f1 = fopen(filename, "rb");
	if (f1 == NULL)
		return false;
	fseek(f1, 0, SEEK_END);
	int n = ftell(f1) / sizeof(Reader);
	rewind(f1);
	for (int i = 0; i < n; i++)
	{
		fread(&temp, sizeof(Reader), 1, f1);
		if (strcmp(card.borrowID, temp.readerID) == 0)
		{
			fclose(f1);
			return true;
		}
	}
	fclose(f1);
	return false;
}

void updateQuantity(Book& book, const char* filename, int k)
{
	FILE* f1 = fopen(filename, "rb+");
	if (f1 == NULL)
		return;
	fseek(f1, k - sizeof(Book), SEEK_SET);
	fwrite(&book, sizeof(Book), 1, f1);
	fclose(f1);
}

bool validBooks(Card card, int index, const char* filename)
{
	Book temp;
	FILE* f1 = fopen(filename, "rb");
	if (f1 == NULL)
		return false;
	fseek(f1, 0, SEEK_END);
	int n = ftell(f1) / sizeof(Book);
	rewind(f1);
	for (int i = 0; i < n; i++)
	{
		fread(&temp, sizeof(Book), 1, f1);
		if (strcmp(temp.ISBN, card.ISBN[index]) == 0)
		{
			if (temp.quantity == 0)
				return false;
			int k = ftell(f1);
			temp.quantity--;
			temp.borrowed++;
			updateQuantity(temp, filename, k);
			return true;
		}
	}
	cout << "Ma ISBN khong ton tai:" << endl;
	return false;
}

int soSanhDate(Date date1, Date date2)
{
	int maxday = maxDay(date1.year, date1.month);
	int stack = 0;
	if (date1.month > date2.month)
	{
		return 0;
	}
	if (date1.year == date2.year)
	{
		if (date1.month == date2.month)
		{
			if (date1.day == date2.day)
				return 0;
			else
				return date2.day - date1.day;
		}
		else
		{
			for (int i = date1.month + 1; i < date2.month; i++)
			{
				stack = stack + maxDay(date1.year, i);
			}
			return maxday - date1.day + stack + date2.day;
		}
	}
	else
	{
		for (int i = date1.month; i < 13; i++)
		{
			stack = stack + maxDay(date1.year, i);
		}
		for (int i = 1; i < date2.month; i++)
		{
			stack = stack + maxDay(date2.year, i);
		}
		return maxday - date1.day + stack + date2.day;

	}

}


//Function 4 Borrow card

bool checkBorrowMore(Card card, char ID[], const char* filename3)
{
	FILE* f1 = fopen(filename3, "rb+");
	if (f1 == NULL)
		return false;
	fseek(f1, 0, SEEK_END);
	int n = ftell(f1) / sizeof(Card);
	rewind(f1);
	for (int i = 0; i < n; i++)
	{
		fread(&card, sizeof(Card), 1, f1);
		if (strcmp(card.borrowID, ID) == 0)
		{
			fclose(f1);
			return true;
		}
	}
	fclose(f1);
	return false;
}

void borrowMore(Card& card, char ID[], const char* filename1
	, const char* filename2, const char* filename3)
{
	FILE* f1 = fopen(filename3, "rb+");
	if (f1 == NULL)
		return;
	fseek(f1, 0, SEEK_END);
	int n = ftell(f1) / sizeof(Card);
	int k = 0;
	rewind(f1);
	for (int i = 0; i < n; i++)
	{
		fread(&card, sizeof(Card), 1, f1);
		if (strcmp(card.borrowID, ID) == 0)
		{
			if (card.number == 5)
			{
				cout << "Khong the muon them sach:" << endl;
				return;
			}
			else
			{
				int more = 5 - card.number;
				int add = 0;
				cout << "So sach duoc muon them :" << more << endl;
				do
				{
					cout << "Nhap vao so sach muon muon them:" << endl;
					cin >> add;
				} while (add > more);
				cin.ignore();
				for (int i = card.number; i < card.number + add; i++)
				{
					do
					{
						cout << "Nhap vao ma ISBN cua sach can muon:";
						cin >> card.ISBN[i];
						cin.ignore();
					} while (validBooks(card, i, filename2) == false);
				}
				card.number = card.number + add;

			}
			k = ftell(f1);
			break;
		}
	}
	fseek(f1, k - sizeof(Card), SEEK_SET);
	fwrite(&card, sizeof(Card), 1, f1);
	fclose(f1);
}

void showcard(Card& card)
{

	cout << "Ten doc gia:" << card.borrowID << endl;
	cout << "So sach muon:" << card.number << endl;
	for (int i = 0; i < card.number; i++)
	{
		cout << "Ma ISBN sach thu " << i + 1 << ":" << card.ISBN[i] << endl;
	}
	cout << "Ngay tra sach du kien la:" << endl;
	cout << card.expectReturn.day << "/" << card.expectReturn.month
		<< "/" << card.expectReturn.year << endl;
	cout << "-------------------------------------------" << endl;
}

void showCardList(Card& card, const char* filename)
{
	FILE* f1 = fopen(filename, "rb+");
	if (f1 == NULL)
	{
		cout << "Khong co the muon sach nao" << endl;
		return;
	}	
	fseek(f1, 0, SEEK_END);
	int n = ftell(f1) / sizeof(Card);
	rewind(f1);
	for (int i = 0; i < n; i++)
	{
		fread(&card, sizeof(Card), 1, f1);
		showcard(card);
		cout << endl;
	}
	fclose(f1);
}

void createBorrowCard(Card& card, const char* filename1,
	const char* filename2, const char* filename3)
{
	char ID[10];
	FILE* f1 = fopen(filename3, "rb+");
	if (f1 == NULL)
	{
		FILE* f1 = fopen(filename3, "wb");
		createBorrowCard(card, filename1, filename2, filename3);
		return;
	}
	cout << "Nhap vao ma doc gia:";
	cin.get(card.borrowID, 10);
	cin.ignore();
	strcpy(ID, card.borrowID);
	if (validReader(card, filename1) == true)
	{
		if (checkBorrowMore(card, ID, filename3) == true)
		{
			borrowMore(card, ID, filename1, filename2, filename3);
			return;
		}
		do
		{
			cout << "Nhap vao so luong sach can muon:";
			cin >> card.number;
		} while (card.number > 5);
		cin.ignore();
		showBookList(filename2);
		for (int i = 0; i < card.number; i++)
		{
			cout << "Nhap vao ma ISBN cua sach can muon:";
			cin >> card.ISBN[i];
			while (validBooks(card, i, filename2) == false)
			{
				cout << "Ma ISBN khong hop le hoac da het sach can muon:" << endl;
				cin >> card.ISBN[i];
				cin.ignore();
			};
		}
		cout << "Nhap vao ngay muon sach:" << endl;
		inputDate(card.borrowDate);
		cin.ignore();
		cout << "Ngay han tra sach la:" << endl;
		card.expectReturn = returnDate(card.borrowDate);
		cout << card.expectReturn.day << "/" << card.expectReturn.month
			<< "/" << card.expectReturn.year << endl;
	}
	else
	{
		cout << "Ma doc gia khong ton tai" << endl;
		return;
	}
	fseek(f1, 0, SEEK_END);
	fwrite(&card, sizeof(Card), 1, f1);
	fclose(f1);
}

//Utility functions for function 5

void moveCardBottom(Card& card, const char* filename, char ID[])
{
	int k = 0;
	Card temp;
	FILE* f1 = fopen(filename, "rb+");
	if (f1 == NULL)
		return;
	fseek(f1, 0, SEEK_END);
	int n = ftell(f1) / sizeof(Card);
	rewind(f1);
	for (int i = 0; i < n; i++)
	{
		fread(&card, sizeof(Card), 1, f1);
		if (strcmp(ID, card.borrowID) == 0)
		{
			temp = card;
			k = ftell(f1);
			for (int j = i; j < n - 1; j++)
			{
				fread(&card, sizeof(Card), 1, f1);
				rewind(f1);
				fseek(f1, k - sizeof(Card), SEEK_SET);
				fwrite(&card, sizeof(Card), 1, f1);
				k = ftell(f1) + sizeof(Card);
				rewind(f1);
				fseek(f1, k, SEEK_SET);
			}
			fseek(f1, k - sizeof(Card), SEEK_SET);
			fwrite(&card, sizeof(Card), 1, f1);
			break;
		}
	}
	fclose(f1);
}

void deleteCard(Card& card, const char* filename1, char ID[])
{
	const char* filename2 = "temp.bin";
	moveCardBottom(card, filename1, ID);

	int k = 0;

	FILE* f1 = fopen(filename1, "rb+");
	if (f1 == NULL)
		return;
	FILE* f2 = fopen(filename2, "wb");
	if (f2 == NULL)
		return;
	fseek(f1, 0, SEEK_END);
	int n = ftell(f1) / sizeof(Card);
	rewind(f1);
	for (int i = 0; i < n - 1; i++)
	{
		fread(&card, sizeof(Card), 1, f1);
		fwrite(&card, sizeof(Card), 1, f2);
	}
	fclose(f1);
	fclose(f2);
	CopyFile(filename2, filename1);
	fclose(f1);
	fclose(f2);
}

int money(Book book, const char* filename2, char ISBN[])
{
	FILE* f1 = fopen(filename2, "rb");
	if (f1 == NULL)
		return 0;
	fseek(f1, 0, SEEK_END);
	int n = ftell(f1) / sizeof(Book);
	rewind(f1);
	for (int i = 0; i < n; i++)
	{
		fread(&book, sizeof(Book), 1, f1);
		if (strcmp(book.ISBN, ISBN) == 0)
		{
			return book.price;
		}
	}
	return 0;
}

int isLost(Book& book, int n, const char* filename2)
{
	FILE* f1 = fopen(filename2, "rb");
	if (f1 == NULL)
		return 0;
	int kq = 0;
	char ISBN[10];
	if (n == 0)
		return 0;
	else
	{
		cout << "Nhap vao ISBN cua sach bi mat :" << endl;
		for (int i = 0; i < n; i++)
		{
			cout << "Nhap vao ISBN cua sach thu " << i + 1 << ":";
			cin >> ISBN;
			kq = kq + money(book, filename2, ISBN) * 2;
		}
	}
	return kq;
}

int isLate(int n)
{
	if (n <= 0)
		return 0;
	else
		return 5000 * n;
}

void backBooks(Book& book, Card& card, char ID[], const char* filename2,
	const char* filename3, int k)
{
	FILE* f1 = fopen(filename3, "rb");
	if (f1 == NULL)
		return;
	FILE* f2 = fopen(filename2, "rb+");
	if (f2 == NULL)
		return;
	int location;
	fseek(f1, k - sizeof(Card), SEEK_SET);
	fread(&card, sizeof(Card), 1, f1);
	fseek(f2, 0, SEEK_END);
	int n = ftell(f2) / sizeof(Book);
	rewind(f2);
	for (int i = 0; i < n; i++)
	{
		fread(&book, sizeof(Book), 1, f2);
		for (int j = 0; j < card.number; j++)
		{
			if (strcmp(card.ISBN[j], book.ISBN) == 0)
			{
				location = ftell(f2);
				book.quantity++;
				if (book.borrowed > 0)
				{
					book.borrowed--;
				}
				updateQuantity(book, filename2, location);
			}
		}
	}
	fclose(f1);
	fclose(f2);

}

//Function 5 Return card

void createReturnCard(Card& card, const char* filename1,
	const char* filename2, const char* filename3)
{
	Book book;
	char ISBN[10];
	char MSR[10];
	int k = 0, late = 0, lost = 0, i = 0, sum = 0;
	FILE* f1 = fopen(filename3, "rb+");
	if (f1 == NULL)
		return;
	fseek(f1, 0, SEEK_END);
	int n = ftell(f1) / sizeof(Card);
	rewind(f1);
	cout << "Nhap vao ma so doc gia:";
	cin.get(MSR, 10);
	cin.ignore();
	for (int i = 0; i < n; i++)
	{
		fread(&card, sizeof(Card), 1, f1);
		if (strcmp(card.borrowID, MSR) == 0)
		{
			k = ftell(f1);
			showcard(card);
			cout << "Co bao nhieu sach bi mat :";
			cin >> lost;
			sum = sum + isLost(book, lost, filename2);
			cout << "Ngay han tra sach la:" << endl;
			card.expectReturn = returnDate(card.borrowDate);
			cout << card.expectReturn.day << "/" << card.expectReturn.month
				<< "/" << card.expectReturn.year << endl;
			cout << "Nhap vao ngay tra thuc te:" << endl;
			inputDate(card.actualReturn);
			late = soSanhDate(card.expectReturn, card.actualReturn) * (card.number - lost);
			backBooks(book, card, MSR, filename2, filename3, k);
			sum = sum + isLate(late);
			cout << "So tien phai den bu cho thu vien la:" << sum;

		}
	}
	deleteCard(card, filename3, MSR);
	fclose(f1);
}

//Function statistical

void statisticOfBook(const char* filename)
{
	Book book;
	int res = 0;

	FILE* f = fopen(filename, "rb");
	if (f == NULL)
		return;

	fseek(f, 0, SEEK_END);
	int n = ftell(f) / sizeof(Book);
	rewind(f);

	for (int i = 0; i < n; i++)
	{
		fread(&book, sizeof(Book), 1, f);
		res += book.quantity;
	}

	cout << "Tong so sach trong thu vien: " << res << endl;
	fclose(f);
}

void statisticOfGenre(const char* filename)
{
	Book book;
	Book temp;

	FILE* f = fopen(filename, "rb");
	if (f == NULL)
		return;

	fseek(f, 0, SEEK_END);
	int n = ftell(f) / sizeof(Book);
	rewind(f);

	int* a = new int[n];
	for (int i = 0; i < n; i++)
	{
		a[i] = 0;
	}
	for (int i = 0; i < n; i++)
	{
		fread(&book, sizeof(Book), 1, f);
		if (a[i] == -1)
			continue;

		int count = 1;
		for (int j = i + 1; j < n; j++)
		{
			fread(&temp, sizeof(Book), 1, f);
			if (strcmp(book.genre, temp.genre) == 0)
			{
				a[j] = -1;
				count++;
			}
		}
		fseek(f, (i + 1) * sizeof(Book), SEEK_SET);
		cout << "The loai " << book.genre << ": " << count << endl;
	}


	delete[]a;

	fclose(f);
}

void statisticOfReader(const char* filename)
{
	FILE* f = fopen(filename, "rb");
	if (f == NULL)
		return;
	fseek(f, 0, SEEK_END);
	int n = ftell(f) / sizeof(Reader);
	cout << "So luong doc gia: " << n << endl;

	fclose(f);
}

void statisticOfReaderGender(const char* filename)
{
	int male = 0;
	int female = 0;
	Reader reader;

	FILE* f = fopen(filename, "rb");
	if (f == NULL)
		return;
	fseek(f, 0, SEEK_END);
	int n = ftell(f) / sizeof(Reader);
	rewind(f);

	for (int i = 0; i < n; i++)
	{
		fread(&reader, sizeof(Reader), 1, f);
		if (_stricmp(reader.gender, "nam") == 0)
		{
			male++;
		}
	}
	female = n - male;
	cout << "So doc gia nam: " << male << endl;
	cout << "So doc gia nu: " << female << endl;

	fclose(f);
}

void statisticOfBorrowedBook(const char* filename)
{
	Book book;

	FILE* f = fopen(filename, "rb");
	if (f == NULL)
		return;

	fseek(f, 0, SEEK_END);
	int n = ftell(f) / sizeof(Book);
	rewind(f);

	for (int i = 0; i < n; i++)
	{
		fread(&book, sizeof(Book), 1, f);
		cout << "So sach " << book.bName << " dang duoc muon: " << book.borrowed << endl;
	}

	fclose(f);
}

void statisticOfLate(const char* filename)
{
	Card card;
	Date date;
	int k = 0, count = 0;
	FILE* f1 = fopen(filename, "rb");
	if (f1 == NULL)
		return;

	fseek(f1, 0, SEEK_END);
	int n = ftell(f1) / sizeof(Card);
	rewind(f1);
	cout << "Nhap vao ngay hom nay:" << endl;
	inputDate(date);
	cout << "Danh sach doc gia tre sach:" << endl;
	for (int i = 0; i < n; i++)
	{
		fread(&card, sizeof(Card), 1, f1);
		k = soSanhDate(card.expectReturn, date);
		if (k > 0)
		{
			count++;
			cout << "Doc gia " << count << ":" << card.borrowID;
			cout << ": Tre " << k << " ngay" << endl;
		}
	}
	if (count == 0)
	{
		cout << "Khong co doc gia tre han" << endl;
	}
}

//clear screen

void clearScreen() {
	HANDLE hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD count;
	DWORD cellCount;
	COORD homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', cellCount, homeCoords, &count)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}