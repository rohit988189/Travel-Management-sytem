#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Bill {
public:
    float totalBill;

    Bill() : totalBill(0) {}  // Constructor initializes totalBill to 0
};

class Travel : public Bill {
public:
    int departureCity, arrivalCity, mode;
    float travelBill = 0, returnTravelBill = 0;

    void selectCities();
    void chooseTransport();
    void applyTravelDiscount();
    void applyReturnDiscount();
};

class Hotel : public Travel {
public:
    float hotelBill = 0;

    void bookHotel();
    void generateInvoice(const string& user);
};

// Function to Select Departure and Arrival Cities
void Travel::selectCities() {
    while (true) {
        cout << "\nDestinations: \n1) Delhi\n2) Mumbai\n3) Chennai";
        cout << "\nEnter Departure City: ";
        cin >> departureCity;
        cout << "Enter Arrival City: ";
        cin >> arrivalCity;

        if (departureCity == arrivalCity) {
            cout << "Error: Departure and Arrival cities cannot be the same! Try again.\n";
        } else {
            break;
        }
    }
}

// Function to Choose Mode of Transport
void Travel::chooseTransport() {
    cout << "\nMode of Transport:\n1) Airplane\n2) Train\n3) Bus";
    cout << "\nEnter Choice: ";
    cin >> mode;

    vector<vector<int>> travelCosts = {
        {5000, 4000, 3000},  // Costs for traveling to Delhi
        {6000, 5500, 2500},  // Costs for traveling to Mumbai
        {4000, 2500, 2000}   // Costs for traveling to Chennai
    };

    if (arrivalCity >= 1 && arrivalCity <= 3 && mode >= 1 && mode <= 3) {
        travelBill = travelCosts[arrivalCity - 1][mode - 1];
        cout << "\nTravel Cost: Rs " << travelBill;
    } else {
        cout << "\nInvalid choice, please restart.\n";
        exit(1);
    }
}

// Apply Travel Discount
void Travel::applyTravelDiscount() {
    int discountType;
    cout << "\n\nDiscount Type:\n1) Student (15%)\n2) Business (20%)\n3) Tourist (No Discount)";
    cout << "\nEnter Choice: ";
    cin >> discountType;

    switch (discountType) {
        case 1: travelBill *= 0.85; cout << "Student Discount Applied!\n"; break;
        case 2: travelBill *= 0.80; cout << "Business Discount Applied!\n"; break;
        case 3: cout << "No Discount Applied.\n"; break;
        default: cout << "Invalid Choice! No discount applied.\n"; break;
    }
    totalBill += travelBill;
}

// Apply Return Travel Discount
void Travel::applyReturnDiscount() {
    if (departureCity >= 1 && departureCity <= 3 && mode >= 1 && mode <= 3) {
        vector<vector<int>> returnCosts = {
            {3500, 2800, 2100},  // Return to Delhi
            {4200, 3850, 1750},  // Return to Mumbai
            {2800, 1750, 1400}   // Return to Chennai
        };

        returnTravelBill = returnCosts[departureCity - 1][mode - 1] * 0.7; // 30% discount on return
        cout << "Return Ticket Cost (30% discount applied): Rs " << returnTravelBill << endl;
        totalBill += returnTravelBill;
    }
}

// Function to Book Hotel
void Hotel::bookHotel() {
    vector<vector<int>> hotelPrices = {
        {1500, 1250, 1000},  // Delhi Hotels
        {2500, 2000, 1800},  // Mumbai Hotels
        {1850, 1500, 1300}   // Chennai Hotels
    };

    cout << "\nChoose a Hotel in Arrival City:\n1) Premium\n2) Deluxe\n3) Standard";
    cout << "\nEnter Hotel Choice: ";
    int hotelChoice, stayDuration;
    cin >> hotelChoice;
    cout << "Enter Number of Days: ";
    cin >> stayDuration;

    if (hotelChoice >= 1 && hotelChoice <= 3) {
        hotelBill = hotelPrices[arrivalCity - 1][hotelChoice - 1] * stayDuration;
        cout << "\nHotel Cost: Rs " << hotelBill;

        // Apply the same discount type as travel
        int discountType;
        cout << "\nEnter Discount Type (1 - Student (10%), 2 - Business (15%), 3 - Tourist (No Discount)): ";
        cin >> discountType;
        switch (discountType) {
            case 1: hotelBill *= 0.90; cout << "Student Discount Applied!\n"; break;
            case 2: hotelBill *= 0.85; cout << "Business Discount Applied!\n"; break;
            case 3: cout << "No Discount Applied.\n"; break;
            default: cout << "Invalid Choice! No discount applied.\n"; break;
        }
    } else {
        cout << "\nInvalid Choice! No hotel booked.\n";
        return;
    }

    totalBill += hotelBill;
}

// Function to Generate Invoice
void Hotel::generateInvoice(const string& user) {
    vector<string> cityNames = {"Delhi", "Mumbai", "Chennai"};
    vector<string> transportModes = {"Airplane", "Train", "Bus"};

    cout << "\n\n====== INVOICE ======";
    cout << "\nUser: " << user;
    cout << "\nFrom: " << cityNames[departureCity - 1] << " To: " << cityNames[arrivalCity - 1];
    cout << "\nMode: " << transportModes[mode - 1];
    cout << "\nTravel Cost: Rs " << travelBill;
    cout << "\nReturn Travel Cost: Rs " << returnTravelBill;
    cout << "\nHotel Cost: Rs " << hotelBill;
    cout << "\nTotal Cost: Rs " << totalBill;
    cout << "\n=====================\n";

    // Save invoice to file
    ofstream file("Trip_Invoice.txt", ios::app);
    file << "User: " << user << "\n"
         << "From: " << cityNames[departureCity - 1] << " To: " << cityNames[arrivalCity - 1] << "\n"
         << "Mode: " << transportModes[mode - 1] << "\n"
         << "Travel Cost: Rs " << travelBill << "\n"
         << "Return Travel Cost: Rs " << returnTravelBill << "\n"
         << "Hotel Cost: Rs " << hotelBill << "\n"
         << "Total Cost: Rs " << totalBill << "\n\n";
    file.close();
}

int main() {
    string user;
    cout << "\n***** TRIP PLANNER SYSTEM *****";
    cout << "\nEnter Your Name: ";
    cin >> user;

    Hotel trip;
    trip.selectCities();
    trip.chooseTransport();
    trip.applyTravelDiscount();

    cout << "\nDo you want a return trip? (1-Yes / Any other key-No): ";
    int choice;
    cin >> choice;
    if (choice == 1) trip.applyReturnDiscount();

    cout << "\nDo you want to book a hotel? (1-Yes / Any other key-No): ";
    cin >> choice;
    if (choice == 1) trip.bookHotel();

    trip.generateInvoice(user);
    cout << "\nThank You for Using Our Service!\n";
    return 0;
}
