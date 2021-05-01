/* 
 * By: Gabriel Valentim
 * Repositório: https://github.com/xValentim/Como_medir_temperatura
 * Descrição: Como medir temperatura utilizando Arduino, LM35 e NTC10K
 * OBS.: Abra o link para checar o circuito desse programa
 * 
 * 
 */

#include <math.h><br>  
// Definindo variáveis iniciais
float temperatura = 0;

// Portas analogicas dos sensores
int lm35 = 0; // Conecte o pino do meio do LM35 no A0
int ntc1 = 2; // Conecte o sinal de tensão (fio roxo) à porta A2
int ntc2 = 4; // Conecte o sinal de tensão (fio roxo) à porta A4

// A média será feita tomando 100 valores de amostras
float numero_de_amostras = 100;

// Valores dos sensores (Vamos receber dentro do registrador de 10 bits do arduino, ou seja, de 0 a 1023)
// É necessário realizar um cálculo de proporção, onde 0 é 0V e 1023 é 5V (regra de 3)
int valor_do_sensor = 0;

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  delay(2000); //INTERVALO DE 2 SEGUNDO ANTES DE INICIAR
  // Primeira linha com os valores das colunas do arquivo
  Serial.print("Tempo");
  Serial.print(",");
  Serial.print("Tlm35 medio");
  Serial.print(",");
  Serial.print("T_lm35");
  // Temporizador para fornecer dados da coluna de tempo (em milisegundos)
  float tempo = millis();
}

void loop() {
  // Funcionam como as listas no Python
  float *lista_de_temperaturas = malloc(numero_de_amostras * sizeof(float)); // alocacao dinamica de temperaturas

  // Necessário caso o arduino não possua memória disponível para alocar valores
  if (lista_de_temperaturas == NULL){
    Serial.println("ERROR");
    Serial.println("Reset...");
    delay(1000);
    asm volatile ("  jmp 0");
  }

  // Loop para coletar as amostras de tensão
  for(int i = 0; i < numero_de_amostras; i++){
    
    valor_do_sensor = analogRead(lm35);
    // a funcao get_temperatura_lm35 recebe o valor do sensor lido pelo lm35
    temperatura = get_temperatura_lm35(valor_do_sensor);
    lista_de_temperaturas[i] = temperatura;
    
    delay(10);
  }

  // Faz a media das temperaturas do LM35
  float media_das_temperaturas = media(lista_de_temperaturas, numero_de_amostras);

  int ultimo_indice = numero_de_amostras - 1;
  float tempo = millis();

  // Printa no monitor serial os valores de temperatura
  // acesse o monitor serial:
  // FERRAMENTAS >>> MONITOR SERIAL
  // ou CTRL + SHIFT + M
  Serial.print(tempo / 1000);
  Serial.print(",");
  Serial.print(media_das_temperaturas);
  Serial.print(",");
  Serial.println(lista_de_temperaturas[ultimo_indice]);
  free(lista_de_temperaturas); // Libera a memória usada na alocação dinâmica   

}
