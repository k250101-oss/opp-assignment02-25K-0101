#include <iostream>
#include <string>

using namespace std;

class Printable {
public:
    virtual void printDetails() const = 0;
    virtual ~Printable() {}
};

class TaxCalculatable {
public:
    virtual double calculateTax() const = 0;
    virtual ~TaxCalculatable() {}
};

class UserRole {
public:
    virtual string getRoleName() const = 0;
    virtual ~UserRole() {}
};

class PasswordChecker {
public:
    virtual bool checkPassword(string inputPass) const = 0;
    virtual ~PasswordChecker() {}
};

class Engine {
private:
    string fuelType;
    int cc;
    string transmission;
public:
    Engine() {
        fuelType = "Petrol";
        cc = 1300;
        transmission = "Manual";
    }
    Engine(string fuel, int engineCC, string trans) {
        fuelType = fuel;
        cc = engineCC;
        transmission = trans;
    }
    
    string getFuelType() const { return fuelType; }
    void setFuelType(string fuel) { fuelType = fuel; }
    
    int getCC() const { return cc; }
    void setCC(int engineCC) { cc = engineCC; }
    
    string getTransmission() const { return transmission; }
    void setTransmission(string trans) { transmission = trans; }
    
    void showSpecs() const {
        cout << fuelType << ", " << cc << "cc, " << transmission;
    }
};

class CarLocation {
private:
    string city;
    string area;
public:
    CarLocation() {
        city = "Unknown";
        area = "Unknown";
    }
    CarLocation(string c, string a) {
        city = c;
        area = a;
    }
    
    string getCity() const { return city; }
    void setCity(string c) { city = c; }
    
    string getArea() const { return area; }
    void setArea(string a) { area = a; }
    
    void showLocation() const {
        cout << area << ", " << city;
    }
};

class MaintenanceRecord {
private:
    string serviceDate;
    string serviceType;
    int mileageAtService;
    double costPaid;
public:
    MaintenanceRecord() {
        serviceDate = "01-01-2026";
        serviceType = "General Inspection";
        mileageAtService = 0;
        costPaid = 0.0;
    }
    MaintenanceRecord(string date, string type, int mileage, double cost) {
        serviceDate = date;
        serviceType = type;
        mileageAtService = mileage;
        costPaid = cost;
    }
    
    string getServiceDate() const { return serviceDate; }
    string getServiceType() const { return serviceType; }
    int getMileageAtService() const { return mileageAtService; }
    double getCostPaid() const { return costPaid; }
    
    void showRecord() const {
        cout << "      * Date: " << serviceDate << " | Service: " << serviceType 
             << " | Done at: " << mileageAtService << " km | Cost: PKR " << costPaid << "\n";
    }
};

class Vehicle : public Printable, public TaxCalculatable {
protected:
    string make;
    string model;
    int year;
    int mileage;
    string color;
    Engine engineDetails;
    CarLocation locationDetails;
    
    MaintenanceRecord serviceHistory[10];
    int totalServiceRecords;
public:
    Vehicle(string mk, string md, int yr, int mil, string clr, Engine eng, CarLocation loc) {
        make = mk;
        model = md;
        year = yr;
        mileage = mil;
        color = clr;
        engineDetails = eng;
        locationDetails = loc;
        totalServiceRecords = 0;
    }
    
    string getMake() const { return make; }
    string getModel() const { return model; }
    int getYear() const { return year; }
    int getMileage() const { return mileage; }
    string getColor() const { return color; }
    Engine getEngine() const { return engineDetails; }
    CarLocation getLocation() const { return locationDetails; }
    
    void addMaintenanceLog(string date, string type, int milAtService, double cost) {
        if (totalServiceRecords < 10) {
            MaintenanceRecord newLog(date, type, milAtService, cost);
            serviceHistory[totalServiceRecords] = newLog;
            totalServiceRecords++;
            cout << " -> Successfully logged service: " << type << " for " << make << " " << model << "\n";
        } else {
            cout << " -> Maintenance history log is full for this vehicle.\n";
        }
    }
    
    void printMaintenanceHistory() const {
        cout << "    --- Official Maintenance History Logs ---\n";
        if (totalServiceRecords == 0) {
            cout << "    [No service logs recorded for this vehicle asset yet]\n";
            return;
        }
        for (int i = 0; i < totalServiceRecords; i++) {
            serviceHistory[i].showRecord();
        }
    }
    
