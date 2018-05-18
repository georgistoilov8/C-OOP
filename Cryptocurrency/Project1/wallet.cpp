#include <iostream>
#include <fstream>
#include "wallet.h"
#include "transaction.h"

bool addWallet() {
	Wallet wallet;
	do {
		std::cin >> wallet.fiatMoney;
	} while (!std::cin);

	std::cin.ignore();
	std::cin.getline(wallet.owner, 255);
	returnWalletId(wallet);

	std::fstream file(WALLET_PATH, std::ios::binary | std::ios::app);
	if (!file) {
		std::cerr << WALLET_PATH << ": error while opening." << std::endl;
	}

	file.write((char*)&wallet, sizeof(wallet));
	if (!file) {
		std::cerr << WALLET_PATH << ": error while writing." << std::endl;
		return false;
	}
	file.close();
	addTransaction(wallet);
	return true;
}

void returnWalletId(Wallet& wallet) {
	wallet.id = 1;
	std::ifstream file(WALLET_PATH, std::ios::binary);
	if (!file) {
		//std::cerr << "wallet.dat didn't open" << std::endl;
		return;
	}
	file.seekg(0, std::ios::end);
	std::streampos file_size = file.tellg();
	if (file_size < sizeof(wallet)) {
		wallet.id = 1;
	}
	else {
		int offset = -(int)sizeof(wallet);
		file.seekg(offset, std::ios::end);
		file.seekg(sizeof(wallet.owner), std::ios::cur);
		file.read((char*)&wallet.id, sizeof(wallet.id));
		if (!file) {
			std::cerr << WALLET_PATH << ": error while reading." << std::endl;
			file.close();
			return;
		}
		wallet.id++;
	}
	file.close();
}

bool getWallet(unsigned id, Wallet& wallet) {
	std::ifstream file(WALLET_PATH, std::ios::binary);
	if (!file) {
		std::cerr << WALLET_PATH << ": didn't open" << std::endl;
		return false;
	}
	//if (!binarySearch(file, wallet, id)) {
	if(!search(file, wallet, id)){
		file.close();
		std::cerr << "Error: not found id." << std::endl;
		return false;
	}
	file.close();
	return true;
}

bool search(std::ifstream& file, Wallet& wallet, unsigned id) {
	while (file) {
		file.read((char*)& wallet, sizeof(wallet));
		if (file) {
			if (wallet.id == id) {
				return true;
			}
		}
	}
	return false;
}

/*bool binarySearch(std::ifstream& file, Wallet& wallet, unsigned id) {
	file.seekg(0, std::ios::end);
	std::streampos file_size = file.tellg();
	bool is_wallet_found = false;
	unsigned wallet_count = file_size / sizeof(Wallet);
	unsigned left = 0;
	unsigned right = file_size / sizeof(Wallet);
	unsigned middle;
	file.seekg(-(int)sizeof(wallet), std::ios::end);
	file.read((char*)&wallet, sizeof(wallet));
	if (!file) {
		std::cerr << WALLET_PATH << ": error while reading" << std::endl;
		return false;
	}
	if (wallet.id < id) {
		// Because IDs are consecutive, so if the id is larger than the last id, it doesn't exist.
		return false;
	}
	while (left <= right) {
		//middle = wallet_count / 2;
		//wallet_count /= 2;
		middle = left + (right - 1) / 2;
		file.seekg(middle * sizeof(Wallet), std::ios::beg);
		file.seekg(sizeof(wallet.owner), std::ios::cur);
		
		file.read((char*)&wallet.id, sizeof(wallet.id));
		if (!file) {
			std::cerr << WALLET_PATH << ": error while reading.!!!!!!!!!!!!!!!" << std::endl;
			return false;
		}
		//std::cout << wallet.id << std::endl;
		if (wallet.id == id) {
			file.seekg(-(int)(sizeof(wallet.id) + sizeof(wallet.owner)), std::ios::cur);
			file.read((char*)&wallet, sizeof(wallet));
			if (!file) {
				std::cerr << WALLET_PATH << ": error while reading." << std::endl;
				return false;
			}
			is_wallet_found = true;
		}
		else if (wallet.id < id) {
			right = middle;
		}
		else {
			left = middle;
		}
	}
	//printWallet(wallet);
	return true;
}*/

bool isWalletContained(unsigned id) {
	Wallet wallet;
	std::ifstream file(WALLET_PATH, std::ios::binary);
	if (!file) {
		std::cerr << WALLET_PATH << ": error while opening" << std::endl;
		return false;
	}
	file.seekg(-(int)sizeof(wallet), std::ios::end);
	file.seekg(sizeof(wallet.owner), std::ios::cur);
	file.read((char*)&wallet.id, sizeof(wallet.id));
	if (!file) {
		std::cerr << WALLET_PATH << ": error while reading" << std::endl;
		file.close();
		return false;
	}
	file.close();
	if (wallet.id < id) {
		return false;
	}
	return true;
}

