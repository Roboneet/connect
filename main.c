#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/****************
==================

An FIFO model

==================
*****************/


/****************
* TODO:
*
* encode and decode passwords
* store data into a file and retrive
*
*****************/

enum ACTIONS {QUIT,CREATE, VIEW_ALL, DISPLAY_ONE, SEARCH, CONNECT, LOGIN, LOGOUT = 99};
enum boolean {TRUE,FALSE};


typedef struct user{
	int id;
	char name[20];
	char password[20];
	int no_of_friends;
	struct user** friends;
	struct user* next;
}user;

typedef struct list{
	user* head;
	int size;
	user* end;
}list;



// user roboneet;
list people;
user* active;

char* user__str__(user *u);
user* createUser();
void insertUser(user* u);
void printFriendsList(user u);
void printUserInfo(user u);
void printAllNames();
void deleteUser();
user* searchUserByName(char* name);
user* searchUserById(int id);
void deleteAllUsers();
int authenticate();
void connect();
void logout();

int main(){
	people.head = NULL;
	people.end = NULL;

	/************
	==============
	
	intialising bot

	==============
	************/
	// roboneet.id = 5;
	// strcpy(roboneet.name,"Robo Neet");
	// roboneet.no_of_friends = l.size;
	// roboneet.friends = (user**)malloc(sizeof(user*)*roboneet.no_of_friends);

	int n = 0;
	char s[20],ch;
	printf("\nWelcome to your social network ! ;) \n");
	do{
		
		n = 0;
		printf("\n\n pick a number: \n");
		if(active==NULL){
			printf("1.Create user\n");
		}
		printf("2.View all users\n");
		printf("3.Display a user's info\n");
		printf("4.Search a user\n");
		printf("5.Connect\n");
		if(active==NULL && people.head!= NULL){
			printf("6.Login\n");
		}
		if(active!=NULL){
		printf("99.Logout\n");
		}
		printf("0.QUIT\n");
		
		scanf("%d",&n);
		scanf("%c",&ch);		

		switch(n){

			case CREATE:
				if(active==NULL){
					insertUser(createUser());
				}else{
					printf(":P");
				}
				break;

			case VIEW_ALL:
				printAllNames();
				break;

			case DISPLAY_ONE:
				printf("\nEnter the username\n");
				gets(s);
				if(searchUserByName(s)!=NULL){
					printUserInfo(*searchUserByName(s));
				}else{
					printf("User not found");
				}
				break;

			case SEARCH:
				printf("\nEnter the username\n");
				gets(s);
				if(searchUserByName(s)==NULL){
					printf("User not found");
				}
				else{
					printf("User exists");
				}
				break;

			case CONNECT:
				connect();
				break;

			case LOGIN:
				authenticate();
				break;
			case LOGOUT:
				logout();
				break;
			case QUIT:
				printf("Bye bye !\n");
				break;
			default:
				printf("Invalid Key");

		}

		do{scanf("%c",&ch);}while(ch!='\n');

	}while(n);


	deleteAllUsers();
	return 0;
}

/******************
===================

function to create a user

===================
*******************/

user* createUser(){
	
	user* u;
	u = (user*)malloc(sizeof(user));
	if(people.end!=NULL){
		u->id = people.end->id + 1;
	}
	else{
		u->id = 7;
	}
	printf("Enter the username");
	gets(u->name);
	printf("Enter password");
	gets(u->password);
	u->no_of_friends = 0;
	u->friends = (user**)malloc(sizeof(user*)*u->no_of_friends);
	u->next = NULL;

	
	return u;
}

/*****************
==================

function to insert a user into the end of the list

==================
*****************/


void insertUser(user* u){
	
	if(people.end == NULL){
		/***
		=============

		List is empty
		
		=============
		***/

		people.head = u;
		people.end = u;
		people.size = 1;
	}else{
		
		people.end->next = u;
		people.end = u;
		people.size++;
		printf("\nsuccesful Insertion \n");
		
	}


}

void printFriendsList(user u){
	int i;
	printf("Your list of friends :\n");
	for(i= 0; i< u.no_of_friends;i++){
		printf("%s\n",user__str__(u.friends[i]));
	}
}

void printUserInfo(user u){
	printf("User id : %d\n",u.id);
	printf("Name: %s\n",u.name);
	printf("Number of friends: %d\n",u.no_of_friends);
	if(u.no_of_friends>0){
	printFriendsList(u);
	}
	
}

char* user__str__(user *u){
	return u->name;
}

void printAllNames(){
	user* curr = people.head;
	
	if(curr == NULL){
		printf("No people here yet");
	}

	while(curr!=NULL){
		printf("%s\n",user__str__(curr));
		curr= curr->next;	
	}
}

void deleteUser(char* name){
	user* temp = people.head;
	user* prev = NULL;
	if(temp == NULL){
		return;
	}
	
	while(temp!=NULL){

		if(strcmp(temp->name,name)){
			break;
		}
		prev = temp;
		temp = temp->next;

	}


	if(temp == people.end){
		people.end = NULL;
	}
	if(prev!=NULL){
	prev->next = temp->next;
	}else{
		people.head = people.head->next;
	}
	free(temp);
}

user* searchUserByName(char* name){
	user* curr = people.head;
	while(curr!=NULL){
		
		if(strcmp(curr->name,name)==TRUE){
			return curr;
		}

		curr = curr->next;

	}


	return NULL;
}

user* searchUserById(int id){
	user *curr = people.head;
	while(curr!=NULL){
		
		if(curr->id == id){
			return curr;
		}

		curr = curr->next;

	}

	return NULL;
}

void deleteAllUsers(){
	user* curr = people.head;
	user* temp;
	while(curr!=NULL){
		temp = curr;
		curr = curr->next;
		free(temp);
	}
	people.head = NULL;
	people.end = NULL;
}

int authenticate(){
	char s[20],p[20];

	printf("Enter your username");
	gets(s);

	printf("Enter your password");
	gets(p);

	user* u = searchUserByName(s);
	if(u!=NULL && strcmp(p,u->password)==TRUE){
		active = u;
		printf("Succesfully authenticated\n");
		return TRUE;
	}
	
	return FALSE;
}

void connect(){
	if(active == NULL && authenticate() == FALSE){
			return;
	}
	char s[20];
	printf("Enter your friend's username\n");
	gets(s);
	user* u = searchUserByName(s);
	if(u==NULL){
		printf("Friend not found");
	}
	else{
		active->no_of_friends += 1;
		active->friends = (user**)realloc(active->friends,sizeof(user*)*(active->no_of_friends));
		active->friends[active->no_of_friends-1] = u;
		printf("Succesfully added to friends list\n");
		printFriendsList(*active);
	}



}

void logout(){
	active = NULL;
}
