#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include<stdio.h>
using namespace std;

struct customer
{
    char name[30], member, room, zone, student, birthday;
    int people, time, hour, food, qtyFood;
    double total;
};

void menu();
int mainScreen();
void booking(customer[],int&);
void orderFood(customer[],int&,double&,double&);
void totalPayment(customer[],int&,double&,double&);
void confirm(customer[],int&,char[][20],char[][20],char[][35]);
void receipt(customer[],int&,char[],char[][20],char[][20],char[][35]);
int allBookings(customer[],int&);
void logout(int);

int main()
{
	system("COLOR F0");

    char username[10]={"Siti"}, user[10], myPass[20]={"genius"}, pass[20], choice='Y';
    bool password=false;
    int choice2, returnScreen, noOfCustomer=0;
    double totalDiscount=0, price=0;
    char zoneName[2][20]={"No Smoking Zone","Smoking Zone"};
    char roomName[2][20]={"Regular Room","VIP Room"};
    char hourName[4][35]={"Breakfast Hour","Lunch Hour (- 15% original price)","Happy Hour (FREE food)","Owl Hour (EXTRA 1 hour karaoke)"};
    customer CUSTOMERS[noOfCustomer+1];

	system("COLOR F0");

    //Login
    cout << "\n\t\t\t\t Employee Login" << endl;
    cout << setw(48) << "----------------" << endl;
    cout << "\t\t\t\t Username: ";
    cin >> user;
    cout << "\t\t\t\t Password: ";
    cin >> pass;

	system("COLOR FC");

    //Check username and password
    if(strcmp(user,username)==0 && strcmp(pass,myPass) == 0)
    {
        system("cls");
        password=true;
        cout << setfill ('-') << setw (80) << "-";
        cout << "\n\t\t\t\tWelcome back, " << user << "!" << endl;
        cout << "\n\t\t\t\t    Signing in..." << endl << endl;
        for (int j = 0; j < 3; j++)
        {
            cout << "\r\t\t\t\t    Please Wait   \r\t\t\t\t    Please Wait";
            for (int i = 0; i < 3; i++)
            {
                for(int x = 0; x < 40000000; x++)
                    continue;
                cout << ".";
            }
        }
        system("cls");
    }
    else
    {
        cout << endl << setfill ('-') << setw (80) << "-";
        cout << "\n\t\t\t\t Access denied.";
        cout << "\n\t\t\t Incorrect password or username." << endl;
        cout << setfill ('-') << setw (80) << "-";
    }

	system("COLOR 17");

    //All process
    while(password==true && tolower(choice) == 'y')
    {
        totalDiscount=0, price=0;
        choice2=mainScreen();
        system("cls");
        if(choice2 == 1)
        {
        	system("COLOR 03");

            menu();
            booking(CUSTOMERS,noOfCustomer);
            totalPayment(CUSTOMERS,noOfCustomer,totalDiscount,price);
            system("cls");
            orderFood(CUSTOMERS,noOfCustomer,totalDiscount,price);
            system("COLOR F1");
            confirm(CUSTOMERS,noOfCustomer,zoneName,roomName,hourName);
            system("COLOR 1F");
            cout << "\n\n   Confirm (Y / N): ";
            cin >> choice;
            if(tolower(choice) == 'y')
            {
                receipt(CUSTOMERS,noOfCustomer,user,zoneName,roomName,hourName);
                noOfCustomer++;

            }
            else
            {
                system("cls");
                menu();
                booking(CUSTOMERS,noOfCustomer);
                totalPayment(CUSTOMERS,noOfCustomer,totalDiscount,price);
                system("cls");
                orderFood(CUSTOMERS,noOfCustomer,totalDiscount,price);
                system("COLOR F1");
                confirm(CUSTOMERS,noOfCustomer,zoneName,roomName,hourName);
                system("COLOR 1F");
                receipt(CUSTOMERS,noOfCustomer,user,zoneName,roomName,hourName);
                noOfCustomer++;
                cout << "\n\n   Confirm (Y / N): ";
                cin >> choice;
            }
            system("cls");
        }
        else if(choice2 == 2)
        {
            returnScreen=allBookings(CUSTOMERS,noOfCustomer);
            system("cls");
        }
        else
        {
        	system("COLOR F0");
            if(choice2 == 3)
            {
                password = false;
                logout(choice2);
            }
        }
    }
    system("PAUSE");

}

