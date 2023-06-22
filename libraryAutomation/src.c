#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student{
	char stdID[9], name[30], surname[30];
	int score;
	struct student *next, *prev;
}STD;

typedef struct author{
	char authorName[30], authorSurname[30];
	int authorID;
	struct author *next;
}AUTHOR;

typedef struct bookCopy{
	char labelNo[20], status[9];
	struct bookCopy *next;
}BOOKCOPY;

typedef struct book{
	char bookName[30], ISBN[14];
	int quantity;
	struct book *next;
	struct bookCopy *head;
}BOOK;

typedef struct authorBook{
	char ISBN[14];
	int authorID;
}AUTHORBOOK;

typedef struct date{
	unsigned int day:5;
	unsigned int month:4;
	unsigned int year:12;
}DATE;

typedef struct borrowed{
	char labelNo[20], stdID[9];
	unsigned int transactionType:1;
	DATE transactionDate;
}BORROWED;


int linesofNPB(char* bookNotPresentFile){
	int lines=0;
	char line[256];
	FILE* fp=fopen(bookNotPresentFile, "r");
	if(fp==NULL){
		printf("couldnt opened\n");
	}
	else{
		while(fgets(line, sizeof(line), fp)!=NULL){
			lines++;
		}
	}
	fclose(fp);
	return lines;
}

// reading authors from file 
AUTHOR* readAuthorsFromFile(char* fileAutName){
	FILE* fpa;
	AUTHOR *head1=NULL, *enda, *tmpa;
	fpa=fopen(fileAutName, "r");
	if(fpa==NULL){
		printf("file couldnt opened\n");
	}
	else{
		while (!feof(fpa)){
			tmpa=(AUTHOR*)malloc(sizeof(AUTHOR));
			if(tmpa==NULL) printf("couldnt allocated\n");		
			fscanf(fpa, "%29[^,],%29[^,],%d\n", tmpa->authorName, tmpa->authorSurname, &tmpa->authorID);
			tmpa->next=NULL;
			if(head1==NULL){
				head1=enda=tmpa;
			}	
			else{
				enda->next=tmpa;
				enda=enda->next;
			}
		}
			
	}
	fclose(fpa);
	return head1;
}

//------------AUTHOR------------

// evaluating if of last author
void authorNumber(char* autFileName, int* a_count){
	FILE* fp=fopen(autFileName, "r");
	char temp1[30], temp2[30];
	if(fp==NULL){
		printf("couldnt opened\n");
	}
	else{
		while(!feof(fp)){
			fscanf(fp, "%29[^,],%29[^,],%d\n", temp1, temp2, a_count);
		}
	}
	fclose(fp);
}

// write to authors file
void writeToAuthors(AUTHOR* heada, char* fileName){
	AUTHOR* iter= heada;
	FILE* fp=fopen(fileName, "w");
	while(iter!=NULL){
		fprintf(fp, "%s,%s,%d\n", iter->authorName, iter->authorSurname, iter->authorID);
		iter=iter->next;
	}
	fclose(fp);
}

// create author and return
AUTHOR* createAuthor(char* autname, char* autsurname, int* a_count){
	AUTHOR* newAuthora=(AUTHOR*)malloc(sizeof(AUTHOR));
	if(newAuthora==NULL) printf("couldnt allocated\n");
	strcpy(newAuthora->authorName, autname);
	strcpy(newAuthora->authorSurname, autsurname);
	newAuthora->authorID=(*a_count)+1;
	newAuthora->next=NULL;
	return newAuthora;
}

// add author
void addAuthors(char *autFileName, int* a_count){
	char autname[30], autsurname[30];
	printf("Author Name: "); scanf(" %29[^\n]", autname);
	printf("Author Surname: "); scanf(" %29[^\n]", autsurname);
	authorNumber(autFileName, a_count);
	FILE *fp=fopen(autFileName, "a");
	if(fp==NULL) printf("couldnt opened\n");
	fprintf(fp, "\n%s,%s,%d", autname, autsurname, *a_count+1);
	fclose(fp);
}

char* deletefromautbookmatch(int id, AUTHORBOOK* autmatchbooktemp, int autbookmatchline, char* bookautfileName){
	int i;
	char *temp=(char*)malloc(14*sizeof(char));
	if(temp==NULL) printf("couldnt allocated\n");
	for(i=0;i<autbookmatchline;i++){
		if(autmatchbooktemp[i].authorID==id){
			autmatchbooktemp[i].authorID=-1;
			strcpy(temp, autmatchbooktemp[i].ISBN);
		}
	}
	FILE *fp3=fopen(bookautfileName, "w");
	if(fp3==NULL){
		printf("couldnt opened\n");
	}
	for(i=0;i<autbookmatchline;i++){
		fprintf(fp3, "%s,%d\n", autmatchbooktemp[i].ISBN, autmatchbooktemp[i].authorID);
	}
	fclose(fp3);
	return temp;
}

// read bookaut file
void readBookAut(char* bookautfileName, AUTHORBOOK* authorBookArr){
	FILE* fp;
	int i=0;
	fp=fopen(bookautfileName, "r");
	if(fp==NULL){
		printf("couldnt opened\n");
	}
	else{
		while (!feof(fp)){		
			fscanf(fp, "%13[^,],%d\n", authorBookArr[i].ISBN, &authorBookArr[i].authorID);
			i++;
		}		
	}
	fclose(fp);
}

