#include <chrono>
#include <cstdio>
#include <iostream>
#include <thread>
#include <ctime>

#include "clockcalendar.h"
#include "examples/OLED/utils.h"

struct ConfiguracaoRelogio
{
    int mes;
    int dia;
    int ano;
    int hora;
    int minuto;
    int segundo;
    int periodo;
};

class InterfaceRelogio
{
public:
    virtual ~InterfaceRelogio() {}

    virtual ConfiguracaoRelogio lerConfiguracao() = 0;
    virtual void mostrarMensagemInicial() = 0;
    virtual void mostrarRelogio(const ClockCalendar& relogio) = 0;
    virtual void esperarUmSegundo() = 0;
};

class InterfaceConsole : public InterfaceRelogio
{
public:
    ConfiguracaoRelogio lerConfiguracao()
    {
        ConfiguracaoRelogio configuracao;

        std::cout << "Digite a data:" << std::endl;
        std::cout << "Mes: ";
        std::cin >> configuracao.mes;
        std::cout << "Dia: ";
        std::cin >> configuracao.dia;
        std::cout << "Ano: ";
        std::cin >> configuracao.ano;

        std::cout << std::endl << "Digite a hora:" << std::endl;
        std::cout << "Hora, no formato de 12 horas: ";
        std::cin >> configuracao.hora;
        std::cout << "Minuto: ";
        std::cin >> configuracao.minuto;
        std::cout << "Segundo: ";
        std::cin >> configuracao.segundo;
        std::cout << "Digite 0 para AM ou 1 para PM: ";
        std::cin >> configuracao.periodo;

        return configuracao;
    }

    void mostrarMensagemInicial()
    {
        std::cout << std::endl << "Relogio iniciado:" << std::endl;
    }

    void mostrarRelogio(const ClockCalendar& relogio)
    {
        std::cout << "\r" << relogio << std::flush;
    }

    void esperarUmSegundo()
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
};

class InterfaceAtlys : public InterfaceRelogio
{
private:
    ConfiguracaoRelogio configuracaoInicial;

    void mostrarTexto(char texto[], int linha)
    {
        printGeneric(texto, linha);
    }

public:
    InterfaceAtlys()
        : configuracaoInicial{9, 16, 2026, 12, 0, 0, 0}
    {
    }

    ConfiguracaoRelogio lerConfiguracao()
    {
        return configuracaoInicial;
    }

    void mostrarMensagemInicial()
    {
        char mensagem[] = "Relogio iniciado";

        oledInit();
        oledClear();
        mostrarTexto(mensagem, 0);
    }

    void mostrarRelogio(const ClockCalendar& relogio)
    {
        int mes;
        int dia;
        int ano;
        int hora;
        int minuto;
        int segundo;
        int periodo;
        char data[24];
        char horario[24];

        relogio.readCalendar(mes, dia, ano);
        relogio.readClock(hora, minuto, segundo, periodo);

        std::snprintf(data, sizeof(data), "%02d/%02d/%04d", dia, mes, ano);
        std::snprintf(
            horario,
            sizeof(horario),
            "%02d:%02d:%02d %s",
            hora,
            minuto,
            segundo,
            periodo ? "PM" : "AM"
        );

        mostrarTexto(data, 1);
        mostrarTexto(horario, 2);
    }

    void esperarUmSegundo()
    {
        clock_t inicio = clock();

        while ((clock() - inicio) < CLOCKS_PER_SEC)
        {
        }
    }
};

class AplicacaoRelogio
{
private:
    InterfaceRelogio& interface;

public:
    AplicacaoRelogio(InterfaceRelogio& interfaceAplicacao)
        : interface(interfaceAplicacao)
    {
    }

    void executar()
    {
        ConfiguracaoRelogio configuracao = interface.lerConfiguracao();

        ClockCalendar relogio(
            configuracao.mes,
            configuracao.dia,
            configuracao.ano,
            configuracao.hora,
            configuracao.minuto,
            configuracao.segundo,
            configuracao.periodo
        );

        interface.mostrarMensagemInicial();

        while (true)
        {
            interface.mostrarRelogio(relogio);
            interface.esperarUmSegundo();
            relogio.advance();
        }
    }
};

int main()
{
#if OLED
    InterfaceAtlys interfaceAtlys;
    InterfaceRelogio& interface = interfaceAtlys;
#else
    InterfaceConsole interfaceConsole;
    InterfaceRelogio& interface = interfaceConsole;
#endif

    AplicacaoRelogio aplicacao(interface);
    aplicacao.executar();

    return 0;
}
