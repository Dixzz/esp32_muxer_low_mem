// #include "BluetoothA2DPSource.h"
// // #include "AudioCodecs/CodecMP3Helix.h"
// #include "AudioTools.h"

// const int buffer_count = 30;
// const int buffer_size = 512;

// BluetoothA2DPSource a2dp_source;
// // MP3DecoderHelix decoder;
// SynchronizedNBuffer<uint8_t> buffer(buffer_size,buffer_count, portMAX_DELAY, 10);
// QueueStream<uint8_t> out(buffer); // convert Buffer to Stream


// class Axy: public AudioSource {
//     protected:
//         SineWaveGenerator<int16_t> *sineWave;               // subclass of SoundGenerator, set max amplitude (=volume)
//         GeneratedSoundStream<int16_t> *in_stream;

//     virtual void begin() override {
//         TRACED();
//         static bool is_sd_setup = false;
//         if (!is_sd_setup) {
//             this->sineWave = new SineWaveGenerator<int16_t>(1212);
//             this->in_stream = new GeneratedSoundStream<int16_t>(*sineWave);
//             auto cfg = in_stream->defaultConfig();
//             cfg.bits_per_sample = 16;
//             cfg.channels = 2;
//             cfg.sample_rate = 44100;
//             in_stream->begin(cfg);
//             sineWave->begin(cfg, N_B4);
//             is_sd_setup = true;
//         }
//     }

//     virtual Stream* nextStream(int offset) override {
//         return in_stream;
//     }
//     virtual Stream* selectStream(const char *path) override {
//         return in_stream;
//     }
// };

// Axy source2;
// CopyDecoder no_decoder{true};
// AudioPlayer player(source2, out, no_decoder);

// const char* name = "OnePlus Bullets Wireless Z2";                        // Replace with your bluetooth speaker name  

// int32_t get_sound_data(Frame* frame, int32_t frameCount) {
//     uint8_t* cc = (uint8_t*) frame;
//     return buffer.readArray(cc, frameCount);
// }

// void setup() {
//     Serial.begin(115200);
//     AudioLogger::instance().begin(Serial, AudioLogger::Info);

//     // start QueueStream
//     out.begin();

//     // setup player
//     player.setDelayIfOutputFull(0);
//     player.setVolume(0.1);
//     player.begin();

//      player.getStreamCopy().copyAll();

//   a2dp_source.start(name, get_sound_data);

//   Serial.println("A2DP started");
// }

// void loop() {
//     player.copy();
// }