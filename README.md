# ESTRUTURA DO REPOSITÓRIO:

```
44xx-PPM
├── PPM_lib
│   ├── PPM_lib.h
│   ├── PPM_lib.c
│   └── ramp_vector.h
├── imagens_do_readme
├── PWM_irqFunctions_ponteiros.c
├── PWM_irqFunctions_varglobal.c
├── create_ramp.cpp
├── LICENSE.txt
├── .gitignore
└── README.md
```
- No projeto, há a pasta das libs, que, na .h, há as definições de tipos, defines structs. Essa, deve ser incluida na pasta inc. A .c, que deve ser incluida na src, tem encapsulamento set get para a estrutura de variáveis do PPM, que permite a manipulação dos endereços sem o uso de variáveis globais. A implementação das funções de interrupção com essas libs está em PWM_irqFunctions_ponteiros.c
  
- Caso queira uma abordagem mais simples, PWM_irqFunctions_varglobal.c tem as mesma aplicações, mas usando só variáveis globais para se comunicar com as funções de interrupção.
  
- create_ramp.cpp é utilizado para criar um arquivo .h com os valores para a rampa do ppm, variando de valores de arr de 1 a 180, representando os graus. É só inserir o ARR escolhido e rodar o scrpt, então, o arquivo ramp_vector.h será criado automaticamente. A partir daí, é só jogar pra pasta inc e dar include no código que desejar usar (por padrão, ele já está incluso na PPM_lib.h).

- Esse repositório é regido pela licensa MIT, por tanto, é livre para uso de qualquer um.
  
# PPM - Pulse Position Modulation:
A Modulação por Posição de Pulso (PPM) é uma técnica de modulação de sinal onde a posição dos pulsos em uma sequência é variada de acordo com a amplitude do sinal de modulação. Em outras palavras, em vez de alterar a largura ou a amplitude dos pulsos, como em outras técnicas de modulação, a PPM ajusta o tempo de ocorrência de cada pulso. Este método é utilizado em diversas aplicações de comunicação e controle, proporcionando uma maneira eficiente de transmitir informações de forma robusta contra interferências e ruídos.
###
### Aplicação da PPM
A PPM é amplamente utilizada em sistemas de comunicação sem fio, sistemas de controle remoto, e em aplicações industriais para controle de potência. Uma das aplicações práticas e relevantes é no controle de SCRs (Silicon Controlled Rectifiers) para ajustar a tensão média aplicada a uma carga.
###
## Controle de angulo de Disparo de SCR usando PPM
###
### O que é um SCR?
- Um SCR (Silicon Controlled Rectifier) é um dispositivo semicondutor que atua como um interruptor controlado. Ele permite o fluxo de corrente elétrica quando uma tensão de disparo é aplicada ao seu terminal de gate. Uma vez disparado, ele continua a conduzir até que a corrente através dele caia abaixo de um certo valor mínimo (corrente de manutenção).
###
### Alteração do angulo de Disparo
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

## Dimensionamento:

