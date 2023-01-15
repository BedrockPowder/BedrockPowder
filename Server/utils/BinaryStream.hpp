//
// Created by pepef on 24.07.2022.
//

#ifndef BEDROCKPOWDER_BINARYSTREAM_HPP
#define BEDROCKPOWDER_BINARYSTREAM_HPP

#include <utility>
#include <cstdint>
#include <cstdlib>

#include "Server/utils/StdEnv.h"

class BinaryStream {
public:
    explicit BinaryStream(const unsigned char* payload, const int offset = 0) {
        this->buffer = (int8_t*)payload;
        this->offset = offset;
    }

    int8_t* get_bytes(size_t count) {
        auto* result = (int8_t*) malloc(count);
        size_t i;
        for(i = 0; i < count; ++i) {
            result[i] = this->buffer[this->offset];
            ++this->offset;
        }
        return result;
    }

    int8_t* get_remaining_bytes() {
        return get_bytes(this->size - this->offset);
    }

    uint8_t get_unsigned_byte() {
        uint8_t value = ((uint8_t) (this->buffer[this->offset] & 0xff));
        ++this->offset;
        return value;
    }

    int8_t get_byte() {
        uint8_t raw = get_unsigned_byte();
        return *(int8_t*) &raw;
    }

    uint16_t get_unsigned_short_le() {
        uint16_t value = ((uint16_t) (this->buffer[this->offset] & 0xff));
        ++this->offset;
        value |= ((uint16_t) (this->buffer[this->offset] & 0xff)) << 8;
        ++this->offset;
        return value;
    }

    uint16_t get_unsigned_short_be() {
        uint16_t value = ((uint16_t) (this->buffer[this->offset] & 0xff)) << 8;
        ++this->offset;
        value |= ((uint16_t) (this->buffer[this->offset] & 0xff));
        ++this->offset;
        return value;
    }

    int16_t get_short_le() {
        uint16_t raw = get_unsigned_short_le();
        return *(int16_t*) &raw;
    }

    int16_t get_short_be() {
        uint16_t raw = get_unsigned_short_be();
        return *(int16_t*) &raw;
    }

    uint32_t get_unsigned_triad_le() {
        uint32_t value = ((uint32_t) this->buffer[this->offset] & 0xff);
        ++this->offset;
        value |= ((uint32_t) (this->buffer[this->offset] & 0xff)) << 8;
        ++this->offset;
        value |= ((uint32_t) (this->buffer[this->offset] & 0xff)) << 16;
        ++this->offset;
        return value;
    }

    uint32_t get_unsigned_triad_be() {
        uint32_t value = ((uint32_t) (this->buffer[this->offset] & 0xff)) << 16;
        ++this->offset;
        value |= ((uint32_t) (this->buffer[this->offset] & 0xff)) << 8;
        ++this->offset;
        value |= ((uint32_t) this->buffer[this->offset] & 0xff);
        ++this->offset;
        return value;
    }

    int32_t get_triad_le() {
        uint32_t raw = get_unsigned_triad_le();
        return *(int32_t*) &raw;
    }

    int32_t get_triad_be() {
        uint32_t raw = get_unsigned_triad_be();
        return *(int32_t*) &raw;
    }

    uint32_t get_unsigned_int_le() {
        uint32_t value = ((uint32_t) (this->buffer[this->offset] & 0xff));
        ++this->offset;
        value |= ((uint32_t) (this->buffer[this->offset] & 0xff)) << 8;
        ++this->offset;
        value |= ((uint32_t) (this->buffer[this->offset] & 0xff)) << 16;
        ++this->offset;
        value |= ((uint32_t) (this->buffer[this->offset] & 0xff)) << 24;
        ++this->offset;
        return value;
    }

    uint32_t get_unsigned_int_be() {
        uint32_t value = ((uint32_t) (this->buffer[this->offset] & 0xff)) << 24;
        ++this->offset;
        value |= ((uint32_t) (this->buffer[this->offset] & 0xff)) << 16;
        ++this->offset;
        value |= ((uint32_t) (this->buffer[this->offset] & 0xff)) << 8;
        ++this->offset;
        value |= ((uint32_t) (this->buffer[this->offset] & 0xff));
        ++this->offset;
        return value;
    }

