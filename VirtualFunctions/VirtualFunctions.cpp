// VirtualFunctions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

using namespace std;



class Vehicle {
public:
    virtual ~Vehicle() = default;
    virtual ostream& print(ostream& out) const = 0;
    friend ostream& operator<<(ostream& out, const Vehicle& v) {
        return v.print(out);
    }
};



class Wheel {
private:
    float diameter;
public:
    Wheel(const float _diameter) : diameter(_diameter) {}
    friend ostream& operator<<(ostream& out, const Wheel& w) {
        out << w.diameter;
        return out;
    }
};


class Engine {
public:
    float power;
public:
    Engine(const float _power) : power(_power) {}
    friend ostream& operator<<(ostream& out, const Engine& e) {
        out << e.power;
        return out;
    }
};


class WaterVehicle : public Vehicle {
private:
    float draft;
public:
    WaterVehicle(float _draft) : draft(_draft) {}
    ostream& print(ostream& out) const override {
        return out << "WaterVehicle Draft: " << draft;
    }
};


class RoadVehicle : public Vehicle {
protected:
    float ride_height;
public:
    RoadVehicle(float _ride_height) : ride_height(_ride_height) {}
};


class Bicycle : public RoadVehicle {
private:
    Wheel wheel1, wheel2;
public:
    Bicycle(Wheel _wheel1, Wheel _wheel2, float _ride_height)
        : RoadVehicle(_ride_height), wheel1(_wheel1), wheel2(_wheel2) {}
    ostream& print(ostream& out) const override {
        return out << "Bicycle Wheels: " << wheel1 << " " << wheel2 << " Ride height: " << ride_height;
    }
};


class Car : public RoadVehicle {
private:
    Engine engine;
    Wheel wheel1, wheel2, wheel3, wheel4;
public:
    Car(Engine _engine, Wheel _wheel1, Wheel _wheel2, Wheel _wheel3, Wheel _wheel4, float _ride_height)
        : RoadVehicle(_ride_height), engine(_engine), wheel1(_wheel1), wheel2(_wheel2), wheel3(_wheel3), wheel4(_wheel4) {}
    ostream& print(ostream& out) const override {
        return out << "Car Engine: " << engine << " Wheels: " << wheel1 << " " << wheel2 << " " << wheel3 << " " << wheel4 << " Ride height: " << ride_height;
    }
    float GetEnginePower() const { return engine.power; }
};


float getHighestPower(const vector<Vehicle*>& v) {
    float max_power = 0;
    for (const auto& vehicle : v) {
        if (dynamic_cast<const Car*>(vehicle)) {
            const auto car = dynamic_cast<const Car*>(vehicle);
            max_power = max(max_power, car->GetEnginePower());
        }
    }
    return max_power;
}

int main() {
    vector<Vehicle*> v;

    v.push_back(new Car(Engine(150), Wheel(17), Wheel(17), Wheel(18), Wheel(18), 250));
    v.push_back(new WaterVehicle(5000));
    v.push_back(new Car(Engine(200), Wheel(19), Wheel(19), Wheel(19), Wheel(19), 130));
    
    for (const auto& vehicle : v) {
        cout << *vehicle << '\n';
    }

    cout << "The highest power is " << getHighestPower(v) << '\n';
    
    for (auto& vehicle : v) {
        delete vehicle;
    }
    v.clear();
     
    return 0;
}
