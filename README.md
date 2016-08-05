# webcppd-example
webcppd动态服务器插件式开发范例

# 依赖(Centos)
* epel-release：`yum -y install epel-release`
* Poco： `yum -y install poco-devel`
* [webcppd](https://github.com/webcpp/webcppd)
* opencv：`yum -y install opencv-devel`
* ubuntu 用户请自行寻找对应依赖

# 使用方法

* 直接
`
make
`


* 配置webcppd
> * http.libHandlerDir 
> * http.tplDirectory


分别指向webcppd-examaple的build和tpl目录.

* 运行webcppd服务器.

* 最后访问
> `http://localhost:8888/helloworld/index`
.

# 全部演示列表

* home
* static
* cookie
* login
* logout
* gzip
* get
* post
* upload
* ajax
* captcha
