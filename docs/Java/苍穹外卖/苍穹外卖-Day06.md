# 苍穹外卖-Day06

## 课程内容

- HttpClient
- 微信小程序开发
- 微信登录
- 导入商品浏览功能代码



功能实现：**微信登录**、**商品浏览**

**微信登录效果图：**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271828806.png" alt="image-20221203184545847" style="zoom:50%;" /> 



**商品浏览效果图：**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604241934027.png" alt="image-20221203184623026" style="zoom:50%;" /> <img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271828736.png" alt="image-20221203184638043" style="zoom:50%;" /> 



## 1. HttpClient

### 1.1 介绍

HttpClient 是 Apache Jakarta Common 下的子项目，可以用来提供高效的、最新的、功能丰富的支持 HTTP 协议的客户端编程工具包，并且它支持 HTTP 协议最新的版本和建议。

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271828193.png" alt="image-20221203185003231" style="zoom:50%;" /> 

**HttpClient 作用：**

- 发送 HTTP 请求
- 接收响应数据

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604241943376.png" alt="image-20221203185149985" style="zoom:33%;" />  为什么要在 Java 程序中发送 Http 请求？有哪些应用场景呢？

**HttpClient 应用场景：**

当我们在使用扫描支付、查看地图、获取验证码、查看天气等功能时

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271828773.png" alt="image-20221203185536013" style="zoom: 50%;" />  <img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271828386.png" alt="image-20221203185557674" style="zoom:50%;" />   <img src="assets/image-20221203185614509.png" alt="image-20221203185614509" style="zoom:50%;" />   <img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271828836.png" alt="image-20221203185632934" style="zoom:50%;" /> 



其实，应用程序本身并未实现这些功能，都是在应用程序里访问提供这些功能的服务，访问这些服务需要发送 HTTP 请求，并且接收响应数据，可通过 HttpClient 来实现。

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271828824.png" alt="image-20221203185427462" style="zoom:50%;" /> 

**HttpClient 的 maven 坐标：**

```xml
<dependency>
	<groupId>org.apache.httpcomponents</groupId>
	<artifactId>httpclient</artifactId>
	<version>4.5.13</version>
</dependency>
```

**HttpClient 的核心 API：**

- HttpClient：Http 客户端对象类型，使用该类型对象可发起 Http 请求。
- HttpClients：可认为是构建器，可创建 HttpClient 对象。
- CloseableHttpClient：实现类，实现了 HttpClient 接口。
- HttpGet：Get 方式请求类型。
- HttpPost：Post 方式请求类型。

**HttpClient 发送请求步骤：**

- 创建 HttpClient 对象
- 创建 Http 请求对象
- 调用 HttpClient 的 execute 方法发送请求



### 1.2 入门案例

对 HttpClient 编程工具包有了一定了解后，那么，我们使用 HttpClient 在 Java 程序当中来构造 Http 的请求，并且把请求发送出去，接下来，就通过入门案例分别发送 **GET 请求**和 **POST 请求**，具体来学习一下它的使用方法。

#### 1.2.1 GET 方式请求

正常来说，首先，应该导入 HttpClient 相关的坐标，但在项目中，就算不导入，也可以使用相关的 API。

因为在项目中已经引入了 aliyun-sdk-oss 坐标：

```xml
<dependency>
    <groupId>com.aliyun.oss</groupId>
    <artifactId>aliyun-sdk-oss</artifactId>
</dependency>
```

上述依赖的底层已经包含了HttpClient相关依赖。

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271829483.png" alt="image-20221203194852825" style="zoom:50%;" /> 

故选择导入或者不导入均可。

进入到 sky-server 模块，编写测试代码，发送 GET 请求。

**实现步骤：**

1. 创建 HttpClient 对象
2. 创建请求对象
3. 发送请求，接受响应结果
4. 解析结果
5. 关闭资源

```java
package com.sky.test;

import org.apache.http.HttpEntity;
import org.apache.http.client.methods.CloseableHttpResponse;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClients;
import org.apache.http.util.EntityUtils;
import org.junit.jupiter.api.Test;
import org.springframework.boot.test.context.SpringBootTest;

@SpringBootTest
public class HttpClientTest {

    /**
     * 测试通过 httpclient 发送 GET 方式的请求
     */
    @Test
    public void testGET() throws Exception {
        // 创建 httpclient 对象
        CloseableHttpClient httpClient = HttpClients.createDefault();

        // 创建请求对象
        HttpGet httpGet = new HttpGet("http://localhost:8080/user/shop/status");

        // 发送请求
        CloseableHttpResponse response = httpClient.execute(httpGet);

        // 获取服务端返回的状态码
        int statusCode = response.getStatusLine().getStatusCode();
        System.out.println("服务端放回的状态码为：" + statusCode);

        // 解析服务端返回的数据
        HttpEntity entity = response.getEntity();
        String body = EntityUtils.toString(entity);
        System.out.println("服务端返回的数据为：" + body);

        // 关闭资源
        response.close();
        httpClient.close();
    }
}
```

