#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

const string ClientsFileName = "Clients.txt";
const string UserFile = "User.txt";

void ShowMainMenue();
void ShowTransactionsMenue();
void PerfromMainMenueOption();
void PerfromManageMenueOption();
void ManageUserSecreen();
void Login();

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};
struct sUser
{
    string UserName;
    string PassWord;
    int Permissions;
    bool MarkForDelete = false;
};
sUser CurrentUser;

enum enTransactionsMenueOptions
{
    eDeposit = 1,
    eWithdraw = 2,
    eShowTotalBalance = 3,
    eShowMainMenue = 4
};
enum enMainMenueOptions
{
    eListClients = 1,
    eAddNewClient = 2,
    eDeleteClient = 3,
    eUpdateClient = 4,
    eFindClient = 5,
    eShowTransactionsMenue = 6,
    eShowManageUserMenue = 7,
    eLogOut = 8
};
enum enMainUsersManue
{
    eListUser = 1,
    eAddNewUser = 2,
    eDeleteUser = 3,
    eUpdateUser = 4,
    eFindUser = 5,
    eMainMune = 6
};
enum enMainMenuePermissions
{
    eAll = -1,
    eListUserPermissions = 2,
    eAddNewUserPermissions = 4,
    eDeleteUserPermissions = 8,
    eUpdateUserPermissions = 16,
    eTransactionsPermissions = 32,
    eFindUserPermissions = 64,

};
vector<string> SplitString(string S1, string Delim)
{

    vector<string> vString;

    short pos = 0;
    string sWord;

    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos);
        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        S1.erase(0, pos + Delim.length());
    }

    if (S1 != "")
    {
        vString.push_back(S1);
    }

    return vString;
}

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{

    sClient Client;
    vector<string> vClientData;

    vClientData = SplitString(Line, Seperator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);

    return Client;
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{

    string stClientRecord = "";

    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{

    vector<sClient> vClients;

    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {

        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {

            Client = ConvertLinetoRecord(Line);
            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }

            vClients.push_back(Client);
        }

        MyFile.close();
    }

    return false;
}

sClient ReadNewClient()
{
    sClient Client;

    cout << "Enter Account Number? ";

    getline(cin >> ws, Client.AccountNumber);

    while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
    {
        cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, Client.AccountNumber);
    }

    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;
}

vector<sClient> LoadCleintsDataFromFile(string FileName)
{
    vector<sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);
    if (MyFile.is_open())
    {
        string Line;
        while (getline(MyFile, Line))
        {

            if (Line != "")
            {
                sClient Client = ConvertLinetoRecord(Line);
                vClients.push_back(Client);
            }
        }
        MyFile.close();
    }
    return vClients;
}

void PrintClientRecordLine(sClient Client)
{

    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintClientRecordBalanceLine(sClient Client)
{

    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void ShowAllClientsScreen()
{

    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (sClient Client : vClients)
        {

            PrintClientRecordLine(Client);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
}

void ShowTotalBalances()
{

    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;

    double TotalBalances = 0;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (sClient Client : vClients)
        {

            PrintClientRecordBalanceLine(Client);
            TotalBalances += Client.AccountBalance;

            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
    cout << "\t\t\t\t\t   Total Balances = " << TotalBalances;
}

void PrintClientCard(sClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code     : " << Client.PinCode;
    cout << "\nName         : " << Client.Name;
    cout << "\nPhone        : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
    cout << "\n-----------------------------------\n";
}

bool FindClientByAccountNumber(string AccountNumber, vector<sClient> vClients, sClient &Client)
{

    for (sClient C : vClients)
    {

        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

sClient ChangeClientRecord(string AccountNumber)
{
    sClient Client;

    Client.AccountNumber = AccountNumber;

    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<sClient> &vClients)
{

    for (sClient &C : vClients)
    {

        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }
    }

    return false;
}

vector<sClient> SaveCleintsDataToFile(string FileName, vector<sClient> vClients)
{

    fstream MyFile;
    MyFile.open(FileName, ios::out); // overwrite

    string DataLine;

    if (MyFile.is_open())
    {

        for (sClient C : vClients)
        {

            if (C.MarkForDelete == false)
            {
                // we only write records that are not marked for delete.
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }
        }

        MyFile.close();
    }

    return vClients;
}

void AddDataLineToFile(string FileName, string stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {

        MyFile << stDataLine << endl;

        MyFile.close();
    }
}

void AddNewClient()
{
    sClient Client;
    Client = ReadNewClient();
    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
}

void AddNewClients()
{
    char AddMore = 'Y';
    do
    {
        system("cls");
        cout << "Adding New Client:\n\n";

        AddNewClient();
        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";

        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');
}

bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient> &vClients)
{

    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);

        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveCleintsDataToFile(ClientsFileName, vClients);

            vClients = LoadCleintsDataFromFile(ClientsFileName);

            cout << "\n\nClient Deleted Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }
}

bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient> &vClients)
{

    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);
        cout << "\n\nAre you sure you want update this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {

            for (sClient &C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }

            SaveCleintsDataToFile(ClientsFileName, vClients);

            cout << "\n\nClient Updated Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }
}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector<sClient> &vClients)
{
    char Answer = 'n';

    cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        for (sClient &C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Amount;
                SaveCleintsDataToFile(ClientsFileName, vClients);

                cout << "\n\nDone Successfully. New balance is: "
                     << C.AccountBalance;

                return true;
            }
        }

        return false;
    }

    return false;
}

