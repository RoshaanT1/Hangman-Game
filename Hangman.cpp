#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <conio.h>
#include <unordered_map>
using namespace std;
class Question
{
public:
    string question;
    string hint1;
    string hint2;
    string hint3;
    string answer;

    Question(string q, string h1, string h2, string h3, string a)
        : question(q), hint1(h1), hint2(h2), hint3(h3), answer(a) {}
};
int remove(string &s, char a)
{
    int loc = s.find(tolower(a));
    int loc2 = s.find(toupper(a));
    if (loc != string::npos)
    {
        s.replace(loc, 1, 1, '#');
        return loc;
    }
    else if (loc2 != string::npos)
    {
        s.replace(loc2, 1, 1, '#');
        return loc2;
    }
    return -1;
}
void display(string a, string b)
{
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] == '#')
            cout << b[i] << " ";
        else if (a[i] == ' ')
            cout << " ";
        else
            cout << "_ ";
    }
    cout << endl;
}
bool revive(string &a, string b, char c)
{
    int check = remove(a, c);
    display(a, b);
    if (check >= 0)
        return true;
    else
        return false;
}
class Category
{
public:
    string name;
    vector<Question> questions;
    bool choosen = false;
    Category(string n) : name(n) {}
};
void displayHangman(int incorrectGuesses, int score)
{
    char heart = 3;
    switch (incorrectGuesses)
    {
    case 0:
        cout << "HEARTS: " << heart << " " << heart << " " << heart << setw(64) << "         + " << setw(80) << "SCORE: " << score << endl;
        cout << setw(77) << "         |\n";
        cout << setw(77) << "         |\n";
        cout << setw(77) << "         |\n";
        cout << setw(77) << "         |\n";
        cout << setw(77) << "         |\n";
        cout << setw(77) << "==========\n";
        break;
    case 1:
        cout << "HEARTS: " << heart << " " << heart << setw(66) << "  +------+ " << setw(80) << "SCORE: " << score << endl;
        cout << setw(77) << "         |\n";
        cout << setw(77) << "         |\n";
        cout << setw(77) << "         |\n";
        cout << setw(77) << "         |\n";
        cout << setw(77) << "         |\n";
        cout << setw(77) << "==========\n";
        break;
    case 2:
        cout << "HEARTS: " << heart << setw(68) << "  +------+ " << setw(80) << "SCORE: " << score << endl;
        cout << setw(77) << "  |      |\n";
        cout << setw(77) << " (^^)    |\n";
        cout << setw(77) << "         |\n";
        cout << setw(77) << "         |\n";
        cout << setw(77) << "         |\n";
        cout << setw(77) << "==========\n";
        break;
    case 3:
        cout << "HEARTS: " << setw(69) << "  +------+ " << setw(80) << "SCORE: " << score << endl;
        cout << setw(77) << "  |      |\n";
        cout << setw(77) << "  O      |\n";
        cout << setw(77) << " /|\\     |\n";
        cout << setw(77) << "         |\n";
        cout << setw(77) << "         |\n";
        cout << setw(77) << "=========\n";
        break;
    case 4:
        cout << setw(77) << "  +------+ " << setw(80) << "SCORE: " << score << endl;
        cout << setw(77) << "  |      |\n";
        cout << setw(77) << "  O      |\n";
        cout << setw(77) << " /|\\     |\n";
        cout << setw(77) << " / \\     |\n";
        cout << setw(77) << "         |\n";
        cout << setw(77) << "=========\n";
        break;
    default:
        cout << "Invalid number of incorrect guesses.\n";
        break;
    }
    cout << endl;
}
vector<Category> loadCategories(const string &filename)
{
    vector<Category> categories;
    ifstream file(filename.c_str());
    if (!file.is_open())
    {
        cerr << setw(85) << "Error opening file!" << endl;
        return categories;
    }
    string line;
    while (getline(file, line))
    {
        if (line.empty())
            continue;

        Category category(line);
        while (getline(file, line) && !line.empty())
        {
            string question = line;
            getline(file, line);
            string hint1 = line;
            getline(file, line);
            string hint2 = line;
            getline(file, line);
            string hint3 = line;
            getline(file, line);
            string answer = line;
            category.questions.push_back(Question(question, hint1, hint2, hint3, answer));
        }
        categories.push_back(category);
    }
    file.close();
    return categories;
}
int length(string a)
{
    int num = 0;
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] != ' ')
            ++num;
    }
    return num;
}
int playGame(vector<Category> &categories)
{
    int wins = 0;
label:
    cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << setw(84) << "SELECT A CATEGORY\n";
    cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    for (size_t i = 0; i < categories.size(); ++i)
    {
        if (categories[i].choosen == false)
        {
            cout << setw(65) << "[" << i + 1 << "]" << ". " << categories[i].name << endl;
        }
    }

    int categoryIndex;
    cout << setw(65) << "";
    cin >> categoryIndex;
    cin.ignore();
    if (categoryIndex < 1 || categoryIndex > categories.size())
    {
        cerr << setw(86) << "Invalid category selection!" << endl;
        goto label;
    }
    categories[categoryIndex - 1].choosen = true;
    const Category &selectedCategory = categories[categoryIndex - 1];
    for (size_t i = 0; i < selectedCategory.questions.size(); ++i)
    {
        cout << endl;
        cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << endl;
        int correctAnswers = 0;
        int wrongAnswer = 0;
        const Question &q = selectedCategory.questions[i];
        int screenWidht = 162;
        int len = q.question.length();
        int padding = (screenWidht - len) / 2;
        cout << setw(padding + len) << q.question << endl
             << endl;
        string ansChk = q.answer;
        while (correctAnswers < length(q.answer) && wrongAnswer < 4)
        {
            screenWidht = 162;
            len = q.answer.length();
            padding = (screenWidht - len) / 2;
            cout << setw(padding - len) << "Input: ";
            bool chk = revive(ansChk, q.answer, '#');
            screenWidht = 155;
            len = q.answer.length();
            padding = (screenWidht - (len)) / 2;
            string userAnswer;
            cout << setw(70) << "";
            char c = _getch();
            cout << endl;
            cout << setw(padding - len) << "";
            chk = revive(ansChk, q.answer, c);
            if (chk)
            {
                ++correctAnswers;
                cout << endl;
                displayHangman(wrongAnswer, wins);
            }
            else
            {
                ++wrongAnswer;
                cout << endl;
                displayHangman(wrongAnswer, wins);
                switch (wrongAnswer)
                {
                case 1:
                    screenWidht = 150;
                    len = q.hint1.length();
                    padding = (screenWidht - len) / 2;
                    cout << setw(82) << "Wrong Answer! Hint " << endl;
                    cout << setw(padding + len) << q.hint1 << endl
                         << endl;
                    break;
                case 2:
                    len = q.hint2.length();
                    padding = (screenWidht - len) / 2;
                    cout << setw(82) << "Wrong Answer! Hint " << endl;
                    cout << setw(padding + len) << q.hint2 << endl
                         << endl;
                    break;
                case 3:
                    len = q.hint3.length();
                    padding = (screenWidht - len) / 2;
                    cout << setw(82) << "Wrong Answer! Hint " << endl;
                    cout << setw(padding + len) << q.hint3 << endl
                         << endl;
                    break;
                case 4:
                    len = q.answer.length();
                    padding = (screenWidht - len) / 2;

                    cout << "******************************************************************************************************************************************************************" << endl;
                    cout << setw(((screenWidht - 31) / 2) + 31) << "Wrong! The correct answer is: " << endl;
                    cout << setw(padding + len) << q.answer << endl;
                    cout << setw(72) << "You Guessed " << wins << " times correctly!" << endl;
                    cout << "******************************************************************************************************************************************************************" << endl;
                    return wins;
                }
            }
        }
        if (correctAnswers == length(q.answer))
            ++wins;
        if (i == selectedCategory.questions.size() - 1)
            goto label;
    }
}
class Front
{
public:
    unordered_map<string, string> load()
    {
        fstream file("UserInfo.txt", ios::in);
        unordered_map<string, string> board;
        string name, password;
        while (file >> name >> password)
        {
            board[name] = password;
        }
        file.close();
        return board;
    }
    string login()
    {
        cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << setw(76) << "LOGIN" << endl;
        cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

        unordered_map<string, string> board = load();
    secure:
        string user, user_pass;
        cout << setw(82) << "Input Username:" << endl;
        cout << setw(71) << " ";
        cin >> user;
        cout << setw(82) << "Input Password:" << endl;
        cout << setw(71) << "";
        cin >> user_pass;
        if (board.find(user) != board.end())
        {
            if (board[user] != user_pass)
            {
                cout << endl
                     << setw(91) << "Username or Password is Incorrect\n"
                     << endl;
                goto secure;
            }
            else
            {
                cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
                cout << endl
                     << setw(88) << "Account Login Successfully\n"
                     << endl;
                cout << endl;
                return user;
            }
        }
        else
        {
            cout << endl
                 << setw(89) << "Username or Password is Incorrect\n"
                 << endl;
            goto secure;
        }
    }
    string lowerCase(string str)
    {
        string s = "";
        for (char ch : str)
            s += tolower(ch);
        return s;
    }
    string signup()
    {
        unordered_map<string, string> board = load();
        string user, user_pass;
        cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << setw(77) << "SIGNUP" << endl;
        cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

        while (1)
        {
            cout << setw(82) << "Input Username:" << endl;
            cout << setw(71) << "";
            cin >> user;
            user = lowerCase(user);
            if (board.find(user) != board.end())
                cout << endl
                     << setw(86) << "Username not available\n"
                     << endl;
            else
                break;
        }
        fstream file("UserInfo.txt", ios::app);
        cout << setw(82) << "Input Password:" << endl;
        cout << setw(71) << "";
        cin >> user_pass;
        cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << endl
             << setw(89) << "Account created successfully\n"
             << endl;
        file << user << ' ' << user_pass << endl;
        file.close();
        cout << endl;
        return user;
    }
    unordered_map<string, int> rankLoad()
    {
        fstream file("ranking.txt", ios::in);
        string name;
        int score;
        unordered_map<string, int> mp;
        while (file >> name >> score)
        {
            mp[name] = score;
        }
        file.close();
        return mp;
    }
    void PlayerScore(string x, int a)
    {
        unordered_map<string, int> mp = rankLoad();
        if (mp.find(x) != mp.end())
        {
            int high = mp[x];
            if (high < a)
                mp[x] = a;
        }
        else
            mp[x] = a;
        rankUpdate(mp);
    }
    void displayRanking()
    {
        fstream file("ranking.txt", ios::in);
        string name;
        int score;
        vector<pair<string, int>> vec;
        while (file >> name >> score)
        {
            vec.push_back({name, score});
        }
        file.close();
        cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

        cout << setw(60) << "RANK" << setw(20) << "NAME" << right << setw(20) << "SCORE" << endl;
        cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

        int i = 1;
        for (const auto v : vec)
        {
            cout << setw(59) << i << '.' << setw(20) << v.first << right << setw(20) << v.second << endl;
            i++;
        }
        cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << endl;
    }
    void rankUpdate(unordered_map<string, int> scores)
    {
        vector<pair<string, int>> vec(scores.begin(), scores.end());
        sort(vec.begin(), vec.end(), [](const auto &a, const auto &b)
             { return a.second > b.second; });
        fstream file("ranking.txt", ios::out);
        for (const auto &v : vec)
        {
            file << v.first << ' ' << v.second << endl;
        }
        file.close();
    }
};
void Hangman()
{
    while (1)
    {
        int opt, score;
        string name;
        class Front security;
        vector<Category> categories = loadCategories("categories.txt");
        if (categories.empty())
        {
            cerr << setw(100) << "No categories loaded. Please check the file." << endl;
            return;
        }
        cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << setw(82) << "THE HANGMAN GAME" << endl;
        cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

        cout << setw(78) << "[1] LOGIN" << endl;
        cout << setw(79) << "[2] SIGNUP" << endl;
        cout << setw(84) << "[3] LEADERBOARD" << endl;
        cout << setw(77) << "[4] EXIT" << endl;
        cout << setw(65) << "";
        cin >> opt;
        if (opt == 1)
        {
            name = security.login();
            score = playGame(categories);
            security.PlayerScore(name, score);
        }
        else if (opt == 2)
        {
            name = security.signup();
            score = playGame(categories);
            security.PlayerScore(name, score);
        }
        else if (opt == 3)
        {
            security.displayRanking();
            Hangman();
        }
        else if (opt == 4)
        {
            cout << setw(79) << "Exiting.." << endl;
            return;
        }
        else
        {
            cout << setw(85) << "Invalid Input" << endl;
            Hangman();
        }
    }
}
int main()
{
    Hangman();
    return 0;
}
