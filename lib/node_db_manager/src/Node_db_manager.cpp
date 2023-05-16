// void addPostTag(const dbo::ptr<Post>& post, const std::string& tagName)
//     {
//         dbo::ptr<Tag> tag = session_.find<Tag>().where("name = ?").bind(tagName);

//         if (tag.is_null()) {
//             tag = session_.add(new Tag());
//             tag.modify()->name = tagName;
//         }

//         post.modify()->tags.insert(tag);
//         tag.modify()->posts.insert(post);

//         session_.flush();
//     }