在访问 http://localhost:8080/user/shop/status 请求时，需要提前启动项目。

**测试结果：**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604242123769.png" alt="image-20260424212347332" style="zoom:50%;" /> 



#### 1.2.2 POST 方式请求

在 HttpClientTest中 添加 POST 方式请求方法，相比 GET 请求来说，POST 请求若携带参数需要封装请求体对象，并将该对象设置在请求对象中。

**实现步骤：**

1. 创建 HttpClient 对象
2. 创建请求对象
3. 发送请求，接收响应结果
4. 解析响应结果
5. 关闭资源

```java
	/**
     * 测试通过httpclient发送POST方式的请求
     */
    @Test
    public void testPOST() throws Exception{
        // 创建httpclient对象
        CloseableHttpClient httpClient = HttpClients.createDefault();

        //创建请求对象
        HttpPost httpPost = new HttpPost("http://localhost:8080/admin/employee/login");

        JSONObject jsonObject = new JSONObject();
        jsonObject.put("username","admin");
        jsonObject.put("password","123456");

        StringEntity entity = new StringEntity(jsonObject.toString());
        //指定请求编码方式
        entity.setContentEncoding("utf-8");
        //数据格式
        entity.setContentType("application/json");
        httpPost.setEntity(entity);

        //发送请求
        CloseableHttpResponse response = httpClient.execute(httpPost);

        //解析返回结果
        int statusCode = response.getStatusLine().getStatusCode();
        System.out.println("响应码为：" + statusCode);

        HttpEntity entity1 = response.getEntity();
        String body = EntityUtils.toString(entity1);
        System.out.println("响应数据为：" + body);

        //关闭资源
        response.close();
        httpClient.close();
    }
```

**测试结果：**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271848909.png" alt="image-20221203201023925" style="zoom:50%;" /> 



## 2. 微信小程序开发

### 2.1 介绍

小程序是一种新的开放能力，开发者可以快速地开发一个小程序。可以在微信内被便捷地获取和传播，同时具有出色的使用体验。

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271829814.png" alt="image-20221203204712437" style="zoom:50%;" /> 

**官方网址：**https://mp.weixin.qq.com/cgi-bin/wx?token=&lang=zh_CN

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271829382.png" alt="image-20221203205305487" style="zoom:50%;" /> 

小程序主要运行微信内部，可通过上述网站来整体了解微信小程序的开发。

**首先，**在进行小程序开发时，需要先去注册一个小程序，在注册的时候，它实际上又分成了不同的注册的主体。我们可以以个人的身份来注册一个小程序，当然，也可以以企业政府、媒体或者其他组织的方式来注册小程序。那么，不同的主体注册小程序，最终开放的权限也是不一样的。比如以个人身份来注册小程序，是无法开通支付权限的。若要提供支付功能，必须是企业、政府或者其它组织等。所以，不同的主体注册小程序后，可开发的功能是不一样的。

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271829109.png" alt="image-20221203210640473" style="zoom:50%;" /> 



**然后，**微信小程序我们提供的一些开发的支持，实际上微信的官方是提供了一系列的工具来帮助开发者快速的接入
并且完成小程序的开发，提供了完善的开发文档，并且专门提供了一个开发者工具，还提供了相应的设计指南，同时也提供了一些小程序体验 DEMO，可以快速的体验小程序实现的功能。

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271829341.png" alt="image-20221203211226920" style="zoom:50%;" /> 

**最后，**开发完一个小程序要上线，也给我们提供了详细地接入流程。

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271829340.png" alt="image-20221203211535565" style="zoom:50%;" /> 



### 2.2 准备工作

开发微信小程序之前需要做如下准备工作：

- 注册小程序
- 完善小程序信息
- 下载开发者工具

**1). 注册小程序**

注册地址：https://mp.weixin.qq.com/wxopen/waregister?action=step1

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271829067.png" alt="image-20221203212348111" style="zoom: 50%;" /> 



**2). 完善小程序信息**

登录小程序后台：https://mp.weixin.qq.com/

两种登录方式选其一即可

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271837376.png" alt="image-20221203212454040" style="zoom:50%;" /> <img src="assets/image-20221203212508081.png" alt="image-20221203212508081" style="zoom:50%;" /> 

完善小程序信息、小程序类目

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271837702.png" alt="image-20221203212615981" style="zoom:50%;" /> 

查看小程序的 AppID

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271837349.png" alt="image-20221203212702993" style="zoom:50%;" /> 



**3). 下载开发者工具**

资料中已提供，无需下载，熟悉下载步骤即可。

下载地址： https://developers.weixin.qq.com/miniprogram/dev/devtools/stable.html

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271837204.png" alt="image-20221203212836364" style="zoom:50%;" /> 

扫描登录开发者工具

创建小程序项目

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271837472.png" alt="image-20221203213042020" style="zoom:50%;" /> 

熟悉开发者工具布局

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271838749.png" alt="image-20221203213108317" style="zoom:50%;" /> 

设置不校验合法域名

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271838159.png" alt="image-20221203213212370" style="zoom:50%;" /> 

