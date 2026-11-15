#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
using namespace std;


class Mission {
public:
    string name;
    string description;
    int scienceTarget;
    int requiredDeltaV;
    int budget;
    int dataMultiplier;

    Mission() {
        name = "";
        description = "";
        scienceTarget = 0;
        requiredDeltaV = 0;
        budget = 0;
        dataMultiplier = 1;
    }
};

class Component {
public:
    string name;
    int mass;
    int power;
    int cost;
    int science;
    int data;
    int powerGeneration;
    int communicationCapacity;
    int deltaV;
    int batteryCapacity;

    Component() {
        name = "";
        mass = power = cost = science = data = 0;
        powerGeneration = communicationCapacity = deltaV = batteryCapacity = 0;
    }

    Component(string n, int m, int p, int c, int s, int d,
              int pg, int cc, int dv, int bc) {
        name = n;
        mass = m;
        power = p;
        cost = c;
        science = s;
        data = d;
        powerGeneration = pg;
        communicationCapacity = cc;
        deltaV = dv;
        batteryCapacity = bc;
    }
};

class Rocket {
public:
    string name;
    int payloadCapacity;
    int cost;
    int maximumDeltaV;

    Rocket() {
        name = "";
        payloadCapacity = cost = maximumDeltaV = 0;
    }

    Rocket(string n, int p, int c, int d) {
        name = n;
        payloadCapacity = p;
        cost = c;
        maximumDeltaV = d;
    }
};

class SpaceMissionGame {
private:
    Mission missions[3];
    Component instruments[4];
    Component powerSystems[3];
    Component batteries[3];
    Component antennas[2];
    Component propulsionSystems[2];
    Rocket rockets[3];

    int selectedMission;
    int selectedInstrument[4];
    int selectedPower;
    int selectedBattery;
    int selectedAntenna;
    int selectedPropulsion;
    int selectedRocket;

    bool missionChosen;
    bool powerChosen;
    bool batteryChosen;
    bool antennaChosen;
    bool propulsionChosen;
    bool rocketChosen;

    string playerName;

    int readNumber(string prompt, int minimum, int maximum) {
        int value;

        while (true) {
            cout << prompt;
            cin >> value;

            if (!cin.fail() && value >= minimum && value <= maximum) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return value;
            }

            cout << "Invalid input. Please enter a number from "
                 << minimum << " to " << maximum << ".\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    void initializeData() {
        missions[0].name = "Earth Observation";
        missions[0].description =
            "Study Earth's land, oceans, weather and changing climate.";
        missions[0].scienceTarget = 45;
        missions[0].requiredDeltaV = 1;
        missions[0].budget = 180;
        missions[0].dataMultiplier = 1;

        missions[1].name = "Moon Exploration";
        missions[1].description =
            "Study the lunar surface and collect scientific measurements.";
        missions[1].scienceTarget = 65;
        missions[1].requiredDeltaV = 3;
        missions[1].budget = 260;
        missions[1].dataMultiplier = 1;

        missions[2].name = "Mars Exploration";
        missions[2].description =
            "Explore Mars and investigate its surface and environment.";
        missions[2].scienceTarget = 80;
        missions[2].requiredDeltaV = 5;
        missions[2].budget = 360;
        missions[2].dataMultiplier = 1;

        instruments[0] = Component("Basic Camera", 8, 25, 12, 12, 8, 0, 0, 0, 0);
        instruments[1] = Component("Multispectral Imager", 18, 55, 28, 25, 20, 0, 0, 0, 0);
        instruments[2] = Component("Radar Instrument", 35, 95, 55, 35, 35, 0, 0, 0, 0);
        instruments[3] = Component("Atmospheric Spectrometer", 22, 70, 40, 30, 25, 0, 0, 0, 0);

        powerSystems[0] = Component("Compact Solar Panels", 15, 0, 15, 0, 0, 90, 0, 0, 0);
        powerSystems[1] = Component("Standard Solar Panels", 28, 0, 30, 0, 0, 180, 0, 0, 0);
        powerSystems[2] = Component("High-Power Solar Array", 45, 0, 50, 0, 0, 320, 0, 0, 0);

        batteries[0] = Component("Small Battery", 6, 0, 8, 0, 0, 0, 0, 0, 100);
        batteries[1] = Component("Medium Battery", 12, 0, 16, 0, 0, 0, 0, 0, 250);
        batteries[2] = Component("Large Battery", 22, 0, 28, 0, 0, 0, 0, 0, 500);

        antennas[0] = Component("Basic Antenna", 5, 10, 8, 0, 0, 0, 15, 0, 0);
        antennas[1] = Component("High-Gain Antenna", 12, 20, 25, 0, 0, 0, 60, 0, 0);

        propulsionSystems[0] = Component("Standard Propulsion System", 20, 15, 20, 0, 0, 0, 0, 3, 0);
        propulsionSystems[1] = Component("Advanced Propulsion System", 38, 25, 45, 0, 0, 0, 0, 6, 0);

        rockets[0] = Rocket("Small Launch Vehicle", 150, 35, 2);
        rockets[1] = Rocket("Medium Launch Vehicle", 350, 65, 4);
        rockets[2] = Rocket("Heavy Launch Vehicle", 700, 110, 7);
    }

