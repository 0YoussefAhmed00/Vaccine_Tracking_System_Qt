#include "User.h"

void User::CreateUserEntry() {

    Entry newEntry;
    cout << "Enter Your Name:\n";
    cin.ignore();
    getline(cin, newEntry.name);
    //cin.getline(name, 40);
    cout << "Enter Your Government:\n";
    //cin.ignore();
    getline(cin, newEntry.government);
    cout << "Enter Your VaccineType:\n";
    //cin.ignore();
    getline(cin, newEntry.vaccineType);
    cout << "Enter Your Id:\n";
    cin >> newEntry.id;
    while (mainManager->CheckID(newEntry.id))
    {
        cout << "This Id Has Been Entered Before The Id Must Be Unique\n";
        cout << "Please enter The Correct Id\n";
        cin >> newEntry.id;
    }
    cout << "Enter your password:\n";
    cin >> newEntry.password;
    cout << "Enter Your Age:\n";
    cin >> newEntry.age;
    cout << "Enter Your Gender:\n";
    cin >> newEntry.gender;
    cout << "Enter Your firstDose 1 for yes 0 for no :\n";
    cin >> newEntry.firstDose;
    if (newEntry.firstDose == 1) {
        cout << "Enter Your FirstDate:\n";
        cin >> newEntry.firstDoseDate;
    }
    cout << "Enter Your secondDose 1 for yes 0 for no:\n";
    cin >> newEntry.secondDose;
    if (newEntry.secondDose == 1) {
        cout << "Enter Your SecondDate:\n";
        cin >> newEntry.secondDoseDate;
    }
    userEntry = newEntry;
    mainManager->CreateEntry(newEntry);
    //ShowAll();
    //mainManager->SaveEntriesToFile("TestingCases.csv");
}

void User::EditUserEntry(int id)
{
    cout << "What would you like to change in your data:\n1:Name\n2:Government\n3:Vaccine Type\n4:First Dose\n5:Second Dose\n6:ID\n7:Password\n";
    Entry myNewEntry = userEntry;
    bool idEdited = false;
    int lastId = myNewEntry.id;
    int choice4; cin >> choice4;
    cin.ignore();
    switch (choice4)
    {
    case 1:
        cout << "Enter your new name:\n";
        getline(cin, myNewEntry.name);
        break;
    case 2:
        cout << "Enter your new government:\n";
        getline(cin, myNewEntry.government);
        break;
    case 3:
        cout << "Enter your new vaccine type:\n";
        getline(cin, myNewEntry.vaccineType);
        break;
    case 4:
        cout << "Enter the date of the first dose, if you didn't take it type No:\n";
        getline(cin, myNewEntry.firstDoseDate);
        if (myNewEntry.firstDoseDate == "No") {
            myNewEntry.firstDose = false;
            myNewEntry.firstDoseDate = "";
        }
        break;
    case 5:
        cout << "Enter the date of the second dose, if you didn't take it type No:\n";
        getline(cin, myNewEntry.secondDoseDate);
        if (myNewEntry.secondDoseDate == "No") {
            myNewEntry.secondDose = false;
            myNewEntry.secondDoseDate = "";
        }
        break;
    case 6:
        cout << "Enter your new id:\n";
        cin>>myNewEntry.id;
        idEdited = true;
        break;
    case 7:
        cout << "Enter your new password\n";
        getline(cin, myNewEntry.password);
        break;
    default:
        break;
    }

    Entry newEntry = { myNewEntry.name, myNewEntry.id, myNewEntry.government, myNewEntry.age, myNewEntry.gender, myNewEntry.vaccineType, myNewEntry.firstDose, myNewEntry.firstDoseDate, myNewEntry.secondDose, myNewEntry.secondDoseDate, myNewEntry.password };
    if (idEdited) {
        mainManager->DeleteEntry(lastId);
        mainManager->CreateEntry(myNewEntry);
    }
    else {
        mainManager->EditEntry(myNewEntry.id, newEntry);
    }
    //mainManager->SaveEntriesToFile("TestingCases.csv");
}

void User::DeleteUserEntry(int id)
{
    mainManager->DeleteEntry(id);
}

void User::ShowUserEntry(int id)
{
    mainManager->ShowEntry(id);
}
