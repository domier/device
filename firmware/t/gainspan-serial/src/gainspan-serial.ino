#include "Arduino.h"
#include "pins.h"
#include "pgmStrToRAM.h"

void setup() {
    // USB serial
    Serial.begin(115200);

    // wait for connection
    while ( ! Serial ) ;

    pinMode( LDO33_ENABLE, OUTPUT );
    digitalWrite( LDO33_ENABLE, HIGH );

    // gainspan
    Serial1.begin(9600);
}

void loop() {
    // gainspan -> usb
    if (Serial1.available()) {
        Serial.write(Serial1.read());
    }

    // usb -> gainspan
    if (Serial.available()) {
        static uint8_t last_character = '0';
        static bool isCommandMode = false;

        last_character = Serial.read();

        if (isCommandMode) {
            Serial1.write(last_character);

            if ( last_character == 0x1B ) {
                isCommandMode = false;
                Serial.println(P("<< command mode finished !!!!"));
            }
            return;
        }
        else if (last_character == 0x1B) {
            isCommandMode = true;
            Serial.println(P(">> entered command mode !!!!"));
            return;
        }

        Serial.write(last_character);
        Serial.println();

        if (last_character == 'g') {
            Serial1.end();
            Serial1.begin(115200);

            Serial.println("change Serial1 baud to 115200");
        }
        else if (last_character == 'G') {
            Serial1.end();
            Serial1.begin(9600);

            Serial.println("change Serial1 baud to 9600");
        }

        Serial.print(P("> "));
    }
}