#pragma once

#ifndef WORD_H_INCLUDED
#define WORD_H

	class Word {
		private:
			char* word;
			int size;
		public:
			Word();
			Word(Word& other);
			Word& operator=(const Word& other);
			~Word();

			int getSize() const;
			void setSize(int size);
			void get(char* word) const;
			void set(const char* word);

			void print() const;

			void copy(const Word& other);
			void clear();

			void addFront(const char* text);
			
			void addEnd(const char* text);

	};

#endif // !WORD_H_INCLUDED