**注：**开发阶段，小程序发出请求到后端的 Tomcat 服务器，若不勾选，请求发送失败。



### 2.3 入门案例

实际上，小程序的开发本质上属于前端开发，主要使用 JavaScript 开发，本项目的定位是后端，所以对于小程序开发简单了解即可。

#### 2.3.1 小程序目录结构

小程序包含一个描述整体程序的 app 和多个描述各自页面的 page。一个小程序主体部分由三个文件组成，必须放在项目的根目录，如下：

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271838597.png" alt="image-20221203220557676" style="zoom:50%;" /> 

**文件说明：**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271838744.png" alt="image-20221203220635867" style="zoom:50%;" /> 

**app.js：**必须存在，主要存放小程序的逻辑代码

**app.json：**必须存在，小程序配置文件，主要存放小程序的公共配置

**app.wxss:**  非必须存在，主要存放小程序公共样式表，类似于前端的 CSS 样式

对小程序主体三个文件了解后，其实一个小程序又有多个页面。比如说，有商品浏览页面、购物车的页面、订单支付的页面、商品的详情页面等等，这些页面会存放在 pages 目录。

每个小程序页面主要由四个文件组成：

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271839862.png" alt="image-20221203220826893" style="zoom:50%;" /> 

**文件说明：**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271839155.png" alt="image-20221203220839187" style="zoom:50%;" /> 

**js 文件：**必须存在，存放页面业务逻辑代码，编写的 js 代码。

**wxml 文件：**必须存在，存放页面结构，主要是做页面布局，页面效果展示的，类似于 HTML 页面。

**json 文件：**非必须，存放页面相关的配置。

**wxss 文件：**非必须，存放页面样式表，相当于 CSS 文件。



#### 2.3.2 编写和编译小程序

**1). 编写**

进入到 index.wxml，编写页面布局

```xml
<view class="container">
  <view>{{msg}}</view>
   <view>
    <button type="default" bindtap="getUserInfo">获取用户信息</button>
    <image style="width: 100px;height: 100px;" src="{{avatarUrl}}"></image>
    {{nickName}}
  </view>
   <view>
    <button type="primary" bindtap="wxlogin">微信登录</button>
    授权码：{{code}}
  </view>
   <view>
    <button type="warn" bindtap="sendRequest">发送请求</button>
    响应结果：{{result}}
  </view>
</view>
```

进入到 index.js，编写业务逻辑代码

```javascript
Page({
  data:{
    msg:'hello world',
    avatarUrl:'',
    nickName:'',
    code:'',
    result:''
  },
  getUserInfo:function(){
    wx.getUserProfile({
      desc: '获取用户信息',
      success:(res) => {
        console.log(res)
        this.setData({
          avatarUrl:res.userInfo.avatarUrl,
          nickName:res.userInfo.nickName
        })
      }
    })
  },
  wxlogin:function(){
    wx.login({
      success: (res) => {
        console.log("授权码："+res.code)
        this.setData({
          code:res.code
        })
      }
    })
  },
  sendRequest:function(){
    wx.request({
      url: 'http://localhost:8080/user/shop/status',
      method:'GET',
      success:(res) => {
        console.log("响应结果：" + res.data.data)
        this.setData({
          result:res.data.data
        })
      }
    })
  }})
```



**2). 编译**

点击编译按钮

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271839518.png" alt="image-20221204181233015" style="zoom:50%;" /> 



**3). 运行效果**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271839707.png" alt="image-20221204181606927" style="zoom:50%;" /> 



点击**获取用户信息**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271839305.png" alt="image-20221204182056440" style="zoom: 67%;" /> 



点击**微信登录**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271840431.png" alt="image-20221204182238762" style="zoom: 67%;" /> 

点击**发送请求**

因为请求 http://localhost:8080/user/shop/status，先要启动后台项目。

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271840551.png" alt="image-20221204192519728" style="zoom: 67%;" /> 

**注：**设置不校验合法域名，若不勾选，请求发送失败。



#### 2.3.3 发布小程序

小程序的代码都已经开发完毕，要将小程序发布上线，让所有的用户都能使用到这个小程序。

点击上传按钮：

<img src="assets/image-20221204225355015.png" alt="image-20221204225355015" style="zoom:50%;" /> 

指定版本号：

<img src="assets/image-20221204225502698.png" alt="image-20221204225502698" style="zoom:50%;" /> 

上传成功：

<img src="assets/image-20221204225557820.png" alt="image-20221204225557820" style="zoom:50%;" /> 

把代码上传到微信服务器就表示小程序已经发布了吗？
**其实并不是。**当前小程序版本只是一个开发版本。

进到微信公众平台，打开版本管理页面。

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271840534.png" alt="image-20221204230231476" style="zoom:50%;" /> 

需提交审核，变成审核版本，审核通过后，进行发布，变成线上版本。

一旦成为线上版本，这就说明小程序就已经发布上线了，微信用户就可以在微信里面去搜索和使用这个小程序了。



## 3. 微信登录

### 3.1 导入小程序代码

