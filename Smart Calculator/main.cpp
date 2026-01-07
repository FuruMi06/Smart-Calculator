// SMART CALCULATOR
//C++ 11+
#include"calculator_function.h"
#include <iostream>

using namespace std;

int main(){

    DC dc;
    AC ac;
    bool flag = true;
    cout<<"\033[0m\n";
    while(flag){
        int choice;
        cout<<"What do you want to do?\n"
            <<"1. Unknowns V=IR\n"
            <<"2. Equivalent Resistor\n"
            <<"3. Equivalent Capacitor\n"
            <<"4. Equivalent Inductor\n"
            <<"5. Delta-Wye\n"
            <<"6. Wye-Delta\n"
            <<"7. Impedance(AC)\n"
            <<"0. ===END==\n\n";
        while(true){
            cin>>choice;
            if(cin.fail()){
                cout<<"\033[1;31mInvalid input\nTry Again\033[0m\n";
                cin.clear();
                cin.ignore(1000,'\n');
            }
            else{break;}
        }
        switch (choice)
        {
        case 1:
            dc.ohmsLaw();
            break;
        case 2:
            dc.equivalentResistance();
            break;
        case 3:
            dc.equivalentCapacitance();
            break;
        case 4:
            dc.equivalentInductance();
            break;
        case 5:
            dc.deltaWye();
            break;
        case 6:
            dc.wyeDelta();
            break;
        case 7:
            ac.impedance();
            break;
        case 0:
            cout<<"\033[1;32mExiting...\033[0m\n";
            return 0;
        default:
            break;
        }
        char つづく;
        bool flag2 = true;
        cout<<"\nDo you want to continue? <Y/N>\n";
        while(flag2){
            cin>>つづく;
            switch (つづく)
            {
            case 'Y':
            case 'y':
                flag = true;
                flag2 = false;
                break;
            case 'N':
            case 'n':
            cout<<"\033[1;32mExiting...\033[0m\n";
                return 0;
            default:
                cout<<"\033[1;31mInvalid input\nTry Again\033[0m\n";
                cin.clear();
                cin.ignore(1000,'\n');
                flag2 = true;
                break;
            }
        }
    }
    return 0;
}