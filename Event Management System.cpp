#include <iostream>
#include <fstream>
#include <string>
#include<string.h>
#include <stdexcept>
#include <windows.h>
#include<cctype>
#include<iomanip>
#include<conio.h>
using namespace std;
void intro();	//introductory screen function
void entry();
string getpassword(const string& prompt = "Enter password> " );

struct User
{
	char username[25],pass[25];
};
struct Hall
{
	int id,	charges;
	char name[30],description[70],place[30];
};
struct Booking
{
	int id,hallid,clientid;
	char description[70],title[30],date[12];
};
struct Client
{
	int id;
	char mobile[15],name[30],email[35],address[70];
};



void validate()
{
	User ln;
	string password;
	char pwd[15],user[25];
	cout<<"Please Enter Username : ";
	cin>>user;
	password=getpassword("Please Enter Password : ");
	strcpy(pwd, password.c_str());
	bool flag=false;
	ifstream inFile;
	inFile.open("user.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
    	while(inFile.read(reinterpret_cast<char *> (&ln), sizeof(User)))
	{
		if(strcmp(ln.username,user)==0 && strcmp(ln.pass,pwd)==0)
		{
			cout<<"\nLoginned Successfully...\n";
			getch();	
			flag=true;
			break;
		}
	}
    inFile.close();
	if(flag==false)
		{
		cout<<"\nYou Entered Incorrect Details...Please Login again...\n";
		getch();
		entry();
		}	
}


void addUser()
{
	User ln;
	string password,password1;
	char pass1[15];
	cout<<"Please Enter Username : ";
	cin>>ln.username;
	password=getpassword("Please Enter Password : ");
	password1=getpassword("\nPlease Confirm Password : ");
	strcpy(ln.pass, password.c_str());
	strcpy(pass1, password1.c_str());
	if(1) //Condistion to check if user already exist or not
	{
	if(strcmp(ln.pass,pass1)==0)
	{
		ofstream outFile;
		outFile.open("User.dat",ios::binary|ios::app);
		outFile.write(reinterpret_cast<char *> (&ln), sizeof(User));
		outFile.close();
		cout<<"\nUser Registered Successfully...\n";
		getch();
		entry();
	}
	else
	{
		cout<<"\nPasswords don't Match...\n";
		getch();
		entry();
	}
	}
	else
	{
		cout<<"\nUser already exist...Please Login..\n";
		getch();
		entry();
	}	
}

Hall inputHall()
{
	Hall h;
	cout<<"Enter the Hall ID: ";
	cin>>(h.id);
	cin.ignore();
	cout<<"Enter the Hall Name: ";
	cin.getline(h.name,30);
	cout<<"Enter the Hall Charges: ";
	cin>>(h.charges);
	cout<<"Enter the Hall Dscription: ";
	cin.ignore();
	cin.getline(h.description,70);
	cout<<"Enter the Hall Place: ";
	//cin.ignore();
	cin.getline(h.place,30);
	ofstream fileHall;
	fileHall.open("Hall.dat",ios::binary|ios::app);
	fileHall.write(reinterpret_cast<char *> (&h), sizeof(Hall));
	fileHall.close();
	cout<<"\n\nHall Registered Succssfully..."<<endl;
	return h;
}

Client inputClient()
{
	fstream fileClient("Client.dat",ios::binary| ios::in | ios::out);
if(fileClient.is_open())
{
	Client c;
	cout<<"Enter the Clint ID: ";
	cin>>(c.id);
	cout<<"Enter the Clint Name: ";
	cin.ignore();
	cin.getline(c.name,30);
	cout<<"Enter the Clint Mobile Number: ";
	cin.ignore();
	cin.getline(c.mobile,15);
	cout<<"Enter the Clint Email: ";
	cin.ignore();
	cin.getline(c.email,35);
	cout<<"Enter the Clint Address: ";
	//cin.ignore();
	cin.getline(c.address,70);
	fileClient.write(reinterpret_cast<char *>(&c), sizeof(c));
	fileClient.close();
	return c;
}
else cout<<"File Opening Error. (ClientFile)"<<endl;
}

Booking inputBooking()
{
	fstream fileBooking("Booking.dat",ios::binary| ios::app);
if(fileBooking.is_open())
{
	Booking b;
	cout<<"Enter the Booking ID: ";
	cin>>(b.id);
	cout<<"Enter the Booking Title: ";
	cin.ignore();
	cin.getline(b.title,30);
	cout<<"Enter the Booking Hall ID: ";
	cin.ignore();
	cin>>b.hallid;
	cout<<"Enter the Booking Date (DD-MM-YYYY): ";
	cin.ignore();
	cin.getline(b.date,12);
	cout<<"Enter the Booking Description: ";
	//cin.ignore();
	cin.getline(b.description,70);
	Client c=inputClient();
	b.clientid=c.id;
	fileBooking.write(reinterpret_cast<char *>(&b), sizeof(b));
	fileBooking.close();
	return b;
}
else cout<<"File Opening Error. (BookingFile)"<<endl;
}

void outputHall()
{
	Hall h1;
	ifstream inFile;
	inFile.open("Hall.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tALL HALLS LIST\n\n";
	cout<<"===========================================================================================\n";
	cout<<"HALL no.      NAME           Charges\t\tDescription\t\t\tLocation\n";
	cout<<"===========================================================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&h1), sizeof(Hall)))
	{
		cout<<h1.id<<setw(10)<<" "<<h1.name<<setw(8)<<" \t"<<h1.charges<<setw(12)<<"\t  "<<h1.description<<"\t\t"<<h1.place<<endl;
	}
	inFile.close();
	}

int checkBooking(string date)
{
	Booking b;
	int i=0;
	ifstream inFile;
	inFile.open("Booking.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return 2;
	}
	cout<<"\n\n\t\tALL BOOKINGS LIST\n\n";
	cout<<"=============================================================================================\n";
	cout<<"BOOK ID.      TITLE           HALL ID\t\tDATE\t\t\tDESCRIPTION\n";
	cout<<"=============================================================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&b), sizeof(Booking)))
	{
		if(b.date==date){
		cout<<b.id<<setw(10)<<" "<<b.title<<setw(8)<<" \t"<<b.hallid<<setw(12)<<"\t  "<<b.date<<"\t\t"<<b.description<<endl;
		i=1;
		}
	}
	inFile.close();
	return i;
}


void outputBooking()
{
	Booking b;
	ifstream inFile;
	inFile.open("Booking.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tALL BOOKINGS LIST\n\n";
	cout<<"===============================================================================================\n";
	cout<<"BOOK ID.      TITLE           HALL ID\t\tDATE\t\t\tDESCRIPTION\n";
	cout<<"===============================================================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&b), sizeof(Booking)))
	{
		cout<<b.id<<setw(10)<<" "<<b.title<<setw(8)<<" \t"<<b.hallid<<setw(12)<<"\t  "<<b.date<<"\t\t"<<b.description<<endl;
	}
	inFile.close();
}

void outputClient()
{
	Client c;
	ifstream inFile;
	inFile.open("Client.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tALL CLIENTS LIST\n\n";
	cout<<"==============================================================================================\n";
	cout<<"Client ID.      Name           Cell #\t\tEmail\t\t\tAddress\n";
	cout<<"==============================================================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&c), sizeof(Client)))
	{
		cout<<c.id<<setw(10)<<" "<<c.name<<setw(8)<<" \t"<<c.mobile<<setw(12)<<"\t  "<<c.email<<"\t\t"<<c.address<<endl;
	}
	inFile.close();
}


int main ()
{
	Hall h; 
	char ch,date[12];
	int num;
	intro();
	entry();
	do
	{
		system("cls");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t[01]. SHOW ALL HALLS";
		cout<<"\n\n\t[02]. ADD HALL";
		cout<<"\n\n\t[03]. SHOW BOOKINGS ON DATE";
		cout<<"\n\n\t[04]. CHECK HALL AVAILABILITY";
		cout<<"\n\n\t[05]. BOOK HALL";
		cout<<"\n\n\t[06]. SHOW ALL BOOKINGS";
		cout<<"\n\n\t[07]. SHOW ALL CLIENTS";
		cout<<"\n\n\t[08]. LOGOUT/EXIT PROGRAM";
		cout<<"\n\n\tSelect Your Option (1-8) ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			outputHall();
			break;
		case '2':
			h=inputHall();
			break;
		case '3':
			cout<<"Enter the Date to search Booking(DD-MM-YYYY):";
			cin.ignore();
			cin.getline(date,12);
			checkBooking(date);
			break;
		case '4': 
			cout<<"Enter the Date to Check Booking Availability(DD-MM-YYYY):";
			cin.ignore();
			cin.getline(date,12);
			if(checkBooking(date)){
				cout<<"Hall is already booked."<<endl;
			} else 
			cout<<"Hall is availabale on this date."<<endl;
			break;
		case '5':
			inputBooking();
			break;
		case '6':
			outputBooking();
			break;
		case '7':
			outputClient();
			break;
		 case '8':
			cout<<"\n\n\tThanks for using Event/Hall Management system";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
    }while(ch!='8');
	return 0;
}

void intro()
{
	cout<<"\n\n\n\t\t\t\t\tE v e n t / H a l l";
	cout<<"\n\n\t\t\t\t\tM a n a g e m e n t";
	cout<<"\n\n\t\t\t\t\t   S Y S T E M";
	cout<<"\n\n\n\n\t\t\tGroup Members : 195033, 195034, 195035, 195036, 195037";
	cout<<"\n\n\t\t\t\t   Air University, Multan Campus";
	cin.get();
}


void entry()
{
	int ch;
	User usr;
	system("CLS");
	cout<<"\n\n\n\n";
	cout<<"\t[1] Login \n";
	cout<<"\t[2] Register \n";
	cout<<"\t[3] Exit\n\t";
	cin>>ch;
	if(ch==1)
	{
		validate();
	}
	else if(ch==2)
	{
		addUser();
	}
	else if(ch==3)
	{
		cout<<"\nProgram is Exiting.\n";
		getch();
		exit(1);
	}
	else
	{
		cout<<"\nYou Entered Incorrect Option.\n";
		getch();
		exit(1);
	}
}

string getpassword( const string& prompt  )
  {
  string result;
  // Set the console mode to no-echo, not-line-buffered input
  DWORD mode, count;
  HANDLE ih = GetStdHandle( STD_INPUT_HANDLE  );
  HANDLE oh = GetStdHandle( STD_OUTPUT_HANDLE );
  if (!GetConsoleMode( ih, &mode ))
    throw runtime_error(
      "getpassword: You must be connected to a console to use this program.\n"
      );
  SetConsoleMode( ih, mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT) );
  // Get the password string
  WriteConsoleA( oh, prompt.c_str(), prompt.length(), &count, NULL );
  char c;
  while (ReadConsoleA( ih, &c, 1, &count, NULL) && (c != '\r') && (c != '\n'))
    {
    if (c == '\b')
      {
      if (result.length())
        {
        WriteConsoleA( oh, "\b \b", 3, &count, NULL );
        result.erase( result.end() -1 );
        }
      }
    else
      {
      WriteConsoleA( oh, "*", 1, &count, NULL );
      result.push_back( c );
      }
    }
  // Restore the console mode
  SetConsoleMode( ih, mode );
  return result;
  }
