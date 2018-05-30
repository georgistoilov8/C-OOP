#pragma once

#ifndef POST_INCLUDED
#define POST

class Post {
	public: 
		enum post_category { image, text, link };
	protected:
		char* content;
		int id;
		post_category type;
	public:
		Post();
		Post(const Post& other);
		Post& operator=(const Post& other);
		~Post();

		void copyFrom(const Post& other);
		void clean();

		void setId(const int id);
		void setContent(const char* content);
		void setType(const post_category type);

		int getId() const;
		char* getContent() const;
		post_category getType() const;

		void print() const;

		virtual char* wrapToHtml() const;

		virtual char* getHtmlContent() const;

		virtual Post* clone() const;
};
#endif // !POST_INCLUDED
