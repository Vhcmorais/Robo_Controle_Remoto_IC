// Adicionando biblioteca Dabble
include <Dabble.h>

// Definição dos pinos digitais e analógicos
const int IN1 = 3;
const int IN2 = 5;
const int IN3 = 9;
const int IN4 = 10;

// Definição de valores de variáveis
const int velocidadeMin = 160;
const int velocidadeMax = 230;
int velocidadeAtual = velocidadeMin;
const int velocidadeCurva = 140;

// Definição de função para o funcionamento dos motores (forward (para frente) e backward (para trás))
void motorWrite(int m1_forward, int m1_backward, int m2_forward, int m2_backward) {
  analogWrite(IN1, m1_forward);
  analogWrite(IN2, m1_backward);
  analogWrite(IN3, m2_forward);
  analogWrite(IN4, m2_backward);
}

// Definição da função Stop, para os motores serem desacionados
void stop() {
  motorWrite(0, 0, 0, 0);
}

// Definindo o setup
void setup() {
  Dabble.begin(9600, 6, 7); // Dabble identifica e faz o SerialSettings para o módulo bluetooth HC-05

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  stop();
}

// Definindo o loop - comportamento do robô através dos controles de Dabble
void loop() {
  Dabble.processInput();

// Função para o "turbo", botão quadrado do gamepad
  if (GamePad.isSquarePressed()) velocidadeAtual = velocidadeMax;
  else velocidadeAtual = velocidadeMin;

// Funções para movimentação do robô pelos botões do gamepad
  if (GamePad.isUpPressed()) motorWrite(velocidadeAtual, 0, velocidadeAtual, 0);
  else if (GamePad.isDownPressed()) motorWrite(0, velocidadeAtual, 0, velocidadeAtual);
  else if (GamePad.isLeftPressed()) motorWrite(0, velocidadeCurva, velocidadeCurva, 0);
  else if (GamePad.isRightPressed()) motorWrite(velocidadeCurva, 0, 0, velocidadeCurva);
  else stop();

  delay(10);
}