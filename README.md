# Mood Light Jar

Mood Light Jar este un proiect interactiv care combină tehnologia și designul pentru a crea un dispozitiv decorativ unic. Acesta utilizează un Arduino Uno, LED-uri RGB, un potențiometru și un afișaj LCD pentru a permite utilizatorilor să ajusteze culorile și intensitatea luminii în funcție de starea lor de spirit sau de preferințele lor.

## Componente

- Arduino Uno
- LED-uri RGB
- LCD Alphanumeric Display
- Senzor de temperatură
- Potențiometru
- Breadboard
- Rezistori
- Fire

## Instrucțiuni de Asamblare

1. **Montaj Hardware:**
   - Conectați LED-urile RGB la pinii digitali ai Arduino Uno.
   - Folosiți rezistori pentru a limita curentul către LED-uri.
   - Conectați potențiometrul pentru a ajusta luminozitatea.
   - Conectați afișajul LCD pentru a afișa informații.
   - Conectați senzorul de temperatură pentru a citi temperatura ambientală.

2. **Configurație Software:**
   - Descărcați și instalați [Arduino IDE](https://www.arduino.cc/en/software).
   - Deschideți fișierul `mood-light-jar.ino` în Arduino IDE.
   - Conectați Arduino Uno la computer folosind un cablu USB.
   - Selectați placa Arduino Uno și portul corespunzător din Arduino IDE.
   - Apăsați butonul de upload pentru a încărca codul pe Arduino.

## Funcționalități

- **Controlul Culorilor:** Culorile LED-urilor RGB diferă în funcție de temperatura ambientală și sensibilitatea setată.
- **Afișaj LCD:** Afișează informații despre temperatura ambientală și factorul de sensibilitate.

## Utilizare

- **Interfață de Control:** Rotiți potențiometrul pentru a ajusta sensibilitatea.
- **Resetare:** Apăsați butonul de resetare pe Arduino pentru a reseta dispozitivul la setările implicite.

---

## Code 

### Definitions and Initialization
      The code starts with defining pin numbers for the LEDs and the potentiometer. It includes necessary libraries for the LCD and the HTU21D sensor.

### Setup Function
      In the setup function, the LCD is initialized, all RGB LED pins are set as outputs. The HTU21D sensor is initialized, and the potentiometer pin is set as an input.

### Loop Function
      In the loop function, the temperature is read from the HTU21D sensor and printed to the serial monitor. The potentiometer value is read and mapped to define a temperature sensitivity range.

      The LED intensities are calculated based on the temperature and potentiometer settings, with distinct ranges for the two sets of LEDs. The calculated intensities are printed to the serial monitor.

      The calculated values are used to set the color intensities for both sets of LEDs. The temperature and sensitivity range are displayed on the LCD.

      This system continuously reads temperature data, adjusts the sensitivity range based on the potentiometer, and updates the LED colors and LCD display accordingly.






