/*****************************************************************************************
 * Projeto : ESP32 - Player de Voz com 4 Mensagens com Timer de Hardware - ESP32
 * Autor   : RodRobot
 * Site    : https://rodrobot.blogspot.com/p/projetos.html
 *
 * Descrição:
 * Este exemplo reproduz quatro áudios utilizando o DAC interno do ESP32.
 * As amostras são enviadas através de um Timer de Hardware configurado
 * para 16 kHz (16000 amostras por segundo), proporcionando um áudio
 * muito mais estável do que utilizando delayMicroseconds().
 *
 * Hardware:
 * - ESP32
 * - PAM8403
 * - Alto-falante 8 Ω
 * - 4 Botões
 *
 * Ligações:
 * GPIO18 -> Botão 1
 * GPIO19 -> Botão 2
 * GPIO21 -> Botão 3
 * GPIO22 -> Botão 4
 * GPIO25 -> DAC
 *
 * Arquivo audios.h:
 * audio1, audio2, audio3, audio4
 * tamanhoAudio1, tamanhoAudio2, tamanhoAudio3, tamanhoAudio4
 *
 *****************************************************************************************/

#include <driver/dac.h>
#include "audios.h"

//==================== BOTÕES ====================

const int pinoBotao1 = 18;             // Botão Áudio 1
const int pinoBotao2 = 19;             // Botão Áudio 2
const int pinoBotao3 = 21;             // Botão Áudio 3
const int pinoBotao4 = 22;             // Botão Áudio 4

//==================== TIMER =====================

hw_timer_t *timer = NULL;              // Ponteiro para o Timer

volatile bool reproduzindo = false;    // Indica reprodução

volatile const unsigned char *audioAtual = NULL;   // Ponteiro do áudio
volatile uint32_t tamanhoAtual = 0;                // Tamanho do áudio
volatile uint32_t indice = 0;                      // Índice da amostra

//================================================

// Interrupção do Timer (16 kHz)

void IRAM_ATTR onTimer()
{
    if (!reproduzindo) return;                     // Não faz nada

    dac_output_voltage(DAC_CHANNEL_1, audioAtual[indice]); // Envia amostra

    indice++;                                     // Próxima amostra

    if (indice >= tamanhoAtual)
    {
        reproduzindo = false;                     // Finaliza áudio
        indice = 0;
        dac_output_voltage(DAC_CHANNEL_1, 0);     // Silencia DAC
    }
}

//================================================

void tocarAudio(const unsigned char *audio,
                uint32_t tamanho)
{
    if (reproduzindo) return;                     // Evita sobreposição

    audioAtual = audio;                           // Seleciona áudio
    tamanhoAtual = tamanho;                       // Define tamanho
    indice = 0;                                   // Reinicia índice
    reproduzindo = true;                          // Inicia reprodução
}

//================================================

void setup()
{
    pinMode(pinoBotao1, INPUT);                   // Botão 1
    pinMode(pinoBotao2, INPUT);                   // Botão 2
    pinMode(pinoBotao3, INPUT);                   // Botão 3
    pinMode(pinoBotao4, INPUT);                   // Botão 4

    dac_output_enable(DAC_CHANNEL_1);             // Habilita DAC

    timer = timerBegin(1000000);                  // Timer em 1 MHz

    timerAttachInterrupt(timer, &onTimer);        // Liga interrupção

    timerAlarm(timer, 62, true, 0);               // 62 µs ≈ 16 kHz

    timerStart(timer);                            // Inicia Timer
}

//================================================

void loop()
{
    if (digitalRead(pinoBotao1) == HIGH)
    {
        tocarAudio(audio1, tamanhoAudio1);        // Toca áudio 1
        delay(300);                               // Debounce
    }

    if (digitalRead(pinoBotao2) == HIGH)
    {
        tocarAudio(audio2, tamanhoAudio2);        // Toca áudio 2
        delay(300);                               // Debounce
    }

    if (digitalRead(pinoBotao3) == HIGH)
    {
        tocarAudio(audio3, tamanhoAudio3);        // Toca áudio 3
        delay(300);                               // Debounce
    }

    if (digitalRead(pinoBotao4) == HIGH)
    {
        tocarAudio(audio4, tamanhoAudio4);        // Toca áudio 4
        delay(300);                               // Debounce
    }
}
