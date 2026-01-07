#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <ctime>
#include <cmath>
#include "calculator_function.h"

using namespace std;

void DC::ohmsLaw()
{
    string V = "0", I = "0", R = "0";
    int valid = 0;
    auto userInput = [](string &V, string &I, string &R)
    {
        cout << "Enter the Voltage value<\"?\" if unknowns>: ";
        cin >> V;
        cout << "Enter the Current value<\"?\" if unknowns>: ";
        cin >> I;
        cout << "Enter the Resistance value<\"?\" if unknowns>: ";
        cin >> R;
    };
    auto validation = [&valid](string &V, string &I, string &R)
    {
        int v = (V == "?"), i = (I == "?"), r = (R == "?");
        if ((v + i + r) == 0)
        {cout << "There's no unknowns";valid = 1;}
        else if ((v + i + r) > 1){cout << "There's too many unknowns";valid = 1;}
    };
    auto calculation = [](string &V, string &I, string &R)
    {
        try{
            if (V == "?")
            {V = to_string(stod(I) * stod(R));}
            else if (I == "?")
            {I = to_string(stod(V) / stod(R));}
            else if (R == "?")
            {R = to_string(stod(V) / stod(I));}
        }
        catch (...){cout << "\033[1;31mInvalid value\033[0\n";}
    };
    auto display = [](string &V, string &I, string &R)
    {
        try{double v = stod(V), i = stod(I), r = stod(R);}catch(...){return;}
        cout<<fixed<<setprecision(4);
        cout<<"Voltage = "<<stod(V)<<" V"<<endl;
        cout<<"Current = "<<stod(I)<<" A"<<endl;
        cout<<"Resistance = "<<stod(R)<<" Ω"<<endl; };
    auto savefile =[](string V, string I, string R){
        time_t now = time(0);
        ofstream file("CalculatorHistory.txt",ios::app);
        try{double v = stod(V), i = stod(I), r = stod(R);}catch(...){return;}
        file<<endl<<ctime(&now)<<endl;
        file<<"==OHM'S LAW==\n";
        file<<fixed<<setprecision(4);
        file<<"Voltage = "<<stod(V)<<" V"<<endl;
        file<<"Current = "<<stod(I)<<" A"<<endl;
        file<<"Resistance = "<<stod(R)<<" Ω"<<endl;
        file.close();
    };
    userInput(V, I, R);
    validation(V, I, R);
    if (valid == 1)
    {
        return;
    }
    calculation(V, I, R);
    display(V, I, R);
    savefile(V,I,R);
}

