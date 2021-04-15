#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
	belum selesai:
	1. 
*/

int total_games=0;
int increment=0;

void view_games();

void cls(){
	for(int i=0; i<45; i++) printf("\n");
}

struct review{
	int id;
	char user[30];
	char title[30];
	char content[50];
	char recommend[10];
	struct review *left;
	struct review *right;
}*review_root = NULL;

struct review *createNewReviewNode(int id, char user[], char title[], char content[], char recommend[]){
	struct review *newNode = (struct review *)malloc(sizeof(struct review));
	newNode->id = id;
	strcpy(newNode->user, user);
	strcpy(newNode->title, title);
	strcpy(newNode->content, content);
	strcpy(newNode->recommend, recommend);
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

struct review *insert_review(struct review *node, int id, char user[], char title[], char content[], char recommend[]){
	if(node == NULL){
		node = createNewReviewNode(id, user, title, content, recommend);
	}else if(node->id > id){
		node->left = insert_review(node->left, id, user, title, content, recommend);
	}else if(node->id < id){
		node->right = insert_review(node->right, id, user, title, content, recommend);
	}
}

void view_in_order_review(struct review *node, char title[]){
	if(node != NULL){
		view_in_order_review(node->left, title);
		if(strcmpi(node->title, title) == 0){
			printf("| %-4d | %-26s | %-50s | %-12s |\n", node->id, node->title, node->content, node->recommend);
		}
		view_in_order_review(node->right, title);		
	}
}

struct games{
	char title[30];
	char description[50];
	int price;
	struct games *left;
	struct games *right;
}*root = NULL;

struct games *createNewSongNode(char title[], char description[], int price){
	struct games *newNode = (struct games *)malloc(sizeof(struct games));
	strcpy(newNode->title, title);
	strcpy(newNode->description, description);
	newNode->price = price;
	newNode->left = NULL;
	newNode->right = NULL;
	total_games++;
	return newNode;
}

struct games *insert_games(struct games *node, char title[], char description[], int price){
	if(node == NULL){
		node = createNewSongNode(title, description, price);
	}else if(strcmp(title, node->title) < 0){
		node->left = insert_games(node->left, title, description, price);
	}else if(strcmp(title, node->title) > 0){
		node->right = insert_games(node->right, title, description, price);
	}
}

struct games *delete_games(struct games *node, char title[]){
	if(node == NULL){
		return NULL;
	} else if(strcmp(title, node->title) < 0){
		node->left = delete_games(node->left, title);
	} else if(strcmp(title, node->title) > 0){
		node->right = delete_games(node->right, title);
	} else {
		if(node->left == NULL && node->right == NULL){
			node = NULL;
			free(node);
		} else if(node->left == NULL || node->right == NULL){
			struct games *temp;
			if(node->left != NULL){
				temp = node->left;
			} else{
				temp = node->right;
			}
			node = temp;
		} else if(node->left != NULL && node->right != NULL){
			struct games *temp = node->left;
			while(temp->right != NULL){
				temp = temp->right;
			}
			strcpy(node->title, temp->title);
			strcpy(node->description, temp->description);
			node->price = temp->price;
			node->left = delete_games(node->left, title);
		}
	}
}

void view_in_order_games(struct games *node){
	if(node != NULL){
		view_in_order_games(node->left);
		increment++;
		printf("| %-3d | %-26s | %-50s | %-5d |\n", increment, node->title, node->description, node->price);
		view_in_order_games(node->right);		
	}
}

struct user{
	char name[30];
	char email[50];
	char password[30];
	int age;
	struct user *next;
	struct user *prev;
}*user_head = NULL, *user_tail = NULL;


void push_head_user(char name[], char email[], char password[], int age){
	struct user *curr = (struct user *)malloc(sizeof(struct user));
	
	strcpy(curr->name, name);
	strcpy(curr->email, email);
	strcpy(curr->password, password);
	curr->age = age;
	
	curr->next = NULL;
	if(user_head == NULL){
		user_head = user_tail = curr;
		user_head->prev = NULL;
	}
	else {
		curr->next = user_head;
		user_head->prev = curr;
		user_head = curr;
	}
}

int validate_email(char n[]){
	struct user *curr = user_head;
	if(user_head != NULL){
		if(strcmp(user_head->email, n) == 0){
			return 1;
		}
		else if(strcmp(user_tail->email, n) == 0){
			return 1;	
		}
		else {
			while(curr->next != NULL){
				if(strcmp(curr->next->email, n) == 0){
					return 1;
				}
				curr = curr->next;
			}
		}
	}
	return 0;
}

int validate_email_pass(char n[], char pass[]){
	struct user *curr = user_head;
	if(user_head != NULL){
		if(strcmp(user_head->email, n) == 0 && strcmp(user_head->password, pass) == 0){
			return 1;
		}
		else if(strcmp(user_tail->email, n) == 0 && strcmp(user_head->password, pass) == 0){
			return 1;	
		}
		else {
			while(curr->next != NULL){
				if(strcmp(curr->next->email, n) == 0 && strcmp(user_head->password, pass) == 0){
					return 1;
				}
				curr = curr->next;
			}
		}
	}
	return 0;
}

void print_admin_page(){
	printf("Hi, Admin\n");
	printf("=========\n");
	printf("1. Add Game\n");
	printf("2. View Game\n");
	printf("3. Update Game\n");
	printf("4. Delete Game\n");
	printf("5. View Game Review\n");
	printf("6. Logout\n");
	printf("Choose >> ");
}

void add_game(){
	char title[50], description[55];
	int price;
	do{
		printf("Insert Title [5 - 25 Characters]: ");
		scanf("%[^\n]", title); getchar();
	}while(strlen(title) < 5 || strlen(title) > 25);
	do{
		printf("Insert Description [5 - 50 Characters]: ");
		scanf("%[^\n]", description); getchar();
	}while(strlen(description) < 5 || strlen(description) > 50);
	do{
		printf("Insert Price [$1 - $999]: ");
		scanf("%d", &price); getchar();
	}while(price < 1 || price > 999);
	
	root = insert_games(root, title, description, price);
}

void view_games(){
	printf("=================================================================================================\n");
	printf("| %-3s | %-26s | %-50s | %-5s |\n", "No", "Title", "Description", "Price");
	printf("=================================================================================================\n");
	increment=0;
	view_in_order_games(root);
	printf("=================================================================================================\n");	
}

void update_game_get_name(struct games *node, int index, char description[], int price){
	if(node != NULL){
		update_game_get_name(node->left, index, description, price);
		increment++;
		if(increment==index){
			root = delete_games(root, node->title);
			root = insert_games(root, node->title, description, price);
		}
		update_game_get_name(node->right, index, description, price);		
	}
}

void update_game(){
	char description[55];
	int option=0, price=0;
	view_games();
	do{
		printf("Choose game [1-%d]: ", total_games);
		scanf("%d", &option); getchar();
	}while(option < 1 || option > total_games);
	do{
		printf("Insert New Description [5 - 50 Characters]: ");
		scanf("%[^\n]", description); getchar();
	}while(strlen(description) < 5 || strlen(description) > 50);
	do{
		printf("Insert New Price [$1 - $999]: ");
		scanf("%d", &price); getchar();
	}while(price < 1 || price > 999);
	
	// update based on index inputed
	increment=0;
	total_games--;
	update_game_get_name(root, option, description, price);
}

void delete_game_get_name(struct games *node, int index){
	if(node != NULL){
		delete_game_get_name(node->left, index);
		increment++;
		if(increment==index) root = delete_games(root, node->title);
		delete_game_get_name(node->right, index);		
	}
}

void delete_game_menu(){
	int option=0;
	increment=0;
	view_games();
	do{
		printf("Choose game [1-%d]: ", total_games);
		scanf("%d", &option); getchar();
	}while(option < 1 || option > total_games);
	
	// delete game
	increment=0;
	delete_game_get_name(root, option);
}

void view_game_review_get_name(struct games *node, int index){
	if(node != NULL){
		view_game_review_get_name(node->left, index);
		increment++;
		if(increment == index) {
			printf("=========================================================================================================\n");
			printf("| %-4s | %-26s | %-50s | %-12s |\n", "id", "Reviewer Name", "Content", "Recommended");
			printf("=========================================================================================================\n");
			view_in_order_review(review_root, node->title);
			printf("=========================================================================================================\n");
		}
		view_game_review_get_name(node->right, index);		
	}
}

void view_game_review(){
	int option=0;
	view_games();
	do{
		printf("Choose game [1-%d]: ", total_games);
		scanf("%d", &option); getchar();
	}while(option < 1 || option > total_games);
	
	increment=0;
	view_game_review_get_name(root, option);
}

void admin_page(){
	int menu=0;
	do{
		cls();
		print_admin_page();
		scanf("%d", &menu); getchar();
		if(menu==1) add_game();
		else if(menu==2) view_games();
		else if(menu==3) update_game();
		else if(menu==4) delete_game_menu();
		else if(menu==5) view_game_review();
		else if(menu==6) break;
		system("pause");
	}while(1);
}

void create_review_get_name(struct review *node, int index, char name[], char content[], char recommend[]){
	if(node != NULL){
		create_review_get_name(node->left, index, name, content, recommend);
		increment++;
		if(increment == index) {
			int random_number = (rand()%9000)+1000;
			insert_review(node, random_number, name, node->title, content, recommend);
		}
		create_review_get_name(node->right, index, name, content, recommend);		
	}
}

void create_review(char name[]){
	char review[55];
	char recommend[20];
	int option=0;
	view_games();
	do{
		printf("Choose game [1-%d]: ", total_games);
		scanf("%d", &option); getchar();
	}while(option < 1 || option > total_games);
	do{
		printf("Insert Review Content [5 - 50 Characters]: ");
		scanf("%[^\n]", review); getchar();
	}while(strlen(review) < 5 || strlen(review) > 50);
	do{
		printf("Recommended: [Yes | No] [Case Sensitive]: ");
		scanf("%[^\n]", recommend); getchar();
		if(strcmp(recommend, "Yes") == 0 || strcmp(recommend, "No") == 0) break;
	}while(1);

	// insert user review
	increment=0;
	create_review_get_name(review_root, option, name, review, recommend);
}

void print_user_page(char name[]){
	printf("Hi, %s\n", name);
	printf("==========\n");
	printf("1. View Games\n");
	printf("2. Create a Review\n");
	printf("3. View Game Reviews\n");
	printf("4. Logout\n");
	printf("Choose >> ");
}

void user_page(char name[]){
	int menu=0;
	do{
		cls();
		print_user_page(name);
		scanf("%d", &menu); getchar();
		if(menu==1) view_games();
		else if(menu==2) create_review(name);
		else if(menu==3) view_game_review();
		else if(menu==4) break;
		system("pause");
	}while(1);
}

void print_menu_login(){
	printf("===================\n");
	printf("|      Login      |\n");
	printf("===================\n");
}

void login_page(){
	int menu=0;
	char email[50], password[32];
	cls();
	print_menu_login();
	do{
		printf("Email: ");
		scanf("%[^\n]", email); getchar();
	}while(strlen(email) <= 0);
	do{
		printf("Password: ");
		scanf("%[^\n]", password); getchar();
	}while(strlen(password) <= 0);
	if(strcmp(email, "admin") == 0 && strcmp(password, "admin") == 0)
		admin_page();
	else if(validate_email_pass(email, password)) 
		user_page(email);
}

int check_email(char email[]){
	int i=strlen(email);
	if(email[i-8] == '@' ) return 0;
	if(email[i-7] == 'm' ) return 0;
	if(email[i-6] == 'a' ) return 0;
	if(email[i-5] == 'i' ) return 0;
	if(email[i-4] == 'l' ) return 0;
	if(email[i-3] == '.' ) return 0;
	if(email[i-2] == 'c' ) return 0;
	if(email[i-1] == 'o' ) return 0;
	if(email[i-0] == 'm' ) return 0;
	return 1;
}

void register_page(){
	int menu=0, age=0;
	char name[50], email[50], password[32];
	cls();
	do{
		printf("Insert Name [5 - 25 characters]: ");
		scanf("%[^\n]", name); getchar();
	}while(strlen(name) < 5 || strlen(name) > 25 );
	do{
		printf("Insert Email [Unique | 10 - 25 characters | must ends with @gmail.com | must not start with '@' or '.']: ");
		scanf("%[^\n]", email); getchar();
		if(strlen(email) >= 10 && strlen(email) <= 25 && email[0] != '.' && email[0] != '@' && check_email(email) == 1){
			if(!validate_email(email)) break;
		}
	}while(1);
	do{
		printf("Insert Password [5-25 characters]: ");
		scanf("%[^\n]", password); getchar();
	}while(strlen(password) < 5 || strlen(password) > 25);
	do{
		printf("Insert Age [10 - 100]: ");
		scanf("%d", &age); getchar();
	}while(age < 10 || age > 100);
	
	push_head_user(name, email, password, age);
}

void main_logo(){
	printf("=========================================================================================\n");
	printf("|  #####     #    #     ## #######   #       #       ####### #     # ### ####### #     #|\n");
	printf("| #     #   # #   ##   # # #         #       #       #       #     #  #  #       #  #  #|\n");
	printf("| #        #   #  # # #  # #         #       #       #       #     #  #  #       #  #  #|\n");
	printf("| #   ### #     # #  #   # #####     #       #       #####   #     #  #  #####   #  #  #|\n");
	printf("| #     # ####### #      # #         #       #       #        #   #   #  #       #  #  #|\n");
	printf("| #     # #     # #      # #         #       #       #         # #    #  #       #  #  #|\n");
	printf("|  #####  #     # #      # #######   ####### ####### #######    #    ### #######  ## ## |\n");
	printf("=========================================================================================\n");
}

void print_menu(){
	main_logo();
	printf("1. Login\n");
	printf("2. Register\n");
	printf("3. Exit\n");
	printf("Choose >> ");
}

void program_first_run(){
	char name[30], description[50];
	
	strcpy(name, "Among Us");
	strcpy(description, "Teach you how to lie :)");
	root = insert_games(root, name, description, 59);
	
	strcpy(name, "God of War");
	strcpy(description, "Experience Kratos saying boy in the entire game");
	root = insert_games(root, name, description, 149);
	
	strcpy(name, "Grand Theft Auto V");
	strcpy(description, "Teach you how to be a good guy");
	root = insert_games(root, name, description, 249);
	
	strcpy(name, "The Witcher 3");
	strcpy(description, "Featuring Geralt, lover of Yennefer");
	root = insert_games(root, name, description, 299);
	
	strcpy(name, "Red Dead Redemption 2");
	strcpy(description, "Winner of over 175 Game of the Year Awards");
	root = insert_games(root, name, description, 399);
	
	strcpy(name, "The Last of Us Part II");
	strcpy(description, "Help Ellie find her redemption");
	root = insert_games(root, name, description, 199);
}

int main(){
	srand(time(NULL));
	
	program_first_run();
	view_games();
	int menu=0;
	do{
		cls();
		print_menu();
		scanf("%d", &menu); getchar();
		if(menu==1) login_page();
		else if(menu==2) register_page();
		else if(menu==3) break;
		system("pause");
	}while(1);
	return 0;
}