// number of certain author books
int findautbooks(char* bookautfileName, int id){
	int i=0, temp1;
	char temp2[14];
	FILE *fp=fopen(bookautfileName, "r");
	if(fp==NULL) printf("couldnt opened\n");
	while(!feof(fp)){
		fscanf(fp, "%13[^,],%d\n", temp2, &temp1);
		if(temp1==id){
			i++;
		}
	}
	fclose(fp);
	return i;
}

//read bookaut v2
void readBookAutv2(char* bookautfileName, AUTHORBOOK* autbook, int id){
	char tempisbn[14];
	int tempid, i=0;
	FILE* fp=fopen(bookautfileName, "r");
	if(fp==NULL) printf("couldnt opened\n");
	while(!feof(fp)){
		fscanf(fp, "%13[^,],%d\n", tempisbn, &tempid);
		if(tempid==id){
			strcpy(autbook[i].ISBN, tempisbn);
			autbook[i].authorID=tempid;
			i++;
		}
	}
	fclose(fp);
}

// read books
BOOK* readBooksFromFile(char* fileBookName){
	FILE* fpb;
	BOOK *headb=NULL, *endb, *tmpb;
	fpb=fopen(fileBookName, "r");
	if(fpb==NULL){
		printf("file couldnt opened\n");
	}
	else{
		while (!feof(fpb)){
			tmpb=(BOOK*)malloc(sizeof(BOOK));
			if(tmpb==NULL) printf("couldnt allocated\n");		
			fscanf(fpb, "%29[^,],%13[^,],%d\n", tmpb->bookName, tmpb->ISBN, &tmpb->quantity);
			tmpb->next=NULL;
			if(headb==NULL){
				headb=endb=tmpb;
			}	
			else{
				endb->next=tmpb;
				endb=endb->next;
			}
		}
			
	}
	fclose(fpb);
	return headb;
}

// list certain author's data
void listCertainAut(char* autFileName, char* bookautfileName, char* bookNotPresentFile, char* bookFileName){
	char name[30], surname[30];
	printf("please enter name of the author: "); scanf("%s", name);
	printf("please enter surname of the author: "); scanf("%s", surname);
	AUTHOR* authead=readAuthorsFromFile(autFileName);
	while(authead!=NULL && (strcmp(authead->authorName, name)!=0 || strcmp(authead->authorSurname, surname)!=0)){
		authead=authead->next;
	}
	if(authead==NULL){
		printf("there is no such author (%s %s)\n", name, surname);
	}
	else{
		int id=authead->authorID;
		int n=findautbooks(bookautfileName, id);
		if(n==0){
			printf("%s %s has no any book records in database\n", authead->authorName, authead->authorSurname);
		}
		else{
			int i;
			AUTHORBOOK* autbook=(AUTHORBOOK*)malloc(n*sizeof(AUTHORBOOK));
			if(autbook==NULL) printf("couldnt allocated\n");
			readBookAutv2(bookautfileName, autbook, id);
			BOOK* booktemp=readBooksFromFile(bookFileName);
			BOOK* booktemp2=booktemp;
			printf("%s %s's books:\n",authead->authorName, authead->authorSurname);
			while(booktemp2!=NULL){
				for(i=0;i<n;i++){
					if(strcmp(autbook[i].ISBN, booktemp2->ISBN)==0){
						printf("%s\n", booktemp2->bookName);
					}
				}
				booktemp2=booktemp2->next;
			}
			free(autbook);
		}	
	}
}

//----STUDENT---------------------

// reading students from file to linked list
STD* readStudentsFromFile(char* fileName){
	FILE* fp;
	STD* head=NULL, *end, *tmp;
	fp=fopen(fileName, "r");
	if(fp==NULL){
		printf("file couldnt opened\n");
	}
	else{
		while(!feof(fp)){
			tmp=(STD*)malloc(sizeof(STD));
			if(tmp==NULL) printf("couldnt allocated\n");
			fscanf(fp, "%8[^,],%29[^,],%29[^,],%d\n", tmp->stdID, tmp->name, tmp->surname, &tmp->score);
			tmp->next=NULL;
			if(head==NULL){
				head=end=tmp;
			}	
			else{
				end->next=tmp;
				end=end->next;
			}
		}
		fclose(fp);	
	}
	return head;
}

// write to students file
void writeToStudents(STD* head, char* fileName){
	STD* iter= head;
	FILE* fp=fopen(fileName, "w");
	while(iter!=NULL){
		fprintf(fp, "%s,%s,%s,%d\n", iter->stdID, iter->name, iter->surname, iter->score);
		iter=iter->next;
	}
	fclose(fp);
}

// create student
STD* createStudent(STD** head, char* stuname, char* stusurname, char* stuID){
	STD* newStudent=(STD*)malloc(1*sizeof(STD));
	strcpy(newStudent->name, stuname);
	strcpy(newStudent->surname, stusurname);
	strcpy(newStudent->stdID, stuID);
	newStudent->score=100;
	newStudent->next=NULL;
	return newStudent;
}

