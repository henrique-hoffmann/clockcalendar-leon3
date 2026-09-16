#include <iostream>
#include <thread>
#include <chrono>

#include "clockcalendar.h"

using namespace std;

int main()
{
    int mes;
    int dia;
    int ano;

    int hora;
    int minuto;
    int segundo;
    int pm;

    cout << "Digite a data:" << endl;
    cout << "Mes: ";
    cin >> mes;

    cout << "Dia: ";
    cin >> dia;

    cout << "Ano: ";
    cin >> ano;

    cout << endl;
    cout << "Digite a hora:" << endl;
    cout << "Hora, no formato de 12 horas: ";
    cin >> hora;

    cout << "Minuto: ";
    cin >> minuto;

    cout << "Segundo: ";
    cin >> segundo;

    cout << "Digite 0 para AM ou 1 para PM: ";
    cin >> pm;

    ClockCalendar relogio(
        mes,
        dia,
        ano,
        hora,
        minuto,
        segundo,
        pm
    );

    cout << endl;
    cout << "Relogio iniciado:" << endl;

    while (true)
    {
        cout << "\r" << relogio << flush;

        this_thread::sleep_for(chrono::seconds(1));

        relogio.advance();
    }

    return 0;
}
