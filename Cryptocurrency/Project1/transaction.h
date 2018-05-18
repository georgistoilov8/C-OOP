#pragma once

#ifndef _TRANSACTION_HEADER_INCLUDED_
#define _TRANSACTION_HEADER_INCLUDED_
#define TRANSACTION_PATH "transaction.dat"
#include "wallet.h"

struct Transaction {
	long long time;
	unsigned senderId;
	unsigned receiverId;
	double fmiCoins;
};

bool addTransaction(Wallet& wallet);

bool addTransaction(Wallet& receiver, Wallet& sender, double fmi_coins);

double walletFmiCoins(unsigned id);

unsigned countTransactions(unsigned id);

time_t timeTransaction(unsigned mode, unsigned id);

void printLastAddedTransaction();

void printTransaction(Transaction& transaction);

#endif //_TRANSACTION_HEADER_INCLUDED_
