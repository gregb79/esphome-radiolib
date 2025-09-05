#pragma once

#include "esphome/core/component.h"
#include "esphome/components/spi/spi.h"


#define RADIOLIB_LOW_LEVEL 1
#include "EHRLHal.h"

namespace esphome {
namespace radio_cc1101 {

enum CC1101_state {CC1101_NOINIT,CC1101_STANDBY,CC1101_RECV,CC1101_XMIT};
enum CC1101Modulation {OOK_MODULATION=0, FSK_MODULATION};

class RadioCC1101Component : public Component {
  public:
    void setup() override;
    void loop() override;
    void dump_config() override;
    int standby();
    int xmit();
    int recv();
    void set_rx_pin(InternalGPIOPin *rx_pin) { _gd0_rx = rx_pin; }
    void set_tx_pin(InternalGPIOPin *tx_pin) { _gd0_tx = tx_pin; }
    void set_frequency(float freq) { _freq=freq/1e6; }
    void set_modulation(CC1101Modulation modulation) { _modulation=modulation; }
    void set_registers();
    void setup_direct_mode();
    float getRSSI();

    EH_RL_Hal* hal;
    CC1101 radio=NULL;
    int init_state=0;
    CC1101_state state=CC1101_NOINIT;
    float _freq=433.92;
    CC1101Modulation _modulation=OOK_MODULATION;
    float _bandwidth=464;
    
    InternalGPIOPin* _gd0_rx=nullptr;
    InternalGPIOPin* _gd0_tx=nullptr;

    // For RSSI rx average
    float last_rx_rssi=0;

  private:
    void adjustBW(float bandwidth); // rx filter bw snapper

};


}  // namespace empty_spi_component
}  // namespace esphome