int mainScreen()
{
    int choice2;
    cout << "\n\t\t\t           ORANGE BOX KARAOKE" << endl;
    cout << "\t\t           Opening hour: 10:00 AM - 4:00 AM" << endl;
    cout << "   " << setw(74) << setfill('-') << "-" << endl;
    cout << "\n\n\t\t       1. New Booking      2. View All Bookings" << endl;
    cout << "\n\t\t       3. Log Out" << endl;
    cout << "   " << setw(74) << setfill('-') << "-" << endl;
    cout << "   Choice: ";
    cin >> choice2;
    return choice2;
}

void menu()
{
    //Display Menu
    cout << "\n\t\t\t        ORANGE BOX KARAOKE" << endl;
    cout << "\t\t        Opening hour: 10:00 AM - 4:00 AM" << endl;
    cout << "\n\n  Pricing (Per Person)" << endl;
    cout << "  " << setw(71) << setfill('-') << "-" << endl;
    cout << "  ROOM TYPE/HOUR |   2 HOURS   |   3 HOURS   |   4 HOURS   |   5 HOURS   " <<endl;
    cout << "  " << setw(71) << setfill('-') << "-" << endl;
    cout << "  [R] Regular \t |    RM 15    |    RM 20    |    RM 25    |    RM 30    " << endl;
    cout << "  [V] VIP \t |    RM 35    |    RM 40    |    RM 45    |    RM 50    " << endl;
    cout << "  " << setw(71) << setfill('-') << "-" << endl;
    cout << "\t\t      [A] No Smoking Zone / [B] Smoking Zone" << endl;
    cout << "  " << setw(71) << setfill('-') << "-" << endl;
}

void booking(customer CUSTOMERS[], int& noOfCustomer)
{
    //Get Customers' Details
    cin.ignore();
    cout << "\n\n   Customer's name           : ";
    cin.getline(CUSTOMERS[noOfCustomer].name,30);
    cout << "   Membership Card (Y / N)   : ";
    cin >> CUSTOMERS[noOfCustomer].member;
    cout << "   Number of people          : ";
    cin >> CUSTOMERS[noOfCustomer].people;
    cout << "   Zone (A / B)              : ";
    cin >> CUSTOMERS[noOfCustomer].zone;
    cout << "   Type of room (R / V)      : ";
    cin >> CUSTOMERS[noOfCustomer].room;
    cout << "   Booking time (24 hrs)     : ";
    cin >> CUSTOMERS[noOfCustomer].time;
    cout << "   Number of hours           : ";
    cin >> CUSTOMERS[noOfCustomer].hour;
    cout << "   Student Card (Y / N)      : ";
    cin >> CUSTOMERS[noOfCustomer].student;
    cout << "   Birthday Special (Y / N)  : ";
    cin >> CUSTOMERS[noOfCustomer].birthday;
}

