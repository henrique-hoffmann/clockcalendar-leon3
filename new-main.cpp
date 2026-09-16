#include <chrono>
#include <iostream>
#include <thread>

#include "clockcalendar.h"

struct ClockCalendarConfiguration
{
    int month;
    int day;
    int year;
    int hour;
    int minute;
    int second;
    int pm;
};

class ClockCalendarInterface
{
public:
    virtual ~ClockCalendarInterface() {}

    virtual ClockCalendarConfiguration readConfiguration() = 0;
    virtual void showStartedMessage() = 0;
    virtual void showClock(const ClockCalendar& clockCalendar) = 0;
    virtual void waitOneSecond() = 0;
};

class ConsoleInterface : public ClockCalendarInterface
{
public:
    ClockCalendarConfiguration readConfiguration()
    {
        ClockCalendarConfiguration configuration;

        std::cout << "Digite a data:" << std::endl;
        std::cout << "Mes: ";
        std::cin >> configuration.month;
        std::cout << "Dia: ";
        std::cin >> configuration.day;
        std::cout << "Ano: ";
        std::cin >> configuration.year;

        std::cout << std::endl << "Digite a hora:" << std::endl;
        std::cout << "Hora, no formato de 12 horas: ";
        std::cin >> configuration.hour;
        std::cout << "Minuto: ";
        std::cin >> configuration.minute;
        std::cout << "Segundo: ";
        std::cin >> configuration.second;
        std::cout << "Digite 0 para AM ou 1 para PM: ";
        std::cin >> configuration.pm;

        return configuration;
    }

    void showStartedMessage()
    {
        std::cout << std::endl << "Relogio iniciado:" << std::endl;
    }

    void showClock(const ClockCalendar& clockCalendar)
    {
        std::cout << "\r" << clockCalendar << std::flush;
    }

    void waitOneSecond()
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
};

class ClockCalendarApplication
{
private:
    ClockCalendarInterface& interface;

public:
    ClockCalendarApplication(ClockCalendarInterface& applicationInterface)
        : interface(applicationInterface)
    {
    }

    void run()
    {
        ClockCalendarConfiguration configuration = interface.readConfiguration();

        ClockCalendar clockCalendar(
            configuration.month,
            configuration.day,
            configuration.year,
            configuration.hour,
            configuration.minute,
            configuration.second,
            configuration.pm
        );

        interface.showStartedMessage();

        while (true)
        {
            interface.showClock(clockCalendar);
            interface.waitOneSecond();
            clockCalendar.advance();
        }
    }
};

int main()
{
    ConsoleInterface consoleInterface;
    ClockCalendarApplication application(consoleInterface);
    application.run();

    return 0;
}
