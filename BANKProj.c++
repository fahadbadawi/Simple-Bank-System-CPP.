#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
const string ClientsFileName = "Claients.txt";
void ShowMainMenue();
struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};
vector<string> Split(string Text, string Delm = "#//#")
{
    vector<string> Vstring;
    short pos = 0;
    string Sword = "";
    while ((pos = Text.find(Delm)) != std::string::npos)
    {
        Sword = Text.substr(0, pos);
        if (Sword != "")
        {
            Vstring.push_back(Sword);
        }
        Text.erase(0, pos + Delm.length());
    }
    if (Text != "")
    {
        Vstring.push_back(Text);
    }
    return Vstring;
}
sClient ConvertLineToRecord(string Line)
{
    vector<string> Vstring = Split(Line);
    sClient Client;
    Client.AccountNumber = Vstring[0];
    Client.PinCode = Vstring[1];
    Client.Name = Vstring[2];
    Client.Phone = Vstring[3];
    Client.AccountBalance = stod(Vstring[4]);
    return Client;
}
string ConvertRecordToLine(sClient Client, string Seproter = "#//#")
{
    string Line = "";
    Line = Client.AccountNumber + Seproter;
    Line += Client.PinCode + Seproter;
    Line += Client.Name + Seproter;
    Line += Client.Phone + Seproter;
    Line += to_string(Client.AccountBalance);
    return Line;
}
vector<sClient> LoadCleintsDataFromFile(string FileName)
{
    vector<sClient> VSC;
    fstream MyFile;
    MyFile.open(FileName, ios ::in);
    if (MyFile.is_open())
    {
        string Line;
        sClient Client;
        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line);
            VSC.push_back(Client);
        }
        MyFile.close();
    }
    return VSC;
}
void PrintClientRecord(sClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}
void ShowAllClientsScreen()
{
    vector<sClient> vClients =
        LoadCleintsDataFromFile(ClientsFileName);
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ")Client(s).";
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
            PrintClientRecord(Client);
            cout << endl;
        }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
}
sClient ReadClient()
{
    sClient Client;
    cout << "Enter Account Number? ";
    // Usage of std::ws will extract allthe whitespace character
    getline(cin >> ws, Client.AccountNumber);
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
void AddDataLineToFile(string FileName, string stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios ::out | ios ::app);
    if (MyFile.is_open())
    {
        MyFile << stDataLine << endl;
        MyFile.close();
    }
}
void AddNewClient()
{
    sClient Client = ReadClient();
    AddDataLineToFile("Claients.txt", ConvertRecordToLine(Client));
}
void AddClients()
{
    char AddMore = 'Y';
    do
    {
        system("cls");
        cout << "Adding New Client:\n\n";
        AddNewClient();
        cout << "\nClient Added Successfully, do you want to add more clients? Y / N ? ";
        cin >> AddMore;
    } while (toupper(AddMore) == 'Y');
}
void PrintClientCard(sClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code : " << Client.PinCode;
    cout << "\nName : " << Client.Name;
    cout << "\nPhone : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
}
bool FindClientByAccountNumber(string AccountNumber, vector<sClient> vClient, sClient &Client)
{
    for (sClient &S : vClient)
    {
        if (S.AccountNumber == AccountNumber)
        {
            Client = S;
            return true;
        }
    }
    return false;
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
        for (sClient &C : vClients)
        {
            if (C.MarkForDelete == false)
            {
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
                DataLine = "";
            }
        }
        MyFile.close();
    }
    return vClients;
}
bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient> &vClients)
{
    sClient Client;
    char Answer = 'n';
    if (FindClientByAccountNumber(AccountNumber, vClients,
                                  Client))
    {
        PrintClientCard(Client);
        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber,
                                               vClients);
            SaveCleintsDataToFile(ClientsFileName, vClients);
            // Refresh Clients
            vClients = LoadCleintsDataFromFile(ClientsFileName);
            cout << "\n\nClient Deleted Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber
             << ") is Not Found!";
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
        cout << "\nClient with Account Number (" << AccountNumber
             << ") is Not Found!";
        return false;
    }
    return false;
}
void ShowDeleteClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n";
    vector<sClient> vClients =
        LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClients);
}
void ShowUpdateClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Info Screen";
    cout << "\n-----------------------------------\n";
    vector<sClient> vClients =
        LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);
}
void ShowAddNewClientsScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n-----------------------------------\n";
    AddNewClient();
}
void ShowFindClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n-----------------------------------\n";
    vector<sClient> vClients =
        LoadCleintsDataFromFile(ClientsFileName);
    sClient Client;
    string AccountNumber = ReadClientAccountNumber();
    if (FindClientByAccountNumber(AccountNumber, vClients,
                                  Client))
        PrintClientCard(Client);
    else
        cout << "\nClient with Account Number[" << AccountNumber
             << "] is not found!";
}
void ShowEndScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tProgram Ends :-)";
    cout << "\n-----------------------------------\n";
}
enum enMainMenueOptions
{
    eListClients = 1,
    eAddNewClient = 2,
    eDeleteClient = 3,
    eUpdateClient = 4,
    eFindClient = 5,
    eExit = 6
};
void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowMainMenue();
}
short ReadMainMenueOption()
{
    cout << "Choose what do you want to do? [1 to 6]? ";
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
    case enMainMenueOptions::eExit:
        system("cls");
        ShowEndScreen();
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
    cout << "\t[6] Exit.\n";
    cout << "===========================================\n";
    PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}
int main()
{
    ShowMainMenue();
    system("pause>0");
    return 0;
}