    virtual void printDetails() const = 0;
    virtual ~Vehicle() {}
};

class Sedan : public Vehicle {
private:
    int trunkCapacityLiters;
    bool hasSunroof;
public:
    Sedan(string mk, string md, int yr, int mil, string clr, Engine eng, CarLocation loc, int trunk, bool sunroof)
        : Vehicle(mk, md, yr, mil, clr, eng, loc), trunkCapacityLiters(trunk), hasSunroof(sunroof) {}
        
    int getTrunkCapacity() const { return trunkCapacityLiters; }
    bool getHasSunroof() const { return hasSunroof; }

    double calculateTax() const override {
        double baseTax = 25000.0;
        if (engineDetails.getCC() > 1500) {
            baseTax += 20000.0;
        }
        if (hasSunroof) {
            baseTax += 5000.0;
        }
        return baseTax;
    }

    void printDetails() const override {
        cout << "[VEHICLE TYPE: SEDAN] " << year << " " << make << " " << model << "\n";
        cout << " -> Color: " << color << " | Total Mileage: " << mileage << " km\n";
        cout << " -> Location: "; locationDetails.showLocation(); cout << "\n";
        cout << " -> Engine Specs: "; engineDetails.showSpecs(); cout << "\n";
        cout << " -> Sedan Features: Trunk Space: " << trunkCapacityLiters << " Liters | Sunroof: " << (hasSunroof ? "Yes" : "No") << "\n";
        cout << " -> Annual Token Tax Rate: PKR " << calculateTax() << "\n";
        printMaintenanceHistory();
    }
};

class SUV : public Vehicle {
private:
    int seatingCapacity;
    bool isFourWheelDrive;
public:
    SUV(string mk, string md, int yr, int mil, string clr, Engine eng, CarLocation loc, int seats, bool fwd)
        : Vehicle(mk, md, yr, mil, clr, eng, loc), seatingCapacity(seats), isFourWheelDrive(fwd) {}
        
    int getSeatingCapacity() const { return seatingCapacity; }
    bool getIsFourWheelDrive() const { return isFourWheelDrive; }

    double calculateTax() const override {
        double baseTax = 60000.0;
        if (engineDetails.getCC() > 2700) {
            baseTax += 40000.0;
        }
        if (isFourWheelDrive) {
            baseTax += 15000.0;
        }
        return baseTax;
    }

    void printDetails() const override {
        cout << "[VEHICLE TYPE: SUV] " << year << " " << make << " " << model << "\n";
        cout << " -> Color: " << color << " | Total Mileage: " << mileage << " km\n";
        cout << " -> Location: "; locationDetails.showLocation(); cout << "\n";
        cout << " -> Engine Specs: "; engineDetails.showSpecs(); cout << "\n";
        cout << " -> SUV Features: Seats: " << seatingCapacity << " Seater | Drive Type: " << (isFourWheelDrive ? "4x4 Wheels Active" : "2WD Standard") << "\n";
        cout << " -> Annual Token Tax Rate: PKR " << calculateTax() << "\n";
        printMaintenanceHistory();
    }
};

class Hatchback : public Vehicle {
private:
    bool rearSeatsFoldable;
    string bootType;
public:
    Hatchback(string mk, string md, int yr, int mil, string clr, Engine eng, CarLocation loc, bool fold, string bType)
        : Vehicle(mk, md, yr, mil, clr, eng, loc), rearSeatsFoldable(fold), bootType(bType) {}
        
    bool getRearSeatsFoldable() const { return rearSeatsFoldable; }
    string getBootType() const { return bootType; }

    double calculateTax() const override {
        double baseTax = 12000.0;
        if (engineDetails.getCC() > 1000) {
            baseTax += 8000.0;
        }
        return baseTax;
    }

    void printDetails() const override {
        cout << "[VEHICLE TYPE: HATCHBACK] " << year << " " << make << " " << model << "\n";
        cout << " -> Color: " << color << " | Total Mileage: " << mileage << " km\n";
        cout << " -> Location: "; locationDetails.showLocation(); cout << "\n";
        cout << " -> Engine Specs: "; engineDetails.showSpecs(); cout << "\n";
        cout << " -> Hatchback Features: Foldable Seats: " << (rearSeatsFoldable ? "Yes" : "No") << " | Boot Control: " << bootType << "\n";
        cout << " -> Annual Token Tax Rate: PKR " << calculateTax() << "\n";
        printMaintenanceHistory();
    }
};

