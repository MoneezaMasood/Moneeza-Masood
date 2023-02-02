#include "Source.cpp"

class Election_Commission {
    Constituency* constituency = NULL;
    Political_party* political_party = NULL;
    Candidate* candidate = NULL;
    Voter* voter = NULL;

    int total_voters = 0;
    bool won = false;

public:

    Election_Commission() {}
    //done
    bool create_or_update_constituency() { 
        ifstream A;
        ofstream B;
        A.open("constituencies.txt");
        if (A.is_open()) {
            cout << "file opened\n";
            int choice;
            cout << "1. Create constituency.\n";
            cout << "2. Update constituency.\n";
            cin >> choice;
            while (choice > 2 or choice < 1) { cerr << "wrong input, try agian: "; cin >> choice; }
            string name;
            if (choice == 1) {
                bool flag = false;
                do {
                    flag = false;
                    cout << "enter the name of the constituency: "; cin >> name;
                    string n;

                    while (A >> n) {
                        if (n == name) {
                            flag = true;
                            cout << "That name already exists\n";
                        }
                    }
                    A.clear();
                    A.seekg(0, ios::beg);

                } while (flag == true);
                A.close();
                B.open("constituencies.txt", ios::app);
                B << name << endl;
                B.close();
                if (A.is_open() or B.is_open()) {
                    A.close(); B.close();
                }
            }
            else if (choice == 2) {
                bool flag = false;
                A.close();
                B.close();
                while (true){
                    string old_name;
                    cout << "enter the name of the constituency to update: "; cin >> old_name;

                    flag = false;

                    A.open("constituencies.txt");
                    string name;
                    string* names = NULL;
                    int size = 0;
                    int index = 0;
                    int i = 0;

                    while (A >> name) {
                        if (name == old_name) {
                           // cout << flag << endl;
                            flag = true;//name found
                        }
                        size++;
                    }
                    bool flag2;
                    names = new string[size];
                    if (flag == true) {//found

                        while (1){
                            flag2 = false;
                            string new_name;
                            cout << "enter the new name for the constituency: "; cin >> new_name;

                            i = 0;
                            A.clear();
                            A.seekg(0, ios::beg);
                            
                            //storing names from file in an array
                            while (A >> names[i]) {
                                i++;
                            }
                            index = 0;
                            for (int j = 0; j < size; j++) {
                                if (names[j] == new_name) {
                                    flag2 = false;
                                    break;
                                }
                                else {
                                    flag2 = true;
                                }
                            }
                            if (flag2 == true) {
                                A.close();
                                B.open("constituencies.txt");
                                i = 0;
                                while (i < size) {
                                    if (names[i] == old_name) {
                                        names[i] = new_name;
                                    }
                                    B << names[i] << endl;
                                    i++;
                                }
                                B.close();
                                break;
                            }
                            else if (flag2 == false) {
                                cout << "that name is already taken.\n";
                                A.open("constituencies.txt");
                            }
                        } 
                        delete []names;
                        break;
                    }
                    else if (flag == false) {
                        cout << "constituency not found\n";
                        delete []names;
                        break;
                    }

                } 
              //  cout << "break\n";
            }
        }
        else {
            cout << "file not found\n";
            return 0;
        }
        A.close();
        B.close();
        return 0;
    }