    void resetDesign() {
        selectedMission = -1;
        for (int i = 0; i < 4; i++) {
            selectedInstrument[i] = 0;
        }

        selectedPower = selectedBattery = selectedAntenna = -1;
        selectedPropulsion = selectedRocket = -1;

        missionChosen = powerChosen = batteryChosen = false;
        antennaChosen = propulsionChosen = rocketChosen = false;
    }

    void showHeader() {
        cout << "\n====================================================\n";
        cout << "              SPACE MISSION DESIGN GAME\n";
        cout << "====================================================\n";
    }

    void showMissions() {
        cout << "\nCHOOSE YOUR MISSION OBJECTIVE\n";
        for (int i = 0; i < 3; i++) {
            cout << i + 1 << ". " << missions[i].name
                 << " | Budget: $" << missions[i].budget << " million\n";
            cout << "   " << missions[i].description << "\n";
        }

        int choice = readNumber("Enter your choice (1-3): ", 1, 3);
        selectedMission = choice - 1;
        missionChosen = true;

        cout << "\nMission selected: " << missions[selectedMission].name << "\n";
        cout << "Your available budget is $"
             << missions[selectedMission].budget << " million.\n";
    }

    void showComponentList(Component list[], int count, string heading) {
        cout << "\n" << heading << "\n";
        cout << left << setw(4) << "No."
             << setw(32) << "Component"
             << setw(10) << "Mass"
             << setw(10) << "Power"
             << setw(12) << "Cost" << "\n";
        cout << "-----------------------------------------------------------------------\n";

        for (int i = 0; i < count; i++) {
            cout << left << setw(4) << i + 1
                 << setw(32) << list[i].name
                 << setw(10) << list[i].mass
                 << setw(10) << list[i].power
                 << "$" << list[i].cost << "M\n";
        }
    }

    void designSpacecraft() {
        if (!missionChosen) {
            cout << "\nPlease select a mission first.\n";
            return;
        }

        cout << "\n========== SPACECRAFT DESIGN ==========\n";
        cout << "Choose the scientific instruments for your mission.\n";
        cout << "You may select multiple instruments.\n";

        showComponentList(instruments, 4, "SCIENTIFIC INSTRUMENTS");

        for (int i = 0; i < 4; i++) {
            cout << "Add " << instruments[i].name << "? (1 = Yes, 0 = No): ";
            selectedInstrument[i] = readNumber("", 0, 1);
        }

        showComponentList(powerSystems, 3, "POWER SYSTEMS");
        int choice = readNumber("Choose a power system (1-3): ", 1, 3);
        selectedPower = choice - 1;
        powerChosen = true;

        showComponentList(batteries, 3, "BATTERIES");
        choice = readNumber("Choose a battery (1-3): ", 1, 3);
        selectedBattery = choice - 1;
        batteryChosen = true;

        showComponentList(antennas, 2, "COMMUNICATION SYSTEMS");
        choice = readNumber("Choose an antenna (1-2): ", 1, 2);
        selectedAntenna = choice - 1;
        antennaChosen = true;

        showComponentList(propulsionSystems, 2, "PROPULSION SYSTEMS");
        choice = readNumber("Choose a propulsion system (1-2): ", 1, 2);
        selectedPropulsion = choice - 1;
        propulsionChosen = true;

        cout << "\nSpacecraft design saved.\n";
    }

