#include<stdio.h>
#include <string.h>
#include<conio.h>
#include<stdlib.h>
#include<ctype.h>
#include<windows.h>

void bookSetup();
int isBookIdPresent(int);
int isStudentCardPresent(int);
void studentSetup();
void issueBook();
void returnBook();
void inquiry();
void bookList();
void studentList();
void issueRegister();
void returnRegister();
int getBookRecordNo(int);
#define AVAILABLE 1
#define ISSUED 0
COORD coord= {0,0};
void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
struct Book
{
	int bid;
	char btitle[100];
	char bauthor[100];
	char bpublisher[100];
	int price;
	int status;
};
struct Student
{
	int cardno;
	int rollno;
	char course[50];
	char name[100];
	char father[100];
	int year;
};
struct Date
{
	int dd,mm,yy;
};
struct Issue
{
	int bid;
	char btitle[100];
	int cardno;
	struct Date idt;
	int days;
};
struct Return
{
	int bid;
	char btitle[100];
	int cardno;
	struct Date rdt;
};

struct Book getBookRecord(int);
struct Student getStudentRecord(int);
struct Student getBookStudent(struct Book);

main()
{
	int ch;
	while(1)
	{
		system("cls");
		gotoxy(30,1);
		printf("Library System");
		gotoxy(1,2);
		printf("-------------------------------------------------------------------");
		gotoxy(1,24);
		printf("--------------------------------------------------------------------");
		gotoxy(20,25);
		gotoxy(30,8);
		printf("1.   Book Setup");
		gotoxy(30,10);
		printf("2.   Student Setup");
		gotoxy(30,12);
		printf("3.   Issue Book");
		gotoxy(30,14);
		printf("4.   Return Book");
		gotoxy(30,16);
		printf("5.   Inqueiry");
		gotoxy(30,18);
		printf("6.   Exit");
		gotoxy(30,20);
		printf("Enter Choice");
		scanf("%d",&ch);
		if(ch==1)
			bookSetup();
		else
		if(ch==2)
			studentSetup();
		else
		if(ch==3)
			issueBook();
		else
		if(ch==4)
			returnBook();
		else
		if(ch==5)
			inquiry();
		else
		if(ch==6)
			break;
	}
}
void bookSetup()
{
	system("cls");
	struct Book b;

	gotoxy(30,1);
	printf("Book Setup");

	gotoxy(20,6);
	printf("Book Id    : ");
	gotoxy(20,8);
	printf("Book Title : ");
	gotoxy(20,10);
	printf("Book Auther: ");
	gotoxy(20,12);
	printf("Publisher  : ");
	gotoxy(20,14);
	printf("Book Price : ");

	while(1)
	{
		gotoxy(33,6);
		scanf("%d",&b.bid);
		if(isBookIdPresent(b.bid))
		{
			gotoxy(20,22);
			printf("Book Id Already Present. Press any Key.. ");
			getch();
		}
		else
			break;
	}

	fflush(stdin);
	gotoxy(33,8);
	gets(b.btitle);
	fflush(stdin);
	gotoxy(33,10);
	gets(b.bauthor);
	fflush(stdin);
	gotoxy(33,12);
	gets(b.bpublisher);
	fflush(stdin);
	gotoxy(33,14);
	scanf("%d",&b.price);
	b.status=AVAILABLE;
	gotoxy(20,20);
	printf("Save This Record (Y/N) ");
	char yn=getch();
	if(yn=='Y' || yn=='y')
	{
		FILE *fp;
		fp=fopen("Book.dat","ab");
		fwrite(&b,sizeof(b),1,fp);
		fclose(fp);
		gotoxy(20,22);
		printf("One Record Saved. Press Any Key to return..");
		getch();
	}
	else
	{
		gotoxy(20,22);
		printf("No Record Saved. Press Any Key To Return ..");
		getch();
	}
}
void studentSetup()
{
	struct Student s;
	system("cls");
	gotoxy(30,1);
	printf("Student Setup");
	gotoxy(30,6);
	printf("Student Card No  : ");
	gotoxy(30,8);
	printf("Student Roll No  : ");
	gotoxy(30,10);
	printf("Student Course   : ");
	gotoxy(30,12);
	printf("Student Name     : ");
	gotoxy(30,14);
	printf("Student Father   : ");
	gotoxy(30,16);
	printf("Year            : ");

	while(1)
	{
		gotoxy(50,6);
		scanf("%d", &s.cardno);
		if(isStudentCardPresent(s.cardno))
		{
			gotoxy(20,24);
			printf("Student Card Already Present.Press Any Key ");
			getch();
		}
		else
			break;
	}
	fflush(stdin);
	gotoxy(50,8);
	scanf("%d", &s.rollno);
	fflush(stdin);
	gotoxy(50,10);
	gets(s.course);
	fflush(stdin);
	gotoxy(50,12);
	gets(s.name);
	fflush(stdin);
	gotoxy(50,14);
	gets(s.father);
	fflush(stdin);
	gotoxy(50,16);
	scanf("%d", &s.year);
	gotoxy(30,18);
	printf("Save This Record (Y/N)");
	char yn=getch();
	if(yn=='Y'||yn=='y')
	{
		FILE *fp;
		fp=fopen("student.dat","ab");
		fwrite(&s,sizeof(s),1,fp);
		fclose(fp);
		gotoxy(30,20);
		printf("One Record Saved. Press Any Key To Return");
		getch();
	}
	else
	{
		gotoxy(30,20);
		printf("No Record Saved, Press Any Key To Return");
		getch();
	}
}
void issueBook()
{
	struct Issue i;
	system("cls");
	gotoxy(30,1);
	printf("Book Issue");
	gotoxy(30,6);
	gotoxy(1,2);
	printf("----------------------------------------------------------------------");
	gotoxy(30,6);
	printf("Book Id      :");
	gotoxy(30,8);
	printf("Book Title   :");
	gotoxy(30,10);
	printf("Student Card No      :");
	gotoxy(30,12);
	printf("Student Name : ");
	gotoxy(30,14);
	printf("Book Date    :");
	gotoxy(30,16);
	printf("No Of Days           :");

	while(1)
	{
		gotoxy(53,6);
		scanf("%d",&i.bid);
		if(isBookIdPresent(i.bid))
		{
			struct Book b=getBookRecord(i.bid);
			if(b.status==ISSUED)
			{
				gotoxy(20,22);
				printf("Specified Book is not available. It is issued.");
				getch();
				return;
			}
			gotoxy(53,8);
			strcpy(i.btitle,b.btitle);
			printf("%s",b.btitle);
			break;
		}
		else
		{
			gotoxy(20,24);
			printf("Bookid Not Present. Press Any Key and Enter Again");
			getch();
		}
	}
	fflush(stdin);
	while(1)
	{
		gotoxy(53,10);
		scanf("%d",&i.cardno);
		if(isStudentCardPresent(i.cardno))
		{
			struct Student s=getStudentRecord(i.cardno);
			gotoxy(53,12);
			printf("%s",s.name);
			break;
		}
		else
		{
			gotoxy(20,24);
			printf("Student Card No. Not Present.Press any Key and Enter Again.. ");
			getch();
		}
	}

	fflush(stdin);
	gotoxy(53,14);
	scanf("%d %d %d",&i.idt.dd,&i.idt.mm,&i.idt.yy);
	fflush(stdin);
	gotoxy(53,16);
	scanf("%d",&i.days);
	gotoxy(30,18);
	printf("Save This Record (Y/N)");
	char yn=getch();
	if(yn=='Y'||yn=='y')
	{
		FILE*fp;
		fp=fopen("issue.dat","ab");
		fwrite(&i,sizeof(i),1,fp);
		fclose(fp);
		gotoxy(30,20);
		printf("One Record Saved.Press Any Key To Return");
		getch();
		int rno=getBookRecordNo(i.bid);
		struct Book b=getBookRecord(i.bid);
		b.status=ISSUED;
		fp=fopen("Book.dat","rb+");
		fseek(fp,(rno-1)*sizeof(b),SEEK_SET);
		fwrite(&b,sizeof(b),1,fp);
		fclose(fp);
		return;
	 }
	 else
	 {
		gotoxy(30,22);
		printf("No Record Saved.Press Any Key To Return");
		getch();
	 }
}
void returnBook()
{
	struct Return r;

	system("cls");
	gotoxy(30,1);
	printf("Book Return");
	gotoxy(30,6);
	gotoxy(1,2);
	printf("----------------------------------------------------------------------");
	gotoxy(30,6);
	printf("Book Id      :");
	gotoxy(30,8);
	printf("Book Title   :");
	gotoxy(30,10);
	printf("Student Card No      :");
	gotoxy(30,12);
	printf("Student Name       :");

	gotoxy(30,14);
	printf("Return Date    :");

	while(1)
	{
		gotoxy(53,6);
		scanf("%d",&r.bid);
		if(isBookIdPresent(r.bid))
		{
			struct Book b=getBookRecord(r.bid);
			if(b.status==AVAILABLE)
			{
				gotoxy(20,22);
				printf("Specified Book is not issued. It is Available.");
				getch();
				return;
			}
			gotoxy(53,8);
			strcpy(r.btitle,b.btitle);
			printf("%s",b.btitle);
			struct Student s=getBookStudent(b);
			gotoxy(53,10);
			printf("%d ",s.cardno);
			r.cardno=s.cardno;
			gotoxy(53,12);
			printf("%s ",s.name);
			break;
		}
		else
		{
			gotoxy(20,24);
			printf("Bookid Not Present. Press Any Key and Enter Again");
			getch();
		}
	}
	fflush(stdin);
	gotoxy(53,14);
	scanf("%d %d %d",&r.rdt.dd,&r.rdt.mm,&r.rdt.yy);
	gotoxy(30,18);
	printf("Save This Record (Y/N)");
	char yn=getch();
	if(yn=='Y'||yn=='y')
	{
		FILE*fp;
		fp=fopen("Return.dat","ab");
		fwrite(&r,sizeof(r),1,fp);
		fclose(fp);
		gotoxy(30,20);
		printf("One Record Saved.Press Any Key To Return");
		getch();

		int rno=getBookRecordNo(r.bid);
		struct Book b=getBookRecord(r.bid);


		fp=fopen("Book.dat","rb+");
		fseek(fp,(rno-1)*sizeof(b),SEEK_SET);
		b.status=AVAILABLE;
		fwrite(&b,sizeof(b),1,fp);
		fclose(fp);
		return;
	 }
	 else
	 {
		gotoxy(30,22);
		printf("No Record Saved.Press Any Key To Return");
		getch();
	 }
}
struct Student getBookStudent(struct Book b)
{
	struct Issue i,I;
	FILE *fp;
	fp=fopen("Issue.dat","rb");
	while(fread(&i,sizeof(i),1,fp))
	{
		if(i.bid==b.bid)
			I=i;
	}
	fclose(fp);
	struct Student s=getStudentRecord(i.cardno);
	return(s);
}

