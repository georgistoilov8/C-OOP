#pragma once

#include "post.h"

#ifndef LINK_POST_INCLUDED
#define LINK_POST

class LinkPost : public Post {
	public:
		char* wrapToHtml() const;
		char* getHtmlContent() const;
		LinkPost* clone() const override;
};
#endif // !LINK_POST_INCLUDED
