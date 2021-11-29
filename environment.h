#include <vector>
#include <string>
#include <iostream>
#include "particle.h"

using namespace std;


void save_particle_positions (vector<Particle>& particles) {
    for (int i = 0; i < size(particles); i++){
        particles[i].save_position();
    }
}


class Environment {
        int x, y, z;
        vector<vector<vector<int>>> environment, backup;
        vector<Particle> particles;
    public:
        Environment(int, int, int);
        void coordinate_modify (int, int, int, bool);
        void see_environment();
        void undo();
        void undo_add_particle();
        void undo_tilt();
        void see_layer (int, int, int);
        void fill_layer (int, int, int);
        int add_particle (int, int, int, int);
        void see_particles_at_id (int);
        void see_all_particles();
        void tilt_up();
        void tilt_down();
        void tilt_left();
        void tilt_right();
        void tilt_forward();
        void tilt_backward();
};


// Sets initial bounds for environment
Environment::Environment (int x, int y, int z) {
    this->x = x;
    this->y = y;
    this->z = z;
    vector<vector<vector<int>>> temp(x, vector<vector<int>>(y, vector<int> (z, 0)));
    environment = temp;
    backup = environment;
}

// Environment
void Environment::see_environment() {
    for(int i = 0; i < size(environment); i++){
        cout << endl << i << "  ";
        for(int j = 0; j < size(environment[i]); j++){
            cout << j << " ";
        }
        cout << endl;
        for(int j = 0; j < size(environment[i]); j++){
            cout << j << ": ";
            for(int x = 0; x < size(environment[i][j]); x++){
                cout << environment[i][j][x] << " ";
            }
            cout << endl;
        }
    }
    cout << endl;
    system("pause");
}

// Returns a specified environment layer
void Environment::see_layer (int x, int y, int z) {
    if(x != -1) {
        for(int i = 0; i < size(environment[x]); i++){
            cout << endl;
            for(int j = 0; j < size(environment[x][i]); j++){
                cout << environment[x][i][j] << " ";
            }
        }
    }
    else if(y != -1) {
        for(int i = 0; i < size(environment); i++){
            cout << endl;
            for(int j = 0; j < size(environment[i][y]); j++){
                cout << environment[i][y][j] << " ";
            }
        }
    }
    else {
        for(int i = 0; i < size(environment); i++){
            cout << endl;
            for(int j = 0; j < size(environment[i]); j++){
                cout << environment[i][j][z] << " ";
            }
        }
    }
    cout << endl << endl;
    system("pause");
}

void Environment::fill_layer (int x, int y, int z) {
    backup = environment;
    if(x != -1) {
        for(int i = 0; i < size(environment[x]); i++){
            for(int j = 0; j < size(environment[x][i]); j++){
                environment[x][i][j] = 1;
            }
        }
    }
    else if(y != -1) {
        for(int i = 0; i < size(environment); i++){
            for(int j = 0; j < size(environment[i][y]); j++){
                environment[i][y][j] = 1;
            }
        }
    }
    else{
        for(int i = 0; i < size(environment); i++){
            for(int j = 0; j < size(environment[i]); j++){
                environment[i][j][z] = 1;
            }
        }
    }
}

// Undo previous operation
void Environment::undo() {
    environment = backup;
}

void Environment::undo_add_particle() {
    environment = backup;
    particles.pop_back();
}

void Environment::undo_tilt() {
    environment = backup;
    for (int i = 0; i < size(particles); i++) {
        particles[i].set_saved_position();
    }
}

// Modifies a single position within environment (0 for empty, 1 for obstacle)
void Environment::coordinate_modify (int x, int y, int z, bool b) {
    backup = environment;
    (b) ? environment[x][y][z] = 1 : environment[x][y][z] = 0;
}

int Environment::add_particle (int id, int x, int y, int z){
    if (x < 0 || x >= this->x || y < 0 || y >= this->y || z < 0 || z >= this->z || environment[x][y][z] != 0) {
        return -1;
    }
    Particle particle(id, x, y, z);
    particles.push_back(particle);
    environment[x][y][z] = 2;
    return 0;
}

