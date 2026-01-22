#include <iostream>
#include <conio.h>
#include <ctime>
#include <windows.h>
#include <fstream>   // ? ADDED for file handling
using namespace std;

// Clear screen
void clearScreen()
{
    system("cls");
}

// Menu
void showMenu()
{
    cout << "+--------------------------------------------------+\n";
    cout << "¦            SIMPLE QUIZ APPLICATION               ¦\n";
    cout << "¦                By Abdullah Aamer                 ¦\n";
    cout << "+--------------------------------------------------+\n";
    cout << "¦   [ 1 ]  Start Test                              ¦\n";
    cout << "¦   [ 2 ]  View Instructions                      ¦\n";
    cout << "¦   [ 3 ]  View Result History                    ¦\n";
    cout << "¦   [ 4 ]  Admin Panel                            ¦\n";
    cout << "¦   [ 5 ]  About Application                      ¦\n";
    cout << "¦   [ 6 ]  Exit                                   ¦\n";
    cout << "+--------------------------------------------------+\n";
}

bool isValidOption(char c)
{
    return (c=='A'||c=='B'||c=='C'||c=='D'||c=='a'||c=='b'||c=='c'||c=='d');
}

char toUpperOpt(char c)
{
    if (c >= 'a' && c <= 'd') return char(c - 32);
    return c;
}

// ? ADDED: Save results to file (called after main test result)
void saveResultToFile(string studentID, string name, string courseName,
                      int correct, int totalQ, float percentage, string status)
{
    ofstream file("results.txt", ios::app);

    // Store as a single line record (easy to read + easy to parse)
    // Format:
    // ID|Name|Course|Correct/Total|Percentage|Status|DateTime
    time_t now = time(0);
    string dt = ctime(&now);

    // remove extra newline from ctime
    if (!dt.empty() && dt[dt.size()-1] == '\n') dt.erase(dt.size()-1);

    file << studentID << "|"
         << name << "|"
         << courseName << "|"
         << correct << "/" << totalQ << "|"
         << percentage << "|"
         << status << "|"
         << dt
         << endl;

    file.close();
}

// ---------------- DEMO TEST (PER QUESTION TIMER) ----------------
bool runTimedQuestion(
    string title, int qNo, int totalQ,
    string question, string options[4],
    int secondsPerQ, char &finalAnswer)
{
    int timeLeft = secondsPerQ;
    finalAnswer = '\0';
    string msg = "Press A / B / C / D";

    while (timeLeft > 0)
    {
        clearScreen();
        int m = timeLeft / 60;
        int s = timeLeft % 60;

        cout << "------------------------------------------------\n";
        cout << title << "    Q: " << qNo << "/" << totalQ
             << "    Time: ";
        if (m < 10) cout << "0";
        cout << m << ":";
        if (s < 10) cout << "0";
        cout << s << "\n";
        cout << "------------------------------------------------\n\n";

        cout << question << "\n\n";
        cout << "A) " << options[0] << "\n";
        cout << "B) " << options[1] << "\n";
        cout << "C) " << options[2] << "\n";
        cout << "D) " << options[3] << "\n";

        cout << "\n" << msg << "\n";

        if (kbhit())
        {
            char key = getch();
            if (isValidOption(key))
            {
                finalAnswer = toUpperOpt(key);
                return false;
            }
            else
            {
                msg = "Invalid choice! Only A / B / C / D allowed.";
                Beep(800,120);
            }
        }

        Sleep(1000);
        timeLeft--;
    }
    return true;
}

// ---------------- MAIN TEST (GLOBAL TIMER) ----------------
bool runMainTimedQuestion(
    string title, int qNo, int totalQ,
    string question, string options[4],
    int &totalTimeLeft, char &finalAnswer)
{
    finalAnswer = '\0';
    string msg = "Press A / B / C / D";

    while (totalTimeLeft > 0)
    {
        clearScreen();
        int m = totalTimeLeft / 60;
        int s = totalTimeLeft % 60;

        cout << "------------------------------------------------\n";
        cout << title << "    Q: " << qNo << "/" << totalQ
             << "    Time Left: ";
        if (m < 10) cout << "0";
        cout << m << ":";
        if (s < 10) cout << "0";
        cout << s << "\n";
        cout << "------------------------------------------------\n\n";

        cout << question << "\n\n";
        cout << "A) " << options[0] << "\n";
        cout << "B) " << options[1] << "\n";
        cout << "C) " << options[2] << "\n";
        cout << "D) " << options[3] << "\n";

        cout << "\n" << msg << "\n";

        if (kbhit())
        {
            char key = getch();
            if (isValidOption(key))
            {
                finalAnswer = toUpperOpt(key);
                return false;
            }
            else
            {
                msg = "Invalid choice! Only A / B / C / D allowed.";
                Beep(800,120);
            }
        }

        Sleep(1000);
        totalTimeLeft--;
    }
    return true;
}

