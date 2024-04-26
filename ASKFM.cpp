#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <set>
#include <cstring>
#include <map>
#include<fstream>
#define ll long long
#define sz(x) int(x.size())
#define MIN INT_MIN
#define MAX INT_MAX
#define TEXT_FILE_PATH "d:/data.txt"


using namespace std;

enum { sign_up = 1, login = 2 };

class Users;
class Questions;
class Answers;


vector<Users>User;
vector<Questions>Question;
vector<Answers>Answer;

class base {
protected:
    int id_to;
    int id_from;
};

class Questions : public base {
    int id;
    using base::id_from;
    using base::id_to;
    string question;
    friend class System;
    friend class Users;
    Questions() {};
    Questions(string Ques, int ID, int ID_FROM, int ID_TO) {
        this->question = Ques;
        this->id_from = ID_FROM;
        this->id_to = ID_TO;
        this->id = ID;
    }
};



class Answers : public base {
    using base::id_from;
    using base::id_to;
    string answer;
    int id;
    friend class System;
    friend class Users;

    Answers() {};
    Answers(string Ans, int ID, int ID_FROM, int ID_TO) {
        this->answer = Ans;
        this->id_from = ID_FROM;
        this->id_to = ID_TO;
        this->id = ID;
    }
};

class Users {
public:
    string User_name;
    string Password;
    int Id;
    friend class Questions;
    friend class Answers;

    Users() {};

    Users(string user_name, string password, int id) {
        this->User_name = user_name;
        this->Password = password;
        this->Id = id;
    }

    int Ask_question() {
        cout << "Enter username to question or -1 to cancel: ";
        string NAME;
        cin >> NAME;
        int ID = 0;
        if (NAME == "-1") {
            return -1;
        }
        else {
            for (int i = 0; i < User.size(); ++i) {
                if (User[i].User_name == NAME) {
                    ID = User[i].Id;
                }
            }
            if (ID == 0) {
                cout << "Not found user...!" << endl;
                return Ask_question();
            }
            cout << "Enter question here: ";
            string Q;
            int ID_Q = 0;
            cin.ignore();
            getline(cin, Q);
            if (Question.empty()) {
                ID_Q = 1;
            }
            else {
                ID_Q = Question.back().id + 1;
            }
            Question.push_back({ Q,ID_Q,Id,ID });
            cout << "Enter 1 to ask new question or any button to cancel: ";
            int OP = 0; cin >> OP;
            if (OP == 1) {
                return Ask_question();
            }
            else {
                return -1;
            }
        }
    }

    int Add_Answer() {
        cout << "Enter id question to answer or -1 to cancel: ";
        int option; cin >> option;
        if (option == -1) {
            return -1;
        }
        else {
            bool found = 0;
            string QU;
            int ID_FROM;
            int ID_TO;
            for (int i = 0; i < Question.size(); ++i) {
                if (Question[i].id == option) {
                    found = 1;
                    QU = Question[i].question;
                    ID_FROM = Question[i].id_to;
                    ID_TO = Question[i].id_from;
                }
            }
            if (!found) {
                cout << "Invalid id ,Please try again..." << endl;
                return Add_Answer();
            }
            else {
                bool found_ans = 0;
                string ANS;
                cout << "Question id (" << option << ") from user id (" << ID_TO << ") " << "\t\t";
                cout << "Question: " << QU << endl;
                for (int i = 0; i < Answer.size(); ++i) {
                    if (ID_FROM == Answer[i].id_to) {
                        found_ans = 1;
                        ANS = Answer[i].answer;
                    }
                }
                if (found_ans) {
                    cout << ANS << endl << endl;
                    cout << "Warning :Already answer..." << endl;
                    return Add_Answer();
                }
                else {
                    string ans;
                    int id_ans = 0;
                    cout << "Enter your answer here: ";
                    cin.ignore();
                    getline(cin, ans);
                    if (Answer.empty()) {
                        id_ans = 1;
                    }
                    else {
                        Answer.back().id + 1;
                    }
                    Answer.push_back({ ans,id_ans,ID_FROM,ID_TO });
                    cout << "Enter 1 to add new answer or any button to cancel: ";
                    int op = 0; cin >> op;
                    if (op == 1) {
                        return Add_Answer();
                    }
                    else {
                        return -1;
                    }
                }
            }
        }
    }

