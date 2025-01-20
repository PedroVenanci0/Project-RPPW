#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "ws2812b_animation.h"

// Máscara original do círculo 5x5
static uint8_t MASK_CIRCLE_5X5[] = {
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0
};

// Definir os limites para determinar a direção do joystick
#define ADC_THRESHOLD_LOW 1000
#define ADC_THRESHOLD_HIGH 3000

// Definindo os pinos do joystick
const int BD = 22;  // Pino digital para o botão do joystick
const int EX = 26;  // Eixo X conectado ao ADC0
const int EY = 27;  // Eixo Y conectado ao ADC1

// Função para percorrer a matriz e alterar os valores
void percorre_matriz(int *matriz, int linhas, int colunas, int ponteiro_pos) {
    int *ponteiro = matriz;  // Ponteiro para o primeiro elemento da matriz

    // Inicializa a matriz com 0's
    for (int i = 0; i < linhas * colunas; i++) {
        *(ponteiro + i) = 0;  // Inicializa o valor como 0
    }

    // Marca a posição atual do ponteiro como 1 (ligando o LED)
    *(ponteiro + ponteiro_pos) = 1;

    // Exibe a matriz após o movimento
    for (int r = 0; r < linhas; r++) {
        for (int c = 0; c < colunas; c++) {
            printf("%d ", *(matriz + r * colunas + c));  // Acesso com aritmética de ponteiro
        }
        printf("\n");
    }
}

int main() {
    stdio_init_all();  // Inicializa UART para saída de dados
    adc_init();        // Inicializa o ADC

    // Configura os pinos GPIO como entradas ADC
    adc_gpio_init(EX); // Eixo X conectado ao ADC0
    adc_gpio_init(EY); // Eixo Y conectado ao ADC1

    // Inicializa o pino do botão do joystick
    gpio_init(BD);             // Inicializa o pino do botão
    gpio_set_dir(BD, GPIO_IN); // Configura o pino do botão como entrada
    gpio_pull_up(BD);          // Ativa o pull-up no pino do botão para evitar flutuações

    // Inicializa o WS2812B
    ws2812b_set_global_dimming(7);
    ws2812b_init(pio0, 7, 25);

    // Posição inicial do ponteiro (por exemplo, no índice 0)
    int ponteiro_pos = 0;

    // Laço principal
    while (true) {
        // Lê o valor do eixo X
        adc_select_input(0);  // Seleciona ADC0 (GPIO26)
        uint adc_x = adc_read();

        // Lê o valor do eixo Y
        adc_select_input(1);  // Seleciona ADC1 (GPIO27)
        uint adc_y = adc_read();

        // Determina a direção com base nos limites
        if (adc_x < ADC_THRESHOLD_LOW) {
            if (ponteiro_pos > 4) {  // Se não for a primeira linha
                ponteiro_pos -= 5;  // Mover para a esquerda
            }
        } else if (adc_x > ADC_THRESHOLD_HIGH) {
            if (ponteiro_pos < 20) {  // Se não for a última linha
                ponteiro_pos += 5;  // Mover para a direita
            }
        }

        if (adc_y < ADC_THRESHOLD_LOW) {
            if (ponteiro_pos > 4) {
                ponteiro_pos -= 1;  // Mover para cima
            }
        } else if (adc_y > ADC_THRESHOLD_HIGH) {
            if (ponteiro_pos < 20) {
                ponteiro_pos += 1;  // Mover para baixo
            }
        }

        // Marca a posição atual do ponteiro como 1 (ligando o LED)
        ws2812b_clear();  // Limpa todos os LEDs
        ws2812b_put(ponteiro_pos, ws2812b_random_color(100.0));  // Acende o LED na posição do ponteiro
        ws2812b_render();  // Renderiza o LED

        // Pausa para visualização
        sleep_ms(200);

        // Verifica se o botão foi pressionado
        if (!gpio_get(BD)) { // Verifica se o botão está pressionado
            printf("Botão pressionado!\n");
        }

        // Pausa por 100 ms para evitar leituras excessivas
        sleep_ms(100);
    }

    return 0;
}
