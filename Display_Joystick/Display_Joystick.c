#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "ssd1306.h"
#include "hardware/i2c.h"

// Definir os limites para determinar a direção do joystick
#define ADC_THRESHOLD_LOW 1000
#define ADC_THRESHOLD_HIGH 3000
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_ADDRESS 0x3C // Endereço I2C do display
#define I2C_SDA 14          // Pino SDA
#define I2C_SCL 15          // Pino SCL

const int BD = 22; // Pino digital para o botão do joystick
const int EX = 26; 
const int EY = 27; 

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

    while (1) {
        // Lê o valor do eixo X
        adc_select_input(0);  // Seleciona ADC0 (GPIO26)
        uint adc_x = adc_read();

        // Lê o valor do eixo Y
        adc_select_input(1);  // Seleciona ADC1 (GPIO27)
        uint adc_y = adc_read();

        // Determina a direção com base nos limites
        if (adc_x < ADC_THRESHOLD_LOW) {
            printf("Baixo\n");
        } else if (adc_x > ADC_THRESHOLD_HIGH) {
            printf("Cima\n");
        }

        if (adc_y < ADC_THRESHOLD_LOW) {
            printf("Esquerda\n");
        } else if (adc_y > ADC_THRESHOLD_HIGH) {
            printf("Direita\n");
        }

        // Verifica se o botão foi pressionado
        if (!gpio_get(BD)) { // Verifica se o botão está pressionado
            printf("Botão pressionado!\n");
        }

        // Pausa por 100 ms para evitar leituras excessivas
        sleep_ms(100);
    }

//Instância do Display
ssd1306_t display;
void demotxt(const char *texto){
    ssd1306_clear(&display);
    ssd1306_draw_string(&display, 0, 0, 2, texto);
    ssd1306_show(&display);
    sleep_ms(1000);
}
    // Inicializa I2C no canal 1
    i2c_init(i2c1, 400 * 1000); // 400 kHz
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Inicializa o display
    if (!ssd1306_init(&display, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_ADDRESS, i2c1)) { 
        printf("Falha ao inicializar o display SSD1306\n");
        return 1; // Sai do programa
    }

    printf("Display SSD1306 inicializado com sucesso!\n");
    //Exibir o texto
    while (true)
    {
        demotxt("Texto Teste");
    }
 

    return 0;
}