string ReadClientAccountNumber()
{
    string AccountNumber = "";

    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;
}

void ShowDeleteClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n";

    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClients);
}

void ShowUpdateClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Info Screen";
    cout << "\n-----------------------------------\n";

    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);
}

void ShowAddNewClientsScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n-----------------------------------\n";

    AddNewClients();
}

void ShowFindClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n-----------------------------------\n";

    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    sClient Client;
    string AccountNumber = ReadClientAccountNumber();
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
        PrintClientCard(Client);
    else
        cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";
}

void ShowEndScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tProgram Ends :-)";
    cout << "\n-----------------------------------\n";
}

void ShowDepositScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n-----------------------------------\n";

    sClient Client;

    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();

    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }

    PrintClientCard(Client);

    double Amount = 0;
    cout << "\nPlease enter deposit amount? ";
    cin >> Amount;

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);
}

void ShowWithDrawScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tWithdraw Screen";
    cout << "\n-----------------------------------\n";

    sClient Client;

    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();

    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }

    PrintClientCard(Client);

    double Amount = 0;
    cout << "\nPlease enter withdraw amount? ";
    cin >> Amount;

    while (Amount > Client.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
        cout << "Please enter another amount? ";
        cin >> Amount;
    }

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);
}

void ShowTotalBalancesScreen()
{

    ShowTotalBalances();
}

void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowMainMenue();
}
void GoBackToTransactionsMenue()
{
    cout << "\n\nPress any key to go back to Transactions Menue...";
    system("pause>0");
    ShowTransactionsMenue();
}
short ReadTransactionsMenueOption()
{
    cout << "Choose what do you want to do? [1 to 4]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

void PerfromTranactionsMenueOption(enTransactionsMenueOptions TransactionMenueOption)
{
    switch (TransactionMenueOption)
    {
    case enTransactionsMenueOptions::eDeposit:
    {
        system("cls");
        ShowDepositScreen();
        GoBackToTransactionsMenue();
        break;
    }

    case enTransactionsMenueOptions::eWithdraw:
    {
        system("cls");
        ShowWithDrawScreen();
        GoBackToTransactionsMenue();
        break;
    }

    case enTransactionsMenueOptions::eShowTotalBalance:
    {
        system("cls");
        ShowTotalBalancesScreen();
        GoBackToTransactionsMenue();
        break;
    }

    case enTransactionsMenueOptions::eShowMainMenue:
    {

        ShowMainMenue();
    }
    }
}

void ShowTransactionsMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tTransactions Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances.\n";
    cout << "\t[4] Main Menue.\n";
    cout << "===========================================\n";
    PerfromTranactionsMenueOption((enTransactionsMenueOptions)ReadTransactionsMenueOption());
}

