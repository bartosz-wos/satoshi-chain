#include "../include/Block.hpp"
#include "../include/SHA256.hpp"
#include <sstream>
#include <iostream>
#include <chrono>

Block::Block(std::string prev_hash, std::vector<Transaction> txs) : prev_block_hash(std::move(prev_hash)), transactions(std::move(txs)){
	auto t = std::chrono::system_clock::now();
	timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(t.time_since_epoch()).count();
	nonce = 0;

	std::stringstream ss;
	for(const auto& tx : transactions)
		ss << tx.tx_hash;
	SHA256 sha;
	sha.update(ss.str());
	merkle_root = sha.digest();

	block_hash = getHash();
}

std::string Block::getHash() const{
	std::stringstream ss;
	ss << prev_block_hash << timestamp << merkle_root << nonce;

	SHA256 sha;
	sha.update(ss.str());
	return sha.digest();
}

void Block::mineblock(uint32_t difficulty){
	std::string pref(difficulty, '0');

	while(block_hash.substr(0, difficulty) != pref){
		++nonce;
		block_hash = getHash();
	}

	std::cout << "block mined, hash: " << block_hash << "nonce: " << nonce << std::endl;
}