    int Delete_Answer() {
        cout << "Enter id question to answer or -1 to cancel: ";
        int option; cin >> option;
        if (option == -1) {
            return -1;
        }
        else {
            vector<Questions>save_question;
            vector<Answers>save_answer;
            int id_ans_del = -1;
            for (int i = 0; i < Question.size(); ++i) {
                if (option == Question[i].id) {
                    id_ans_del = Question[i].id_from;
                    continue;
                }
                else {
                    save_question.push_back(Question[i]);
                }
            }

            for (int j = 0; j < Answer.size(); ++j) {
                if (id_ans_del == Answer[j].id_to) { continue; }
                else {
                    save_answer.push_back(Answer[j]);
                }
            }
            Question.clear();
            Answer.clear();
            for (int i = 0; i < save_question.size(); ++i) {
                Question.push_back(save_question[i]);
            }
            for (int j = 0; j < save_answer.size(); ++j) {
                Answer.push_back(save_answer[j]);
            }
            cout << "Enter 1 to delete another answer or any button to cancel: ";
            int op = 0; cin >> op;
            if (op == 1) {
                return Delete_Answer();
            }
            else {
                return -1;
            }
        }
    }

};



class System {
public:
    friend class Users;
    friend class Questions;
    friend class Answers;

    int menu() {
        cout << "Menu:" << endl;
        cout << '\t' << "1: Sign up" << endl;
        cout << '\t' << "2: login" << endl;
        cout << "Enter number in range 1 - 2:";
        int n; cin >> n;
        cout << endl;
        switch (n)
        {
        case sign_up:
            return n;
            break;
        case login:
            return n;
            break;
        default:
            cout << "Selection not found, Try again..." << endl << endl;
            return menu();
        }
    }

    Users Sign_Up() {
        string user_name;
        string password;
        int id;

        cout << "Enter username : ";
        cin >> user_name;
        cout << "Enter your password: ";
        cin >> password;

        for (int i = 0; i < User.size(); ++i) {
            if (User[i].User_name == user_name) {
                cout << "This user_name is already used...!";
                return Sign_Up();
            }
        }

        if (User.empty()) {
            id = 1;
        }
        else {
            id = User.back().Id + 1;
        }
        Users user = { user_name,password,id };
        User.push_back(user);
        return user;
    }

    Users Login() {
        string user_name;
        string password;

        cout << "Enter username : ";
        cin >> user_name;
        cout << "Enter your password: ";
        cin >> password;

        for (int i = 0; i < User.size(); ++i) {
            if (User[i].User_name == user_name && User[i].Password == password) {
                return User[i];
            }
        }

        cout << "Invalid user ,Please try again..." << endl << endl;
        cout << "Enter :" << endl;
        cout << '\t' << "1- TO try again." << endl;
        cout << '\t' << "Any button." << endl;
        string option;
        cin >> option;
        if (option == "1") { return Login(); }
        Users invalid = { "-1","-1",-1 };
        return invalid;
    }

    int options_menu() {
        cout << "Menu:" << endl;
        cout << '\t' << "1: Print Questions To Me" << endl;
        cout << '\t' << "2: Print Questions From Me" << endl;
        cout << '\t' << "3: Answer Questions " << endl;
        cout << '\t' << "4: Delete Questions " << endl;
        cout << '\t' << "5: Ask Questions " << endl;
        cout << '\t' << "6: List System Users" << endl;
        cout << '\t' << "7: Feed" << endl;
        cout << '\t' << "8: Logout" << endl << endl;
        cout << "Enter number in range 1 - 8:";

        int option; cin >> option;

        if (option < 1 || option > 8) {
            cout << "Invalid option...!" << endl;
            return options_menu();
        }
        else {
            return option;
        }

    }
    System() {
        ifstream file("USERS.txt", ios::in);
        if (file.fail()) {
            cout << "fail download users data" << endl;
            return;
        }
        User.clear();
        if (!file.fail()) {
            Users us;
            while (file >> us.User_name >> us.Password >> us.Id) {
                User.push_back(us);
            }
            file.close();
        }


        ifstream file2("question.txt", ios::in);
        if (file2.fail()) {
            cout << "fail download users data" << endl;
            return;
        }
        Question.clear();
        if (!file2.fail()) {
            Questions ques;
            while (file2 >> ques.question >> ques.id_from >> ques.id_to) {
                Question.push_back(ques);
            }
            file2.close();
        }


        ifstream file3("answer.txt", ios::in);
        if (file3.fail()) {
            cout << "fail download users data" << endl;
            return;
        }
        Answer.clear();
        if (!file3.fail()) {
            Answers ans;
            while (file2 >> ans.answer >> ans.id_from >> ans.id_to) {
                Answer.push_back(ans);
            }
            file3.close();
        }
    }
    ~System() {
        ofstream file("USERS.txt", ios::out);
        if (file.fail()) {
            cout << "faild download users data" << endl;
            return;
        }
        for (int i = 0; i < User.size(); ++i) {
            Users us = User[i];
            file << us.User_name << endl;
            file << us.Password << endl;
            file << us.Id << endl;
        }
        file.close();

        ofstream file2("question.txt", ios::out);
        if (file2.fail()) {
            cout << "faild download questions data" << endl;
            return;
        }
        for (int i = 0; i < Question.size(); i++) {
            Questions ques = Question[i];
            file2 << ques.question << endl;
            file2 << ques.id_from << endl;
            file2 << ques.id_to << endl;
        }
        file2.close();

        ofstream file3("answer.txt", ios::out);
        if (file3.fail()) {
            cout << "faild download answer data" << endl;
            return;
        }
        for (int i = 0; i < Answer.size(); i++) {
            Answers ans = Answer[i];
            file3 << ans.answer << endl;
            file3 << ans.id_from << endl;
            file3 << ans.id_to << endl;
        }
        file3.close();
    }

