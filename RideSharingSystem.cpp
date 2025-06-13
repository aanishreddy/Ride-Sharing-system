#include <iostream>
#include <vector>
#include <memory>

using namespace std;

// Base class: Ride
class Ride {
protected:
    int rideID;
    string pickupLocation;
    string dropoffLocation;
    double distance;

public:
    Ride(int id, string pickup, string dropoff, double dist)
        : rideID(id), pickupLocation(pickup), dropoffLocation(dropoff), distance(dist) {}

    virtual double fare() const = 0;
    virtual void rideDetails() const {
        cout << "Ride ID: " << rideID
             << ", From: " << pickupLocation
             << ", To: " << dropoffLocation
             << ", Distance: " << distance << " miles" << endl;
    }

    virtual ~Ride() = default;
};

// Subclass: StandardRide
class StandardRide : public Ride {
public:
    StandardRide(int id, string pickup, string dropoff, double dist)
        : Ride(id, pickup, dropoff, dist) {}

    double fare() const override {
        return distance * 1.5;  // $1.5 per mile
    }

    void rideDetails() const override {
        Ride::rideDetails();
        cout << "Type: Standard, Fare: $" << fare() << endl;
    }
};

// Subclass: PremiumRide
class PremiumRide : public Ride {
public:
    PremiumRide(int id, string pickup, string dropoff, double dist)
        : Ride(id, pickup, dropoff, dist) {}

    double fare() const override {
        return distance * 3.0;  // $3.0 per mile
    }

    void rideDetails() const override {
        Ride::rideDetails();
        cout << "Type: Premium, Fare: $" << fare() << endl;
    }
};

// Driver class
class Driver {
private:
    int driverID;
    string name;
    double rating;
    vector<shared_ptr<Ride>> assignedRides;

public:
    Driver(int id, string name, double rating) : driverID(id), name(name), rating(rating) {}

    void addRide(shared_ptr<Ride> ride) {
        assignedRides.push_back(ride);
    }

    void getDriverInfo() const {
        cout << "Driver ID: " << driverID << ", Name: " << name << ", Rating: " << rating << endl;
        cout << "Completed Rides:\n";
        for (const auto& ride : assignedRides) {
            ride->rideDetails();
        }
    }
};

// Rider class
class Rider {
private:
    int riderID;
    string name;
    vector<shared_ptr<Ride>> requestedRides;

public:
    Rider(int id, string name) : riderID(id), name(name) {}

    void requestRide(shared_ptr<Ride> ride) {
        requestedRides.push_back(ride);
    }

    void viewRides() const {
        cout << "Rider ID: " << riderID << ", Name: " << name << endl;
        cout << "Requested Rides:\n";
        for (const auto& ride : requestedRides) {
            ride->rideDetails();
        }
    }
};

// Main function to demonstrate polymorphism
int main() {
    shared_ptr<Ride> r1 = make_shared<StandardRide>(101, "A", "B", 10);
    shared_ptr<Ride> r2 = make_shared<PremiumRide>(102, "C", "D", 8);

    Driver d1(1, "Alice", 4.9);
    d1.addRide(r1);
    d1.addRide(r2);

    Rider rider1(201, "Bob");
    rider1.requestRide(r1);
    rider1.requestRide(r2);

    vector<shared_ptr<Ride>> rideList = {r1, r2};
    cout << "---- Polymorphic Fare Display ----\n";
    for (const auto& ride : rideList) {
        ride->rideDetails();
    }

    cout << "\n---- Driver Info ----\n";
    d1.getDriverInfo();

    cout << "\n---- Rider Info ----\n";
    rider1.viewRides();

    return 0;
}