void Environment::see_all_particles(){
    for(int i = 0; i < size(particles); i++){
        int x, y, z;
        particles[i].position(x, y, z);
        cout << endl << "ID: " << particles[i].id_number() << ", Position: " << x << " " << y << " " << z;
    }
    cout << endl << endl;
    system("pause");
}

void Environment::see_particles_at_id(int id){
    bool flag = true;
    for(int i = 0; i < size(particles); i++){
        if(particles[i].id_number() == id){
            int x, y, z;
            particles[i].position(x, y, z);
            cout << "Position: " << x << " " << y << " " << z;
            flag = false;
        }
    }
    if (flag) {
        cout << "No particle with selected ID" << id;
    }
    cout << endl << endl;
    system("pause");
}

void Environment::tilt_up(){
    backup = environment;
    save_particle_positions(particles);
    bool flag;
    do
    {
        flag = false;
        for(int i = 0; i < size(particles); i++){
            int x, y, z;
            particles[i].position(x, y, z);
            environment[x][y][z] = 0;
            while(x+1 < this->x && environment[x+1][y][z] == 0){
                x++;
                flag = true;
            }
            particles[i].set_position(x, y, z);
            environment[x][y][z] = 2;
        }
    } while (flag);
}

void Environment::tilt_down(){
    backup = environment;
    save_particle_positions(particles);
    bool flag;
    do
    {
        flag = false;
        for(int i = 0; i < size(particles); i++){
            int x, y, z;
            particles[i].position(x, y, z);
            environment[x][y][z] = 0;
            while(x-1 >= 0 && environment[x-1][y][z] == 0){
                x--;
                flag = true;
            }
            particles[i].set_position(x, y, z);
            environment[x][y][z] = 2;
        }
    } while (flag);
}

void Environment::tilt_left(){
    backup = environment;
    save_particle_positions(particles);
    bool flag;
    do
    {
        flag = false;
        for(int i = 0; i < size(particles); i++){
            int x, y, z;
            particles[i].position(x, y, z);
            environment[x][y][z] = 0;
            while(y-1 >= 0 && environment[x][y-1][z] == 0){
                y--;
                flag = true;
            }
            particles[i].set_position(x, y, z);
            environment[x][y][z] = 2;
        }
    } while (flag);
}

void Environment::tilt_right(){
    backup = environment;
    save_particle_positions(particles);
    bool flag;
    do
    {
        flag = false;
        for(int i = 0; i < size(particles); i++){
            int x, y, z;
            particles[i].position(x, y, z);
            environment[x][y][z] = 0;
            while(y+1 < this->y && environment[x][y+1][z] == 0){
                y++;
                flag = true;
            }
            particles[i].set_position(x, y, z);
            environment[x][y][z] = 2;
        }
    } while (flag);
}

void Environment::tilt_forward(){
    backup = environment;
    save_particle_positions(particles);
    bool flag;
    do
    {
        flag = false;
        for(int i = 0; i < size(particles); i++){
            int x, y, z;
            particles[i].position(x, y, z);
            environment[x][y][z] = 0;
            while(z+1 < this->z && environment[x][y][z+1] == 0){
                z++;
                flag = true;
            }
            particles[i].set_position(x, y, z);
            environment[x][y][z] = 2;
        }
    } while (flag);
}

void Environment::tilt_backward(){
    backup = environment;
    save_particle_positions(particles);
    bool flag;
    do
    {
        flag = false;
        for(int i = 0; i < size(particles); i++){
            int x, y, z;
            particles[i].position(x, y, z);
            environment[x][y][z] = 0;
            while(z-1 >= 0 && environment[x][y][z-1] == 0){
                z--;
                flag = true;
            }
            particles[i].set_position(x, y, z);
            environment[x][y][z] = 2;
        }
    } while (flag);
}
