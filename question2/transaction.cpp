#include "transaction.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <algorithm>

TransactionList::TransactionList() {

}

void TransactionList::parseFile(const std::string& filename) {
    std::ifstream filestream(filename);
    if(!filestream) {
        throw std::ifstream::failure("Can't open a file!");
    }
    transactions.clear();
    for (std::string line; std::getline(filestream, line);) {
        std::cout << line << std::endl;
        transactions.push_back(parseRecord(line));
    }
}

Transaction TransactionList::parseRecord(const std::string& record_line) {
    std::vector<std::string> tokens = split(record_line, '|');
    Transaction record(tokens[0], tokens[1], tokens[2], std::stod(tokens[3]), tokens[4], create_time_t(tokens[5], tokens[6]));
    return record;
}

std::vector<std::string> TransactionList::split(const std::string &s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

time_t TransactionList::create_time_t(const std::string &date, const std::string &time) {
    struct std::tm tm{};
    std::istringstream ss(date + " " + time);
    ss >> std::get_time(&tm, "%d.%m.%Y %H:%M:%S");
    return mktime(&tm);
}

std::vector<Transaction>::iterator TransactionList::begin() {
    return transactions.begin();
}

std::vector<Transaction>::iterator TransactionList::end() {
    return transactions.end();
}

TransactionList TransactionList::sort() {
    TransactionRecComp comp;
    std::sort(begin(), end(), comp);
    return *this;
}

bool TransactionRecComp::operator()(const Transaction &a, const Transaction &b) {
    return a.acc_nb.compare(b.acc_nb) <= 0;
}

int main()
{
    TransactionList tl;
    tl.parseFile("/home/studone/PassauOOP/passau-cplusplus-oop/question2/transactions.txt");
    tl.sort();
    Transaction t = *tl.begin();
    std::cout << display(t) << std::endl;
    return 0;
}



