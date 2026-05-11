#include "esphome.h"

class MyRFDecoder : public Component {
 public:
  void setup() override {
    ESP_LOGI("custom", "RF Decoder initialized");
  }

  void loop() override {
    if (!id(remote_receiver).available()) return; // Ждем сигнал

    auto raw_signal = id(remote_receiver).receive(); // Получаем сигнал
    std::string bits;

    for (auto pulse : raw_signal) {
      if (pulse.duration > 1800 && pulse.duration < 2200) {
        bits += "0";
      } else if (pulse.duration > 3800 && pulse.duration < 4200) {
        bits += "1";
      }
    }

    ESP_LOGI("custom", "Полученные данные: %s", bits.c_str());
  }
};