#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "ssd1306.h"
#include "hardware/i2c.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_ADDRESS 0x3C // Endereço I2C do display
#define I2C_SDA 14          // Pino SDA
#define I2C_SCL 15          // Pino SCL

//Instância do Display
ssd1306_t display;
void demotxt(const char *texto){
    ssd1306_clear(&display);
    ssd1306_draw_string(&display, 0, 35, 1, texto);
    ssd1306_show(&display);
    sleep_ms(1000);
}

int main() {
    // Inicializa UART para depuração
    stdio_init_all();

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
        demotxt("venancio meu gostoso");
    }
    return 0;
}