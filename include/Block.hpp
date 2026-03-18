#pragma once

#include "Transaction.hpp"

#include <string>
#include <vector>
#include <cstdint>
#include <ctime>

class Block{
public:
	std::string prev_block_hash;
	std::string merkle_root;
	uint64_t timestamp;
	uint64_t nonce;

	std::string block_hash;
	std::vector<Transaction> transactions;

	Block(std::string prev_hash, std::vector<Transaction> txs);

	std::string getHash() const;

	static std::string calcMerkleRoot(const std::vector<Transaction>& txs);

	std::vector<std::string> getMerkleProof(const std::string& target_tx_hash) const;

	void mineblock(uint32_t difficulty);
};
