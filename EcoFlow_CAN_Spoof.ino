/*
#include <SPI.h>
#include <mcp_can.h>

// Pin di selezione chip (CS)
const int CS_PIN = 10;

// Inizializza il modulo MCP2515
MCP_CAN CAN(CS_PIN); // Usa la libreria mcp_can

// Definisci l'intervallo di invio dei messaggi (in secondi)
const float SEND_INTERVAL = 0.5;

// Matrici/Array per messaggi CAN e header
uint8_t header[] = {
    0xaa, 0x03, 0x84, 0x00, 0x3c, 0x2e, 0xac, 0x04,
    0x00, 0x00, 0x0b, 0x3c, 0x03, 0x14, 0x01, 0x01,
    0x03, 0x2f
};

uint8_t message[] = {
    0x01, 0x84, 0x00, 0x4d, 0x31, 0x30, 
    0x32, 0x5a, 0x33, 0x42, 0x34, 0x5a, 0x45, 0x35,
    0x48, 0x30, 0x36, 0x30, 0x31, 0x3c, 0x00, 0x0b,
    0x00, 0x01, 0x4d, 0x03, 0x01, 0x01, 0x11, 0x01,
    0x00, 0x01, 0x02, 0x01, 0x02, 0x00, 0xc8, 0x00,
    0x00, 0x01, 0x00, 0x6e, 0xd2, 0x00, 0x00, 0x51,
    0x56, 0x00, 0x00, 0x01, 0x00, 0x02, 0x8e, 0x88,
    0x05, 0x41, 0x0f, 0x9a, 0xca, 0x00, 0x00, 0x49,
    0xff, 0xff, 0xff, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x15, 0x15, 0x40, 0x9c, 0x00, 0x00, 0x7f, 0x32,
    0x02, 0x00, 0x7a, 0x02, 0x00, 0x00, 0x64, 0x05,
    0x00, 0x64
};

// Funzione di calcolo CRC16
uint16_t crc16(uint8_t *data, uint16_t len) {
  uint16_t crc = 0xFFFF;
  for (uint16_t i = 0; i < len; i++) {
    crc ^= (uint16_t)data[i] << 8;
    for (uint8_t j = 0; j < 8; j++) {
      if (crc & 0x8000) crc = (crc << 1) ^ 0x1021;
      else crc <<= 1;
    }
  }
  return crc;
}

// Funzione per inviare il messaggio CAN
void sendData() {
  // Calcola CRC16 e aggiungilo al messaggio
  uint16_t crc = crc16(message, sizeof(message));
  message[sizeof(message) - 2] = crc >> 8;
  message[sizeof(message) - 1] = crc & 0xFF;
  
  // Invia il messaggio tramite MCP2515
  CAN.sendMsgBuf(0x10003001, 0, sizeof(message), message);
  
  //Serial.println("Messaggio CAN inviato.");
}

// Funzione per leggere i messaggi CAN
void readData() {
  long unsigned int id;
  uint8_t len = 0;
  uint8_t buf[8];

  if (CAN.readMsgBuf(&id, &len, buf)) {
    Serial.print("ID: ");
    Serial.print(id, HEX);
    Serial.print(" Data: ");
    for (int i = 0; i < len; i++) {
      Serial.print(buf[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial);  // Attendere la connessione seriale

  Serial.println("Inizializzazione MCP2515...");

  // Inizializzazione MCP2515 con baudrate 1Mbps e oscillatore a 8 MHz
  if (CAN.begin(MCP_ANY, CAN_1000KBPS, MCP_8MHZ) != CAN_OK) {
    Serial.println("Errore nell'inizializzazione di MCP2515.");
    while (1);  // Se l'inizializzazione fallisce, rimani qui
  }

  Serial.println("MCP2515 inizializzato con successo.");
}

void loop() {
  // Invio messaggio CAN
  sendData();
  
  // Lettura dei messaggi CAN
  readData();
  
  // Aspetta per l'intervallo specificato prima di inviare un altro messaggio
  delay(SEND_INTERVAL * 1000);  // Millisecondi
}

*/



#include <mcp_can.h>
#include <SPI.h>

#define CAN_CS_PIN 10
MCP_CAN CAN(CAN_CS_PIN);

#define SEND_INTERVAL 0.5

// Header
unsigned char header[] = {
    0xaa, 0x03, 0x84, 0x00, 0x3c, 0x2e, 0xac, 0x04,
    0x00, 0x00, 0x0b, 0x3c, 0x03, 0x14, 0x01, 0x01,
    0x03, 0x2f
};

// Message
unsigned char message[] = {
    0x01, 0x84, 0x00, 0x4d, 0x31, 0x30, 0x32, 0x5a, 0x33, 0x42, 0x34, 0x5a, 0x45, 0x35,
    0x48, 0x30, 0x36, 0x30, 0x31, 0x3c, 0x00, 0x0b,
    0x00, 0x01, 0x4d, 0x03, 0x01, 0x01, 0x11, 0x01,
    0x00, 0x01, 0x02, 0x01, 0x02, 0x00, 0xc8, 0x00,
    0x00, 0x01, 0x00, 0x6e, 0xd2, 0x00, 0x00, 0x51,
    0x56, 0x00, 0x00, 0x01, 0x00, 0x02, 0x8e, 0x88,
    0x05, 0x41, 0x0f, 0x9a, 0xca, 0x00, 0x00, 0x49,
    0xff, 0xff, 0xff, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x15, 0x15, 0x40, 0x9c,
    0x00, 0x00, 0x7f, 0x32, 0x02, 0x00, 0x7a, 0x02,
    0x00, 0x00, 0x64, 0x05, 0x00, 0x64
};

// CRC16 function to calculate the checksum
unsigned int crc16(const unsigned char *data, unsigned int length) {
    unsigned int crc = 0xFFFF;
    for (unsigned int i = 0; i < length; i++) {
        crc ^= data[i];
        for (unsigned int j = 8; j; j--) {
            if (crc & 0x01) crc = (crc >> 1) ^ 0xA001;
            else crc >>= 1;
        }
    }
    return crc;
}

// Function to send the data over CAN bus
void send_data() {
    unsigned char msg[sizeof(header) + sizeof(message)];
    
    // Copy header and message into the msg array
    memcpy(msg, header, sizeof(header));
    memcpy(msg + sizeof(header), message, sizeof(message));
    
    // Calculate CRC16 and append it to the message
    unsigned int crc = crc16(msg, sizeof(msg));
    msg[sizeof(msg) - 2] = crc & 0xFF;
    msg[sizeof(msg) - 1] = (crc >> 8) & 0xFF;

    int msg_len = sizeof(msg);
    // Send message in chunks of 8 bytes
    for (int i = 0; i < msg_len / 8; i++) {
        unsigned char data_chunk[8];
        memcpy(data_chunk, msg + i * 8, 8);
        CAN.sendMsgBuf(0x10003001 + i, 0, 8, data_chunk);
    }
    Serial.println("Messaggio inviato!");
}

void setup() {
    Serial.begin(115200);

    // Inizializza CAN a 1 Mbps con quarzo da 8 MHz
    if (CAN.begin(MCP_ANY, CAN_1000KBPS, MCP_8MHZ) == CAN_OK) {
        Serial.println("CAN bus inizializzato correttamente a 1 Mbps su 8 MHz!");
    } else {
        Serial.println("Errore nell'inizializzazione del CAN bus.");
        while (1);
    }

    CAN.setMode(MCP_NORMAL); // modalità normale (no loopback o sleep)
}
void loop() {
    send_data();
    delay(SEND_INTERVAL * 1000); // Delay between sending messages
}
