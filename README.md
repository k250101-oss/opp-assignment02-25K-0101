# Car Management System 🚗🏍️

**Student Name:** Abbas Ali Haider  
**Roll Number:** 25K-0009  
**Class:** BAI-2C  

A comprehensive C++ Vehicle Marketplace and Transaction Management Application designed to simulate realistic vehicle listings, multi-tier user portal engagements, and automated compliance auditing. This project adheres strictly to Object-Oriented Programming (OOP) concepts, including complete abstraction, multi-level inheritance, runtime polymorphism, friend architectures, and custom operator overloading.

---

## 📋 Table of Contents
1. [Vehicle Listing](#-vehicle-listing)
2. [Car Ads](#-car-ads)
3. [Hatchback Ads](#-hatchback-ads)
4. [Bike Ads](#-bike-ads)
5. [Buyer Accounts](#-buyer-accounts)
6. [Seller Accounts](#-seller-accounts)
7. [Admin Compliance Controls](#-admin-compliance-controls)
8. [Filter by Brand](#-filter-by-brand)
9. [Filter by Maintenance Records (Feature 1)](#-filter-by-maintenance-records-feature-1)
10. [View Reserved Bookings (Feature 2)](#-view-reserved-bookings-feature-2)
11. [Compare Listings & App Statistics](#-compare-listings--app-statistics)

---

## 🗂️ Vehicle Listing

The Vehicle Listing module serves as the primary data aggregator for the application marketplace. It maps an individual vehicle profile to an active marketplace post, tracking the listing price, current lifecycle status (`Pending`, `Active`, `Reserved`, `Sold`), and essential booking criteria variables.

### 📸 Execution Screenshot
*Place your "Vehicle Listing" module execution screenshot right here.*

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
