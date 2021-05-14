//includes
#include <iostream>
#include <mysql.h>
#include <string>
#include <vector>
#include <Windows.h>
#include <sstream>
//end includes

// Global Variables
MYSQL* conn;
MYSQL_RES* res;
MYSQL_ROW row;
int qstate;
// end Global Variables
using namespace std;

class db_response
{
public:
	static void ConnectionFunction()
	{
		conn = mysql_init(0);
		if (conn)
		{
			std::cout << "Sucessfully Connected to Database !" << std::endl;
			Sleep(1000);
		}
		else std::cout << "Error : " << mysql_errno(conn) << std::endl;
		system("cls");
		conn = mysql_real_connect(conn, "localhost", "root", "", "accounts", 0, NULL, 0);
		if (conn)
		{
			std::cout << "Sucessfully connected 'accounts'" << std::endl;
			Sleep(1000);
		}
		else std::cout << "ERROR : " << mysql_errno(conn) << std::endl;
	}
};

//************** --- Functions ---**********************
void searchApp();
void seeAll();
//*********End Functions
void searchApp()
{
	system("PAUSE");
	std::string app_seach, app_query("select application from accounts_data");
	const char* qp = app_query.c_str();
	std::vector <std::string> apps(0);
	qstate = mysql_query(conn, qp);
	if (!qstate)
	{
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			apps.push_back(row[0]);
		}
	}
	else
	{
		std::cout << "Error : " << mysql_errno(conn) << std::endl;
		system("PAUSE");
	}
	std::cout << "Application : ";
	std::cin >> app_seach;
	bool found(false);
	for (int i = 0; i < apps.size(); i++)
	{
		if (app_seach == apps[i])
		{
			found = true;
			break;
		}
		else
		{
			found = false;
		}
	}
	if (found)
	{
		std::string qm = "select * from accounts_data where application = '" + app_seach + "'";
		const char* pm = qm.c_str();
		qstate = mysql_query(conn, pm);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				printf("| %-10s | %-10s | %-10s | %-10s |\n", "Application", "email", "username", "password");
				printf("| %-10s | %-10s | %-10s | %-10s |\n", row[4], row[3], row[1], row[2]);
			}
			system("PAUSE");
		}
		else
		{
			std::cout << "ERROR : " << mysql_errno(conn) << std::endl;
			system("PAUSE");
		}
	}
}

void seeAll()
{
	system("cls");
	printf("| %-10s | %-10s | %-10s | %-10s |\n", "Application", "email", "username", "password");
	std::string qy = "select * from accounts_data";
	const char* qo = qy.c_str();
	qstate = mysql_query(conn, qo);
	if (!qstate)
	{
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			printf("| %-10s | %-10s | %-10s | %-10s |\n", row[4], row[3], row[1], row[2]);
		}
		system("PAUSE");
	}
}

