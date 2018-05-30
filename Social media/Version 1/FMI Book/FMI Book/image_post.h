#pragma once

#include "post.h"

#ifndef IMAGE_POST_INCLUDED
#define IMAGE_POST

class ImagePost : public Post {
	public:
		char* wrapToHtml() const;
		char* getHtmlContent() const;
		ImagePost* clone() const override;
};
#endif // !IMAGE_POST_INCLUDED
