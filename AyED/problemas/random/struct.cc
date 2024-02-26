#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Equipo {
   string nombre_;
   int partidos_jugados_;
   int partidos_ganados_;
   int partidos_empatados_; 
};

struct Clasificacion_Equipos {
  string equipo;
  int puntos;
};


void Tabla(struct Equipo liga[n], struct Clasificacion_Equipos clasificacion[n]) {
  for (int i = 0; i < n; i++) {
    clasificacion[i].equipo = liga[i].nombre_;
    clasificacion[i].puntos = liga[i].partidos_ganados_ * 3 + liga[i].partidos_empatados_;
  }
}

int main() {
    struct Equipo Liga[22];
    vector<Clasificacion_Equipos> Clasificacion[22];
    return 0;
}