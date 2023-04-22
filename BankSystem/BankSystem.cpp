#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>

using namespace std;
///////////////////ENUMS///////////////////
enum enOptions
{
	showList = 1 , addList = 2 , deletList = 3 , updateList = 4 , findList = 5 , transactions = 6 , ManaguUsers = 7 , Logout = 8
};
enum enManagUsersOptions
{
	ShowUers = 1 , AddUser = 2 , DeleteUser = 3 , UpdateUser = 4 , FindUser = 5 , Transactions = 6 , BackToMAinMenue = 7
};
enum enPremissions
{
	eAll = -1 , pListClients = 1 , pAddNewClint = 2 , pDeleteClient = 4 , pUpdateClients = 8 , pFindClients = 16 , pTransactions = 32 , pManagUsers = 64
};
enum enTransactions
{
	deposit = 1 , withdrow = 2 , totalBalance = 3 , MainMenue = 4
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
struct stUsers
{
	string userName;
	string password;
	int preimission;
	bool deleteFlag = false;
};
//////////////GLOBAL VARS//////////////////
string ClientsFile = "clinet_Data_File.txt";
string UsersFile = "users.txt";
stUsers UserAccount;
//////////////FUNCTIONS Calls////////////////////
bool checkIfClientAccountNumberIsAlreadyTaken( string accountNumber , string flieName );
void pages( enOptions choice );
bool chechPremissions( enPremissions premission );
bool checkIfUserAccountNameIsAlreadyTaken( string accountName , string flieName );
void backToManageUsersMainMenue();
//////////////FUNCTIONS/////////////////////
stAccountData readRecord()
{
	stAccountData record;
	cout << "Enter Account Number: ";
	getline( cin >> ws , record.accountNumber );
	while ( checkIfClientAccountNumberIsAlreadyTaken( record.accountNumber , "clinet_Data_File.txt" ) )
	{
		cout << "\nClient With [ " << record.accountNumber << " ] is Already Exist, Enter Another Account Number." << endl;
		getline( cin >> ws , record.accountNumber );
	}
	cout << "Enter Pin Code: ";
	getline( cin >> ws , record.pinCode );
	cout << "Enter Name: ";
	getline( cin >> ws , record.name );
	cout << "Enter Phone: ";
	getline( cin >> ws , record.phone );
	cout << "Enter Account Balance: ";
	cin >> record.accountBalance;
	return record;
}
int readPremissions() {
	int premission = 0;
	char answer = 'n';
	cout << "Do You Want To Give This User Full Access ? ";
	cin >> answer;
	if ( answer == 'y' || answer == 'Y' )
	{
		return -1;
	}
	cout << "Do You Want To Give This User  Access To Show Clients List ? ";
	cin >> answer;
	if ( answer == 'y' || answer == 'Y' )
	{
		premission += enPremissions::pListClients;
	}
	cout << "Do You Want To Give This User Access To Add New Client ? ";
	cin >> answer;
	if ( answer == 'y' || answer == 'Y' )
	{
		premission += enPremissions::pAddNewClint;
	}
	cout << "Do You Want To Give This User Access To Delete Clients ? ";
	cin >> answer;
	if ( answer == 'y' || answer == 'Y' )
	{
		premission += enPremissions::pDeleteClient;
	}
	cout << "Do You Want To Give This User Access To Update Clients ? ";
	cin >> answer;
	if ( answer == 'y' || answer == 'Y' )
	{
		premission += enPremissions::pUpdateClients;
	}
	cout << "Do You Want To Give This User Access To Find A Client ? ";
	cin >> answer;
	if ( answer == 'y' || answer == 'Y' )
	{
		premission += enPremissions::pFindClients;
	}
	cout << "Do You Want To Give This User Access To See Transactions? ";
	cin >> answer;
	if ( answer == 'y' || answer == 'Y' )
	{
		premission += enPremissions::pTransactions;
	}
	cout << "Do You Want To Give This User Access To Manage Clients ? ";
	cin >> answer;
	if ( answer == 'y' || answer == 'Y' )
	{
		premission += enPremissions::pManagUsers;
	}
	return premission;
}
stUsers readUserRecord()
{
	stUsers record;
	cout << "Enter User Name: ";
	getline( cin >> ws , record.userName );
	while ( checkIfUserAccountNameIsAlreadyTaken( record.userName , UsersFile ) )
	{
		cout << "\nClient With [ " << record.userName << " ] is Already Exist, Enter Another User Name." << endl;
		getline( cin >> ws , record.userName );
	}
	cout << "Enter A Password: ";
	getline( cin >> ws , record.password );
	record.preimission = readPremissions();
	return record;
}
stAccountData readToUpdateRecord()
{
	stAccountData record;
	cout << "Enter Pin Code: ";
	getline( cin >> ws , record.pinCode );
	cout << "Enter Name: ";
	getline( cin >> ws , record.name );
	cout << "Enter Phone: ";
	getline( cin >> ws , record.phone );
	cout << "Enter Account Balance: ";
	cin >> record.accountBalance;
	return record;
}
stUsers readToUpdateUserRecord()
{
	stUsers record;
	int premissiomn = 0;
	cout << "Enter User Name: ";
	getline( cin >> ws , record.userName );
	cout << "Enter Passwrod: ";
	getline( cin >> ws , record.password );
	premissiomn = readPremissions();

	return record;
}
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
void drowUsersHeader()
{
	cout << "\n\t\t\t\t\t Users List" << endl;
	cout << "\n__________________________________________________________________________________________________\n"
		<< endl;
	cout << "|" << left << setw( 15 ) << "User Name ";
	cout << "|" << left << setw( 10 ) << "Password ";
	cout << "|" << left << setw( 40 ) << "Premissions ";

	cout << "\n__________________________________________________________________________________________________\n"
		<< endl;
}
void drowBalancesScreenHeader()
{
	cout << "\n\t\t\t\t\t Client List" << endl;
	cout << "\n__________________________________________________________________________________________________\n"
		<< endl;
	cout << "|" << left << setw( 15 ) << "Account Number ";
	cout << "|" << left << setw( 40 ) << "Name ";
	cout << "|" << left << setw( 12 ) << "Account Balance";
	cout << "\n__________________________________________________________________________________________________\n"
		<< endl;
}
void drowFooter()
{
	cout << "\n__________________________________________________________________________________________________\n"
		<< endl;
}
void performTransaction( enTransactions options );
short showTransactionsOptions();
short mainMenue() {
	system( "cls" ); // system("clear");
	short choice = 0;
	cout << "\n-------------------------------------------------------\n";
	cout << "\t\t\t MAIN MENUE\n";
	cout << "-------------------------------------------------------\n";
	cout << "\t[1]=> SHOW CLIENTS" << endl;
	cout << "\t[2]=> ADD NEW CLIENT" << endl;
	cout << "\t[3]=> SELETE CLIENT" << endl;
	cout << "\t[4]=> UPDATE CLIENT" << endl;
	cout << "\t[5]=> FIND CLIENT" << endl;
	cout << "\t[6]=> TRANSACTIONS" << endl;
	cout << "\t[7]=> MANAGE USERS" << endl;
	cout << "\t[8]=> LOGOUT";
	cout << "\n-------------------------------------------------------\n";
	cout << "Choose What You Want To Do From [1 - 8] ?: ";
	cin >> choice;
	return choice;

}
void backToMainMenue() {
	cout << "To Back To Main menue Press Any Key.." << endl;
	system( "pause" );
	pages( ( enOptions ) mainMenue() );
}
void backToTransactionsMenue() {
	cout << "To Back To Transactions menue Press Any Key.." << endl;
	system( "pause" );
	performTransaction( ( enTransactions ) showTransactionsOptions() );
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
stAccountData convertLineToRecord( string line , string seperator = "#//#" )
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
stUsers convertUserLineToRecord( string line , string seperator = "#//#" )
{
	stUsers user;
	vector<string> vUserData;

	vUserData = seperateString( line , seperator );

	user.userName = vUserData[ 0 ];
	user.password = vUserData[ 1 ];
	user.preimission = stoi( vUserData[ 2 ] );


	return user;
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
			clinet = convertLineToRecord( line );
			vRecord.push_back( clinet );
		}
		file.close();
	}
	return vRecord;
}
vector<stUsers> ReadUsersFileToVector( string fileName )
{
	vector<stUsers> vRecord;
	fstream file;
	file.open( fileName , ios::in );

	if ( file.is_open() )
	{
		string line;
		stUsers user;
		while ( getline( file , line ) )
		{
			user = convertUserLineToRecord( line );
			vRecord.push_back( user );
		}
		file.close();
	}
	return vRecord;
}
vector<stUsers> loadUsersFromFile( string fileName )
{
	vector<stUsers> vRecord;
	fstream file;
	file.open( fileName , ios::in );

	if ( file.is_open() )
	{
		string line;
		stUsers user;
		while ( getline( file , line ) )
		{
			user = convertUserLineToRecord( line );
			vRecord.push_back( user );
		}
		file.close();
	}
	return vRecord;
}
string convertDataToLineOfData( stAccountData& record , string seperator = " " )
{
	string stRescord = "";

	stRescord += record.accountNumber + seperator;
	stRescord += record.pinCode + seperator;
	stRescord += record.name + seperator;
	stRescord += record.phone + seperator;
	stRescord += to_string( record.accountBalance );

	return stRescord;
}
string convertUserDataToLineOfData( stUsers& record , string seperator = " " )
{
	string stRescord = "";

	stRescord += record.userName + seperator;
	stRescord += record.password + seperator;
	stRescord += to_string( record.preimission );
	return stRescord;
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
void WriteUserRecordToFile( string fileName , stUsers& record )
{
	fstream file;
	file.open( fileName , ios::out | ios::app );
	if ( file.is_open() )
	{

		file << convertUserDataToLineOfData( record , "#//#" ) << endl;

		file.close();
	}
}
vector<stAccountData> refreshFileAfterDeleteAccount( string fileName , stAccountData& clinet )
{
	vector<stAccountData> vRecord;
	fstream file;
	file.open( fileName , ios::in );

	if ( file.is_open() )
	{
		string line;
		while ( getline( file , line ) )
		{
			if ( clinet.deleteFlag == false )
			{
				clinet = convertLineToRecord( line , "#//#" );
				vRecord.push_back( clinet );
			}
		}
		file.close();
	}
	return vRecord;
}
vector<stUsers> refreshUsersFileAfterDeleteAccount( string fileName , stUsers& user )
{
	vector<stUsers> vRecord;
	fstream file;
	file.open( fileName , ios::in );

	if ( file.is_open() )
	{
		string line;
		while ( getline( file , line ) )
		{
			if ( user.deleteFlag == false )
			{
				user = convertUserLineToRecord( line , "#//#" );
				vRecord.push_back( user );
			}
		}
		file.close();
	}
	return vRecord;
}
void printClientData( stAccountData& client ) {
	cout << "|" << left << setw( 15 ) << client.accountNumber;
	cout << "|" << left << setw( 10 ) << client.pinCode;
	cout << "|" << left << setw( 40 ) << client.name;
	cout << "|" << left << setw( 12 ) << client.phone;
	cout << "|" << left << setw( 12 ) << client.accountBalance;
	cout << endl;
}
void printUserData( stUsers& user ) {
	cout << "|" << left << setw( 15 ) << user.userName;
	cout << "|" << left << setw( 10 ) << user.password;
	cout << "|" << left << setw( 10 ) << user.preimission;
	cout << endl;
}
void printBalancesData( stAccountData& client )
{
	cout << "|" << left << setw( 15 ) << client.accountNumber;
	cout << "|" << left << setw( 40 ) << client.name;
	cout << "|" << left << setw( 12 ) << client.accountBalance;
	cout << endl;
}
void showClientsData( vector<stAccountData> vClients ) {

	for ( stAccountData& cl : vClients )
	{
		printClientData( cl );
	}
}
void showUsersData( vector<stUsers> vUsers ) {

	for ( stUsers& u : vUsers )
	{
		printUserData( u );
	}
}
void showBalancessData( vector<stAccountData> vClients )
{

	for ( stAccountData& cl : vClients )
	{
		printBalancesData( cl );
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
bool findUserByUserName( vector<stUsers>& vUsers , stUsers& user , string userName )
{
	for ( stUsers& cl : vUsers )
	{
		if ( cl.userName == userName )
		{
			user = cl; // if we find the account number we fill the client struct and return
			return true;
		}
	}
	return false;
}
bool checkIfClientAccountNumberIsAlreadyTaken( string accountNumber , string flieName ) {
	vector <stAccountData> vClients;
	fstream file;
	file.open( flieName , ios::in ); // open file in read mode

	if ( file.is_open() )
	{
		string line;
		stAccountData client;

		while ( getline( file , line ) )
		{
			client = convertLineToRecord( line );
			if ( client.accountNumber == accountNumber )
			{
				file.close();
				return true;
			}
			vClients.push_back( client );
		}
		file.close();
	}
	return false;
}
bool checkIfUserAccountNameIsAlreadyTaken( string accountName , string flieName ) {
	vector <stUsers> vUsers;
	fstream file;
	file.open( flieName , ios::in ); // open file in read mode

	if ( file.is_open() )
	{
		string line;
		stUsers user;

		while ( getline( file , line ) )
		{
			user = convertUserLineToRecord( line );
			if ( user.userName == accountName )
			{
				file.close();
				return true;
			}
			vUsers.push_back( user );
		}
		file.close();
	}
	return false;
}
bool checkIfUserNameAndPasswordIsCorrect( string userName , string password , stUsers& user ) {

	vector <stUsers> vUsers = loadUsersFromFile( UsersFile );
	for ( stUsers& u : vUsers ) {
		if ( u.userName == userName && u.password == password )
		{
			user = u;
			return true;
		}
	}
	return false;
}
vector<stAccountData> saveClientsDataToFileAfterDelete( string fileName , vector<stAccountData>& vClients )
{
	fstream file;
	file.open( fileName , ios::out ); // overwrite
	string line;
	if ( file.is_open() )
	{
		for ( stAccountData& cl : vClients )
		{
			if ( cl.deleteFlag == false )
			{
				WriteRecordToFile( "clinet_Data_File.txt" , cl );
			}
		}
		file.close();
	}
	return vClients;
}
vector<stUsers> saveUsersDataToFileAfterDelete( string fileName , vector<stUsers>& vUsers )
{
	fstream file;
	file.open( fileName , ios::out ); // overwrite
	string line;
	if ( file.is_open() )
	{
		for ( stUsers& cl : vUsers )
		{
			if ( cl.deleteFlag == false )
			{
				WriteUserRecordToFile( UsersFile , cl );
			}
		}
		file.close();
	}
	return vUsers;
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
			WriteRecordToFile( "clinet_Data_File.txt" , cl );
		}
		file.close();
	}
	return vClients;
}
vector<stUsers> saveUsersDataToFileAfterUpdate( string fileName , vector<stUsers>& vUsers )
{
	fstream file;
	file.open( fileName , ios::out ); // overwrite
	string line;
	if ( file.is_open() )
	{
		for ( stUsers& cl : vUsers )
		{
			WriteUserRecordToFile( UsersFile , cl );
		}
		file.close();
	}
	return vUsers;
}
void readRecordToFile( stAccountData& stRecord )
{

	stRecord = readRecord();
	WriteRecordToFile( ClientsFile , stRecord );
}
void readUserRecordToFile( stUsers& stRecord )
{

	stRecord = readUserRecord();
	WriteUserRecordToFile( UsersFile , stRecord );
}
void deleteClients( vector<stAccountData>& vClients , stAccountData& client , string accuontNumberToDelete )
{

	for ( stAccountData& cl : vClients )
	{
		if ( cl.accountNumber == accuontNumberToDelete )
		{
			cl.deleteFlag = true;
			saveClientsDataToFileAfterDelete( "clinet_Data_File.txt" , vClients );
			break;
		}
	}
	// refresh the clients
	vClients = refreshFileAfterDeleteAccount( "clinet_Data_File.txt" , client );
}
void deleteUserData( vector<stUsers>& vUsers , stUsers& user , string userNameToDelete )
{

	for ( stUsers& cl : vUsers )
	{
		if ( cl.userName == userNameToDelete )
		{
			cl.deleteFlag = true;
			saveUsersDataToFileAfterDelete( UsersFile , vUsers );
			break;
		}
	}
	// refresh the clients
	vUsers = refreshUsersFileAfterDeleteAccount( UsersFile , user );
}
void updateClients( vector<stAccountData>& vClients , stAccountData& client , string accountNumber )
{
	stAccountData updatedClient = readToUpdateRecord();

	for ( stAccountData& cl : vClients )
	{
		if ( cl.accountNumber == accountNumber )
		{
			cl.name = updatedClient.name;
			cl.pinCode = updatedClient.pinCode;
			cl.phone = updatedClient.phone;
			cl.accountBalance = updatedClient.accountBalance;
			saveClientsDataToFileAfterUpdate( ClientsFile , vClients );
			break;
		}
	}
}
void updateUser( vector<stUsers>& vUsers , stUsers& user , string accountName )
{
	stUsers updatedUser = readToUpdateUserRecord();

	for ( stUsers& cl : vUsers )
	{
		if ( cl.userName == accountName )
		{
			cl.userName = updatedUser.userName;
			cl.password = updatedUser.password;
			cl.preimission = updatedUser.preimission;
			saveUsersDataToFileAfterUpdate( UsersFile , vUsers );
			break;
		}
	}
}
void showClients() {
	if ( !chechPremissions( enPremissions::pListClients ) )
	{
		cout << "Access Denied,,\n Please Contact Your Admin..\n\n" << endl;
		return;
	}
	vector<stAccountData> vClients = ReadFileToVector( ClientsFile );
	drowHeader();
	showClientsData( vClients );
	drowFooter();
}
void showUserss() {
	vector<stUsers> vUsers = ReadUsersFileToVector( UsersFile );
	drowUsersHeader();
	showUsersData( vUsers );
	drowFooter();
}
void addClient() {
	if ( !chechPremissions( enPremissions::pAddNewClint ) )
	{
		cout << "Access Denied,,\n Please Contact Your Admin..\n\n" << endl;
		return;
	}

	stAccountData stRecord;
	char more = 'y';

	// Insert Clients Data
	do
	{
		system( "cls" );
		cout << "Enter Client Data: \n";

		readRecordToFile( stRecord );

		cout << "Do You Want To Add Other Rcords? : y => yes | n => no : ";
		cin >> more;
	} while ( more == 'y' || more == 'Y' );


}
void addUser() {
	stUsers stRecord;
	char more = 'y';

	// Insert Clients Data
	do
	{
		system( "cls" );
		cout << "Enter User Data: \n";

		readUserRecordToFile( stRecord );

		cout << "Do You Want To Add Other User? : y => yes | n => no : ";
		cin >> more;
	} while ( more == 'y' || more == 'Y' );
}
void findClient() {
	if ( !chechPremissions( enPremissions::pFindClients ) )
	{
		cout << "Access Denied,,\n Please Contact Your Admin..\n\n" << endl;
		return;
	}
	showClients();
	vector<stAccountData> vClients = ReadFileToVector( "clinet_Data_File.txt" );
	stAccountData client;
	string accountToFind = "";
	cout << "Do You Want To Search For Client? ";
	getline( cin >> ws , accountToFind );
	if ( findClientByAccountNumber( vClients , client , accountToFind ) )
	{

		drowHeader();
		printClientData( client );
		drowFooter();
	}
	else
	{
		cout << "No Account With That Number.." << endl;
	}
}
void findUser() {

	showUserss();
	vector<stUsers> vUsers = ReadUsersFileToVector( UsersFile );
	stUsers user;
	string UserNameToFind = "";
	cout << "Do You Want To Search For User? ";
	getline( cin >> ws , UserNameToFind );
	if ( findUserByUserName( vUsers , user , UserNameToFind ) )
	{

		drowHeader();
		printUserData( user );
		drowFooter();
	}
	else
	{
		cout << "No User With That Name.." << endl;
	}
}
void deleteClient() {
	if ( !chechPremissions( enPremissions::pDeleteClient ) )
	{
		cout << "Access Denied,,\n Please Contact Your Admin..\n\n" << endl;
		return;
	}
	showClients();
	vector <stAccountData> vClients = ReadFileToVector( "clinet_Data_File.txt" );
	string accountToFind = "";
	string accountNumberToDelete;
	stAccountData client;
	cout << "Enter An Account Number To Delete: ";
	getline( cin >> ws , accountNumberToDelete );
	if ( findClientByAccountNumber( vClients , client , accountNumberToDelete ) )
	{
		system( "cls" );
		drowHeader();
		printClientData( client );
		drowFooter();
		char del;
		cout << "Are You Sure You Want to delete " << client.name << " ?";
		cin >> del;
		if ( del == 'y' || del == 'Y' )
		{
			deleteClients( vClients , client , accountNumberToDelete );
			cout << "The Account Deleted Succsessfuly.." << endl;
		}
	}
	else
	{
		cout << "No Account With This " << accountNumberToDelete << "Number.." << endl;
	}

}
void deleteUser() {

	showUserss();
	vector <stUsers> vUsers = ReadUsersFileToVector( UsersFile );
	string accountToFind = "";
	string accountNameToDelete;
	stUsers user;
	cout << "Enter An Account Name To Delete: ";
	getline( cin >> ws , accountNameToDelete );
	if ( findUserByUserName( vUsers , user , accountNameToDelete ) )
	{
		system( "cls" );
		drowHeader();
		printUserData( user );
		drowFooter();
		char del;
		cout << "Are You Sure You Want to delete " << user.userName << " ?";
		cin >> del;
		if ( del == 'y' || del == 'Y' )
		{
			deleteUserData( vUsers , user , accountNameToDelete );
			cout << "The Account Deleted Succsessfuly.." << endl;
		}
	}
	else
	{
		cout << "No Account With This " << accountNameToDelete << "Name.." << endl;
	}

}
void updateClient() {
	if ( !chechPremissions( enPremissions::pUpdateClients ) )
	{
		cout << "Access Denied,,\n Please Contact Your Admin..\n\n" << endl;
		return;
	}
	showClients();
	vector<stAccountData> vClients = ReadFileToVector( "clinet_Data_File.txt" );
	stAccountData client;
	string accountToFind = "";
	cout << "Do You Want To Search For Client? ";
	getline( cin >> ws , accountToFind );
	if ( findClientByAccountNumber( vClients , client , accountToFind ) )
	{
		system( "cls" );
		drowHeader();
		printClientData( client );
		drowFooter();
		// update Client
		char updateOrNot;
		cout << "Do you Want To Update Client (" << client.name << ") ?";
		cin >> updateOrNot;
		if ( updateOrNot == 'Y' || updateOrNot == 'y' )
		{
			updateClients( vClients , client , accountToFind );
		}
	}
	else
	{
		cout << "No Account With That Number.." << endl;
	}

}
void updateUser() {

	showUserss();
	vector<stUsers> vUserss = ReadUsersFileToVector( UsersFile );
	stUsers user;
	string accountToFind = "";
	cout << "Do You Want To Search For User? ";
	getline( cin >> ws , accountToFind );
	if ( findUserByUserName( vUserss , user , accountToFind ) )
	{
		system( "cls" );
		drowHeader();
		printUserData( user );
		drowFooter();
		// update Client
		char updateOrNot;
		cout << "Do you Want To Update User (" << user.userName << ") ?";
		cin >> updateOrNot;
		if ( updateOrNot == 'Y' || updateOrNot == 'y' )
		{
			updateUser( vUserss , user , accountToFind );
		}
	}
	else
	{
		cout << "No Account With That Name.." << endl;
	}

}
short showTransactionsOptions() {
	if ( !chechPremissions( enPremissions::pTransactions ) )
	{
		cout << "Access Denied,,\n Please Contact Your Admin..\n\n" << endl;
	}
	system( "cls" ); // system("clear");
	short choice = 0;
	cout << "\n-------------------------------------------------------\n";
	cout << "\t\t Transactions Screen\n";
	cout << "-------------------------------------------------------\n";
	cout << "\t[1]=> Deposit" << endl;
	cout << "\t[2]=> Withdrow" << endl;
	cout << "\t[3]=> TotalBalance" << endl;
	cout << "\t[4]=> Main Menue";
	cout << "\n-------------------------------------------------------\n";
	cout << "Choose What You Want To Do From [1 - 4] ?: ";
	cin >> choice;
	return choice;


}
void Deposit() {
	showClients();
	vector<stAccountData> vClients = ReadFileToVector( "clinet_Data_File.txt" );
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
			saveClientsDataToFileAfterUpdate( "clinet_Data_File.txt" , vClients );
			break;
		}
	}
}
void WithDrow() {
	showClients();
	vector<stAccountData> vClients = ReadFileToVector( "clinet_Data_File.txt" );
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
			saveClientsDataToFileAfterUpdate( "clinet_Data_File.txt" , vClients );
			break;
		}
	}

}
void TotalBalance() {
	vector<stAccountData> vClients = ReadFileToVector( "clinet_Data_File.txt" );
	drowBalancesScreenHeader();
	showBalancessData( vClients );
	drowFooter();
}
void performTransaction( enTransactions options ) {
	switch ( options )
	{
	case enTransactions::deposit:
		Deposit();
		backToTransactionsMenue();
		break;
	case enTransactions::withdrow:
		WithDrow();
		backToTransactionsMenue();
		break;
	case enTransactions::totalBalance:
		TotalBalance();
		backToTransactionsMenue();
		break;
	case enTransactions::MainMenue:
		mainMenue();
		backToMainMenue();
		break;
	}
}
bool loadUser( string userName , string password ) {
	if ( checkIfUserNameAndPasswordIsCorrect( userName , password , UserAccount ) )
	{
		return true;
	}
	else
	{
		return false;
	}
}
//////////////users///////////////////
bool chechPremissions( enPremissions premission ) {
	if ( UserAccount.preimission == enPremissions::eAll )
	{
		return true;
	}
	if ( ( premission & UserAccount.preimission ) == premission )
	{
		return true;
	}
	else
	{
		return false;
	}
}
void screens( enManagUsersOptions choice );
void login() {
	bool loginFlag = false;
	string userName = "";
	string password = "";
	do
	{
		system( "cls" ); // system("clear");
		cout << "\n-------------------------------------------------------\n";
		cout << "\t\t\t LOGIN PAGE\n";
		cout << "-------------------------------------------------------\n";
		if ( loginFlag )
		{
			cout << "Invalid Username Or Password.." << endl;
		}
		cout << "Enter User Name: ";
		getline( cin >> ws , userName );
		cout << "Enter Password: ";
		getline( cin >> ws , password );

		loginFlag = !loadUser( userName , password );
	} while ( loginFlag );
	pages( ( enOptions ) mainMenue() );
}
short manageUsersScreen() {
	if ( UserAccount.preimission == enPremissions::eAll || UserAccount.preimission == enPremissions::pManagUsers )
	{
		system( "cls" ); // system("clear");
		short choice = 0;
		cout << "\n-------------------------------------------------------\n";
		cout << "\t\t\t MANAGE USERS MENUE SCREEN\n";
		cout << "-------------------------------------------------------\n";
		cout << "\t[1]=> SHOW USERS" << endl;
		cout << "\t[2]=> ADD NEW USERS" << endl;
		cout << "\t[3]=> DELETE USERS" << endl;
		cout << "\t[4]=> UPDATE USERS" << endl;
		cout << "\t[5]=> FIND USERS" << endl;
		cout << "\t[6]=> TRANSACTIONS" << endl;
		cout << "\t[7]=> BACK TO MAIN MENUE";
		cout << "\n-------------------------------------------------------\n";
		cout << "Choose What You Want To Do From [1 - 7] ?: ";
		cin >> choice;
		return choice;
	}
	else
	{
		cout << "Access Denied ,, \nPlease Contact Your Admin..\n\n" << endl;
		return 0;
	}

}
void backToManageUsersMainMenue() {
	cout << "To Back To Manage Users menue Press Any Key.." << endl;
	system( "pause" );
	screens( ( enManagUsersOptions ) manageUsersScreen() );
}
void screens( enManagUsersOptions choice ) {
	switch ( choice )
	{
	case enManagUsersOptions::ShowUers:
		system( "cls" );
		showUserss();
		backToManageUsersMainMenue();
		break;
	case enManagUsersOptions::AddUser:
		system( "cls" );
		addUser();
		backToManageUsersMainMenue();
		break;
	case enManagUsersOptions::DeleteUser:
		system( "cls" );
		deleteUser();
		backToManageUsersMainMenue();
		break;
	case enManagUsersOptions::UpdateUser:
		system( "cls" );
		updateUser();
		backToManageUsersMainMenue();
		break;
	case enManagUsersOptions::FindUser:
		system( "cls" );
		findUser();
		backToManageUsersMainMenue();
		break;
	case enManagUsersOptions::Transactions:
		system( "cls" );
		performTransaction( ( enTransactions ) showTransactionsOptions() );
		break;
	case enManagUsersOptions::BackToMAinMenue:
		backToMainMenue();
		break;

	}
}
void pages( enOptions choice ) {
	switch ( choice )
	{
	case enOptions::showList:
		system( "cls" );
		showClients();
		backToMainMenue();
		//cout << "ShowPage";
		break;
	case enOptions::addList:
		system( "cls" );
		addClient();
		backToMainMenue();
		//cout << "AddPage";
		break;
	case enOptions::deletList:
		system( "cls" );
		deleteClient();
		backToMainMenue();
		//cout << "deleetePage";
		break;
	case enOptions::updateList:
		system( "cls" );
		updateClient();
		backToMainMenue();
		//cout << "updatePage";
		break;
	case enOptions::findList:
		system( "cls" );
		findClient();
		backToMainMenue();
		//cout << "findPage";
		break;
	case enOptions::transactions:
		system( "cls" );
		performTransaction( ( enTransactions ) showTransactionsOptions() );
		break;
	case enOptions::ManaguUsers:
		system( "cls" );
		screens( ( enManagUsersOptions ) manageUsersScreen() );
		break;
	case enOptions::Logout:
		system( "cls" );
		exit;
	}
}

int main()
{
	login();
	return 0;
}