// adding student
void addStudent(STD** head, char *stdFileName){
	char stuname[30], stusurname[30], stuID[8];
	printf("Student Name: "); scanf(" %29[^\n]", stuname);
	printf("Student Surname: "); scanf(" %29[^\n]", stusurname);
	printf("Student ID: "); scanf("%s", stuID);
	STD* newStudent=createStudent(head, stuname, stusurname, stuID);
	*head=readStudentsFromFile(stdFileName);
	if(*head==NULL){
		newStudent->next=*head;
		*head=newStudent;
	}
	else{
		STD* iter=*head;
		while(iter->next!=NULL){
			iter=iter->next;
		}
		newStudent->next=iter->next;
		iter->next=newStudent;
	}
	writeToStudents(*head, stdFileName);
}

// listing students
void listStudent(char* stdFileName){
	STD* iter=readStudentsFromFile(stdFileName);
	if(iter==NULL){
		printf("list is empty\n");
	}
	else{
		while(iter!=NULL){
			printf("ID: %s Full Name: %s %s Score: %d\n", iter->stdID, iter->name, iter->surname, iter->score);
			iter=iter->next;
		}
	}
	
}

// search student
void searchStudent(STD* head, char* stdFileName, BORROWED* odunctutstd, int numbernPBstd){
	char stuID[10];
	int i, a, b, c, d;
	printf("Student ID: "); scanf("%s", stuID);
	STD* tmp=readStudentsFromFile(stdFileName);
	
	while(tmp!=NULL && strcmp(tmp->stdID, stuID)!=0){
		tmp=tmp->next;
	}
	if(tmp==NULL){
		printf("%s not found\n", stuID);
	}
	else{
		printf("Name: %s Surname: %s ID: %s Score: %d\n", tmp->name, tmp->surname, tmp->stdID, tmp->score);
	}
	printf("%s's transactions:\n", tmp->name);
	for(i=0;i<numbernPBstd;i++){
		if(strcmp(odunctutstd[i].stdID, stuID)==0){
			a=odunctutstd[i].transactionType; b=odunctutstd[i].transactionDate.day; c=odunctutstd[i].transactionDate.month; d=odunctutstd[i].transactionDate.year;
			printf("%s,%s,%d, %d.%d.%d\n", odunctutstd[i].labelNo, odunctutstd[i].stdID, a, b, c, d);
		}
	}
}

// deleting student
void deleteStudent(STD** head, char* stdFileName){
	char stuID[10];
	printf("Student ID: "); scanf("%s", stuID);
	STD* tmp2=readStudentsFromFile(stdFileName);
	STD* tmp=tmp2;
	if(strcmp(tmp2->stdID, stuID)==0){
		tmp=tmp2;
		tmp2=tmp2->next;
		free(tmp);
		printf("%s deleted\n", stuID);
	}
	else{
		STD* cur;
		tmp=tmp2;
		while(tmp->next!=NULL && strcmp(tmp->next->stdID, stuID)!=0){
			tmp=tmp->next;
		}
		if(tmp->next!=NULL){
			cur = tmp->next;
			tmp->next=tmp->next->next;
			free(cur);
			printf("%s deleted\n", stuID);
		}
		else{
			printf("%s not found ", stuID);
		}
	}
	writeToStudents(tmp2, stdFileName);
}

//-----BOOK--------------------------

//read book not present file
BOOKCOPY* readNPB(char* bookNotPresentFile){
	FILE* fp=fopen(bookNotPresentFile, "r");
	if(fp==NULL) printf("couldnt opened\n");
	BOOKCOPY* head=NULL, *end, *tmp;
	while(!feof(fp)){
		tmp=(BOOKCOPY*)malloc(sizeof(BOOKCOPY));
		fscanf(fp, "%13[^,],%8[^,]\n", tmp->labelNo, tmp->status);
		tmp->next=NULL;
		if(head==NULL){
			head=end=tmp;
		}	
		else{
			end->next=tmp;
			end=end->next;
		}
	}
	fclose(fp);
	return head;
}

//kitap ornegý linked liste alma
BOOKCOPY* readBookCopy(char* bookcopyname){
	BOOKCOPY *head=NULL, *end, *tempbb;
	FILE *fp=fopen(bookcopyname, "r");
	if(fp==NULL) printf("couldnt opened\n");
	while(!feof(fp)){
		tempbb=(BOOKCOPY*)malloc(sizeof(BOOKCOPY));
		if(tempbb==NULL) printf("allocation error\n");
		fscanf(fp, "%19[^,],%s\n", tempbb->labelNo, tempbb->status);
		tempbb->next=NULL;
			if(head==NULL){
				head=end=tempbb;
			}	
			else{
				end->next=tempbb;
				end=end->next;
			}
	}
	fclose(fp);
	return head;
}

//write to kitapornek
void writetokitapornek(BOOKCOPY* head, char* bookNotPresentFile){
	FILE* fpfpfp=fopen(bookNotPresentFile, "w");
	if(fpfpfp==NULL) printf("couldnt opened\n");
	BOOKCOPY* iter=head;
	while(iter!=NULL){
		fprintf(fpfpfp, "%s,%s\n", iter->labelNo, iter->status);
		iter=iter->next;
	}
	fclose(fpfpfp);
}

// after deleting author write "-1" front of his books
void deletebooktoo(char* isbntemp, char* bookNotPresentFile){
	char* newstatus="-1";
	BOOKCOPY* copyhead=readBookCopy(bookNotPresentFile);
	BOOKCOPY* copytemp=copyhead;
	while(copytemp!=NULL){
		if(strncmp(copytemp->labelNo, isbntemp, 13)==0){
			strcpy(copytemp->status, newstatus);
		}
		copytemp=copytemp->next;
	}
	writetokitapornek(copyhead, bookNotPresentFile);
}

