#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

struct Constituency {
    string name = "";

    Constituency* next = NULL;
    Constituency* prev = NULL;
};
struct Requests {
    int req_no = 0;
    string name_of_candidate = "";
    string constituency_of_candidate = "";
    bool req_accepted = false;

    Requests* next = NULL;
    Requests* prev = NULL;
};
struct Political_party {
    string name;
    string symbol;
    int symbol_id;

    string username;
    string password;

    int total_candidates = 0;
    int total_votes = 0;
    int total_candidates_won = 0;

    //did the party won the elections r not
    bool won = false;

    //requests of all the candidates tha want to register themselve against a party
    Requests* requests = NULL;

    Political_party* next = NULL;
    Political_party* prev = NULL;
};
struct Candidate {

    string name;
    string party_name;

    bool dependet = false;
    int candidate_total_votes = 0;

    //basicaly names of the constituencys the candidate is gonna fight for
    Constituency* constituency = NULL;

    //did the candidate won the election or not
    bool won = false;

    //same symbol and symbol id if the candidate is dependant
    string symbol;
    int symbol_id;

    //request to send to a political party to register himsel against
    Requests request;

    Candidate* next = NULL;
    Candidate* prev = NULL;
};
struct Voter {
    string name;
    //a Voter can be registerd in only 1 constituency
    bool already_registered = false;

    string constituency_to_register_from = "";
    long int CNIC = 0;
    string password;

    bool vote_casted = false;

    Voter* next = NULL;
    Voter* prev = NULL;
};
struct EC_login {
    string name;
    int id;
    string password;
};

bool ec_login() {
    EC_login log = { "Election_Commission_of_Pakistan",1122334455,"what,mynameishwat,itschi1kach1ka" };
    int id; string name; string pass;
    cout << "enter ID of the Election Commission: "; cin >> id;
    cout << "enter Password of the Election Commission: "; cin >> pass;
    if (id == log.id and pass == log.password) {
        system("cls");
        return true;
    }
    else {
        system("cls");
        return false;
    }
}
bool pp_login() {
    fstream A;
    string username, password;
    cout << "enter username: "; cin >> username;
    cout << "enter password: "; cin >> password;
    string na, use, pas, sy;
    int id, s_id;
    string line;

    A.open("parties.txt", ios::in);
    if (A.is_open()) {

        while (!A.eof()) {
            getline(A, line);
            std::istringstream stream(line);
            stream >> na >> sy >> id >> use >> pas;
            if (username == use and password == pas) {
                cout << "party found\n";
                A.close();

                return true;
            }
        }
        return false;
    }
    else {
        cout << "parties file not found\n";
    }
    return false;
}

