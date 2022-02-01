#include <chrono>
#include <ctime>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

class Transaction {
public:
    std::string acc_nb;
    std::string fname;
    std::string lname;
    double amt;
    std::string merchant;
    time_t timestamp;
    Transaction(std::string acc_nb, std::string fname, std::string lname,
                double amt, std::string merchant, time_t timestamp)
            : acc_nb(acc_nb), fname(fname), lname(lname), amt(amt),
              merchant(merchant), timestamp(timestamp) {};
};

class TransactionList {
private:
    std::vector<Transaction> transactions;
    static std::vector<std::string> split(const std::string& s, char delimiter);
    static time_t create_time_t(const std::string& date, const std::string& time);

public:
    TransactionList();
    void parseFile(const std::string&);
    static Transaction parseRecord(const std::string& record_line);
    std::vector<Transaction>::iterator begin();
    std::vector<Transaction>::iterator end();
    TransactionList sort();
};

class TransactionRecComp {
public:
    bool operator()(const Transaction& a, const Transaction& b);
};


class display {
public:
    display(Transaction t) : obj{std::move(t)} {}
    std::ostream& operator()(std::ostream& os) const {
        struct tm * timeinfo;
        timeinfo = localtime ( &obj.timestamp );
        auto time_s = std::put_time(timeinfo, "%d.%m.%y;%H:%M:%S");

        os << std::setw(15) << std::right << "Account Nb: " << std::setw(50) << std::right << obj.acc_nb << std::endl;
        os << std::setw(15) << std::right << "First Name: " << std::setw(50) << std::right << obj.fname << std::endl;
        os << std::setw(15) << std::right << "Last Name: " << std::setw(50) << std::right << obj.lname << std::endl;
        os.imbue(std::locale("de_DE.UTF-8"));
        os << std::setw(15) << std::right << "Amount: " << std::setw(47) << std::right << std::put_money(obj.amt ) << std::setw(3) << "EUR" << std::endl;
        os << std::setw(15) << std::right << "Merchant: " << std::setw(50) << std::right << obj.merchant << std::endl;
        os << std::setw(15) << std::right << "Date Time: " << std::setw(33) << "" << time_s << std::endl;
        os.flush();
        return os;
    }
private:
    Transaction obj;
};

inline std::ostream& operator<<(std::ostream& os, const display& dp) {
    return dp(os);
}