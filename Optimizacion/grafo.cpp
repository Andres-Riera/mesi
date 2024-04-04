 /*
 *  GRAFO.CPP - Plantilla para la implementaci�n de la clase GRAFOS
 *
 *
 *  Autores : Antonio Sedeno Noda, Sergio Alonso
 *  Cursos   : 2012-2021
 */

#include "grafo.h"

void GRAFO :: destroy()
{
	for (unsigned i=0; i< n; i++)
    {
		LS[i].clear();
		A[i].clear();
		if (dirigido == 1)
        {
            LP[i].clear();
        };
	}
	LS.clear();
	LP.clear();
	A.clear();

}

void GRAFO :: build (char nombrefichero[85], int &errorapertura)
{
    ElementoLista dummy;
	ifstream textfile;
	textfile.open(nombrefichero);
	if (textfile.is_open())
    {
		unsigned i, j, k;
		// leemos por conversion implicita el numero de nodos, arcos y el atributo dirigido
		textfile >> (unsigned &) n >> (unsigned &) m >> (unsigned &) dirigido;
		// los nodos internamente se numeran desde 0 a n-1
		// creamos las n listas de sucesores
		LS.resize(n);
        A.resize(n);
        if (dirigido == 1) { LP.resize(n); }
        // leemos los m arcos
		for (k=0;k<m;k++)
        	{
			textfile >> (unsigned &) i  >> (unsigned &) j >> (int &) dummy.c;
			//damos los valores a dummy.j y dummy.c
            dummy.j = j - 1;
			//situamos en la posici�n del nodo i a dummy mediante push_back
            LS[i - 1].push_back(dummy);
            A[i - 1].push_back(dummy);
            dummy.j = i -1;
            A[j -1].push_back(dummy);
			//pendiente de hacer un segundo push_back si es no dirigido. O no.
            if (dirigido == 1) {
            //pendiente la construcci�n de LP, si es dirigido
                LP[j - 1].push_back(dummy);
            } else {
                if (i != j) {
                    LS[j -1].push_back(dummy); // LS --> lista de adyacencia
                }
            }
			
        } 
        //...
        textfile.close();
            //pendiente del valor a devolver en errorapertura
        errorapertura = 0;
    } else { errorapertura = 1; }

}

GRAFO::~GRAFO()
{
	destroy();
}

GRAFO::GRAFO(char nombrefichero[85], int &errorapertura)
{
	build (nombrefichero, errorapertura);
}

void GRAFO:: actualizar (char nombrefichero[85], int &errorapertura)
{
    //Limpiamos la memoria dinamica asumida en la carga previa, como el destructor
    destroy();
    //Leemos del fichero y actualizamos G con nuevas LS y, en su caso, LP
    build(nombrefichero, errorapertura);
}

unsigned GRAFO::Es_dirigido()
{
    return dirigido;
}

void GRAFO::Info_Grafo()
{
    if (dirigido == 1) {
        cout << "El grafo es dirigido\n";
    } else { cout << "El grafo es no dirigido\n"; }
    cout << "Número de nodos: " << n << endl;
    cout << "Número de arcos: " << m << endl;
}

void Mostrar_Lista(vector<LA_nodo> L)
{
    int pos = 0;
    for (LA_nodo k : L) {
        if (!k.empty()) {
            cout << "Nodo " << pos + 1 << " : { ";
            for (ElementoLista l : k) {
                cout << "(" << l.j + 1<< ", " << l.c << ") "; 
            }
            cout << "}\n";
        }
        pos++;
    }
}


void GRAFO :: Mostrar_Listas (int l)
{
    if (l == 0) {
        cout << "Nodo : (Adyacente, Coste)\n";
        Mostrar_Lista(LS);
    } else if (l == 1) {
        cout << "Nodo : (Sucesor, Coste)\n";
        Mostrar_Lista(LS);
    } else if (l == -1) {
        cout << "Nodo : (Predecesor, Coste)\n";
        Mostrar_Lista(LP);
    }
}

void GRAFO::Mostrar_Matriz() { //Muestra la matriz de adyacencia, tanto los nodos adyacentes como sus costes
    cout << "Matriz de adyacencia:" << endl;
    for (unsigned k = 0; k < A.size(); k++) {
        cout << "| ";
        for (unsigned j = 0; j < A.size(); j++) {
            bool adyacente = false;
            for (const auto& elemento : A[k]) {
                if (elemento.j == j) {
                    adyacente = true;
                    break;
                }
            }
            if (adyacente) {
                cout << "1 ";
            } else {
                cout << "0 ";
            }
        }
        cout << "|" << endl;
    }

    cout << "Matriz de costos:" << endl;
    for (unsigned k = 0; k < A.size(); k++) {
        cout << "| ";
        for (unsigned j = 0; j < A.size(); j++) {
            int c = maxint;
            for (const auto& aux : A[k]) {
                if (aux.j == j) {
                    c = aux.c;
                    break;
                }
            }
            if (c != maxint) {
                cout << c << " ";
            } else {
                cout << "INF ";
            }
        }
        cout << "|" << endl;
    }
}