void DC::equivalentResistance()
{
    char choice;
    char options[4] = {'S', 'P', 's', 'p'};
    time_t now = time(0);
    ofstream file("CalculatorHistory.txt",ios::app);
    file <<endl<<ctime(&now)<<endl;
    file <<"==Equivalent Resistor==\n";
    file <<fixed<<setprecision(3);

    auto userChoice = [&choice]()
    {
        cout << "What type of resistor configuration you want to find?\n";
        cout << "<S if series>\n<P if parallel>\n";
        cin >> choice;
    };
    auto parallel = [](ofstream &file)
    {
        int count;
        double sumResistance = 0;
        file<<"Use choice : Parallel\n";
        cout << "How many resistor ? ";
        while(true){
            cin >> count;
            if(cin.fail()){
                cout<<"\n\033[1;31mInvalid input\nTry Again !\033[0m\n";
                cin.clear();
                cin.ignore(1000,'\n');
            }
            else{
                file<<"How many resitor : "<<count<<endl;
                break;}
        }
        for (int i = 0; i < count; i++)
        {
            double temp = 0;
            cout << "Enter the #" << i + 1 << " value of the resistor:";
            while(true){
            cin >> temp;
            if(cin.fail()){
                cout<<"\n\033[1;31mInvalid input\nTry Again !\033[0m\n";
                cin.clear();
                cin.ignore(1000,'\n');
            }
            else{
                file<< "The #" << i + 1 << " value of the resistor:"<<temp<<" Ω\n";
                break;}
        }
            sumResistance += 1 / temp;
        }
        cout << fixed << setprecision(3);
        cout << "The equivalent value of resistor is " << (1 / sumResistance) << " Ω\n";
        file << "The equivalent value of resistor is " << (1 / sumResistance) << " Ω\n";
    };
    auto series = [](ofstream &file)
    {
        int count;
        double sumResistance = 0;
        file<<"Use choice : Parallel\n";
        cout << "How many resistor ? ";
        while(true){
            cin >> count;
            if(cin.fail()){
                cout<<"\n\033[1;31mInvalid input\nTry Again !\033[0m\n";
                cin.clear();
                cin.ignore(1000,'\n');
            }
            else{
                file<<"How many resitor : "<<count<<endl;
                break;}
        }
        for (int i = 0; i < count; i++)
        {
            double temp = 0;
            cout << "Enter the #" << i + 1 << " value of the resistor:";
            while(true){
            cin >> temp;
            if(cin.fail()){
                cout<<"\n\033[1;31mInvalid input\nTry Again !\033[0m\n";
                cin.clear();
                cin.ignore(1000,'\n');
            }
            else{
                file<< "The #" << i + 1 << " value of the resistor:"<<temp<<" Ω\n";
                break;}
            }
            sumResistance += temp;
        }   

        cout << fixed << setprecision(3);
        cout << "The equivalent value of resistor is " << sumResistance << " Ω\n";
        file << "The equivalent value of resistor is " << sumResistance << " Ω\n";
    };
    while (true)
    {
        userChoice();
        switch (choice)
        {
        case ('S'):
        case ('s'):
        {
            series(file);
            file.close();
            return;
        }
        case ('P'):
        case ('p'):
        {
            parallel(file);
            file.close();
            return;
        }

        default:
        {
            cout << "\033[1;31mInvalid input\nTry Again !\033[0m\n";
            cin.clear();
            cin.ignore(1000,'\n');
            break;
        }
        }
    }
}
void DC::equivalentCapacitance(){
    char choice;
    char options[4] = {'S', 'P', 's', 'p'};
    time_t now = time(0);
    ofstream file("CalculatorHistory.txt",ios::app);
    file <<endl<<ctime(&now)<<endl;
    file <<"==Equivalent Capacitor==\n";
    file <<fixed<<setprecision(3);
    auto userChoice = [&choice]()
    {
        cout << "What type of capacitors configuration you want to find?\n";
        cout << "<S if series>\n<P if parallel>\n<unit in uF>\n";
        cin >> choice;
    };
    auto series = [](ofstream &file)
    {
        int count;
        double sumCapacitance = 0;
        file<<"User Choice = Series\n";
        cout << "How many capacitor ? ";
        while(true){
            cin >> count;
            if(cin.fail()){
                cout<<"\n\033[1;31mInvalid input\nTry Again !\033[0m\n";
                cin.clear();
                cin.ignore(1000,'\n');
            }
            else{
                file<<"How many capacitor : "<<count<<endl;
                break;}
        }
        for (int i = 0; i < count; i++)
        {
            double temp = 0;
            cout << "Enter the #" << i + 1 << " value of the capacitor:";
            while(true){
            cin >> temp;
            if(cin.fail()){
                cout<<"\n\033[1;31mInvalid input\nTry Again !\033[0m\n";
                cin.clear();
                cin.ignore(1000,'\n');
            }
            else{
                file<< "The #" << i + 1 << "  value of the capacitor: "<<temp<<" uF\n";
                break;}
        }
            sumCapacitance += 1 / temp;
        }
        cout << fixed << setprecision(3);
        cout << "The equivalent value of capacitor is " << (1 / sumCapacitance) << " uF";
        file << "The equivalent value of capacitor is " << (1 / sumCapacitance) << " uF\n";
    };
    auto parallel = [](ofstream &file)
    {
        int count;
        double sumCapacitance = 0;
        file<<"User Choice = Parallel\n";
        cout << "How many capacitor ? ";
        while(true){
            cin >> count;
            if(cin.fail()){
                cout<<"\n\033[1;31mInvalid input\nTry Again !\033[0m\n";
                cin.clear();
                cin.ignore(1000,'\n');
            }
            else{break;}
        }
        for (int i = 0; i < count; i++)
        {
            double temp = 0;
            cout << "Enter the #" << i + 1 << " value of the capacitor:";
            while(true){
            cin >> temp;
            if(cin.fail()){
                cout<<"\n\033[1;31mInvalid input\nTry Again !\033[0m\n";
                cin.clear();
                cin.ignore(1000,'\n');
            }
            else{
                file<< "The #" << i + 1 << " value of the capacitor:"<<temp<<" uF\n";
                break;}
            }
            sumCapacitance += temp;
        }
        cout << fixed << setprecision(3);
        cout << "The equivalent value of capacitor is " << sumCapacitance << " uF";
        file << "The equivalent value of capacitor is " << sumCapacitance << " uF\n";
    };
    while (true)
    {
        userChoice();
        switch (choice)
        {
        case ('P'):
        case ('p'):
        {
            parallel(file);
            file.close();
            return;
        }
        case ('S'):
        case ('s'):
        {
            series(file);
            file.close();
            return;
        }

        default:
        {
            cout<<"\n\033[1;31mInvalid input\nTry Again !\033[0m\n";
            cin.clear();
            cin.ignore(1000,'\n');
            break;
        }
        }
    }
}
void DC::equivalentInductance(){
char choice;
char options[4] = {'S', 'P', 's', 'p'};
time_t now = time(0);
ofstream file("CalculatorHistory.txt",ios::app);
file <<endl<<ctime(&now)<<endl;
file <<"==Equivalent Inductor==\n";
auto userChoice = [&choice]()
{
    cout << "What type of inductors configuration you want to find?\n";
    cout << "<S if series>\n<P if parallel>\n<unit in mH>\n";
    cin >> choice;
};
auto parallel = [](ofstream &file)
{
    int count;
    double sumInductance = 0;
    file<<"User Choice: Parallel\n";
    cout << "How many inductor ? ";
    while(true){
            cin >> count;
            if(cin.fail()){
                cout<<"\n\033[1;31mInvalid input\nTry Again !\033[0m\n";
                cin.clear();
                cin.ignore(1000,'\n');
            }
            else{
                file<<"How many inductor : "<<count<<endl;
                break;}
        }
    for (int i = 0; i < count; i++)
    {
        double temp = 0;
        cout << "Enter the #" << i + 1 << " value of the inductor:";
        while(true){
            cin >> temp;
            if(cin.fail()){
                cout<<"\n\033[1;31mInvalid input\nTry Again !\033[0m\n";
                cin.clear();
                cin.ignore(1000,'\n');
            }
            else{
                file<< "The #" << i + 1 << " value of the inductor:"<<temp<<" mH\n";
                break;}
        }
        sumInductance += 1 / temp;
    }
    cout << fixed << setprecision(3);
    cout << "The equivalent value of inductor is " << (1 / sumInductance) << " mH";
    file << "The equivalent value of inductor is " << 1/sumInductance << " Ω\n";
};
auto series = [](ofstream &file)
{
    int count;
    double sumInductance = 0;
    file<<"User Choice: Series\n";
    cout << "How many inductor ? ";
    while(true){
            cin >> count;
            if(cin.fail()){
                cout<<"\n\033[1;31mInvalid input\nTry Again !\033[0m\n";
                cin.clear();
                cin.ignore(1000,'\n');
            }
            else{
                file<<"How many inductor : "<<count<<endl;
                break;}
        }
    for (int i = 0; i < count; i++)
    {
        double temp = 0;
        cout << "Enter the #" << i + 1 << " value of the inductor:";
        while(true){
            cin >> temp;
            if(cin.fail()){
                cout<<"\n\033[1;31mInvalid input\nTry Again !\033[0m\n";
                cin.clear();
                cin.ignore(1000,'\n');
            }
            else{
                file<< "The #" << i + 1 << " value of the inductor:"<<temp<<" mH\n";
                break;}
        }
        sumInductance += temp;
    }
    cout << fixed << setprecision(3);
    cout << "The equivalent value of inductor is " << sumInductance << " mH";
    file << "The equivalent value of inductor is " << sumInductance << " mH\n";
};
while (true)
{
    userChoice();
    switch (choice)
    {
    case ('S'):
    case ('s'):
    {
        series(file);
        file.close();
        return;
    }
    case ('P'):
    case ('p'):
    {
        parallel(file);
        file.close();
        return;
    }

    default:
    {
        cout<<"\n\033[1;31mInvalid input\nTry Again !\033[0m\n";
        cin.clear();
        cin.ignore(1000,'\n');
        break;
    }
    }
}
}
void DC::deltaWye(){
    cout<<"R1 opposite Ra\nR2 opposite Rb\nR3 opposite Rc\n";
    double R[3];//Array
    double Req[3]={0,0,0};//Array
    char abc[3] = {'a','b','c'};
    time_t now = time(0);
    ofstream file("CalculatorHistory.txt",ios::app);
    file <<endl<<ctime(&now)<<endl;
    file <<"==Delta-Wye==\n";
    auto userInput = [abc](double *R,ofstream &file){//Pointer
        for(int i=0;i<3;i++){
            cout<<"Enter the value of R"<<abc[i]<<": ";
            while(true){
                cin>>R[i];
                if(cin.fail()){
                    cout<<"\n\033[1;31mInvalid input\nTry Again !\033[0m\n";
                    cin.clear();
                    cin.ignore(1000,'\n');
                }
                else{
                    file<<"The value of R"<<abc[i]<<": "<<R[i]<<endl;
                    break;
                }
            }  
        }
    };
    auto calculation = [](double *R, double *Req){//Pointer
        double sum = R[0]+R[1]+R[2];
        Req[0]=(R[1]*R[2])/sum;
        Req[1]=(R[2]*R[0])/sum;
        Req[2]=(R[0]*R[1])/sum;
    };
    auto display = [](double *Req,ofstream &file){//Pointer
        cout<<fixed<<setprecision(4);
        for(int i = 0;i<3;i++){
            cout<<"Value of R"<<i+1<<" is "<<Req[i]<<" Ω"<<endl;
            file<<"Value of R"<<i+1<<" is "<<Req[i]<<" Ω"<<endl;
        }
    };
    userInput(R,file);
    calculation(R,Req);
    display(Req,file);
    file.close();
}
void DC::wyeDelta(){
    cout<<"Ra opposite R1\nRb opposite R2\nRc opposite R3\n";
    double R[3];
    double Req[3]={0,0,0};
    char abc[3] = {'a','b','c'};
    time_t now = time(0);
    ofstream file("CalculatorHistory.txt",ios::app);
    file <<endl<<ctime(&now)<<endl;
    file <<"==Wye-Delta==\n";
    auto userInput = [abc](double *R,ofstream &file){
        for(int i=0;i<3;i++){
            cout<<"Enter the value of R"<<i+1<<": ";
            while(true){
                cin>>R[i];
                if(cin.fail()){
                    cout<<"\n\033[1;31mInvalid input\nTry Again !\033[0m\n";
                    cin.clear();
                    cin.ignore(1000,'\n');
                }
                else{
                    file<<"The value of R"<<i+1<<": "<<R[i]<<endl;
                    break;}
            }  
        }
    };
    auto calculation = [](double *R, double *Req){
        double sum ;
        sum = R[0]*R[1] + R[1]*R[2] + R[2]*R[0];
        for(int i = 0; i<3; i++){
            Req[i] = sum/R[i];
        }
    };
    auto display = [abc](double *Req,ofstream &file){
        cout<<fixed<<setprecision(4);
        for(int i = 0;i<3;i++){
            cout<<"Value of R"<<abc[i]<<" is "<<Req[i]<<" Ω"<<endl;
            file<<"Value of R"<<abc[i]<<" is "<<Req[i]<<" Ω"<<endl;
        }
    };

    userInput(R,file);
    calculation(R,Req);
    display(Req,file);
    file.close();
}

