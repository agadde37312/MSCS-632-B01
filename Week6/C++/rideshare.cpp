#include <iostream>
#include <vector>
#include <memory>
#include <sstream>
#include <iomanip>

// ---------- Base Ride Class ----------
class Ride {
protected:
    int rideID;
    std::string pickupLocation;
    std::string dropoffLocation;
    double distance; // in miles

public:
    Ride(int id, const std::string &pickup, const std::string &dropoff, double dist)
        : rideID(id), pickupLocation(pickup), dropoffLocation(dropoff), distance(dist) {}

    // Virtual function to calculate fare.
    virtual double fare() const {
        // Default base rate: 2 units per mile
        return distance * 2;
    }

    // Virtual method for ride details.
    virtual std::string rideDetails() const {
        std::ostringstream oss;
        oss << "Ride ID: " << rideID
            << " | Pickup: " << pickupLocation
            << " | Dropoff: " << dropoffLocation
            << " | Distance: " << distance << " miles"
            << " | Fare: $" << std::fixed << std::setprecision(2) << fare();
        return oss.str();
    }

    // Virtual destructor for proper cleanup.
    virtual ~Ride() = default;
};

// ---------- Derived StandardRide Class ----------
class StandardRide : public Ride {
public:
    StandardRide(int id, const std::string &pickup, const std::string &dropoff, double dist)
        : Ride(id, pickup, dropoff, dist) {}

    // Override fare for StandardRide.
    double fare() const override {
        return distance * 2; // standard rate
    }
};

// ---------- Derived PremiumRide Class ----------
class PremiumRide : public Ride {
public:
    PremiumRide(int id, const std::string &pickup, const std::string &dropoff, double dist)
        : Ride(id, pickup, dropoff, dist) {}

    // Override fare for PremiumRide.
    double fare() const override {
        return (distance * 3.5) + 5; // premium rate with extra fee
    }
};

// ---------- Driver Class ----------
class Driver {
private:
    int driverID;
    std::string name;
    double rating;
    std::vector<std::shared_ptr<Ride>> assignedRides; // encapsulated list of rides

public:
    Driver(int id, const std::string &driverName, double rate)
        : driverID(id), name(driverName), rating(rate) {}

    // Add a ride to the driver’s list.
    void addRide(const std::shared_ptr<Ride> &ride) {
        assignedRides.push_back(ride);
    }

    // Display driver information.
    std::string getDriverInfo() const {
        std::ostringstream oss;
        oss << "Driver ID: " << driverID
            << " | Name: " << name
            << " | Rating: " << rating
            << " | Assigned Rides: " << assignedRides.size();
        return oss.str();
    }
};

// ---------- Rider Class ----------
class Rider {
private:
    int riderID;
    std::string name;
    std::vector<std::shared_ptr<Ride>> requestedRides; // encapsulated list of rides

public:
    Rider(int id, const std::string &riderName)
        : riderID(id), name(riderName) {}

    // Request a ride.
    void requestRide(const std::shared_ptr<Ride> &ride) {
        requestedRides.push_back(ride);
    }

    // View ride history.
    void viewRides() const {
        std::cout << "Ride history for Rider ID: " << riderID << " (" << name << "):\n";
        for (const auto &ride : requestedRides) {
            std::cout << ride->rideDetails() << std::endl;
        }
    }
};

// ---------- Main Function to Demonstrate Functionality ----------
int main() {
    // Create rides using polymorphism.
    std::vector<std::shared_ptr<Ride>> rides;
    rides.push_back(std::make_shared<StandardRide>(101, "Mt Juliet", "Nashville", 15));
    rides.push_back(std::make_shared<PremiumRide>(102, "Wall Street", "Broadway", 7));

    std::cout << "Demonstrating Polymorphism with Ride Details:\n";
    for (const auto &ride : rides) {
        std::cout << ride->rideDetails() << "\n";
    }

    // Create a driver and assign rides.
    Driver driver1(1, "Arun", 5.9);
    driver1.addRide(rides[0]);
    std::cout << "\nDriver Information:\n" << driver1.getDriverInfo() << "\n";


    Driver driver2(2, "Gadde", 5.6);
    driver2.addRide(rides[1]);
    std::cout << "\nDriver Information:\n" << driver2.getDriverInfo() << "\n";

    // Create a rider and request rides.
    Rider rider1(1, "Sravya");
    rider1.requestRide(rides[0]);
    rider1.requestRide(rides[1]);
    std::cout << "\nRider Ride History:\n";
    rider1.viewRides();

    return 0;
}



class Ride {
    // Base class with virtual methods
};

class StandardRide : public Ride {
    // Inherits from Ride
    double fare() const override { return distance * 2; }
};

class PremiumRide : public Ride {
    // Inherits from Ride
    double fare() const override { return (distance * 3.5) + 5; }
};
