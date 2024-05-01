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

void GRAFO::Mostrar_Matriz() //Muestra la matriz de adyacencia, tanto los nodos adyacentes como sus costes
{ 
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

//Recorrido en amplitud con la construcci�n de pred y d: usamos la cola
void GRAFO::bfs_num(	unsigned i, //nodo desde el que realizamos el recorrido en amplitud
				vector<LA_nodo>  L, //lista que recorremos, LS o LP; por defecto LS
				vector<unsigned> &pred, //vector de predecesores en el recorrido
				vector<unsigned> &d) //vector de distancias a nodo i+1 
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
        for (unsigned j=0;j<L[k].size();++j) {
            //Recorremos todos los nodos u adyacentes al nodo k+1
            //Si el nodo u no est� visitado
            if (!visitado[L[k][j].j]){
            //Lo visitamos
                visitado[L[k][j].j] = true;
            //Lo metemos en la cola
                cola.push(L[k][j].j);
            //le asignamos el predecesor
                pred[L[k][j].j] = k;
            //le calculamos su etiqueta distancia
                d[L[k][j].j] = d[k] + 1;
            }
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
    for (int k = 0; k <= d[d.size() - 1]; k++) {
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
    for (int k = 1; k < pred.size(); k++) {
        cout << k + 1 << " <- ";
        cout << pred[k]+1 << endl;
    }
    cout << endl;    
}

void GRAFO::Kruskal() {
    vector <AristaPesada> Aristas;
    // Cargamos todas las aristas de la lista de adyacencia
    Aristas.resize(m);
    unsigned k = 0;
    for (unsigned i = 0; i<n; i++) {
        for (unsigned j=0; j<LS[i].size();j++) {
            if (i < LS[i][j].j) {
                Aristas[k].extremo1 = i;
                Aristas[k].extremo2 = LS[i][j].j;
                Aristas[k++].peso = LS[i][j].c;
            }
        }
    };

    // Inicializamos el registro de componentes conexas: cada nodo está en su componente conexa
    vector<unsigned> Raiz;
    Raiz.resize(n);
    for (unsigned q = 0; q < n; q++) {
        Raiz[q]=q;
    };

    int head = 0;
    int n_aristas = 0;
    int peso_total = 0;
    do {
        // Colocamos en la posición head la arista con menor peso desde head + 1
        if(head < m - 1) {
            for (unsigned i = head + 1; i < m; i++) {
                if(Aristas[head].peso > Aristas[i].peso) {
                    AristaPesada temp = Aristas[i];
                    Aristas[i] = Aristas[head];
                    Aristas[head] = temp;
                }
            }
        }

        // Si los extremos de las aristas tienen distinta raíz actualizamos la raíz de uno de ellos
        if(Raiz[Aristas[head].extremo1] != Raiz[Aristas[head].extremo2]) {
            unsigned kill = Raiz[Aristas[head].extremo1];
            for (unsigned i = 0; i < n - 1; i++) {
                if (Raiz[i] == kill) {
                    Raiz[i] = Raiz[Aristas[head].extremo2];
                }
            }
            // Incorporamos la arista
            cout << "Arista número " << ++n_aristas << " incorporada (" << Aristas[head].extremo1 + 1 << ", " 
                 << Aristas[head].extremo2 + 1 << ") con peso " << Aristas[head].peso << endl;
            peso_total += Aristas[head].peso;
        }

        head++;
    } while (head < m && n_aristas < n - 1);
    
    if (n_aristas  == n - 1) {
        cout << "El peso del arbol generador de mínimo coste es " << peso_total << endl;
    } else {
        cout << "El grafo no es conexo y el bosque generador de mínimo coste tiene peso " << peso_total << endl;
    }
}

/*
Tests de circuitos de coste negativo

Si no hay -> camino óptimo
es elemental (no repite nodo) -> a lo sumo usa n - 1 arcos
eoc
Definir 
Cmin = min {Cij : Cij < 0}
El menor valor posible de di es (n - 1) Cmin
->  Si algún di < (n - 1) Cmin -> con seguridad hay un circuito de coste negativo
*/

void GRAFO::PDM() {
    deque<unsigned> dcola;
    vector<int> d;
    vector<unsigned> pred;
    vector<bool> Encola;
    unsigned s;
    bool Negativo = false;
    int Cmin = 0;

    for (LA_nodo j : LS) {
        if (!j.empty()) {
            for (ElementoLista l : j) {
                if (l.c < Cmin) {
                    Cmin = l.c;
                } 
            }
        }
    }

    //Inicialmente no hay ningun nodo permanentemente etiquetado
    Encola.resize(n,false);
    //Inicialmente todas las etiquetas distancias son infinito
    d.resize(n,maxint);
    //Inicialmente el pred es null
    pred.resize(n,0);
    //- Pedimos por pantalla el nodo de partida s.
    cout << "Introduce el nodo de salida" << endl;
    cin >> s;
    s = s - 1;
    //La etiqueta distancia del nodo s es 0, y es su propio pred
    d[s]=0; pred[s]=s;
    //añadimos s a dcola y actualizamos Encola
    dcola.push_back(s); Encola[s] = true;
    while (!dcola.empty() && !Negativo) {
         //- Sacamos el primer nodo, k, de la dcola y lo borramos. Debemos actualizar también Encola.
         unsigned k = dcola.front();
         dcola.pop_front();
         Encola[k] = false;
        /*- Recorremos la lista de sucesores que permite identificar los arcos (k,
        j). Si d[j] > d[k] + ckj para el arco (k, j) significa que podemos mejorar
        el camino actual hacía el nodo j pasando por k. Para ello actualizamos d
        y pred y debemos añadir el nodo j en la cola siempre que no esté en ella.
        Ojo, hay que distinguir cuando se añade al final o al principio de la
        dcola. Es decir, seguir el siguiente pseudo-código.
        - */
        // Para todo nodo j sucesor del nodo k Hacer
        for (ElementoLista aux : LS[k]) {
            unsigned j = aux.j;
            // Si (dj > dk + ckj) entonces {
            if (d[j] > d[k] + aux.c) {
                // si el nodo j nunca ha estado en la cola
                // Si (predj == 0) entonces
                if (pred[j] == 0) {
                    // InsertarEnCola(j,dcola);  final de cola
                    dcola.push_back(j);
                    Encola[j] = true;
                }
                // en otro caso  ya ha estado en la cola
                else {
                    // si NoEstaEnCola(j, dcola)entonces
                    if (Encola[j] == false) {
                        // IsertarPrincipioCola(j, dcola);
                        dcola.push_front(j);
                        Encola[j] = true;
                    }
                }
                // dj = dk + ckj; predj = k; Actualizar Encola;
                d[j] = d[k] + aux.c; 
                pred[j] = k;
                if (d[j] < 0 && d[j] < Cmin) {
                    Negativo = true;
                    break;
                }
            }
        }
    }

// En esta parte del código, mostramos los caminos mínimos para cada nodo si
// los hay, y siempre y cuando no haya circuitos de coste negativo.
    if (!Negativo) {
        cout << "Soluciones:" << endl;
        for (int j = 0; j < n; j++) {
            if (j != s) {
                cout << "El camino del nodo " << s + 1 << " al nodo " << j + 1 << " es : ";
                MostrarCamino(s, j, pred);
                cout << " de longitud " << d[j] << endl;
            }
        }
    } else {
        cout << "Existe al menos un circuito de coste negativo en el grafo\n";
    }
}


void GRAFO::MostrarCamino(unsigned s, unsigned i, vector<unsigned>& pred) {
    if (i != s) {
        MostrarCamino(s,pred[i],pred);
        cout << " -> " << i + 1;
    }
    else {
        cout << i + 1;
    }
}
