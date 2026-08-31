#pragma once
#include <AP_Common/AP_Common.h>
#include <AP_HAL/AP_HAL.h>

#if defined(HAL_WITH_PAGE_EEPROM) &&  HAL_WITH_PAGE_EEPROM

class AP_PageEEPROM {
public:

    bool init(void);

    uint32_t get_size(void) const {return (id == UINT8_MAX) ? 0 : pg_eeprom_ids[id].size_kbyte * 1024UL;}

    bool read (uint32_t offset, uint8_t * const buf, uint32_t size);

    bool write (uint32_t offset, uint8_t const * const  buf, uint32_t);

private:

    AP_HAL::SPIDevice *dev;
    AP_HAL::Semaphore *dev_sem;

    enum class RDID_type : uint8_t {
        ST
    };

    struct pg_eeprom_id {
        uint8_t  id1;
        uint8_t  id2;
        uint16_t size_kbyte;
        uint16_t size_page_byte;
        uint8_t  addrlen;
        RDID_type rdid_type;
    };

    static const struct pg_eeprom_id pg_eeprom_ids[];
    uint8_t id = UINT8_MAX;
    
    bool _init(void);
    bool _read(uint32_t offset, uint8_t * const buf, uint32_t size);
    void send_offset(uint8_t cmd, uint32_t offset) const;

    void WriteEnable(void);
    uint8_t ReadStatusReg(void);

    bool Busy(void);
    void WaitReady(void);

};

#endif //HAL_WITH_PAGE_EEPROM