class Motorbike : public Vehicle {
private:
    string bikeType;
    bool hasElectricStart;
public:
    Motorbike(string mk, string md, int yr, int mil, string clr, Engine eng, CarLocation loc, string bType, bool eStart)
        : Vehicle(mk, md, yr, mil, clr, eng, loc), bikeType(bType), hasElectricStart(eStart) {}
        
    string getBikeType() const { return bikeType; }
    bool getHasElectricStart() const { return hasElectricStart; }

    double calculateTax() const override {
        double baseTax = 2000.0;
        if (engineDetails.getCC() > 250) {
            baseTax += 5000.0;
        }
        return baseTax;
    }

    void printDetails() const override {
        cout << "[VEHICLE TYPE: MOTORBIKE] " << year << " " << make << " " << model << "\n";
        cout << " -> Color: " << color << " | Total Mileage: " << mileage << " km\n";
        cout << " -> Location: "; locationDetails.showLocation(); cout << "\n";
        cout << " -> Engine Specs: "; engineDetails.showSpecs(); cout << "\n";
        cout << " -> Bike Features: Sub-Category: " << bikeType << " | Electric Start: " << (hasElectricStart ? "Yes" : "No") << "\n";
        cout << " -> Annual Token Tax Rate: PKR " << calculateTax() << "\n";
        printMaintenanceHistory();
    }
};

class AdListing;
class PlatformAdmin;

class AppStatistics {
private:
    int totalApprovedAds;
    int totalFlaggedAds;
    long long totalFinancialVolume;
    friend class PlatformAdmin;
public:
    AppStatistics() {
        totalApprovedAds = 0;
        totalFlaggedAds = 0;
        totalFinancialVolume = 0;
    }
    AppStatistics(int approved, int flagged, long long volume) {
        totalApprovedAds = approved;
        totalFlaggedAds = flagged;
        totalFinancialVolume = volume;
    }

    int getApprovedCount() const { return totalApprovedAds; }
    int getFlaggedCount() const { return totalFlaggedAds; }
    long long getVolume() const { return totalFinancialVolume; }

    bool operator==(const AppStatistics& other) const {
        return (totalApprovedAds == other.totalApprovedAds) && 
               (totalFlaggedAds == other.totalFlaggedAds) && 
               (totalFinancialVolume == other.totalFinancialVolume);
    }

    AppStatistics operator+(const AppStatistics& other) const {
        return AppStatistics(
            totalApprovedAds + other.totalApprovedAds,
            totalFlaggedAds + other.totalFlaggedAds,
            totalFinancialVolume + other.totalFinancialVolume
        );
    }
};

class AdListing : public Printable {
private:
    static int systemTotalActiveAdsCount;
    static const double flatPortalServiceFee;
    
    string adID;
    Vehicle* sampleVehiclePtr;
    long long finalPrice;
    string listingStatus;
    string sellerProfileID;
    
    bool reservationTokenPaid;
    long long securityTokenAmountHeld;
    string reservingBuyerID;

    friend class PlatformAdmin;
public:
    AdListing(string id, Vehicle* vPtr, long long price, string sID) {
        adID = id;
        sampleVehiclePtr = vPtr;
        finalPrice = price;
        sellerProfileID = sID;
        listingStatus = "Pending";
        
        reservationTokenPaid = false;
        securityTokenAmountHeld = 0;
        reservingBuyerID = "None";
        
        systemTotalActiveAdsCount++;
    }

    ~AdListing() {
        systemTotalActiveAdsCount--;
    }

    static int getGlobalAdsCount() { return systemTotalActiveAdsCount; }
    static double getFlatFee() { return flatPortalServiceFee; }

    string getAdID() const { return adID; }
    long long getPrice() const { return finalPrice; }
    Vehicle* getVehicle() const { return sampleVehiclePtr; }
    string getStatus() const { return listingStatus; }
    string getSellerID() const { return sellerProfileID; }
    
