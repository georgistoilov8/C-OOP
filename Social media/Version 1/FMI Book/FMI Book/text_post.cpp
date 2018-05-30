#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include "text_post.h"

char* TextPost::wrapToHtml() const {
	int content_length = strlen(getContent());
	int html_length = 48;
	char* result = new char[html_length + content_length + 1];
	strcpy(result, "<!DOCTYPE html><html><body><p>");
	strcat(result, getContent());
	strcat(result, "</p></body></html>");
	/*
	<!DOCTYPE html>
	<html>
		<body>
			<p>
				Text	
			</p>
		</body>
	</html>
	*/

	return result;
}

char* TextPost::getHtmlContent() const {
	int content_length = strlen(getContent());
	int html_length = 7;
	char* result = new char[html_length + content_length + 1];
	strcpy(result, "<p>");
	strcat(result, getContent());
	strcat(result, "</p>");
	return result;
}

TextPost* TextPost::clone() const {
	return new TextPost(*this);
}