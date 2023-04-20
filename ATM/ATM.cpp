#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>

using namespace std;
///////////////////ENUMS///////////////////
;
enum enTransactions
{
	QUICKWITHDROW = 1 , NORMALWITHDROW = 2 , DEPOSIT = 3 , TOTALBALANCE = 4 , LOGOUT = 5
};
////////////////STRUCTS/////////////////
struct stAccountData {

	string accountNumber;
	string pinCode;
	string name;
	string phone;
	double accountBalance;
	bool deleteFlag = false;
};
//////////////GLOBAL VARS//////////////////
string ClientsFile = "D:\\Programing\\c++\\Bank_System_With_ATM\\BankSystem\\Debug\\clinet_Data_File.txt";
stAccountData UserAccount;
////////////Fuctions Calls//////////////
void login();
void performTransaction( enTransactions options );
short mainMenue();
////////////FUNCTIONS//////////////
void drowHeader()
{
	cout << "\n\t\t\t\t\t Client List" << endl;
	cout << "\n__________________________________________________________________________________________________\n"
		<< endl;
	cout << "|" << left << setw( 15 ) << "Account Number ";
	cout << "|" << left << setw( 10 ) << "Pin Code ";
	cout << "|" << left << setw( 40 ) << "Name ";
	cout << "|" << left << setw( 12 ) << "Phone ";
	cout << "|" << left << setw( 12 ) << "Account Balance";
	cout << "\n__________________________________________________________________________________________________\n"
		<< endl;
}
void drowFooter()
{
	cout << "\n__________________________________________________________________________________________________\n"
		<< endl;
}
void drowBalancesScreenHeader()
{
	cout << "\n\t\t\t\t\t Client Account" << endl;
	cout << "\n__________________________________________________________________________________________________\n"
		<< endl;
	cout << "|" << left << setw( 15 ) << "Account Number ";
	cout << "|" << left << setw( 40 ) << "Name ";
	cout << "|" << left << setw( 12 ) << "Account Balance";
	cout << "\n__________________________________________________________________________________________________\n"
		<< endl;
}
vector<string> seperateString( string& text , string seperator = " " )
{
	int position = 0;
	string word;
	vector<string> words;
	position = text.find( seperator );

	while ( ( position = text.find( seperator ) ) != std::string::npos )
	{
		word = text.substr( 0 , position );
		if ( word != "" )
		{
			words.push_back( word );
		}
		text.erase( 0 , position + seperator.length() );
		position = text.find( seperator );
	}

	if ( text != "" )
	{
		words.push_back( text );
	}
	return words;
}
stAccountData convertUserLineToRecord( string line , string seperator = "#//#" )
{
	stAccountData client;
	vector<string> vClientData;

	vClientData = seperateString( line , seperator );

	client.accountNumber = vClientData[ 0 ];
	client.pinCode = vClientData[ 1 ];
	client.name = vClientData[ 2 ];
	client.phone = vClientData[ 3 ];
	client.accountBalance = stod( vClientData[ 4 ] );

	return client;
}
string convertDataToLineOfData( stAccountData& record , string seperator = " " )
{
	string stRescord = "";

	stRescord += record.accountNumber + seperator;
	stRescord += record.pinCode + seperator;
	stRescord += record.name + seperator;
	stRescord += record.phone + seperator;
	stRescord += record.accountBalance;

	return stRescord;
}
vector<stAccountData> ReadFileToVector( string fileName )
{
	vector<stAccountData> vRecord;
	fstream file;
	file.open( fileName , ios::in );

	if ( file.is_open() )
	{
		string line;
		stAccountData clinet;
		while ( getline( file , line ) )
		{
			clinet = convertUserLineToRecord( line );
			vRecord.push_back( clinet );
		}
		file.close();
	}
	return vRecord;
}
void WriteRecordToFile( string fileName , stAccountData& record )
{
	fstream file;
	file.open( fileName , ios::out | ios::app );
	if ( file.is_open() )
	{

		file << convertDataToLineOfData( record , "#//#" ) << endl;

		file.close();
	}
}
void backToTransactionsMenue() {
	cout << "To Back To Transactions menue Press Any Key.." << endl;
	system( "pause" );
	performTransaction( ( enTransactions ) mainMenue() );
}

