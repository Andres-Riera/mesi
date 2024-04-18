 /*
 *  Programa principal.
 *
 *
 *               Autores : Antonio Sedeno Noda, Sergio Alonso.
 *               Cursos  : 2012-2021
 */

#include <string.h>
#include <cstdlib> // For system("pause") in Windows

#include "grafo.h"


// Function to clear the screen
void clrscr() {
    // Use system dependent command to clear the screen
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Function to wait for user input
void pressanykey() {
    cout << "Presione enter para continuar" << endl;
    std::cin.ignore(); // Ignore any previous newline character
    std::cin.get();    // Wait for user to press Enter
}



void menu (unsigned dirigido, char &opcion)
//Expresion del menu de opciones segun sea un grafo dirigido o no dirigido
{
    cout << "Optimiza!cion en Grafos, 2023-2024 Andrés David Riera Rivera" << endl;
    cout << "c. [c]argar grafo desde fichero" << endl;
    if (dirigido == 0) //Grafo no dirigido
            {
            cout << "i. Mostrar [i]nformacion basica del grafo" << endl;
            cout << "a. Mostrar la lista de [a]dyacencia del grafo" << endl;
	        //Aqu� se a�aden m�s opciones al men� del grafo no dirigido
            cout << "y. Mostrar la matriz de ad[y]acencia del grafo" << endl;
            cout << "m. Realizar un recorrido en a[m]plitud del grafo desde un nodo por sucesores" << endl;
            cout << "r. Realizar un recorrido en p[r]ofundidad del grafo desde un nodo por sucesores" << endl;
            cout << "k. Mostrar arbol generador minimo coste, [k]ruskal" << endl;
            }
    else
            {
            cout << "i. Mostrar [i]nformacion basica del grafo" << endl;
            cout << "s. Mostrar la lista de [s]ucesores del grafo" << endl;
            cout << "p. Mostrar la lista de [p]redecesores del grafo" << endl;
	        //Aqu� se a�aden m�s opciones al men� del grafo dirigido
            cout << "y. Mostrar la matriz de ad[y]acencia del grafo" << endl;
            cout << "m. Realizar un recorrido en a[m]plitud del grafo desde un nodo por sucesores" << endl;
            cout << "r. Realizar un recorrido en p[r]ofundidad del grafo desde un nodo por sucesores" << endl;
            };
    cout << "q. Finalizar el programa" << endl;
    cout << "Introduce la letra de la accion a ejecutar  > ";
    cin >> opcion;
};


// El principal es simplemente un gestor de menu, diferenciando acciones para dirigido y para no dirigido, y un men� inicial si no hay un grafo cargado
int main(int argc, char *argv[])
{
    int error_apertura;
    char nombrefichero[85], opcion;
    clrscr();
    //Si tenemos el nombre del primer fichero por argumento, es una excepcion, y lo intentamos cargar, si no, lo pedimos desde teclado
    if (argc > 1)
    {
	cout << "Cargando datos desde el fichero dado como argumento" << endl;
        strcpy(nombrefichero, argv[1]);
    }
    else
    {
        cout << "Introduce el nombre completo del fichero de datos" << endl;
        cin >> nombrefichero;
    };
    GRAFO G(nombrefichero, error_apertura);
    if (error_apertura == 1)
    {
        cout << "Error en la apertura del fichero desde argumento: revisa nombre y formato" << endl;
        pressanykey();
        clrscr();
    }
    else
    {
        cout<< "Grafo cargado desde el fichero " << nombrefichero << endl;
        clrscr();
        do
        {
            menu(G.Es_dirigido(), opcion);
            if (G.Es_dirigido()) {
                switch (opcion)
                {
                 case 'c' :
                        clrscr();
         	        cout << "Introduce el nombre completo del fichero de datos" << endl;
                        cin >> nombrefichero;
                        G.actualizar(nombrefichero, error_apertura);
                        if (error_apertura == 1)
                        {
                            cout << "Error en la apertura del fichero: revisa nombre y formato : puedes volver a intentarlo" << endl;
                        }
                        else
                        {
                            cout << "Fichero cargado correctamente desde " << nombrefichero << endl;
                        };
                        pressanykey();
                        clrscr();
                        break;

                    case 'i' :
                        clrscr();
		                cout << "Grafo cargado desde " << nombrefichero << endl;
                        G.Info_Grafo();
                        pressanykey();
                        clrscr();
                        break;

                    case 's' :
                        clrscr();
                        cout << "Grafo cargado desde " << nombrefichero << endl;
                        G.Mostrar_Listas(1);
                        pressanykey();
                        clrscr();
                        break;

                    case 'p' :
                        clrscr();
                        cout << "Grafo cargado desde " << nombrefichero << endl;
                        G.Mostrar_Listas(-1);
                        pressanykey();
                        clrscr();
                        break;
                    
                    case 'm' :
                        clrscr();
                        cout << "Grafo cargado desde " << nombrefichero << endl;
                        G.RecorridoAmplitud();
                        pressanykey();
                        clrscr();
                        break;
                    
                    case 'r' :
                        clrscr();
                        cout << "Grafo cargado desde " << nombrefichero << endl;
                        G.RecorridoProfundidad();
                        pressanykey();
                        clrscr();
                        break;
                    
                    case 'y' :
                        clrscr();
                        cout << "Grafo cargado desde " << nombrefichero << endl;
                        G.Mostrar_Matriz();
                        pressanykey();
                        clrscr();
                        break;

                    case 'q' :
                        break;
                    
                    default :
                        cout << "Opción inválida" << endl;
                        pressanykey();
                        clrscr();
                        break;
                }
            } else {
              switch (opcion)
                {
                 case 'c' :
                        clrscr();
         	        cout << "Introduce el nombre completo del fichero de datos" << endl;
                        cin >> nombrefichero;
                        G.actualizar(nombrefichero, error_apertura);
                        if (error_apertura == 1)
                        {
                            cout << "Error en la apertura del fichero: revisa nombre y formato : puedes volver a intentarlo" << endl;
                        }
                        else
                        {
                            cout << "Fichero cargado correctamente desde " << nombrefichero << endl;
                        };
                        pressanykey();
                        clrscr();
                        break;

                    case 'i' :
                        clrscr();
		                cout << "Grafo cargado desde " << nombrefichero << endl;
                        G.Info_Grafo();
                        pressanykey();
                        clrscr();
                        break;

                    case 'a' :
                        clrscr();
                        cout << "Grafo cargado desde " << nombrefichero << endl;
                        G.Mostrar_Listas(0);
                        pressanykey();
                        clrscr();
                        break;
                    
                    case 'm' :
                        clrscr();
                        cout << "Grafo cargado desde " << nombrefichero << endl;
                        G.RecorridoAmplitud();
                        pressanykey();
                        clrscr();
                        break;
                    
                    case 'r' :
                        clrscr();
                        cout << "Grafo cargado desde " << nombrefichero << endl;
                        G.RecorridoProfundidad();
                        pressanykey();
                        clrscr();
                        break;
                    
                    case 'y' :
                        clrscr();
                        cout << "Grafo cargado desde " << nombrefichero << endl;
                        G.Mostrar_Matriz();
                        pressanykey();
                        clrscr();
                        break;

                    case 'k' :
                        clrscr();
                        cout << "Grafo cargado desde " << nombrefichero << endl;
                        G.Kruskal();
                        pressanykey();
                        clrscr();
                        break;
                    
                    case 'q' :
                        clrscr();
                        break;

                    default :
                        clrscr();
                        cout << "Opción inválida" << endl;
                        pressanykey();
                        clrscr();
                        break;
                }
            }
    }
    while (opcion != 'q');
    }
    cout << "Fin del programa" << endl;
	return(0);
};