void GRAFO::dfs_num(unsigned i, vector<LA_nodo>  L, vector<bool> &visitado, vector<unsigned> &prenum, unsigned &prenum_ind, vector<unsigned> &postnum, unsigned &postnum_ind) //Recorrido en profundidad recursivo con recorridos enum y postnum
{
	visitado[i] = true;
    prenum[prenum_ind++]=i;//asignamos el orden de visita prenum que corresponde el nodo i
    for (unsigned j=0;j<L[i].size();j++)
             if (!visitado[L[i][j].j])
                {
                dfs_num(L[i][j].j, L, visitado, prenum, prenum_ind, postnum, postnum_ind);
                };
    postnum[postnum_ind++]=i;//asignamos el orden de visita posnum que corresponde al nodo i
}

void GRAFO::RecorridoProfundidad()
{
    // 1- Definir e inicializar vector de visita de los nodos 
    vector<bool> visitado;
    visitado.resize(n, false);
    // 2- Definir e inicializar prenum y postnum
    vector<unsigned> prenum;
    prenum.resize(n);
    vector<unsigned> postnum;
    postnum.resize(n);
    // 3- Definir e inicializar prenum_ind y postnum_ind
    unsigned prenum_ind = 0;
    unsigned postnum_ind = 0;
    // 4- Definir la variable del nodo inicial i
    unsigned i;
    // 5- Solicitar por pantalla el nodo inicial
    cout << "Introduce el nodo inicial" << endl;
    // 6- Asignamos el valor del nodo inicial i
    cin >> i;
    // 7- Realizamos el recorrido en profundidad 
    dfs_num(i-1, LS, visitado, prenum, prenum_ind, postnum, postnum_ind);
    // 8- Imprimir en pantalla la información almacenada en prenum y postnum
    cout << "Orden de visita de los nodos en preorden" << endl;
    for (int k = 0; k < prenum.size(); k++) {
        cout << "[" << prenum[k] + 1  << "] ";
        if (k != prenum.size() - 1) { cout << "-> "; }
    }
    cout << "\nOrden de visita de los nodos en postorden" << endl;
    for (int k = 0; k < postnum.size(); k++) {
        cout << "[" << postnum[k] + 1  << "] ";
        if (k != postnum.size() - 1) { cout << "-> "; }
    }
    cout << endl;
}

void GRAFO::bfs_num(	unsigned i, //nodo desde el que realizamos el recorrido en amplitud
				vector<LA_nodo>  L, //lista que recorremos, LS o LP; por defecto LS
				vector<unsigned> &pred, //vector de predecesores en el recorrido
				vector<unsigned> &d) //vector de distancias a nodo i+1
//Recorrido en amplitud con la construcci�n de pred y d: usamos la cola
{
    vector<bool> visitado; //creamos e iniciamos el vector visitado
    visitado.resize(n, false);
    visitado[i] = true;

    pred.resize(n, 0); //creamos e inicializamos pred y d
    d.resize(n, 0);
    pred[i] = i;
    d[i] = 0;

    queue<unsigned> cola; //creamos e inicializamos la cola
    cola.push(i);//iniciamos el recorrido desde el nodo i+1

    while (!cola.empty()) //al menos entra una vez al visitar el nodo i+1 y contin�a hasta que la cola se vac�e
    {   unsigned k = cola.front(); //cogemos el nodo k+1 de la cola
        cola.pop(); //lo sacamos de la cola
        //Hacemos el recorrido sobre L desde el nodo k+1
        for (unsigned j=0;j<L[k].size();j++)
            //Recorremos todos los nodos u adyacentes al nodo k+1
            //Si el nodo u no est� visitado 
            if (!visitado[L[k][j].j]){
            //Lo visitamos
                L[k][j].j == true;
            //Lo metemos en la cola
                cola.push(L[k][j].j);
            //le asignamos el predecesor
                pred[L[k][j].j] = k;
            //le calculamos su etiqueta distancia
                d[L[k][j].j] = d[k] + 1;
            };
        //Hemos terminado pues la cola est� vac�a
    };
}


void GRAFO::RecorridoAmplitud() //Construye un recorrido en amplitud desde un nodo inicial
{
    // 1- Definir los vectores pred y d
    vector<unsigned> pred;
    vector<unsigned> d;
    // 2- Definimos la variable del nodo inicial
    unsigned i;
    // 3- Solicitamos por pantalla el nodo inicial
    cout << "Introduce el nodo inicial" << endl;
    // 4- Asignamos el valor del nodo inicial
    cin >> i;
    // 5- Realizamos el recorrido en amplitud
    bfs_num(i - 1, LS, pred, d);
    // 6- Imprimimos en pantalla la información de pred y d
    cout << "Nodo inicial: " << i << endl;
    cout << "\nNodos según distancia al nodo inicial en número de aristas" << i << endl;
    bool first = true;
    for (int k = 0; k <= d[d.size() - 1]; ++k) {
        cout << "Distancia " << k << " aristas : ";
        for (int j = 0; j < d.size(); j++) {
            if (k == d[j] && k == 0 && first) {
                cout << j + 1 << " ";
                first = false;
            }
            else if (k == d[j] && k == 0 && !first) {

            }
            else if (k == d[j]) {
                cout << j + 1 << " ";
            }
        }
        cout << endl;
    }
    cout << "Ramas de conexión en el recorrido" << endl;
    for (unsigned k = 1; k < pred.size(); k++) {
        cout << k + 1 << " - ";
        cout << pred[k]+1 << endl;
    }
    cout << endl;    
}