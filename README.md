# Clock, Calendar e ClockCalendar em duas plataformas

## Objetivo

Reutilizar a logica de data e hora em um computador convencional e na plataforma Atlys/LEON3, mantendo os detalhes de cada plataforma fora das classes de dominio.

## Estrutura atual

- `clockcalendar.h` e `clockcalendar.cpp`: implementam `Clock`, `Calendar` e `ClockCalendar`. Essas classes armazenam e avancam a data e a hora.
- `main.cpp`: versao original, com entrada, saida, temporizacao e regra de execucao no mesmo arquivo.
- `new-main.cpp`: versao experimental com separacao entre aplicacao e interface.
- `Exemplos de programas para o LEON3 na Atlys/`: referencias para a futura integracao com OLED e GPIO.

## Abordagem do `new-main.cpp`

O novo ponto de entrada possui tres responsabilidades separadas:

1. `ClockCalendarInterface` define o contrato que a aplicacao precisa da plataforma:
   - ler a configuracao inicial;
   - mostrar o estado atual;
   - esperar um segundo.
2. `ConsoleInterface` implementa esse contrato usando `cin`, `cout`, `chrono` e `thread`.
3. `ClockCalendarApplication` executa o fluxo da aplicacao e usa somente o contrato da interface. Ela nao conhece console, OLED, LEDs ou botoes.

O objeto `ClockCalendar` continua responsavel pela regra de avancar segundos, minutos, horas, periodo AM/PM e calendario. Assim, a mesma aplicacao pode receber outra implementacao de `ClockCalendarInterface` sem alterar essa logica.

## Proxima implementacao para a Atlys

A proxima interface pode ser uma classe como `AtlysInterface`, implementando o mesmo contrato. Ela podera:

- obter os valores iniciais por chaves e botoes;
- mostrar a data e a hora no OLED;
- usar um temporizador ou uma rotina de atraso da plataforma para `waitOneSecond()`;
- controlar LEDs como indicacao de estado, se necessario.

Os includes de `Oled.h`, os enderecos de GPIO e demais dependencias do LEON3 devem ficar somente nessa implementacao. O `clockcalendar.cpp` e o controlador da aplicacao nao devem incluir codigo especifico da placa.

## Compilacao no computador

Com um compilador C++11 ou mais recente:

```text
g++ -std=c++11 clockcalendar.cpp new-main.cpp -o clockcalendar
```

A execucao continua intencionalmente ate ser interrompida pelo usuario, como na versao original.

## Estrategia de testes

Antes da placa, testar a logica de `ClockCalendar` em pontos de transicao:

- `11:59:59 AM` para `12:00:00 PM`;
- `11:59:59 PM` para `12:00:00 AM`, verificando a troca do dia;
- ultimo dia de um mes;
- fevereiro em ano bissexto e nao bissexto;
- `31/12` para `01/01` do ano seguinte.

Uma etapa posterior pode extrair a interface para um arquivo proprio e criar um adaptador de teste que substitua a espera de um segundo por uma operacao imediata. Isso permite testar o fluxo sem depender de tempo real ou hardware.

## Diagrama conceitual

```text
+---------------------------+
| ClockCalendarApplication  |
+-------------+-------------+
              | usa
              v
+---------------------------+
| ClockCalendarInterface    |<------------------+
+-------------+-------------+                   |
              |                                |
              v                                |
+---------------------------+       +----------+----------+
| ClockCalendar             |       | ConsoleInterface    |
| (Clock + Calendar)        |       | AtlysInterface      |
+---------------------------+       +---------------------+
```

`ClockCalendar` e as regras de data/hora sao reutilizaveis. As classes de interface sao substituiveis e concentram as diferencas entre computador e Atlys.
