#include "clockcalendar.h"

#include <iomanip>

using namespace std;

ClockCalendar::ClockCalendar(
    int mt, int d, int y,
    int h, int m, int s, int pm
)
    : Clock(h, m, s, pm),
      Calendar(mt, d, y)
{
}

void ClockCalendar::advance()
{
    int wasPm = is_pm;

    Clock::advance();

    int isPm = is_pm;

    // Quando o horário passa de PM para AM,
    // significa que começou um novo dia.
    if (wasPm && !isPm)
    {
        Calendar::advance();
    }
}

Clock::Clock(int h, int m, int s, int pm)
{
    hr = h;
    min = m;
    sec = s;
    is_pm = pm;
}

void Clock::setClock(int h, int m, int s, int pm)
{
    hr = h;
    min = m;
    sec = s;
    is_pm = pm;
}

void Clock::readClock(int& h, int& m, int& s, int& pm)
{
    h = hr;
    m = min;
    s = sec;
    pm = is_pm;
}

void Clock::advance()
{
    sec++;

    if (sec == 60)
    {
        sec = 0;
        min++;
    }

    if (min == 60)
    {
        min = 0;
        hr++;
    }

    // Relógio no formato de 12 horas.
    if (hr == 13)
    {
        hr = 1;
    }

    // A troca de período ocorre ao chegar em 12:00:00.
    if (hr == 12 && min == 0 && sec == 0)
    {
        is_pm = !is_pm;
    }
}

Calendar::Calendar(int m, int d, int y)
{
    mo = m;
    day = d;
    yr = y;
}

void Calendar::setCalendar(int m, int d, int y)
{
    mo = m;
    day = d;
    yr = y;
}

void Calendar::readCalendar(int& m, int& d, int& y)
{
    m = mo;
    d = day;
    y = yr;
}

void Calendar::advance()
{
    int diasNoMes;

    switch (mo)
    {
        case 2:
            if ((yr % 400 == 0) ||
                (yr % 4 == 0 && yr % 100 != 0))
            {
                diasNoMes = 29;
            }
            else
            {
                diasNoMes = 28;
            }
            break;

        case 4:
        case 6:
        case 9:
        case 11:
            diasNoMes = 30;
            break;

        default:
            diasNoMes = 31;
            break;
    }

    day++;

    if (day > diasNoMes)
    {
        day = 1;
        mo++;
    }

    if (mo > 12)
    {
        mo = 1;
        yr++;
    }
}

ostream& operator<<(
    ostream& os,
    const Clock& horaAtual
)
{
    os << setfill('0') << setw(2) << horaAtual.hr << ":" << setw(2) << horaAtual.min << ":" << setw(2) << horaAtual.sec << " ";

    if (horaAtual.is_pm)
    {
        os << "PM";
    }
    else
    {
        os << "AM";
    }

    os << setfill(' ');

    return os;
}

ostream& operator<<(
    ostream& os,
    const Calendar& calendarioAtual
)
{
    os << setfill('0') << setw(2) << calendarioAtual.day << "/" << setw(2) << calendarioAtual.mo << "/" << setw(4) << calendarioAtual.yr << setfill(' ');

    return os;
}

ostream& operator<<(
    ostream& os,
    const ClockCalendar& relogio
)
{
    os << static_cast<const Calendar&>(relogio) << " " << static_cast<const Clock&>(relogio);

    return os;
}
