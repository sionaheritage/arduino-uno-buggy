# Buggy Hardware & Wiring Reference

Summary of the buggy's electrical connections to match the code.

## Power Distribution
[cite_start]The buggy uses a 4x AA battery pack (~6V nominal) to power the entire system[cite: 145, 161]. 
* [cite_start]**Battery Pack (+)** ➔ Rocker Switch (Input)[cite: 174, 180].
* [cite_start]**Rocker Switch (Output)** ➔ Breadboard Power Rail (+) **AND** L298N `+12V` Terminal **AND** Arduino `VIN` Pin[cite: 184, 263, 264].
* [cite_start]**Battery Pack (-)** ➔ Breadboard Ground Rail (-)[cite: 184].
* [cite_start]**Shared Ground**: The Breadboard (-), Arduino `GND`, and L298N `GND` **MUST** all be connected together to prevent erratic behavior[cite: 166, 206, 266, 268].

---

## Motor Driver (L298N)
Controls the two DC gear motors. [cite_start]The `EN` pins must connect to PWM-capable Arduino pins (marked with a `~`) for speed control[cite: 350, 401].

| L298N Pin | Arduino Pin | Function |
| :--- | :--- | :--- |
| **ENA** | Digital Pin 6 (PWM) | [cite_start]Left Motor Speed [cite: 654] |
| **IN1** | Digital Pin 8 | [cite_start]Left Motor Direction A [cite: 400] |
| **IN2** | Digital Pin 7 | [cite_start]Left Motor Direction B [cite: 400] |
| **IN3** | Digital Pin 4 | [cite_start]Right Motor Direction A [cite: 400] |
| **IN4** | Digital Pin 2 | [cite_start]Right Motor Direction B [cite: 400] |
| **ENB** | Digital Pin 3 (PWM) | [cite_start]Right Motor Speed [cite: 654] |

### Motor Terminals
* [cite_start]**Left Motor**: Connect wires to L298N `OUT1` (Red) and `OUT2` (Black)[cite: 293, 294].
* [cite_start]**Right Motor**: Connect wires to L298N `OUT4` (Red) and `OUT3` (Black)[cite: 293, 294].

---

## Ultrasonic Sensor (HC-SR04)
[cite_start]Acts as the buggy's "eyes" to measure distance using sound waves[cite: 438].

| Sensor Pin | Connection | Function |
| :--- | :--- | :--- |
| **VCC** | Breadboard (+) | [cite_start]5V Power Supply [cite: 447, 461] |
| **Trig** | Digital Pin 13 | [cite_start]Sends the ultrasonic pulse [cite: 448, 462, 742] |
| **Echo** | Digital Pin 12 | [cite_start]Listens for the returning pulse [cite: 454, 462, 742] |
| **GND** | Breadboard (-) | [cite_start]Ground Connection [cite: 455, 461] |

---

## Servo Motor (SG90)
[cite_start]Rotates the Ultrasonic sensor to scan for clear paths[cite: 440].

| Servo Wire Color | Connection | Function |
| :--- | :--- | :--- |
| **Red** | Breadboard (+) | [cite_start]5V Power Supply [cite: 420, 422] |
| **Brown/Black** | Breadboard (-) | [cite_start]Ground Connection [cite: 422] |
| **Orange/Yellow**| Digital Pin 11 (PWM) | [cite_start]Signal/Control [cite: 426, 788] |