void orderFood(customer CUSTOMERS[], int& noOfCustomer,double& totalDiscount,double& price)
{
    double food;
    cout << "\n\t\t\t           ORANGE BOX KARAOKE" << endl;
    cout << "\t\t           Opening hour: 10:00 AM - 4:00 AM" << endl;
    cout << "   " << setw(74) << setfill('-') << "-" << endl;
    cout << "\n\n\t\t\t    Current Total Payment: RM " << CUSTOMERS[noOfCustomer].total << endl;
    cout << "\t\t\t" << setw(37) << setfill('-') << "-" << endl;

    //Food Menu
    if(CUSTOMERS[noOfCustomer].time >= 1000 && CUSTOMERS[noOfCustomer].time < 1200)
    {
        //Breakfast Set
        cout << "\t\t         FOOD & DRINKS ORDER (BREAKFAST SET): " << endl << endl;
        cout << "\t\t\t  1. SET A - Nasi Lemak  \t x 1 \n \t\t\t\t     Sandwich \t\t x 1 \n \t\t\t\t     Hot Milo \t\t x 1 \n\t\t\t\t\t\t\t-----" << endl;
        cout << "\t\t\t\t\t\t\tRM 10" << endl << endl;
        cout << "\t\t\t  2. SET B - Nasi Lemak  \t x 2 \n \t\t\t\t     Sandwich \t\t x 2 \n \t\t\t\t     Hot Milo \t\t x 4 \n\t\t\t\t\t\t\t-----" << endl;
        cout << "\t\t\t\t\t\t\tRM 25" << endl << endl;
        cout << "\t\t\t  3. SET C - Nasi Lemak  \t x 2 \n \t\t\t\t     Hot Milo \t\t x 2 \n \t\t\t\t     Teh O \t\t x 2 \n\t\t\t\t\t\t\t-----" << endl;
        cout << "\t\t\t\t\t\t\tRM 30" << endl << endl;
        cout << "   " << setw(74) << setfill('-') << "-" << endl << endl;
    }
    else
    {
        //Normal Set
        cout << "\n\t\t\t\t FOOD & DRINKS ORDER: " << endl << endl;
        cout << "\t\t\t1. SET A - 1 liter Pepsi \t x 1 \n \t\t\t\t   Potato chips \t x 2 \n\t\t\t\t\t\t\t-----" << endl;
        cout << "\t\t\t\t\t\t\tRM 18" << endl << endl;
        cout << "\t\t\t2. SET B - 1 liter Pepsi \t x 2 \n \t\t\t\t   Potato chips \t x 4 \n\t\t\t\t\t\t\t-----" << endl;
        cout << "\t\t\t\t\t\t\tRM 25" << endl << endl;
        cout << "\t\t\t3. SET C - 1 liter Pepsi \t x 2 \n \t\t\t\t   500 ML Ice Lemon Tea  x 2 " << endl;
        cout << " \t\t\t\t   Potato chips \t x 6 \n\t\t\t\t\t\t\t-----" << endl;
        cout << "\t\t\t\t\t\t\tRM 32" << endl << endl;
        cout << "\t\t\t4. None" << endl;
        cout << "   " << setw(74) << setfill('-') << "-" << endl << endl;
    }


    //Order Food
    cout << "\t Set       : ";
    cin >> CUSTOMERS[noOfCustomer].food;
    if(CUSTOMERS[noOfCustomer].food != 4)
    {
        cout << "\t Quantity  : ";
        cin >> CUSTOMERS[noOfCustomer].qtyFood;
    }
    //Food Price
    if(CUSTOMERS[noOfCustomer].time >= 1000 && CUSTOMERS[noOfCustomer].time < 1200)
    {
        if(CUSTOMERS[noOfCustomer].food == 1)
            food=(10*CUSTOMERS[noOfCustomer].qtyFood);
        else if(CUSTOMERS[noOfCustomer].food == 2)
            food=(25*CUSTOMERS[noOfCustomer].qtyFood);
        else
        {
            if(CUSTOMERS[noOfCustomer].food == 3)
                food=(35*CUSTOMERS[noOfCustomer].qtyFood);
        }
    }
    else
    {
        if(CUSTOMERS[noOfCustomer].food == 1)
            food=(18*CUSTOMERS[noOfCustomer].qtyFood);
        else if(CUSTOMERS[noOfCustomer].food == 2)
            food=(25*CUSTOMERS[noOfCustomer].qtyFood);
        else if(CUSTOMERS[noOfCustomer].food == 3)
            food=(32*CUSTOMERS[noOfCustomer].qtyFood);
        else
            food=0;
    }
    //HAPPY HOUR (FREE FOOD)
    if(CUSTOMERS[noOfCustomer].time >= 1400 && CUSTOMERS[noOfCustomer].time < 2200)
        food=0;

    //New Total
    CUSTOMERS[noOfCustomer].total = price+food-totalDiscount;
    system("cls");
}