double walletFiatMoney(unsigned id) {
	Wallet wallet;
	getWallet(id, wallet);
	//printWallet(wallet);
	return wallet.fiatMoney;
}

bool changeFiatMoney(Wallet& wallet) {
	//printWallet(wallet);
	std::fstream file(WALLET_PATH, std::ios::binary | std::ios::in | std::ios::out);
	if (!file) {
		std::cerr << WALLET_PATH << ": error while opening." << std::endl;
		return false;
	}
	file.seekp((wallet.id-1)*sizeof(wallet), std::ios::beg);
	file.write((char*)&wallet, sizeof(wallet));
	if (!file) {
		std::cerr << WALLET_PATH << ": error while writing." << std::endl;
		file.close();
		return false;
	}
	file.close();
	return true;
}

void topWealthiest() {
	Wallet wealthiest_wallets[10];
	double wealthiest_coins[10];
	Wallet wallet;
	unsigned wallet_count = 0;
	std::ifstream file(WALLET_PATH, std::ios::binary);
	if (!file) {
		std::cerr << WALLET_PATH << ": error while opening." << std::endl;
		return;
	}
	while (!file.eof()) {
		file.read((char*)&wallet, sizeof(wallet));
		if (file) {
			if (wallet_count < 10) {
				change(wealthiest_wallets[wallet_count], wallet);
				wealthiest_coins[wallet_count] = walletFmiCoins(wallet.id);
				wallet_count++;
			}
			else {
				double new_coins = walletFmiCoins(wallet.id);
				double min_coins = wealthiest_coins[0];
				unsigned index = 0;
				for (unsigned i = 1; i < 10; i++) {
					if (min_coins > wealthiest_coins[i]) {
						min_coins = wealthiest_coins[i];
						index = i;
					}
				}
				if (min_coins < new_coins) {
					change(wealthiest_wallets[index], wallet);
					wealthiest_coins[index] = new_coins;
				}
			}
		}
	}
	file.close();	
	for (unsigned i = 0; i < 10; i++) {
		printWallet(wealthiest_wallets[i]);
		std::cout << "FMICoins: " << wealthiest_coins[i] << std::endl;
		std::cout << "Transactions: " << countTransactions(wealthiest_wallets[i].id) << std::endl;
		std::cout << "Time first transaction: " << timeTransaction(1, wealthiest_wallets[i].id) << std::endl; // 1 for first
		std::cout << "Time last transaction: " << timeTransaction(2, wealthiest_wallets[i].id) << std::endl;  // 2 for last
		std::cout << std::endl;
	}
}

void change(Wallet& old_wallet, Wallet& new_wallet) {
	old_wallet.fiatMoney = new_wallet.fiatMoney;
	old_wallet.id = new_wallet.id;
	strcpy_s(old_wallet.owner, new_wallet.owner);
	// Using strcpy_s because of this error: Severity	Code	Description	Project	File	Line	Suppression State
	//Error	C4996	'strcpy': This function or variable may be unsafe.Consider using strcpy_s instead.
	//To disable deprecation, use _CRT_SECURE_NO_WARNINGS.See online help for details.Project1	
	//wallet.cpp	234

}

void walletInfo(unsigned id) {
	Wallet wallet;
	getWallet(id, wallet);
	printWallet(wallet);
	std::cout << "FMICoins: " << walletFmiCoins(wallet.id) << std::endl;
}

bool printLastAddedWallet() {
	Wallet wallet;
	std::ifstream file(WALLET_PATH, std::ios::binary);
	if (!file) {
		std::cerr << WALLET_PATH << ": error while opening." << std::endl;
		return false;
	}
	int offset = -(int)(sizeof(wallet));
	file.seekg(offset, std::ios::end);
	file.read((char*)&wallet, sizeof(wallet));
	if (!file) {
		std::cerr << WALLET_PATH << ": error while reading." << std::endl;
		file.close();
		return false;
	}
	file.close();

	printWallet(wallet);
	return true;
}

void printAllWallets() {
	Wallet wallet;
	std::ifstream file(WALLET_PATH, std::ios::binary);
	if (!file) {
		std::cerr << WALLET_PATH << ": error while opening." << std::endl;
		return;
	}
	while (!file.eof()) {
		file.read((char*)&wallet, sizeof(wallet));
		if(file)
			printWallet(wallet);
	}
	file.close();
}

void printWallet(Wallet& wallet) {
	std::cout << "Wallet money: " << wallet.fiatMoney << std::endl;
	std::cout << "Wallet id: " << wallet.id << std::endl;
	std::cout << "Wallet owner: " << wallet.owner << std::endl;
}