int main()
{
	system("title Accounts Management System");
	db_response::ConnectionFunction();
	system("cls");
	// Local Var
	std::string username_real, password_real, id_real;
	//End Local Var

	std::string username, password, pass, id;
	bool notInDb(true), running(false);
	std::vector <std::string> usernames(0);
	std::vector <std::string> ids(0);
	std::cout << "Login :" << std::endl;
	std::cout << "Username:";
	std::cin >> username;
	std::cout << "Password :";
	std::cin >> password;
	std::string run_query("select * from users");
	const char* q = run_query.c_str();
	qstate = mysql_query(conn, q);
	if (!qstate)
	{
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			ids.push_back(row[0]);
			usernames.push_back(row[1]);
		}
	}
	else std::cout << "ERROR : Database Execution Query : " << mysql_errno(conn) << std::endl;
	for (int i = 0; i < usernames.size(); i++)
	{
		if (username != usernames[i])
		{
			notInDb = true;
		}
		else
		{
			notInDb = false;
			id = ids[i];
			break;
		}
	}
	if (!notInDb)
	{
		std::string find_query("select * from users where id =" + id);
		const char* qu = find_query.c_str();
		qstate = mysql_query(conn, qu);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);
			pass = row[2];
			if (password == pass)
			{
				std::cout << "Sucessfully Connected !" << std::endl;
				Sleep(1000);
				username_real = row[1];
				id_real = row[0];
				password_real[2];
				running = true;
			}
			else
			{
				std::cout << "Password Does Not Match !" << std::endl;
				system("PAUSE");
				running = false;
			}
		}
		else std::cout << "Error : " << mysql_errno(conn) << std::endl;
	}
	else
	{
		std::cout << "This Username Does Not Existe !" << std::endl;
		system("PAUSE");
	}
	while (running)
	{
		system("cls");
		std::string command;
		std::cout << "Hello " << username_real << std::endl;
		std::cout << "--- Main Menue ---" << std::endl;
		std::cout << "1. Add Account Data" << std::endl;
		std::cout << "2. See all accounts " << std::endl;
		std::cout << "3. Search an account" << std::endl;
		std::cout << "4. Add Accounts" << std::endl;
		std::cout << "5. Modify An account data" << std::endl;
		std::cout << "6. Exit" << std::endl;
		std::cout << "Your Comand :";
		std::cin >> command;
		if (command == "1")
		{
			std::string email, app;
			system("cls");
			std::cout << "username :(if no write NEON):";
			std::cin >> username;
			std::cout << "Email :";
			std::cin >> email;
			std::cout << "Application :";
			std::cin >> app;
			std::cout << "Password :";
			std::cin >> pass;
			system("cls");
			std::cout << "Adding Data..." << std::endl;
			std::string newAcc_qu = "insert into accounts_data (username, password, email,application) values ('" + username + "','" + pass + "','" + email + "','" + app + "')";
			const char* qi = newAcc_qu.c_str();
			qstate = mysql_query(conn, qi);
			if (!qstate)
			{
				std::cout << "Account Successfully added !" << std::endl;
				system("PAUSE");
			}
			else
			{
				std::cout << "Execution in database error : " << mysql_errno(conn) << std::endl;
				system("PAUSE");
			}
		}
		if (command == "2")
		{
			seeAll();
		}
		if (command == "3")
		{
			searchApp();
		}
		if (command == "4")
		{
			system("cls");
			bool exist(false);
			std::cout << "Add Account" << std::endl;
			std::string user, passd;
			std::cout << "Username :";
			std::cin >> user;
			std::cout << "password : ";
			std::cin >> passd;
			std::cout << "Verification of the username Existance" << std::endl;
			for (int i = 0; i < usernames.size(); i++)
			{
				if (user == usernames[i])
				{
					exist = true;
					break;
				}
				else
				{
					exist = false;
				}
			}
			if (!exist)
			{
				system("CLS");
				std::string newUsr = "insert into users (username, password) values ('" + user + "','" + passd+"')";
				const char* qu = newUsr.c_str();
				qstate = mysql_query(conn, qu);
				if (!qstate)
				{
					std::cout << "Username " + user + "Have sucessfully been added" << std::endl;
					Sleep(5000);
					system("cls");
					usernames.push_back(user);
				}
				else
				{
					std::cout << "ERROR : " << mysql_errno(conn) << std::endl;
				}
			}
			else
			{
				std::cout << "Username Already Exsit" << std::endl;
				system("PAUSE");
			}
		}
		if (command == "5")
		{
			std::string app, id;
			system("cls");
			std::cout << "Edit Acount Infromation" << std::endl;
			seeAll();
			std::cout << "Application :";
			std::cin >> app;
			std::cout << "Processing..." << std::endl;
			std::string app_query("select * from accounts_data where application ='"+app+"'");
			const char* qo = app_query.c_str();
			qstate = mysql_query(conn, qo);
			std::string newUser, newPass, newEmail, usrBc, passBc,emailBc, changes("/nx");
			bool pass(false);
			if (!qstate)
			{
				res = mysql_store_result(conn);
				system("cls");
				while (row = mysql_fetch_row(res))
				{
					printf("| %-10s | %-10s | %-10s | %-10s |\n", "Application", "email", "username", "password");
					printf("| %-10s | %-10s | %-10s | %-10s |\n", row[4], row[3], row[1], row[2]);
					app = row[4];
					usrBc = row[1];
					passBc = row[2];
					emailBc = row[3];
					id = row[0];
					pass = 1;
				}
			}
			else std::cout << "Error Fetching Data : " << mysql_errno(conn) << std::endl;
			if (pass)
			{
				std::cout << "-------------------------------------------------" << std::endl;
				std::cout << "Username (write(/nx) if you won't change) :";
				std::cin >> newUser;
				std::cout << "password (write(/nx) if you won't change) :";
				std::cin >> newPass;
				std::cout << "email (write(/nx) if you won't change) :";
				std::cin >> newEmail;
				if (newUser == changes)
				{
					newUser = usrBc;
				}
				if (newPass == changes)
				{
					newPass = passBc;
				}
				if (newEmail == changes)
				{
					newEmail = emailBc;
				}
				system("cls");
				std::cout << "Processing ..." << std::endl;
				bool test(false);
				std::string querys("delete from accounts_data where id ='" + id + "'");
				const char* qk = querys.c_str();
				qstate = mysql_query(conn, qk);
				if (!qstate)
				{
					std::cout << "Account sucessfully Deeleted !" << std::endl;
					Sleep(1100);
					system("cls");
					test = true;
				}
				else std::cout << "Error fetching data : " << mysql_errno(conn) << std::endl;
				if (test)
				{
					std::string aq = "insert into accounts_data (username , password,email,application) values ('" + newUser + "','" + newPass + "','" + newEmail + "','" + app + "')";
					const char* qa = aq.c_str();
					qstate = mysql_query(conn, qa);
					if (!qstate)
					{
						std::cout << "Account Edited Sucessfully" << std::endl;
						system("PAUSE");
					}
					else std::cout << "Error Fetching Data : " << mysql_errno(conn) << std::endl;
				}
				else
				{
					std::cout << "Fault !" << std::endl;
					Sleep(1000);
				}
			}
			else
			{
				std::cout << "Error : fetching data err" << std::endl;
			}
		}
		if (command == "6")
		{
			std::string appd;
			system("cls");
			seeAll();
			std::cout << "------------------------------ Your Application To DElete :" << std::endl;
			std::cin >> appd;
			std::string fetc("delete from accounts_data where application ='" + appd + "'");
			const char* mp(fetc.c_str());
			qstate = mysql_query(conn, mp);
			if (!qstate)
			{
				std::cout << "Account's app " << appd << " Sucessfully Deleted !" << std::endl;
				system("PAUSE");
			}
			else
			{
				std::cout << "Error : " << mysql_errno(conn) << std::endl;
				system("PAUSE");
			}
		}
		if (command == "7")
		{
			std::cout << "Exiting..." << std::endl;
			std::cout << "Disconnection ..." << std::endl;
			Sleep(5000);
			running = false;
			return 0;
		}
	}
}