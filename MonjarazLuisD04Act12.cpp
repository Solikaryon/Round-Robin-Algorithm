#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include <string.h>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <cctype>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <unordered_set>
#include <queue>
#include <chrono>

using namespace std;
using namespace chrono;

// Código creado por Monjaraz Briseño Luis Fernando

int totalProcesses;
int totallotes;
int totallotesr;
int totallotesrr;
int timer = 0;
int timecontador = 0;
int programNumber = 0;
int verficatiempollegada = 0;
int verficatiemporespuesta = 0;
int iwannadie = 0;
int xn = 7;
int quantum;
int quantumcopia;
struct Process {
    string operation;
    int number1;
    int number2;
    string result;
    string result2;
    int estimatedTime;
    int programNumber;
    int currentQueue;
    int tiempotranscurrido; // no se aplica en todos los casos
    int tiemporestante; // no se aplica en todos los casos

    int tiempobloqueado;
    int tiempobloqueado2; // esta siempre sera 8
    int tiempollegada;
    int tiempofinalizacion;
    int tiemporetorno;
    int tiemporespuesta;
    int tiempoespera;
    int tiemposervicio; // este sera igual al tiempotransucurrido o al estimatedTime
};

// Función que valida que los datos ingresados por el usuario sean números enteros
bool ValidaNumerosEnteros(char *dato){
    bool ban = true;
    int i = 0;
    if (*dato == '-' || *dato == '+') {
        i++;
    }
    while (*(dato + i) != '\0') {
        if (*(dato + i) < '0' || *(dato + i) > '9') {
            ban = false;
            break;
        }
        i++;
    }
    return ban;
}

void gotoxy(int x,int y){  
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos);  
 }  


    const int maxProcessesPerQueue = 5;
    const int maxQueues = maxProcessesPerQueue;
    queue<Process> queues[maxQueues];
    queue<Process> totalProcessesQueue[0];
    queue<Process> totalProcessesQueueCopia[0];
    queue<Process> totalProcessesQueueVacia[0];
    unordered_set<int> usedProgramNumbers;

void IWillHaveOrder(){
    int x = 1, y = 1;
    gotoxy(0,0);
    printf("%c", 201); //╔
    gotoxy(132,0);
    printf("%c", 187); //╗
    gotoxy(0,31);
    printf("%c", 200); //╚
    gotoxy(132,31);
    printf("%c", 188); //╝
    while (y<=30)
    {
        gotoxy(0,y);
        printf("%c", 186); //║
        gotoxy(132,y);
        printf("%c", 186); //║
        y++;
    }
    while (x<=131)
    {
        gotoxy(x,0);
        printf("%c", 205); //═
        gotoxy(x,31);
        printf("%c", 205); //═
        x++;
    }
    y = 1;
    int y2 = 3;
    gotoxy(16,2);
    printf("%c", 203); //╦
    gotoxy(16,31);
    printf("%c", 202); //╩
    gotoxy(33,0);
    printf("%c", 203); //╦
    gotoxy(33,31);
    printf("%c", 202); //╩
    gotoxy(79,0);
    printf("%c", 203); //╦
    gotoxy(79,31);
    printf("%c", 202); //╩
    while (y<=30)
    {
        gotoxy(33,y);
        printf("%c", 186); //║
        gotoxy(79,y);
        printf("%c", 186); //║
        y++;
    }
    while (y2<=30){
        gotoxy(16,y2);
        printf("%c", 186); //║
        y2++;
    }
    x = 1;
    gotoxy(0,2);
    printf("%c", 204); //╠
    gotoxy(23,2);
    printf("%c", 185); //╣
    while (x<=32)
    {
        gotoxy(x,2);
        printf("%c", 205); //═
        x++;
    }
    gotoxy(16,2);
    printf("%c", 203); //╦
}

void ThisIsOrder(){
    int x = 1, y = 1;
    gotoxy(0,0);
    printf("%c", 201); //╔
    gotoxy(132,0);
    printf("%c", 187); //╗
    gotoxy(0,31);
    printf("%c", 200); //╚
    gotoxy(132,31);
    printf("%c", 188); //╝
    while (y<=30)
    {
        gotoxy(0,y);
        printf("%c", 186); //║
        gotoxy(132,y);
        printf("%c", 186); //║
        y++;
    }
    while (x<=131)
    {
        gotoxy(x,0);
        printf("%c", 205); //═
        gotoxy(x,31);
        printf("%c", 205); //═
        x++;
    }
}
queue<Process> unifiedQueue;
void datosLotes(){
    char totalProcessesc[100];
    char quantumc[100];
    gotoxy(1,1);
    cout << "Ingrese el numero de procesos: ";
    cin >> totalProcessesc;
    while(!ValidaNumerosEnteros(totalProcessesc)){
        gotoxy(1,1);
        cout << "                                                 ";
        gotoxy(1,1);
        cout << "Ingrese el numero de procesos de nuevo: ";
        cin >> totalProcessesc;
    }
    totalProcesses = atoi(totalProcessesc);
    gotoxy(1,4);
    cout << "Ingrese el quantum: ";
    while(!ValidaNumerosEnteros(quantumc)){
        gotoxy(1,4);
        cout << "                                                 ";
        gotoxy(1,4);
        cout << "Ingrese el quantum de nuevo: ";
        cin >> quantumc;
    }
    quantum = atoi(quantumc);
    quantumcopia = quantum;
    int currentQueue = 0;
    for (int i = 1; i <= totalProcesses; ++i) {
        Process newProcess;
        newProcess.currentQueue = currentQueue+1;
        int operationIndex = rand() % 6;
        switch (operationIndex)
        {
        case 0:
            newProcess.operation = "+";
            break;
        case 1:
            newProcess.operation = "-";
            break;
        case 2:
            newProcess.operation = "*";
            break;
        case 3:
            newProcess.operation = "/";
            break;
        case 4:
            newProcess.operation = "residuo";
            break;
        case 5:
            newProcess.operation = "porcentaje";
            break;
        default:
            break;
        }
        int operationN1 = rand() % 101;
        int operationN2 = rand() % 101;
        newProcess.number1 = operationN1;
        newProcess.number2 = operationN2;

        if(newProcess.operation == "/"){
            while(newProcess.number2 == 0){
                int operationN2 = rand() % 101;
                newProcess.number2 = operationN2;
            }
        }
        if(newProcess.operation == "+"){
            newProcess.result = newProcess.number1 + newProcess.number2;       
        }
        else if(newProcess.operation == "-"){
            newProcess.result = to_string(newProcess.number1 - newProcess.number2);       
        }
        else if(newProcess.operation == "*"){
            newProcess.result = to_string(newProcess.number1 * newProcess.number2);       
        }
        else if(newProcess.operation == "/"){
            newProcess.result = to_string(newProcess.number1 / newProcess.number2);       
        }
        else if(newProcess.operation == "residuo"){
            newProcess.result = to_string(newProcess.number1 % newProcess.number2);       
        }
        else if(newProcess.operation == "porcentaje"){
            newProcess.result = to_string((newProcess.number1 * newProcess.number2) / 100);        
        }
        else {
            gotoxy(1,11);
            cout << "Operacion no valida" << endl;
        }
        int operationET = 6 + (rand() % 13); // Tiempo estimado de 6 a 18 segundos
        newProcess.estimatedTime = operationET;
        while(newProcess.estimatedTime == 0){
            int operationET = 6 + (rand() % 13); // Tiempo estimado de 6 a 18 segundos
            newProcess.estimatedTime = operationET;
        }

        newProcess.tiempotranscurrido = 0;
        newProcess.tiemporestante = newProcess.estimatedTime;
        
        programNumber++;
        newProcess.programNumber = programNumber;

        newProcess.tiempobloqueado = 8;
        newProcess.tiempobloqueado2 = 8;
        newProcess.tiempollegada = 0;
        newProcess.tiempofinalizacion = 0;
        newProcess.tiemporetorno = 0;
        newProcess.tiemporespuesta = 0;
        newProcess.tiempoespera = 0;
        newProcess.tiemposervicio = 0;
        newProcess.result2 = "Normal";

        usedProgramNumbers.insert(newProcess.programNumber);
        queues[currentQueue].push(newProcess);
        /* totalProcessesQueueCopia->push(newProcess); */
        if (queues[currentQueue].size() >= maxProcessesPerQueue) {
            currentQueue++;
        }
    }
    
    for (int i = 0; i < maxQueues; ++i) {
        queue<Process> copyQueue = queues[i]; // Copia la cola original
        while (!copyQueue.empty()) {
            Process process = copyQueue.front();
            unifiedQueue.push(process);
            copyQueue.pop();
        }
    }
/*     while (!unifiedQueue.empty()) {
        Process process = unifiedQueue.front();
        cout << "Proceso #" << process.programNumber << endl;
        unifiedQueue.pop();
    }
    system("pause"); */
}




