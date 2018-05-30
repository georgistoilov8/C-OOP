#pragma once

#include "post.h"

#ifndef TEXT_POST_INCLUDED
#define TEXT_POST

class TextPost : public Post {
	public:
		char* wrapToHtml() const;
		char* getHtmlContent() const;
		TextPost* clone() const override;
};
#endif // !TEXT_POST_INCLUDED