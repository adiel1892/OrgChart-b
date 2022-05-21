#include "sources/OrgChart.hpp"
#include "sources/OrgChart.cpp"
#include <cmath>
using namespace std;
using namespace ariel;

int main(){
    OrgChart org;
    string i_want = "y";
    cout << "Welcome to our organization!" << endl;
    while(i_want != "n"){
        cout << "Do you want to continue?? yes - any key , no - n " << endl;
        cin >> i_want;
        if(i_want == "n"){
            cout << "********************* " << "GOODBYE " << "*********************" << endl;
            break;
        }
        cout << "Choose from the menu the operation you want to do next" << endl;
        cout << "********************** " << "MENU " << "**********************" << endl;
        cout << "1 - Add Root" << endl;
        cout << "2 - Add Sub" << endl;
        cout << "3 - Check if worker in the organization" << endl;
        cout << "4 - Print the organization" << endl;
        cout << "5 - iterator by level order" << endl;
        cout << "6 - iterator by reverse level order" << endl;
        cout << "7 - iterator by pre order" << endl;
        

        string user_choice_s;
        int user_choice;
        cin >> user_choice_s;
        user_choice = stoi(user_choice_s);
        string worker = "";
        string father = "";
        bool flag = false;

        switch(user_choice){
            case 1:
                cout << "Please write the root worker name." << endl;
                cin >> worker;
                org.add_root(worker);
                break;
            case 2:
                if(org.begin_level_order().getNodes().size() == 0){
                    cout << "The organization is empty! cant add subs" << endl;
                    break;
                }
                while(!flag){
                    cout << "Please write the father worker name that you want to add to." << endl;
                    cin >> father;
                    if(org.in_the_org(father)){
                        flag = true;
                    }else{
                        cout << "Please insert a father that he is part of the organization." << endl;
                    }
                }
                cout << "Please write the sub worker name." << endl;
                cin >> worker;
                org.add_sub(father , worker);
                break;
            case 3:
                cout << "Please insert the worker name to check if he is part of the organization" << endl;
                cin >> worker;
                if(org.in_the_org(worker)){
                    cout << "Yes! " << worker << " is part of the organization!" << endl;
                }else{
                    cout << "No! " << worker << " is not part of the organization" << endl;
                }
                break;
            case 4:
                cout << "Printing the organization..." << endl;
                cout << org << endl;
                break;
            case 5:
                cout << "iterator by level order" << endl;
                for (auto it = org.begin_level_order(); it != org.end_level_order(); ++it){
                    cout << (*it) << " " ;
                }
                cout << endl;
                break;
            case 6:
                cout << "iterator by reverse level order" << endl;
                for (auto it = org.begin_reverse_order(); it != org.reverse_order(); ++it){
                    cout << (*it) << " " ;
                }
                cout << endl;
                break;
            case 7:
                cout << "iterator by pre order" << endl;
                for (auto it = org.begin_preorder(); it != org.end_preorder(); ++it){
                    cout << (*it) << " " ;
                }
                cout << endl;
                break;
            default:
                cout << "Please insert a valid case." << endl;
                break;
        }

    }
    


    return 0;
}