    int32_t get_int_le() {
        uint32_t raw = get_unsigned_int_le();
        return *(int32_t*) &raw;
    }

    int32_t get_int_be() {
        uint32_t raw = get_unsigned_int_be();
        return *(int32_t*) &raw;
    }

    uint64_t get_unsigned_long_le() {
        uint64_t value = ((uint64_t) (this->buffer[this->offset] & 0xff));
        ++this->offset;
        value |= ((uint64_t) (this->buffer[this->offset] & 0xff)) << ((uint64_t) 8);
        ++this->offset;
        value |= ((uint64_t) (this->buffer[this->offset] & 0xff)) << ((uint64_t) 16);
        ++this->offset;
        value |= ((uint64_t) (this->buffer[this->offset] & 0xff)) << ((uint64_t) 24);
        ++this->offset;
        value |= ((uint64_t) (this->buffer[this->offset] & 0xff)) << ((uint64_t) 32);
        ++this->offset;
        value |= ((uint64_t) (this->buffer[this->offset] & 0xff)) << ((uint64_t) 40);
        ++this->offset;
        value |= ((uint64_t) (this->buffer[this->offset] & 0xff)) << ((uint64_t) 48);
        ++this->offset;
        value |= ((uint64_t) (this->buffer[this->offset] & 0xff)) << ((uint64_t) 56);
        ++this->offset;
        return value;
    }

    uint64_t get_unsigned_long_be() {
        uint64_t value = ((uint64_t) (this->buffer[this->offset] & 0xff)) << ((uint64_t) 56);
        ++this->offset;
        value |= ((uint64_t) (this->buffer[this->offset] & 0xff)) << ((uint64_t) 48);
        ++this->offset;
        value |= ((uint64_t) (this->buffer[this->offset] & 0xff)) << ((uint64_t) 40);
        ++this->offset;
        value |= ((uint64_t) (this->buffer[this->offset] & 0xff)) << ((uint64_t) 32);
        ++this->offset;
        value |= ((uint64_t) (this->buffer[this->offset] & 0xff)) << ((uint64_t) 24);
        ++this->offset;
        value |= ((uint64_t) (this->buffer[this->offset] & 0xff)) << ((uint64_t) 16);
        ++this->offset;
        value |= ((uint64_t) (this->buffer[this->offset] & 0xff)) << ((uint64_t) 8);
        ++this->offset;
        value |= ((uint64_t) (this->buffer[this->offset] & 0xff));
        ++this->offset;
        return value;
    }

    int64_t get_long_le() {
        uint64_t raw = get_unsigned_long_le();
        return *(int64_t*) &raw;
    }

    int64_t get_long_be() {
        uint64_t raw = get_unsigned_long_be();
        return *(int64_t*) &raw;
    }

    uint32_t get_var_int() {
        uint32_t value = 0;
        int i;
        for(i = 0; i < 35; i += 7) {
            uint8_t to_read = get_unsigned_byte();
            value |= ((to_read & 0x7f) << i);
            if((to_read & 0x80) == 0) {
                return value;
            }
        }
        return 0;
    }

    int32_t get_signed_var_int() {
        uint32_t raw = get_var_int();
        return (raw >> 1) ^ (-1 * (raw & 1));
    }

    uint64_t get_var_long() {
        uint64_t value = 0;
        int i;
        for(i = 0; i < 70; i += 7) {
            uint8_t to_read = get_unsigned_byte();
            value |= (((uint64_t) (to_read & 0x7f)) << ((uint64_t) i));
            if((to_read & 0x80) == 0) {
                return value;
            }
        }
        return 0;
    }

    int64_t get_signed_var_long() {
        uint64_t raw = get_var_long();
        return ((int64_t) (raw >> 1)) ^ (-1 * ((int64_t) (raw & 1)));
    }

    float get_float_le() {
        uint32_t i = get_unsigned_int_le();
        float f;
        memcpy(&f, &i, sizeof(f));
        return f;
    }