void inquiry()
{
	int ch;
	while(1)
	{
		system("cls");
		gotoxy(35,1);
		printf("Inquiry");
		gotoxy(1,2);
		printf("-------------------------------------------------------");
		gotoxy(30,8);
		printf("1.    Book List");
		gotoxy(30,10);
		printf("2.    Student List");
		gotoxy(30,12);
		printf("3.    Issue Register");
		gotoxy(30,14);
		printf("4.    Return Register");
		gotoxy(30,16);
		printf("5.    Exit");
		gotoxy(30,18);
		printf("Enter Choice");
		scanf("%d",&ch);
		if(ch==1)
			bookList();
		else
		if(ch==2)
			studentList();
		else
		if(ch==3)
			issueRegister();
		else
		if(ch==4)
			returnRegister();
		else
		if(ch==5)
			break;
	}
}

void bookList()
{
	FILE *fp;
	fp=fopen("book.dat","rb");
	if(fp==NULL)
	{
		gotoxy(25,20);
		printf("No Book Record Present ");
		getch();
		return;
	}
	struct Book b;
	system("cls");
	gotoxy(30,1);
	printf("List of Books");
	gotoxy(1,2);
	printf("-------------------------------------------------------------------------\n");
	printf("BookId  BookTitle       Author                Publisher     Price  Status\n");
	printf("-------------------------------------------------------------------------\n");

	while(fread(&b,sizeof(b),1,fp))
	{
		printf("%6d  %-14s  %-20s  %-16s  %d  %s\n",b.bid,b.btitle,b.bauthor,b.bpublisher,b.price,(b.status==ISSUED?"Issued":"Available"));
	}
	fclose(fp);
	getch();
}
void studentList()
{

       FILE *fp;
       fp=fopen("student.dat","rb");
       if(fp==NULL)
       {
		gotoxy(25,20);
		printf("No struct Book Record Present ");
		getch();
		return;
       }
       struct Student s;
       system("cls");
       gotoxy(30,1);
       printf("List of Students\n");
       printf("---------------------------------------------------------------------\n");
       printf("CardNo  RollNo   Course    Name                 Father         Year\n");
       printf("---------------------------------------------------------------------\n");
       while(fread(&s,sizeof(s),1,fp))
       {
		printf("%6d  %6d   %-10s  %-15s  %-15s  %d\n",s.cardno,s.rollno,s.course,s.name,s.father,s.year);
	}
	fclose(fp);
	getch();
}

