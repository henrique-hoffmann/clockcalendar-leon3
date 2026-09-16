// Para dicas sobre a funcao asctime, ver:
// http://www.cplusplus.com/reference/ctime/asctime/
#include <iostream>
#include <time.h>

int gasta_tempo (int n) {
  int i,j;
  int freq=n-1;
  for (i=0; i<=n; ++i) {
     std::cout << "i = " << i << std::endl;
     for (j=0;j< 2;++j);
  }
	    
	    
  return freq;
}

int main(int c, char** v){
  int conta, anos;
  struct tm * timeinfo;
  int segundos = 0;
  time_t timer;
  clock_t inicio, fim;
  std::cout << "Calculando..." << std::endl;
  inicio = clock();
  conta = gasta_tempo(999);
  fim = clock();
  // segundos = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
  segundos = (fim - inicio) / CLOCKS_PER_SEC;
  std::cout << "Foram necessarios " << segundos << " segundos para executar a funcao gasta_tempo()." << std::endl << std::endl;
  time(&timer);
  timeinfo = localtime(&timer);
  //segundos = difftime(timer,mktime(&y2k));
  std::cout << "Data/hora do kit Atlys: " << asctime(timeinfo) << std::endl;
  std::cout << "Fim..." << std::endl;
  return 1;
}

