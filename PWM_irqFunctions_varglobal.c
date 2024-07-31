/**
 *  @brief   Este módulo fornece um exemplo de implementação das funções de callback que regem o PPM (Pulse Position Modulation).
 *           As funções de callback são configuradas para responder a interrupções de comparação de saída e de estouro de período
 *           dos timers configurados no Cube IDE.
 *           Este exemplo mostra como incluir e tratar essas funções no ambiente do Cube IDE, garantindo a manipulação adequada
 *           dos parâmetros PPM, como `borda`, `pulso` e `angulo_iterador`.
 *           Para que este exemplo funcione corretamente, é essencial que o IOC seja configurado adequadamente e que os
 *           registradores necessários sejam inicializados na função `main`.
 *
 *  @autor   Rafael V. Volkmer
 */

/* *********************************
 * DEFINIÇÃO DE ESTRUTURAS PÚBLICAS *
 * *********************************/

/**
 * @def N_BORDAS
 * @brief Define o número de bordas utilizadas no PPM.
 */
#define N_BORDAS 2

/**
 * @def PULSO_INICIAL_CCR
 * @brief Define o valor inicial do pulso CCR.
 */
#define PULSO_INICIAL_CCR 17400

/**
 * @def LARGURA_PULSO_CCR
 * @brief Define a largura do pulso CCR.
 */
#define LARGURA_PULSO_CCR 540

/**
 * @brief Enumeração que define os tipos de borda (subida e descida).
 */
typedef enum {SUBIDA = 0, DESCIDA} Borda_t;

/* *********************************
 * DEFINIÇÃO DE VARIÁVEIS GLOBAIS *
 * *********************************/

/**
 * @brief Variável estática que armazena o estado atual da borda.
 */
static Borda_t Borda = SUBIDA;

/**
 * @brief Array estático que armazena os valores dos pulsos para as bordas de subida e descida.
 */
static uint16_t Pulso[N_BORDAS] = {PULSO_INICIAL_CCR, (PULSO_INICIAL_CCR + LARGURA_PULSO_CCR)};

/**
 * @brief Variável estática usada para iterar pelos valores do pulso.
 */
static uint16_t i;

/**
 * @brief Variável estática que armazena o valor do ângulo.
 */
static uint16_t angulo;

/**
 * @brief  Callback de Interrupção de Comparação de Saída do Timer
 *
 * @details Esta função é chamada quando uma interrupção de comparação de saída ocorre no Timer 3, Canal 1.
 *          A interrupção é gatilhada quando o valor do contador do timer atinge o valor do registro de comparação.
 *          A função alterna a borda (de subida para descida ou vice-versa) e atualiza o valor de comparação para a próxima borda.
 *
 * @param   htim [in] : Ponteiro para a estrutura TIM_HandleTypeDef que contém a configuração do timer.
 */
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
	UNUSED(htim);

	// Verifica se a interrupção é do Timer 3, Canal 1
	if ((htim->Instance == TIM3) && (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1))
	{
		// Alterna a borda (de subida para descida ou vice-versa)
		Borda = (Borda == DESCIDA) ? SUBIDA : DESCIDA;

		// Atualiza o valor de comparação do Timer 3, Canal 1
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, (Pulso[Borda]));
	}
	else
	{
		// No Operation (nenhuma operação é realizada)
		__NOP();
	}
}

/**
 * @brief  Callback de Interrupção de Período do Timer
 *
 * @details Esta função é chamada quando uma interrupção de estouro de período ocorre no Timer 2.
 *          A interrupção é gatilhada quando o valor do contador do timer atinge o valor máximo e reinicia.
 *          A função atualiza os valores dos pulsos de subida e descida com base nos valores de Ramp_SoftStarter.
 *
 * @param   htim [in] : Ponteiro para a estrutura TIM_HandleTypeDef que contém a configuração do timer.
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	UNUSED(htim);

	// Verifica se a interrupção é do Timer 2
	if (htim->Instance == TIM2)
	{
		// Atualiza os valores dos pulsos de subida e descida
		Pulso[SUBIDA] = Ramp_SoftStarter[i];
		Pulso[DESCIDA] = (Pulso[SUBIDA] + LARGURA_PULSO_CCR);
	}
	else
	{
		// No Operation (nenhuma operação é realizada)
		__NOP();
	}
}