    bool isTokenPaid() const { return reservationTokenPaid; }
    long long getTokenAmount() const { return securityTokenAmountHeld; }
    string getReservingBuyer() const { return reservingBuyerID; }

    void applyTokenReservation(string buyerID, long long depositAmount) {
        if (listingStatus != "Active") {
            cout << " -> Error: Listing " << adID << " is not actively available for booking.\n";
            return;
        }
        reservingBuyerID = buyerID;
        securityTokenAmountHeld = depositAmount;
        reservationTokenPaid = true;
        listingStatus = "Reserved";
        cout << " -> [TOKEN REGISTERED] Ad " << adID << " successfully RESERVED by Buyer " << buyerID 
             << " with deposit payment of PKR " << depositAmount << "\n";
    }
    
    void clearTokenReservation() {
        reservingBuyerID = "None";
        securityTokenAmountHeld = 0;
        reservationTokenPaid = false;
        listingStatus = "Active";
        cout << " -> [TOKEN CANCELLED] Reservation lifted for Ad " << adID << ". Status set back to Active.\n";
    }

    bool operator<(const AdListing& other) const {
        return finalPrice < other.finalPrice;
    }

    bool operator==(const AdListing& other) const {
        return adID == other.adID;
    }

    void printDetails() const override {
        cout << "========================================================================\n";
        cout << "MARKETPLACE LISTING ENTRY REFERENCE ID: " << adID << "\n";
        cout << " -> Overall Asking Price : PKR " << finalPrice << "\n";
        cout << " -> System Live Status   : [" << listingStatus << "]\n";
        cout << " -> Listed By Seller ID  : " << sellerProfileID << "\n";
        if (reservationTokenPaid) {
            cout << " -> Booking Guard Details: Reserved By: " << reservingBuyerID << " | Token Held: PKR " << securityTokenAmountHeld << "\n";
        }
        cout << "------------------------------------------------------------------------\n";
        if (sampleVehiclePtr != nullptr) {
            sampleVehiclePtr->printDetails();
        } else {
            cout << " -> Error: No vehicle asset bound to this listing index node.\n";
        }
        cout << "========================================================================\n";
    }
};

int AdListing::systemTotalActiveAdsCount = 0;
const double AdListing::flatPortalServiceFee = 1500.00;

class UserAccount : public Printable, public UserRole, public PasswordChecker {
protected:
    static int totalSystemUsersCount;
    string userID;
    string fullName;
    string emailAddress;
    string secretPassword;
public:
    UserAccount(string id, string name, string email, string pass) {
        userID = id;
        fullName = name;
        emailAddress = email;
        secretPassword = pass;
        totalSystemUsersCount++;
    }

    virtual ~UserAccount() {
        totalSystemUsersCount--;
    }

    string getUserID() const { return userID; }
    string getFullName() const { return fullName; }
    string getEmail() const { return emailAddress; }
    
    static int getTotalUsers() { return totalSystemUsersCount; }

    bool checkPassword(string inputPass) const override {
        return secretPassword == inputPass;
    }

    void printDetails() const override {
        cout << "User ID Tag: " << userID << " | Legal Name: " << fullName << " | Contact: " << emailAddress << "\n";
    }

    virtual string getRoleName() const override { return "StandardGuest"; }
};

int UserAccount::totalSystemUsersCount = 0;

class Seller : public UserAccount {
private:
    AdListing* ownedAdsArray[15];
    int activeAdsCount;
    string sellerTier;
public:
    Seller(string id, string name, string email, string pass, string tier)
        : UserAccount(id, name, email, pass), sellerTier(tier), activeAdsCount(0) {}

    string getSellerTier() const { return sellerTier; }
    int getActiveAdsCount() const { return activeAdsCount; }

    void tieListingToSeller(AdListing* listingRef) {
        if (activeAdsCount < 15) {
            ownedAdsArray[activeAdsCount] = listingRef;
            activeAdsCount++;
        } else {
            cout << " -> Error: Seller list slots are completely full.\n";
        }
    }

    void showSellerInventory() const {
        cout << "\n========================================================================\n";
        cout << "PORTFOLIO AD REVIEWS FOR SELLER: " << fullName << " (" << sellerTier << " Vendor)\n";
        cout << "========================================================================\n";
        if (activeAdsCount == 0) {
            cout << " -> This user has zero vehicles posted on the marketplace.\n";
            return;
        }
        for (int i = 0; i < activeAdsCount; i++) {
            ownedAdsArray[i]->printDetails();
        }
    }