void issueRegister()
{
	FILE *fp;
	fp=fopen("Issue.dat","rb");
	if(fp==NULL)
	{
		gotoxy(25,20);
		printf("No Book Record Present ");
		getch();
		return;
	}

	struct Issue i;
	system("cls");
	gotoxy(30,1);
	printf("Issue Register\n");
	printf("----------------------------------------------------------------\n");
	printf("BookId  Book Title            CardNo   Issue Date     Days\n");
	printf("----------------------------------------------------------------\n");
	while(fread(&i,sizeof(i),1,fp))
	{
		printf("%6d  %-15s    %6d      %d/%d/%d    %d\n",i.bid,i.btitle,i.cardno,i.idt.dd,i.idt.mm,i.idt.yy,i.days);
	}
	fclose(fp);
	getch();
}
int isStudentCardPresent(int cno)
{
	FILE *fp;
	fp=fopen("Student.dat","rb");
	if(fp==NULL)
	{
		return 0;
	}
	struct Student s;
	while(fread(&s,sizeof(s),1,fp))
	{
		if(cno==s.cardno)
		{
			fclose(fp);
			return 1;
		}
	}
	fclose(fp);
	return 0;
}



int isBookIdPresent(int bid)
{
	FILE *fp;
	fp=fopen("book.dat","rb");
	if(fp==NULL)
	{
		return 0;
	}
	struct Book b;
	while(fread(&b,sizeof(b),1,fp))
	{
		if(bid==b.bid)
		{
			fclose(fp);
			return 1;
		}
	}
	fclose(fp);
	return 0;
}