void totalPayment(customer CUSTOMERS[], int& noOfCustomer, double& totalDiscount, double& price)
{
    //Normal Price
    if(tolower(CUSTOMERS[noOfCustomer].room) == 'r')
    {
        if(CUSTOMERS[noOfCustomer].hour == 2)
            price=CUSTOMERS[noOfCustomer].people*15;
        else if(CUSTOMERS[noOfCustomer].hour == 3)
            price=CUSTOMERS[noOfCustomer].people*20;
        else if(CUSTOMERS[noOfCustomer].hour == 4)
            price=CUSTOMERS[noOfCustomer].people*25;
        else
        {
        if(CUSTOMERS[noOfCustomer].hour == 5)
                price=CUSTOMERS[noOfCustomer].people*30;
        }
    }
    else
    {
        if(tolower(CUSTOMERS[noOfCustomer].room) == 'v')
        {
            if(CUSTOMERS[noOfCustomer].hour == 2)
                price=CUSTOMERS[noOfCustomer].people*35;
            else if(CUSTOMERS[noOfCustomer].hour == 3)
                price=CUSTOMERS[noOfCustomer].people*40;
            else if(CUSTOMERS[noOfCustomer].hour == 4)
                price=CUSTOMERS[noOfCustomer].people*45;
            else
            {
                if(CUSTOMERS[noOfCustomer].hour == 5)
                    price=CUSTOMERS[noOfCustomer].people*50;
            }
        }
    }

    //Discount
    if(tolower(CUSTOMERS[noOfCustomer].member) == 'y')
        totalDiscount = price*0.2;
    else
    {
        if(CUSTOMERS[noOfCustomer].time >= 1200 && CUSTOMERS[noOfCustomer].time < 1400)
            totalDiscount += price*0.15;
        if(CUSTOMERS[noOfCustomer].student == 'Y' || CUSTOMERS[noOfCustomer].student == 'y')
            totalDiscount += price*0.1;
        else
            totalDiscount += 0;
        if(CUSTOMERS[noOfCustomer].birthday == 'Y' || CUSTOMERS[noOfCustomer].birthday == 'y')
            totalDiscount += price*0.05;
        else
            totalDiscount += 0;
    }

    //Total Payment
    CUSTOMERS[noOfCustomer].total = price-totalDiscount;
}

