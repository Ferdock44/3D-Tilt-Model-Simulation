#include <iostream>
#include <string>
#include <limits>
#include "environment.h"
#include "app.h"

using namespace std;


int main()
{
    // Prompt user for action
    cout << "3D Tilt Simulation" << endl << endl
    << "[C] Create Environment" << endl << endl;

    string input;
    
    cin >> input;
    while (input != "C") {
        errorMessage();
        cin >> input;
    }

    if (input == "C") {
        system ("CLS");
        cout << "Environment Creation: Set Bounds" << endl;
        int x, y, z;
        intput_xyz(x, y, z);
        Environment env(x, y, z);

        bool flag = true;
        int b;
        do
        {
            system ("CLS");
            cout << "Environment Creation: Enter operation to perform" << endl << endl
            << "All coordinates are based on 0-indexed positions" << endl << endl
            << "[0] See Environment" << endl
            << "[1] See Layer" << endl
            << "[2] Fill Layer" << endl
            << "[3] Coordinate Modify" << endl
            << "[4] Undo Environment Modification (max 1)" << endl
            << "[F] Finish Environment Setup" << endl << endl;

            cin >> input;
            while (input != "0" && input != "1" && input != "2" && input != "3" && input != "4" && input != "F") {
                errorMessage();
                cin >> input;
            }

            if (input == "0") {
                env.see_environment();
            }
            else if (input == "1"){
                cout << "Only input for layers to be seen, -1 otherwise" << endl;
                intput_xyz(x, y, z);
                env.see_layer(x, y, z);
            }
            else if (input == "2"){
                cout << "Only input for layer to be filled, -1 otherwise" << endl;
                intput_xyz(x, y, z);
                env.fill_layer(x, y, z);
                cout << endl << "Filled layer " << x << " " << y << " " << z << endl << endl;
                system("pause");
            }
            else if (input == "3"){
                intput_xyz(x, y, z);
                cout << endl << "Input [0] for empty space and [1] for obstacle" << endl;
                cin >> b;
                while (!cin) {
                    errorMessage();
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin >> b;
                }
                env.coordinate_modify(x, y, z, b);
                cout << endl << "Modified at " << x << " " << y << " " << z << " to " << b << endl << endl;
                system("pause");
            }
            else if (input == "4"){
                env.undo();
                cout << endl << "Previous operation reverted" << endl << endl;
                system("pause");
            }
            else{
                vector<string> tilt_log = {};
                flag = true;
                int id;
                do
                {
                    system ("CLS");
                    cout << "Simulation: Enter operation to perform" << endl << endl
                    << "[0] See Environment" << endl
                    << "[1] See Layer" << endl
                    << "[2] Add Particle" << endl
                    << "[3] See All Particles" << endl
                    << "[4] See Particle at ID" << endl
                    << "[5] See Tilt History" << endl
                    << "[6] Undo Tilt (max 1)" << endl
                    << "[U] Tilt Up" << endl
                    << "[D] Tilt Down" << endl
                    << "[L] Tilt Left" << endl
                    << "[R] Tilt Right" << endl
                    << "[F] Tilt Forward" << endl
                    << "[B] Tilt Backward" << endl
                    << "[E] Exit" << endl << endl;

                    cin >> input;
                    while (input != "0" && input != "1" && input != "2" && input != "3" && input != "4" && input != "5" && input != "6" &&
                    input != "U" && input != "D" && input != "R" && input != "L" && input != "F" && input != "B" && input != "E") {
                        errorMessage();
                        cin >> input;
                    }

                    if (input == "0") {
                        env.see_environment();
                    }
                    else if (input == "1"){
                        cout << "Only input for layers to be seen, 0 otherwise";
                        intput_xyz(x, y, z);
                        env.see_layer(x, y, z);
                    }
                    else if (input == "2"){
                        intput_xyz(x, y, z);
                        cout << "ID: ";
                        cin >> id;
                        while (!cin) {
                            errorMessage();
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cin >> id;
                        }
                        if(env.add_particle(id, x, y, z) == -1){
                            cout << "Error: Obstacle; Out of bounds; Exisitng particle" << endl << endl;
                            system("pause");
                        }
                        else{
                            cout << endl << "Added particle ID: " << id << " at " << x << " " << y << " " << z << endl << endl;
                            system("pause");
                        }
                    }
                    else if (input == "3"){
                        env.see_all_particles();
                    }
                    else if (input == "4"){
                        cout << "ID: ";
                        cin >> id;
                        while (!cin) {
                            errorMessage();
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cin >> id;
                        }
                        env.see_particles_at_id(id);
                    }
                    else if (input == "5"){
                        cout << "Tilt History: " << endl;
                        for (int i = 0; i < size(tilt_log); i++) {
                            cout << tilt_log[i] << endl;
                        }
                        cout << endl;
                        system("pause");
                    }
                    else if (input == "6"){
                        env.undo_tilt();
                        tilt_log.pop_back();
                        cout << endl << "Previous tilt reverted" << endl << endl;
                        system("pause");
                    }
                    else if (input == "U"){
                        env.tilt_up();
                        tilt_log.push_back("Up");
                    }
                    else if (input == "D"){
                        env.tilt_down();
                        tilt_log.push_back("Down");
                    }
                    else if (input == "L"){
                        env.tilt_left();
                        tilt_log.push_back("Left");
                    }
                    else if (input == "R"){
                        env.tilt_right();
                        tilt_log.push_back("Right");
                    }
                    else if (input == "F"){
                        env.tilt_forward();
                        tilt_log.push_back("Forward");
                    }
                    else if (input == "B"){
                        env.tilt_backward();
                        tilt_log.push_back("Backward");
                    }
                    else if (input == "E"){
                        flag = false;
                    }
                } while (flag);
            }
        } while (flag);
    }
    return 0;
}
