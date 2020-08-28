#include<iostream>
#include<stdlib.h>
#include <fstream>

using namespace std;

long long Number_Account = 0; // for the number of accounts

class account {
	friend class customer;
private:
	long long money;
	account * pnext;
	char * name;
	char * sur_name;
	long long id_number;
	long long date_of_birth;
	char gender;

public:
	account(long long val, account * next, char * F, char * L, long long ID, long long DB, char  g) {
		money = val;
		pnext = next;
		name = F;
		sur_name = L;
		id_number = ID;
		date_of_birth = DB;
		gender = g;
		Number_Account++;
	}

	account(long long val, char * F, char * L, long long ID, long long DB, char  g) {
		money = val;
		pnext = NULL;
		name = F;
		sur_name = L;
		id_number = ID;
		date_of_birth = DB;
		gender = g;
		Number_Account++;
	}

	long long getmoney(void) {
		return money;
	}

	account * getNext(void) {
		return pnext;
	}

	void setmoney(long long data) {
		money = data;
	}

	void setNext(account * p) {
		pnext = p;
	}

};

class customer {
private:
	account * head;
	account * tail;

public:
	customer(void);
	customer(long long a, char *b, char * c, long long d, long long e, char  f);
	~customer(void);
	void traverse_print_1_acc(long long a);
	void traverse_print_all_accs();
	void add_account(long long a, char *b, char * c, long long d, long long e, char  f);
	bool existence(long long a);
	void add_acc_4_already_customer(long long a, long long b);
	void delete_one_customer(long long a);
	void delete_all_accounts();
	void depos_inac(long long a, long long b);
	void withdraw(long long a, long long b);
	void withdraw_and_deops(long long a, long long b, long long c);
};

customer::customer() {
	head = tail = NULL;
}

customer::customer(long long val, char *f, char * l, long long id, long long bd, char  g) {
	head = new account(val, f, l, id, bd, g);
	tail = head;
}

void customer::traverse_print_1_acc(long long id) {
	account *p = head;
	int count = 0; // "number of this account"
	if (p == NULL) {
		cout << "Theres no Account !!!" << endl;
		return;
	}

	while (p != NULL) {
		if (p->id_number == id) {
			count++;
			cout << "number of account for this ID is :" << count << endl;
			cout << "name :" << p->name << " " << p->sur_name << " id : " << p->id_number << " money : " << p->money << " " << p->gender << " ";

			cout << endl;
		}
		p = p->pnext;
	}
	cout << endl;
}

void customer::traverse_print_all_accs()
{
	account *p = head;
	int count = 0;
	if (p == NULL) {
		cout << "There is no Account !!!" << std::endl;
		return;
	}

	while (p != NULL) {
		count++;
		cout << "name :" << p->name << " " << p->sur_name << " id : " << p->id_number << " number of account : " << count << " money : " << p->money << " gender : " << p->gender << " ";
		p = p->pnext;
		cout << endl;
	}
	cout << endl;
}

bool customer::existence(long long id)
{
	account *p = head;
	if (p == NULL)
	{
		cout << "this ID didn't find for any account" << std::endl;
		return false;
	}

	while (p != NULL)
	{
		if (p->id_number == id)
			return true;
		p = p->pnext;
	}
	return false;
	cout << endl;
}
void customer::add_account(long long val, char *f, char * l, long long id, long long bd, char  g)
{
	if (head == NULL)
	{
		head = new account(val, f, l, id, bd, g);
		tail = head;
		return;
	}
	tail->pnext = new account(val, f, l, id, bd, g);
	tail = tail->pnext;
}

void customer::add_acc_4_already_customer(long long val, long long id)
{
	account * p = head;
	while (p != NULL)
	{
		if (p->id_number == id)
		{
			add_account(val, p->name, p->sur_name, p->id_number, p->date_of_birth, p->gender);
			break;
		}
		p = p->pnext;
	}
}

customer::~customer()
{
	account *p;
	while (head)
	{
		p = head->pnext;
		delete head;
		head = p;
	}
}
void customer::delete_one_customer(long long id) {
	account * p = head;
	account * temp;
	account * temp_bef = p;
	while (p != NULL) {
		if (head->id_number == id) {
			temp = head;
			head = head->pnext;
		    delete temp;
		}
		if (p->id_number == id) {
			temp = p;
			delete temp;
		}
		p = p->pnext;
		temp_bef = p;
	}
}
void customer::delete_all_accounts() {
	account *p;
	while (head)
	{
		p = head->pnext;
		delete head;
		head = p;
	}
}
void customer::depos_inac(long long val, long long id) {
	account * p = head;
	while (p != NULL) {
		if (p->id_number == id) {
			p->money += val;
		    break;
		}
		p = p->pnext;
	}
}
void customer::withdraw(long long val, long long id) {
	account * p = head;
	while (p != NULL) {
		if (p->id_number == id) {
			p->money -= val;
			break;
		}
		p = p->pnext;
	}
}
void customer::withdraw_and_deops(long long val, long long id, long long id2) {
	account * p = head;
	while (p != NULL) {
		if (p->id_number == id)
			p->money -= val;
		p = p->pnext;
		if (p->id_number == id2) {
			p->money += val;
			break;
		}
	}
}