int getBookRecordNo(int bid)
{
	FILE *fp;
	fp=fopen("book.dat","rb");
	if(fp==NULL)
	{
		return 0;
	}
	struct Book b;
	int i=0;
	while(fread(&b,sizeof(b),1,fp))
	{
		i++;
		if(bid==b.bid)
		{
			fclose(fp);
			return i;
		}
	}
	fclose(fp);
	return 0;
}


struct Book getBookRecord(int bid)
{
	FILE *fp;
	fp=fopen("book.dat","rb");
	struct Book b;
	if(fp==NULL)
	{
		printf("Book File Not Present ");
		getch();
		return b;
	}
	while(fread(&b,sizeof(b),1,fp))
	{
		if(bid==b.bid)
		{
			fclose(fp);
			return(b);
		}
	}
	fclose(fp);
	return b;
}

struct Student getStudentRecord(int cno)
{
	FILE *fp;
	fp=fopen("Student.dat","rb");
	struct Student s;
	if(fp==NULL)
	{
		printf("Student File Not Present ");
		getch();
		return s;
	}
	while(fread(&s,sizeof(s),1,fp))
	{
		if(cno==s.cardno)
		{
			fclose(fp);
			return(s);
		}
	}
	fclose(fp);
	return s;
}



void returnRegister()
{
	FILE *fp;
	fp=fopen("Return.dat","rb");
	if(fp==NULL)
	{
		gotoxy(25,20);
		printf("No struct Book Record Present ");
		getch();
		return;
	}
	int bid;
	char btitle[100];
	int cardno;
	struct Date rdt;


	struct Return r;
	system("cls");
	gotoxy(30,1);
	printf("struct Book Return Register\n");
	printf("----------------------------------------------------------------\n");
	printf("BookId  Book Title            CardNo   Return Date     \n");
	printf("----------------------------------------------------------------\n");
	while(fread(&r,sizeof(r),1,fp))
	{
		printf("%6d  %-15s    %6d      %d/%d/%d    \n",r.bid,r.btitle,r.cardno,r.rdt.dd,r.rdt.mm,r.rdt.yy);
	}
	fclose(fp);
	getch();
}