// delete author
void deleteAuthor(AUTHOR** heada, char* autFileName, char* bookautfileName, AUTHORBOOK* autmatchbook, int autbookmatchline, char* bookNotPresentFile){
	int autID;
	char *isbntemp;
	printf("Author ID: "); scanf("%d", &autID);
	AUTHOR* tmp2=readAuthorsFromFile(autFileName);
	AUTHOR* tmp=tmp2;	
	if(tmp2->authorID==autID){
		tmp2=tmp2->next;
		printf("%s %s (%d) deleted\n", tmp->authorName, tmp->authorSurname, tmp->authorID);
		isbntemp=deletefromautbookmatch(autID, autmatchbook, autbookmatchline, bookautfileName);
		deletebooktoo(isbntemp, bookNotPresentFile);
		free(tmp);
	}
	else{
		AUTHOR* cur;
		while(tmp->next!=NULL && tmp->next->authorID!=autID){
			tmp=tmp->next;
		}
		if(tmp->next!=NULL){
			cur = tmp->next;
			tmp->next=tmp->next->next;	
			printf("%s %s (%d) deleted\n",  cur->authorName, cur->authorSurname, cur->authorID);
			isbntemp=deletefromautbookmatch(autID, autmatchbook, autbookmatchline, bookautfileName);
			deletebooktoo(isbntemp, bookNotPresentFile);
			free(cur);
		}
		else{
			printf("%d not found ", autID);
		}
	}
	writeToAuthors(tmp2, autFileName);
}



// write to books file
void writeToBooks(BOOK* headb, char* fileName){
	BOOK* iter= headb;
	FILE* fp=fopen(fileName, "w");
	while(iter!=NULL){
		fprintf(fp, "%s,%s,%d\n", iter->bookName, iter->ISBN, iter->quantity);
		iter=iter->next;
	}
	fclose(fp);
}

// create book and return
BOOK* createBook(char* bookname, char* bookisbn, int bookcopy){
	BOOK* newbook=(BOOK*)malloc(sizeof(BOOK));
	if(newbook==NULL) printf("couldnt allocated\n");
	strcpy(newbook->bookName, bookname);
	strcpy(newbook->ISBN, bookisbn);
	newbook->quantity=bookcopy;
	newbook->next=NULL;
	return newbook;
}

// append new book to AuthorBook file
void appendToBookAut(BOOK* newBook, char* bookautfileName, int book_aut){
	FILE* fp=fopen(bookautfileName, "a");
	if(fp==NULL){
		printf("couldnt opened\n");
	}
	fprintf(fp, "%s,%d\n", newBook->ISBN, book_aut);
	fclose(fp);
}

// append to "bookcopy" file
void appendtobookcopy(char* bookNotPresentFile, char* bookisbn, int bookcopy){
	int i;
	char *status="RAFTA", *underscore="_", tut[5], neew[20];
	FILE* fp=fopen(bookNotPresentFile, "a");
	if(fp==NULL) printf("couldnt opened\n");
	for(i=0;i<bookcopy;i++){
		itoa(i+1, tut, 10);
		strcpy(neew, bookisbn);
		strcat(neew, underscore);
		strcat(neew, tut);
		fprintf(fp, "%s,%s\n", neew, status);
	}
	fclose(fp);
}

// add book
void addBook(BOOK** headb, char *bookFileName, int* deleted_auts, AUTHOR** heada, char* autFileName, char* bookautfileName, AUTHORBOOK* authorBookArr, char* bookNotPresentFile){
	*heada=readAuthorsFromFile(autFileName);
	int flag=0;
	int valid_input=0, i;
	char bookName[30], bookisbn[14];
	int bookcopy, book_aut;
	*headb=readBooksFromFile(bookFileName);
	BOOK* isbn_control=*headb;
	printf("Book Name: "); scanf(" %29[^\n]", bookName);
	printf("Book ISBN: "); scanf("%s", bookisbn);
	while(strlen(bookisbn)!=13){
		printf("please enter 13 digits ISBN: ");
		scanf("%s", bookisbn);
	}
	while(isbn_control!=NULL && strcmp(bookisbn, isbn_control->ISBN)!=0){
		isbn_control=isbn_control->next;
	}
	if(isbn_control!=NULL){
		flag=1;
	}
	if(flag==1){
		printf("this book is already recorded in database\nit will added as a new copy\n");
		isbn_control->quantity++;
	}
	else{
		printf("how many copies are there? "); scanf("%d", &bookcopy);
		AUTHOR* autids=readAuthorsFromFile(autFileName);
		AUTHOR* auttemp;
		while(valid_input==0){
			printf("please enter the id of author: "); scanf("%d", &book_aut);
			auttemp=autids;
			while(auttemp!=NULL && valid_input!=1){
				if(auttemp->authorID==book_aut){
					valid_input=1;
				}
				auttemp=auttemp->next;
			}
		}
		BOOK* newBook=createBook(bookName, bookisbn, bookcopy);
		if(*headb==NULL){
			newBook->next=*headb;
			*headb=newBook;
		}
		else{
			BOOK* iter=*headb;
			while(iter->next!=NULL){
				iter=iter->next;
			}
			newBook->next=iter->next;
			iter->next=newBook;
		}
		appendToBookAut(newBook, bookautfileName, book_aut);
		readBookAut(bookautfileName, authorBookArr);
		appendtobookcopy(bookNotPresentFile, bookisbn, bookcopy);
	}
	writeToBooks(*headb, bookFileName);
}