void confirm(customer CUSTOMERS[],int& noOfCustomer,char zoneName[][20],char roomName[][20],char hourName[][35])
{
    cout << "\n\t\t\t           ORANGE BOX KARAOKE" << endl;
    cout << "\t\t           Opening hour: 10:00 AM - 4:00 AM" << endl;
    cout << "   " << setw(74) << setfill('-') << "-" << endl;
    cout << "   Name                     : " << CUSTOMERS[noOfCustomer].name << endl;
    cout << "   Number of people         : " << CUSTOMERS[noOfCustomer].people << " people" << endl;
    cout << "   Number of hours          : " << CUSTOMERS[noOfCustomer].hour << " hours" << endl;
    if(tolower(CUSTOMERS[noOfCustomer].member) == 'y')
    {
        cout << "   Membership Discount      : APPLIED (-20% original price)" << endl;
        if(CUSTOMERS[noOfCustomer].time >= 1200 && CUSTOMERS[noOfCustomer].time < 1400)
            cout << "   Booking Hour             : Lunch Hour" << endl;
    }
    else
    {
        cout << "   Membership Discount      : NOT APPLIED" << endl;
        if(CUSTOMERS[noOfCustomer].time >= 1200 && CUSTOMERS[noOfCustomer].time < 1400)
            cout << "   Booking Hour             : " << hourName[1] << endl;
    }
    //Hour
    if(CUSTOMERS[noOfCustomer].time >= 1000 && CUSTOMERS[noOfCustomer].time < 1200)
            cout << "   Booking Hour             : " << hourName[0] << endl;
    else if(CUSTOMERS[noOfCustomer].time >= 1400 && CUSTOMERS[noOfCustomer].time < 2200)
            cout << "   Booking Hour             : " << hourName[2] << endl;
    else
    {
        if(CUSTOMERS[noOfCustomer].time >= 0000 && CUSTOMERS[noOfCustomer].time < 0400)
            cout << "   Booking Hour             : " << hourName[3] << endl;
    }

    //Zone
    if(tolower(CUSTOMERS[noOfCustomer].zone) == 'a')
        cout << "   Zone                     : " << zoneName[0] << endl;
    else
        cout << "   Zone                     : " << zoneName[1] << endl;
    //Room
    if(tolower(CUSTOMERS[noOfCustomer].room) == 'r')
        cout << "   Type of room             : " << roomName[0] << endl;
    else
        cout << "   Type of room             : " << roomName[1] << endl;
    //Student Card
    if(tolower(CUSTOMERS[noOfCustomer].member) == 'n')
    {
        if(tolower(CUSTOMERS[noOfCustomer].student) == 'y')
            cout << "   Student Card Discount    : APPLIED (-10% original price)" << endl;
        else
            cout << "   Student Card Discount    : NOT APPLIED" << endl;
    }
    //Birthday
    if(tolower(CUSTOMERS[noOfCustomer].member) == 'n')
    {
        if(tolower(CUSTOMERS[noOfCustomer].birthday) == 'y')
            cout << "   Birthday Special Discount: APPLIED (-5% original price)" << endl;
        else
            cout << "   Birthday Special Discount: NOT APPLIED" << endl;
    }
    cout << "\n   TOTAL                    : RM " << CUSTOMERS[noOfCustomer].total << endl;
    cout << "   " << setw(74) << setfill('-') << "-" << endl;
}

void receipt(customer CUSTOMERS[],int& noOfCustomer,char user[], char zoneName[][20],char roomName[][20],char hourName[][35])
{
    //Write Receipt
    ofstream outData;
    outData.open("custReceipt.txt");
    outData << "\t\t\t\t ORANGE BOX KARAOKE" << endl;
    outData << "\t\t\t\t  TEL: 06-2827614" << endl;
    outData << "  " << setw(74) << setfill('-') << "-" << endl;
    outData << "  \t\t\t\t   WORKER: " << user << endl;
    outData << "  " << setw(74) << setfill('-') << "-" << endl;
    outData << "   Name                     \t\t " << CUSTOMERS[noOfCustomer].name << endl;
    outData << "   Number of people         \t\t " << CUSTOMERS[noOfCustomer].people << " people" << endl;
    outData << "   Number of hours          \t\t " << CUSTOMERS[noOfCustomer].hour << " hours" << endl;
    if(tolower(CUSTOMERS[noOfCustomer].member) == 'y')
    {
        outData << "   Membership Discount      \t\t APPLIED (-20% original price)" << endl;
        if(CUSTOMERS[noOfCustomer].time >= 1200 && CUSTOMERS[noOfCustomer].time < 1400)
            outData << "   Booking Hour             \t\t Lunch Hour" << endl;
    }
    else
    {
        outData << "   Membership Discount      \t\t NOT APPLIED" << endl;
        if(CUSTOMERS[noOfCustomer].time >= 1200 && CUSTOMERS[noOfCustomer].time < 1400)
            outData << "   Booking Hour             \t\t " << hourName[1] << endl;
    }
    //Hour
    if(CUSTOMERS[noOfCustomer].time >= 1000 && CUSTOMERS[noOfCustomer].time < 1200)
            outData << "   Booking Hour             \t\t " << hourName[0] << endl;
    else if(CUSTOMERS[noOfCustomer].time >= 1400 && CUSTOMERS[noOfCustomer].time < 2200)
            outData << "   Booking Hour             \t\t " << hourName[2] << endl;
    else
    {
        if(CUSTOMERS[noOfCustomer].time >= 0000 && CUSTOMERS[noOfCustomer].time < 0400)
            outData << "   Booking Hour             \t\t " << hourName[3] << endl;
    }
    //Zone
    if(tolower(CUSTOMERS[noOfCustomer].zone) == 'a')
        outData << "   Zone                     \t\t " << zoneName[0] << endl;
    else
        outData << "   Zone                     \t\t " << zoneName[1] << endl;
    //Room
    if(tolower(CUSTOMERS[noOfCustomer].room) == 'r')
        outData << "   Type of room             \t\t " << roomName[0] << endl;
        outData << "   Type of room             \t\t " << roomName[1] << endl;
    //Student Card
    if(tolower(CUSTOMERS[noOfCustomer].member) == 'n')
    {
        if(tolower(CUSTOMERS[noOfCustomer].student) == 'y')
            outData << "   Student Card Discount    \t\t APPLIED (-10% original price)" << endl;
        else
            outData << "   Student Card Discount    \t\t NOT APPLIED" << endl;
    }
    //Birthday
    if(tolower(CUSTOMERS[noOfCustomer].member) == 'n')
    {
        if(tolower(CUSTOMERS[noOfCustomer].birthday) == 'y')
            outData << "   Birthday Special Discount\t\t APPLIED (-5% original price)" << endl;
        else
            outData << "   Birthday Special Discount\t\t NOT APPLIED" << endl;
    }
    outData << "\n\n   TOTAL                    \t\t RM " << CUSTOMERS[noOfCustomer].total << endl;
    outData << "   " << setw(74) << setfill('-') << "-" << endl;
    outData << "   \t\t\t\t PLEASE COME AGAIN " << endl;
    outData << "  " << setw(74) << setfill('-') << "-" << endl;
    outData.close();
}

