#pragma once

#ifndef CELL_INCLUDED
#define CELL

class Cell {
	public:
	enum cell_type{Integer, RealNumber, String, Date, Empty};
	
	protected:
	cell_type type = Empty;

	private:
		//void copyFrom(const Cell& cell);

	public:
		Cell();
		//Cell(const Cell& cell);
		//virtual Cell& operator=(const Cell& cell);
		virtual ~Cell();
		virtual Cell* clone() const = 0;
		virtual void print() const = 0;
		virtual int getValue() const = 0;
		virtual void getCellToFile(std::ostream& file) const = 0;

		void setType(const cell_type type);
		cell_type getType() const;

};

#endif // !CELL_INCLUDED