// finding number of lines
int findlinenumber(char* filename){
	int line_count=0;
	char line[256];
	FILE* fpfp=fopen(filename, "r");
	if(fpfp==NULL){
		printf("couldnt opened\n");
	}
	else{
		while(fgets(line, sizeof(line), fpfp)!=NULL){
			line_count++;
		}
	}
	fclose(fpfp);
	return line_count;
}

void appendBookTransactions(BOOKCOPY* search, char* borrowerID, int d, int m, int y, char* bookTransactions){
	FILE* fp=fopen(bookTransactions, "a");
	if(fp==NULL) printf("couldnt opened\n");
	fprintf(fp, "\n%s,%s,%d,%d.%d.%d", search->labelNo, borrowerID, 0, d, m, y);
	fclose(fp);
}

// borrowing book
void borrowBook(char* stdFileName, char* bookNotPresentFile, BOOKCOPY* notPresentBook, char* fileBookName, int numbernPB, char* bookTransactions, BORROWED* odunctut){
	STD* temp=readStudentsFromFile(stdFileName);
	char* shelfornot="RAFTA";
	char borrowerID[9];
	printf("enter the ID of student who will borrow book"); scanf("%s", borrowerID);
	while(strlen(borrowerID)!=8){
		printf("please enter 8 digit"); scanf("%s", borrowerID);
	}
	STD* iterstu=temp;
	while(iterstu!=NULL && strcmp(iterstu->stdID, borrowerID)!=0){
		iterstu=iterstu->next;
	}
	if(iterstu==NULL){
		printf("there is no student record with this id (%s)\n", borrowerID);
	}
	else{
		if(iterstu->score<=0){
			printf("your score is below 0 you cannot borrow any book!\n");
		}
		else{
			printf("%s %s %s found\n", iterstu->name, iterstu->surname, iterstu->stdID);
			char booktoborrowed[30];
			printf("which book will be borrowed?"); scanf(" %29[^\n]", booktoborrowed);
			BOOK* booknode=readBooksFromFile(fileBookName);
			BOOK* tempbook=booknode;
			while(tempbook!=NULL && strcmp(tempbook->bookName, booktoborrowed)!=0){
			tempbook=tempbook->next;
			}
			if(tempbook==NULL){
				printf("there is no such book (%s)\n", booktoborrowed);
			}
			else{
				int a, numberofnp=0;
				BOOKCOPY* iter=notPresentBook;
				BOOKCOPY* headC=readBookCopy(bookNotPresentFile);
				BOOKCOPY* search=headC;
				BOOKCOPY* current=headC;
				while((strncmp(search->labelNo, tempbook->ISBN, 13)!=0 || strcmp(search->status, shelfornot)!=0) && search!=NULL){
				search=search->next;
				}
				if(search==NULL){
					printf("there are no left copies of this book (%s)\n", tempbook->bookName);
				}
				else{
					int d, m, y;
					printf("enter date date in format dd mm yyyy: "); scanf("%d%d%d", &d, &m, &y);
					appendBookTransactions(search, borrowerID, d, m, y, bookTransactions);
					strcpy(search->status, borrowerID);
					FILE* fpo=fopen(bookNotPresentFile, "w");
					if(fpo==NULL) printf("couldnt opened\n");
					while(current!=NULL){
					fprintf(fpo, "%s,%s\n", current->labelNo, current->status);
					current=current->next;
					}
					fclose(fpo);
				}
			}
		}	
	}	
}

int linesBookTransactions(char* bookTransactions){
	int a, b, c, d;
	int lines=0;
	FILE* fp=fopen(bookTransactions, "r");
	char temp1[20], temp2[10];
	if(fp==NULL){
		printf("couldnt opened\n");
	}
	else{
		while(!feof(fp)){
			fscanf(fp, "%15[^,],%8[^,],%d,%d.%d.%d\n", temp1, temp2, &a, &b, &c, &d);
			lines++;
		}
	}
	fclose(fp);
	return lines;
}

void readBorrowed(char* bookTransactions, BORROWED* odunctut){
	int a, b, c, d, i=0;
	FILE* fp=fopen(bookTransactions, "r");
	if(fp==NULL){
		printf("couldnt opened\n");
	}
	else{
		while(!feof(fp)){
			fscanf(fp, "%15[^,],%8[^,],%d,%d.%d.%d\n", odunctut[i].labelNo, odunctut[i].stdID, &a, &b, &c, &d);
			odunctut[i].transactionType=a; odunctut[i].transactionDate.day=b; odunctut[i].transactionDate.month=c; odunctut[i].transactionDate.year=d;
			i++;
		}
	}
	fclose(fp);
}

