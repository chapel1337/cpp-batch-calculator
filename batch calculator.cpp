#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>

using std::cout; using std::string; using std::cin; using std::getline; using std::ws;

// written by chapel1337
// started on 10/8/2022
// speedran making this, will make actual menu tomorrow
// literally 11:30pm
// actual working one line calculator (kinda)

// finished on 10/9/2022
// program last night was very rudimentary
// program right now is as efficient as it can be (in my opinion)
// now supports no spacing

std::ofstream output{};
bool noteSent{ false };

// ------- \\

void menu();

void clear()
{
    system("cls");
}

auto sleep(auto time)
{
    Sleep(time * 1000);
}

void title(string title)
{
    std::system(("title " + title).c_str());
}

void invalidInput()
{
    clear();

    cout << "invalid input\n";

    sleep(2);
    menu();
}

// ------- \\

void runBat(string& number1, string& number2, string& operation, bool spaced)
{
    clear();
    title("batch calculator - result");

    output.open("funny.bat");

    output << "@echo off\n";

    output << "set num1=" + number1 + '\n';
    output << "set num2=" + number2 + '\n';
    output << "set /a result=%num1%" + operation + "%num2%\n";

    output << "echo %result%\n";

    output.close();

    if (spaced)
    {
        cout << number1 + ' ' + operation + ' ' + number2 << "\n\n";
    }
    else
    {
        cout << number1 + operation + number2 << "\n\n";
    }
    cout << "result: ";

    std::system("funny.bat");
    std::system("del funny.bat");

    cout << '\n';
    system("pause");

    // for precaution
    number1 = "";
    number2 = "";
    operation = "";
}

void calculateNoSpace(string input)
{
    static string operation{};
    static int operationPosition{};

    static string number1{};
    static string number2{};

    number1 = input.substr(0, operationPosition);
    number2 = input.substr(operationPosition, input.length());

    runBat(number1, number2, operation, false);

    menu();
}

void checkForInvalid(string& input, string& operation, int& operationPosition)
{
    static int whitespaceCount{ 0 };

    for (int i{ 0 }; i <= input.length(); i++)
    {
        if (input[i] == ' ')
        {
            whitespaceCount++;
        }

        switch (input[i])
        {
        case '+':
            operation = "+";
            operationPosition = i;
            break;

        case '-':
            operation = "-";
            operationPosition = i;
            break;

        case '*':
            operation = "*";
            operationPosition = i;
            break;

        case '/':
            operation = "/";
            operationPosition = i;
            break;

        case '%':
            operation = "%";
            operationPosition = i;
            break;
        }
    }

    if (whitespaceCount == 0)
    {
        calculateNoSpace(input);
    }
    if (operationPosition == 0)
    {
        invalidInput();
    }
    if (input.length() == ' ')
    {
        invalidInput();
    }
    if (input == "")
    {
        invalidInput();
    }

    whitespaceCount = 0;
}

void calculate(string input)
{
    static string operation{};
    static int operationPosition{};

    static string number1{};
    static string number2{};

    checkForInvalid(input, operation, operationPosition);
    
    number1 = input.substr(0, operationPosition - 1);
    number2 = input.substr(operationPosition + 2, input.length());

    runBat(number1, number2, operation, true);

    menu();
}

// ------- \\

void getFileLines(string& file)
{
    string line{ "" };

    std::ifstream inputFile(file);

    if (!inputFile.is_open())
    {
        cout << "could not open file\n";

        sleep(2);
        menu();
    }
    else
    {
        while (getline(inputFile, line))
        {
            calculate(line);
        }
        inputFile.close();
    }
}

void fileCalculator()
{
    clear();
    title("batch calculator - file");

    if (!noteSent)
    {
        cout << "note: this only works with files with a single line";

        noteSent = true;
        clear();
    }
    
    string fileName{ "" };
    string fileDirectory{ "" };
    string file{ "" };

    cout << "remember to include the drive name (C:\\)\n";
    cout << "input file directory: \n";

    cout << "> ";
    getline(cin >> ws, fileDirectory);

    if (fileDirectory[fileDirectory.length()] != '\\')
    {
        fileDirectory += '\\';
    }

    clear();

    cout << "input file name and file extension: \n";

    cout << "> ";
    getline(cin >> ws, fileName);

    clear();

    file = fileDirectory + fileName;
    getFileLines(file);
}

void inputCalculator()
{
    clear();
    title("batch calculator - input");

    string input{ "" };

    cout << "input an equation: \n";
    
    cout << "> ";
    getline(cin >> ws, input);

    calculate(input);
}

// ------- \\

void menu()
{
    clear();
    title("batch calculator - menu");

    char response{};

    cout << "batch calculator\n\n";

    cout << "1. input calculator\n";
    cout << "2. file calculator\n\n";

    cout << "> ";
    cin >> response;

    switch (response)
    {
    case '1':
        inputCalculator();
        break;

    case '2':
        fileCalculator();
        break;

    default:
        invalidInput();
        break;
    }
}

int main()
{
    cout << "written by chapel1337";

    sleep(2);
    menu();
}