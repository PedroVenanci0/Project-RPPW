#include <stdio.h>
#include "pico/stdlib.h"
#include "ws2812b_animation.h"
#include "ssd1306.h"  // Biblioteca para o display OLED

#define BTN_A_PIN 5
#define BTN_B_PIN 6
#define SIZE 5  // Dimensão do tabuleiro 5x5
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_ADDRESS 0x3C // Endereço I2C do display
#define I2C_SDA 14          // Pino SDA do display
#define I2C_SCL 15          // Pino SCL do display

// Estrutura do tabuleiro para controle das posições jogáveis
int board[SIZE][SIZE] = {
    {1, 0, 1, 0, 1},
    {0, 0, 0, 0, 0},
    {1, 0, 1, 0, 1},
    {0, 0, 0, 0, 0},
    {1, 0, 1, 0, 1}
};

int cursor_x = 0, cursor_y = 0;
int current_player = 1;  // Alterna entre 1 (X) e 2 (O)

// Instância do display OLED
ssd1306_t display;

// Função para inicializar o display OLED
void init_oled_display() {
    i2c_init(i2c1, 400 * 1000); // 400 kHz
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    if (!ssd1306_init(&display, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_ADDRESS, i2c1)) {
        printf("Erro ao inicializar o display OLED\n");
    } else {
        ssd1306_clear(&display);
        ssd1306_show(&display);
    }
}

// Função para exibir qual jogador está com a vez
void display_player_turn() {
    char player_turn[20];
    if (current_player == 1) {
        snprintf(player_turn, sizeof(player_turn), "Vez do Jogador X");
    } else {
        snprintf(player_turn, sizeof(player_turn), "Vez do Jogador O");
    }
    
    ssd1306_clear(&display);
    ssd1306_draw_string(&display, 0, 0, 1, player_turn);
    ssd1306_show(&display);
}

// Verifica se há um vencedor
int check_winner() {
    for (int i = 0; i < SIZE; i += 2) {
        if (board[i][0] > 2 && board[i][0] == board[i][2] && board[i][2] == board[i][4])
            return board[i][0];
        if (board[0][i] > 2 && board[0][i] == board[2][i] && board[2][i] == board[4][i])
            return board[0][i];
    }
    if (board[0][0] > 2 && board[0][0] == board[2][2] && board[2][2] == board[4][4])
        return board[0][0];
    if (board[0][4] > 2 && board[0][4] == board[2][2] && board[2][2] == board[4][0])
        return board[0][4];
    return 0;
}

// Verifica se o jogo terminou em empate
int check_draw() {
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            if (board[y][x] == 1)
                return 0;
        }
    }
    return 1;
}

// Reinicia o jogo
void reset_game() {
    int initial_board[SIZE][SIZE] = {
        {1, 0, 1, 0, 1},
        {0, 0, 0, 0, 0},
        {1, 0, 1, 0, 1},
        {0, 0, 0, 0, 0},
        {1, 0, 1, 0, 1}
    };
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            board[y][x] = initial_board[y][x];
        }
    }
    cursor_x = 0;
    cursor_y = 0;
    current_player = 1;
}

// Atualiza a matriz de LEDs conforme o estado do tabuleiro
void update_display() {
    ws2812b_clear();
    ws2812b_set_global_dimming(10);
    printf("\n Jogo da Velha\n");
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            int index = y * SIZE + x;
            if (board[y][x] == 1) {
                ws2812b_put(index, 0x000000);
                printf(" 1 ");
            } else if (board[y][x] == 3) {
                ws2812b_put(index, 0x0000FF);
                printf(" X ");
            } else if (board[y][x] == 4) {
                ws2812b_put(index, 0xFFFF00);
                printf(" O ");
            } else {
                ws2812b_put(index, 0x808080);
                printf(" 0 ");
            }
        }
        printf("\n");
    }
    printf("\n");

    int cursor_index = cursor_y * SIZE + cursor_x;
    if (board[cursor_y][cursor_x] == 1) {
        ws2812b_put(cursor_index, 0x00FF00);
    }

    ws2812b_render();
}

// Brilhar a matriz de LEDs na cor do vencedor
void highlight_winner(int winner) {
    int winner_color = (winner == 3) ? 0x0000FF : 0xFFFF00;
    for (int i = 0; i < SIZE * SIZE; i++) {
        ws2812b_put(i, winner_color);
    }
    ws2812b_render();
    sleep_ms(1000);
}

int main() {
    stdio_init_all();
    ws2812b_init(pio0, 7, 25);
    gpio_init(BTN_A_PIN);
    gpio_set_dir(BTN_A_PIN, GPIO_IN);
    gpio_pull_up(BTN_A_PIN);
    gpio_init(BTN_B_PIN);
    gpio_set_dir(BTN_B_PIN, GPIO_IN);
    gpio_pull_up(BTN_B_PIN);

    // Inicializa o display OLED
    init_oled_display();

    // Exibe a vez do jogador inicial
    display_player_turn();

    while (true) {
        if (gpio_get(BTN_A_PIN) == 0) {
            do {
                cursor_x = (cursor_x + 1) % SIZE;
                if (cursor_x == 0) cursor_y = (cursor_y + 1) % SIZE;
            } while (board[cursor_y][cursor_x] == 0);
            update_display();
            sleep_ms(300);
        }
        if (gpio_get(BTN_B_PIN) == 0) {
            if (board[cursor_y][cursor_x] == 1) {
                board[cursor_y][cursor_x] = current_player + 2;
                int winner = check_winner();
                if (winner) {
                    printf("Jogador %d venceu!\n", winner - 2);
                    highlight_winner(winner);
                    break;
                }

                if (check_draw()) {
                    printf("Empate! O jogo será reiniciado.\n");
                    reset_game();
                } else {
                    current_player = (current_player == 1) ? 2 : 1;
                }
                update_display();
                display_player_turn();  // Atualiza a tela com a vez do jogador
            }
            sleep_ms(300);
        }
    }
    return 0;
}
