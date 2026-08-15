#pragma once

#include <cstdint>

namespace GermaniumProtocol
{

static constexpr uint16_t PROTOCOL_MAJOR = 1;
static constexpr uint16_t PROTOCOL_MINOR = 0;
static constexpr uint32_t PROTOCOL_VERSION =
    (static_cast<uint32_t>(PROTOCOL_MAJOR) << 16) | PROTOCOL_MINOR;

static constexpr uint16_t protocolVersionMajor(uint32_t version)
{
    return static_cast<uint16_t>((version >> 16) & 0xFFFFu);
}

static constexpr uint16_t protocolVersionMinor(uint32_t version)
{
    return static_cast<uint16_t>(version & 0xFFFFu);
}

struct Message
{
    uint32_t cmd;
    uint32_t addr;
    uint32_t value;
};

static_assert(sizeof(Message) == 12, 
              "GermaniumProtocol::Message must be 12 bytes");

namespace Command
{
    static constexpr uint32_t REG_READ          = 0x00;
    static constexpr uint32_t REG_WRITE         = 0x01;

    static constexpr uint32_t MARS_GLOBAL_SET   = 0x10;
    static constexpr uint32_t MARS_GLOBAL_READ  = 0x11;
    static constexpr uint32_t MARS_CHANNEL_SET  = 0x12;
    static constexpr uint32_t MARS_CHANNEL_READ = 0x13;
    static constexpr uint32_t MARS_LOAD         = 0x14;

    static constexpr uint32_t ADC_CLK_SKEW_SET  = 0x20;
    static constexpr uint32_t I2C_TEMP_READ     = 0x21;
    static constexpr uint32_t XADC_READ         = 0x22;
    static constexpr uint32_t I2C_DAC_WRITE     = 0x23;
    static constexpr uint32_t I2C_ADC_READ      = 0x24;
    static constexpr uint32_t I2C_DAC_INIT      = 0x25;
    static constexpr uint32_t ADC_CLK_SKEW_READ = 0x26;

    static constexpr uint32_t SET_LOG_LEVEL     = 0x30;
    static constexpr uint32_t GET_PROTOCOL_VERSION = 0xFE;
    static constexpr uint32_t HEARTBEAT         = 0xFF;
}

namespace Register
{   
    static constexpr uint32_t MARS_CONF_LOAD    = 0;
    static constexpr uint32_t LEDS              = 1;
    static constexpr uint32_t MARS_CONFIG       = 2;
    static constexpr uint32_t VERSIONREG        = 3;
    static constexpr uint32_t MARS_CALPULSE     = 4;
    static constexpr uint32_t MARS_PIPE_DELAY   = 5;
    static constexpr uint32_t DETECTOR_TYPE     = 6;
    static constexpr uint32_t DETECTOR_MODEL    = DETECTOR_TYPE;
    static constexpr uint32_t MARS_RDOUT_ENB    = 8;
    static constexpr uint32_t EVENT_TIME_CNTR   = 9;
    static constexpr uint32_t SIM_EVT_SEL       = 10;
    static constexpr uint32_t SIM_EVENT_RATE    = 11;
    static constexpr uint32_t ADC_SPI           = 12;
    static constexpr uint32_t CALPULSE_CNT      = 16;
    static constexpr uint32_t CALPULSE_RATE     = 17;
    static constexpr uint32_t CALPULSE_WIDTH    = 18;
    static constexpr uint32_t CALPULSE_MODE     = 19;
    static constexpr uint32_t TD_CAL            = 20;
    static constexpr uint32_t EVENT_FIFO_DATA   = 24;
    static constexpr uint32_t EVENT_FIFO_CNT    = 25;
    static constexpr uint32_t EVENT_FIFO_CNTRL  = 26;
    static constexpr uint32_t EVENT_FIFO_CTRL   = EVENT_FIFO_CNTRL;
    static constexpr uint32_t DMA_CONTROL       = 32;
    static constexpr uint32_t DMA_STAT          = 33;
    static constexpr uint32_t DMA_STATUS        = DMA_STAT;
    static constexpr uint32_t DMA_BASEADDR      = 34;
    static constexpr uint32_t DMA_BURSTLEN      = 35;
    static constexpr uint32_t DMA_BUFLEN        = 36;
    static constexpr uint32_t DMA_CURADDR       = 37;
    static constexpr uint32_t DMA_THROTTLE      = 38;
    static constexpr uint32_t UDP_IP_ADDR       = 40;
    static constexpr uint32_t DMA_IRQ_THROTTLE  = 48;
    static constexpr uint32_t DMA_IRQ_ENABLE    = 49;
    static constexpr uint32_t DMA_IRQ_COUNT     = 50;
    static constexpr uint32_t TRIG              = 52;
    static constexpr uint32_t COUNT_TIME_LO     = 53;
    static constexpr uint32_t COUNT_TIME_HI     = 54;
    static constexpr uint32_t FRAME_NO          = 55;
    static constexpr uint32_t COUNT_MODE        = 56;
}

enum MarsGlobalField
{
    MARS_FIELD_ST    = 0,
    MARS_FIELD_GAIN  = 1,
    MARS_FIELD_POL   = 2,
    MARS_FIELD_EBLK  = 3,
    MARS_FIELD_GMON  = 4,
    MARS_FIELD_PUEN  = 5,
    MARS_FIELD_MFS   = 6,
    MARS_FIELD_TDS   = 7,
    MARS_FIELD_TDM   = 8,
    MARS_FIELD_TH    = 9,
    MARS_FIELD_TPAMP = 10,
    MARS_FIELD_C     = 11,
    MARS_FIELD_M0    = 12,
    MARS_FIELD_SAUX  = 13,
};

enum MarsChannelField
{
    MARS_CH_CHEN = 0,
    MARS_CH_TSEN = 1,
    MARS_CH_THTR = 2,
    MARS_CH_PUTR = 3,
    MARS_CH_SEL  = 4,
};

} // namespace GermaniumProtocol
