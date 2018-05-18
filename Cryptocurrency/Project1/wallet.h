#pragma once

#ifndef _WALLET_HEADER_INCLUDED_
#define _WALLET_HEADER_INCLUDED_
#define WALLET_PATH "wallet.dat"

struct Wallet {
	char owner[256];
	unsigned id;
	double fiatMoney;
};

bool addWallet();

void returnWalletId(Wallet& wallet);

bool getWallet(unsigned id, Wallet& wallet);

//bool binarySearch(std::ifstream& file, Wallet& wallet, unsigned id);

bool search(std::ifstream& file, Wallet& wallet, unsigned id);

bool isWalletContained(unsigned id);

double walletFiatMoney(unsigned id);

bool changeFiatMoney(Wallet& wallet);

void topWealthiest();

void change(Wallet& old_wallet, Wallet& new_wallet);

void walletInfo(unsigned id);

bool printLastAddedWallet();

void printAllWallets();

void printWallet(Wallet& wallet);

#endif //_WALLET_HEADER_INCLUDED_
