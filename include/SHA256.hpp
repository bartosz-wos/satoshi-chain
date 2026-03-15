#pragma once

#include <cstdint>
#include <string>
#include <cstddef>

class SHA256{
private:
	uint32_t state[8];
	uint64_t bit_len;
	uint32_t data_len;
	uint8_t data[64];

	void transform();
public:
	SHA256();
	void update(const uint8_t* data_in, size_t length);
	void update(const std::string& data_in);
	std::string digest();
};