//her kitap ornegi icin kitap ornege al
void writeToBookCopyeach(char* bookFileName, char* bookNotPresentFile){
	int i;
	char temp[30], quant[5], *underscore="_", *shelf=",RAFTA";
	BOOK* bookhead=readBooksFromFile(bookFileName);
	FILE* fp=fopen(bookNotPresentFile, "w");
	if(fp==NULL) printf("couldnt opened\n");
	BOOK* iter=bookhead;
	
	while(iter!=NULL){
		for(i=0;i<iter->quantity;i++){
			strcpy(temp, iter->ISBN);
			strcat(temp, underscore);
			itoa(i+1, quant, 10);
			strcat(temp, quant);
			strcat(temp, shelf);
			fprintf(fp, "%s\n", temp);
		}
		iter=iter->next;
	}
	fclose(fp);
}

void writebookcopyfromborrowed(char* bookNotPresentFile, BORROWED* odunctut, int numbernPB, char* bookFileName, BOOKCOPY* headnotPresentBook){
	int i, j, counter, typeControl, readedlinescount=0;
	char *comma=",";
	int flag;
	BOOKCOPY* cur;
	BOOKCOPY* temptemp;
	char** readedLines=(char**)malloc(numbernPB*sizeof(char*)); if(readedLines==NULL) printf("allocation error\n");
	for(i=0;i<numbernPB;i++){
		readedLines[i]=(char*)malloc(40*sizeof(char)); 
		if(readedLines[i]==NULL) printf("allocation error\n");
	}
	
	for(i=0;i<numbernPB;i++){
		counter=0;
		for(j=0;j<numbernPB;j++){
			if(strcmp(odunctut[i].labelNo, odunctut[j].labelNo)==0)
			counter=j;
		}
		typeControl=odunctut[counter].transactionType;
		if(typeControl==0){
			temptemp=headnotPresentBook; 
			flag=0;
			while(flag==0){
				if(strcmp(odunctut[counter].labelNo, temptemp->labelNo)==0){
					flag=1;
				}
				cur=temptemp;
				temptemp=temptemp->next;
			}
			strcpy(cur->status, odunctut[counter].stdID);
		}
	}
	
	FILE* fp12=fopen(bookNotPresentFile, "w");
	if(fp12==NULL) printf("couldnt opened\n");
	BOOKCOPY* iteriter=headnotPresentBook;
	while(iteriter!=NULL){
		fprintf(fp12, "%s,%s\n", iteriter->labelNo, iteriter->status);
		iteriter=iteriter->next;
	}
	fclose(fp12);
}

//calculate days
int calculatedays(int d,int m,int y,int d1,int m1,int y1){
	int a=d+(m-1)*30+(y-1)*365;
	int b=d1+(m1-1)*30+(y1-1)*365;
	return a-b;
}

void receivedtoappendBookTra(char* bookTransactions, char* id, int d, int m, int y, BOOKCOPY* copyiter){
	FILE* fp=fopen(bookTransactions, "a");
	if(fp==NULL) printf("couldnt opened\n");
	fprintf(fp, "\n%s,%s,%d,%d.%d.%d", copyiter->labelNo, id, 1, d, m, y);
	fclose(fp);
}

// give back book
void receiveBook(char* stdFileName, char* bookNotPresentFile, char* bookFileName, BORROWED* odunctut2, char* bookTransactions){
	STD* stdhead=readStudentsFromFile(stdFileName);
	STD* temp=stdhead;
	char id[9];
	printf("enter the ID of student who will receive a book\n"); scanf("%s", id);
	while(strlen(id)!=8){
		printf("please enter 8 digit"); scanf("%s", id);
	}
	STD* iter=temp;
	while(iter!=NULL && strcmp(iter->stdID, id)!=0){
		iter=iter->next;
	}
	if(iter==NULL){
		printf("there is no student record with this id (%s)\n", id);
	}
	else{
		printf("%s %s %s found\n", iter->name, iter->surname, iter->stdID);
		char booktoreceive[30];
		printf("which book will be received?"); scanf(" %29[^\n]", booktoreceive);
		BOOK* booknode=readBooksFromFile(bookFileName);
		BOOK* tempbook=booknode;
		while(tempbook!=NULL && strcmp(tempbook->bookName, booktoreceive)!=0){
			tempbook=tempbook->next;
		}
		if(tempbook==NULL){
			printf("there is no such book in database(%s)\n", booktoreceive);
		}
		else{
			BOOKCOPY* headC=readBookCopy(bookNotPresentFile);
			BOOKCOPY* copyiter=headC;
			while(copyiter!=NULL && (strncmp(copyiter->labelNo, tempbook->ISBN, 13)!=0 ||  strcmp(copyiter->status, id)!=0)){
				copyiter=copyiter->next;
			}
			if(copyiter==NULL){
				printf("there is no such record\n");
			} 
			else{
				char* onshelf="RAFTA";
				int d,m,y,i=0,type;
				printf("please enter the date in format dd mm yyyy: "); scanf("%d%d%d", &d,&m,&y);
				type=0;
				while(strcmp(odunctut2[i].labelNo, copyiter->labelNo)!=0 || strcmp(odunctut2[i].stdID, copyiter->status)!=0 || type!=0){
					i++;
				}
				int d1,m1,y1;
				d1=odunctut2[i].transactionDate.day; m1=odunctut2[i].transactionDate.month; y1=odunctut2[i].transactionDate.year;
				int days=calculatedays( d, m, y, d1, m1, y1);
				while(days<0){
					printf("you entered a date from past! please enter again in format dd mm yyyy: "); scanf("%d%d%d", &d,&m,&y);
					days=calculatedays( d, m, y, d1, m1, y1);
				}
				if(days>15){
					printf("you didnt received at right time. Your score has been reduced 10! New score = (%d)\n", iter->score-10);
					iter->score=iter->score-10;
				}
				receivedtoappendBookTra(bookTransactions, id, d, m, y, copyiter);
				strcpy(copyiter->status, onshelf);
				FILE *fpfpfp=fopen(bookNotPresentFile, "w");
				if(fpfpfp==NULL) printf("couldnt opened\n");
				while(headC!=NULL){
					fprintf(fpfpfp, "%s,%s\n", headC->labelNo, headC->status);
					headC=headC->next;
				}
				fclose(fpfpfp);
				writeToStudents(stdhead, stdFileName);
			}
		}
	}
	
}

