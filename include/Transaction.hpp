#pragma once

#include <string>
#include <vector>
#include <cstdint>

struct TxIn{
	std::string prev_tx_hash;
	uint32_t output_idx;
	std::string signature;
};

struct Txout{
	double amount;
	std::string to_adress;
};

class Transaction{
public:
	std::string tx_hash;
	std::vector<TxIn>inputs;
	std::vector<TxOut>outputs;

	Transaction() = default;
	Transaction(std::vector<TxIn> in, std::vector<TxOut> out);

	std::string getHash() const;
};
