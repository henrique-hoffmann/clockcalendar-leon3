#ifndef CLOCKCALENDAR_H
#define CLOCKCALENDAR_H

#include <iostream>

class Clock
{
protected:
    int hr, min, sec, is_pm;

public:
    Clock(int h, int m, int s, int pm);

    void setClock(int h, int m, int s, int pm);
    void readClock(int& h, int& m, int& s, int& pm);
    void advance();

    friend std::ostream& operator<<(std::ostream& os, const Clock& horaAtual);
};

class Calendar
{
protected:
    int mo, day, yr;

public:
    Calendar(int m, int d, int y);

    void setCalendar(int m, int d, int y);
    void readCalendar(int& m, int& d, int& y);
    void advance();

    friend std::ostream& operator<<(std::ostream& os, const Calendar& calendarioAtual);
};

class ClockCalendar : public Clock, public Calendar
{
public:
    ClockCalendar(
        int mt, int d, int y,
        int h, int m, int s, int pm
    );

    void advance();

    friend std::ostream& operator<<(std::ostream& os, const ClockCalendar& relogio);
};

#endif