    void chooseRocket() {
        if (!missionChosen) {
            cout << "\nPlease select a mission first.\n";
            return;
        }

        cout << "\n========== LAUNCH VEHICLE SELECTION ==========\n";
        cout << left << setw(4) << "No."
             << setw(30) << "Launch Vehicle"
             << setw(18) << "Payload Capacity"
             << "Cost\n";
        cout << "---------------------------------------------------------------\n";

        for (int i = 0; i < 3; i++) {
            cout << left << setw(4) << i + 1
                 << setw(30) << rockets[i].name
                 << setw(18) << rockets[i].payloadCapacity
                 << "$" << rockets[i].cost << "M\n";
        }

        int choice = readNumber("Choose a launch vehicle (1-3): ", 1, 3);
        selectedRocket = choice - 1;
        rocketChosen = true;

        cout << "\nSelected: " << rockets[selectedRocket].name << "\n";
    }

    void calculateResources(int &mass, int &powerDemand, int &powerSupply,
                            int &cost, int &science, int &data,
                            int &communication, int &deltaV, int &battery) {
        // Basic spacecraft bus: structure, computer and essential systems.
        mass = 45;
        powerDemand = 45;
        powerSupply = 0;
        cost = 25;
        science = 0;
        data = 0;
        communication = 0;
        deltaV = 0;
        battery = 0;

        for (int i = 0; i < 4; i++) {
            if (selectedInstrument[i] == 1) {
                mass += instruments[i].mass;
                powerDemand += instruments[i].power;
                cost += instruments[i].cost;
                science += instruments[i].science;
                data += instruments[i].data;
            }
        }

        if (powerChosen) {
            mass += powerSystems[selectedPower].mass;
            cost += powerSystems[selectedPower].cost;
            powerSupply += powerSystems[selectedPower].powerGeneration;
        }

        if (batteryChosen) {
            mass += batteries[selectedBattery].mass;
            cost += batteries[selectedBattery].cost;
            battery = batteries[selectedBattery].batteryCapacity;
        }

        if (antennaChosen) {
            mass += antennas[selectedAntenna].mass;
            powerDemand += antennas[selectedAntenna].power;
            cost += antennas[selectedAntenna].cost;
            communication = antennas[selectedAntenna].communicationCapacity;
        }

        if (propulsionChosen) {
            mass += propulsionSystems[selectedPropulsion].mass;
            powerDemand += propulsionSystems[selectedPropulsion].power;
            cost += propulsionSystems[selectedPropulsion].cost;
            deltaV = propulsionSystems[selectedPropulsion].deltaV;
        }
    }

    void viewDashboard() {
        if (!missionChosen) {
            cout << "\nPlease select a mission first.\n";
            return;
        }

        int mass, demand, supply, cost, science, data, communication, deltaV, battery;
        calculateResources(mass, demand, supply, cost, science, data,
                           communication, deltaV, battery);

        cout << "\n================ MISSION DASHBOARD ================\n";
        cout << "Mission: " << missions[selectedMission].name << "\n";
        cout << "Available budget:       $" << missions[selectedMission].budget << "M\n";
        cout << "Spacecraft component cost: $" << cost << "M\n";

        if (rocketChosen) {
            cout << "Launch vehicle cost:    $" << rockets[selectedRocket].cost << "M\n";
            cout << "Total estimated cost:   $" << cost + rockets[selectedRocket].cost << "M\n";
        } else {
            cout << "Launch vehicle:         Not selected\n";
        }

        cout << "\nRESOURCE SUMMARY\n";
        cout << "Spacecraft mass:        " << mass << " kg\n";
        cout << "Power demand:           " << demand << " W\n";
        cout << "Power generation:       " << supply << " W\n";
        cout << "Battery capacity:       " << battery << " Wh\n";
        cout << "Communication capacity: " << communication << " data units\n";
        cout << "Generated data:         " << data << " data units\n";
        cout << "Propulsion capability:  " << deltaV << " km/s (simplified)\n";
        cout << "Scientific value:       " << science << " points\n";

        if (powerChosen && supply >= demand) {
            cout << "Power status:            SUFFICIENT\n";
        } else {
            cout << "Power status:            INSUFFICIENT or not selected\n";
        }

        if (antennaChosen && communication >= data) {
            cout << "Communication status:    SUFFICIENT\n";
        } else {
            cout << "Communication status:    INSUFFICIENT or not selected\n";
        }

        cout << "====================================================\n";
    }