int main()
{
	ifstream infile("inputaccount.txt");
	if (infile.fail()) {
		cerr << "error" << endl;
	}
	char *name1 = new char[100];
	char *sur_name1 = new char[100];
	
	int in = 0;
	customer acc;

	/*int i = 0;
	while (infile >> name1 >> sur_name1 >> ID_NUMBER >> birth_date >> g >> money)
		i++;*/
	while (true) {

		cout << "1  : Add Account " << endl;
		cout << "2  : Add Extra Account for An existing Account" << endl;
		cout << "3  : Delete Account "<< endl;
		cout << "4  : Delete All Account " << endl;
		cout << "5  : Deposit into account " << endl;
		cout << "6  : Withdraw money from the account " << endl;
		cout << "7  : Display Account " << endl;
		cout << "8  : Display All Account " << endl;
		cout << "9  : withdraw from an account and add to another " << endl;
		cout << "10 : EXIT " << endl;
		cout << "Other Numbers : back to menu " << endl;
		cout << endl;

		cout << "so what do you want to do ? ";
		cin >> in;

		switch (in) {
		case 1:
			long long money;
			long long ID_NUMBER;
			long long birth_date;
			char g;

			cout << endl << "Enter  your first name :";
			cin >> name1;
			cout << endl;
			cout << "Enter your last name :";
			cin >> sur_name1;
			cout << endl;
			cout << "Enter your ID number:";
			cin >> ID_NUMBER;
			cout << endl;
			cout << "Enter your birth date :";
			cin >> birth_date;
			cout << endl;
			cout << "what's your sexuality? (m foe man and f for female ) :";
			cin >> g;
			cout << endl;
			cout << "Enter the amount of money you want to put to your account :";
			cin >> money;
			cout << endl;

			acc.add_account(money, name1, sur_name1, ID_NUMBER, birth_date, g);
			cout << "adding account fortunately was successful!!" << endl;
			break;

		case 2:
			long long a;
			cout << "Please Enter your ID number for the account :";
			cin >> a;

			if (acc.existence(a) == true)
			{
				long long money;      // the amont of money you want to create your account with 
				cout << "Enter the amount of money you want to create the account to start with: ";
				cin >> money;
				acc.add_acc_4_already_customer(money, a);
				cout << "adding account fortunately was successful!!" << endl;
			}
			else {
				cout << "such account did't found!" << endl;
			}
			break;
		case 3 :
			long long w;
			cout << "Please Enter ID account :";
			cin >> w;
			if (acc.existence(w) == true)
			{
				acc.delete_one_customer(w);
				cout << "delete Account of Customer this ID was successful" << endl;
			}
			else {
				cout << "such account didn't found!" << endl;
			}
			break;
		case 4 :
			acc.delete_all_accounts();
			cout << "all accounts were safely removed!!" << endl;

		case 5:
			long long l;
			cout << "enter your ID number for the account :";
			cin >> l;
			if (acc.existence(l) == true) {
				long long val;
				cout << "Enter the amount of money you want to add to your account:";
				cin >> val;
				acc.depos_inac(val, l);
			}
			else {
				cout << "such account did't found";
			}
			break;
		case 6:
			long long p;
			cout << "Please Enter ID account :";
			cin >> p;
			if (acc.existence(p) == true) {
				long long val;
				cout << "Enter the amount of money you want to withdraw from your account:";
				cin >> val;
				acc.withdraw(val, p);
			}
			else {
				cout << "such account did't found" << endl;
			}
			break;
		case  7:
			long long b;
			cout <<" Enter ID number for the account : ";
			cin >> b;
			cout << endl;
			acc.traverse_print_1_acc(b);
			break;

		case  8:
			acc.traverse_print_all_accs();
			break;
		case 9:
			long long s;
			long long s2;
			cout << " Enter ID number for the origin account : ";
			cin >> s;
			cout << " Enter ID number for the receiver account : ";
			cin >> s2;
			if (acc.existence(s) == true && acc.existence(s2) == true) {
				long long val;
				cout << "Enter the amount of money you want to withdraw from the origin account:";
				cin >> val;
				acc.withdraw_and_deops(val, s, s2);
				cout << "the money transfering was successful!!" << endl;
			}
			break;
		case  10:
			exit(EXIT_FAILURE); // exit(1)
		}
	}
	infile.close();
	return 0;
}