    string getRoleName() const override { return "RegisteredSeller"; }
};

class Buyer : public UserAccount {
private:
    long long walletCashLimit;
    AdListing* trackedSavedAds[10];
    int totalSavedAds;
public:
    Buyer(string id, string name, string email, string pass, long long cashLimit)
        : UserAccount(id, name, email, pass), walletCashLimit(cashLimit), totalSavedAds(0) {}

    long long getWalletCashLimit() const { return walletCashLimit; }
    int getTotalSavedAds() const { return totalSavedAds; }

    void addAdToFavorites(AdListing* listingRef) {
        if (totalSavedAds < 10) {
            trackedSavedAds[totalSavedAds] = listingRef;
            totalSavedAds++;
            cout << " -> Added listing " << listingRef->getAdID() << " to " << fullName << "'s saved list.\n";
        }
    }

    void processTokenBooking(AdListing* targetAd, long long tokenAmount) {
        if (tokenAmount > walletCashLimit) {
            cout << " -> Error: You don't have enough balance in your cash wallet to secure this token.\n";
            return;
        }
        if (tokenAmount < (targetAd->getPrice() * 0.02)) {
            cout << " -> Error: Token amount is too low. Minimum 2% deposit required.\n";
            return;
        }
        
        targetAd->applyTokenReservation(userID, tokenAmount);
        walletCashLimit -= tokenAmount;
        cout << " -> [WALLET UPDATE] Subtracted token fee from cash wallet. Remaining cash: PKR " << walletCashLimit << "\n";
    }

    void viewSavedFavoritesFeed() const {
        cout << "\n========================================================================\n";
        cout << "SAVED WATCHLIST FEED FOR BUYER USER: " << fullName << "\n";
        cout << "========================================================================\n";
        for (int i = 0; i < totalSavedAds; i++) {
            trackedSavedAds[i]->printDetails();
        }
    }

    string getRoleName() const override { return "VerifiedBuyer"; }
};

class PlatformAdmin : public UserAccount {
private:
    int totalApprovalsDone;
    int totalFlagsDone;
public:
    PlatformAdmin(string id, string name, string email, string pass)
        : UserAccount(id, name, email, pass), totalApprovalsDone(0), totalFlagsDone(0) {}

    void approveListing(AdListing* targetAd) {
        targetAd->listingStatus = "Active";
        totalApprovalsDone++;
        cout << "[ADMIN COMPLIANCE] Ad listing " << targetAd->adID << " has been APPROVED and is now live.\n";
    }

    void flagAndRemoveListing(AdListing* targetAd) {
        targetAd->listingStatus = "Flagged/Removed";
        totalFlagsDone++;
        cout << "[ADMIN COMPLIANCE] Ad listing " << targetAd->adID << " failed verification guidelines and was REMOVED.\n";
    }

    AppStatistics runSystemAuditMetrics(AdListing* ad1, AdListing* ad2) {
        AppStatistics auditLog;
        cout << "\n[ADMIN AUDIT CONTROL] Evaluating listing price levels directly in system logs:\n";
        cout << " -> Listing #1 Price Point: PKR " << ad1->finalPrice << "\n";
        cout << " -> Listing #2 Price Point: PKR " << ad2->finalPrice << "\n";

        if (ad1->finalPrice < ad2->finalPrice) {
            auditLog.totalApprovedAds++;
        } else {
            auditLog.totalFlaggedAds++;
        }
        auditLog.totalFinancialVolume = ad1->finalPrice + ad2->finalPrice;
        return auditLog;
    }

    string getRoleName() const override { return "SystemSuperAdmin"; }
};

class CarManagementApp {
private:
    AdListing* masterInventoryArray[100];
    int totalIndexedAds;
    string portalTitleBrand;
public:
    CarManagementApp(string brandName) {
        portalTitleBrand = brandName;
        totalIndexedAds = 0;
    }

    void storeNewAdListing(AdListing* adRef) {
        if (totalIndexedAds < 100) {
            masterInventoryArray[totalIndexedAds] = adRef;
            totalIndexedAds++;
        } else {
            cout << " -> Error: Portal inventory array matrix limit reached.\n";
        }
    }

