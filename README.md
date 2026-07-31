# ESP32 - Reproduzindo 4 Mensagens de Voz com o DAC Interno

Este projeto demonstra como utilizar o **DAC interno do ESP32** para reproduzir quatro mensagens de voz armazenadas em memória Flash.

A reprodução é realizada utilizando um **Timer de Hardware**, garantindo uma taxa de amostragem de **16 kHz** e uma reprodução muito mais estável do que utilizando `delayMicroseconds()`.

---

## Demonstração

O ESP32 reproduz as seguintes mensagens:

- 🔊 Temperatura 30 graus
- 🔊 Aguarde um momento
- 🔊 Sensor garagem
- 🔊 Sensor porta

Cada mensagem é acionada por um sensor touch TTP223.

---

## Recursos

- ESP32 DevKit
- DAC interno (GPIO25)
- Timer de Hardware
- Reprodução de áudio em 8 bits
- Frequência de 16 kHz
- Quatro mensagens de voz
- Código comentado
- Arduino IDE

  
