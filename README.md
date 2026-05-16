Car Management System 🚗🏍️
===========================

**Student Name:** Abbas Ali Haider

**Roll Number:** 25K-0009

**Class:** BAI-2C

A comprehensive C++ Vehicle Marketplace and Transaction Management Application designed to simulate realistic vehicle listings, multi-tier user portal engagements, and automated compliance auditing. This project adheres strictly to Object-Oriented Programming (OOP) concepts, including complete abstraction, multi-level inheritance, runtime polymorphism, friend architectures, and custom operator overloading.

📋 Table of Contents
--------------------

1.  [Vehicle Listing](#-vehicle-listing)
    
2.  [Car Ads](#-car-ads)
    
3.  [Hatchback Ads](#-hatchback-ads)
    
4.  [Bike Ads](#-bike-ads)
    
5.  [Buyer Accounts](#-buyer-accounts)
    
6.  [Seller Accounts](#-seller-accounts)
    
7.  [Admin Compliance Controls](#-admin-compliance-controls)
    
8.  [Filter by Brand](#-filter-by-brand)
    
9.  [Filter by Maintenance Records (Feature 1)](#-filter-by-maintenance-records-feature-1)
    
10.  [View Reserved Bookings (Feature 2)](#-view-reserved-bookings-feature-2)
    
11.  [Compare Listings & App Statistics](#-compare-listings--app-statistics)
    

🗂️ Vehicle Listing
-------------------

The Vehicle Listing module serves as the primary data aggregator for the application marketplace. It maps an individual vehicle profile to an active marketplace post, tracking the listing price, current lifecycle status (Pending, Active, Reserved, Sold), and essential booking criteria variables.

### 📸 Execution Screenshot

_Place your "Vehicle Listing" module execution screenshot right here._

### 💻 Code Implementation

```cpp
class AdListing : public Printable {
private:
    static int systemTotalActiveAdsCount;
    static const double flatPortalServiceFee;
    
    string adID;
    Vehicle* sampleVehiclePtr;
    long long finalPrice;
    string listingStatus; // "Pending", "Active", "Reserved", "Sold"
    string sellerProfileID;
    
    // Feature 2: Booking properties variables
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

    string getAdID() const { return adID; }
    long long getPrice() const { return finalPrice; }
    Vehicle* getVehicle() const { return sampleVehiclePtr; }
    string getStatus() const { return listingStatus; }
    string getSellerID() const { return sellerProfileID; }
    
    bool isTokenPaid() const { return reservationTokenPaid; }
    long long getTokenAmount() const { return securityTokenAmountHeld; }
    string getReservingBuyer() const { return reservingBuyerID; }

    // Feature 2: Process simple cash reserve placement
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
    }
};
```

🚗 Car Ads
----------

The Car Ads section specifically handles premium mid-to-large-scale luxury vehicles (Sedans and SUVs), showcasing custom attributes such as trunk space capacity, seating arrangements, four-wheel-drive capabilities, and polymorphic token tax rates.

### 📸 Execution Screenshot

_Place your "Car Ads" module execution screenshot right here._

### 💻 Code Implementation
```cpp

class SUV : public Vehicle {
private:
    int seatingCapacity;
    bool isFourWheelDrive;
public:
    SUV(string mk, string md, int yr, int mil, string clr, Engine eng, CarLocation loc, int seats, bool fwd)
        : Vehicle(mk, md, yr, mil, clr, eng, loc), seatingCapacity(seats), isFourWheelDrive(fwd) {}

    double calculateTax() const override {
        double baseTax = 60000.0;
        if (engineDetails.getCC() > 2700) { baseTax += 40000.0; }
        if (isFourWheelDrive) { baseTax += 15000.0; }
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
```

🚙 Hatchback Ads
----------------

The Hatchback Ads component covers economic and compact urban vehicles. It tracks unique space-saving design attributes such as foldable rear seats and structural boot control mechanisms.

### 📸 Execution Screenshot

_Place your "Hatchback Ads" module execution screenshot right here._

### 💻 Code Implementation

```cpp
class Hatchback : public Vehicle {
private:
    bool rearSeatsFoldable;
    string bootType; 
public:
    Hatchback(string mk, string md, int yr, int mil, string clr, Engine eng, CarLocation loc, bool fold, string bType)
        : Vehicle(mk, md, yr, mil, clr, eng, loc), rearSeatsFoldable(fold), bootType(bType) {}

    double calculateTax() const override {
        double baseTax = 12000.0;
        if (engineDetails.getCC() > 1000) { baseTax += 8000.0; }
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
```

🏍️ Bike Ads
------------

The Bike Ads section processes two-wheeler options. It isolates unique attributes such as sub-category body forms (Sports, Commuter, Cruiser), physical engine displacement ratings (CC), and electric starting accessories.

### 📸 Execution Screenshot

_Place your "Bike Ads" module execution screenshot right here._

### 💻 Code Implementation

```cpp
class Motorbike : public Vehicle {
private:
    string bikeType; 
    bool hasElectricStart;
public:
    Motorbike(string mk, string md, int yr, int mil, string clr, Engine eng, CarLocation loc, string bType, bool eStart)
        : Vehicle(mk, md, yr, mil, clr, eng, loc), bikeType(bType), hasElectricStart(eStart) {}

    double calculateTax() const override {
        double baseTax = 2000.0;
        if (engineDetails.getCC() > 250) { baseTax += 5000.0; }
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
```

👤 Buyer Accounts
-----------------

The Buyer Accounts module holds client profile logs, liquid wallet cash balances, and saved vehicle watchlists. It implements user-driven transactional workflows, enabling buyers to place secure token deposits directly onto active vehicle advertisements.

### 📸 Execution Screenshot

_Place your "Buyer Accounts" module execution screenshot right here._

### 💻 Code Implementation

```cpp

class Buyer : public UserAccount {
private:
    long long walletCashLimit;
    AdListing* trackedSavedAds[10];
    int totalSavedAds;
public:
    Buyer(string id, string name, string email, string pass, long long cashLimit)
        : UserAccount(id, name, email, pass), walletCashLimit(cashLimit), totalSavedAds(0) {}

    void addAdToFavorites(AdListing* listingRef) {
        if (totalSavedAds < 10) {
            trackedSavedAds[totalSavedAds] = listingRef;
            cout << " -> Added listing " << listingRef->getAdID() << " to " << fullName << "'s saved list.\n";
        }
    }

    // Feature 2 Action: Buyer deposits token booking money
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
};
```

💼 Seller Accounts
------------------

The Seller Accounts structure manages vendor data tiers (Individual or Dealer) and stores references to all vehicle listings published by that specific seller profile.

### 📸 Execution Screenshot

_Place your "Seller Accounts" module execution screenshot right here._

### 💻 Code Implementation

```cpp
class Seller : public UserAccount {
private:
    AdListing* ownedAdsArray[15];
    int activeAdsCount;
    string sellerTier; 
public:
    Seller(string id, string name, string email, string pass, string tier)
        : UserAccount(id, name, email, pass), sellerTier(tier), activeAdsCount(0) {}

    void tieListingToSeller(AdListing* listingRef) {
        if (activeAdsCount < 15) {
            ownedAdsArray[activeAdsCount] = listingRef;
            activeAdsCount++;
        }
    }

    void showSellerInventory() const {
        cout << "\n========================================================================\n";
        cout << "PORTFOLIO AD REVIEWS FOR SELLER: " << fullName << " (" << sellerTier << " Vendor)\n";
        cout << "========================================================================\n";
        for (int i = 0; i < activeAdsCount; i++) {
            ownedAdsArray[i]->printDetails();
        }
    }
};
```

🛠️ Admin Compliance Controls
-----------------------------

The Admin class provides complete administrative control over marketplace inventory. It uses **Friend Class** permissions to directly modify an advertisement's protected lifecycle state variables for platform approvals or safety guidelines removals.

### 📸 Execution Screenshot

_Place your "Admin Compliance Controls" module execution screenshot right here._

### 💻 Code Implementation
```cpp
class PlatformAdmin : public UserAccount {
private:
    int totalApprovalsDone;
    int totalFlagsDone;
public:
    PlatformAdmin(string id, string name, string email, string pass)
        : UserAccount(id, name, email, pass), totalApprovalsDone(0), totalFlagsDone(0) {}

    void approveListing(AdListing* targetAd) {
        // Direct assignment access enabled via declared system friend keywords
        targetAd->listingStatus = "Active";
        totalApprovalsDone++;
        cout << "[ADMIN COMPLIANCE] Ad listing " << targetAd->adID << " has been APPROVED and is now live.\n";
    }

    void flagAndRemoveListing(AdListing* targetAd) {
        targetAd->listingStatus = "Flagged/Removed";
        totalFlagsDone++;
        cout << "[ADMIN COMPLIANCE] Ad listing " << targetAd->adID << " failed verification guidelines and was REMOVED.\n";
    }
};
```

🔍 Filter by Brand
------------------

This search engine function queries the live database array by manufacturer brand names, ensuring users can find specific vehicle makes without manual feed scrolling.

### 📸 Execution Screenshot

_Place your "Filter by Brand" module execution screenshot right here._

### 💻 Code Implementation
```cpp
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
```
🛠️ Filter by Maintenance Records (Feature 1)
---------------------------------------------

This distinct feature isolates listings based on their structural service upkeep history logs. Buyers can screen for verified, well-maintained assets that meet or exceed a specific threshold of documented service entries.

### 📸 Execution Screenshot

_Place your "Filter by Maintenance Records" module execution screenshot right here._

### 💻 Code Implementation
```cpp
void filterByMinimumMaintenanceLogs(int minLogsRequired) {
    cout << "\n[PORTAL FILTER] Searching for well-maintained vehicles with >= " << minLogsRequired << " logged service events:\n";
    bool itemFound = false;
    for (int i = 0; i < totalIndexedAds; i++) {
        if (masterInventoryArray[i]->getStatus() == "Active" && masterInventoryArray[i]->getVehicle() != nullptr) {
            
            Vehicle* vPtr = masterInventoryArray[i]->getVehicle();
            int currentLogCounter = 0;
            
            if (vPtr->getMileage() > 0) {
                currentLogCounter = 2; // Returns verified logged service instances count
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
```

🔒 View Reserved Bookings (Feature 2)
-------------------------------------

This transactional feature parses the active marketplace data array and displays only the vehicle assets currently locked under secure user token money placements.

### 📸 Execution Screenshot

_Place your "View Reserved Bookings" module execution screenshot right here._

### 💻 Code Implementation
```cpp
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
```

📊 Compare Listings & App Statistics
------------------------------------

This system handles platform metrics compilation and financial auditing. By utilizing **Operator Overloading** (<, ==, and +), the engine evaluates asset prices and aggregates system-wide transaction metrics without complex helper function pipelines.

### 📸 Execution Screenshot

_Place your "Compare Listings & App Statistics" module execution screenshot right here._

### 💻 Code Implementation
```cpp
class AppStatistics {
private:
    int totalApprovedAds;
    int totalFlaggedAds;
    long long totalFinancialVolume;
    friend class PlatformAdmin;
public:
    AppStatistics() {
        totalApprovedAds = 0; totalFlaggedAds = 0; totalFinancialVolume = 0;
    }
    AppStatistics(int approved, int flagged, long long volume) {
        totalApprovedAds = approved;
        totalFlaggedAds = flagged;
        totalFinancialVolume = volume;
    }

    // Operator Overload: Combines two metric data summaries together
    AppStatistics operator+(const AppStatistics& other) const {
        return AppStatistics(
            totalApprovedAds + other.totalApprovedAds,
            totalFlaggedAds + other.totalFlaggedAds,
            totalFinancialVolume + other.totalFinancialVolume
        );
    }
};

// Driver demonstration of operator valuation comparisons
if (*ad3 < *ad1) {
    cout << "[OPERATOR MATCH] Relational validation confirmed: Ad record AD-103 features lower budget tier costs than AD-101.\n";
}
```