// ---------------- START TEST ----------------
void startTest()
{
    clearScreen();

    string studentID, name, courseName;
    time_t now = time(0);
    string date = ctime(&now);

    cout << "=========== STUDENT INFORMATION ===========\n";
    cout << "Student ID / Registration No: ";
    cin.ignore();
    getline(cin, studentID);
    cout << "Name: ";
    getline(cin, name);
    cout << "Course / Test Name: ";
    getline(cin, courseName);
    cout << "Date: " << date;
    cout << "===========================================\n";

    int demoChoice;
    cout << "\nDo you want to attempt Demo Test (Practice)?\n";
    cout << "[1] Yes\n[2] Skip\nChoice: ";
    cin >> demoChoice;

    const int secondsPerQ = 90;

    if (demoChoice == 1)
    {
        string demoQ[5] = {
            "What is C++?",
            "Which symbol ends a statement?",
            "Which loop runs at least once?",
            "Which keyword is used for input?",
            "Which data type stores integers?"
        };

        string demoOpt[5][4] = {
            {"Language","OS","Browser","Game"},
            {";",";",".",","},
            {"do-while","for","while","switch"},
            {"cin","cout","input","scan"},
            {"int","float","char","double"}
        };

        for (int i = 0; i < 5; i++)
        {
            char ans;
            string opts[4] = {
                demoOpt[i][0], demoOpt[i][1],
                demoOpt[i][2], demoOpt[i][3]
            };

            runTimedQuestion("Demo Test", i+1, 5, demoQ[i], opts, secondsPerQ, ans);
        }
    }

    clearScreen();
    cout << "Main Test: " << courseName << "\n";
    cout << "Total Time: 30 Minutes\n";
    cout << "Press any key to start...";
    getch();

    const int totalQ = 20;
    int totalMainTime = totalQ * 90;

    char userAns[20] = {'\0'};
    char correctAns[20] = {
        'A','A','A','A','A','B','A','A','A','A',
        'A','A','A','A','A','A','D','A','A','A'
    };

    string questions[20] = {
        "What does CPU stand for?",
        "Which operator is logical AND?",
        "Which header is used for cin/cout?",
        "Which loop is best for fixed iterations?",
        "Which data type stores decimal values?",
        "Which symbol ends a statement?",
        "Which keyword returns a value?",
        "Which operator increments value?",
        "What is RAM?",
        "Which comment is single line?",
        "Which loop runs at least once?",
        "Which keyword selects multiple cases?",
        "Which is a valid variable?",
        "Which stops loop immediately?",
        "Index of first array element?",
        "Which stores true/false?",
        "Which is not a data type?",
        "Which is correct array syntax?",
        "Which is relational operator?",
        "Which is correct 2D array?"
    };

    string options[20][4] = {
        {"Central Processing Unit","Computer Unit","Central Program","Control Unit"},
        {"&&","||","&","%"},
        {"<iostream>","<stdio.h>","<math.h>","<string>"},
        {"for","while","do-while","switch"},
        {"float","int","char","bool"},
        {":",";",".",","},
        {"return","give","send","output"},
        {"++","--","**","//"},
        {"Random Access Memory","Read Memory","Run All","None"},
        {"//","/* */","##","**"},
        {"do-while","for","while","switch"},
        {"switch","if","case","break"},
        {"name_1","1name","name-1","name 1"},
        {"break","continue","stop","exit"},
        {"0","1","-1","Depends"},
        {"bool","int","float","string"},
        {"int","float","char","loop"},
        {"int a[5];","int a(5);","array a","int a{}"},
        {"!=","==","<>","><"},
        {"int a[3][4];","int a(3)(4);","a[3,4]","int a[4][3]"}
    };

    for (int i = 0; i < totalQ; i++)
    {
        string opts[4] = {
            options[i][0], options[i][1],
            options[i][2], options[i][3]
        };

        char ans;
        runMainTimedQuestion(courseName, i+1, totalQ, questions[i], opts, totalMainTime, ans);
        userAns[i] = ans;
    }

    int correct = 0;
    for (int i = 0; i < totalQ; i++)
        if (userAns[i] == correctAns[i]) correct++;

    float percentage = (correct * 100.0f) / totalQ;

    clearScreen();
    cout << "=========== RESULT ===========\n";
    cout << "Name: " << name << "\n";
    cout << "ID: " << studentID << "\n";
    cout << "Score: " << correct << "/" << totalQ << "\n";
    cout << "Percentage: " << percentage << "%\n";
    cout << "Status: " << (percentage >= 50 ? "PASS" : "FAIL") << "\n\n";

    if (percentage >= 50)
        cout << "Congratulations! Keep up the great work.\n";
    else
        cout << "Don't worry! Practice and try again.\n";

    // ? ADDED: Save main test result to file (no UI change)
    saveResultToFile(studentID, name, courseName,
                     correct, totalQ, percentage,
                     (percentage >= 50 ? "PASS" : "FAIL"));

    cout << "\nPress any key to return to menu...";
    getch();
}

