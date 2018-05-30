#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include "link_post.h"

char* LinkPost::wrapToHtml() const {
	int content_length = strlen(getContent());
	int html_length = 60;
	char* result = new char[html_length + content_length + 1];
	strcpy(result, "<!DOCTYPE html><html><body><a href=\"");
	strcat(result, getContent());
	strcat(result, "\">Link</a></body></html>");
	/*
	<!DOCTYPE html>
	<html>
		<body>
			<a href="">Link</a>
		</body>
	</html>
	*/

	return result;
}

char* LinkPost::getHtmlContent() const {
	int content_length = strlen(getContent());
	int html_length = 20;
	char* result = new char[html_length + content_length + 1];
	strcpy(result, "<a href=\"");
	strcat(result, getContent());
	strcat(result, "\">Link</a>");
	return result;
}

LinkPost* LinkPost::clone() const {
	return new LinkPost(*this);
}