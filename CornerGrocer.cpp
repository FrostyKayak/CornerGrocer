
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <iomanip>
using namespace std;

//class that handles file reading, frequency counting, and output generation
class CornerGrocer {
private:
    map<string, int> itemFrequency; //stores item names and their purchase counts

public:
    //reads the grocery list and populates the map
    void LoadDataFile(const string& inputFileName) {
        ifstream inFile(inputFileName);
        if (!inFile.is_open()) {
            cout << "error: could not open " << inputFileName << endl;
            return;
        }

        string item;
        while (inFile >> item) {
            itemFrequency[item]++; //increment frequency count for each item
        }
        inFile.close();
    }

    //creates the backup file frequency.dat
    void CreateBackupFile(const string& outputFileName) {
        ofstream outFile(outputFileName);
        for (auto& pair : itemFrequency) {
            outFile << pair.first << " " << pair.second << endl;
        }
        outFile.close();
    }

    //finds and prints the frequency of a specific item
    void GetItemFrequency(const string& searchItem) {
        auto it = itemFrequency.find(searchItem);
        if (it != itemFrequency.end()) {
            cout << searchItem << " appears " << it->second << " times." << endl;
        }
        else {
            cout << searchItem << " does not appear in the list." << endl;
        }
    }

    //displays all items and their frequencies
    void PrintAllFrequencies() {
        cout << left << setw(15) << "Item" << "Frequency" << endl;
        cout << "------------------------" << endl;
        for (auto& pair : itemFrequency) {
            cout << left << setw(15) << pair.first << pair.second << endl;
        }
    }

    //displays histogram using asterisks
    void PrintHistogram() {
        cout << "\nItem Purchase Histogram" << endl;
        cout << "------------------------" << endl;
        for (auto& pair : itemFrequency) {
            cout << left << setw(15) << pair.first;
            for (int i = 0; i < pair.second; ++i) {
                cout << "*";
            }
            cout << endl;
        }
    }
};

//main program with interactive menu
int main() {
    CornerGrocer grocer;
    grocer.LoadDataFile("CS210_Project_Three_Input_File.txt");
    grocer.CreateBackupFile("frequency.dat");

    int choice = 0;
    string userItem;

    while (choice != 4) {
        cout << "\n===== Corner Grocer Menu =====" << endl;
        cout << "1. Search for item frequency" << endl;
        cout << "2. Display all item frequencies" << endl;
        cout << "3. Display histogram of items" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter item name: ";
            cin >> userItem;
            grocer.GetItemFrequency(userItem);
            break;
        case 2:
            grocer.PrintAllFrequencies();
            break;
        case 3:
            grocer.PrintHistogram();
            break;
        case 4:
            cout << "exiting program." << endl;
            break;
        default:
            cout << "invalid choice. please try again." << endl;
        }
    }

    return 0;
}