vector<stAccountData> loadUsersFromFile( string fileName )
{
	vector<stAccountData> vRecord;
	fstream file;
	file.open( fileName , ios::in );

	if ( file.is_open() )
	{
		string line;
		stAccountData user;
		while ( getline( file , line ) )
		{
			user = convertUserLineToRecord( line );
			vRecord.push_back( user );
		}
		file.close();
	}
	return vRecord;
}
bool checkIfUserNameAndPasswordIsCorrect( string accountNumber , string pinCode , stAccountData& user ) {

	vector <stAccountData> vUsers = loadUsersFromFile( ClientsFile );
	for ( stAccountData& u : vUsers ) {
		if ( u.accountNumber == accountNumber && u.pinCode == pinCode )
		{
			user = u;
			return true;
		}
	}
	return false;
}
bool loadUser( string accountNumber , string pinCode ) {
	if ( checkIfUserNameAndPasswordIsCorrect( accountNumber , pinCode , UserAccount ) )
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool findClientByAccountNumber( vector<stAccountData>& vClients , stAccountData& client , string accountNumberToFind )
{
	for ( stAccountData& cl : vClients )
	{
		if ( cl.accountNumber == accountNumberToFind )
		{
			client = cl; // if we find the account number we fill the client struct and return
			return true;
		}
	}
	return false;
}
void printClientData( stAccountData& client ) {
	cout << "|" << left << setw( 15 ) << client.accountNumber;
	cout << "|" << left << setw( 10 ) << client.pinCode;
	cout << "|" << left << setw( 40 ) << client.name;
	cout << "|" << left << setw( 12 ) << client.phone;
	cout << "|" << left << setw( 12 ) << client.accountBalance;
	cout << endl;
}
vector<stAccountData> saveClientsDataToFileAfterUpdate( string fileName , vector<stAccountData>& vClients )
{
	fstream file;
	file.open( fileName , ios::out ); // overwrite
	string line;
	if ( file.is_open() )
	{
		for ( stAccountData& cl : vClients )
		{
			WriteRecordToFile( ClientsFile , cl );
		}
		file.close();
	}
	return vClients;
}
void Deposit() {

	vector<stAccountData> vClients = ReadFileToVector( ClientsFile );
	stAccountData client;
	string accountToFind = "";
	double depositAmount = 0;
	cout << "Enter Account Number? ";
	getline( cin >> ws , accountToFind );
	while ( !findClientByAccountNumber( vClients , client , accountToFind ) )
	{
		cout << "No Account With Number " << accountToFind << endl;

		cout << "Enter Account Number? ";
		getline( cin >> ws , accountToFind );
	}
	system( "cls" );
	drowHeader();
	printClientData( client );
	drowFooter();
	cout << "How Much Do You Want To Deposit? ";
	cin >> depositAmount;
	for ( stAccountData& cl : vClients )
	{
		if ( cl.accountNumber == accountToFind )
		{
			cl.accountBalance = cl.accountBalance + depositAmount;
			saveClientsDataToFileAfterUpdate( ClientsFile , vClients );
			break;
		}
	}
}
void normalWithDrow() {
	vector<stAccountData> vClients = ReadFileToVector( ClientsFile );
	stAccountData client;
	string accountToFind = "";
	double depositAmount = 0;
	cout << "Enter Account Number? ";
	getline( cin >> ws , accountToFind );
	while ( !findClientByAccountNumber( vClients , client , accountToFind ) )
	{
		cout << "No Account With Number " << accountToFind << endl;
		cout << "Enter Account Number? ";
		getline( cin >> ws , accountToFind );
	}
	system( "cls" );
	drowHeader();
	printClientData( client );
	drowFooter();
	cout << "How Much Do You Want To Withdrow? (make Sure To Enter A correct Amount..) ";
	cin >> depositAmount;

	for ( stAccountData& cl : vClients )
	{
		if ( cl.accountNumber == accountToFind )
		{
			while ( depositAmount > cl.accountBalance )
			{
				cout << "The Amount That you have entered is more than the account balance.." << endl;
				cout << "How Much Do You Want To Withdrow? (make Sure To Enter A correct Amount..) ";
				cin >> depositAmount;
			}
			cl.accountBalance = cl.accountBalance - depositAmount;
			saveClientsDataToFileAfterUpdate( ClientsFile , vClients );
			break;
		}
	}

}
void printBalancesData( stAccountData& client )
{
	cout << "|" << left << setw( 15 ) << client.accountNumber;
	cout << "|" << left << setw( 40 ) << client.name;
	cout << "|" << left << setw( 12 ) << client.accountBalance;
	cout << endl;
}
void showBalancessData( vector<stAccountData> vClients )
{

	for ( stAccountData& cl : vClients )
	{
		printBalancesData( cl );
	}
}

void TotalBalance() {
	vector<stAccountData> vClients = ReadFileToVector( ClientsFile );
	drowBalancesScreenHeader();
	showBalancessData( vClients );
	drowFooter();
}
short withDrowOptions() {
	system("cls");
	short withDrow = 0;
	cout << setw( 12 ) << "[1]  50 \t"<< setw( 12 ) << "[2]  1000" << endl;
	cout << setw( 12 ) << "[3]  200\t"<< setw( 12 ) <<"[4]  2000" << endl;
	cout << setw( 12 ) << "[5]  400\t"<< setw( 12 ) <<"[6]  3000" << endl;
	cout << setw( 12 ) << "[7]  500\t"<< setw( 12 ) <<"[8]  5000" << endl;
	cout << setw( 12 ) << "[9]  Back" << endl;
	cin >> withDrow;
	return withDrow;
}
void BalanceAfterquickWithdrow( ) {
	short withDrow = withDrowOptions();
	vector<stAccountData> vClients = ReadFileToVector( ClientsFile );
	switch ( withDrow )
	{
	case 1:
		if ( UserAccount.accountBalance < 50 )
		{
			cout << "The Amount That you have entered is more than the account balance.." << endl;
			break;
		}
		else
		{
			UserAccount.accountBalance -= 50;
		}
		break;
	case 2:
		if ( UserAccount.accountBalance < 200 )
		{
			cout << "The Amount That you have entered is more than the account balance.." << endl;
			break;
		}
		else
		{
			UserAccount.accountBalance -= 200;
		}
		break;
	case 3:
		if ( UserAccount.accountBalance < 400 )
		{
			cout << "The Amount That you have entered is more than the account balance.." << endl;
			break;
		}
		else
		{
			UserAccount.accountBalance -= 400;
		}
		break;
	case 4:
		if ( UserAccount.accountBalance < 500 )
		{
			cout << "The Amount That you have entered is more than the account balance.." << endl;
			break;;
		}
		else
		{
			UserAccount.accountBalance -= 500;
		}
		break;
	case 5:
		if ( UserAccount.accountBalance < 1000 )
		{
			cout << "The Amount That you have entered is more than the account balance.." << endl;
			break;
		}
		else
		{
			UserAccount.accountBalance -= 1000;
		}
		break;
	case 6:
		if ( UserAccount.accountBalance < 2000 )
		{
			cout << "The Amount That you have entered is more than the account balance.." << endl;
			break;
		}
		else
		{
			UserAccount.accountBalance -= 2000;
		}
		break;
	case 7:
		if ( UserAccount.accountBalance < 3000 )
		{
			cout << "The Amount That you have entered is more than the account balance.." << endl;
			break;
		}
		else
		{
			UserAccount.accountBalance -= 3000;
		}
		break;
	case 8:
		if ( UserAccount.accountBalance < 5000 )
		{
			cout << "The Amount That you have entered is more than the account balance.." << endl;
			break;
		}
		else
		{
			UserAccount.accountBalance -= 5000;
		}
		break;

	}
	saveClientsDataToFileAfterUpdate( ClientsFile , vClients );

}
void quickWithdrow(  ) {
	BalanceAfterquickWithdrow();
	cout << "Your Total Balance Now Is : " << UserAccount.accountBalance << endl;
}
short mainMenue() {
	system( "cls" ); // system("clear");
	short choice = 0;
	cout << "\n-------------------------------------------------------\n";
	cout << "\t\t\t MAIN MENUE\n";
	cout << "-------------------------------------------------------\n";
	cout << "\t[1]=> QUICK WITHDROW" << endl;
	cout << "\t[2]=> NORMAL WITHDROW" << endl;
	cout << "\t[3]=> DEPOSIT" << endl;
	cout << "\t[4]=> CHECK BALANCE" << endl;
	cout << "\t[5]=> LOGOUT" << endl;
	cout << "\n-------------------------------------------------------\n";
	cout << "Choose What You Want To Do From [1 - 5] ?: ";
	cin >> choice;
	return choice;

}
void performTransaction( enTransactions options ) {
	switch ( options )
	{
	case enTransactions::QUICKWITHDROW:
		system( "pause" );
		quickWithdrow(  );
		backToTransactionsMenue();
		break;
	case enTransactions::NORMALWITHDROW:
		system( "pause" );
		normalWithDrow();
		backToTransactionsMenue();
		break;
	case enTransactions::DEPOSIT:
		system( "pause" );
		Deposit();
		backToTransactionsMenue();
		break;
	case enTransactions::TOTALBALANCE:
		system( "pause" );
		TotalBalance();
		backToTransactionsMenue();
		break;
	case enTransactions::LOGOUT:
		system( "pause" );
		login();
		break;
	}
}
void login() {
	bool loginFlag = false;
	string accountNumber = "";
	string pinCode = "";
	do
	{
		system( "cls" ); // system("clear");
		cout << "\n-------------------------------------------------------\n";
		cout << "\t\t\t LOGIN PAGE\n";
		cout << "-------------------------------------------------------\n";
		if ( loginFlag )
		{
			cout << "Invalid Account Number Or Pin Code.." << endl;
		}
		cout << "Enter Account Number: ";
		getline( cin >> ws , accountNumber );
		cout << "Enter Pin Code: ";
		getline( cin >> ws , pinCode );

		loginFlag = !loadUser( accountNumber , pinCode );
	} while ( loginFlag );
	performTransaction( ( enTransactions ) mainMenue() );
}
int main()
{
	login();

	return 0;
}
