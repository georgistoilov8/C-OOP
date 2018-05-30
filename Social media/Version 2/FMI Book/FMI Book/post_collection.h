#pragma once

#include "post.h"

#ifndef POST_COLLECTION_INCLUDED
#define POST_COLLECTION

class PostCollection {
		Post** posts;
		int posts_capacity = 2;
		int posts_count = 0;

	public:
		PostCollection();
		PostCollection(const PostCollection& other);
		PostCollection& operator=(const PostCollection& other);
		~PostCollection();

		void copyFrom(const PostCollection& other);
		void clean();

		void setPosts(Post** posts, int posts_capacity, int posts_count);
		
		Post** getPosts() const;
		int getPostsCapacity() const;
		int getPostsCount() const;
		Post* getPost(int index) const;
		
		void createPost(const Post& post);

		void resize();
		void reduce();

		void removePost(const int index);

		void showPosts() const;

};

#endif // !POST_COLLECTION_INCLUDED