开发微信小程序，本质上是属于前端的开发，我们的重点其实还是后端代码开发。所以，小程序的代码已经提供好了，直接导入到微信开发者工具当中，直接来使用就可以了。

**1). 找到资料**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271840651.png" alt="image-20221204205429798" style="zoom: 67%;" /> 



**2). 导入代码**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271840807.png" alt="image-20221204205631809" style="zoom:50%;" /> 

AppID：使用自己的 AppID

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271840373.png" alt="image-20221204210011364" style="zoom:50%;" /> 



**3). 查看项目结构**

主体的文件：`app.js`、`app.json`、`app.wxss`
项目的页面比较多，主要存放在 pages 目录。

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271841248.png" alt="image-20221204210739195" style="zoom:50%;" /> 



**4). 修改配置**

因为小程序要请求后端服务，需要修改为自己后端服务的 ip 地址和端口号（默认不需要修改）

common-->vendor.js-->搜索(ctrl+f)-->baseUri

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271841699.png" alt="image-20221204211239035" style="zoom:50%;" /> 



### 3.2 微信登录流程

微信登录：https://developers.weixin.qq.com/miniprogram/dev/framework/open-ability/login.html

**流程图：**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271841729.png" alt="image-20221204211800753" style="zoom:50%;" /> 



**步骤分析：**

1. 小程序端，调用 wx.login() 获取 code，就是授权码。
2. 小程序端，调用 wx.request() 发送请求并携带 code，请求开发者服务器(自己编写的后端服务)。
3. 开发者服务端，通过 HttpClient 向微信接口服务发送请求，并携带 appId + appsecret + code 三个参数。
4. 开发者服务端，接收微信接口服务返回的数据，session_key + opendId 等。opendId 是微信用户的唯一标识。
5. 开发者服务端，自定义登录态，生成令牌（token）和 openid 等数据返回给小程序端，方便后绪请求身份校验。
6. 小程序端，收到自定义登录态，存储 storage。
7. 小程序端，后绪通过 wx.request() 发起业务请求时，携带 token。
8. 开发者服务端，收到请求后，通过携带的 token，解析当前登录用户的 id。
9. 开发者服务端，身份校验通过后，继续相关的业务逻辑处理，最终返回业务数据。



接下来，我们使用 Postman 进行测试。

**说明：**

1. 调用 [wx.login()](https://developers.weixin.qq.com/miniprogram/dev/api/open-api/login/wx.login.html) 获取 **临时登录凭证 code** ，并回传到开发者服务器。
2. 调用 [auth.code2Session](https://developers.weixin.qq.com/miniprogram/dev/api-backend/open-api/login/auth.code2Session.html) 接口，换取 **用户唯一标识 OpenID** 、 用户在微信开放平台帐号下的**唯一标识 UnionID**（若当前小程序已绑定到微信开放平台帐号） 和 **会话密钥 session_key**。

之后开发者服务器可以根据用户标识来生成自定义登录态，用于后续业务逻辑中前后端交互时识别用户身份。

**实现步骤：**

**1). 获取授权码**

点击确定按钮，获取授权码，每个授权码只能使用一次，每次测试，需重新获取。

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271843727.png" alt="image-20221204222008130" style="zoom:50%;" /> 



**2). 明确请求接口**

请求方式、请求路径、请求参数

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271843258.png" alt="image-20221204222434054" style="zoom:50%;" /> 



**3). 发送请求**

获取 session_key 和 openid

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271843013.png" alt="image-20221204223956568" style="zoom:50%;" /> 

若出现 code been used 错误提示，说明授权码已被使用过，请重新获取

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271843828.png" alt="image-20221204224130409" style="zoom:50%;" /> 

 

### 3.3 需求分析和设计

#### 3.3.1 产品原型

用户进入到小程序的时候，微信授权登录之后才能点餐。需要获取当前微信用户的相关信息，比如昵称、头像等，这样才能够进入到小程序进行下单操作。是基于微信登录来实现小程序的登录功能，没有采用传统账户密码登录的方式。若第一次使用小程序来点餐，就是一个新用户，需要把这个新的用户保存到数据库当中完成自动注册。

**登录功能原型图：**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271956863.png" alt="image-20221205173711304" style="zoom:50%;" /> 



**业务规则：**

- 基于微信登录实现小程序的登录功能
- 如果是新用户需要自动完成注册



#### 3.3.2 接口设计

通过微信登录的流程，如果要完成微信登录的话，最终就要获得微信用户的 openid。在小程序端获取授权码后，向后端服务发送请求，并携带授权码，这样后端服务在收到授权码后，就可以去请求微信接口服务。最终，后端向小程序返回 openid 和 token 等数据。

基于上述的登录流程，就可以设计出该接口的**请求参数**和**返回数据**。

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271956910.png" alt="image-20221205175429394" style="zoom:50%;" /> <img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604271956316.png" alt="image-20221205175441256" style="zoom:50%;" />

**说明：**请求路径 /user/user/login，第一个 user 代表用户端，第二个 user 代表用户模块。



