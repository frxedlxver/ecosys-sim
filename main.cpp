#include <iostream>
#include <thread>
#include "map.hpp"
#include "humanoid_controller.hpp"

using std::cout, std::this_thread::sleep_for, std::chrono::milliseconds;

void testRuns(int numberOfRuns);
void normalRun();

// To run this program normally, use without any arguments.

// To perform a series of test runs,
// run this program with a single argument (integer only)
// indicating the number of test runs to perform.
// Tests will run the program without any visual representation.
// Runs are marked as successful if they reach 100 turns without an extinction event.
// After all runs are completed, program will tell you how many were successful.
int main(int argc, char *argv[]) {

    if(argc > 1) {
        try {
            testRuns(std::stoi(argv[1]));
        } catch (std::exception) {
            cout << "Incorrect argument usage.";
        }
    } else {
        normalRun();
    }


    return 0;
}

void normalRun() {
    Map m = Map();
    HumanoidController *hc = new HumanoidController(&m);

    int turns = 0;
    do {
        // print game state
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        cout << &m;
        cout << "\nTURN " << turns << "\nHUMANS: " << hc->getCurrentHumanCount() << " - ZOMBIES: " << hc->getCurrentZombieCount();
        sleep_for(milliseconds(FRAME_SPEED_MS));

        // process game
        hc->processFrame();
        turns++;

    } while(!hc->extinctionEvent());

    // after extinction, print final map and stats
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << &m;
    cout << "\nTURNS BEFORE EXTINCTION: " << turns;
    cout << "\nHUMANS AT END: " << hc->getCurrentHumanCount() << " - ZOMBIES AT END: " << hc->getCurrentZombieCount();
    cout << "\nTOTAL HUMANS ALL TIME: " << hc->getTotalHumanCount() << " - ZOMBIES ALL TIME: " << hc->getTotalZombieCount();
}

void testRuns(int numberOfRuns) {

    int successfulRuns = 0;
    for(int i = 0; i < numberOfRuns; i++) {
        Map m = Map();
        HumanoidController *hc = new HumanoidController(&m);

        int turns = 0;
        do {
            hc->processFrame();
            turns++;

            if (turns > 100) {
                break;
            }

        } while(!hc->extinctionEvent());

        if(turns >= 100) {
            successfulRuns += 1;
        }
    }

    cout << successfulRuns << "/" << numberOfRuns << " runs were successful!";
}

