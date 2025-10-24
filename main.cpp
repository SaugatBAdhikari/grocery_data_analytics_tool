/*
 * Corner Grocer Item Tracking Program
 * CS 210 Project 3
 * 
 * This program analyzes grocery item purchase frequency data
 * to help optimize produce section layout.
 * 
 * Features:
 * - Search for specific item frequency
 * - Display all items with frequencies
 * - Generate histogram visualization
 * - Create backup data file
 */

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

class ItemTracker {
private:
    map<string, int> itemFrequency;  // Map to store item frequencies
    string inputFileName;           // Name of input file
    string backupFileName;          // Name of backup file
    
    // Private helper method to read data from input file
    void readInputFile() {
        ifstream inputFile(inputFileName);
        string item;
        
        if (!inputFile.is_open()) {
            cout << "Error: Could not open input file: " << inputFileName << endl;
            return;
        }
        
        // Read each item and increment frequency count
        while (getline(inputFile, item)) {
            if (!item.empty()) {
                itemFrequency[item]++;
            }
        }
        
        inputFile.close();
    }
    
    // Private helper method to create backup file
    void createBackupFile() {
        ofstream backupFile(backupFileName);
        
        if (!backupFile.is_open()) {
            cout << "Error: Could not create backup file: " << backupFileName << endl;
            return;
        }
        
        // Write frequency data to backup file
        for (const auto& pair : itemFrequency) {
            backupFile << pair.first << " " << pair.second << endl;
        }
        
        backupFile.close();
        cout << "Backup file '" << backupFileName << "' created successfully." << endl;
    }

public:
    // Constructor - initializes file names and reads data
    ItemTracker(const string& inputFile = "CS210_Project_Three_Input_File.txt",
                const string& backupFile = "frequency.dat") 
        : inputFileName(inputFile), backupFileName(backupFile) {
        readInputFile();
        createBackupFile();
    }
    
    // Method to search for specific item frequency
    void searchItemFrequency() {
        string searchItem;
        cout << "\nEnter the item you wish to search for: ";
        getline(cin, searchItem);
        
        // Convert to proper case for consistent searching
        transform(searchItem.begin(), searchItem.end(), searchItem.begin(), ::tolower);
        
        // Search for item (case-insensitive)
        bool found = false;
        for (const auto& pair : itemFrequency) {
            string itemName = pair.first;
            transform(itemName.begin(), itemName.end(), itemName.begin(), ::tolower);
            
            if (itemName == searchItem) {
                cout << "\nFrequency of '" << pair.first << "': " << pair.second << endl;
                found = true;
                break;
            }
        }
        
        if (!found) {
            cout << "\nItem '" << searchItem << "' not found in the data." << endl;
        }
    }
    
    // Method to display all items with their frequencies
    void displayAllFrequencies() {
        cout << "\n=== All Items and Their Frequencies ===" << endl;
        cout << setw(15) << left << "Item" << "Frequency" << endl;
        cout << string(25, '-') << endl;
        
        for (const auto& pair : itemFrequency) {
            cout << setw(15) << left << pair.first << pair.second << endl;
        }
    }
    
    // Method to display histogram
    void displayHistogram() {
        cout << "\n=== Item Frequency Histogram ===" << endl;
        
        for (const auto& pair : itemFrequency) {
            cout << setw(15) << left << pair.first;
            
            // Print asterisks based on frequency
            for (int i = 0; i < pair.second; i++) {
                cout << "*";
            }
            cout << endl;
        }
    }
    
    // Method to display menu options
    void displayMenu() {
        cout << "\n" << string(50, '=') << endl;
        cout << "        CORNER GROCER ITEM TRACKER" << endl;
        cout << string(50, '=') << endl;
        cout << "1. Search for item frequency" << endl;
        cout << "2. Display all item frequencies" << endl;
        cout << "3. Display frequency histogram" << endl;
        cout << "4. Exit program" << endl;
        cout << string(50, '=') << endl;
        cout << "Enter your choice (1-4): ";
    }
    
    // Method to validate user input
    bool isValidChoice(int choice) {
        return (choice >= 1 && choice <= 4);
    }
    
    // Method to get total number of items
    int getTotalItems() {
        return itemFrequency.size();
    }
};

int main() {
    // Initialize the item tracker
    ItemTracker tracker;
    
    cout << "Welcome to the Corner Grocer Item Tracking System!" << endl;
    cout << "Data loaded from input file. Backup file created." << endl;
    cout << "Total unique items found: " << tracker.getTotalItems() << endl;
    
    int choice;
    bool running = true;
    
    // Main program loop
    while (running) {
        tracker.displayMenu();
        cin >> choice;
        cin.ignore(); // Clear the newline character
        
        // Validate choice
        if (!tracker.isValidChoice(choice)) {
            cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
            continue;
        }
        
        // Execute chosen option
        switch (choice) {
            case 1:
                tracker.searchItemFrequency();
                break;
            case 2:
                tracker.displayAllFrequencies();
                break;
            case 3:
                tracker.displayHistogram();
                break;
            case 4:
                cout << "\nThank you for using the Corner Grocer Item Tracking System!" << endl;
                cout << "Goodbye!" << endl;
                running = false;
                break;
            default:
                cout << "An unexpected error occurred." << endl;
                break;
        }
        
        // Pause before showing menu again (except when exiting)
        if (running) {
            cout << "\nPress Enter to continue...";
            cin.get();
        }
    }
    
    return 0;
}