    bool create_political_party() {
        ifstream A;
        ofstream B;

        political_party = new Political_party;
        cout << "enter name of the political party(no spaces): "; cin >> political_party->name;
        cout << "enter symbol name(no spaces): "; cin >> political_party->symbol;
        cout << "enter symbol ID: (integer): "; cin >> political_party->symbol_id;
        cout << "enter username(no spaces): "; cin >> political_party->username;
        cout << "enter password(no spaces): "; cin >> political_party->password;

        A.open("parties.txt");
        string* lines = NULL;
        string name, symb, user, pass;
        int total_parties = 0;
        int t, id = 0;
        bool to;
        bool flag_for_party_checking = false;

        if (A.is_open()) {

            flag_for_party_checking = false;
            while (getline(A, name)) {
                total_parties++;
            }

            lines = new string[total_parties+1];
            int k = 0;
            A.clear();
            A.seekg(0, ios::beg);

            while (getline(A, lines[k])) { k++; }
            k = 0;

            while (k <= total_parties) {

                istringstream ss(lines[k]);
                ss >> name >> symb >> id >> user >> pass >> t >> t >> t >> to;

                if (name == political_party->name or symb == political_party->symbol or id == political_party->symbol_id
                    or user == political_party->username or pass == political_party->password) {
                    flag_for_party_checking = true;
                    if (name == political_party->name) {
                        cout << "a party with the same name already exists, party registration failed....\n";
                        break;
                    }
                    else if (symb == political_party->symbol) {
                        cout << "a party with the same symbol already exists, party registration failed....\n";
                        break;
                    }
                    else if (id == political_party->symbol_id) {
                        cout << "a party with the same symbol id already exists, party registration failed....\n";
                        break;
                    }
                    else if (user == political_party->username) {
                        cout << "a party with the same username already exists, party registration failed....\n";
                        break;
                    }
                    else if (pass == political_party->password) {
                        cout << "a party with the same password already exists, party registration failed....\n";
                        break;
                    }
                }
                k++;
            }
            if (flag_for_party_checking == true) {//if party alrerady exists
                A.close();
                delete political_party;
                delete[]lines;
                return 0;
            }
            else if (flag_for_party_checking == false) {
                A.close();
                B.open("parties.txt", ios::app);
                if (B.is_open()) {
                    cout << "file opened\n";
                }
                B << political_party->name << "\t" << political_party->symbol << "\t" << political_party->symbol_id << "\t"
                    << political_party->username << "\t" << political_party->password << "\t" << political_party->total_candidates << "\t"
                    << political_party->total_votes << "\t" << political_party->total_candidates_won << "\t" << "false" << endl;
                B.close();
                delete political_party;
            }
        }
        else {
            cerr << "failed to open the parties.txt file\n";
        }
        delete[]lines;
        A.close();
        B.close();
        return 0;
    }

    bool register_candidate() { cout << "register cand\n"; return 0; }
    bool register_voter() { cout << "reg vot\n"; return 0; }
    bool results(int choice) { cout << "results...\n"; return 1; }
    
    bool send_req_to_party() { cout << "send req\n"; return 0; }
    bool start_voting() { cout << "voting...\n"; return 0; }//every register voter has to vote before ending the voting session
    bool party_login() { return 0; }
    bool voter_login() { return 0; }

};




int main() {
    system("color 0b");
    int choice = 0;
    int which_log_in = 0;//1 for election commision login, 2 for political party login

    Election_Commission EC;

    while (1) {
        cout << "1. Election Commision Log in\n";
        cout << "2. Political Party Log in\n";

        cin >> which_log_in;
        while (which_log_in > 3 or which_log_in < 1) { cerr << "wrong input, try again: "; cin >> which_log_in; }

        if (which_log_in == 1) {
            system("cls");
            if (ec_login() == true) {
                while (true) {

                    cout << "***********************MAIN MENU***********************" << endl;;
                    cout << "1. create/update a constituency\n";
                    cout << "2. create a political party\n";
                    cout << "3. register a candidate\n";
                    cout << "4. send request of a constituent to register against a party(for constituents only)\n";
                    cout << "5. register a Voter\n";
                    cout << "6. start voting\n";
                    cout << "7. show results voting\n";
                    cout << "8. TO go back\n";
                    cout << "choose: "; cin >> choice;
                    while (choice > 9 or choice < 1) { cerr << "wrong choice, try again: "; cin >> choice; }

                    if (choice == 1) {
                        system("cls");
                        EC.create_or_update_constituency();
                    }
                    else if (choice == 2) {
                        system("cls");

                        EC.create_political_party();
                    }
                    else if (choice == 3) {
                        system("cls");

                        EC.register_candidate();
                    }
                    else if (choice == 4) {
                        system("cls");

                        EC.send_req_to_party();
                    }
                    else if (choice == 5) {
                        system("cls");

                        EC.register_voter();
                    }
                    else if (choice == 6) {
                        system("cls");
                        cout << "******************************VOTING******************************\n";

                        EC.start_voting();
                    }
                    else if (choice == 7) {
                        system("cls");

                        cout << "******************************RESULTS******************************\n";
                        cout << "1. show results of all constituents\n";
                        cout << "2. show results of a particular constituency\n";
                        cout << "0. show results of a particular constituency\n";
                        cout << "choose: "; cin >> choice;
                        while (choice < 0 or choice > 2) { cerr << "wrong choice, choose again: "; cin >> choice; }
                        if (choice == 1 or choice == 2) {
                            EC.results(choice);
                        }
                    }
                    else if (choice == 8) { break; }
                }
            }
            else {
                cout << "wrong id or password entered.\n";
            }
        }

        else if (which_log_in == 2) {
            system("cls");
            if (pp_login()) {
                EC.party_login();
            }
            else { cerr << "wrong id or password\n"; }
        }

    }



    cout << "Hello World!\n";


    return 0;
}