int allBookings(customer CUSTOMERS[], int& noOfCustomer)
{
    int returnScreen;
    ifstream inData;
    inData.open("custReceipt.txt");
    if(!inData)
    {
        cout << setfill ('-') << setw (80) << "-";
        cout << "\n\t CUSTOMER'S NAME \t\t HOURS \t\t TOTAL (RM)" << endl;
        cout << setfill ('-') << setw (80) << "-" << endl;
        cout << "\n\n\t\t\t\t No Data Inserted." << endl;
        cout << setfill ('-') << setw (80) << "-";
        cout << "\n\n   1.Return to Screen: ";
        cin >> returnScreen;
    }
    else
    {
        cout << setfill ('-') << setw (80) << "-";
        cout << "\n\t CUSTOMER'S NAME \t\t HOURS \t\t TOTAL (RM)" << endl;
        cout << setfill ('-') << setw (80) << "-" << endl;
        for(int i=0; i<noOfCustomer; i++)
        {

            cout << " (" << i+1 << ") \t " << left << setfill(' ') << setw(35) << CUSTOMERS[i].name << CUSTOMERS[i].hour << " \t\t " << CUSTOMERS[i].total << endl;

        }
        cout << setfill ('-') << setw (80) << "-";
        cout << "\n\n   1. Return to Screen: ";
        cin >> returnScreen;
    }
    inData.close();
    return returnScreen;
}

void logout(int choice2)
{
    cout << setfill ('-') << setw (80) << "-";
    cout << "\n\t\t\t\t    Signing out..." << endl << endl;
    for (int j = 0; j < 3; j++)
    {
        cout << "\r\t\t\t\t    Please Wait   \r\t\t\t\t    Please Wait";
        for (int i = 0; i < 3; i++)
        {
            for(int x = 0; x < 40000000; x++)
                continue;
            cout << ".";
        }
    }
    system("cls");

    cout << "\n\t\t\t\t End of Shift." << endl;
    cout << "\t\t\t      Have a good rest! :)" << endl;
}
