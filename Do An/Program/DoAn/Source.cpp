#include "Function.h"

void return0(Book& book, const char* filename)
{
	FILE* f = fopen(filename, "rb+");
	if (f == NULL)
		return;

	fseek(f, 0, SEEK_END);
	int n = ftell(f) / sizeof(Book);
	rewind(f);

	for (int i = 0; i < n; i++)
	{
		fread(&book, sizeof(Book), 1, f);
		int k = ftell(f);
		book.borrowed = 0;
		fseek(f, k - sizeof(Book), SEEK_SET);
		fwrite(&book, sizeof(Book), 1, f);
	}

	fclose(f);
}

void main(int argc, char* argv[])
{
	int index, func, y;
	bool isAdmin = false, isMng = false, isExec = false;
	User user;
	Reader reader;
	Book book;
	Card card;
	char curUser[50];
	char curPass[50];
	char curID[10];
	char curName[50];
	bool open = execLib(argv);
	if (open == false)
		return;
	else
	{
		if (login(user, "user.bin", isAdmin, isMng, isExec, curUser, curPass) == 0)
			cout << "Nhap sai tai khoan vui long dang nhap lai" << endl;
		else
		{
			cout << "Dang nhap thanh cong" << endl;
			system("pause");
			system("cls");
			if (isAdmin == 1)
			{
				do
				{
					cout << "---------- CHUONG TRINH QUAN LY THU VIEN ----------" << endl << endl;
					cout << "Nhap vao 1 de quan ly he thong" << endl << endl;
					cout << "Nhap vao 2 de quan ly doc gia" << endl << endl;
					cout << "Nhap vao 3 de quan ly sach" << endl << endl;
					cout << "Nhap vao 4 de tao the muon sach" << endl << endl;
					cout << "Nhap vao 5 de tao the tra sach" << endl << endl;
					cout << "Nhap vao 6 de thong ke" << endl << endl;
					cout << "Nhap vao 7 de thoat chuong trinh" << endl << endl;
					cin >> func;
					system("cls");
					switch (func)
					{
					case 1:
						do
						{
							cout << "---------- QUAN LY HE THONG ----------" << endl << endl;
							cout << "Nhap vao 1 de dang xuat" << endl << endl;
							cout << "Nhap vao 2 de thay doi mat khau" << endl << endl;
							cout << "Nhap vao 3 de cap nhat thong tin nguoi dung" << endl << endl;
							cout << "Nhap vao 4 de tao nguoi dung" << endl << endl;
							cout << "Nhap vao 5 de phan quyen nguoi dung" << endl << endl;
							cout << "Nhap vao 6 de thoat chuc nang 1" << endl << endl;
							cin >> y;
							cin.ignore();
							system("cls");
							switch (y)
							{
							case 1:
								return;
							case 2:
								changePassword(user, "user.bin");
								cout << "Mat khau duoc doi lai thanh cong" << endl;
								break;
							case 3:
								cout << "Admin khong co info de thay doi" << endl;
								break;
							case 4:
								addUser(user, "user.bin");
								break;
							case 5:
								showList(user, "user.bin");
								cout << "Nhap vao STT cua nguoi dung can cap lai quyen:";
								cin >> index;
								typeUser(user, "user.bin", index);
								break;
							case 6:
								break;
							default:
								cout << "Khong ton tai chuc nang" << endl;
								break;
							}
							system("pause");
							system("cls");
						} while (y != 6);
						break;
					case 2:
						do
						{
							cout << "---------- QUAN LY DOC GIA ----------" << endl << endl;
							cout << "Nhap vao 1 xem danh sach doc gia" << endl << endl;
							cout << "Nhap vao 2 de them doc gia" << endl << endl;
							cout << "Nhap vao 3 de chinh sua thong tin doc gia" << endl << endl;
							cout << "Nhap vao 4 de xoa mot doc gia" << endl << endl;
							cout << "Nhap vao 5 de tim doc gia theo CMND" << endl << endl;
							cout << "Nhap vao 6 de tim doc gia theo ten" << endl << endl;
							cout << "Nhap vao 7 de thoat chuc nang 2" << endl << endl;
							cin >> y;
							cin.ignore();
							system("cls");
							switch (y)
							{
							case 1:
								cout << "Danh sach doc gia:" << endl;
								listReader(reader, "reader.bin");
								break;
							case 2:
								addReader(reader, "reader.bin");
								cout << "Doc gia duoc them thanh cong" << endl;
								break;
							case 3:
								listReader(reader, "reader.bin");
								cout << "Nhap vap STT doc gia can thay doi thong tin:";
								cin >> index;
								cin.ignore();
								updateReaderInfo(reader, "reader.bin", index);
								cout << "Thong tin doc gia duoc thay doi thanh cong" << endl;
								break;
							case 4:
								listReader(reader, "reader.bin");
								cout << "Nhap vap STT doc gia can xoa";
								cin >> index;
								cin.ignore();
								deleteReader(reader, "reader.bin", "temp.bin", index);
								cout << "Xoa thanh cong doc gia" << endl;
								break;
							case 5:
								cout << "Nhap vao CMND can tim :";
								cin.get(curID, 10);
								cin.ignore();
								findReaderID(reader, "reader.bin", curID);
								break;
							case 6:
								cout << "Nhap vao ten can tim :";
								cin.get(curName, 50);
								cin.ignore();
								findReaderName(reader, "reader.bin", curName);
								break;
							case 7:
								break;
							default:
								cout << "Khong ton tai chuc nang" << endl;
								break;
							}
							system("pause");
							system("cls");
						} while (y != 7);
						break;
					case 3:
						do
						{
							cout << "---------- QUAN LY SACH ----------" << endl << endl;
							cout << "Nhap vao 1 de xem danh sach sach trong thu vien" << endl << endl;
							cout << "Nhap vao 2 de them sach" << endl << endl;
							cout << "Nhap vao 3 de chinh sua thong tin sach" << endl << endl;
							cout << "Nhap vao 4 de xoa thong tin sach" << endl << endl;
							cout << "Nhap vao 5 de tim sach theo ma ISBN" << endl << endl;
							cout << "Nhap vao 6 de tim sach theo ten" << endl << endl;
							cout << "Nhap vao 7 de thoat chuc nang 3" << endl << endl;
							cin >> y;
							cin.ignore();
							system("cls");
							switch (y)
							{
							case 1:
								cout << "Danh sach sach trong thu vien:" << endl;
								showBookList("book.bin");
								break;
							case 2:
								addBook(book, "book.bin");
								cout << "Sach duoc them thanh cong" << endl;
								break;
							case 3:
								showBookList("book.bin");
								cout << "Nhap vao STT cua sach can thay doi thong tin:";
								cin >> index;
								cin.ignore();
								changeBookInfo("book.bin", book.ISBN, book.bName, index);
								cout << "Thay doi thong tin sach thanh cong thanh cong sach" << endl;
								break;
							case 4:
								showBookList("book.bin");
								cout << "Nhap vao STT cua sach can xoa:";
								cin >> index;
								cin.ignore();
								deleteBook(book, "book.bin", index);
								cout << "Xoa thanh cong sach" << endl;
								break;
							case 5:
								cout << "Nhap vao ISBN cua sach can tim:";
								cin >> curID;
								cin.ignore();
								findBookISBN("book.bin", curID);
								break;
							case 6:
								cout << "Nhap vao ten cua sach can tim:";
								cin.get(curName, 51);
								cin.ignore();
								findBookName("book.bin",curName);
								break;
							case 7:break;
							default:
								cout << "Khong ton tai chuc nang" << endl;
								break;
							}
							system("pause");
							system("cls");
						} while (y != 7);
						break;
					case 4:
						system("cls");
						cout << "---------- QUAN LY THE MUON SACH ----------" << endl << endl;
						do
						{
							cout << "Nhap vao 1 de xem danh sach the muon sach" << endl << endl;
							cout << "Nhap vao 2 de tao the muon sach" << endl << endl;
							cout << "Nhap vao 3 de thoat chuc nang 4:" << endl << endl;
							cin >> y;
							cin.ignore();
							switch (y)
							{
							case 1:
								showCardList(card, "card.bin");
								break;
							case 2:
								createBorrowCard(card, "reader.bin", "book.bin", "card.bin");
								cout << "The muon sach duoc tao thanh cong" << endl;
								break;
							case 3:
								break;
							default:
								cout << "Khong ton tai chuc nang" << endl;
								break;
							}
							system("pause");
							system("cls");
						} while (y != 3);
						break;
					case 5:
						cin.ignore();
						cout << "---------- QUAN LY THE TRA SACH ----------" << endl << endl;
						createReturnCard(card, "reader.bin", "book.bin", "card.bin");
						system("pause");
						system("cls");
						break;
					case 6:
						cout << "---------- THONG KE CO BAN ----------" << endl << endl;
						do
						{
							cout << "Nhap vao 1 de thong ke so luong sach trong thu vien" << endl << endl;
							cout << "Nhap vao 2 de thong ke so luong sach theo the loai" << endl << endl;
							cout << "Nhap vao 3 de thong ke so luong doc gia" << endl << endl;
							cout << "Nhap vao 4 de thong ke so luong doc gia theo gioi tinh" << endl << endl;
							cout << "Nhap vao 5 de thong ke so sach dang duoc muon" << endl << endl;
							cout << "Nhap vao 6 de thong ke danh sach do gia tre hen" << endl << endl;
							cout << "Nhap vao 7 de thoat chuc nang 6" << endl << endl;
							cin >> y;
							cin.ignore();
							system("cls");
							switch (y)
							{
							case 1:
								statisticOfBook("book.bin");
								cout << endl;
								break;
							case 2:
								statisticOfGenre("book.bin");
								cout << endl;
								break;
							case 3:
								statisticOfReader("reader.bin");
								cout << endl;
								break;
							case 4:
								statisticOfReaderGender("reader.bin");
								cout << endl;
								break;
							case 5:
								statisticOfBorrowedBook("book.bin");
								cout << endl;
								break;
							case 6:
								statisticOfLate("card.bin");
								cout << endl;
								break;
							case 7:
								break;
							default:
								cout << "Khong ton tai chuc nang" << endl;
								break;
							}
							system("pause");
							system("cls");
						} while (y != 7);
						break;
					case 7:
						break;
					default:
						cout << "Khong ton tai chuc nang" << endl;
						break;
					}
					system("cls");
				} while (func != 7);
			}
			else if (isMng == 1)
			{
				do
				{
					cout << "---------- CHUONG TRINH QUAN LY THU VIEN ----------" << endl << endl;
					cout << "Nhap vao 1 de quan ly he thong" << endl << endl;
					cout << "Nhap vao 2 de quan ly doc gia" << endl << endl;
					cout << "Nhap vao 3 de quan ly sach" << endl << endl;
					cout << "Nhap vao 4 de tao the muon sach" << endl << endl;
					cout << "Nhap vao 5 de tao the tra sach" << endl << endl;
					cout << "Nhap vao 6 de thong ke" << endl << endl;
					cout << "Nhap vao 7 de thoat chuong trinh" << endl << endl;
					cin >> func;
					system("cls");
					switch (func)
					{
					case 1:
						do
						{
							cout << "---------- QUAN LY NGUOI DUNG ----------" << endl << endl;
							cout << "Nhap vao 1 de dang xuat" << endl << endl;
							cout << "Nhap vao 2 de thay doi mat khau" << endl << endl;
							cout << "Nhap vao 3 de cap nhat thong tin nguoi dung" << endl << endl;
							cout << "Nhap vao 4 de thoat chuc nang 1" << endl << endl;
							cin >> y;
							cin.ignore();
							system("cls");
							switch (y)
							{
							case 1:
								return;
							case 2:
								changePassword(user, "user.bin");
								cout << "Mat khau duoc doi lai thanh cong" << endl;
								break;
							case 3:
								cout << "Thong tin hien tai cua nguoi dung" << endl;
								showInfo(user, "user.bin", curUser, curPass);
								system("pause");
								system("cls");
								updateInfo(user, "user.bin", curUser, curPass);
								cout << "Thong tin duoc cap nhat thanh cong" << endl;
								break;
							case 4:
								break;
							default:
								cout << "Khong ton tai chuc nang" << endl;
								break;
							}
							system("pause");
							system("cls");
						} while (y != 4);
						break;
					case 2:
						do
						{
							cout << "---------- QUAN LY DOC GIA ----------" << endl << endl;
							cout << "Nhap vao 1 xem danh sach doc gia" << endl << endl;
							cout << "Nhap vao 2 de them doc gia" << endl << endl;
							cout << "Nhap vao 3 de chinh sua thong tin doc gia" << endl << endl;
							cout << "Nhap vao 4 de xoa mot doc gia" << endl << endl;
							cout << "Nhap vao 5 de tim doc gia theo CMND" << endl << endl;
							cout << "Nhap vao 6 de tim doc gia theo ten" << endl << endl;
							cout << "Nhap vao 7 de thoat chuc nang 2" << endl << endl;
							cin >> y;
							cin.ignore();
							system("cls");
							switch (y)
							{
							case 1:
								cout << "Danh sach doc gia:" << endl;
								listReader(reader, "reader.bin");
								break;
							case 2:
								addReader(reader, "reader.bin");
								cout << "Doc gia duoc them thanh cong" << endl;
								break;
							case 3:
								listReader(reader, "reader.bin");
								cout << "Nhap vap STT doc gia can thay doi thong tin:";
								cin >> index;
								cin.ignore();
								updateReaderInfo(reader, "reader.bin", index);
								cout << "Thong tin doc gia duoc thay doi thanh cong" << endl;
								break;
							case 4:
								listReader(reader, "reader.bin");
								cout << "Nhap vap STT doc gia can xoa";
								cin >> index;
								cin.ignore();
								deleteReader(reader, "reader.bin", "temp.bin", index);
								cout << "Xoa thanh cong doc gia" << endl;
								break;
							case 5:
								cout << "Nhap vao CMND can tim :";
								cin.get(curID, 10);
								cin.ignore();
								findReaderID(reader, "reader.bin", curID);
								break;
							case 6:
								cout << "Nhap vao ten can tim :";
								cin.get(curName, 50);
								cin.ignore();
								findReaderName(reader, "reader.bin", curName);
								break;
							case 7:
								break;
							default:
								cout << "Khong ton tai chuc nang" << endl;
								break;
							}
							system("pause");
							system("cls");
						} while (y != 7);
						break;
					case 3:
						do
						{
							cout << "---------- QUAN LY SACH ----------" << endl << endl;
							cout << "Nhap vao 1 de xem danh sach sach trong thu vien" << endl << endl;
							cout << "Nhap vao 2 de them sach" << endl << endl;
							cout << "Nhap vao 3 de chinh sua thong tin sach" << endl << endl;
							cout << "Nhap vao 4 de xoa thong tin sach" << endl << endl;
							cout << "Nhap vao 5 de tim sach theo ma ISBN" << endl << endl;
							cout << "Nhap vao 6 de tim sach theo ten" << endl << endl;
							cout << "Nhap vao 7 de thoat chuc nang 3" << endl << endl;
							cin >> y;
							cin.ignore();
							system("cls");
							switch (y)
							{
							case 1:
								cout << "Danh sach sach trong thu vien:" << endl;
								showBookList("book.bin");
								break;
							case 2:
								addBook(book, "book.bin");
								cout << "Sach duoc them thanh cong" << endl;
								break;
							case 3:
								showBookList("book.bin");
								cout << "Nhap vao STT cua sach can thay doi thong tin:";
								cin >> index;
								cin.ignore();
								changeBookInfo("book.bin", book.ISBN, book.bName, index);
								cout << "Thay doi thong tin sach thanh cong thanh cong sach" << endl;
								break;
							case 4:
								showBookList("book.bin");
								cout << "Nhap vao STT cua sach can xoa:";
								cin >> index;
								cin.ignore();
								deleteBook(book, "book.bin", index);
								cout << "Xoa thanh cong sach" << endl;
								break;
							case 5:
								cout << "Nhap vao ISBN cua sach can tim:";
								cin >> curID;
								cin.ignore();
								findAndShowBookInfo("book.bin", curID, curName, 0);
								break;
							case 6:
								cout << "Nhap vao ten cua sach can tim:";
								cin.get (curName,51);
								cin.ignore();
								findAndShowBookInfo("book.bin", curID, curName, 0);
								break;
							case 7: break;
							default:
								cout << "Khong ton tai chuc nang" << endl;
								break;
							}
							system("pause");
							system("cls");
						} while (y != 7);
						break;
					case 4:
						system("cls");
						cout << "---------- QUAN LY THE MUON SACH ----------" << endl << endl;
						do
						{
							cout << "Nhap vao 1 de xem danh sach the muon sach" << endl << endl;
							cout << "Nhap vao 2 de tao the muon sach" << endl << endl;
							cout << "Nhap vao 3 de thoat chuc nang 4:" << endl << endl;
							cin >> y;
							cin.ignore();
							switch (y)
							{
							case 1:
								showCardList(card, "card.bin");
								break;
							case 2:
								createBorrowCard(card, "reader.bin", "book.bin", "card.bin");
								cout << "The muon sach duoc tao thanh cong" << endl;
								break;
							case 3:
								break;
							default:
								cout << "Khong ton tai chuc nang" << endl;
								break;
							}
							system("pause");
							system("cls");
						} while (y != 3);
						break;
					case 5:
						cin.ignore();
						cout << "---------- QUAN LY THE TRA SACH ----------" << endl << endl;
						createReturnCard(card, "reader.bin", "book.bin", "card.bin");
						system("pause");
						system("cls");
					case 6:
						do
						{
							cout << "---------- THONG KE CO BAN ----------" << endl << endl;
							cout << "Nhap vao 1 de thong ke so luong sach trong thu vien" << endl << endl;
							cout << "Nhap vao 2 de thong ke so luong sach theo the loai" << endl << endl;
							cout << "Nhap vao 3 de thong ke so luong doc gia" << endl << endl;
							cout << "Nhap vao 4 de thong ke so luong doc gia theo gioi tinh" << endl << endl;
							cout << "Nhap vao 5 de thong ke so sach dang duoc muon" << endl << endl;
							cout << "Nhap vao 6 de thong ke danh sach do gia tre hen" << endl << endl;
							cout << "Nhap vao 7 de thoat chuc nang 6" << endl << endl;
							cin >> y;
							cin.ignore();
							system("cls");
							switch (y)
							{
							case 1:
								statisticOfBook("book.bin");
								cout << endl;
								break;
							case 2:
								statisticOfGenre("book.bin");
								cout << endl;
								break;
							case 3:
								statisticOfReader("reader.bin");
								cout << endl;
								break;
							case 4:
								statisticOfReaderGender("reader.bin");
								cout << endl;
								break;
							case 5:
								statisticOfBorrowedBook("book.bin");
								cout << endl;
								break;
							case 6:
								statisticOfLate("card.bin");
								cout << endl;
								break;
							case 7:
								break;
							default:
								cout << "Khong ton tai chuc nang" << endl;
								break;
							}
							system("pause");
							system("cls");
						} while (y != 7);
						break;
					case 7:
						break;
					default:
						cout << "Khong ton tai chuc nang" << endl;
						break;
					}
					system("cls");
				} while (func != 7);
			}
			else if (isExec == 1)

			{
				do
				{
					cout << "---------- CHUONG TRINH QUAN LY THU VIEN ----------" << endl << endl;
					cout << "Nhap vao 1 de quan ly he thong" << endl << endl;
					cout << "Nhap vao 2 de quan ly doc gia" << endl << endl;
					cout << "Nhap vao 3 de quan ly sach" << endl << endl;
					cout << "Nhap vao 4 de tao the muon sach" << endl << endl;
					cout << "Nhap vao 5 de tao the tra sach" << endl << endl;
					cout << "Nhap vao 6 de thong ke" << endl << endl;
					cout << "Nhap vao 7 de thoat chuong trinh" << endl << endl;
					cin >> func;
					system("cls");
					switch (func)
					{
					case 1:
						do
						{
							cout << "---------- QUAN LY NGUOI DUNG ----------" << endl << endl;
							cout << "Nhap vao 1 de dang xuat" << endl << endl;
							cout << "Nhap vao 2 de thay doi mat khau" << endl << endl;
							cout << "Nhap vao 3 de cap nhat thong tin nguoi dung" << endl << endl;
							cout << "Nhap vao 4 de thoat chuc nang 1" << endl << endl;
							cin >> y;
							cin.ignore();
							system("cls");
							switch (y)
							{
							case 1:
								return;
							case 2:
								changePassword(user, "user.bin");
								cout << "Mat khau duoc doi lai thanh cong" << endl;
								break;
							case 3:
								cout << "Thong tin hien tai cua nguoi dung" << endl;
								showInfo(user, "user.bin", curUser, curPass);
								system("pause");
								system("cls");
								updateInfo(user, "user.bin", curUser, curPass);
								cout << "Thong tin duoc cap nhat thanh cong" << endl;
								break;
							case 4:
								break;
							default:
								cout << "Khong ton tai chuc nang" << endl;
								break;
							}
							system("pause");
							system("cls");
						} while (y != 4);
						break;
					case 2:
						do
						{
							cout << "---------- QUAN LY DOC GIA ----------" << endl << endl;
							cout << "Nhap vao 1 xem danh sach doc gia" << endl << endl;
							cout << "Nhap vao 2 de them doc gia" << endl << endl;
							cout << "Nhap vao 3 de chinh sua thong tin doc gia" << endl << endl;
							cout << "Nhap vao 4 de tim doc gia theo CMND" << endl << endl;
							cout << "Nhap vao 5 de tim doc gia theo ten" << endl << endl;
							cout << "Nhap vao 6 de thoat chuc nang 2" << endl << endl;
							cin >> y;
							cin.ignore();
							system("cls");
							switch (y)
							{
							case 1:
								cout << "Danh sach doc gia:" << endl;
								listReader(reader, "reader.bin");
								break;
							case 2:
								addReader(reader, "reader.bin");
								cout << "Doc gia duoc them thanh cong" << endl;
								break;
							case 3:
								listReader(reader, "reader.bin");
								cout << "Nhap vap STT doc gia can thay doi thong tin:";
								cin >> index;
								cin.ignore();
								updateReaderInfo(reader, "reader.bin", index);
								cout << "Thong tin doc gia duoc thay doi thanh cong" << endl;
								break;
							case 4:
								cout << "Nhap vao CMND can tim :";
								cin.get(curID, 10);
								cin.ignore();
								findReaderID(reader, "reader.bin", curID);
								break;
							case 5:
								cout << "Nhap vao ten can tim :";
								cin.get(curName, 50);
								cin.ignore();
								findReaderName(reader, "reader.bin", curName);
								break;
							case 6:
								break;
							default:
								cout << "Khong ton tai chuc nang" << endl;
								break;
							}
							system("pause");
							system("cls");
						} while (y != 6);
						break;
					case 3:
						do
						{
							cout << "---------- QUAN LY SACH ----------" << endl << endl;
							cout << "Nhap vao 1 de tim sach theo ma ISBN" << endl << endl;
							cout << "Nhap vao 2 de tim sach theo ten" << endl << endl;
							cout << "Nhap vao 3 de thoat chuc nang 3" << endl << endl;
							cin >> y;
							cin.ignore();
							system("cls");
							switch (y)
							{
							case 1:
								cout << "Nhap vao ISBN cua sach can tim:";
								cin >> curID;
								cin.ignore();
								findAndShowBookInfo("book.bin", curID, curName, 0);
								break;
							case 2:
								cout << "Nhap vao ten cua sach can tim:";
								cin.get(curName, 51);
								cin.ignore();
								findAndShowBookInfo("book.bin", curID, curName, 0);
								break;
							case 3:
								break;
							default:
								cout << "Khong ton tai chuc nang" << endl;
								break;
							}
							system("pause");
							system("cls");
						} while (y != 3);
						break;
					case 4:
						system("cls");
						cout << "---------- QUAN LY THE MUON SACH ----------" << endl << endl;
						do
						{
							cout << "Nhap vao 1 de xem danh sach the muon sach" << endl << endl;
							cout << "Nhap vao 2 de tao the muon sach" << endl << endl;
							cout << "Nhap vao 3 de thoat chuc nang 4:" << endl << endl;
							cin >> y;
							cin.ignore();
							switch (y)
							{
							case 1:
								showCardList(card, "card.bin");
								break;
							case 2:
								createBorrowCard(card, "reader.bin", "book.bin", "card.bin");
								cout << "The muon sach duoc tao thanh cong" << endl;
								break;
							case 3:
								break;
							default:
								cout << "Khong ton tai chuc nang" << endl;
								break;
							}
							system("pause");
							system("cls");
						} while (y != 3);
						break;
					case 5:
						cin.ignore();
						cout << "---------- QUAN LY THE TRA SACH ----------" << endl << endl;
						createReturnCard(card, "reader.bin", "book.bin", "card.bin");
						system("pause");
						system("cls");
					case 6:
						do
						{
							cout << "---------- THONG KE CO BAN ----------" << endl << endl;
							cout << "Nhap vao 1 de thong ke so sach dang duoc muon" << endl << endl;
							cout << "Nhap vao 2 de thong ke danh sach do gia tre hen" << endl << endl;
							cout << "Nhap vao 3 de thoat chuc nang 6" << endl << endl;
							cin >> y;
							cin.ignore();
							system("cls");
							switch (y)
							{
							case 1:
								statisticOfBorrowedBook("book.bin");
								cout << endl;
								break;
							case 2:
								statisticOfLate("card.bin");
								cout << endl;
								break;
							case 3:
								break;
							default:
								cout << "Khong ton tai chuc nang" << endl;
								break;
							}
							system("pause");
							system("cls");
						} while (y != 3);
						break;
					case 7:
						break;
					default:
						cout << "Khong ton tai chuc nang" << endl;
						break;
					}
					system("cls");
				} while (func != 7);
			}
		}
	}
}