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
###
- Eficiência: Controlando a tensão média diretamente, a PPM pode ser utilizada em sistemas de controle de potência com alta eficiência.
###
- Imunidade a Ruído: A modulação por posição de pulso é menos suscetível a interferências de ruído, tornando-a uma escolha robusta para aplicações industriais.
###

# ALGORITIMO DO PPM:

## Timer na Função Output Compare:

###
Os timers do STM32F441 oferecem várias funcionalidades avançadas, incluindo a função de Output Compare (OC). Essa função é usada para gerar pulsos ou PWM (Pulse Width Modulation), bem como para medir a duração de eventos. A seguir, uma explicação detalhada sobre como essa função opera com os registros relevantes: ARR, CCR, PSC e a frequência de clock.
###

## Componentes Principais

### ARR (Auto-Reload Register):

- O ARR define o valor máximo que o contador do timer pode atingir antes de reiniciar.
O timer conta de 0 até o valor de ARR, momento em que ele gera um evento de atualização e reinicia a contagem.
O valor de ARR determina a frequência do timer e a resolução do PWM.

##

### CCR (Capture/Compare Register):

- O CCR é usado para armazenar o valor de comparação ou captura.
No modo Output Compare, o valor do CCR é comparado com o valor do contador.
Quando o valor do contador iguala o valor do CCR, uma ação definida é realizada (por exemplo, a saída do canal é alterada).

##

### PSC (Prescaler)

- O PSC divide a frequência de clock do timer para diminuir a frequência do contador.
O valor do PSC define o fator de divisão do clock. Por exemplo, um valor de PSC de 7 dividirá a frequência do clock por 8.
Isso permite ajustar a frequência do timer de acordo com a aplicação.
Frequência de Clock:

##

### Frequência de Clock

- A frequência de clock do timer é derivada do clock do sistema, que pode ser ajustado usando o PLL e outros divisores.
Por exemplo, se o clock do sistema for 180 MHz e o PSC estiver configurado para 9, a frequência do timer será 20 MHz.
Configuração da Função Output Compare
Para configurar a função Output Compare, é necessário ajustar os registros ARR, CCR, PSC e configurar o timer para o modo desejado. Aqui está um exemplo de como esses registros interagem:

# Exemplo de Configuração
- Clock do sistema: 180 MHz
##
- Prescaler (PSC): 179
##
- Auto-Reload Register (ARR): 9999
##
- Capture/Compare Register (CCR): 5000
##
# Passos:
### Configuração do PSC:
- Se PSC = 179, o clock do timer será dividido por 180.
###
- Frequência do timer = 180 MHz / (PSC + 1) = 1 MHz.
##
### Configuração do ARR:
- Se ARR = 9999, o timer contará de 0 até 9999 antes de reiniciar.
###
- Período do timer = ARR + 1 = 10000 ciclos.
###
- Frequência do timer = 1 MHz / 10000 = 100 Hz.
##
### Configuração do CCR:
- Se CCR = 5000, a comparação ocorrerá quando o contador alcançar 5000.
##
Isso pode ser usado para gerar um pulso ou alterar a saída a cada metade do período (50% do ciclo de trabalho para PWM).

##

# DETECTOR DE ZERO:
<p align="center">
  <img src="https://github.com/RafaelVVolkmer/44xx-PPM/blob/master/imagens_do_readme/dectector_de_zero.png" alt="DETECTOR_DE_ZERO">
</p>

##

O detector de zero é responsável por nos dar uma informação quando a senóide da rede entrar
no próximo ciclo, de negativo para positivo ou positivo para negativo. Quando sua tensão for 0v e seu
gráfico estiver intersectando o eixo X do plano cartesiano, haverá um pulso em nível lógico 1, com
uma tensão de pico diferente de 0, que irá para o microcontrolador, para sincronizar o nosso PPM com
a rede através de uma ETR — sinal externo que ativará nosso periférico de temporização.
Para a montagem do detector de zero, foram usados dois Opto-Acopladores 4N25, com leds e
transistores internos, cada um responsável por ativar em determinado ciclo, comutando no VCC de
3v3 e nos trazendo a informação que precisamos para a aplicação. Esse circuito também pode ser
usado como detector de ciclo, informando em qual deles a senóide está no momento.

<p align="center">
  <img src="https://github.com/RafaelVVolkmer/44xx-PPM/blob/master/imagens_do_readme/PPM_sinal.jpg" alt="PPM_SIGNAL">
</p>


<p align="center">
  <img src="https://github.com/RafaelVVolkmer/44xx-PPM/blob/master/imagens_do_readme/frequencia_do_pulso.png" alt="FREQUENCIA_DO_PULSO">
</p>
<p align="center">
  <img src="https://github.com/RafaelVVolkmer/44xx-PPM/blob/master/imagens_do_readme/Sinal%20no%20osciloscópio.png" alt="SINAL_OSCILOSCOPIO">
</p>


  ###