short ReadMainMenueOption()
{
    cout << "Choose what do you want to do? [1 to 8]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

void PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
{

    switch (MainMenueOption)
    {
    case enMainMenueOptions::eListClients:
    {
        system("cls");
        ShowAllClientsScreen();
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOptions::eAddNewClient:
        system("cls");
        ShowAddNewClientsScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eDeleteClient:
        system("cls");
        ShowDeleteClientScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eUpdateClient:
        system("cls");
        ShowUpdateClientScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eFindClient:
        system("cls");
        ShowFindClientScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eShowTransactionsMenue:
        system("cls");
        ShowTransactionsMenue();
        break;
    case enMainMenueOptions::eShowManageUserMenue:
    {
        system("cls");
        ManageUserSecreen();
        break;
    }
    case enMainMenueOptions::eLogOut:
        Login();
        break;
    }
}
void ShowMainMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Manag User \n";
    cout << "\t[8] login.\n";
    cout << "===========================================\n";
    PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}
//  EXTENSION 2 ---------------------------------------------------
sUser ReadUserInfo()
{
    sUser User;

    cout << "Enter UserName :";
    getline(cin >> ws, User.UserName);

    cout << "Enter PassWord :";
    getline(cin, User.PassWord);

    return User;
}
sUser ConvertUserLineToRecord(string Line, string Seperator = "#//#")
{
    sUser User;
    vector<string> vUserData = SplitString(Line, Seperator);

    if (vUserData.size() >= 3)
    {
        User.UserName = vUserData[0];
        User.PassWord = vUserData[1];
        User.Permissions = stoi(vUserData[2]);
    }

    return User;
}
string ConvertUserReacordToLine(sUser User, string Seperator = "#//#")
{
    string Line = "";
    Line = User.UserName + Seperator;
    Line += User.PassWord + Seperator;
    Line += to_string(User.Permissions);
    return Line;
}
vector<sUser> LoadUserDataFromFile(string FileName)
{
    vector<sUser> vUsers;
    fstream Myfile;
    Myfile.open(FileName, ios::in);
    if (Myfile.is_open())
    {
        string Line;
        sUser User;
        while (getline(Myfile, Line))
        {
            User = ConvertUserLineToRecord(Line);
            vUsers.push_back(User);
        }
        Myfile.close();
    }
    return vUsers;
}
short ReadManagUserMenueOption()
{
    cout << "Choose what do you want to do? [1 to 6]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}
// Permissions Access ----------------------------------------------------------
bool CheckAccessPermissions(enMainMenuePermissions Permissions)
{
    if (CurrentUser.Permissions == enMainMenuePermissions::eAll)
    {
        return true;
    }
    if ((Permissions & CurrentUser.Permissions) == Permissions)
    {
        return true;
    }
    return false;
}
int ReadPermissionsToset()
{
    int Permissions = 0;
    char Answer = 'n';

    cout << "\nDo you want to give full access? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        return -1;
    }

    cout << "\nDo you want to give access to : \n ";

    cout << "\nShow Client List? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {

        Permissions += enMainMenuePermissions::eListUserPermissions;
    }

    cout << "\nAdd New Client? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::eAddNewUserPermissions;
    }

    cout << "\nDelete Client? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::eDeleteUserPermissions;
    }

    cout << "\nUpdate Client? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::eUpdateUserPermissions;
    }

    cout << "\nFind Client? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::eFindUserPermissions;
    }
    return Permissions;
}
void ShowAccessDeniedMessage()
{
   
    cout << "-----------------------------------------------" << endl;
    cout << "Access Denied, \nYou don't Have Permission To Do this,\nPlease Contact Your Admin." << endl;
    cout << "-----------------------------------------------" << endl;
}