#### 3.3.3 表设计

当用户第一次使用小程序时，会完成自动注册，把用户信息存储到 **user** 表中。

| **字段名**  | **数据类型** | **说明**           | **备注** |
| ----------- | ------------ | ------------------ | -------- |
| id          | bigint       | 主键               | 自增     |
| openid      | varchar(45)  | 微信用户的唯一标识 |          |
| name        | varchar(32)  | 用户姓名           |          |
| phone       | varchar(11)  | 手机号             |          |
| sex         | varchar(2)   | 性别               |          |
| id_number   | varchar(18)  | 身份证号           |          |
| avatar      | varchar(500) | 微信用户头像路径   |          |
| create_time | datetime     | 注册时间           |          |

**说明：**手机号字段比较特殊，个人身份注册的小程序没有权限获取到微信用户的手机号。如果是以企业的资质注册的小程序就能够拿到微信用户的手机号。



### 3.4 代码开发

#### 3.4.1 定义相关配置

**配置微信登录所需配置项：**

application-dev.yml

```yaml
sky:
  wechat:
    appid: 
    secret: 
```

application.yml

```yaml
sky:
  wechat:
    appid: ${sky.wechat.appid}
    secret: ${sky.wechat.secret}
```

**配置为微信用户生成 jwt 令牌时使用的配置项：**

application.yml

```yaml
sky:
  jwt:
    # 设置 jwt 签名加密时使用的秘钥
    admin-secret-key: itcast
    # 设置 jwt 过期时间
    admin-ttl: 7200000
    # 设置前端传递过来的令牌名称
    admin-token-name: token
    user-secret-key: itheima
    user-ttl: 7200000
    user-token-name: authentication
```



#### 3.4.2 DTO 设计

**根据传入参数设计 DTO 类：**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604272032888.png" alt="image-20221205183625049" style="zoom:50%;" /> 

在 sky-pojo 模块，UserLoginDTO.java 已定义

```java
package com.sky.dto;

import lombok.Data;

import java.io.Serializable;

/**
 * C端用户登录
 */
@Data
public class UserLoginDTO implements Serializable {

    private String code;

}
```



#### 3.4.3 VO 设计

**根据返回数据设计 VO 类：**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604280909008.png" alt="image-20221205183923272" style="zoom:50%;" /> 

在 sky-pojo 模块，UserLoginVO.java 已定义

```java
package com.sky.vo;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.io.Serializable;

@Data
@Builder
@NoArgsConstructor
@AllArgsConstructor
public class UserLoginVO implements Serializable {

    private Long id;
    private String openid;
    private String token;

}
```



#### 3.4.4 Controller 层

**根据接口定义创建 UserController 的 login 方法：**

```java
package com.sky.controller.user;

import com.sky.constant.JwtClaimsConstant;
import com.sky.dto.UserLoginDTO;
import com.sky.entity.User;
import com.sky.properties.JwtProperties;
import com.sky.result.Result;
import com.sky.service.UserService;
import com.sky.utils.JwtUtil;
import com.sky.vo.UserLoginVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.HashMap;
import java.util.Map;

@RestController
@RequestMapping("/user/user")
@Api(tags = "C端用户相关接口")
@Slf4j
public class UserController {

    @Autowired
    private UserService userService;
    @Autowired
    private JwtProperties jwtProperties;

    /**
     * 微信登录
     */
    @PostMapping("/login")
    @ApiOperation(value = "微信登录")
    public Result<UserLoginVO> login(@RequestBody UserLoginDTO userLoginDTO) {
        log.info("微信登录: {}", userLoginDTO.getCode());

        // 微信登录
        User user = userService.wxLogin(userLoginDTO);

        // 为微信用户设置 jwt 令牌
        Map<String, Object> claims = new HashMap<>();
        claims.put(JwtClaimsConstant.USER_ID, user.getId());
        String token = JwtUtil.createJWT(jwtProperties.getUserSecretKey(), jwtProperties.getUserTtl(), claims);

        UserLoginVO userLoginVO = UserLoginVO.builder().id(user.getId()).openid(user.getOpenid()).token(token).build();
        return Result.success(userLoginVO);
    }
}
```

其中，JwtClaimsConstant.USER_ID 常量已定义。



#### 3.4.5 Service 层接口

**创建 UserService 接口：**

```java
package com.sky.service;


import com.sky.dto.UserLoginDTO;
import com.sky.entity.User;

public interface UserService {

    /**
     * 微信登录
     */
    User wxLogin(UserLoginDTO userLoginDTO);
}
```



#### 3.4.6 Service 层实现类

**创建 UserServiceImpl 实现类：**实现获取微信用户的 openid 和微信登录功能