    float get_float_be() {
        uint32_t i = get_unsigned_int_be();
        float f;
        memcpy(&f, &i, sizeof(f));
        return f;
    }

    double get_double_le() {
        uint64_t l = get_unsigned_long_le();
        double f;
        memcpy(&f, &l, sizeof(f));
        return f;
    }

    double get_double_be() {
        uint64_t l = get_unsigned_long_be();
        double f;
        memcpy(&f, &l, sizeof(f));
        return f;
    }

    void put_bytes(const int8_t* data, size_t size_) {
        size_t i;
        this->buffer = (int8_t*) realloc(this->buffer, sizeof(this->buffer + size_));
        for(i = 0; i < size_; ++i) {
            this->buffer[this->size] = data[i];
            ++this->size;
        }
    }

    void put_unsigned_byte(uint8_t value) {
        this->buffer = (int8_t*) realloc(this->buffer, sizeof(this->buffer + 1));
        this->buffer[this->size] = value & 0xff;
        ++this->size;
    }

    void put_byte(int8_t value) {
        put_unsigned_byte(value & 0xff);
    }

    void put_unsigned_short_le(uint16_t value) {
        this->buffer = (int8_t*) realloc(this->buffer, sizeof(this->buffer + 2));
        this->buffer[this->size] = value & 0xff;
        ++this->size;
        this->buffer[this->size] = (value >> 8) & 0xff;
        ++this->size;
    }

    void put_unsigned_short_be(uint16_t value) {
        this->buffer = (int8_t*) realloc(this->buffer, sizeof(this->buffer + 2));
        this->buffer[this->size] = (value >> 8) & 0xff;
        ++this->size;
        this->buffer[this->size] = value & 0xff;
        ++this->size;
    }

    void put_short_le(int16_t value) {
        put_unsigned_short_le(value & 0xffff);
    }

    void put_short_be(int16_t value) {
        put_unsigned_short_be(value & 0xffff);
    }

    void put_unsigned_triad_le(uint32_t value) {
        this->buffer = (int8_t*) realloc(this->buffer, sizeof(this->buffer + 3));
        this->buffer[this->size] = value & 0xff;
        ++this->size;
        this->buffer[this->size] = (value >> 8) & 0xff;
        ++this->size;
        this->buffer[this->size] = (value >> 16) & 0xff;
        ++this->size;
    }

    void put_unsigned_triad_be(uint32_t value) {
        this->buffer = (int8_t*) realloc(this->buffer, sizeof(this->buffer + 3));
        this->buffer[this->size] = (value >> 16) & 0xff;
        ++this->size;
        this->buffer[this->size] = (value >> 8) & 0xff;
        ++this->size;
        this->buffer[this->size] = value & 0xff;
        ++this->size;
    }

    void put_triad_le(int32_t value) {
        put_unsigned_triad_le(value & 0xffffff);
    }

    void put_triad_be(int32_t value) {
        put_unsigned_triad_be(value & 0xffffff);
    }

    void put_unsigned_int_le(uint32_t value) {
        this->buffer = (int8_t*) realloc(this->buffer, sizeof(this->buffer + 4));
        this->buffer[this->size] = value & 0xff;
        ++this->size;
        this->buffer[this->size] = (value >> 8) & 0xff;
        ++this->size;
        this->buffer[this->size] = (value >> 16) & 0xff;
        ++this->size;
        this->buffer[this->size] = (value >> 24) & 0xff;
        ++this->size;
    }

    void put_unsigned_int_be(uint32_t value) {
        this->buffer = (int8_t*) sizeof(this->buffer + 4);
        this->buffer[this->size] = (value >> 24) & 0xff;
        ++this->size;
        this->buffer[this->size] = (value >> 16) & 0xff;
        ++this->size;
        this->buffer[this->size] = (value >> 8) & 0xff;
        ++this->size;
        this->buffer[this->size] = value & 0xff;
        ++this->size;
    }

    void put_int_le(int32_t value) {
        put_unsigned_int_le(value & 0xffffffff);
    }

    void put_int_be(int32_t value) {
        put_unsigned_int_be(value & 0xffffffff);
    }

