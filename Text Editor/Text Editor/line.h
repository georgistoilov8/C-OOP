#include "word.h"

#pragma once

#ifndef LINE_H_INCLUDED
#define LINE_H

	class Line {
		private:
			Word* words;
			Word* whitespaces; //for space and tabs
			int word_count;
			int whitespaces_count;
			char* content;
			int size;
			bool removed;
			bool start_word; // true -> line start with word; false -> line start whit whitespace
		public:
			Line();
			Line(const Line& line);
			Line& operator=(const Line& line);
			~Line();

			int getWordCount() const;
			void setWordCount(const int number);

			int getWhitespaceCount() const;
			void setWhitespaceCount(const int number);

			int getContentSize() const;
			void setContentSize(const int number);

			bool isRemoved() const;
			void setRemove(const bool b);

			bool startWithWord() const;
			void setStartWord(const bool b);

			void getContent(char* text) const;
			void setContent(const char* content);
			void clearContent();

			Word& getWord(const int number) const;
			Word& getWhitespace(const int number) const;

			void copyWords(const Line& line);
			void copyWhitespaces(const Line& line);

			void setWords(const char* content);
			void setWhitespaces(const char* content);

			void startWith(const char* content);
			void rebuildLine(char* final_line);
			int findSize();

			void copy(const Line& other);
			void clear();

			void printWords() const;
			void printWhitespaces() const;
	};

	bool isWordLetter(char c);
	int wordCount(const char* text);
	int whitespaceCount(const char* text);
#endif // !LINE_H_INCLUDED