//write to AUTHORBOOK file
void writetoautbook(AUTHORBOOK* head, char* bookautfileName, int counter){
	int i;
	FILE* fpfpfp=fopen(bookautfileName, "w");
	if(fpfpfp==NULL) printf("couldnt opened\n");
	for(i=0;i<counter;i++){
		fprintf(fpfpfp, "%s,%d\n", head[i].ISBN, head[i].authorID);
	}
	fclose(fpfpfp);
}

// delete book
void deletingBook(char* bookFileName, char* bookautfileName, char* bookNotPresentFile){
	int i;
	char bookname[30];
	printf("enter the name of the book to be delete:"); scanf(" %29[^\n]", bookname);
	BOOK* bookhead=readBooksFromFile(bookFileName);
	BOOK* iterbook=bookhead, *cur, *tempbook, *booknametut;
	while(iterbook!=NULL && strcmp(iterbook->bookName, bookname)!=0){
		tempbook=iterbook;
		iterbook=iterbook->next;
	}
	if(iterbook==NULL){
		printf("this book (%s) is not in database\n", bookname);
	}
	else{
		if(iterbook==bookhead){
			cur=iterbook;
			iterbook=iterbook->next;
			bookhead=iterbook;
			booknametut=cur;
			free(cur);
		}
		else{
			tempbook->next=tempbook->next->next;
			booknametut=iterbook;
			free(iterbook);
		}
		char *deleted="-1";
		BOOKCOPY* copyhead=readBookCopy(bookNotPresentFile);
		BOOKCOPY* copyiter=copyhead;
		while(copyiter!=NULL){
			if(strncmp(copyiter->labelNo,booknametut->ISBN, 13)==0){
				strcpy(copyiter->status, deleted);
			}
			copyiter=copyiter->next;
		}
		int autbooklines=linesofNPB(bookautfileName);
		AUTHORBOOK* bookautdelete=(AUTHORBOOK*)malloc(autbooklines*sizeof(AUTHORBOOK));
		readBookAut(bookautfileName, bookautdelete);
		for(i=0;i<autbooklines;i++){
			if(strcmp(bookautdelete[i].ISBN, booknametut->ISBN)==0){
				bookautdelete[i].authorID=-1;
			}
		}
		writeToBooks(bookhead, bookFileName);
		writetokitapornek(copyhead, bookNotPresentFile);
		writetoautbook(bookautdelete, bookautfileName, autbooklines);
		printf("%s was deleted\n", bookname);
	}
}

void listBooks(char* bookFileName){
	BOOK temp;
	FILE* fp=fopen(bookFileName, "r");
	if(fp==NULL) printf("couldnt opened\n");
	while(!feof(fp)){
		fscanf(fp, "%29[^,],%14[^,],%d\n", temp.bookName, temp.ISBN, &temp.quantity);
		printf("%s (%s) %d\n", temp.bookName, temp.ISBN, temp.quantity);
	}
	fclose(fp);
}

void listSuspendedBooks(char* bookNotPresentFile, char* bookFileName){
		BOOKCOPY* copytemp=readBookCopy(bookNotPresentFile);
		BOOK* booktemp=readBooksFromFile(bookFileName);
		BOOK* head;
		char* cont="RAFTA", *cont1="-1";
		while(copytemp!=NULL){
			if(strcmp(copytemp->status, cont)!=0 && strcmp(copytemp->status, cont1)!=0){
				head=booktemp;
				while(strncmp(copytemp->labelNo, head->ISBN, 13)!=0){
					head=head->next;
				}
				printf("%s %s is not on shelf\n", head->bookName, copytemp->labelNo);
			}
			copytemp=copytemp->next;
		}
}