    void put_unsigned_long_le(uint64_t value) {
        this->buffer = (int8_t*) realloc(this->buffer, sizeof(this->buffer + 8));
        this->buffer[this->size] = value & 0xff;
        ++this->size;
        this->buffer[this->size] = (value >> 8) & 0xff;
        ++this->size;
        this->buffer[this->size] = (value >> 16) & 0xff;
        ++this->size;
        this->buffer[this->size] = (value >> 24) & 0xff;
        ++this->size;
        this->buffer[this->size] = (value >> 32) & 0xff;
        ++this->size;
        this->buffer[this->size] = (value >> 40) & 0xff;
        ++this->size;
        this->buffer[this->size] = (value >> 48) & 0xff;
        ++this->size;
        this->buffer[this->size] = (value >> 56) & 0xff;
        ++this->size;
    }

    void put_unsigned_long_be(uint64_t value) {
        this->buffer = (int8_t*) realloc(this->buffer, sizeof(this->buffer + 8));
        this->buffer[this->size] = (value >> 56) & 0xff;
        ++this->size;
        this->buffer[this->size] = (value >> 48) & 0xff;
        ++this->size;
        this->buffer[this->size] = (value >> 40) & 0xff;
        ++this->size;
        this->buffer[this->size] = (value >> 32) & 0xff;
        ++this->size;
        this->buffer[this->size] = (value >> 24) & 0xff;
        ++this->size;
        this->buffer[this->size] = (value >> 16) & 0xff;
        ++this->size;
        this->buffer[this->size] = (value >> 8) & 0xff;
        ++this->size;
        this->buffer[this->size] = value & 0xff;
        ++this->size;
    }

    void put_long_le(int64_t value) {
        put_unsigned_long_le(value & 0xffffffffffffffff);
    }

    void put_long_be(int64_t value) {
        put_unsigned_long_be(value & 0xffffffffffffffff);
    }

    void put_var_int(uint32_t value) {
        value &= 0xffffffff;
        int i;
        for(i = 0; i < 5; ++i) {
            uint8_t to_write = value & 0x7f;
            value >>= 7;
            this->buffer = (int8_t*) realloc(this->buffer, sizeof(this->buffer + 1));
            if(value != 0) {
                this->buffer[this->size] = (to_write | 0x80);
                ++this->size;
            } else {
                this->buffer[this->size] = to_write;
                ++this->size;
                break;
            }
        }
    }

    void put_signed_var_int(int32_t value) {
        put_var_int(value >= 0 ? (((uint32_t) value) << 1) : ((((uint32_t) (-1 - value)) << 1) | 0x01));
    }

    void put_var_long(uint64_t value) {
        value &= 0xffffffffffffffff;
        int i;
        for(i = 0; i < 10; ++i) {
            uint8_t to_write = value & 0x7f;
            value >>= 7;
            this->buffer = (int8_t*) realloc(this->buffer, sizeof(this->buffer + size));
            if(value != 0) {
                this->buffer[this->size] = (to_write | 0x80);
                ++this->size;
            } else {
                this->buffer[this->size] = to_write;
                ++this->size;
                break;
            }
        }
    }

    void put_signed_var_long(int64_t value) {
        put_var_long(value >= 0 ? (((uint64_t) value) << 1) : ((((uint64_t) (-1 - value)) << 1) | 0x01));
    }

    void put_float_le(float value) {
        uint32_t i;
        memcpy(&i, &value, sizeof(i));
        put_unsigned_int_le(i);
    }

    void put_float_be(float value) {
        uint32_t i;
        memcpy(&i, &value, sizeof(i));
        put_unsigned_int_be(i);
    }

    void put_double_le(double value) {
        uint64_t l;
        memcpy(&l, &value, sizeof(l));
        put_unsigned_long_le(l);
    }

    void put_double_be(double value) {
        uint64_t l;
        memcpy(&l, &value, sizeof(l));
        put_unsigned_long_be(l);
    }

    int8_t* buffer;
    size_t size;
    size_t offset;
};

#endif //BEDROCKPOWDER_BINARYSTREAM_HPP