void AC::impedance(){
    const double pi = 3.14159265;
    double freq=50,C=0,L=0,R=0,Z=0;
    char choice;
    time_t now = time(0);
    ofstream file("CalculatorHistory.txt",ios::app);
    file <<endl<<ctime(&now)<<endl;
    file <<"==Impedance==\n";
    auto userInput = [](double &freq, double &C,double &L,double &R){
        while(true){
            cout<<"Enter the value of Frequency(Hz): ";
            cin>>freq;
            cout<<"Enter the value of Resistor(Ω): ";
            cin>>R;
            cout<<"Enter the value of Inductor(H): ";
            cin>>L;
            cout<<"Enter the value of Capacitance(F): ";
            cin>>C;
            if(cin.fail()){
                cout<<"\n";
                cout<<"\033[1;31mInvalid input\nTry Again\033[0m\n";
                cin.clear();
                cin.ignore(1000,'\n');
            }
            else{break;}
        }
        ;
    };
    auto calculation = [pi](double &freq, double &C,double &L, ofstream &file,double R){
        if(freq == 0){cout<<"Frequency cannot be 0, set frequency = 50 Hz\n";freq = 50;}
        file<<"The value of Frequency(Hz): "<<freq<<endl
            <<"The value of Resistor(Ω): "<<R<<endl
            <<"The value of Inductor(H): "<<L<<endl
            <<"the value of Capacitor(F):"<<C<<endl;
        if (!(C == 0)){C = 1/(2*pi*freq*C);}
        if (!(L == 0)){L = 2*pi*freq*L;}
        file<<"The value of X_L(Ω):"<<L<<endl
            <<"The value of X_C(Ω):"<<C<<endl;
    };
    auto parallel = [](double R, double L, double C, double &Z){
        double r;
        if (R == 0 ){r = 0;}
        else{r = 1/R;}
        if (L != 0 && C != 0){Z = 1/sqrt(((r)*(r))+(((1/L)-(1/C))*((1/L)-(1/C))));}
        else if ( L == 0){Z = 1/sqrt(((r)*(r))+((-(1/C))*((-(1/C)))));}
        else if ( C == 0){Z = 1/sqrt(((r)*(r))+(((1/L))*((1/L))));}
    };

    auto series = [](double R, double L, double C, double &Z){
        Z= sqrt((R*R)+((L-C)*(L-C)));
    };

    userInput(freq,C,L,R);
    calculation(freq,C,L,file,R);
    cout<<"Enter circuit configuration\n<S for series>\n<P for parallel>\n";
    cin>>choice;
    switch (choice)
    {
    case 'P':
    case 'p':
        file<<"User Choice: Parallel\n";
        parallel(R,L,C,Z);
        break;
    case 'S':
    case 's':
        file<<"User Choice: Series\n";
        series(R,L,C,Z);
        break;
    default:
        break;
    }
    cout<<"#Frequency("<<freq<<" Hz)\n";
    cout<<fixed<<setprecision(3);
    if(Z <=0.01){
        cout<<"Impedance, Z = "<<Z*1000<<" mΩ";
        file<<"Impedance, Z = "<<Z*1000<<" mΩ";
    }
    else{
        cout<<"Impedance, Z ="<<Z<<" Ω";
        file<<"Impedance, Z = "<<Z<<" Ω";
    }
    file<<"\n";
    file.close();
}