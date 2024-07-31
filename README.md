# PPM - Pulse Position Modulation:
A Modulação por Posição de Pulso (PPM) é uma técnica de modulação de sinal onde a posição dos pulsos em uma sequência é variada de acordo com a amplitude do sinal de modulação. Em outras palavras, em vez de alterar a largura ou a amplitude dos pulsos, como em outras técnicas de modulação, a PPM ajusta o tempo de ocorrência de cada pulso. Este método é utilizado em diversas aplicações de comunicação e controle, proporcionando uma maneira eficiente de transmitir informações de forma robusta contra interferências e ruídos.
###
### Aplicação da PPM
A PPM é amplamente utilizada em sistemas de comunicação sem fio, sistemas de controle remoto, e em aplicações industriais para controle de potência. Uma das aplicações práticas e relevantes é no controle de SCRs (Silicon Controlled Rectifiers) para ajustar a tensão média aplicada a uma carga.
###
## Controle de Ângulo de Disparo de SCR usando PPM
###
### O que é um SCR?
- Um SCR (Silicon Controlled Rectifier) é um dispositivo semicondutor que atua como um interruptor controlado. Ele permite o fluxo de corrente elétrica quando uma tensão de disparo é aplicada ao seu terminal de gate. Uma vez disparado, ele continua a conduzir até que a corrente através dele caia abaixo de um certo valor mínimo (corrente de manutenção).
###
### Alteração do Ângulo de Disparo
- O ângulo de disparo de um SCR é o ponto no ciclo de uma forma de onda AC em que o SCR é ativado. Alterando o ângulo de disparo, é possível controlar a quantidade de tempo que o SCR permanece conduzindo durante cada ciclo da onda AC. Isso, por sua vez, controla a quantidade de potência entregue à carga.
###
### Controle de Tensão Média
-  Na PPM, um sinal de modulação (que pode ser um sinal de controle, como uma tensão de referência) determina a posição dos pulsos. Alterando o ângulo de disparo através da PPM, é possível ajustar a tensão média aplicada à carga. Um ângulo de disparo menor resulta em mais tempo de condução e maior tensão média, enquanto um ângulo de disparo maior resulta em menos tempo de condução e menor tensão média.
###
### Geração de Pulsos: 
- Os pulsos são gerados de tal forma que suas posições (tempos de ocorrência) correspondam ao ângulo de disparo desejado do SCR. Quanto maior o ângulo de disparo, mais tarde no ciclo de AC o SCR será ativado, resultando em menos tempo de condução e, portanto, menor tensão média na carga.
###
### Disparo do SCR: 
- Quando o pulso é aplicado ao gate do SCR no momento apropriado (determinado pela PPM), o SCR é disparado. Este pulso controla exatamente quando o SCR começa a conduzir.
  
# 
<p align="center">
  <img src="https://github.com/RafaelVVolkmer/44xx-PPM/blob/master/imagens_do_readme/onda_ppm.png" alt="PPM_WAVW">
</p>

#

###
## Vantagens do Uso da PPM para Controle de SCR:
###
- Precisão: A PPM permite um controle preciso do ângulo de disparo, proporcionando uma maneira eficaz de ajustar a tensão média na carga.
- Eficiência: Controlando a tensão média diretamente, a PPM pode ser utilizada em sistemas de controle de potência com alta eficiência.
- Imunidade a Ruído: A modulação por posição de pulso é menos suscetível a interferências de ruído, tornando-a uma escolha robusta para aplicações industriais.
###
<p align="center">
  <img src="https://github.com/RafaelVVolkmer/44xx-PPM/blob/master/imagens_do_readme/PPM_sinal.jpg" alt="PPM_SIGNAL">
</p>
<p align="center">
  <img src="https://github.com/RafaelVVolkmer/44xx-PPM/blob/master/imagens_do_readme/dectector_de_zero.png" alt="DETECTOR_DE_ZERO">
</p>
<p align="center">
  <img src="https://github.com/RafaelVVolkmer/44xx-PPM/blob/master/imagens_do_readme/frequencia_do_pulso.png" alt="FREQUENCIA_DO_PULSO">
</p>
<p align="center">
  <img src="https://github.com/RafaelVVolkmer/44xx-PPM/blob/master/imagens_do_readme/Sinal%20no%20osciloscópio.png" alt="SINAL_OSCILOSCOPIO">
</p>


  ###
