class Particle {
    int id, x, y, z, px, py, pz;
    public:
        Particle (int, int, int, int);
        void set_id (int);
        void set_position (int, int, int);
        void save_position ();
        void set_saved_position ();
        int id_number();
        void position(int&, int&, int&);
};

Particle::Particle (int id, int x, int y, int z){
    this->id = id;
    this->x = x;
    this->y = y;
    this->z = z;
}

void Particle::set_id (int id){
    this->id = id;
}

void Particle::set_position (int x, int y, int z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

void Particle::save_position () {
    this->px = this->x;
    this->py = this->y;
    this->pz = this->z;
}

void Particle::set_saved_position () {
    this->x = this->px;
    this->y = this->py;
    this->z = this->pz;
}

void Particle::position(int& x, int& y, int& z) {
    x = this->x;
    y = this->y;
    z = this->z;
}

int Particle::id_number() {
    return id;
}
