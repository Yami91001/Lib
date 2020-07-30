#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include<conio.h>
#include<Windows.h>
#define BUF_SIZE 1024*10

using namespace std;

//Biến động
static int location;


// Các struct
struct Date
{
	int year;
	int month;
	int day;
};

struct User
{
	char username[50];
	char password[50];
	char name[50];
	Date birthday;
	char ID[10];
	char address[50];
	char gender[4];
	int status;
	//1 Activated 0 Blocked
	int type;
	//1 Manager 0 Executive
};

struct Reader
{
	char readerID[10];
	char name[50];
	char ID[50];
	Date birthday;
	char gender[7];
	char email[50];
	char address[50];
	Date cardCreate;
	Date cardExpire;
};

struct Book
{
	char ISBN[10];
	char bName[50];
	char author[50];
	char publisher[50];
	int publishY;
	char genre[20];
	int price;
	int quantity;
	int borrowed ;
};

struct Card
{
	char borrowID[10];
	char ISBN[5][10];
	Date borrowDate;
	Date expectReturn;
	Date actualReturn;
	int number;
	bool late = 0;
	bool lost = 0;
};

//Các định nghĩa hàm

bool login(User& user, const char* filename, bool& isAdmin,
	bool& isManager, bool& isExecutive, char curUser[], char curPass[]);

int maxDay(int y, int m);

bool execLib(char* argv[]);

bool isLeapY(int n);

void inputDate(Date& date);

void newLogin(User& user);

bool checkAvailability(User user, const char* filename);

void changePassword(User& user, const char* filename);

void updateInfo(User& user, const char* filename, char curUser[], char curPass[]);

void showInfo(User user, const char* filename, char curUser[], char Pass[]);

void generalInfo(User& user);

void generalInfoUpdated(User& user);

void addUser(User& user, const char* filename);

void showList(User user, const char* filename);

void typeUser(User& user, const char* filename, int index);

bool checkReader(Reader reader, const char* filename);

void newReader(Reader& reader);

void generalReaderInfo(Reader& reader);

void listReader(Reader& reader, const char* filename);

void readerInfo(Reader& reader);

void CopyFile(const char* filename1, const char* filename2);

void addReader(Reader& reader, const char* filename);

void updateReaderInfo(Reader& reader, const char* filename, int index);

void deleteReader(Reader& reader, const char* filename1, const char* filename2, int index);

void findReaderID(Reader& reader, const char* filename, char curID[]);

void findReaderName(Reader& reader, const char* filename, char curName[]);

void newBook(Book& book);

bool checkBook(Book& book, const char* filename);

void bookInfo(Book& book);

void showBookInfo(Book book);

void showBookList(const char* filename);

void addBook(Book& book, const char* filename);

int findBook(const char* filename, const char* ISBN, const char* bName, int order);

void findAndShowBookInfo(const char* filename, const char* ISBN, const char* bName, int order);

void changeBookInfo(const char* filename, const char* ISBN, const char* bName, int order);

void moveBBottom(Book& book, const char* filename, int index);

void deleteBook(Book& book, const char* filename2, int index);

void findBookISBN(const char* filename, char curID[]);

void findBookName(const char* filename, char curName[]);

Date returnDate(Date date);

bool validReader(Card card, const char* filename);

void updateQuantity(Book& book, const char* filename, int k);

bool validBooks(Card card, int index, const char* filename);

int soSanhDate(Date date1, Date date2);

bool checkBorrowMore(Card card, char ID[], const char* filename3);

void borrowMore(Card& card, char ID[], const char* filename1, const char* filename2, const char* filename3);

void showcard(Card& card);

void showCardList(Card& card, const char* filename);

void createBorrowCard(Card& card, const char* filename1, const char* filename2, const char* filename3);

void moveCardBottom(Card& card, const char* filename, char ID[]);

void deleteCard(Card& card, const char* filename1, char ID[]);

int money(Book book, const char* filename2, char ISBN[]);

int isLost(Book& book, int n, const char* filename2);

int isLate(int n);

void backBooks(Book &book, Card &card, char ID[], const char* filename2, const char* filename3, int k);

void createReturnCard(Card& card, const char* filename1, const char* filename2, const char* filename3);

void statisticOfBook(const char* filename);

void statisticOfGenre(const char* filename);

void statisticOfReader(const char* filename);

void statisticOfReaderGender(const char* filename);

void statisticOfBorrowedBook(const char* filename);

void statisticOfLate(const char* filename);

void pass(char mk[]);

void clearScreen();