// Login ----------------------------------------------------------------
void showLoginSecreen()
{
    cout << "--------------------------------" << endl;
    cout << "         Login Secreen          " << endl;
    cout << "--------------------------------" << endl;
}
bool FindUserByUserNameAndPassWord(string UserName, string PassWord, sUser &User)
{
    vector<sUser> VUsers = LoadUserDataFromFile(UserFile);
    for (sUser &U : VUsers)
    {
        if (U.UserName == UserName && U.PassWord == PassWord)
        {
            User = U;
            return true;
        }
    }
    return false;
}
bool LodeUserInfo(string UserName, string PassWord)
{
    if (FindUserByUserNameAndPassWord(UserName, PassWord, CurrentUser))
    {
        return true;
    }
    return false;
}
void Login()
{
    bool LoginFaled = false;
    sUser User;
    do
    {
        system("cls");
        showLoginSecreen();
        if (LoginFaled)
        {
            cout << "Invaled UserName/PassWord !" << endl;
        }
        User = ReadUserInfo();
        LoginFaled = !LodeUserInfo(User.UserName, User.PassWord);
    } while (LoginFaled);
    ShowMainMenue();
}
// Manage Users -------------------------------------------------------------
void ShowManageUserSecreen()
{
    cout << "============================" << endl;
    cout << "      Manage Users Main    " << endl;
    cout << "============================" << endl;
    cout << "       [1]Lise User         " << endl;
    cout << "       [2]Add New User      " << endl;
    cout << "       [3]Delete User       " << endl;
    cout << "       [4]Update User       " << endl;
    cout << "       [5]Find User         " << endl;
    cout << "       [6]Main Menue        " << endl;
}
short ReadManageUserMainChose()
{
    short Chose;
    cout << "Chose what do want ? [1-6] " << endl;
    cin >> Chose;
    return Chose;
}
// List User -------------------------------------------------------------------
void PrintUserCard(sUser User)
{
    cout << "\nThe following are the User details:\n";
    cout << "-----------------------------------";
    cout << "\nUserName : " << User.UserName;
    cout << "\nPassword : " << User.PassWord;
    cout << "\nPermissions: " << User.Permissions;
    cout << "\n-----------------------------------\n";
}
void ShowAllUserScreen()
{
     if (!CheckAccessPermissions(enMainMenuePermissions::eListUserPermissions))
     {
        ShowAccessDeniedMessage ();
        return;
    }
     
    vector<sUser> vUser = LoadUserDataFromFile(UserFile);

    cout << "\n\t\t\t\t\tUser List (" << vUser.size() << ") User(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;

    cout << "| " << left << setw(15) << "UserName";
    cout << "| " << left << setw(10) << "PassWord";
    cout << "| " << left << setw(40) << "Permissions";

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;

    if (vUser.size() == 0)
        cout << "\t\t\t\tNo User Available In the System!";
    else

        for (sUser U : vUser)
        {

            cout << "| " << left << setw(15) << U.UserName;
            cout << "| " << left << setw(10) << U.PassWord;
            cout << "| " << left << setw(40) << U.Permissions;
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
}
// Add New User -----------------------------------------------------------------
bool UserExistsByUsername(string Username, string FileName)
{

    fstream MyFile;
    MyFile.open(FileName, ios::in); 

    if (MyFile.is_open())
    {

        string Line;
        sUser User;

        while (getline(MyFile, Line))
        {

            User = ConvertUserLineToRecord(Line);
            if (User.UserName == Username)
            {
                MyFile.close();
                return true;
            }
        }

        MyFile.close();
    }

    return false;
}
sUser ReadNewUserInfo()
{
    sUser User;

    cout << "Enter Username? ";

    getline(cin >> ws, User.UserName);

    while (UserExistsByUsername(User.UserName, UserFile))
    {
        cout << "\nUser with [" << User.UserName << "] already exists, Enter another Username? ";
        getline(cin >> ws, User.UserName);
    }

    cout << "Enter Password? ";
    getline(cin, User.PassWord);

    User.Permissions = ReadPermissionsToset();

    return User;
}
void showAddNewUserSecreen()
{
    cout << "--------------------------------" << endl;
    cout << "         Add New User           " << endl;
    cout << "--------------------------------" << endl;
}
void AddUserDataToFile(string FileName, string DataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);
    if (MyFile.is_open())
    {
        MyFile << DataLine << endl;
        MyFile.close();
    }
}
void AddNewUser()
{
    sUser User = ReadNewUserInfo();
    AddUserDataToFile(UserFile, ConvertUserReacordToLine(User));
}
void AddNewUsers()
{
    if (!CheckAccessPermissions(enMainMenuePermissions::eAddNewUserPermissions))
     {
        ShowAccessDeniedMessage ();
        return;
    }
    char AddMore = 'y';

    do
    {
        system("cls");
        showAddNewUserSecreen();
        cout << "Adding New User:\n\n";
        AddNewUser();
        cout << "\nUser Added Successfully, do you want to add more User? Y/N? ";

        cin >> AddMore;
        cin.ignore();
    } while (tolower(AddMore) == 'y');
}
// Delete User -----------------------------------------------------------------------
void ShowDeleteUserSecreen()
{
    cout << "--------------------------------" << endl;
    cout << "         Delete User           " << endl;
    cout << "--------------------------------" << endl;
}
bool MarkUserForDelete(string UserName, string PassWord, vector<sUser> &VUsers)
{
    for (sUser &U : VUsers)
    {
        if (U.UserName == UserName && U.PassWord == PassWord)
        {
            U.MarkForDelete = true;
            return true;
        }
    }
    return false;
}
vector<sUser> SaveUsersToFile(string FileName, vector<sUser> VUsers)
{
    fstream Myfile;
    Myfile.open(FileName, ios::out);
    if (Myfile.is_open())
    {
        string Line = "";
        for (sUser &U : VUsers)
        {
            if (U.MarkForDelete == false)
            {
                Line = ConvertUserReacordToLine(U);
                Myfile << Line << endl;
                Line = "";
            }
        }
        Myfile.close();
    }
    return VUsers;
}
bool DeleteUserByUserNameAndPassWord(string UserName, string PassWord, vector<sUser> &vUsers)
{

    sUser User;
    char Answer = 'n';
     if (UserName=="Admin")
     {
        cout<<"Can't delete this user !"<<endl;
        return false;
     }
     
    if (FindUserByUserNameAndPassWord(UserName, PassWord, User))
    {

        PrintUserCard(User);

        cout << "\n\nAre you sure you want delete this User? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkUserForDelete(UserName, PassWord, vUsers);
            vUsers = SaveUsersToFile(UserFile, vUsers);

            cout << "\n\nUser Deleted Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with UserName (" << UserName << ") is Not Found!";
        return false;
    }
}
void DeleteUser()
{
if (!CheckAccessPermissions(enMainMenuePermissions::eDeleteUserPermissions))
     {
        ShowAccessDeniedMessage ();
        return;
    }
    ShowDeleteUserSecreen();
    sUser User = ReadUserInfo();
    vector<sUser> vUsers = LoadUserDataFromFile(UserFile);
    DeleteUserByUserNameAndPassWord(User.UserName, User.PassWord, vUsers);
}
// UPDATE User ----------------------------------------------------------------------------
void ShowUpDateUserSecreen()
{
    cout << "--------------------------------" << endl;
    cout << "         UpDate User           " << endl;
    cout << "--------------------------------" << endl;
}
sUser ChageUserInfo()
{
    sUser User;
    cout << "Enter New UserName :";
    getline(cin, User.UserName);
    cout << "\nEnter New PassWord :";
    getline(cin, User.PassWord);

    return User;
}
bool UpDateUserInfoByUserNameAndPassWord(string UserName, string PassWord, vector<sUser> &vUsers)
{
    sUser User;
    char Answer = 'n';

    if (FindUserByUserNameAndPassWord(UserName, PassWord, User))
    {

        PrintUserCard(User);
        cout << "\n\nAre you sure you want update this User? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            cin.ignore();
            for (sUser &U : vUsers)
            {
                if (U.UserName == User.UserName && U.PassWord == User.PassWord)
                {
                    U = ChageUserInfo();
                }
            }
            SaveUsersToFile(UserFile, vUsers);
            cout << "\n\nUser Updated Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with UserName (" << UserName << ") is Not Found!";
    }
    return false;
}
void UpDateUserInfo()
{
    if (!CheckAccessPermissions(enMainMenuePermissions::eUpdateUserPermissions))
     {
        ShowAccessDeniedMessage ();
        return;
    }
    ShowUpDateUserSecreen();
    sUser User = ReadUserInfo();
    vector<sUser> VUser = LoadUserDataFromFile(UserFile);
    UpDateUserInfoByUserNameAndPassWord(User.UserName, User.PassWord, VUser);
}
// Find User -------------------------------------------------------------------------------
void ShowFindUserSecreen()
{
    cout << "--------------------------------" << endl;
    cout << "         Find User           " << endl;
    cout << "--------------------------------" << endl;
}
void FindUser()
{
    if (!CheckAccessPermissions(enMainMenuePermissions::eFindUserPermissions))
     {
        ShowAccessDeniedMessage ();
        return;
    }
    system("cls");
    ShowFindUserSecreen();
    sUser User = ReadUserInfo();
    if (FindUserByUserNameAndPassWord(User.UserName, User.PassWord, User))
    {
        PrintUserCard(User);
    }
    else
    {
        cout << "User not found " << endl;
    }
}
// ------------------------------------------------------------------------
void GoBackToManageMenueSecreen()
{
    cout << "\n\nPress any key to go back to Manag User Menue...";
    system("pause>0");
    ManageUserSecreen();
}
void PerfromManageMenueOption(enMainUsersManue ManageMenueOptions)
{
    switch (ManageMenueOptions)
    {
    case enMainUsersManue::eListUser:
        system("cls");
        ShowAllUserScreen();
        GoBackToManageMenueSecreen();
        break;
    case enMainUsersManue::eAddNewUser:
        system("cls");
        AddNewUsers();
        GoBackToManageMenueSecreen();
        break;
    case enMainUsersManue::eDeleteUser:
        system("cls");
        DeleteUser();
        GoBackToManageMenueSecreen();
        break;
    case enMainUsersManue::eUpdateUser:
        system("cls");
        UpDateUserInfo();
        GoBackToManageMenueSecreen();
        break;
    case enMainUsersManue::eFindUser:
        system("cls");
        FindUser();
        GoBackToManageMenueSecreen();
        break;
    case enMainUsersManue::eMainMune:
        system("cls");
        ShowMainMenue();
        break;
    }
}
void ManageUserSecreen()
{
    system("cls");
    ShowManageUserSecreen();
    PerfromManageMenueOption((enMainUsersManue)ReadManagUserMenueOption());
}

int main()
{
    Login();
}