```java
package com.sky.service.impl;

import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.JSONObject;
import com.sky.constant.MessageConstant;
import com.sky.dto.UserLoginDTO;
import com.sky.entity.User;
import com.sky.exception.LoginFailedException;
import com.sky.mapper.UserMapper;
import com.sky.properties.WeChatProperties;
import com.sky.service.UserService;
import com.sky.utils.HttpClientUtil;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.time.LocalDateTime;
import java.util.HashMap;
import java.util.Map;

@Service
@Slf4j
public class UserServiceImpl implements UserService {

    // 微信登录服务接口地址
    private static final String WX_LOGIN_URL = "https://api.weixin.qq.com/sns/jscode2session";

    @Autowired
    private WeChatProperties weChatProperties;
    @Autowired
    private UserMapper userMapper;

    /**
     * 微信登录
     */
    @Override
    public User wxLogin(UserLoginDTO userLoginDTO) {
        // 调用微信接口服务，获得当前微信用户的 openid
        String openid = getOpenid(userLoginDTO.getCode());

        // 判断 openid 是否为空，如果为空则表示登录失败，抛出业务异常
        if (openid == null) {
            throw new LoginFailedException(MessageConstant.LOGIN_FAILED);
        }

        // 判断当前用户是否为新用户
        User user = userMapper.getByOpenid(openid);

        // 如果是新用户，自动完成注册
        if (user == null) {
            user = User.builder().openid(openid).createTime(LocalDateTime.now()).build();
            userMapper.insert(user);
        }

        // 返回这个用户对象
        return user;
    }

    /**
     * 根据 code 获取的当前微信用户的 openid
     */
    private String getOpenid(String code) {
        Map<String, String> paramMap = new HashMap<>();
        paramMap.put("appid", weChatProperties.getAppid());
        paramMap.put("secret", weChatProperties.getSecret());
        paramMap.put("js_code", code);
        paramMap.put("grant_type", "authorization_code");
        String json = HttpClientUtil.doGet(WX_LOGIN_URL, paramMap);

        JSONObject jsonObject = JSON.parseObject(json);
        return jsonObject.getString("openid");
    }
}
```



#### 3.4.7 Mapper 层

**创建 UserMapper 接口：**

```java
package com.sky.mapper;

import com.sky.entity.User;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;

@Mapper
public interface UserMapper {

    /**
     * 根据 openid 查询用户
     */
    @Select("select * from user where openid = #{openid}")
    User getByOpenid(String openid);

    /**
     * 插入数据
     */
    void insert(User user);
}

```

**创建 UserMapper.xml 映射文件：**

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE mapper PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-mapper.dtd" >
<mapper namespace="com.sky.mapper.UserMapper">

    <insert id="insert" useGeneratedKeys="true" keyProperty="id">
        insert into user (openid, name, phone, sex, id_number, avatar, create_time)
        values (#{openid}, #{name}, #{phone}, #{sex}, #{idNumber}, #{avatar}, #{createTime})
    </insert>

</mapper>
```



#### 3.4.8 编写拦截器

**编写拦截器 JwtTokenUserInterceptor ：**统一拦截用户端发送的请求并进行 jwt 校验

```java
package com.sky.interceptor;

import com.sky.constant.JwtClaimsConstant;
import com.sky.context.BaseContext;
import com.sky.properties.JwtProperties;
import com.sky.utils.JwtUtil;
import io.jsonwebtoken.Claims;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;
import org.springframework.web.method.HandlerMethod;
import org.springframework.web.servlet.HandlerInterceptor;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * jwt 令牌校验的拦截器
 */
@Component
@Slf4j
public class JwtTokenUserInterceptor implements HandlerInterceptor {

    @Autowired
    private JwtProperties jwtProperties;

    /**
     * 校验 jwt
     */
    public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
        // 输出当前线程 id
        System.out.println("当前线程的 id: " + Thread.currentThread().getId());

        //判断当前拦截到的是 Controller 的方法还是其他资源
        if (!(handler instanceof HandlerMethod)) {
            //当前拦截到的不是动态方法，直接放行
            return true;
        }

        //1、从请求头中获取令牌
        String token = request.getHeader(jwtProperties.getUserTokenName());

        //2、校验令牌
        try {
            log.info("jwt 校验：{}", token);
            Claims claims = JwtUtil.parseJWT(jwtProperties.getUserSecretKey(), token);
            Long userId = Long.valueOf(claims.get(JwtClaimsConstant.USER_ID).toString());
            log.info("当前用户 id：", userId);

            // 存储当前用户 id
            BaseContext.setCurrentId(userId);

            //3、通过，放行
            return true;
        } catch (Exception ex) {
            //4、不通过，响应 401 状态码
            response.setStatus(401);
            return false;
        }
    }
}
```

**在 WebMvcConfiguration 配置类中注册拦截器：**

```java
	@Autowired
    private JwtTokenUserInterceptor jwtTokenUserInterceptor;
	/**
     * 注册自定义拦截器
     */
    protected void addInterceptors(InterceptorRegistry registry) {
        log.info("开始注册自定义拦截器...");
        //.........

        registry.addInterceptor(jwtTokenUserInterceptor)
                .addPathPatterns("/user/**")
                .excludePathPatterns("/user/user/login")
                .excludePathPatterns("/user/shop/status");
    }
