#include <iostream>
#include <vector>

using namespace std;

int NEW_PIECES_PER_DAY = 100;
float NEW_PIECES_TIME = 1440;
float BREAK_INTERVAL = 210; //Cantidad de horas que descansa
float BREAK_TIME = 60;
float MEDIA_FRESADO = 5;
float MEDIA_TALADRADO = 4;

vector<float> piezas;

void agregarNuevasPiezas(int numPiezas, float tiempoLlegada){
    for(int n=0; n<numPiezas; ++n) {
        piezas.push_back(tiempoLlegada);
    }
}



int main()
{
    float contTiempoPorPieza = 0;
    float contPiezasInventario = 0;

    int numPiezas = 0;
    int tiempo = 0;
    bool rest = false;
    float fresadoTime = 0;
    float taladradoTime = 0;
    float remainTnewPieces = 0;
    float remainBreakInterval = BREAK_INTERVAL;
    float breakTime = BREAK_TIME;
    int jornada = 0; //Cada trabajador tiene 2 jornadas
    int totalPiezas = 0;
    

    while(tiempo < 2880)
    {
        tiempo++;
        contPiezasInventario += numPiezas;
        if(remainTnewPieces == 0)   //Cada que pase un día, se agragará una nueva cantidad de piezas
        {
            numPiezas += NEW_PIECES_PER_DAY; 
            remainTnewPieces = NEW_PIECES_TIME;
            agregarNuevasPiezas(NEW_PIECES_PER_DAY, tiempo);
        }
        remainTnewPieces--;
        if(!rest)
        {
            remainBreakInterval--;
            if(remainBreakInterval == 0)
            {
                jornada++;
                if(jornada % 2 == 1){
                    rest = true;
                } 
                remainBreakInterval = BREAK_INTERVAL;
                
            }
            
            if(numPiezas > 0)
            {
                    if(fresadoTime > 0)
                {
                    fresadoTime--;
                }
                else if(taladradoTime > 0)
                {
                    taladradoTime--;
                }

                if((fresadoTime <= 0) && (taladradoTime <= 0))
                {
                    contTiempoPorPieza += tiempo - piezas[piezas.size() -1];
                    piezas.pop_back();
                    numPiezas--;
                    totalPiezas++;
                    fresadoTime = 5;
                    taladradoTime = 4;
                }   
            }
        }
        else
        {
            breakTime--;    
            if(breakTime == 0)
            {
                rest = false;
                breakTime = BREAK_TIME;
            }
        }
        if(tiempo % 60 == 0){
            cout << "Minuto: " << tiempo << " - Piezas: " << numPiezas << endl;
        }
    }
    cout << "Cantidad total de piezas que se producen: " << totalPiezas << endl;
    cout << "Promedio que tiene que eseperar una pieza en el almacén:" << contTiempoPorPieza / totalPiezas << " minutos" << endl;
    cout << "Cantidad promedio de piezas en inventario:" << contPiezasInventario/ 2880 << " engranajes" << endl;

    cout << tiempo << endl;

    return 0;
}
