Jogo da Velha Inteligente - Sistema Embarcado Interativo

📌 Sobre o Projeto

O Jogo da Velha Inteligente é um sistema embarcado interativo que implementa um jogo da velha utilizando a placa Raspberry Pico W, um display OLED SSD1306 e uma matriz de LEDs WS2812B. O objetivo é proporcionar uma experiência intuitiva e visualmente envolvente para os jogadores, explorando conceitos de eletrônica embarcada, lógica de programação e comunicação entre periféricos.

🎯 Funcionalidades

Tabuleiro 5x5 representado por LEDs endereçáveis WS2812B.

Exibição interativa das informações do jogo no display OLED SSD1306.

Controle via botões físicos para navegação e seleção de posições.

Verificação automática de vitória ou empate com alertas visuais e sonoros.

💡 Justificativa

O projeto visa integrar hardware e software em uma aplicação prática, permitindo aprendizado técnico e experimental sobre sistemas embarcados. Além disso, demonstra a versatilidade dos microcontroladores e seus periféricos, incentivando a criatividade e inovação no desenvolvimento de soluções tecnológicas.

🛠️ Hardware Utilizado

Raspberry Pico W: Unidade de processamento principal do sistema.

BitDogLab: Placa didática para facilitar a prototipação.

Display OLED SSD1306: Exibição de informações sobre o jogo.

Matriz de LEDs WS2812B: Representação visual do tabuleiro.

Botões físicos: Interação para movimentação e seleção de posições.

🖥️ Desenvolvimento do Firmware

O firmware foi desenvolvido em C, utilizando a biblioteca standard do Raspberry Pico W para controle dos pinos GPIO e comunicação I2C. O código segue uma estrutura modular, com funções para:

Inicialização dos periféricos;

Controle do display OLED;

Gestão da matriz de LEDs;

Implementação da lógica do jogo.

O sistema lê os botões para movimentação do cursor, atualiza o tabuleiro e verifica automaticamente as condições de vitória ou empate. Quando um jogador vence, o sistema destaca a linha de vitória nos LEDs e exibe uma mensagem no display OLED.

🚀 Execução do Projeto

O desenvolvimento seguiu uma abordagem iterativa com testes frequentes. O processo incluiu:

Configuração e testes individuais dos periféricos.

Implementação da lógica do jogo para garantir a aplicação correta das regras.

Otimização do código para garantir uma jogabilidade fluida.

Testes finais para validar o funcionamento do sistema e o feedback visual.

📊 Resultados Obtidos

Os testes mostraram que o sistema oferece uma jogabilidade intuitiva e visualmente envolvente. Os principais pontos positivos foram:
✅ Interface clara e objetiva no display OLED;
✅ Efeito dinâmico e interativo na matriz de LEDs;
✅ Resposta rápida e precisa dos botões físicos.

📌 Melhorias Futuras

🔹 Implementação de jogabilidade remota via Wi-Fi;
🔹 Armazenamento de estatísticas das partidas;
🔹 Otimização do consumo de energia para aplicações portáteis.

📁 Código-Fonte

O código-fonte do projeto está disponível para consulta e futuras melhorias.

📂 Repositório do Projeto (adicione o link aqui)

Desenvolvido por Pedro Victor Venâncio dos Santos 