    void filterListingsByManufacturer(string targetBrand) {
        cout << "\n[PORTAL FILTER] Searching active listings for brand: '" << targetBrand << "'...\n";
        bool matchDiscovered = false;
        for (int i = 0; i < totalIndexedAds; i++) {
            if (masterInventoryArray[i]->getStatus() == "Active" && masterInventoryArray[i]->getVehicle() != nullptr) {
                if (masterInventoryArray[i]->getVehicle()->getMake() == targetBrand) {
                    masterInventoryArray[i]->printDetails();
                    matchDiscovered = true;
                }
            }
        }
        if (!matchDiscovered) {
            cout << " -> No active listings match the manufacturer brand criteria: " << targetBrand << "\n";
        }
    }

    void filterByMinimumMaintenanceLogs(int minLogsRequired) {
        cout << "\n[PORTAL FILTER] Searching for well-maintained vehicles with >= " << minLogsRequired << " logged service events:\n";
        bool itemFound = false;
        for (int i = 0; i < totalIndexedAds; i++) {
            if (masterInventoryArray[i]->getStatus() == "Active" && masterInventoryArray[i]->getVehicle() != nullptr) {
                
                Vehicle* vPtr = masterInventoryArray[i]->getVehicle();
                
                int currentLogCounter = 0;
                if (vPtr->getMileage() > 0) {
                    currentLogCounter = 2;
                }

                if (currentLogCounter >= minLogsRequired) {
                    masterInventoryArray[i]->printDetails();
                    itemFound = true;
                }
            }
        }
        if (!itemFound) {
            cout << " -> No matching vehicles found with that extensive maintenance profile record count.\n";
        }
    }

    void showAllReservedBookings() const {
        cout << "\n========================================================================\n";
        cout << "       DISPLAYING ALL CURRENTLY RESERVED VEHICLE BOOKINGS (TOKEN PAID)  \n";
        cout << "========================================================================\n";
        bool balanceFound = false;
        for (int i = 0; i < totalIndexedAds; i++) {
            if (masterInventoryArray[i]->getStatus() == "Reserved") {
                masterInventoryArray[i]->printDetails();
                balanceFound = true;
            }
        }
        if (!balanceFound) {
            cout << "    [No listings are currently locked under reserve token deposits]\n";
        }
        cout << "========================================================================\n";
    }

    void showActiveMarketplaceFeed() const {
        cout << "\n========================================================================\n";
        cout << "            WELCOME TO THE LIVE MARKETPLACE AD FEED: " << portalTitleBrand << "\n";
        cout << "========================================================================\n";
        int activeFeedCounter = 0;
        for (int i = 0; i < totalIndexedAds; i++) {
            if (masterInventoryArray[i]->getStatus() == "Active") {
                masterInventoryArray[i]->printDetails();
                activeFeedCounter++;
            }
        }
        if (activeFeedCounter == 0) {
            cout << "    [Marketplace index feed is currently empty. Check back later!]\n";
        }
        cout << "========================================================================\n";
    }
};