// ---------------- INFO SECTIONS ----------------
void instructions()
{
    clearScreen();
    cout << "=========== INSTRUCTIONS ===========\n";
    cout << "1. Follow on-screen instructions carefully.\n";
    cout << "2. Only A/B/C/D answers are allowed.\n";
    cout << "3. Demo test is optional and for practice only.\n";
    cout << "4. Main test has a fixed 30-minute timer.\n";
    cout << "5. Results are shown automatically.\n";
    cout << "====================================\n";
    getch();
}

void resultHistory()
{
    // ? UPDATED (placeholder replaced with full professional logic)
    clearScreen();

    ifstream file("results.txt");
    if (!file)
    {
        cout << "No results available yet.\n";
        cout << "\nPress any key to return...";
        getch();
        return;
    }

    const int MAX = 300;
    string id[MAX], stName[MAX], course[MAX], status[MAX], dateTime[MAX];
    int correct[MAX], total[MAX];
    float percent[MAX];

    int count = 0;
    string line;

    while (getline(file, line) && count < MAX)
    {
        // Parse: ID|Name|Course|Correct/Total|Percentage|Status|DateTime
        int p1 = line.find('|');
        int p2 = line.find('|', p1+1);
        int p3 = line.find('|', p2+1);
        int p4 = line.find('|', p3+1);
        int p5 = line.find('|', p4+1);
        int p6 = line.find('|', p5+1);

        if (p1==-1 || p2==-1 || p3==-1 || p4==-1 || p5==-1 || p6==-1)
            continue;

        id[count] = line.substr(0, p1);
        stName[count] = line.substr(p1+1, p2-p1-1);
        course[count] = line.substr(p2+1, p3-p2-1);

        string marksPart = line.substr(p3+1, p4-p3-1); // Correct/Total
        int slash = marksPart.find('/');
        if (slash != -1)
        {
            correct[count] = atoi(marksPart.substr(0, slash).c_str());
            total[count]   = atoi(marksPart.substr(slash+1).c_str());
        }
        else
        {
            correct[count] = 0;
            total[count] = 0;
        }

        percent[count] = (float)atof(line.substr(p4+1, p5-p4-1).c_str());
        status[count] = line.substr(p5+1, p6-p5-1);
        dateTime[count] = line.substr(p6+1);

        count++;
    }
    file.close();

    int choice;
    cout << "=========== RESULT HISTORY ===========\n";
    cout << "Total Students Attempted: " << count << "\n\n";
    cout << "[ 1 ] View All Results\n";
    cout << "[ 2 ] Search by Student ID\n";
    cout << "[ 3 ] Highest Marks\n";
    cout << "[ 4 ] Average Marks\n";
    cout << "[ 5 ] Recent Result (Last Student)\n";
    cout << "\nEnter choice: ";
    cin >> choice;

    clearScreen();

    if (choice == 1)
    {
        cout << "=========== ALL RESULTS ===========\n\n";
        for (int i = 0; i < count; i++)
        {
            cout << "ID: " << id[i]
                 << " | Name: " << stName[i]
                 << " | Test: " << course[i]
                 << " | Score: " << correct[i] << "/" << total[i]
                 << " | %: " << percent[i]
                 << " | " << status[i]
                 << " | " << dateTime[i]
                 << "\n";
        }
    }
    else if (choice == 2)
    {
        string searchID;
        cout << "Enter Student ID: ";
        cin >> searchID;

        bool found = false;
        for (int i = 0; i < count; i++)
        {
            if (id[i] == searchID)
            {
                cout << "=========== STUDENT RESULT ===========\n\n";
                cout << "Student ID : " << id[i] << "\n";
                cout << "Name       : " << stName[i] << "\n";
                cout << "Test Name  : " << course[i] << "\n";
                cout << "Score      : " << correct[i] << "/" << total[i] << "\n";
                cout << "Percentage : " << percent[i] << "%\n";
                cout << "Status     : " << status[i] << "\n";
                cout << "Date/Time  : " << dateTime[i] << "\n";
                found = true;
                break;
            }
        }
        if (!found)
            cout << "No record found for this Student ID.\n";
    }
    else if (choice == 3)
    {
        int maxMarks = correct[0];
        int idx = 0;

        for (int i = 1; i < count; i++)
        {
            if (correct[i] > maxMarks)
            {
                maxMarks = correct[i];
                idx = i;
            }
        }

        cout << "=========== HIGHEST MARKS ===========\n\n";
        cout << "Highest Marks: " << maxMarks << "/" << total[idx] << "\n";
        cout << "Student ID  : " << id[idx] << "\n";
        cout << "Name        : " << stName[idx] << "\n";
        cout << "Test        : " << course[idx] << "\n";
        cout << "Percentage  : " << percent[idx] << "%\n";
        cout << "Status      : " << status[idx] << "\n";
        cout << "Date/Time   : " << dateTime[idx] << "\n";
    }
    else if (choice == 4)
    {
        float sum = 0;
        for (int i = 0; i < count; i++)
            sum += correct[i];

        cout << "=========== AVERAGE MARKS ===========\n\n";
        cout << "Average Marks: " << (sum / count) << " out of 20\n";
    }
    else if (choice == 5)
    {
        if (count == 0)
        {
            cout << "No data available.\n";
        }
        else
        {
            int i = count - 1;
            cout << "=========== MOST RECENT RESULT ===========\n\n";
            cout << "Student ID : " << id[i] << "\n";
            cout << "Name       : " << stName[i] << "\n";
            cout << "Test Name  : " << course[i] << "\n";
            cout << "Score      : " << correct[i] << "/" << total[i] << "\n";
            cout << "Percentage : " << percent[i] << "%\n";
            cout << "Status     : " << status[i] << "\n";
            cout << "Date/Time  : " << dateTime[i] << "\n";
        }
    }
    else
    {
        cout << "Invalid choice!\n";
    }

    cout << "\nPress any key to return...";
    getch();
}