    void runSimulation() {
        if (!missionChosen || !powerChosen || !batteryChosen ||
            !antennaChosen || !propulsionChosen || !rocketChosen) {
            cout << "\nYour design is incomplete.\n";
            cout << "Select a mission, design your spacecraft and choose a rocket first.\n";
            return;
        }

        int mass, demand, supply, cost, science, data, communication, deltaV, battery;
        calculateResources(mass, demand, supply, cost, science, data,
                           communication, deltaV, battery);

        int totalCost = cost + rockets[selectedRocket].cost;
        int budget = missions[selectedMission].budget;
        int scienceTarget = missions[selectedMission].scienceTarget;
        int requiredDeltaV = missions[selectedMission].requiredDeltaV;

        bool budgetOK = totalCost <= budget;
        bool massOK = mass <= rockets[selectedRocket].payloadCapacity;
        bool powerOK = supply >= demand;
        bool communicationOK = communication >= data;
        bool propulsionOK = deltaV >= requiredDeltaV;
        bool rocketOrbitOK = rockets[selectedRocket].maximumDeltaV >= requiredDeltaV;
        bool scienceOK = science >= scienceTarget;
        bool batteryOK = battery >= requiredDeltaV * 40;

        int score = 0;
        if (budgetOK) score += 15;
        if (massOK) score += 15;
        if (powerOK) score += 15;
        if (communicationOK) score += 10;
        if (propulsionOK) score += 15;
        if (rocketOrbitOK) score += 10;
        if (scienceOK) score += 15;
        if (batteryOK) score += 5;

        cout << "\n\n";
        cout << "****************************************************\n";
        cout << "                 MISSION SIMULATION\n";
        cout << "****************************************************\n";
        cout << "Mission: " << missions[selectedMission].name << "\n\n";

        cout << left << setw(29) << "Engineering requirement" << "Result\n";
        cout << "----------------------------------------------------\n";
        cout << left << setw(29) << "Budget within limit"
             << (budgetOK ? "PASS" : "FAIL") << "\n";
        cout << left << setw(29) << "Rocket payload capacity"
             << (massOK ? "PASS" : "FAIL") << "\n";
        cout << left << setw(29) << "Power supply"
             << (powerOK ? "PASS" : "FAIL") << "\n";
        cout << left << setw(29) << "Communication capacity"
             << (communicationOK ? "PASS" : "FAIL") << "\n";
        cout << left << setw(29) << "Spacecraft propulsion"
             << (propulsionOK ? "PASS" : "FAIL") << "\n";
        cout << left << setw(29) << "Rocket mission capability"
             << (rocketOrbitOK ? "PASS" : "FAIL") << "\n";
        cout << left << setw(29) << "Scientific objective"
             << (scienceOK ? "PASS" : "FAIL") << "\n";
        cout << left << setw(29) << "Battery reserve"
             << (batteryOK ? "PASS" : "FAIL") << "\n";

        cout << "\nFINAL SCORE: " << score << "/100\n";

        if (score >= 90) {
            cout << "MISSION RESULT: EXCELLENT SUCCESS!\n";
            cout << "Your design meets nearly all mission requirements.\n";
        } else if (score >= 70) {
            cout << "MISSION RESULT: PARTIAL SUCCESS.\n";
            cout << "Your mission has potential, but some engineering limits remain.\n";
        } else {
            cout << "MISSION RESULT: MISSION FAILURE.\n";
            cout << "Your spacecraft design does not meet enough requirements.\n";
        }

        cout << "\nENGINEERING FEEDBACK\n";
        if (!budgetOK)
            cout << "- Reduce component or launch costs to meet the budget.\n";
        if (!massOK)
            cout << "- Reduce spacecraft mass or select a rocket with more payload capacity.\n";
        if (!powerOK)
            cout << "- Select a stronger power system or reduce power-consuming components.\n";
        if (!communicationOK)
            cout << "- Select a better antenna or reduce the amount of generated data.\n";
        if (!propulsionOK)
            cout << "- Choose a propulsion system with greater delta-v capability.\n";
        if (!rocketOrbitOK)
            cout << "- Select a launch vehicle capable of reaching the mission destination.\n";
        if (!scienceOK)
            cout << "- Add more scientific instruments to meet the science target.\n";
        if (!batteryOK)
            cout << "- Increase battery capacity to improve energy reserves.\n";

        if (score == 100) {
            cout << "- Excellent balance of cost, mass, power, science and mission capability!\n";
        }

        cout << "\nThis is a simplified educational model, not a real flight certification.\n";
        cout << "****************************************************\n";
    }