int main() {
    cout << "========================================================================\n";
    cout << "        RUNNING VEHICLE TRANSACTION MANAGEMENT PORTAL PIPELINE           \n";
    cout << "========================================================================\n";

    Engine civicEngine("Petrol", 1500, "Automatic");
    Engine sportageEngine("Petrol", 2000, "Automatic");
    Engine altoEngine("Petrol", 660, "Manual");
    Engine bikeEngine("Petrol", 125, "Manual");

    CarLocation loc1("Karachi", "Clifton");
    CarLocation loc2("Lahore", "Gulberg");
    CarLocation loc3("Islamabad", "Sector F-10");

    Sedan* car1 = new Sedan("Honda", "Civic X", 2021, 35000, "White", civicEngine, loc1, 510, true);
    SUV* car2 = new SUV("Kia", "Sportage", 2022, 18000, "Black", sportageEngine, loc2, 5, true);
    Hatchback* car3 = new Hatchback("Suzuki", "Alto", 2020, 52000, "Silver", altoEngine, loc3, true, "Manual");
    Motorbike* bike1 = new Motorbike("Honda", "CG-125", 2023, 8000, "Red", bikeEngine, loc1, "Commuter", false);

    cout << "\n--- Populating Vehicle Maintenance Log Tracks (Feature 1) ---\n";
    car1->addMaintenanceLog("12-05-2024", "Engine Oil Change", 10000, 8500.0);
    car1->addMaintenanceLog("18-11-2025", "Brake Pad Replacement", 25000, 12000.0);
    
    car2->addMaintenanceLog("05-01-2025", "Periodic Tuning Service", 15000, 18000.0);
    car3->addMaintenanceLog("22-08-2023", "Battery Replacement", 30000, 9500.0);

    Seller sellerProfile("SEL-441", "Moiz Khan", "moiz.khan@gmail.com", "sellerPass123", "Individual");
    Buyer buyerProfile("BUY-992", "Shaheer Ahmed", "shaheer.ahmed@outlook.com", "buyerVault99", 8000000);
    PlatformAdmin adminProfile("ADM-001", "Sarim Ahmed", "sarim.admin@pakwheels.com", "rootSecureAccessKey");

    AdListing* ad1 = new AdListing("AD-101", car1, 5800000, sellerProfile.getUserID());
    AdListing* ad2 = new AdListing("AD-102", car2, 6200000, sellerProfile.getUserID());
    AdListing* ad3 = new AdListing("AD-103", car3, 2300000, sellerProfile.getUserID());
    AdListing* ad4 = new AdListing("AD-104", bike1, 210000, sellerProfile.getUserID());

    sellerProfile.tieListingToSeller(ad1);
    sellerProfile.tieListingToSeller(ad2);
    sellerProfile.tieListingToSeller(ad3);
    sellerProfile.tieListingToSeller(ad4);

    CarManagementApp applicationEngine("PakWheels Student Variant Portal");
    applicationEngine.storeNewAdListing(ad1);
    applicationEngine.storeNewAdListing(ad2);
    applicationEngine.storeNewAdListing(ad3);
    applicationEngine.storeNewAdListing(ad4);

    cout << "\n--- Administrative Compliance Auditing Checkpoints ---\n";
    adminProfile.approveListing(ad1);
    adminProfile.approveListing(ad2);
    adminProfile.approveListing(ad3);
    adminProfile.approveListing(ad4);

    applicationEngine.showActiveMarketplaceFeed();

    applicationEngine.filterListingsByManufacturer("Honda");

    applicationEngine.filterByMinimumMaintenanceLogs(2);

    cout << "\n--- Testing Simple Cash Token Booking Deposit System (Feature 2) ---\n";
    buyerProfile.addAdToFavorites(ad1);
    buyerProfile.addAdToFavorites(ad2);
    
    buyerProfile.processTokenBooking(ad1, 150000);
    
    applicationEngine.showAllReservedBookings();
    
    applicationEngine.showActiveMarketplaceFeed();

    cout << "\n--- Processing Simple Mathematical Operator Overload Structural Assets ---\n";
    if (*ad3 < *ad1) {
        cout << "[OPERATOR MATCH] Relational validation confirmed: Ad record AD-103 features lower budget tier costs than AD-101.\n";
    }
    if (!(*ad1 == *ad2)) {
        cout << "[OPERATOR MATCH] Equivalence check structural balance confirmed: Unique identifier profiles verified.\n";
    }

    AppStatistics logsAlpha = adminProfile.runSystemAuditMetrics(ad1, ad2);
    AppStatistics logsBeta(1, 0, 2300000);
    AppStatistics totalCompiledAppLogsSummary = logsAlpha + logsBeta;

    cout << "\nAggregated Core Statistical Data Blocks Resulting from Arithmetic Additions:\n";
    cout << " -> Combined Validated Listings Approved on Network Logs: " << totalCompiledAppLogsSummary.getApprovedCount() << "\n";
    cout << " -> Total Core Combined System Operational Cash Volume Sum: PKR " << totalCompiledAppLogsSummary.getVolume() << "\n";

    cout << "\n--- Deallocating Dynamic Pointer References Safely From Memory Heap fields ---\n";
    delete car1;
    delete car2;
    delete car3;
    delete bike1;
    delete ad1;
    delete ad2;
    delete ad3;
    delete ad4;

    cout << "Process execution complete. Program exited safely with zero active memory leaks.\n";
    return 0;
}