#include "../include/Block.hpp"
#include "../include/SHA256.hpp"
#include <sstream>
#include <iostream>
#include <chrono>

Block::Block(std::string prev_hash, std::vector<Transaction> txs) : prev_block_hash(std::move(prev_hash)), transactions(std::move(txs)){
	auto t = std::chrono::system_clock::now();
	timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(t.time_since_epoch()).count();
	nonce = 0;

	merkle_root = calcMerkleRoot(transactions);
	block_hash = getHash();
}

std::string Block::calcMerkleRoot(const std::vector<Transaction>& txs){
	if(txs.empty())return std::string(64, '0');
	std::vector<std::string> merkle_tree;
	for(const auto& tx : txs)
		merkle_tree.push_back(tx.getHash());

	while(merkle_tree.size() > 1){
		if(merkle_tree.size() & 1)
			merkle_tree.push_back(merkle_tree.back());
		std::vector<std::string> level;
		for(size_t i = 0; i < merkle_tree.size(); i += 2){
			SHA256 sha;
			sha.update(merkle_tree[i] + merkle_tree[i + 1]);
			level.push_back(sha.digest());
		}
		merkle_tree = level;
	}
	return merkle_tree[0];
}

std::vector<std::string> Block::getMerkleProof(const std::string& target_tx_hash) const{
	std::vector<std::string> proof, cur_level;

	int target_idx = -1;
	for(size_t i = 0; i < transactions.size(); ++i){
		cur_level.push_back(transactions[i].getHash());
		if(cur_level.back() == target_tx_hash)
			target_idx = i;
	}

	if(target_idx == -1)
		return proof;

	while(cur_level.size() > 1){
		if(cur_level.size() & 1)
			cur_level.push_back(cur_level.back());

		std::vector<std::string> nxt_level;
		if(target_idx & 1)
			proof.push_back(cur_level[target_idx - 1]);
		else
			proof.push_back(cur_level[target_idx + 1]);

		for(size_t i = 0; i < cur_level.size(); i += 2){
			SHA256 sha;
			sha.update(cur_level[i] + cur_level[i + 1]);
			nxt_level.push_back(sha.digest());
		}
		cur_level.swap(nxt_level);
		target_idx >>= 1;
	}
	return proof;
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
