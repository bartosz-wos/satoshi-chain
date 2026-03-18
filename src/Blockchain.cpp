#include "../include/Blockchain.hpp"
#include "../include/SHA256.hpp"
#include <iostream>
#include <sstream>

Blockchain::Blockchain(uint32_t difficulty) : difficulty(difficulty){
	std::cout << "block init, block 0\n";

	std::vector<Transaction> txs;
	std::string prev_hash(64, '0');

	Block genesis(prev_hash, std::move(txs));
	genesis.mineblock(difficulty);
	chain.push_back(std::move(genesis));
}

const Block& Blockchain::getLastBlock() const{
	return chain.back();
}

void Blockchain::addBlock(Block new_block){
	new_block.prev_block_hash = getLastBlock().block_hash;

	std::cout << "mining block nr " << chain.size() << std::endl;
	
	new_block.mineblock(difficulty);
	chain.push_back(std::move(new_block));
}

bool Blockchain::isValid() const{
	for(size_t i = 1; i < chain.size(); ++i){
		const Block& cur = chain[i];
		const Block& prev = chain[i - 1];

		if(cur.prev_block_hash != prev.block_hash){
			std::cout << "block broke!!!";
			return 0;
		}

		std::string calc_merkle = Block::calcMerkleRoot(cur.transactions);

		if(calc_merkle != cur.merkle_root){
			std::cout << "merkle root is wrong" << std::endl;
			return 0;
		}
		if(cur.block_hash != cur.getHash()){
			std::cout << "hash doesnt match!!!";
			return 0;
		}
	}
	return 1;
}