```



### 3.5 功能测试

重新编译小程序，进行登录，获取到 openid 和 token 数据

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604281119579.png" alt="image-20221205192506490" style="zoom:50%;" /> 

查看后台日志

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604281119080.png" alt="image-20221205192943394" style="zoom:67%;" />  

查看数据库 user 表，第一次登录，会自动注册

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604281119754.png" alt="image-20221205193018421" style="zoom: 67%;" />  



## 4. 导入商品浏览功能代码

### 4.1 需求分析和设计

#### 4.1.1 产品原型

用户登录成功后跳转到系统首页，在首页需要根据分类来展示菜品和套餐。如果菜品设置了口味信息，需要展示<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604281119801.png" alt="image-20210812205330291" style="zoom: 80%;" />按钮，否则显示<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604281119238.png" alt="image-20210812205346846" style="zoom:80%;" />按钮。

   **图1：菜品列表效果图**                                      **图2：菜品口味效果图**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604281119746.png" alt="image-20221205193821129" style="zoom: 50%;" />                               <img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604281119522.png" alt="image-20221205193846867" style="zoom:50%;" /> 

​    **图3：套餐列表效果图**                                     **图4：套餐详情效果图**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604281119430.png" alt="image-20221205193859016" style="zoom:50%;" />                               <img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604281119148.png" alt="image-20221205193911476" style="zoom:50%;" /> 



#### 4.1.2 接口设计

根据上述原型图先**粗粒度**设计接口，共包含 4 个接口。

**接口设计：**

- 查询分类（图1）
- 根据分类 id 查询菜品（图2）
- 根据分类 id 查询套餐（图3）
- 根据套餐 id 查询包含的菜品（图4）



接下来**细粒度**分析每个接口，明确每个接口的请求方式、请求路径、传入参数和返回值。

**1). 查询分类**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604281627567.png" alt="image-20221205200235328" style="zoom:50%;" /> <img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604281627195.png" alt="image-20221205200246588" style="zoom:50%;" />



**2). 根据分类 id 查询菜品**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604281627625.png" alt="image-20221205200319686" style="zoom:50%;" /> <img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604281627688.png" alt="image-20221205200335214" style="zoom:50%;" />



**3). 根据分类 id 查询套餐**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604281627267.png" alt="image-20221205200415135" style="zoom:50%;" /> <img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604281627615.png" alt="image-20221205200425607" style="zoom:50%;" />



**4). 根据套餐 id 查询包含的菜品**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604281628779.png" alt="image-20221205200537591" style="zoom:50%;" />

 



### 4.2 代码导入

导入资料中的商品浏览功能代码即可

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604281628778.png" alt="image-20221205201043358" style="zoom:50%;" /> 

可按照 mapper-->service-->controller 依次导入，这样代码不会显示相应的报错。

进入到 sky-server 模块中

#### 4.2.1 Mapper 层

**在 SetmealMapper.java 中添加 list 和 getDishItemBySetmealId 两个方法**

```java
	/**
     * 动态条件查询套餐
     * @param setmeal
     * @return
     */
    List<Setmeal> list(Setmeal setmeal);

    /**
     * 根据套餐id查询菜品选项
     * @param setmealId
     * @return
     */
    @Select("select sd.name, sd.copies, d.image, d.description " +
            "from setmeal_dish sd left join dish d on sd.dish_id = d.id " +
            "where sd.setmeal_id = #{setmealId}")
    List<DishItemVO> getDishItemBySetmealId(Long setmealId);
```

**创建 SetmealMapper.xml 文件**

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE mapper PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-mapper.dtd" >
<mapper namespace="com.sky.mapper.SetmealMapper">

    <select id="list" parameterType="Setmeal" resultType="Setmeal">
        select * from setmeal
        <where>
            <if test="name != null">
                and name like concat('%',#{name},'%')
            </if>
            <if test="categoryId != null">
                and category_id = #{categoryId}
            </if>
            <if test="status != null">
                and status = #{status}
            </if>
        </where>
    </select>
</mapper>
```



#### 4.2.2 Service 层

**创建 SetmealService.java**

```java
package com.sky.service;

import com.sky.dto.SetmealDTO;
import com.sky.dto.SetmealPageQueryDTO;
import com.sky.entity.Setmeal;
import com.sky.result.PageResult;
import com.sky.vo.DishItemVO;
import com.sky.vo.SetmealVO;
import java.util.List;

public interface SetmealService {

    /**
     * 条件查询
     * @param setmeal
     * @return
     */
    List<Setmeal> list(Setmeal setmeal);

    /**
     * 根据id查询菜品选项
     * @param id
     * @return
     */
    List<DishItemVO> getDishItemById(Long id);

}
```

**创建 SetmealServiceImpl.java**

