#pragma once

#include "Block.hpp"
#include <vector>
#include <cstdint>

class Blockchain{
public:
	std::vector<Block> chain;
	uint32_t difficulty;

public:
	Blockchain(uint32_t difficulty);
	const Block& getLastBlock() const;
	void addBlock(Block new_block);
	bool isValid() const;
};
