#include "led_controller.h"

#include <avr/io.h>
#include <avr/pgmspace.h>

static constexpr uint16_t INTENSITY = 0x60;
static const uint8_t lookup_table[256] PROGMEM =
{
    (0x00 * INTENSITY) / 0xFF,
    (0x01 * INTENSITY) / 0xFF,
    (0x02 * INTENSITY) / 0xFF,
    (0x03 * INTENSITY) / 0xFF,
    (0x04 * INTENSITY) / 0xFF,
    (0x05 * INTENSITY) / 0xFF,
    (0x06 * INTENSITY) / 0xFF,
    (0x07 * INTENSITY) / 0xFF,
    (0x08 * INTENSITY) / 0xFF,
    (0x09 * INTENSITY) / 0xFF,
    (0x0A * INTENSITY) / 0xFF,
    (0x0B * INTENSITY) / 0xFF,
    (0x0C * INTENSITY) / 0xFF,
    (0x0D * INTENSITY) / 0xFF,
    (0x0E * INTENSITY) / 0xFF,
    (0x0F * INTENSITY) / 0xFF,

    (0x10 * INTENSITY) / 0xFF,
    (0x11 * INTENSITY) / 0xFF,
    (0x12 * INTENSITY) / 0xFF,
    (0x13 * INTENSITY) / 0xFF,
    (0x14 * INTENSITY) / 0xFF,
    (0x15 * INTENSITY) / 0xFF,
    (0x16 * INTENSITY) / 0xFF,
    (0x17 * INTENSITY) / 0xFF,
    (0x18 * INTENSITY) / 0xFF,
    (0x19 * INTENSITY) / 0xFF,
    (0x1A * INTENSITY) / 0xFF,
    (0x1B * INTENSITY) / 0xFF,
    (0x1C * INTENSITY) / 0xFF,
    (0x1D * INTENSITY) / 0xFF,
    (0x1E * INTENSITY) / 0xFF,
    (0x1F * INTENSITY) / 0xFF,

    (0x20 * INTENSITY) / 0xFF,
    (0x21 * INTENSITY) / 0xFF,
    (0x22 * INTENSITY) / 0xFF,
    (0x23 * INTENSITY) / 0xFF,
    (0x24 * INTENSITY) / 0xFF,
    (0x25 * INTENSITY) / 0xFF,
    (0x26 * INTENSITY) / 0xFF,
    (0x27 * INTENSITY) / 0xFF,
    (0x28 * INTENSITY) / 0xFF,
    (0x29 * INTENSITY) / 0xFF,
    (0x2A * INTENSITY) / 0xFF,
    (0x2B * INTENSITY) / 0xFF,
    (0x2C * INTENSITY) / 0xFF,
    (0x2D * INTENSITY) / 0xFF,
    (0x2E * INTENSITY) / 0xFF,
    (0x2F * INTENSITY) / 0xFF,

    (0x30 * INTENSITY) / 0xFF,
    (0x31 * INTENSITY) / 0xFF,
    (0x32 * INTENSITY) / 0xFF,
    (0x33 * INTENSITY) / 0xFF,
    (0x34 * INTENSITY) / 0xFF,
    (0x35 * INTENSITY) / 0xFF,
    (0x36 * INTENSITY) / 0xFF,
    (0x37 * INTENSITY) / 0xFF,
    (0x38 * INTENSITY) / 0xFF,
    (0x39 * INTENSITY) / 0xFF,
    (0x3A * INTENSITY) / 0xFF,
    (0x3B * INTENSITY) / 0xFF,
    (0x3C * INTENSITY) / 0xFF,
    (0x3D * INTENSITY) / 0xFF,
    (0x3E * INTENSITY) / 0xFF,
    (0x3F * INTENSITY) / 0xFF,

    (0x40 * INTENSITY) / 0xFF,
    (0x41 * INTENSITY) / 0xFF,
    (0x42 * INTENSITY) / 0xFF,
    (0x43 * INTENSITY) / 0xFF,
    (0x44 * INTENSITY) / 0xFF,
    (0x45 * INTENSITY) / 0xFF,
    (0x46 * INTENSITY) / 0xFF,
    (0x47 * INTENSITY) / 0xFF,
    (0x48 * INTENSITY) / 0xFF,
    (0x49 * INTENSITY) / 0xFF,
    (0x4A * INTENSITY) / 0xFF,
    (0x4B * INTENSITY) / 0xFF,
    (0x4C * INTENSITY) / 0xFF,
    (0x4D * INTENSITY) / 0xFF,
    (0x4E * INTENSITY) / 0xFF,
    (0x4F * INTENSITY) / 0xFF,

    (0x50 * INTENSITY) / 0xFF,
    (0x51 * INTENSITY) / 0xFF,
    (0x52 * INTENSITY) / 0xFF,
    (0x53 * INTENSITY) / 0xFF,
    (0x54 * INTENSITY) / 0xFF,
    (0x55 * INTENSITY) / 0xFF,
    (0x56 * INTENSITY) / 0xFF,
    (0x57 * INTENSITY) / 0xFF,
    (0x58 * INTENSITY) / 0xFF,
    (0x59 * INTENSITY) / 0xFF,
    (0x5A * INTENSITY) / 0xFF,
    (0x5B * INTENSITY) / 0xFF,
    (0x5C * INTENSITY) / 0xFF,
    (0x5D * INTENSITY) / 0xFF,
    (0x5E * INTENSITY) / 0xFF,
    (0x5F * INTENSITY) / 0xFF,

    (0x60 * INTENSITY) / 0xFF,
    (0x61 * INTENSITY) / 0xFF,
    (0x62 * INTENSITY) / 0xFF,
    (0x63 * INTENSITY) / 0xFF,
    (0x64 * INTENSITY) / 0xFF,
    (0x65 * INTENSITY) / 0xFF,
    (0x66 * INTENSITY) / 0xFF,
    (0x67 * INTENSITY) / 0xFF,
    (0x68 * INTENSITY) / 0xFF,
    (0x69 * INTENSITY) / 0xFF,
    (0x6A * INTENSITY) / 0xFF,
    (0x6B * INTENSITY) / 0xFF,
    (0x6C * INTENSITY) / 0xFF,
    (0x6D * INTENSITY) / 0xFF,
    (0x6E * INTENSITY) / 0xFF,
    (0x6F * INTENSITY) / 0xFF,

    (0x70 * INTENSITY) / 0xFF,
    (0x71 * INTENSITY) / 0xFF,
    (0x72 * INTENSITY) / 0xFF,
    (0x73 * INTENSITY) / 0xFF,
    (0x74 * INTENSITY) / 0xFF,
    (0x75 * INTENSITY) / 0xFF,
    (0x76 * INTENSITY) / 0xFF,
    (0x77 * INTENSITY) / 0xFF,
    (0x78 * INTENSITY) / 0xFF,
    (0x79 * INTENSITY) / 0xFF,
    (0x7A * INTENSITY) / 0xFF,
    (0x7B * INTENSITY) / 0xFF,
    (0x7C * INTENSITY) / 0xFF,
    (0x7D * INTENSITY) / 0xFF,
    (0x7E * INTENSITY) / 0xFF,
    (0x7F * INTENSITY) / 0xFF,

    (0x80 * INTENSITY) / 0xFF,
    (0x81 * INTENSITY) / 0xFF,
    (0x82 * INTENSITY) / 0xFF,
    (0x83 * INTENSITY) / 0xFF,
    (0x84 * INTENSITY) / 0xFF,
    (0x85 * INTENSITY) / 0xFF,
    (0x86 * INTENSITY) / 0xFF,
    (0x87 * INTENSITY) / 0xFF,
    (0x88 * INTENSITY) / 0xFF,
    (0x89 * INTENSITY) / 0xFF,
    (0x8A * INTENSITY) / 0xFF,
    (0x8B * INTENSITY) / 0xFF,
    (0x8C * INTENSITY) / 0xFF,
    (0x8D * INTENSITY) / 0xFF,
    (0x8E * INTENSITY) / 0xFF,
    (0x8F * INTENSITY) / 0xFF,

    (0x90 * INTENSITY) / 0xFF,
    (0x91 * INTENSITY) / 0xFF,
    (0x92 * INTENSITY) / 0xFF,
    (0x93 * INTENSITY) / 0xFF,
    (0x94 * INTENSITY) / 0xFF,
    (0x95 * INTENSITY) / 0xFF,
    (0x96 * INTENSITY) / 0xFF,
    (0x97 * INTENSITY) / 0xFF,
    (0x98 * INTENSITY) / 0xFF,
    (0x99 * INTENSITY) / 0xFF,
    (0x9A * INTENSITY) / 0xFF,
    (0x9B * INTENSITY) / 0xFF,
    (0x9C * INTENSITY) / 0xFF,
    (0x9D * INTENSITY) / 0xFF,
    (0x9E * INTENSITY) / 0xFF,
    (0x9F * INTENSITY) / 0xFF,

    (0xA0 * INTENSITY) / 0xFF,
    (0xA1 * INTENSITY) / 0xFF,
    (0xA2 * INTENSITY) / 0xFF,
    (0xA3 * INTENSITY) / 0xFF,
    (0xA4 * INTENSITY) / 0xFF,
    (0xA5 * INTENSITY) / 0xFF,
    (0xA6 * INTENSITY) / 0xFF,
    (0xA7 * INTENSITY) / 0xFF,
    (0xA8 * INTENSITY) / 0xFF,
    (0xA9 * INTENSITY) / 0xFF,
    (0xAA * INTENSITY) / 0xFF,
    (0xAB * INTENSITY) / 0xFF,
    (0xAC * INTENSITY) / 0xFF,
    (0xAD * INTENSITY) / 0xFF,
    (0xAE * INTENSITY) / 0xFF,
    (0xAF * INTENSITY) / 0xFF,

    (0xB0 * INTENSITY) / 0xFF,
    (0xB1 * INTENSITY) / 0xFF,
    (0xB2 * INTENSITY) / 0xFF,
    (0xB3 * INTENSITY) / 0xFF,
    (0xB4 * INTENSITY) / 0xFF,
    (0xB5 * INTENSITY) / 0xFF,
    (0xB6 * INTENSITY) / 0xFF,
    (0xB7 * INTENSITY) / 0xFF,
    (0xB8 * INTENSITY) / 0xFF,
    (0xB9 * INTENSITY) / 0xFF,
    (0xBA * INTENSITY) / 0xFF,
    (0xBB * INTENSITY) / 0xFF,
    (0xBC * INTENSITY) / 0xFF,
    (0xBD * INTENSITY) / 0xFF,
    (0xBE * INTENSITY) / 0xFF,
    (0xBF * INTENSITY) / 0xFF,

    (0xC0 * INTENSITY) / 0xFF,
    (0xC1 * INTENSITY) / 0xFF,
    (0xC2 * INTENSITY) / 0xFF,
    (0xC3 * INTENSITY) / 0xFF,
    (0xC4 * INTENSITY) / 0xFF,
    (0xC5 * INTENSITY) / 0xFF,
    (0xC6 * INTENSITY) / 0xFF,
    (0xC7 * INTENSITY) / 0xFF,
    (0xC8 * INTENSITY) / 0xFF,
    (0xC9 * INTENSITY) / 0xFF,
    (0xCA * INTENSITY) / 0xFF,
    (0xCB * INTENSITY) / 0xFF,
    (0xCC * INTENSITY) / 0xFF,
    (0xCD * INTENSITY) / 0xFF,
    (0xCE * INTENSITY) / 0xFF,
    (0xCF * INTENSITY) / 0xFF,

    (0xD0 * INTENSITY) / 0xFF,
    (0xD1 * INTENSITY) / 0xFF,
    (0xD2 * INTENSITY) / 0xFF,
    (0xD3 * INTENSITY) / 0xFF,
    (0xD4 * INTENSITY) / 0xFF,
    (0xD5 * INTENSITY) / 0xFF,
    (0xD6 * INTENSITY) / 0xFF,
    (0xD7 * INTENSITY) / 0xFF,
    (0xD8 * INTENSITY) / 0xFF,
    (0xD9 * INTENSITY) / 0xFF,
    (0xDA * INTENSITY) / 0xFF,
    (0xDB * INTENSITY) / 0xFF,
    (0xDC * INTENSITY) / 0xFF,
    (0xDD * INTENSITY) / 0xFF,
    (0xDE * INTENSITY) / 0xFF,
    (0xDF * INTENSITY) / 0xFF,

    (0xE0 * INTENSITY) / 0xFF,
    (0xE1 * INTENSITY) / 0xFF,
    (0xE2 * INTENSITY) / 0xFF,
    (0xE3 * INTENSITY) / 0xFF,
    (0xE4 * INTENSITY) / 0xFF,
    (0xE5 * INTENSITY) / 0xFF,
    (0xE6 * INTENSITY) / 0xFF,
    (0xE7 * INTENSITY) / 0xFF,
    (0xE8 * INTENSITY) / 0xFF,
    (0xE9 * INTENSITY) / 0xFF,
    (0xEA * INTENSITY) / 0xFF,
    (0xEB * INTENSITY) / 0xFF,
    (0xEC * INTENSITY) / 0xFF,
    (0xED * INTENSITY) / 0xFF,
    (0xEE * INTENSITY) / 0xFF,
    (0xEF * INTENSITY) / 0xFF,

    (0xF0 * INTENSITY) / 0xFF,
    (0xF1 * INTENSITY) / 0xFF,
    (0xF2 * INTENSITY) / 0xFF,
    (0xF3 * INTENSITY) / 0xFF,
    (0xF4 * INTENSITY) / 0xFF,
    (0xF5 * INTENSITY) / 0xFF,
    (0xF6 * INTENSITY) / 0xFF,
    (0xF7 * INTENSITY) / 0xFF,
    (0xF8 * INTENSITY) / 0xFF,
    (0xF9 * INTENSITY) / 0xFF,
    (0xFA * INTENSITY) / 0xFF,
    (0xFB * INTENSITY) / 0xFF,
    (0xFC * INTENSITY) / 0xFF,
    (0xFD * INTENSITY) / 0xFF,
    (0xFE * INTENSITY) / 0xFF,
    (0xFF * INTENSITY) / 0xFF,
};