```java
package com.sky.service.impl;

import com.sky.entity.Setmeal;
import com.sky.mapper.DishMapper;
import com.sky.mapper.SetmealDishMapper;
import com.sky.mapper.SetmealMapper;
import com.sky.service.SetmealService;
import com.sky.vo.DishItemVO;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

/**
 * 套餐业务实现
 */
@Service
@Slf4j
public class SetmealServiceImpl implements SetmealService {

    @Autowired
    private SetmealMapper setmealMapper;
    @Autowired
    private SetmealDishMapper setmealDishMapper;
    @Autowired
    private DishMapper dishMapper;

    /**
     * 条件查询
     * @param setmeal
     * @return
     */
    public List<Setmeal> list(Setmeal setmeal) {
        List<Setmeal> list = setmealMapper.list(setmeal);
        return list;
    }

    /**
     * 根据id查询菜品选项
     * @param id
     * @return
     */
    public List<DishItemVO> getDishItemById(Long id) {
        return setmealMapper.getDishItemBySetmealId(id);
    }
}
```

**在 DishService.java 中添加 listWithFlavor 方法定义**

```java
	/**
     * 条件查询菜品和口味
     * @param dish
     * @return
     */
    List<DishVO> listWithFlavor(Dish dish);
```

**在 DishServiceImpl.java 中实现 listWithFlavor 方法**

```java
	/**
     * 条件查询菜品和口味
     * @param dish
     * @return
     */
    public List<DishVO> listWithFlavor(Dish dish) {
        List<Dish> dishList = dishMapper.list(dish);

        List<DishVO> dishVOList = new ArrayList<>();

        for (Dish d : dishList) {
            DishVO dishVO = new DishVO();
            BeanUtils.copyProperties(d,dishVO);

            //根据菜品id查询对应的口味
            List<DishFlavor> flavors = dishFlavorMapper.getByDishId(d.getId());

            dishVO.setFlavors(flavors);
            dishVOList.add(dishVO);
        }

        return dishVOList;
    }
```



#### 4.2.3 Controller 层

**创建 DishController.java**

```java
package com.sky.controller.user;

import com.sky.constant.StatusConstant;
import com.sky.entity.Dish;
import com.sky.result.Result;
import com.sky.service.DishService;
import com.sky.vo.DishVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import java.util.List;

@RestController("userDishController")
@RequestMapping("/user/dish")
@Slf4j
@Api(tags = "C端-菜品浏览接口")
public class DishController {
    @Autowired
    private DishService dishService;

    /**
     * 根据分类id查询菜品
     *
     * @param categoryId
     * @return
     */
    @GetMapping("/list")
    @ApiOperation("根据分类id查询菜品")
    public Result<List<DishVO>> list(Long categoryId) {
        Dish dish = new Dish();
        dish.setCategoryId(categoryId);
        dish.setStatus(StatusConstant.ENABLE);//查询起售中的菜品

        List<DishVO> list = dishService.listWithFlavor(dish);

        return Result.success(list);
    }

}
```

**创建 CategoryController.java**

```java
package com.sky.controller.user;

import com.sky.entity.Category;
import com.sky.result.Result;
import com.sky.service.CategoryService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import java.util.List;

@RestController("userCategoryController")
@RequestMapping("/user/category")
@Api(tags = "C端-分类接口")
public class CategoryController {

    @Autowired
    private CategoryService categoryService;

    /**
     * 查询分类
     * @param type
     * @return
     */
    @GetMapping("/list")
    @ApiOperation("查询分类")
    public Result<List<Category>> list(Integer type) {
        List<Category> list = categoryService.list(type);
        return Result.success(list);
    }
}
```

**创建 SetmealController.java**

```java
package com.sky.controller.user;

import com.sky.constant.StatusConstant;
import com.sky.entity.Setmeal;
import com.sky.result.Result;
import com.sky.service.SetmealService;
import com.sky.vo.DishItemVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import java.util.List;

@RestController("userSetmealController")
@RequestMapping("/user/setmeal")
@Api(tags = "C端-套餐浏览接口")
public class SetmealController {
    @Autowired
    private SetmealService setmealService;

    /**
     * 条件查询
     *
     * @param categoryId
     * @return
     */
    @GetMapping("/list")
    @ApiOperation("根据分类id查询套餐")
    public Result<List<Setmeal>> list(Long categoryId) {
        Setmeal setmeal = new Setmeal();
        setmeal.setCategoryId(categoryId);
        setmeal.setStatus(StatusConstant.ENABLE);

        List<Setmeal> list = setmealService.list(setmeal);
        return Result.success(list);
    }

    /**
     * 根据套餐 id 查询包含的菜品列表
     *
     * @param id
     * @return
     */
    @GetMapping("/dish/{id}")
    @ApiOperation("根据套餐id查询包含的菜品列表")
    public Result<List<DishItemVO>> dishList(@PathVariable("id") Long id) {
        List<DishItemVO> list = setmealService.getDishItemById(id);
        return Result.success(list);
    }
}
```



### 4.3 功能测试

重启服务器、重新编译小程序

微信登录进入首页

**菜品和套餐分类查询：**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604281630225.png" alt="image-20221205205634465" style="zoom:50%;" /> 

**具体分类下的菜品查询：**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604281630779.png" alt="image-20221205205935019" style="zoom:50%;" /> 

**菜品口味查询：**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604281630105.png" alt="image-20221205210121546" style="zoom:50%;" /> 