    void showInstructions() {
        cout << "\n================ HOW TO PLAY ================\n";
        cout << "1. Choose a mission objective.\n";
        cout << "2. Select scientific instruments for your spacecraft.\n";
        cout << "3. Select power, battery, communication and propulsion systems.\n";
        cout << "4. Choose a launch vehicle.\n";
        cout << "5. Review the mission dashboard.\n";
        cout << "6. Run the simulation and study the engineering feedback.\n\n";
        cout << "Every design choice has consequences:\n";
        cout << "- More instruments can increase scientific value and data generation.\n";
        cout << "- More equipment increases spacecraft mass and cost.\n";
        cout << "- Instruments and systems consume electrical power.\n";
        cout << "- Solar panels generate power; batteries provide energy reserves.\n";
        cout << "- Antennas determine how much data can be sent to Earth.\n";
        cout << "- Propulsion and rocket capability must suit the destination.\n";
        cout << "All numerical values are simplified for this educational game.\n";
        cout << "=============================================\n";
    }

public:
    SpaceMissionGame() {
        initializeData();
        resetDesign();
    }

    void start() {
        showHeader();

        cout << "Welcome, Mission Director!\n";
        cout << "Enter your name: ";
        getline(cin, playerName);

        if (playerName.length() == 0) {
            playerName = "Mission Director";
        }

        cout << "\nWelcome, " << playerName << "!\n";
        cout << "Your task is to design a spacecraft and complete a mission.\n";

        int choice;

        do {
            showHeader();
            cout << "Mission Director: " << playerName << "\n\n";
            cout << "1. How to Play\n";
            cout << "2. Select Mission Objective\n";
            cout << "3. Design Spacecraft\n";
            cout << "4. Select Launch Vehicle\n";
            cout << "5. View Mission Dashboard\n";
            cout << "6. Run Mission Simulation\n";
            cout << "7. Start a New Mission\n";
            cout << "8. Exit Game\n";

            choice = readNumber("\nEnter your choice (1-8): ", 1, 8);

            switch (choice) {
                case 1:
                    showInstructions();
                    break;
                case 2:
                    showMissions();
                    break;
                case 3:
                    designSpacecraft();
                    break;
                case 4:
                    chooseRocket();
                    break;
                case 5:
                    viewDashboard();
                    break;
                case 6:
                    runSimulation();
                    break;
                case 7:
                    resetDesign();
                    cout << "\nNew mission started. Select your objective.\n";
                    break;
                case 8:
                    cout << "\nThank you for playing, " << playerName << "!\n";
                    cout << "Keep exploring the universe!\n";
                    break;
            }

            if (choice != 8) {
                cout << "\nPress Enter to return to the main menu...";
                cin.get();
            }

        } while (choice != 8);
    }
};

int main() {
    SpaceMissionGame game;
    game.start();
    return 0;
}
