Example of the program and how to test it:

```
$: Admin add_user Pesho 21
Pesho created.
$: Pesho post [url] http://www.example.com Някакъв пример.
Post 0 created.
$: Pesho post [image] /home/pesho/img/hello.png
Post 1 created.
$: Admin add_moderator Gencho 28
Gencho created.
$: Gencho post [text] Hello everybody!
Post 2 created.
$: Pesho post [text] Hi, Gencho!
Post 3 created.
$: Pesho post [text] See my new bike:
Post 4 created.
$: Pesho post [image] /home/pesho/img/dzvera.png
Post 5 created.
$: Pesho post [text] egati i typoto kolelo e!!!
Post 6 created.
$: Pesho remove_post 6.
Post 6 removed.
$: Pesho post [text] egati i qkoto kolelo e!!!
Post 7 created.
$: Gencho post [text] Please do not use shliokavitsa!
Post 8 created.
$: Pesho post [text] Be ti li 6a mi kaje6!?
Post 9 created.
$: Gencho block Pesho.
Pesho blocked.
$: Pesho post [text] Na kyw mi se prai6!?
Post not created - user blocked!
$: Pesho post [text] Ej!!!!?
Post not created - user blocked!
$: Gencho post [text] Pesho, please, calm down!
Post 10 created.
$: Pesho post [text] Ti li 6a mi kave6!!!!?
Post not created - user blocked!
$: Admin remove_user Pesho.
Pesho removed. 
$: Admin rename Pesho.
User Admin is now known as Pesho.
$: info
There are 2 users:
Pesho - Administrator, 0 posts.
Gencho - Moderator, 2 posts.
There aren’t any blocked users.
oldest Gencho 28
youngest Gencho 28
$: Gencho remove_post 9
No such post!
$: Gencho remove_post 10
Post 10 removed.
$: Admin add_user Mimi 19
No such user : Admin!
$: Pesho add_user Mimi 19
User Mimi created.
$: Mimi post [image] /home/mimi/img/profile_pic.jpg
Post 11 created.
$: Gecho view_post 11
HTML view for post 11 created.
$: Mimi view_all_posts Gencho
HTML view for all Gencho’s posts created.
$: delete system
Unknown command!
$: quit
```
