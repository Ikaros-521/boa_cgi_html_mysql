效果参考：

https://ikaros-521.gitee.io/boa_cgi_html_mysql/login.html

使用到的软件和技术

	BOA服务器，CGI，CCGI，MySQL，SQLite。C，HTML，CSS，JS，SQL
	
具体功能讲解

	1、运行BOA服务器 （来到BOA目录下的src，终端输入 sudo ./boa 启动服务）
	
	2、打开浏览器，输入localhost:端口号/login.html （文件都要放在 /var/www 目录下）
	
	3、登录页面，注册页面。（登录注册将表单发送给对应CGI文件，CGI文件和MySQL数据库交互（运行MySQL，建好数据库和表)，将结果输出）
	
	4、登录成功后会来到 配置页面。（对相应参数进行配置，可自由发挥，同样HTML的表单发送给CGI程序，打开系统文件，写入相应参数，重启服务）
	
环境搭建和配置等其他问题可以参考大佬的博客讲解  [https://blog.csdn.net/A642960662/article/details/66473793](https://blog.csdn.net/A642960662/article/details/66473793)

ajax局部刷新，这个demo链接在这 [https://gitee.com/ikaros-521/ajax_cgi/tree/master](https://gitee.com/ikaros-521/ajax_cgi/tree/master)

## 准备环境

操作系统： Ubuntu12.04 LTS

环境搭建： 需要 [BOA](http://www.boa.org/)，CCGI，MySQL，GCC

[Linux下嵌入式Web服务器BOA和CGI编程开发](https://blog.csdn.net/Ikaros_521/article/details/102610768)

[数据库的相关知识——学习笔记](https://blog.csdn.net/Ikaros_521/article/details/102610768) 的三

[mysql中文乱码问题解决 / C程序插入仍是乱码解决 / 卸载重装教学](https://blog.csdn.net/Ikaros_521/article/details/102664117)

扩展： 我还用了[bootstrap](https://www.runoob.com/bootstrap/bootstrap-tutorial.html)框架，CSS/JS

源码链接：GitHub：[传送门](https://github.com/Ikaros-521/boa_cgi_html_mysql)  ， 码云：[传送门](https://gitee.com/ikaros-521/boa_cgi_html_mysql)

## 使用方法

环境准备好后，我们在 /var/www 下写HTML文件

![在这里插入图片描述](https://images.gitee.com/uploads/images/2019/1204/132133_b3009318_5140590.png)

在 /var/www/cgi-bin 下写c文件，编译后命名为.cgi。

编译命令仅供参考

 `gcc -o login.cgi login.c cgic.c -lpthread -ldl -lmysqlclient`
 
![在这里插入图片描述](https://images.gitee.com/uploads/images/2019/1204/132132_1fb658de_5140590.png)

程序都写好后，我们开始测试。


**1、开启MySQL服务    默认开启**

![在这里插入图片描述](https://images.gitee.com/uploads/images/2019/1204/132133_1a9afdc8_5140590.png)

我的程序需要事先   新建用户test，数据库register，表user

```bash
mysql -utest -ptest
```

```sql
// 创建新用户test
mysql> create user 'test'@'localhost' identified by 'test';
// 给test用户所有权限
mysql> grant all privileges on *.*  to test@localhost identified by 'test';
// 刷新权限
mysql> flush privileges;
```

```sql
mysql> create database register;
```

```sql
mysql> use register;
mysql> CREATE TABLE user(username varchar(20) PRIMARY KEY,password varchar(20));
```

**2、开启BOA服务器，在/boa/src目录下**    `sudo ./boa`

![在这里插入图片描述](https://images.gitee.com/uploads/images/2019/1204/132133_f700e66f_5140590.png)

**3、打开浏览器，访问localhost:端口号 访问的即 /var/www 目录**

**我直接访问 http://localhost:886/login.html  我的登录页面**

![在这里插入图片描述](https://images.gitee.com/uploads/images/2019/1204/132133_e7bdc3ce_5140590.png)
   
   其他页面都是同理。

## 思路讲解

![在这里插入图片描述](https://images.gitee.com/uploads/images/2019/1204/132132_571039c1_5140590.png)

**开启boa服务器后，我们访问到我们在 /var/www 下编写的HTML文件，显示我们的登录页面。
我们点击“注册”按钮，跳转到 register.html**

![在这里插入图片描述](https://images.gitee.com/uploads/images/2019/1204/132133_86b0bd91_5140590.png)

**点击“注册”按钮，提交form表单信息给cgi-bin/register.cgi**

![在这里插入图片描述](https://images.gitee.com/uploads/images/2019/1204/132132_d547f5dc_5140590.png)

**cgi程序通过 cgiFormString函数试图检索发送给指定字段的字符串。存入变量中。我们连接MySQL数据库**

![在这里插入图片描述](https://images.gitee.com/uploads/images/2019/1204/132133_cacd702b_5140590.png)

![在这里插入图片描述](https://images.gitee.com/uploads/images/2019/1204/132133_6fed70a0_5140590.png)

**将数据写入register数据库中的user表中（此数据库和表需要先建好）**

![在这里插入图片描述](https://images.gitee.com/uploads/images/2019/1204/132132_c2ec4688_5140590.png)

**处理完毕后，跳回 login.html 登录页面**

![在这里插入图片描述](https://images.gitee.com/uploads/images/2019/1204/132133_f52eddcc_5140590.png)

![在这里插入图片描述](https://images.gitee.com/uploads/images/2019/1204/132133_8c29a6c5_5140590.png)

**现在我们输入数据，点击“登录”，同理将表单发给 login.cgi ，对数据在MySQL数据库中查询后，成功就来到base_config.html 配置页面。**

![在这里插入图片描述](https://images.gitee.com/uploads/images/2019/1204/132132_2d22eb4b_5140590.png)

**然后我们输入相应数据，点击“提交”，交给base_config.cgi处理，之后任意发挥就好了。**

![在这里插入图片描述](https://images.gitee.com/uploads/images/2019/1204/132132_85401fe3_5140590.png)

**我是打印出来，写入系统文件的代码暂时注释了，慎用**

![在这里插入图片描述](https://images.gitee.com/uploads/images/2019/1204/132133_6d4c6fd5_5140590.png)

*遇到问题可以参考页首的链接*

---


**其余参考[GitHub](https://github.com/Ikaros-521/boa_cgi_html_mysql)或[码云](https://gitee.com/ikaros-521/boa_cgi_html_mysql)**

## 补充
### 文件上传
前端post方式上传文件到后端 /var/www/cgi-bin 目录下
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210114163024637.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0lrYXJvc181MjE=,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210114163624243.png)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210114163640400.png)