    void Print_question_to_me(Users U) {
        bool found = 0;
        for (int i = 0; i < Question.size(); ++i) {
            if (U.Id == Question[i].id_to) {
                found = 1;
            }
        }
        if (!found) {
            cout << "Not found question to this user...!" << endl << endl;
        }
        else {
            for (int i = 0; i < Question.size(); ++i) {
                string ANS = "Not answerd here.";
                if (U.Id == Question[i].id_to) {
                    for (int j = 0; j < Answer.size(); ++j) {
                        if (Answer[j].id_from == U.Id) {
                            ANS = Answer[j].answer;
                        }
                    }
                    cout << "Question ( " << Question[i].id << " ) :" << Question[i].question << endl;
                    cout << "Answer: " << ANS << endl;
                }
            }
        }
    }

    void Print_question_from_me(Users U) {
        bool found = 0;
        for (int i = 0; i < Question.size(); ++i) {
            if (U.Id == Question[i].id_from) {
                found = 1;
            }
        }
        if (!found) {
            cout << "Not found question from this user...!" << endl << endl;
        }
        else {

            for (int i = 0; i < Question.size(); ++i) {
                string ANS = "Not answerd here.";
                if (U.Id == Question[i].id_from) {
                    for (int j = 0; j < Answer.size(); ++j) {
                        if (Answer[j].id_to == U.Id) {
                            ANS = Answer[j].answer;
                        }
                    }
                    cout << "Question ( " << Question[i].id << " ) :" << Question[i].question << endl;
                    cout << "Answer: " << ANS << endl;
                }
            }
        }
    }

    void Listing_system_user() {
        for (int i = 0; i < User.size(); ++i) {
            cout << "ID: " << User[i].Id << '\t' << '\t' << "Name: " << User[i].User_name << endl;
        }
    }

    void Feed() {
        if (Question.empty()) {
            cout << "Not found questions...!" << endl << endl;
        }
        else {
            for (int i = 0; i < Question.size(); ++i) {
                string ANS = "Not answered.";
                for (int j = 0; j < Answer.size(); ++j) {
                    if (Answer[j].id_to == Question[i].id_from) {
                        ANS = Answer[j].answer;
                    }
                }
                cout << "Question ( " << Question[i].id << " ) :" << Question[i].question << endl;
                cout << "Answer: " << ANS << endl;
            }
        }
    }

    int Logout() {
        return 1;
    }
};

int main()
{
    System sys;
    Users USER;

    int op;
    op = sys.menu();
    if (op == 2) {
        USER = sys.Login();
        if (USER.Id == -1) {
            return 0;
        }
    }
    if (op == 1) {
        USER = sys.Sign_Up();
    }
    cout << "Hello ," << USER.User_name << endl;
start:
    op = sys.options_menu();
    switch (op)
    {
    case 1:
        sys.Print_question_to_me(USER);
        goto start;
        break;
    case 2:
        sys.Print_question_from_me(USER);
        goto start;
        break;
    case 3:
        USER.Add_Answer();
        goto start;
        break;
    case 4:
        USER.Delete_Answer();
        goto start;
        break;
    case 5:
        USER.Ask_question();
        goto start;
        break;
    case 6:
        sys.Listing_system_user();
        goto start;
        break;
    case 7:
        sys.Feed();
        goto start;
        break;
    case 8:
        return 0;
        break;
    default:
        cout << "Selection not found, Try again..." << endl << endl;
        goto start;
    }



}