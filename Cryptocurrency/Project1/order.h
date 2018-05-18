#pragma once

#ifndef _ORDER_HEADER_INCLUDED_
#define _ORDER_HEADER_INCLUDED_
#define ORDER_PATH "order.dat"

struct Order {
	enum Type { SELL, BUY } type;
	unsigned walletId;
	double fmiCoins;
};

void makeOrder();

void processOrder(Order& order);

void extendOrder(Order& order);

double returnOrderCoins(unsigned id);

void printOrders();

void printOrder(Order& order);

#endif //_ORDER_HEADER_INCLUDED_
