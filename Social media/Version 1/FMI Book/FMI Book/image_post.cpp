#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include "image_post.h"

char* ImagePost::wrapToHtml() const {
	int content_length = strlen(getContent());
	int html_length = 65;
	char* result = new char[html_length + content_length + 1];
	strcpy(result, "<!DOCTYPE html><html><body><img src=\"");
	strcat(result, getContent());
	strcat(result, "\" alt=\"Image\"></body></html>");
	/*
		<!DOCTYPE html>
		<html>
			<body>
				<img src="" alt="Image">
			</body>
		</html>
	*/

	return result;
}

char* ImagePost::getHtmlContent() const {
	int content_length = strlen(getContent());
	int html_length = 24;
	char* result = new char[html_length + content_length + 1];
	strcpy(result, "<img src=\"");
	strcat(result, getContent());
	strcat(result, "\" alt=\"Image\">");
	return result;
}

ImagePost* ImagePost::clone() const {
	return new ImagePost(*this);
}