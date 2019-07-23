/*This project was created to creat file carries user's name
so, The user can write notes inside it with the time it was written
Authers :
Amir ALtakroori and Faris Abu 3ram
*/

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

void printUserMenu()
{
	cout << "Welcome to the brand new Sticky Notes!\n\n"
		<< "Here is the list of operation this program offers : \n"
		<< " 1 - Add new user \n 2 - Add new note \n "
		<< "3 - View notes for a specific user \n 4 - Exit \n\n"
		<< "Please, enter your choice: ";
}

void pressEnter()
{
	char Enter ;
	do
	{
		cout << "Press Enter to return to main menu : ";
		cin.ignore();
		cin.get(Enter);
	}while(Enter!='\n');
}

class Password
{
public:

	bool checkWithGeneratingPassword (string userName)
	{
		string userPassword , verifyPassword ;
		cin.get();
		cout << "Please enter your password: ";
		getline (cin,userPassword);
		cout << "Please enter it again: ";
		getline (cin,verifyPassword);

		if (userPassword == verifyPassword)
		{
			ofstream file;
			file.open("UserName and Password", ios_base::app); //ios_base::app use to overwrite the note into the file
			file << userName << endl << userPassword << endl;	
			return true;
		}
		else
		{
			cout << "\nPassword and verification do not match!\n"
				<< "If you want to try again please press *1\n"
				<< "If you want to go back press *2 \n";

			int choice;		cin >> choice;
			if (choice == 1)
				checkWithGeneratingPassword (userName);
			else
				return false;
		}
	}

	string getUserPassword(string fullNameUser)
	{
		ifstream inUserFile("UserName and Password");
		string storedUserName, storedPassword;
		while (getline(inUserFile,storedUserName))// we guarantee that there is userName and password already
			if (storedUserName == fullNameUser )
			{
				getline(inUserFile,storedPassword);
				return storedPassword;
			}
			return "";
	}

	bool askPassword(string userName)
	{
		string enteredUserPassword ;
		cout << "Please enter your password: ";
		cin.get();
		getline(cin,enteredUserPassword);

		if (enteredUserPassword == getUserPassword (userName))
			return true;

		cout << "\nPassword is not correct!\n"
			<< "If you want to try again please press: 1\n"
			<< "If you want to go back press: 2 \n";

		int choice;		cin >> choice;
		if (choice == 1)
			askPassword (userName);
		else
			return false;

		return false;
	}
};

// This function will implement the first option in main menu
void addNewUser()
{
	/*
	This fuction let the user to add new user
	by entering first name and last name.
	Adding new user means open a new file in specific directory.
	Project guarantee that there is a unique user.
	*/

	cout << "\nWelcome aboard new user!\nPlease let me know your first name: ";
	string firstName;				cin >> firstName;

	cout << "Great " << firstName << ", now please enter your last name: ";
	string lastName;				cin >> lastName;

	string fullName = firstName + " " + lastName;
	ifstream inUserFile (fullName);

	if (!inUserFile) // there is no file have the same user name
	{
		Password* userPasswoed = new Password();
		if (userPasswoed->checkWithGeneratingPassword(fullName))  // to generate a password and to check if that proccess done
		{
			ofstream outUserFile (fullName); // just to open new file have the same name of user
			cout << fullName << " is added successfully\n";
		}
	}
	else // user name was used
		cout << "\n" << fullName << " was used!\n please try another name or write your notes directly!\n";
}

class  Note
{
	// class to add new note
private:
	string note;//a note that user add it
	void getTime(int& year, int& month, int& day, int& hour, int& mins)
	{
		// to claculate the current time

		time_t Time;//The time_t datatype is a data type in the ISO C library defined for storing system time values
		time(&Time);//Get the current calendar time as a value of type time_t.
		tm TM = *localtime(&Time);//Structure containing a calendar date and time broken down into its components.

		year = TM.tm_year + 1900;
		month = TM.tm_mon;
		day = TM.tm_mday;
		hour = TM.tm_hour;
		mins = TM.tm_min;
	}

public:
	Note(string note)
	{
		//constructure was take note as  a parameters
		this->note = note;
	}

	string toStringNote()
	{
		// to return a note and time  in best way
		int year, month, day, hour, mins;
		getTime(year, month, day, hour, mins);
		return (to_string(day) + '/' + to_string(month) + '/' + to_string(year) + " " + to_string(hour) + ':' + to_string(mins)  +':'+ "\n"+ note+'\n'+'\n' );
	}
};

void addNewNote()
{
	string firstName, lastName;//user's full name
	cout << "Let's add a new note ... \n";
	cout << "Please enter your full name first:  "; cin >> firstName >> lastName;
	string fullName = firstName + " " + lastName ;
	ifstream file(fullName);
	if (!file)
	{
		cout << "Oh! Sorry the user name was not found, please check the name again and if this is your first time here,"
			<< "please go ahead and create a new user from the main menu ..." << endl;
	}
	else
	{
		Password* userPassword = new Password();
		if (userPassword -> askPassword(fullName))
		{
			cout << "Your record is found, I'm now opening your file,,,.\nReady!\nPlease enter your note :";
			string newNote;
			cin.ignore();
			getline(cin, newNote);
			Note note(newNote);
			ofstream File;
			File.open(fullName, ios_base::app);//ios_base::app use to overwrite the note into the file
			File << note.toStringNote();
			File.close();
		}
	}
}

// This function will implement the third option in main menu
void printAllNotes()
{

	cout << "Retrieve your notes? Absolutely! Please let know your full name first: ";

	string firstName , lastName;
	cin >> firstName >> lastName;

	string fullName = firstName + " " + lastName;
	ifstream inUserFile (fullName);

	if (!inUserFile) // there is no file have the same user name
		cout << "\n\n" << "User name: " << fullName << "was not found, please try diffrent user name!\n";
	

	else // user name was found
	{
		Password* userPassword = new Password();
		if (userPassword -> askPassword(fullName))
		{
			cout << "Found it!\n"
				<< "Here are your stored notes:\n"
				<< "-------------\n";

			string fileContents;
			while (getline(inUserFile,fileContents))
				cout << fileContents << endl;
			cout << "-------------\n"
				<< "Happy to serve you :)\n";
		}
	}
}

int main()
{
	int userChoice; // to control what is the option to user need to move it
	do
	{
		printUserMenu();
		system ("color 07");
		cin >> userChoice;
		switch (userChoice)
		{
		case 1:
			{
				/*
				This option let the user to add new user
				by entering first name and last name.
				Adding new user means open a new file in specific directory.
				Project guarantee that there is a unique user.
				*/
				system("cls");
				system("color 70");
				addNewUser();
				pressEnter();
			}
			break;
		case 2:
			{
				/*
				This option let the user to add new note
				by entering first name and last name.
				Adding new note means open a specific file depend on user name if exist or not .
				*/
				system("cls");
				system("color 70");
				addNewNote();
				pressEnter();
			}
			break;
		case 3:
			{
				system("cls");
				system("color 70");
				printAllNotes();
				pressEnter();
			}
			break;
		case 4:
			break;
		default:
			{
				cout << "Invalid choice! \n";
				system("color 4");
				pressEnter();
			}
		}
		system("cls");
	} while (userChoice != 4);

	return 0;
}