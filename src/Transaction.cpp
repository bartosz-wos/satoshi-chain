#include "../include/Transaction.hpp"
#include "../include/SHA256.hpp"
#include <sstream>

Transaction::Transaction(std::vector<TxIn> in, std::vector<TxOut> out) : inputs(std::move(in)), outputs(std::move(out)){
        tx_hash = getHash();
}

std::string Transaction::getHash() const{
        std::stringstream ss;
        for(const auto& in : inputs)
                ss << in.prev_tx_hash << in.output_idx << in.signature;
        for(const auto& : outputs)
                ss << out.amount << out.to_adress;
        SHA256 sha;
        sha.update(ss.str());
        return sha.digest();
}