void imprimirdata() {
    int procesosTotales = totalProcesses;
    int contadordeprocesosnuevos = totalProcesses;
    int contadordeprocesoslistos = 0;
    int ffy = 7;
    char pulsar = ' ';
    int a = 1;
    gotoxy(80, 13);
    cout << "I = Interrumpir";
    gotoxy(80, 15);
    cout << "E = Error";
    gotoxy(80, 17);
    cout << "P = Pausar";
    gotoxy(80, 19);
    cout << "C = Continuar";
    queue<Process> cpc = queues[0];
    queue<Process> totalProcessesQueueCopia[0];
    queue<Process> tpqc = totalProcessesQueueCopia[0];
    while(!cpc.empty()){
        Process temporal = cpc.front();
        cpc.pop();
        contadordeprocesoslistos = contadordeprocesoslistos + 1;
        contadordeprocesosnuevos = contadordeprocesosnuevos - 1;
    }
    queue<Process> totalProcessesQueue[1]; // En esta cola se almacenaran todos los datos finalizados
    queue<Process> totalProcessesQueueVacia[1];
    queue<Process> tpqv = totalProcessesQueueVacia[1];
    for (int i = 0; i < maxQueues; i++) {
        gotoxy(1,1);
        cout << "Procesos Nuevos: " << contadordeprocesosnuevos; // Modi
        int acomodainterumpir = 11;
        int ay = 7;
        int y = 7;
        if (!queues[i].empty()) {
            gotoxy(3,3);
            cout << "P Listos #" << contadordeprocesoslistos << endl; // Modi
            queue<Process> tempQueue = queues[i];  // Copia temporal de la cola
            queue<Process> bloqueados;
            gotoxy(80,50);
            while (!tempQueue.empty()) {
                // fila 1
                Process tprocess = tempQueue.front();
                tempQueue.pop();
                gotoxy(3,5);
                cout << "ID";
                gotoxy(3,y);
                cout << tprocess.programNumber;
                gotoxy(6,5);
                cout << "TME";
                gotoxy(6,y);
                cout << tprocess.estimatedTime;
                gotoxy(10,5);
                cout << "TT";
                gotoxy(10,y);
                cout << "  ";
                gotoxy(10,y);
                cout << tprocess.tiempotranscurrido;
                gotoxy(3,7);
                cout << "            ";
                y = y + 1;
                gotoxy(3,15);
                cout << "Bloqueados";
                gotoxy(3,17);
                cout << "ID";
                gotoxy(6,17);
                cout << "TB"; // tiempo bloqueado
            }
            while(!queues[i].empty()){
                int by = 19;
                
                // fila 2
                Process& process = queues[i].front();
                gotoxy(17,3);
                cout << "Ejec";
                gotoxy(17,5);
                cout << "Nn "; // nombre
                gotoxy(17,7);
                cout << "ID";
                gotoxy(17,9);
                cout << "Ope";
                gotoxy(17,11);
                cout << "TME";
                gotoxy(17,13);
                cout << "TT";
                gotoxy(17,15);
                cout << "TR";
                gotoxy(22,7);
                cout << process.programNumber;
                gotoxy(22,9);
                cout << "          ";
                gotoxy(22,9);
                cout << process.operation;
                gotoxy(22,11);
                cout << "   ";
                gotoxy(22,11);
                cout << process.estimatedTime;
                gotoxy(80,5);
                cout << "Procesos restantes";
                gotoxy(80,7);
                cout << "            ";
                gotoxy(80,7);
                cout << procesosTotales;
                while(process.estimatedTime > process.tiempotranscurrido || !bloqueados.empty()){
                    gotoxy(1,1);
                    cout << "Procesos Nuevos: " << contadordeprocesosnuevos;
                    gotoxy(3,3);
                    cout << "P Listos #" << contadordeprocesoslistos << endl;
                    gotoxy(3,15);
                    cout << "Bloqueados";
                    gotoxy(3,17);
                    cout << "ID";
                    gotoxy(6,17);
                    cout << "TB"; // tiempo bloqueado
                    queue<Process> imp = queues[i];
                    y = 7;
                    while(imp.empty()){
                        Process yanosequenombre = imp.front();
                        imp.pop();
                        gotoxy(3,5);
                        cout << "ID";
                        gotoxy(3,y);
                        cout << yanosequenombre.programNumber;
                        gotoxy(6,5);
                        cout << "TME";
                        gotoxy(6,y);
                        cout << yanosequenombre.estimatedTime;
                        gotoxy(10,5);
                        cout << "TT";
                        gotoxy(10,y);
                        cout << "  ";
                        gotoxy(10,y);
                        cout << yanosequenombre.tiempotranscurrido;
                        gotoxy(3,7);
                        cout << "            ";
                    }
                    by = 19;
                    gotoxy(22,13);
                    cout << "   ";
                    gotoxy(22,13);
                    cout << process.tiempotranscurrido;
                    gotoxy(22,15);
                    cout << "   ";
                    gotoxy(22,15);
                    cout << process.tiemporestante;
                    gotoxy(80,9);
                    cout << "Tiempo total";
                    gotoxy(80,11);
                    cout << "            ";
                    gotoxy(80,11);
                    cout << timecontador;
                    gotoxy(95,9);
                    cout << "Tiempo Quantum";
                    gotoxy(95,11);
                    cout << "            ";
                    gotoxy(95,11);
                    cout << quantum;
                    gotoxy(17,17);
                    cout << "Qm";
                    gotoxy(22,17);
                    cout << "   ";
                    gotoxy(22,17);
                    cout << quantum;
                    Sleep(1000); // Modi temporizador
                    timer = timer + 1;
                    timecontador = timecontador + 1;
                    // tiempo de finalizacion
                    process.tiempofinalizacion = timecontador;
                    // tiempo de retorno
                    process.tiemporetorno = process.tiempofinalizacion - process.tiempollegada;
                    // tiempo de respuesta                    
                    if(process.tiemporespuesta == 0){
                        process.tiemporespuesta = timecontador - process.tiempollegada - 1;
                    }
                    else
                    {
                    }
                    // tiempo de espera
                    process.tiempoespera = process.tiemporetorno - process.tiemposervicio - 1; // El -1 es para ajustar el tiempo, pues por como funciona hace un incremento antes de terminar.
                    // tiempo de servicio
                    process.tiemposervicio = process.tiemposervicio + 1; 
                    process.tiemporestante = process.tiemporestante - 1;
                    process.tiempotranscurrido = process.tiempotranscurrido + 1;
                    quantum = quantum - 1;
                    /* Sleep(1000); // Modi temporizador */
                    if(quantum == 0){
                        pulsar = 'q';
                        break;
                    }
                    Process interruptedProcess = queues[i].front(); // Obtener el proceso actual
                    if (_kbhit() && process.tiempotranscurrido != process.estimatedTime) {
                        char key = _getch();
                        if (key == 'I' || key == 'i') { // interrumpir
                            pulsar = 'i';
                            interruptedProcess.tiempotranscurrido = process.tiempotranscurrido; // Guardar el tiempo transcurrido
                            interruptedProcess.tiemporestante = process.tiemporestante; // Guardar el tiempo total
                            queues[i].pop(); // Sacar el proceso de la cola actual
                            bloqueados.push(interruptedProcess);
                            gotoxy(18,15);
                            cout << "    ";
                            timecontador = timecontador - 1;
                            // Limpiar la cola temporal
                            while (!tempQueue.empty()) {
                                tempQueue.pop();
                            }
                            // Volver a llenar la cola temporal con los procesos restantes de la cola original
                            queue<Process> originalQueue = queues[i];
                            Process tprocess = originalQueue.front();
                            y = 7;
                            while (!originalQueue.empty()) {
                                tempQueue.push(originalQueue.front());
                                gotoxy(3,5);
                                cout << "ID";
                                gotoxy(3,y);
                                cout << tprocess.programNumber;
                                gotoxy(6,5);
                                cout << "TME";
                                gotoxy(6,y);
                                cout << tprocess.estimatedTime;
                                gotoxy(10,5);
                                cout << "TT";
                                gotoxy(10,y);
                                cout << "  ";
                                gotoxy(10,y);
                                cout << tprocess.tiempotranscurrido;
                                gotoxy(3,7);
                                cout << "            ";
                                y = y + 1;
                                originalQueue.pop();
                            }
                            queue<Process> tempQueue = queues[i];  // Copia temporal de la cola
                            y = 7;
                            ay = 7;
                            int contadorded = 5;
                            while(contadorded >=0)
                            {
                                gotoxy(3,y);
                                cout << "             ";
                                y = y + 1;
                                contadorded--;
                            }
                            y = 7;
                            while (!tempQueue.empty()) {
                                // fila 1
                                Process tprocess = tempQueue.front();
                                tempQueue.pop();
                                gotoxy(3,5);
                                cout << "ID";
                                gotoxy(3,y);
                                cout << "  ";
                                gotoxy(3,y);
                                cout << tprocess.programNumber;
                                gotoxy(6,5);
                                cout << "TME";
                                gotoxy(6,y);
                                cout << "  ";
                                gotoxy(6,y);
                                cout << tprocess.estimatedTime;
                                gotoxy(10,5);
                                cout << "TT";
                                gotoxy(10,y);
                                cout << "  ";
                                gotoxy(10,y);
                                cout << tprocess.tiempotranscurrido;
                                gotoxy(3,7);
                                cout << "            ";
                                y = y + 1;
                            }
                            break;
                        } else if (key == 'P' || key == 'p') { // pausar
                            gotoxy(80,21);
                            cout << "Pausado";
                            while (true)
                            {
                                if (_kbhit()) {
                                    char key = _getch();
                                    if (key == 'C' || key == 'c') { // continuar
                                        gotoxy(80,21);
                                        cout << "        ";
                                        break;
                                    }
                                }
                            }
                        } else if (key == 'E' || key == 'e') { // error
                            pulsar = 'e';
                            timecontador = timecontador - 1;
                            break;
                        } else if(key == 'B' || key == 'b') {
                            pulsar = 'b';
                            break;
                        } else if(key == 'N' || key == 'n') {
                            pulsar = 'n';
                            break;
                        }
                    }
                    iwannadie = iwannadie + process.tiempofinalizacion;       
                    int contadorded = 5;
                    while(contadorded >=0)
                    {
                        gotoxy(3,by);
                        cout << "             ";
                        by = by + 1;
                        contadorded--;
                    }
                    by = 19;
                    if (!bloqueados.empty()) {        
                        queue<Process> tempbloq = bloqueados;
                        while (!tempbloq.empty()) {
                            Process temporal = tempbloq.front();
                            tempbloq.pop();
                            temporal.tiempobloqueado = temporal.tiempobloqueado - 1;
                            // Aquí se imprimirán los datos de cada proceso en la cola de bloqueados
                            gotoxy(3, by);
                            cout << temporal.programNumber;
                            gotoxy(6, by);
                            cout << temporal.tiempobloqueado; // tiempo bloqueado
                            by = by + 1;
                            bloqueados.pop();
                            bloqueados.push(temporal);
                            if (temporal.tiempobloqueado <= 0) {
                                temporal.tiempobloqueado = 8;
                                queues[i].push(temporal);
                                bloqueados.pop();
                                /* contadordeprocesoslistos = contadordeprocesoslistos + 1; */
                            }
                            queue<Process> tempQueue = queues[i];  // Copia temporal de la cola
                            y = 7;
                            ay = 7;
                            int contadorded = 5;
                            while(contadorded >=0)
                            {
                                gotoxy(3,y);
                                cout << "             ";
                                y = y + 1;
                                contadorded--;
                            }
                            y = 7;
                            while (!tempQueue.empty()) {
                                // fila 1
                                Process tprocess = tempQueue.front();
                                tempQueue.pop();
                                gotoxy(3,5);
                                cout << "ID";
                                gotoxy(3,y);
                                cout << "  ";
                                gotoxy(3,y);
                                cout << tprocess.programNumber;
                                gotoxy(6,5);
                                cout << "TME";
                                gotoxy(6,y);
                                cout << "  ";
                                gotoxy(6,y);
                                cout << tprocess.estimatedTime;
                                gotoxy(10,5);
                                cout << "TT";
                                gotoxy(10,y);
                                cout << "  ";
                                gotoxy(10,y);
                                cout << tprocess.tiempotranscurrido;
                                gotoxy(3,7);
                                cout << "            ";
                                y = y + 1;
                            }
                        }
                    }
                    queue<Process> tempQueue = queues[i];  // Copia temporal de la cola
                    y = 7;
                    ay = 7;
                    contadorded = 5;
                    while(contadorded >=0)
                    {
                        gotoxy(3,y);
                        cout << "             ";
                        y = y + 1;
                        contadorded--;
                    }
                    y = 7;
                    while (!tempQueue.empty()) {
                        // fila 1
                        Process tprocess = tempQueue.front();
                        tempQueue.pop();
                        gotoxy(3,5);
                        cout << "ID";
                        gotoxy(3,y);
                        cout << "  ";
                        gotoxy(3,y);
                        cout << tprocess.programNumber;
                        gotoxy(6,5);
                        cout << "TME";
                        gotoxy(6,y);
                        cout << "  ";
                        gotoxy(6,y);
                        cout << tprocess.estimatedTime;
                        gotoxy(10,5);
                        cout << "TT";
                        gotoxy(10,y);
                        cout << "  ";
                        gotoxy(10,y);
                        cout << tprocess.tiempotranscurrido;
                        gotoxy(3,7);
                        cout << "            ";
                        y = y + 1;
                    }
                    /* Sleep(1000); */
                }
                gotoxy(22,7);
                cout << "   ";
                gotoxy(22,9);
                cout << "          ";;
                gotoxy(22,11);
                cout << "   ";
                gotoxy(22,13);
                cout << "   ";
                gotoxy(22,15);
                cout << "   ";
                while(queues[i].empty()){ // mi salvación para el problema de bloqueos
                    Sleep(1000);
                    int contadorded = 5;
                    while(contadorded >=0)
                    {
                        gotoxy(3,by);
                        cout << "             ";
                        by = by + 1;
                        contadorded--;
                    }
                    by = 19;
                    if(!bloqueados.empty()){
                        pulsar = 'm';
                        queue<Process> tempbloq = bloqueados;
                        while (!tempbloq.empty()){
                            Process temporal = tempbloq.front();
                            tempbloq.pop();
                            temporal.tiempobloqueado = temporal.tiempobloqueado - 1;
                            // Aquí se imprimirán los datos de cada proceso en la cola de bloqueados
                            gotoxy(3, by);
                            cout << temporal.programNumber;
                            gotoxy(6, by);
                            cout << temporal.tiempobloqueado; // tiempo bloqueado
                            by = by + 1;
                            bloqueados.pop();
                            bloqueados.push(temporal);
                            if (temporal.tiempobloqueado <= 0) {
                                temporal.tiempobloqueado = 8;
                                queues[i].push(temporal);
                                bloqueados.pop();
                                /* contadordeprocesoslistos = contadordeprocesoslistos + 1; */
                            }
                        }
                    }         
                }
                // fila 3           
                gotoxy(34,3);
                cout << "Terminados";
                gotoxy(34,5);
                cout << "ID";
                gotoxy(38,5);
                cout << "Ope";
                gotoxy(60,5);
                cout << "Res";
                gotoxy(74,5);
                cout << "Tanda";
                gotoxy(74,6);
                cout << "Guia";
                ffy = 7;
                if(pulsar == 'e'){
                    quantum = quantumcopia;
                    contadordeprocesoslistos = contadordeprocesoslistos - 1;
                    gotoxy(3,3);
                    cout << "             ";
                    gotoxy(3,3);
                    cout << "P Listos #" << contadordeprocesoslistos << endl; // Modi
                    gotoxy(34,xn);
                    cout << "      ";
                    gotoxy(34,xn);
                    cout << process.programNumber;
                    gotoxy(38,xn);
                    cout << "         ";
                    gotoxy(38,xn);
                    cout << process.number1 << process.operation << process.number2;
                    gotoxy(60,xn);
                    cout << "      ";
                    process.result = "Error";
                    process.result2 = "Error";
                    gotoxy(60,xn);
                    cout << process.result;
                    gotoxy(66,xn);
                    cout << "      ";
                    gotoxy(74,xn);
                    cout << process.currentQueue;
                    xn = xn + 1;
                    pulsar = ' ';
                    // acomodar fila 1
                    gotoxy(3,ay);
                    cout << "       ";
                    ay = ay + 1;
                    queues[i].pop();
                    procesosTotales = procesosTotales - 1;
                    totalProcessesQueue->push(process);
                    tpqv.push(process);
                    queue<Process> tempQueue = queues[i];  // Copia temporal de la cola
                    y = 7;
                    ay = 7;
                    int contadorded = 5;
                    while(contadorded >=0)
                    {
                        gotoxy(3,y);
                        cout << "             ";
                        y = y + 1;
                        contadorded--;
                    }
                    y = 7;
                    while (!tempQueue.empty()) {
                        // fila 1
                        Process tprocess = tempQueue.front();
                        tempQueue.pop();
                        gotoxy(3,5);
                        cout << "ID";
                        gotoxy(3,y);
                        cout << "  ";
                        gotoxy(3,y);
                        cout << tprocess.programNumber;
                        gotoxy(6,5);
                        cout << "TME";
                        gotoxy(6,y);
                        cout << "  ";
                        gotoxy(6,y);
                        cout << tprocess.estimatedTime;
                        gotoxy(10,5);
                        cout << "TT";
                        gotoxy(10,y);
                        cout << "  ";
                        gotoxy(10,y);
                        cout << tprocess.tiempotranscurrido;
                        gotoxy(3,7);
                        cout << "            ";
                        y = y + 1;
                    }
                    bool flag = false;
                    int buscador = 0;
                    while (!flag){
                        buscador = buscador + 1;
                        if (i + a < maxQueues) {
                            if (!queues[i + a].empty()) {
                                Process otherqueue = queues[i + a].front(); // Obtenemos el elemento de la cola origen
                                queues[i + a].pop(); // Eliminamos el elemento de la cola origen
                                otherqueue.tiempollegada = timecontador;
                                queues[i].push(otherqueue); // Insertamos el elemento en la cola destino (queues[i])
                                contadordeprocesosnuevos = contadordeprocesosnuevos - 1;
                                gotoxy(1,1);
                                cout << "                      ";
                                gotoxy(1,1);
                                cout << "Procesos Nuevos: " << contadordeprocesosnuevos; // Modi
                                contadordeprocesoslistos = contadordeprocesoslistos + 1;
                                gotoxy(3,3);
                                cout << "             ";
                                gotoxy(3,3);
                                cout << "P Listos #" << contadordeprocesoslistos << endl; // Modi
                                flag = true;
                            } else {
                                a = a + 1; // Incrementamos 'a' si la cola origen está vacía
                            }
                        }
                        if(buscador == 5){
                            flag = true;
                        }
                    }
                }
                else if (pulsar == 'q'){
                    // copia de queues[i]
                    queue<Process> tempQueue = queues[i];  // Copia temporal de la cola
                    queues[i].pop();
                    // Volver a formar
                    queues[i].push(tempQueue.front());
                    quantum = quantumcopia;
                }
                else if (pulsar == 'i')
                {
                    quantum = quantumcopia;
                    /* contadordeprocesoslistos = contadordeprocesoslistos - 1; */
                    if(process.estimatedTime == process.tiempotranscurrido){
                        gotoxy(34,ffy);
                        cout << "      ";
                        gotoxy(34,ffy);
                        cout << process.programNumber;
                        gotoxy(38,ffy);
                        cout << "         ";
                        gotoxy(38,ffy);
                        cout << process.number1 << process.operation << process.number2;
                        gotoxy(60,ffy);
                        cout << "      ";
                        gotoxy(60,ffy);
                        cout << process.result;
                        gotoxy(66,ffy);
                        cout << "      ";
                        gotoxy(74,ffy);
                        cout << process.currentQueue;
                        ffy = ffy + 1;
                        // acomodar fila 1
                        gotoxy(3,ay);
                        cout << "       ";
                        ay = ay + 1;
                        queues[i].pop();
                        procesosTotales = procesosTotales - 1;
                        gotoxy(3,acomodainterumpir);
                        cout << "            ";
                        acomodainterumpir = acomodainterumpir - 1;
                        totalProcessesQueue->push(process);
                        tpqv.push(process);
                    }
                    queue<Process> tempQueue = queues[i];  // Copia temporal de la cola
                    y = 7;
                    ay = 7;
                    int contadorded = 5;
                    while(contadorded >=0)
                    {
                        gotoxy(3,y);
                        cout << "             ";
                        y = y + 1;
                        contadorded--;
                    }
                    y = 7;
                    while (!tempQueue.empty()) {
                        // fila 1
                        Process tprocess = tempQueue.front();
                        tempQueue.pop();
                        gotoxy(3,5);
                        cout << "ID";
                        gotoxy(3,y);
                        cout << "  ";
                        gotoxy(3,y);
                        cout << tprocess.programNumber;
                        gotoxy(6,5);
                        cout << "TME";
                        gotoxy(6,y);
                        cout << "  ";
                        gotoxy(6,y);
                        cout << tprocess.estimatedTime;
                        gotoxy(10,5);
                        cout << "TT";
                        gotoxy(10,y);
                        cout << "  ";
                        gotoxy(10,y);
                        cout << tprocess.tiempotranscurrido;
                        gotoxy(3,7);
                        cout << "            ";
                        y = y + 1;
                    }
                }
                else if (pulsar == 'm'){
                    contadordeprocesoslistos = contadordeprocesoslistos - 1;
                }
                else if (pulsar == 'b'){

                    system("cls");
/*                     int i = 0;
                    while(!queues[i].empty()){
                        queues[i].pop();
                        // Imprime el tme de queues[i]
                        cout << queues[i].front().tiemposervicio << endl;
                    }
                    system("pause"); */
                    ThisIsOrder();
                    // imrpimir datos finales
                    gotoxy(3,1);
                    cout << "Procesos Activos";
                    gotoxy(3,2);
                    cout << "ID"; // ID
                    gotoxy(7,2);
                    cout << "TL"; // tiempo llegada
                    gotoxy(11,2);
                    cout << "TF"; // tiempo finalizacion
                    gotoxy(15,2);
                    cout << "TR"; // tiempo retorno
                    gotoxy(19,2);
                    cout << "TRa"; // tiempo respuesta
                    gotoxy(25,2);
                    cout << "TE"; // tiempo espera
                    gotoxy(31,2);
                    cout << "TS"; // tiempo servicio
                    gotoxy(37,2);
                    cout << "TME"; // tiempo estimado
                    gotoxy(43,2);
                    cout << "Estado"; // Tipo de finalización (Normal o Error)
                    /* gotoxy(58,2);
                    cout << "Operacion"; */
                    gotoxy(58,2);
                    cout << "TT";
                    ffy = 3;
                    // Impresión TDD
                    queue<Process> copiadebloqueados = bloqueados;
                    queue<Process> tddimpresionblanco = unifiedQueue;
/*                     while(!tddimpresionblanco.empty()){
                        Process processtddb = tddimpresionblanco.front();
                        tddimpresionblanco.pop();
                        gotoxy(3,ffy);
                        cout << processtddb.programNumber;
                        gotoxy(7,ffy);
                        cout << processtddb.tiempollegada;
                        gotoxy(11,ffy);
                        cout << "NA";
                        gotoxy(15,ffy);
                        cout << "NA";
                        gotoxy(19,ffy);
                        cout << processtddb.tiemporespuesta;
                        gotoxy(25,ffy);
                        cout << timecontador - processtddb.tiempollegada;
                        gotoxy(31,ffy);
                        cout << processtddb.tiemposervicio; // Al momento
                        gotoxy(37,ffy);
                        cout << processtddb.estimatedTime;
                        gotoxy(43,ffy);
                        cout << "NA";
                        gotoxy(54,ffy);
                        cout << "NA";
                        gotoxy(58,ffy);
                        cout << processtddb.operation;
                        gotoxy(90,ffy);
                        cout << processtddb.result;
                        gotoxy(90,ffy);
                        cout << "               ";
                        ffy = ffy + 1;
                    } */
                    
                    for (int i = 0; i < maxQueues; i++)
                    {
                        queue<Process> salvacion = queues[i];
                        while(!salvacion.empty()){
                            Process salvacionproceso = salvacion.front();
                            salvacion.pop();
                            gotoxy(3,ffy);
                            cout << salvacionproceso.programNumber;
                            gotoxy(7,ffy);
                            cout << salvacionproceso.tiempollegada;
                            gotoxy(11,ffy);
                            cout << "NA";
                            gotoxy(15,ffy);
                            cout << "NA";
                            gotoxy(19,ffy);
                            cout << salvacionproceso.tiemporespuesta;
                            gotoxy(25,ffy);
                            cout << timecontador - salvacionproceso.tiempollegada;
                            gotoxy(31,ffy);
                            cout << salvacionproceso.tiemposervicio; // Al momento
                            gotoxy(37,ffy);
                            cout << salvacionproceso.estimatedTime;
                            gotoxy(43,ffy);
                            cout << "NA";
                            /* gotoxy(58,ffy);
                            cout << salvacionproceso.number1 << salvacionproceso.operation << salvacionproceso.number2; */
                            gotoxy(58,ffy);
                            cout << salvacionproceso.tiempotranscurrido;
                            ffy = ffy + 1;
                        }
                    }
                    ffy = 18;
                    queue<Process> p2 = totalProcessesQueue[0];
                    gotoxy(3,16);
                    cout << "Procesos Terminados";
                    gotoxy(3,17);
                    cout << "ID"; // ID
                    gotoxy(7,17);
                    cout << "TL"; // tiempo llegada
                    gotoxy(11,17);
                    cout << "TF"; // tiempo finalizacion
                    gotoxy(15,17);
                    cout << "TR"; // tiempo retorno
                    gotoxy(19,17);
                    cout << "TRa"; // tiempo respuesta
                    gotoxy(25,17);
                    cout << "TE"; // tiempo espera
                    gotoxy(31,17);
                    cout << "TS"; // tiempo servicio
                    gotoxy(37,17);
                    cout << "TME"; // tiempo estimado
                    gotoxy(43,17);
                    cout << "Estado"; // Tipo de finalización (Normal o Error)
                    /* gotoxy(58,17);
                    cout << "Operación"; // operación */
                    gotoxy(58,17);
                    cout << "Resultado";
                    gotoxy(72,17);
                    cout << "TT";
                    while(!p2.empty()){
                        Process pp = p2.front();
                        p2.pop();
                        gotoxy(3,ffy);
                        cout << pp.programNumber;
                        gotoxy(7,ffy);
                        cout << pp.tiempollegada;
                        gotoxy(11,ffy);
                        cout << pp.tiempofinalizacion;
                        gotoxy(15,ffy);
                        cout << pp.tiemporetorno;
                        gotoxy(19,ffy);
                        cout << pp.tiemporespuesta;
                        gotoxy(25,ffy);
                        cout << process.tiempoespera;
                        gotoxy(31,ffy);
                        cout << pp.tiemposervicio; // Al momento
                        gotoxy(37,ffy);
                        cout << pp.estimatedTime;
                        gotoxy(43,ffy);
                        cout << pp.result2;
                        /* gotoxy(58,ffy);
                        cout << pp.number1 << pp.operation << pp.number2; */
                        gotoxy(58,ffy);
                        cout << pp.result;
                        gotoxy(72,ffy);
                        cout << pp.tiempotranscurrido;
                        ffy = ffy + 1;
                    }
                    ffy = 3;
                    gotoxy(66,1);
                    cout << "Procesos Bloqueados";
                    gotoxy(66,2);
                    cout << "ID";
                    gotoxy(70,2);
                    cout << "TL";
                    gotoxy(74,2);
                    cout << "TB";
                    gotoxy(78,2);
                    cout << "TE";
                    gotoxy(82,2);
                    cout << "TRa";
                    gotoxy(86,2);
                    cout << "TME";
                    gotoxy(90,2);
                    cout << "TT";
                    while(!copiadebloqueados.empty()){
                        Process bbb = copiadebloqueados.front();
                        copiadebloqueados.pop();
                        gotoxy(66,ffy);
                        cout << bbb.programNumber;
                        gotoxy(70,ffy);
                        cout << bbb.tiempollegada;
                        gotoxy(74,ffy);
                        cout << bbb.tiempobloqueado;
                        gotoxy(78,ffy);
                        cout << bbb.tiempoespera;
                        gotoxy(82,ffy);
                        cout << bbb.tiemporespuesta;
                        gotoxy(86,ffy);
                        cout << bbb.estimatedTime;
                        gotoxy(90,ffy);
                        cout << bbb.tiempotranscurrido;
                        ffy = ffy + 1;
                    }
                    ffy = 7;
                    
/*                     queue<Process> copiatotalProcessesQueue = tpqv;
                    while(!copiatotalProcessesQueue.empty()){
                        Process processxd = copiatotalProcessesQueue.front();
                        copiatotalProcessesQueue.pop();
                        gotoxy(3,ffy);
                        cout << processxd.programNumber;
                        gotoxy(7,ffy);
                        cout << processxd.tiempollegada;
                        gotoxy(11,ffy);
                        cout << "    ";
                        gotoxy(11,ffy);
                        cout << processxd.tiempofinalizacion;
                        gotoxy(15,ffy);
                        cout << "    ";
                        gotoxy(15,ffy);
                        cout << processxd.tiemporetorno;
                        gotoxy(19,ffy);
                        cout << "    ";
                        gotoxy(19,ffy);
                        cout << processxd.tiemporespuesta;
                        gotoxy(25,ffy);
                        cout << "    ";
                        gotoxy(25,ffy); 
                        cout << processxd.tiempoespera;
                        gotoxy(31,ffy);
                        cout << "    ";
                        gotoxy(31,ffy);
                        cout << processxd.tiemposervicio;
                        gotoxy(37,ffy);
                        cout << "    ";
                        gotoxy(37,ffy);
                        cout << processxd.estimatedTime;
                        gotoxy(43,ffy);
                        cout << "       ";
                        gotoxy(43,ffy);
                        cout << processxd.result2;
                        gotoxy(54,ffy);
                        cout << "    ";
                        gotoxy(54,ffy);
                        cout << processxd.tiempobloqueado - processxd.tiempobloqueado2;
                        gotoxy(58,ffy);
                        cout << "         ";
                        gotoxy(58,ffy);
                        cout << processxd.number1 << processxd.operation << processxd.number2;
                        gotoxy(90,ffy);
                        cout << "               ";
                        gotoxy(90,ffy);
                        cout << processxd.result;
                        gotoxy(107,ffy);
                        cout << "               ";
                        gotoxy(107,ffy);
                        cout << 8 - processxd.tiempobloqueado2;
                        ffy = ffy + 1;
                    }
                    ffy = 7;
                    // Puede salvar
                    while(!copiadebloqueados.empty()){
                        Process bbb = copiadebloqueados.front();
                        copiadebloqueados.pop();
                        gotoxy(130,ffy);
                        cout << bbb.programNumber;
                        gotoxy(134,ffy);
                        cout << bbb.tiempobloqueado;
                        ffy = ffy + 1;
                    } */
/*                     queue<Process> copiadecopia = tpqc;
                    while(!copiadecopia.empty()){
                        Process processzzz = copiadecopia.front();
                        copiadecopia.pop();
                        gotoxy(3,ffy);
                        cout << processzzz.programNumber;
                        gotoxy(7,ffy);
                        cout << processzzz.tiempollegada;
                        gotoxy(11,ffy);
                        cout << "NA";
                        gotoxy(15,ffy);
                        cout << "NA";
                        gotoxy(19,ffy);
                        cout << processzzz.tiemporespuesta;
                        gotoxy(25,ffy); 
                        cout << timecontador;
                        gotoxy(31,ffy);
                        cout << processzzz.tiemposervicio; // Al momento
                        gotoxy(37,ffy);
                        cout << processzzz.estimatedTime;
                        gotoxy(43,ffy);
                        cout << "NA";
                        gotoxy(54,ffy);
                        cout << "NA";
                        gotoxy(58,ffy);
                        cout << processzzz.operation;
                        gotoxy(90,ffy);
                        cout << processzzz.result;
                        gotoxy(90,ffy);
                        cout << "               ";
                        ffy = ffy + 1;
                    }
                    ffy = 7;
                    queue<Process> copiatotalProcessesQueue = tpqv;
                    while(!copiatotalProcessesQueue.empty()){
                        Process processxd = copiatotalProcessesQueue.front();
                        copiatotalProcessesQueue.pop();
                        gotoxy(3,ffy);
                        cout << processxd.programNumber;
                        gotoxy(7,ffy);
                        cout << processxd.tiempollegada;
                        gotoxy(11,ffy);
                        cout << "    ";
                        gotoxy(11,ffy);
                        cout << processxd.tiempofinalizacion;
                        gotoxy(15,ffy);
                        cout << "    ";
                        gotoxy(15,ffy);
                        cout << processxd.tiemporetorno;
                        gotoxy(19,ffy);
                        cout << "    ";
                        gotoxy(19,ffy);
                        cout << processxd.tiemporespuesta;
                        gotoxy(25,ffy);
                        cout << "    ";
                        gotoxy(25,ffy); 
                        cout << processxd.tiempoespera;
                        gotoxy(31,ffy);
                        cout << "    ";
                        gotoxy(31,ffy);
                        cout << processxd.tiemposervicio;
                        gotoxy(37,ffy);
                        cout << "    ";
                        gotoxy(37,ffy);
                        cout << processxd.estimatedTime;
                        gotoxy(43,ffy);
                        cout << "       ";
                        gotoxy(43,ffy);
                        cout << processxd.result2;
                        gotoxy(54,ffy);
                        cout << "    ";
                        gotoxy(54,ffy);
                        cout << processxd.tiempobloqueado - processxd.tiempobloqueado2;
                        gotoxy(58,ffy);
                        cout << "         ";
                        gotoxy(58,ffy);
                        cout << processxd.number1 << processxd.operation << processxd.number2;
                        gotoxy(90,ffy);
                        cout << "               ";
                        gotoxy(90,ffy);
                        cout << processxd.result;
                        ffy = ffy + 1;
                    } */
                    while (true)
                    {
                        if (_kbhit()) {
                            char key = _getch();
                            if (key == 'C' || key == 'c') { // continuar
                                system("cls");
                                IWillHaveOrder();
                                break;
                            }
                        }
                    }
                }
                else if(pulsar == 'n'){
                    int currentQueue = 0;
                    Process newProcess;
                    newProcess.currentQueue = currentQueue+1;
                    int operationIndex = rand() % 6;
                    switch (operationIndex)
                    {
                    case 0:
                        newProcess.operation = "+";
                        break;
                    case 1:
                        newProcess.operation = "-";
                        break;
                    case 2:
                        newProcess.operation = "*";
                        break;
                    case 3:
                        newProcess.operation = "/";
                        break;
                    case 4:
                        newProcess.operation = "residuo";
                        break;
                    case 5:
                        newProcess.operation = "porcentaje";
                        break;
                    default:
                        break;
                    }
                    int operationN1 = rand() % 101;
                    int operationN2 = rand() % 101;
                    newProcess.number1 = operationN1;
                    newProcess.number2 = operationN2;
                    if(newProcess.operation == "/"){
                        while(newProcess.number2 == 0){
                            int operationN2 = rand() % 101;
                            newProcess.number2 = operationN2;
                        }
                    }
                    if(newProcess.operation == "+"){
                        newProcess.result = newProcess.number1 + newProcess.number2;       
                    }
                    else if(newProcess.operation == "-"){
                        newProcess.result = to_string(newProcess.number1 - newProcess.number2);       
                    }
                    else if(newProcess.operation == "*"){
                        newProcess.result = to_string(newProcess.number1 * newProcess.number2);       
                    }
                    else if(newProcess.operation == "/"){
                        newProcess.result = to_string(newProcess.number1 / newProcess.number2);       
                    }
                    else if(newProcess.operation == "residuo"){
                        newProcess.result = to_string(newProcess.number1 % newProcess.number2);       
                    }
                    else if(newProcess.operation == "porcentaje"){
                        newProcess.result = to_string((newProcess.number1 * newProcess.number2) / 100);        
                    }
                    else {
                        gotoxy(1,11);
                        cout << "Operacion no valida" << endl;
                    }
                    int operationET = 6 + (rand() % 13); // Tiempo estimado de 6 a 18 segundos
                    newProcess.estimatedTime = operationET;
                    while(newProcess.estimatedTime == 0){
                        int operationET = 6 + (rand() % 13); // Tiempo estimado de 6 a 18 segundos
                        newProcess.estimatedTime = operationET;
                    }
                    newProcess.tiempotranscurrido = 0;
                    newProcess.tiemporestante = newProcess.estimatedTime;
                    programNumber++;
                    newProcess.programNumber = programNumber;
                    newProcess.tiempobloqueado = 8;
                    newProcess.tiempollegada = timecontador;
                    newProcess.tiempofinalizacion = 0;
                    newProcess.tiemporetorno = 0;
                    newProcess.tiemporespuesta = 0;
                    newProcess.tiempoespera = 0;
                    newProcess.tiemposervicio = 0;
                    newProcess.result2 = "Normal";
                    usedProgramNumbers.insert(newProcess.programNumber);
                    /* totalProcessesQueue->push(newProcess); */
                    /* tpqc.push(newProcess); */
                    unifiedQueue.push(newProcess);
                   /*  queue<Process> tpqc = totalProcessesQueueCopia[0]; */
                    bool inserted = false;
                    currentQueue = 0;
                    while (!inserted) {
                        int cq = queues[currentQueue].size();
                        if (cq < 5) {
                            if(currentQueue == 0 && contadordeprocesoslistos < 5){
                                contadordeprocesoslistos = contadordeprocesoslistos + 1;
                                gotoxy(3,3);
                                cout << "             ";
                                gotoxy(3,3);
                                cout << "P Listos #" << contadordeprocesoslistos << endl; // Modi
                                queues[currentQueue].push(newProcess);
                            }
                            else{
                                contadordeprocesosnuevos = contadordeprocesosnuevos + 1;
                                gotoxy(1,1);
                                cout << "                      ";
                                gotoxy(1,1);
                                cout << "Procesos Nuevos: " << contadordeprocesosnuevos; // Modi
                                queues[currentQueue+1].push(newProcess);
                            }
                            inserted = true;
                        } else {
                            currentQueue++;
                        }
                    }
                }
                else {
                    ffy = 7;
                    contadordeprocesoslistos = contadordeprocesoslistos - 1;
                    gotoxy(3,3);
                    cout << "             ";
                    gotoxy(3,3);
                    cout << "P Listos #" << contadordeprocesoslistos << endl; // Modi
                    gotoxy(34,xn);
                    cout << "      ";
                    gotoxy(34,xn);
                    cout << process.programNumber;
                    gotoxy(38,xn);
                    cout << "         ";
                    gotoxy(38,xn);
                    cout << process.number1 << process.operation << process.number2;
                    gotoxy(60,xn);
                    cout << "      ";
                    gotoxy(60,xn);
                    cout << process.result;
                    gotoxy(66,xn);
                    cout << "      ";
                    gotoxy(74,ffy);
                    cout << process.currentQueue;
                    xn = xn + 1;
                    // acomodar fila 1
                    gotoxy(3,ay);
                    cout << "       ";
                    ay = ay + 1;
                    process.tiemposervicio = process.estimatedTime;
                    queues[i].pop();
                    procesosTotales = procesosTotales - 1;
                    totalProcessesQueue->push(process);
                    tpqv.push(process);
                    bool flag = false;
                    int buscador = 0;
                    while (!flag){
                        buscador = buscador + 1;
                        if (i + a < maxQueues) {
                            if (!queues[i + a].empty()) {
                                Process otherqueue = queues[i + a].front(); // Obtenemos el elemento de la cola origen
                                queues[i + a].pop(); // Eliminamos el elemento de la cola origen
                                otherqueue.tiempollegada = timecontador;
                                queues[i].push(otherqueue); // Insertamos el elemento en la cola destino (queues[i])
                                contadordeprocesosnuevos = contadordeprocesosnuevos - 1;
                                gotoxy(1,1);
                                cout << "                      ";
                                gotoxy(1,1);
                                cout << "Procesos Nuevos: " << contadordeprocesosnuevos; // Modi
                                contadordeprocesoslistos = contadordeprocesoslistos + 1;
                                gotoxy(3,3);
                                cout << "             ";
                                gotoxy(3,3);
                                cout << "P Listos #" << contadordeprocesoslistos << endl; // Modi
                                flag = true;
                            } else {
                                a = a + 1; // Incrementamos 'a' si la cola origen está vacía
                            }
                        }
                        if(buscador == 5){
                            flag = true;
                        }
                    }
                }
                pulsar = ' ';
                queue<Process> tempQueue = queues[i];  // Copia temporal de la cola
                y = 7;
                ay = 7;
                int contadorded = 5;
                while(contadorded >=0)
                {
                    gotoxy(3,y);
                    cout << "             ";
                    y = y + 1;
                    contadorded--;
                }
                y = 7;
                while (!tempQueue.empty()) {
                    // fila 1
                    Process tprocess = tempQueue.front();
                    tempQueue.pop();
                    gotoxy(3,5);
                    cout << "ID";
                    gotoxy(3,y);
                    cout << "  ";
                    gotoxy(3,y);
                    cout << tprocess.programNumber;
                    gotoxy(6,5);
                    cout << "TME";
                    gotoxy(6,y);
                    cout << "  ";
                    gotoxy(6,y);
                    cout << tprocess.estimatedTime;
                    gotoxy(10,5);
                    cout << "TT";
                    gotoxy(10,y);
                    cout << "  ";
                    gotoxy(10,y);
                    cout << tprocess.tiempotranscurrido;
                    gotoxy(3,7);
                    cout << "            ";
                    y = y + 1;
                }
            }
            int contador = 0;
            int by = 9;
            while (contador <= 5){
                gotoxy(3,by);
                cout << "       ";
                by = by + 1;
                contador++;
            }
        }
    }
    gotoxy(22,7);
    cout << "   ";
    gotoxy(22,9);
    cout << "          ";;
    gotoxy(22,11);
    cout << "   ";
    gotoxy(22,13);
    cout << "   ";
    gotoxy(22,15);
    cout << "   ";
    procesosTotales = 0;
    gotoxy(80,7);
    cout << "            ";
    gotoxy(80,30);
    system("pause");
    system("cls");
    ThisIsOrder();
    // imrpimir datos finales
    gotoxy(3,3);
    cout << "Procesos terminados";
    gotoxy(3,5);
    cout << "ID"; // ID
    gotoxy(7,5);
    cout << "TL"; // tiempo llegada
    gotoxy(11,5);
    cout << "TF"; // tiempo finalizacion
    gotoxy(15,5);
    cout << "TR"; // tiempo retorno
    gotoxy(19,5);
    cout << "TRa"; // tiempo respuesta
    gotoxy(25,5);
    cout << "TE"; // tiempo espera
    gotoxy(31,5);
    cout << "TS"; // tiempo servicio
    gotoxy(37,5);
    cout << "TME"; // tiempo estimado
    gotoxy(43,5);
    cout << "Estado"; // Tipo de finalización (Normal o Error)
    ffy = 7;
    while(!totalProcessesQueue->empty()){
        Process process = totalProcessesQueue->front();
        totalProcessesQueue->pop();
        gotoxy(3,ffy);
        cout << process.programNumber;
        gotoxy(7,ffy);
        cout << process.tiempollegada;
        gotoxy(11,ffy);
        cout << process.tiempofinalizacion;
        gotoxy(15,ffy);
        cout << process.tiemporetorno;
        gotoxy(19,ffy);
        cout << process.tiemporespuesta;
        gotoxy(25,ffy); 
        cout << process.tiempoespera;
        gotoxy(31,ffy);
        cout << process.tiemposervicio;
        gotoxy(37,ffy);
        cout << process.estimatedTime;
        gotoxy(43,ffy);
        cout << process.result2;
        ffy = ffy + 1;
    }
}


int main() {
    HWND consoleWindow = GetConsoleWindow();
    RECT desktop;
    GetWindowRect(GetDesktopWindow(), &desktop);
    MoveWindow(consoleWindow, desktop.left, desktop.top, desktop.right, desktop.bottom, TRUE);
    system("pause");
    ThisIsOrder();
    datosLotes();
    system("cls");
    IWillHaveOrder();
    imprimirdata();
    gotoxy(80,30);
    system("pause");
    system("cls");
    return 0;
}
