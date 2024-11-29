#include <Arduino.h>
// #include <IRremote.hpp>
#include <SD.h>
#include <FS.h>
// #include "BluetoothA2DPSource.h"
// #include "AudioLibs/AudioSourceSDMMC.h"
#include "AudioTools.h"
#include "AudioLibs/A2DPStream.h"

// #define IR_RECEIVE_PIN 5

#define CS 5
// #define IR_SENDER_PIN 19

const char* mp3 = "/Major-Lazer-And-DJ-Snake-Ft-MØ-Lean-On-(TrendyBeatz.com).mp3";


void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
    Serial.printf("Listing directory: %s\n", dirname);

    File root = fs.open(dirname);
    if(!root){
        Serial.println("Failed to open directory");
        return;
    }
    if(!root.isDirectory()){
        Serial.println("Not a directory");
        return;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if(levels){
                listDir(fs, file.path(), levels -1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("  SIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}


void writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Writing file: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }
    if(file.print(message)){
        Serial.println("File written");
    } else {
        Serial.println("Write failed");
    }
    file.close();
}

const char* name = "OnePlus Bullets Wireless Z2";                        // Replace with your bluetooth speaker name  
SineWaveGenerator<int16_t> sineWave(15000);               // subclass of SoundGenerator, set max amplitude (=volume)
GeneratedSoundStream<int16_t> in_stream(sineWave);        // Stream generated from sine wave
BluetoothA2DPSource a2dp_source;                          // A2DP Sender
A2DPStream out;

File file;
// callback used by A2DP to provide the sound data - usually len is 128 * 2 channel int16 frames
int32_t get_sound_data(uint8_t * data, int32_t len) {
  

    // File file = SD.open(mp3);
    // if(!file){
    //     Serial.println("Failed to open file for reading");
    //     return;
    // }

    // Serial.print("Read from file: ");
    // while(file.available()){
      // Serial.println(file.available());
      // return file.read((uint8_t*)data, len);
    // }
    // file.close();
  return in_stream.readBytes((uint8_t*)data, len);
}

void setup() {
  Serial.begin(115200); // // Establish serial communication
  // IrSender.begin(IR_SENDER_PIN);
  // Serial.print("MOSI: ");
  // Serial.println(MOSI);
  // Serial.print("MISO: ");
  // Serial.println(MISO);
  // Serial.print("SCK: ");
  // Serial.println(SCK);
  // IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the receiver
    if (!SD.begin(CS)) {
    Serial.println("initialization failed!");
    return;
  }
    uint8_t cardType = SD.cardType();

    if(cardType == CARD_NONE){
        Serial.println("No SD card attached");
        return;
    }

    Serial.print("SD Card Type: ");
    if(cardType == CARD_MMC){
        Serial.println("MMC");
    } else if(cardType == CARD_SD){
        Serial.println("SDSC");
    } else if(cardType == CARD_SDHC){
        Serial.println("SDHC");
    } else {
        Serial.println("UNKNOWN");
    }

    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    Serial.printf("SD Card Size: %lluMB\n", cardSize);
    listDir(SD, "/", 0);
    Serial.printf("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
    Serial.printf("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));
  
  AudioLogger::instance().begin(Serial, AudioLogger::Warning);

  // start input 
  auto cfg = in_stream.defaultConfig();
  cfg.bits_per_sample = 16;
  cfg.channels = 2;
  cfg.sample_rate = 44100;
  in_stream.begin(cfg);
  sineWave.begin(cfg, N_B4);


    // file = SD.open(mp3);
    // if(!file){
    //     Serial.println("Failed to open file for reading");
    //     return;
    // }

    // Serial.println(file.available());
    // while(file.available()){
    //   uint8_t bytes = file.read((uint8_t*)data, len);
    // }
    // file.close();

  // start the bluetooth
  Serial.println("starting A2DP...");
  // a2dp_source.set_auto_reconnect(false);
  a2dp_source.start_raw(name, get_sound_data);
}

void loop() {
  // delay(2000);
  // IrSender.sendNEC(0xEF00, 0x8, 0xFF);
  //  Serial.println("Sent");

  // delay(500);
  // if (IrReceiver.decode()) {
  //     Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX); // Print "old" raw data
  //     IrReceiver.printIRResultRawFormatted(&Serial, true);
  //     IrReceiver.printIRResultShort(&Serial); // Print complete received data in one line
  //     IrReceiver.printIRSendUsage(&Serial);   // Print the statement required to send this data
  //     delay(1000);
  //     IrReceiver.resume(); // Enable receiving of the next value
  // }
}