void adminPanel()
{
    clearScreen();
    cout << "Admin Panel\n";
    cout << "Coming Soon...\n";
    cout << "This feature requires advanced logic and security.\n";
    getch();
}

void aboutApp()
{
    clearScreen();
    cout << "=========== ABOUT APPLICATION ===========\n";
    cout << "Developer Name : Muhammad Abdullah Bin Aamer\n";
    cout << "Student ID     : F25605346\n";
    cout << "Institution    : National University of Technology ( NUTECH ))\n";
    cout << "Program        : Bachelor of Science in Computer Science ( BS CS )\n";
    cout << "Project Type   : Academic Semester Project\n\n";
    cout << "This application is a console-based quiz system\n";
    cout << "developed using C++ programming language.\n";
    cout << "It demonstrates professional examination flow,\n";
    cout << "timed assessments, and result evaluation.\n\n";
    cout << "Feedback (Mandatory):\n";
    cout << "Email: abdullahaamer56@gmail.com\n";
    cout << "==========================================\n";
    getch();
}

// ---------------- MAIN LOOP ----------------
int main()
{
    int choice;
    while (true)
    {
        clearScreen();
        showMenu();
        cout << "\nSelect option: ";
        cin >> choice;

        switch(choice)
        {
            case 1: startTest(); break;
            case 2: instructions(); break;
            case 3: resultHistory(); break;
            case 4: adminPanel(); break;
            case 5: aboutApp(); break;
            case 6:
                clearScreen();
                cout << "Thank you for using the application.\n";
                return 0;
            default:
                cout << "Invalid choice!";
                getch();
        }
    }
}

