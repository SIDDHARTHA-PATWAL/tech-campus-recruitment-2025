#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Function to perform binary search for the specific date in the log file
bool binarySearchForDate(ifstream &logFile, const string &targetDate, long &targetPos) {
    // Get the size of the file
    logFile.seekg(0, ios::end);
    long left = 0, right = logFile.tellg(), mid;
    string line;

    while (left <= right) {
        mid = left + (right - left) / 2;
        logFile.seekg(mid); // Move to the mid-point in the file
        
        // Make sure to read a full line after seeking
        getline(logFile, line);
        if (line.empty()) continue; // Skip empty lines

        // Extract the timestamp (first 10 characters) from the line
        string timestamp = line.substr(0, 10);

        if (timestamp == targetDate) {
            targetPos = mid;  // Found the target position
            return true;
        } else if (timestamp < targetDate) {
            left = mid + 1;  // Move right if the date is earlier
        } else {
            right = mid - 1;  // Move left if the date is later
        }
    }

    return false;
}

// Function to extract and save logs for the given date
void extractLogs(const string &date) {
    ifstream logFile("./logs_2024.log");
    ofstream outFile("../output/output_" + date + ".txt");

    if (!logFile.is_open() || !outFile.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }

    long targetPos = 0;
    if (binarySearchForDate(logFile, date, targetPos)) {
        logFile.seekg(targetPos); // Seek to the target position

        string line;
        while (getline(logFile, line)) {
            string logDate = line.substr(0, 10);
            if (logDate == date) {
                outFile << line << endl; // Write log to output file
            } else if (logDate > date) {
                break; // Exit once we've passed the target date
            }
        }
    } else {
        cerr << "Date not found in log file!" << endl;
    }

    logFile.close();
    outFile.close();
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "Please provide a date (YYYY-MM-DD) as a command-line argument." << endl;
        return 1;
    }

    string targetDate = argv[1]; // Get the target date from the command-line argument
    extractLogs(targetDate); // Extract logs for the specified date

    return 0;
}
