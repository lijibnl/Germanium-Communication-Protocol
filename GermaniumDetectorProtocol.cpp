#include "GermaniumDetectorProtocol.hpp"

#include <iomanip>
#include <sstream>

namespace GermaniumProtocol
{

const char* commandName(uint32_t cmd)
{
    switch (cmd)
    {
        case Command::REG_READ:             return "REG_READ";
        case Command::REG_WRITE:            return "REG_WRITE";
        case Command::MARS_GLOBAL_SET:      return "MARS_GLOBAL_SET";
        case Command::MARS_GLOBAL_READ:     return "MARS_GLOBAL_READ";
        case Command::MARS_CHANNEL_SET:     return "MARS_CHANNEL_SET";
        case Command::MARS_CHANNEL_READ:    return "MARS_CHANNEL_READ";
        case Command::MARS_LOAD:            return "MARS_LOAD";
        case Command::ADC_CLK_SKEW_SET:     return "ADC_CLK_SKEW_SET";
        case Command::ADC_CLK_SKEW_READ:    return "ADC_CLK_SKEW_READ";
        case Command::I2C_TEMP_READ:        return "I2C_TEMP_READ";
        case Command::XADC_READ:            return "XADC_READ";
        case Command::I2C_DAC_WRITE:        return "I2C_DAC_WRITE";
        case Command::I2C_ADC_READ:         return "I2C_ADC_READ";
        case Command::I2C_DAC_INIT:         return "I2C_DAC_INIT";
        case Command::SET_LOG_LEVEL:        return "SET_LOG_LEVEL";
        case Command::GET_PROTOCOL_VERSION: return "GET_PROTOCOL_VERSION";
        case Command::HEARTBEAT:            return "HEARTBEAT";
        default:                            return "UNKNOWN";
    }
}

const char* registerName(uint32_t addr)
{
    switch (addr)
    {
        case Register::MARS_CONF_LOAD:   return "MARS_CONF_LOAD";
        case Register::LEDS:             return "LEDS";
        case Register::MARS_CONFIG:      return "MARS_CONFIG";
        case Register::VERSIONREG:       return "VERSIONREG";
        case Register::MARS_CALPULSE:    return "MARS_CALPULSE";
        case Register::MARS_PIPE_DELAY:  return "MARS_PIPE_DELAY";
        case Register::DETECTOR_TYPE:    return "DETECTOR_MODEL";
        case Register::MARS_RDOUT_ENB:   return "MARS_RDOUT_ENB";
        case Register::EVENT_TIME_CNTR:  return "EVENT_TIME_CNTR";
        case Register::SIM_EVT_SEL:      return "SIM_EVT_SEL";
        case Register::SIM_EVENT_RATE:   return "SIM_EVENT_RATE";
        case Register::ADC_SPI:          return "ADC_SPI";
        case Register::CALPULSE_CNT:     return "CALPULSE_CNT";
        case Register::CALPULSE_RATE:    return "CALPULSE_RATE";
        case Register::CALPULSE_WIDTH:   return "CALPULSE_WIDTH";
        case Register::CALPULSE_MODE:    return "CALPULSE_MODE";
        case Register::TD_CAL:           return "TD_CAL";
        case Register::EVENT_FIFO_DATA:  return "EVENT_FIFO_DATA";
        case Register::EVENT_FIFO_CNT:   return "EVENT_FIFO_CNT";
        case Register::EVENT_FIFO_CNTRL: return "EVENT_FIFO_CTRL";
        case Register::DMA_CONTROL:      return "DMA_CONTROL";
        case Register::DMA_STAT:         return "DMA_STAT";
        case Register::DMA_BASEADDR:     return "DMA_BASEADDR";
        case Register::DMA_BURSTLEN:     return "DMA_BURSTLEN";
        case Register::DMA_BUFLEN:       return "DMA_BUFLEN";
        case Register::DMA_CURADDR:      return "DMA_CURADDR";
        case Register::DMA_THROTTLE:     return "DMA_THROTTLE";
        case Register::UDP_IP_ADDR:      return "UDP_IP_ADDR";
        case Register::DMA_IRQ_THROTTLE: return "DMA_IRQ_THROTTLE";
        case Register::DMA_IRQ_ENABLE:   return "DMA_IRQ_ENABLE";
        case Register::DMA_IRQ_COUNT:    return "DMA_IRQ_COUNT";
        case Register::TRIG:             return "TRIG";
        case Register::COUNT_TIME_LO:    return "COUNT_TIME_LO";
        case Register::COUNT_TIME_HI:    return "COUNT_TIME_HI";
        case Register::FRAME_NO:         return "FRAME_NO";
        case Register::COUNT_MODE:       return "COUNT_MODE";
        default:                         return nullptr;
    }
}

const char* marsGlobalFieldName(uint16_t field)
{
    switch (field)
    {
        case MARS_FIELD_ST:    return "ST";
        case MARS_FIELD_GAIN:  return "GAIN";
        case MARS_FIELD_POL:   return "POL";
        case MARS_FIELD_EBLK:  return "EBLK";
        case MARS_FIELD_GMON:  return "GMON";
        case MARS_FIELD_PUEN:  return "PUEN";
        case MARS_FIELD_MFS:   return "MFS";
        case MARS_FIELD_TDS:   return "TDS";
        case MARS_FIELD_TDM:   return "TDM";
        case MARS_FIELD_TH:    return "TH";
        case MARS_FIELD_TPAMP: return "TPAMP";
        case MARS_FIELD_C:     return "C";
        case MARS_FIELD_M0:    return "M0";
        case MARS_FIELD_SAUX:  return "SAUX";
        default:               return "?";
    }
}

const char* marsChannelFieldName(uint16_t field)
{
    switch (field)
    {
        case MARS_CH_CHEN: return "CHEN";
        case MARS_CH_TSEN: return "TSEN";
        case MARS_CH_THTR: return "THTR";
        case MARS_CH_PUTR: return "PUTR";
        case MARS_CH_SEL:  return "SEL";
        default:           return "?";
    }
}

std::string formatMessage(const Message& msg)
{
    std::ostringstream oss;
    oss << commandName(msg.cmd) << ": ";

    switch (msg.cmd)
    {
        case Command::REG_READ:
        case Command::REG_WRITE:
        {
            const char* name = registerName(msg.addr);
            oss << (name ? name : "reg?")
                << " [0x" << std::hex << msg.addr << "]"
                << " value=0x" << std::hex << msg.value;
            break;
        }

        case Command::MARS_GLOBAL_SET:
        case Command::MARS_GLOBAL_READ:
        {
            uint16_t chip_mask = static_cast<uint16_t>((msg.addr >> 16) & 0x0FFF);
            uint16_t field_id = static_cast<uint16_t>(msg.addr & 0xFFFF);
            oss << "chip_mask=0x" << std::hex << chip_mask
                << " field=" << marsGlobalFieldName(field_id)
                << " [" << std::dec << field_id << "]"
                << " value=0x" << std::hex << msg.value;
            break;
        }

        case Command::MARS_CHANNEL_SET:
        case Command::MARS_CHANNEL_READ:
        {
            uint16_t channel = static_cast<uint16_t>((msg.addr >> 16) & 0x0FFF);
            uint16_t field_id = static_cast<uint16_t>(msg.addr & 0xFFFF);
            oss << "channel=" << std::dec << channel
                << " field=" << marsChannelFieldName(field_id)
                << " [" << field_id << "]"
                << " value=0x" << std::hex << msg.value;
            break;
        }

        case Command::MARS_LOAD:
        {
            uint16_t chip_mask = static_cast<uint16_t>(msg.addr & 0x0FFF);
            oss << "chip_mask=0x" << std::hex << chip_mask;
            break;
        }

        case Command::ADC_CLK_SKEW_SET:
        case Command::ADC_CLK_SKEW_READ:
        case Command::I2C_TEMP_READ:
        case Command::XADC_READ:
        case Command::I2C_DAC_WRITE:
        case Command::I2C_ADC_READ:
        case Command::I2C_DAC_INIT:
            oss << "addr=0x" << std::hex << msg.addr
                << " value=0x" << std::hex << msg.value;
            break;

        case Command::SET_LOG_LEVEL:
            oss << "level=" << std::dec << msg.value;
            break;

        case Command::GET_PROTOCOL_VERSION:
            oss << "version="
                << protocolVersionMajor(msg.value)
                << "."
                << protocolVersionMinor(msg.value);
            break;

        case Command::HEARTBEAT:
            oss << "heartbeat";
            break;

        default:
            oss << "addr=0x" << std::hex << msg.addr
                << " value=0x" << std::hex << msg.value;
            break;
    }

    return oss.str();
}

} // namespace GermaniumProtocol