static constexpr uint8_t ZERO_BIT_PULSE_LENGTH = 1;
static constexpr uint8_t ONE_BIT_PULSE_LENGTH = 3;


void LedController::initialize()
{
    // Set output direction to PB2
    PORTB &= ~((1 << DDB2));
    DDRB |= ((1 << DDB2));
}

void LedController::update(const AbstractLedStrip * led_strip)
{
    const uint8_t * data = reinterpret_cast<const uint8_t *>(&led_strip->leds);
    const uint8_t * data_end =
            reinterpret_cast<const uint8_t *>(&led_strip->leds) +
            (led_strip->led_count * sizeof(LedState));

    {
        uint16_t tmp_w;
        uint8_t current_byte;
        uint8_t bit_position;
        uint8_t pulse_length;
        uint8_t old_sreg;

        asm volatile (
                "    rjmp  lu_check_all_sent           \n"
                "lu_send_byte:                         \n"
                "    ld    %[current_byte], %a[data]+  \n"
                // Do the lookup table correction
                "    movw  %[tmp_w], %[lookup_table]   \n"
                "    add   %A[tmp_w], %[current_byte]  \n"
                "    adc   %B[tmp_w], __zero_reg__     \n"
                "    lpm   %[current_byte], %a[tmp_w]  \n"

                "    ldi   %[bit_position], 0x80       \n"

                "lu_send_bit:                          \n"
                "    ldi   %[pulse_length], %[zero_pl] \n"
                "    lsl   %[current_byte]             \n"
                "    brcc  lu_pulse_start              \n"
                "    ldi   %[pulse_length], %[one_pl]  \n"

                "lu_pulse_start:                       \n"
                "    in %[old_sreg], __SREG__          \n"
                "    cli                               \n"
                "    sbi   %[pinr], %[pinb]            \n"

                "lu_wait_pulse_end:                    \n"
                "    subi  %[pulse_length], 1          \n"
                "    brne  lu_wait_pulse_end           \n"
                "    sbi   %[pinr], %[pinb]            \n"
                "    out   __SREG__, %[old_sreg]       \n"

                "lu_check_byte_sent:                   \n"
                "    lsr   %[bit_position]             \n"
                "    brne  lu_send_bit                 \n"

                "lu_check_all_sent:                    \n"
                "    cp    %A[data], %A[data_end]      \n"
                "    cpc   %B[data], %B[data_end]      \n"
                "    brne  lu_send_byte               \n"
                : [current_byte] "=&r" (current_byte),
                  [old_sreg] "=&r" (old_sreg),
                  [bit_position] "=&d" (bit_position),
                  [pulse_length] "=&d" (pulse_length),
                  [tmp_w] "=&z" (tmp_w)
                : [data] "e" (data),
                  [data_end] "e" (data_end),
                  [lookup_table] "w" (lookup_table),
                  [zero_pl] "M" (ZERO_BIT_PULSE_LENGTH),
                  [one_pl] "M" (ONE_BIT_PULSE_LENGTH),
                  [pinr] "I" (_SFR_IO_ADDR(PINB)),
                  [pinb] "I" (PINB2)
        );
    }
}