![Equação](https://latex.codecogs.com/png.image?\dpi{110}\bg{black}&space;R1=\frac{12-Vled}{10*10{^{-3}}}\Rightarrow\frac{12-1.6v}{10*10{^{-3}}}=1K\Omega&space;) 

![Equação](https://latex.codecogs.com/png.image?\dpi{110}\bg{black}R2=\frac{Vcc}{10*10{^{-3}}}\Rightarrow\frac{3.3v}{10*10{^{-3}}}=300K\Omega&space;) 

##
- O pulso do detector de zero tem tamanho de 200 us, dado obtido por nós ao medirmos a
largura do pulso com os cursores do osciloscópio. Como visto na imagem abaixo:

##

<p align="center">
  <img src="https://github.com/RafaelVVolkmer/44xx-PPM/blob/master/imagens_do_readme/frequencia_do_pulso.png" alt="FREQUENCIA_DO_PULSO">
</p>

##

## Dimensionamento:

![Equação](https://latex.codecogs.com/png.image?\dpi{110}\bg{black}F=\frac{1}{T}\Rightarrow\frac{1}{200us}\Rightarrow&space;5000hz\Rightarrow&space;5Khz) 

##

- Além disso, temos a medição de sua tensão de pico em nível alto, também realizada no
osciloscópio, que está em volta de, aproximadamente, 3,20V(DC). O STM32F446RE, que é o
microcontrolador usado no projeto, opera em uma frequência de 180 MHz, com um clock interno,
configurado por nós, de 84 MHz, e aguenta, em suas entradas, até 5V(DC), sendo o uso típico em
3v3(DC), por t#nto, esse pulso é capaz de ser lido de forma eficaz pelo microcontrolador

##

# SINAL FINAL NO OSCILOSCÓPIO (DETECTOR DE ZERO)

<p align="center">
  <img src="https://github.com/RafaelVVolkmer/44xx-PPM/blob/master/imagens_do_readme/Sinal%20no%20osciloscópio.png" alt="SINAL_OSCILOSCOPIO">
</p>

##

- Como podemos ver, o sinal faz a intersecção direitinho com o zero da senoide que pegamos da rede, passando pelo transformador monofasico 12v.

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

# SINAL SIMULADO COM EVENTOS DO TIMER:

<p align="center">
  <img src="https://github.com/RafaelVVolkmer/44xx-PPM/blob/master/imagens_do_readme/PPM_sinal.jpg" alt="PPM_SIGNAL">
</p>

##

Com o microcontrolador STM32F446RE, usamos um canal de um timer, no modo output
compare (OC) para fazer nosso PPM. Definimos sua frequência para 120hz, com um período de
8,3ms, que é metade do período total de uma senóide, de 16,6 ms e 60hz, pois cada sinal atuará em um
ciclo. O timer utilizado foi o TIM3, que tem um trigger externo em seu ETR1, no PD2, que é ativado
pela detecção de zero e está no modo one-pulse. Resumidamente, o sinal do detector irá ativar a
contagem do timer, que irá estourar após 8,3ms, e parará de contar, sendo reativado pelo próximo
pulso. Durante esse período até o timer estourar e iniciar uma nova contagem, variamos o valor de seu
CCR até o máximo valor de ARR, que, no caso, é 18k. Assim, podemos dizer que, por exemplo, ele
sobe a primeira vez em 17.500 e desce em 17.400, formando a primeira posição. Depois, ele pode
subir novamente em 16.700 e descer em 16.300, variando, com suas bordas bem definidas. Esse é o
algoritmo do nosso PPM, como mostrado na imagem abaixo:

## Para os cálculos do TIM 3:

<p align="center">
  <img src="https://github.com/RafaelVVolkmer/44xx-PPM/blob/master/imagens_do_readme/CALCULOS_TIM3.png" alt="PPM_SIGNAL">
</p>

##

Para a estruturação do código, decidimos usar um vetor de 180 posições, que contém as bordas
de subida do nosso CCR. A borda de descida será sempre BORDA DE SUBIDA + LARGURA DO
PULSO e, assim, atualizaremos esses 2 valores a cada estouro de um outro timer, o TIM2, que irá
variar sua frequência de acordo com o tempo de rampa que escolhermos na parte de especificações,
através da alteração do ARR através de um cálculo, por regra de três, que a própria MCU irá realizar.
Devido às quedas de tensão dos SCRs, os pulsos em 171 - 180 iam para a meia onda da
próxima senóide, por tanto, tivemos que diminuir o número de elementos para 170. Isso não alterou a
tensão na carga conforme a varredura do vetor, continuou de forma eficaz.

##

## Para o cálculo de ARR do TIM 2:

<p align="center">
  <img src="https://github.com/RafaelVVolkmer/44xx-PPM/blob/master/imagens_do_readme/CALCULOS_TIM2.png" alt="PPM_SIGNAL">
</p>

##

# IMPORTANTE (CÓDIGO):

```c
htim3.Instance->CCMR1 |= TIM_CCMR1_OC1CE;  // DÁ CLEAR NO OC DE FORMA A NÃO ATRAPALHAR OS PULSOS
```
O código htim3.Instance->CCMR1 |= TIM_CCMR1_OC1CE é uma instrução em C para manipular um registrador de um timer em um microcontrolador STM32. Vamos detalhar o que cada parte desse código faz:

Contexto
No contexto de microcontroladores STM32, htim3 é uma instância de um manipulador de timer (TIM_HandleTypeDef), e Instance é um ponteiro para a estrutura de registros do hardware do timer específico (neste caso, o Timer 3). Os registros do timer controlam várias configurações e estados do timer.

## Estrutura do Código

### htim3.Instance:

htim3 é uma variável do tipo TIM_HandleTypeDef, que é uma estrutura definida pela biblioteca HAL (Hardware Abstraction Layer) da STMicroelectronics.
Instance é um membro dessa estrutura que aponta para a base dos registros do periférico Timer 3. Essa base é do tipo TIM_TypeDef, que é uma estrutura que mapeia todos os registros do timer.

### ->CCMR1:

CCMR1 é o "Capture/Compare Mode Register 1" do timer. Este registro controla os modos de captura/comparação para os canais 1 e 2 do timer.
|= TIM_CCMR1_OC1CE:

### TIM_CCMR1_OC1CE 
é uma constante definida na biblioteca HAL que representa o bit "Output Compare 1 Clear Enable". Configurar esse bit ativa a funcionalidade de limpeza automática do canal de saída 1.

## Propósito

O propósito dessa linha de código é configurar o Timer 3 para que a função de limpeza automática seja ativada no canal 1 de comparação de saída. Isso pode ser usado em aplicações onde você precisa que a saída de comparação de um canal seja automaticamente redefinida sob certas condições, sem necessidade de intervenção adicional do software.

### Explicação Detalhada do Registrador

- CCMR1 (Capture/Compare Mode Register 1): Controla os modos de captura/comparação para os canais 1 e 2 do timer.
  
- TIM_CCMR1_OC1CE (Output Compare 1 Clear Enable): Quando este bit está definido, ele ativa a função de limpeza automática da saída do canal 

###
