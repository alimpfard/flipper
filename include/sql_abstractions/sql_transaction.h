#pragma once

#include <QReadWriteLock>
#include <set>
#include "sql_abstractions/sql_database.h"

namespace sql{
class Transaction{
public:
    Transaction(Database);
    Transaction(const Transaction&) = default;
    ~Transaction() = default;
    bool start();
    bool cancel();
    bool finalize();
    Database db;
    bool isOpen = false;
    static QReadWriteLock lock;
    static std::set<std::string> transactionSet;
};
}