//read "kitapyazar" file
AUTHORBOOK* readAutBook(char* bookautfileName, AUTHORBOOK* autmatchbook, int autbookmatchline){
	int i;
	FILE *fp=fopen(bookautfileName, "r");
	if(fp==NULL) printf("couldnt opened\n");
	for(i=0;i<autbookmatchline;i++){
		fscanf(fp, "%13[^,],%d\n", autmatchbook[i].ISBN, &autmatchbook[i].authorID);
	}
	return autmatchbook;
}
//------MAIN---------
int main(){
	int cho, sj=0, stu, boo, aut, a_count=0, a_count_1=0, deleted_a_count=0, autbookmatchline, i;
	AUTHOR* aheada=NULL;
	int kk;
	int* deleted_auts=(int*)malloc(sizeof(int));
	STD* head=NULL;
	BOOK* headb=NULL;
	BOOKCOPY* head_bookcopy=NULL;
	char* stdFileName="Ogrenciler.csv";
	char* autFileName="Yazarlar.csv";
	char* bookFileName="Kitaplar.csv";
	char* bookautfileName="KitapYazar.csv";
	char* bookNotPresentFile="KitapOrnek.csv";
	char* bookTransactions="KitapOdunc.csv";
	int aut_book_lines;
	AUTHORBOOK* authorBookArr;
	BOOKCOPY* headnotPresentBook = NULL;
	AUTHORBOOK* autmatchbook;
	FILE* nPB;
	int numbernPB, numbernPB2, numbernPBstd;
	BORROWED *odunctut, *odunctut2, *odunctutstd;
	while(sj==0){
		int ss=0, aa=0, bb=0;
		printf("Choose a Option:\n1-for Students Operations\n2-for Book Operations\n3-for Author Operations\n4-for Exit\n"); scanf("%d", &cho);
		switch(cho){
			case 1: // students
			while(ss==0){
				printf("Choose a option:\n1-for add student\n2-for delete student");
				printf("\n3-for search certain student's data\n4-for list all students");
				printf("\n5-for borrow book\n6-give back book\n7-for back to main menu\n"); scanf("%d", &stu);
				switch(stu){
					case 1: // create & add student
						addStudent(&head, stdFileName);
					break;
					case 2: // delete student
						deleteStudent(&head, stdFileName);
					break;
					case 3: // search certain student
						numbernPBstd=linesBookTransactions(bookTransactions); 
						odunctutstd=(BORROWED*)malloc(numbernPBstd*sizeof(BORROWED));
						readBorrowed(bookTransactions, odunctutstd);	
						searchStudent(head, stdFileName, odunctutstd, numbernPBstd);
					break;
					case 4: // list all students
						listStudent(stdFileName);
					break;
					case 5: // borrow book
						numbernPB=linesBookTransactions(bookTransactions); 
						odunctut=(BORROWED*)malloc(numbernPB*sizeof(BORROWED));	
						writeToBookCopyeach(bookFileName, bookNotPresentFile);
						headnotPresentBook=readBookCopy(bookNotPresentFile);
						readBorrowed(bookTransactions, odunctut);	
						writebookcopyfromborrowed(bookNotPresentFile, odunctut, numbernPB, bookFileName, headnotPresentBook);		
						borrowBook(stdFileName, bookNotPresentFile, headnotPresentBook, bookFileName, numbernPB, bookTransactions, odunctut);
					break;
					case 6: // give back book
						numbernPB2=linesBookTransactions(bookTransactions); 
						odunctut2=(BORROWED*)malloc(numbernPB2*sizeof(BORROWED));
						writeToBookCopyeach(bookFileName, bookNotPresentFile);
						headnotPresentBook=readBookCopy(bookNotPresentFile);
						readBorrowed(bookTransactions, odunctut2);
						writebookcopyfromborrowed(bookNotPresentFile, odunctut2, numbernPB2, bookFileName, headnotPresentBook);
						receiveBook(stdFileName, bookNotPresentFile, bookFileName, odunctut2, bookTransactions);
					break;
					case 7: // exit
						ss=1;
					break;
					default:
						printf("out of range\n");
					break;	
				}
			}
			break;
			case 2: // books
				while(bb==0){
					printf("Choose a option:\n1-for add book\n2-for delete book\n3-for list books");
					printf("\n4-for list suspended books\n5-for back to main menu");
					scanf("%d", &boo);
					switch(boo){
						case 1: // add book
							aut_book_lines=findlinenumber(bookautfileName);
							authorBookArr=(AUTHORBOOK*)malloc(aut_book_lines*sizeof(AUTHORBOOK));
							addBook(&headb, bookFileName, deleted_auts, &aheada, autFileName, bookautfileName, authorBookArr, bookNotPresentFile);
						break;
						case 2: // delete book
							deletingBook(bookFileName, bookautfileName, bookNotPresentFile);
						break;
						case 3: // list all books
							listBooks(bookFileName);
						break;
						case 4: // list books that not present
							listSuspendedBooks(bookNotPresentFile, bookFileName);
						break;
						case 5: // exit
							bb=1;
						break;
						default:
							printf("out of range\n");
						break;
					}
				}
			break;
			case 3: // authors
				while(aa==0){
					printf("Choose a option:\n1-for add author\n2-for delete author");
					printf("\n3-for see authors data\n4-for back to main menu");
					scanf("%d", &aut);
					switch(aut){
						case 1: // add author
							addAuthors(autFileName, &a_count);
						break;	
						case 2: // delete author
							autbookmatchline=linesofNPB(bookautfileName);
							autmatchbook=(AUTHORBOOK*)malloc(autbookmatchline*sizeof(AUTHORBOOK));
							autmatchbook=readAutBook(bookautfileName, autmatchbook, autbookmatchline);
							deleteAuthor(&aheada, autFileName, bookautfileName, autmatchbook, autbookmatchline, bookNotPresentFile);
						break;	
						case 3: //see author's data
							listCertainAut(autFileName, bookautfileName, bookNotPresentFile, bookFileName);
						break;
						case 4: //back to main menu
							aa=1;
						break;	
						default:
							printf("out of range\n");
						break;
					}
				}
			break;
			case 4: // exit
				sj=1;
			break;
			default:
			printf("out of range\n");
			break;	
		}
	}
	return 0;
}
