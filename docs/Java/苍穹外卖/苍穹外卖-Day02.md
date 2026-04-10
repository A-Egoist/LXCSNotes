# 苍穹外卖-Day02

## 课程内容

- 新增员工
- 员工分页查询
- 启用禁用员工账号
- 编辑员工
- 导入分类模块功能代码



**功能实现：**员工管理、菜品分类管理。

**员工管理效果：**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604091744571.png" alt="image-20221112172846316" style="zoom:50%;" /> 



**菜品分类管理效果：**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604091744276.png" alt="image-20221112172925354" style="zoom:50%;" /> 



## 1. 新增员工

### 1.1 需求分析和设计

#### 1.1.1 产品原型

一般在做需求分析时，往往都是对照着产品原型进行分析，因为产品原型比较直观，便于理解业务。

后台系统中可以管理员工信息，通过新增员工来添加后台系统用户。

**新增员工原型：**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604091745424.png" alt="image-20221111161120975" style="zoom: 50%;" /> 



当填写完表单信息, 点击"保存"按钮后, 会提交该表单的数据到服务端, 在服务端中需要接受数据, 然后将数据保存至数据库中。

**注意事项：**

1. 账号必须是唯一的
2. 手机号为合法的 11 位手机号码
3. 身份证号为合法的 18 位身份证号码
4. 密码默认为 123456



#### 1.1.2 接口设计

>   文档位置：资料-->项目接口文档-->苍穹外卖-管理端接口.html

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604091747624.png" alt="image-20221111162912753" style="zoom:50%;" /> <img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604091747111.png" alt="image-20221111162930483" style="zoom:50%;" />

明确新增员工接口的**请求路径、请求方式、请求参数、返回数据**。



本项目约定：

- **管理端**发出的请求，统一使用 **/admin** 作为前缀。
- **用户端**发出的请求，统一使用 **/user** 作为前缀。



#### 1.1.3 表设计

新增员工，其实就是将我们新增页面录入的员工数据插入到 employee 表。

**employee 表结构：**

| **字段名**  | **数据类型** | **说明**     | **备注**    |
| ----------- | ------------ | ------------ | ----------- |
| id          | bigint       | 主键         | 自增        |
| name        | varchar(32)  | 姓名         |             |
| username    | varchar(32)  | 用户名       | 唯一        |
| password    | varchar(64)  | 密码         |             |
| phone       | varchar(11)  | 手机号       |             |
| sex         | varchar(2)   | 性别         |             |
| id_number   | varchar(18)  | 身份证号     |             |
| status      | Int          | 账号状态     | 1正常 0锁定 |
| create_time | Datetime     | 创建时间     |             |
| update_time | datetime     | 最后修改时间 |             |
| create_user | bigint       | 创建人id     |             |
| update_user | bigint       | 最后修改人id |             |

其中，employee 表中的 status 字段已经设置了默认值 1，表示状态正常。

![image-20221111180159188](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604091751888.png)  



### 1.2 代码开发

#### 1.2.1 设计 DTO 类

**根据新增员工接口设计对应的 DTO**

前端传递参数列表：

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604091949888.png" alt="image-20221111164002448" style="zoom:50%;" /> 

**思考：**是否可以使用对应的实体类来接收呢？

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604091949272.png" alt="image-20221111164453341" style="zoom:50%;" /> 

**注意：**当前端提交的数据和实体类中对应的属性差别比较大时，建议使用 DTO 来封装数据

由于上述传入参数和实体类有较大差别，所以自定义 DTO 类。

进入 sky-pojo 模块，在 com.sky.dto 包下，已定义 EmployeeDTO

```java
package com.sky.dto;

import lombok.Data;

import java.io.Serializable;

@Data
public class EmployeeDTO implements Serializable {

    private Long id;

    private String username;

    private String name;

    private String phone;

    private String sex;

    private String idNumber;

}
```



#### 1.2.2 Controller 层

 **EmployeeController 中创建新增员工方法**

进入到 sky-server 模块中，在 com.sky.controller.admin 包下，在 EmployeeController 中创建新增员工方法，接收前端提交的参数。

```java
	/**
     * 新增员工
     * @param employeeDTO
     * @return
     */
    @PostMapping
    @ApiOperation("新增员工")
    public Result save(@RequestBody EmployeeDTO employeeDTO){
        log.info("新增员工：{}",employeeDTO);
        employeeService.save(employeeDTO);//该方法后续步骤会定义
        return Result.success();
    }
```

**注：**Result 类定义了后端统一返回结果格式。

进入 sky-common 模块，在 com.sky.result 包下定义了 Result.java

```java
package com.sky.result;

import lombok.Data;

import java.io.Serializable;

/**
 * 后端统一返回结果
 * @param <T>
 */
@Data
public class Result<T> implements Serializable {

    private Integer code; //编码：1成功，0和其它数字为失败
    private String msg; //错误信息
    private T data; //数据

    public static <T> Result<T> success() {
        Result<T> result = new Result<T>();
        result.code = 1;
        return result;
    }

    public static <T> Result<T> success(T object) {
        Result<T> result = new Result<T>();
        result.data = object;
        result.code = 1;
        return result;
    }

    public static <T> Result<T> error(String msg) {
        Result result = new Result();
        result.msg = msg;
        result.code = 0;
        return result;
    }

}
```



#### 1.2.3 Service 层接口

**在 EmployeeService 接口中声明新增员工方法**

进入到 sky-server 模块中的 com.sky.server.EmployeeService

```java
	/**
     * 新增员工
     * @param employeeDTO
     */
    void save(EmployeeDTO employeeDTO);
```



#### 1.2.4 Service 层实现类

**在 EmployeeServiceImpl 中实现新增员工方法**

com.sky.server.impl.EmployeeServiceImpl 中创建方法

```java
	/**
     * 新增员工
     *
     * @param employeeDTO
     */
    public void save(EmployeeDTO employeeDTO) {
        Employee employee = new Employee();

        // 对象属性拷贝，属性名必须一致
        BeanUtils.copyProperties(employeeDTO, employee);

        // 设置账号的状态，默认正常状态，1 表示正常，0 表示锁定
        employee.setStatus(StatusConstant.ENABLE);

        // 设置密码，默认密码 123456
        employee.setPassword(DigestUtils.md5DigestAsHex(PasswordConstant.DEFAULT_PASSWORD.getBytes()));

        // 设置当前记录的创建时间和修改时间
        employee.setCreateTime(LocalDateTime.now());
        employee.setUpdateTime(LocalDateTime.now());

        // 设置当前记录创建人 id 和修改人 id
        // TODO 后期需要改为当前登录用户的 id
        employee.setCreateUser(10L);
        employee.setUpdateUser(10L);

        employeeMapper.insert(employee);
    }
```



在 sky-common 模块 com.sky.constants 包下已定义 StatusConstant.java

```java
package com.sky.constant;

/**
 * 状态常量，启用或者禁用
 */
public class StatusConstant {

    //启用
    public static final Integer ENABLE = 1;

    //禁用
    public static final Integer DISABLE = 0;
}

```



#### 1.2.5 Mapper层

**在 EmployeeMapper 中声明 insert 方法**

com.sky.EmployeeMapper 中添加方法

```java
	/**
     * 插入员工数据
     * @param employee
     */
    // 注意驼峰命名和下划线命名的映射
    @Insert("insert into employee (name, username, password, phone, sex, id_number, create_time, update_time, create_user, update_user) " +
            "values (#{name}, #{username}, #{password}, #{phone}, #{sex}, #{idNumber}, #{createTime}, #{updateTime}, #{createUser}, #{updateUser})")
    void insert(Employee employee);
```



在 application.yml 中已开启驼峰命名，故 id_number 和 idNumber 可对应。

```yaml
mybatis:
  configuration:
    #开启驼峰命名
    map-underscore-to-camel-case: true
```



### 1.3 功能测试

代码已经发开发完毕，对新增员工功能进行测试。

**功能测试实现方式：**

- 通过接口文档测试
- 通前后端联调测试

接下来我们使用上述两种方式分别测试。



#### 1.3.1 接口文档测试

**启动服务：**访问 http://localhost:8080/doc.html，进入新增员工接口

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604092005319.png" alt="image-20221111184934153" style="zoom:50%;" />   

json 数据：

```json
{
  "id": 0,
  "idNumber": "111222333444555666",
  "name": "xiaozhi",
  "phone": "13812344321",
  "sex": "1",
  "username": "小智"
}
```

响应码：401 报错

**通过断点调试：**进入到 JwtTokenAdminInterceptor 拦截器

```java
 	/**
     * 校验jwt
     *
     * @param request
     * @param response
     * @param handler
     * @return
     * @throws Exception
     */
    public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
        //判断当前拦截到的是Controller的方法还是其他资源
        if (!(handler instanceof HandlerMethod)) {
            //当前拦截到的不是动态方法，直接放行
            return true;
        }

        //1、从请求头中获取令牌 jwtProperties.getAdminTokenName()获取为token
        String token = request.getHeader(jwtProperties.getAdminTokenName());

        //2、校验令牌
        try {
            log.info("jwt校验:{}", token);
            Claims claims = JwtUtil.parseJWT(jwtProperties.getAdminSecretKey(), token);
            Long empId = Long.valueOf(claims.get(JwtClaimsConstant.EMP_ID).toString());
            log.info("当前员工id：", empId);
            //3、通过，放行
            return true;
        } catch (Exception ex) {
            //4、不通过，响应401状态码
            response.setStatus(401);
            return false;
        }
    }
```

**报错原因：**由于 JWT 令牌校验失败，导致 EmployeeController 的 save 方法没有被调用

**解决方法：**调用员工登录接口获得一个合法的 JWT 令牌

使用 admin 用户登录获取令牌

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604092005305.png" alt="image-20221111185649636" style="zoom: 50%;" /> 

**添加令牌：**

将合法的 JWT 令牌添加到全局参数中

文档管理-->全局参数设置-->添加参数

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604092005842.png" alt="image-20221111185901726" style="zoom: 50%;" /> 

**接口测试：**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604092005302.png" alt="image-20221111190132481" style="zoom:50%;" /> 

其中，请求头部含有 JWT 令牌

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604092005976.png" alt="image-20221111190248268" style="zoom:50%;" /> 

**查看 employee 表：**

![image-20260409200705461](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604092007272.png)

测试成功。



#### 1.3.2 前后端联调测试

启动 nginx，访问 http://localhost

登录-->员工管理-->添加员工

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604092007151.png" alt="image-20221111192339271" style="zoom:50%;" /> 

保存后，查看 employee 表

![image-20260409200836376](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604092008994.png) 

测试成功。



:warning: ​由于开发阶段前端和后端是并行开发的，后端完成某个功能后，此时前端对应的功能可能还没有开发完成，导致无法进行前后端联调测试。所以在开发阶段，后端测试主要以接口文档测试为主。



### 1.4 代码完善

目前，程序存在的问题主要有两个：

- 录入的用户名已存，抛出的异常后没有处理
- 新增员工时，创建人 id 和修改人 id 设置为固定值

接下来，我们对上述两个问题依次进行分析和解决。



#### 1.4.1 问题一

**描述：**录入的用户名已存，抛出的异常后没有处理

**分析：**

新增 username=zhangsan 的用户，若 employee 表中之前已存在。

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604092037479.png" alt="image-20221111193700895" style="zoom: 50%;" /> 

后台报错信息：

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604092037470.png" alt="image-20221111194049620" style="zoom:80%;" /> 

查看 employee 表结构：

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604092037746.png" alt="image-20221111194131787" style="zoom:50%;" /> 

发现，username 已经添加了唯一约束，不能重复。

**解决：**

通过全局异常处理器来处理。

进入到 sky-server 模块，com.sky.hander 包下，GlobalExceptionHandler.java 添加方法

```java
	/**
     * 处理SQL异常
     * @param ex
     * @return
     */
    @ExceptionHandler
    public Result exceptionHandler(SQLIntegrityConstraintViolationException ex){
        // Duplicate entry 'zhangsan' for key 'employee.idx_username'
        String message = ex.getMessage();
        if (message.contains("Duplicate entry")) {
            String[] split = message.split(" ");
            String username = split[2];
            String msg = username + MessageConstant.ALREADY_EXISTS;
            return Result.error(msg);
        } else {
            return Result.error(MessageConstant.UNKNOWN_ERROR);
        }
    }
```

进入到 sky-common 模块，在 MessageConstant.java 添加

```java
public static final String ALREADY_EXISTS = "已存在";
```

再次，接口测试：

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604092038408.png" alt="image-20221111195521095" style="zoom:50%;" /> 



####  1.4.2 问题二

**描述**：新增员工时，创建人 id 和修改人 id 设置为固定值

**分析：**

```java
	/**
     * 新增员工
     *
     * @param employeeDTO
     */
    public void save(EmployeeDTO employeeDTO) {
        Employee employee = new Employee();
        //................
        //////////当前设置的id为固定值10//////////
        employee.setCreateUser(10L);
        employee.setUpdateUser(10L);
        //////////////////////////////////////
        //.................................

        employeeMapper.insert(employee);//后续步骤定义
    }
```

**解决：**

通过某种方式动态获取当前登录员工的 id。

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604092245191.png" alt="image-20221111201922482" style="zoom:50%;" /> 

员工登录成功后会生成 JWT 令牌并响应给前端：

在 sky-server 模块

```java
package com.sky.controller.admin;
/**
 * 员工管理
 */
@RestController
@RequestMapping("/admin/employee")
@Slf4j
@Api(tags = "员工相关接口")
public class EmployeeController {

    @Autowired
    private EmployeeService employeeService;
    @Autowired
    private JwtProperties jwtProperties;

    /**
     * 登录
     *
     * @param employeeLoginDTO
     * @return
     */
    @PostMapping("/login")
    @ApiOperation(value = "员工登录")
    public Result<EmployeeLoginVO> login(@RequestBody EmployeeLoginDTO employeeLoginDTO) {
        //.........

        //登录成功后，生成jwt令牌
        Map<String, Object> claims = new HashMap<>();
        claims.put(JwtClaimsConstant.EMP_ID, employee.getId());
        String token = JwtUtil.createJWT(
                jwtProperties.getAdminSecretKey(),
                jwtProperties.getAdminTtl(),
                claims);

        //............

        return Result.success(employeeLoginVO);
    }

}
```

后续请求中，前端会携带 JWT 令牌，通过 JWT 令牌可以解析出当前登录员工 id：

JwtTokenAdminInterceptor.java

```java
package com.sky.interceptor;

/**
 * jwt令牌校验的拦截器
 */
@Component
@Slf4j
public class JwtTokenAdminInterceptor implements HandlerInterceptor {

    @Autowired
    private JwtProperties jwtProperties;

    /**
     * 校验jwt
     *
     * @param request
     * @param response
     * @param handler
     * @return
     * @throws Exception
     */
    public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
       
		//..............
        
        //1、从请求头中获取令牌
        String token = request.getHeader(jwtProperties.getAdminTokenName());

        //2、校验令牌
        try {
            log.info("jwt校验:{}", token);
            Claims claims = JwtUtil.parseJWT(jwtProperties.getAdminSecretKey(), token);
            Long empId = Long.valueOf(claims.get(JwtClaimsConstant.EMP_ID).toString());
            log.info("当前员工id：", empId);
            //3、通过，放行
            return true;
        } catch (Exception ex) {
            //4、不通过，响应401状态码
            response.setStatus(401);
            return false;
        }
    }
}
```

**思考：**解析出登录员工 id 后，如何传递给 Service 的 save 方法？

通过 ThreadLocal 进行传递。



#### 1.4.3 ThreadLocal

**介绍：**

ThreadLocal 并不是一个 Thread，而是 Thread 的局部变量。
ThreadLocal 为每个线程提供单独一份存储空间，具有线程隔离的效果，只有在线程内才能获取到对应的值，线程外则不能访问。

**常用方法：**

- `public void set(T value)`：设置当前线程的线程局部变量的值
- `public T get()`：返回当前线程所对应的线程局部变量的值
- `public void remove()`：移除当前线程的线程局部变量

对 ThreadLocal 有了一定认识后，接下来继续解决**问题二**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604092253120.png" alt="image-20221111212349365" style="zoom:67%;" /> 

初始工程中已经封装了 ThreadLocal 操作的工具类：

在 sky-common 模块

```java
package com.sky.context;

public class BaseContext {

    public static ThreadLocal<Long> threadLocal = new ThreadLocal<>();

    public static void setCurrentId(Long id) {
        threadLocal.set(id);
    }

    public static Long getCurrentId() {
        return threadLocal.get();
    }

    public static void removeCurrentId() {
        threadLocal.remove();
    }

}
```

在拦截器中解析出当前登录员工 id，并放入线程局部变量中：

在 sky-server 模块中，拦截器：

```java
package com.sky.interceptor;

/**
 * jwt令牌校验的拦截器
 */
@Component
@Slf4j
public class JwtTokenAdminInterceptor implements HandlerInterceptor {

    @Autowired
    private JwtProperties jwtProperties;

    /**
     * 校验jwt
     *
     * @param request
     * @param response
     * @param handler
     * @return
     * @throws Exception
     */
    public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
        
		//.............................
       
        //2、校验令牌
        try {
            //.................
            Claims claims = JwtUtil.parseJWT(jwtProperties.getAdminSecretKey(), token);
            Long empId = Long.valueOf(claims.get(JwtClaimsConstant.EMP_ID).toString());
            log.info("当前员工id：", empId);
            // 存储当前员工 id 到 ThreadLocal
            BaseContext.setCurrentId(empId);
            //3、通过，放行
            return true;
        } catch (Exception ex) {
            //......................
        }
    }
}
```

在 Service 中获取线程局部变量中的值：

```java
	/**
     * 新增员工
     *
     * @param employeeDTO
     */
    public void save(EmployeeDTO employeeDTO) {
        //.............................

        // 设置当前记录创建人 id 和修改人 id
        employee.setCreateUser(BaseContext.getCurrentId());
        employee.setUpdateUser(BaseContext.getCurrentId());

        employeeMapper.insert(employee);
    }
```

测试：使用 admin(id=1) 用户登录后添加一条记录

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604092258814.png" alt="image-20221111214044510" style="zoom:50%;" /> 

查看 employee 表记录

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604092259339.png" alt="image-20221111214354053" style="zoom:50%;" />

 

>   个人笔记：
>
>   在 Tlias 项目中，后端被分为了 Controller 层、Service 层、Dao 层，但是在苍穹外卖项目中，使用了 MyBatis 来代替 Dao 层的实现类，将其替换为了 Mapper 接口。
>
>   Mapper 的作用是将 Java 方法和 SQL 语句相互映射，通常使用 `@Mapper` 注解，而不是 `@Repository` 注解。



## 2. 员工分页查询

### 2.1 需求分析和设计

#### 2.1.1 产品原型

系统中的员工很多的时候，如果在一个页面中全部展示出来会显得比较乱，不便于查看，所以一般的系统中都会以分页的方式来展示列表数据。而在我们的分页查询页面中, 除了分页条件以外，还有一个查询条件 "员工姓名"。

**查询员工原型：**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604101113037.png" alt="image-20221111215309289" style="zoom:67%;" /> 

**业务规则**：

- 根据页码展示员工信息
- 每页展示 10 条数据
- 分页查询时可以根据需要，输入员工姓名进行查询



#### 2.1.2 接口设计

>   文档位置：资料-->项目接口文档-->苍穹外卖-管理端接口.html

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604101115785.png" alt="image-20221111220031113" style="zoom:50%;" /><img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604101115443.png" alt="image-20221111220041965" style="zoom:50%;" />

**注意事项：**

- 请求参数类型为 Query，**不是 json 格式提交**，在路径后直接拼接。/admin/employee/page?name=zhangsan
- 返回数据中 records 数组中使用 Employee 实体类对属性进行封装。
- 单表查询操作



### 2.2 代码开发

#### 2.2.1 设计 DTO 类

根据请求参数进行封装，在 sky-pojo 模块中

```java
package com.sky.dto;

import lombok.Data;

import java.io.Serializable;

@Data
public class EmployeePageQueryDTO implements Serializable {

    //员工姓名
    private String name;

    //页码
    private int page;

    //每页显示记录数
    private int pageSize;

}
```



#### 2.2.2 封装 PageResult

后面所有的分页查询，统一都封装为 PageResult 对象。

在 sky-common 模块

```java
package com.sky.result;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.io.Serializable;
import java.util.List;

/**
 * 封装分页查询结果
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
public class PageResult implements Serializable {

    private long total; //总记录数

    private List records; //当前页数据集合

}
```

员工信息分页查询后端返回的对象类型为: Result<PageResult>

```java
package com.sky.result;

import lombok.Data;

import java.io.Serializable;

/**
 * 后端统一返回结果
 * @param <T>
 */
@Data
public class Result<T> implements Serializable {

    private Integer code; //编码：1成功，0和其它数字为失败
    private String msg; //错误信息
    private T data; //数据

    public static <T> Result<T> success() {
        Result<T> result = new Result<T>();
        result.code = 1;
        return result;
    }

    public static <T> Result<T> success(T object) {
        Result<T> result = new Result<T>();
        result.data = object;
        result.code = 1;
        return result;
    }

    public static <T> Result<T> error(String msg) {
        Result result = new Result();
        result.msg = msg;
        result.code = 0;
        return result;
    }

}
```



#### 2.2.3 Controller 层

在 sky-server 模块中，com.sky.controller.admin.EmployeeController 中添加分页查询方法。

```java
	/**
     * 员工分页查询
     * @param employeePageQueryDTO
     * @return
     */
    @GetMapping("/page")
    @ApiOperation(value = "员工分页查询")
    public Result<PageResult> page(EmployeePageQueryDTO employeePageQueryDTO) {
        log.info("员工分页查询，参数为：{}", employeePageQueryDTO);
        PageResult pageResult = employeeService.pageQuery(employeePageQueryDTO);
        return Result.success(pageResult);
    }
```



#### 2.2.4 Service 层接口

在 EmployeeService 接口中声明 pageQuery 方法：

```java
	/**
     * 分页查询
     * @param employeePageQueryDTO
     * @return
     */
    PageResult pageQuery(EmployeePageQueryDTO employeePageQueryDTO);
```



#### 2.2.5 Service 层实现类

在 EmployeeServiceImpl 中实现 pageQuery 方法：

```java
	/**
     * 分页查询
     *
     * @param employeePageQueryDTO
     * @return
     */
    public PageResult pageQuery(EmployeePageQueryDTO employeePageQueryDTO) {
        // select * from employee limit 0,10
        //开始分页查询
        PageHelper.startPage(employeePageQueryDTO.getPage(), employeePageQueryDTO.getPageSize());

        Page<Employee> page = employeeMapper.pageQuery(employeePageQueryDTO);//后续定义

        long total = page.getTotal();
        List<Employee> records = page.getResult();

        return new PageResult(total, records);
    }
```

**注意：**此处使用 mybatis 的分页插件 PageHelper 来简化分页代码的开发。底层基于 mybatis 的拦截器实现。

故在 pom.xml 文中添加依赖(初始工程已添加)

```xml
<dependency>
   <groupId>com.github.pagehelper</groupId>
   <artifactId>pagehelper-spring-boot-starter</artifactId>
   <version>${pagehelper}</version>
</dependency>
```



#### 2.2.6 Mapper 层

在 EmployeeMapper 中声明 pageQuery 方法：

```java
	/**
     * 分页查询
     * @param employeePageQueryDTO
     * @return
     */
    Page<Employee> pageQuery(EmployeePageQueryDTO employeePageQueryDTO);
```

在 src/main/resources/mapper/EmployeeMapper.xml 中编写 SQL：

```sql
	<select id="pageQuery" resultType="com.sky.entity.Employee">
        select * from employee
        <where>
            <if test="name != null and name != ''">
                and name like concat('%',#{name},'%')
            </if>
        </where>
        order by create_time desc
    </select>
```



### 2.3 功能测试

可以通过接口文档进行测试，也可以进行前后端联调测试。

接下来使用两种方式分别测试：



#### 2.3.1 接口文档测试

**重启服务：**访问 http://localhost:8080/doc.html，进入员工分页查询

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604101257582.png" alt="image-20221112101848657" style="zoom:67%;" /> 

**响应结果：**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604101257678.png" alt="image-20221112101946022" style="zoom:50%;" /> 



#### 2.3.2 前后端联调测试

**点击员工管理**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604101257497.png" alt="image-20221112102441810" style="zoom:50%;" />  



**输入员工姓名为 zhangsan**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604101257848.png" alt="image-20221112102540938" style="zoom:50%;" /> 

不难发现，**最后操作时间格式**不清晰，在**代码完善**中解决。

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604101257557.png" alt="image-20221112102745437" style="zoom:50%;" /> 



### 2.4 代码完善

**问题描述：**操作时间字段显示有问题。

<img src="D:/Projects/1、黑马程序员Java项目《苍穹外卖》企业级开发实战/讲义/day02/assets/image-20221112103235539.png" alt="image-20221112103235539" style="zoom:50%;" /> 



**解决方式：**

**1).  方式一**

在属性上加上注解，对日期进行格式化

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604101315727.png" alt="image-20221112103501581" style="zoom:67%;" /> 

但这种方式，需要在每个时间属性上都要加上该注解，使用较麻烦，不能全局处理。



**2).  方式二（推荐 )**

在 WebMvcConfiguration 中扩展 SpringMVC 的消息转换器，统一对日期类型进行格式处理

```java
	/**
     * 扩展Spring MVC框架的消息转化器
     * @param converters
     */
    protected void extendMessageConverters(List<HttpMessageConverter<?>> converters) {
        log.info("扩展消息转换器...");
        //创建一个消息转换器对象
        MappingJackson2HttpMessageConverter converter = new MappingJackson2HttpMessageConverter();
        //需要为消息转换器设置一个对象转换器，对象转换器可以将Java对象序列化为json数据
        converter.setObjectMapper(new JacksonObjectMapper());
        //将自己的消息转化器加入容器中
        converters.add(0,converter);
    }
```

添加后，再次测试

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604101315368.png" alt="image-20221112104305608" style="zoom:67%;" /> 

时间格式定义，sky-common 模块中

```java
package com.sky.json;

public class JacksonObjectMapper extends ObjectMapper {

	//.......
    public static final String DEFAULT_DATE_TIME_FORMAT = "yyyy-MM-dd HH:mm";
    //.......

    }
}
```



## 3. 启用禁用员工账号

### 3.1 需求分析与设计

#### 3.1.1 产品原型

在员工管理列表页面，可以对某个员工账号进行启用或者禁用操作。账号禁用的员工不能登录系统，启用后的员工可以正常登录。如果某个员工账号状态为正常，则按钮显示为 "禁用"，如果员工账号状态为已禁用，则按钮显示为"启用"。

**启禁用员工原型：**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604101536970.png" alt="image-20221112112359233" style="zoom:67%;" /> 

**业务规则：**

- 可以对状态为 “启用” 的员工账号进行 “禁用” 操作
- 可以对状态为 “禁用” 的员工账号进行 “启用” 操作
- 状态为 “禁用” 的员工账号不能登录系统



#### 3.1.2 接口设计

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604101537088.png" alt="image-20221112112728333" style="zoom:50%;" /><img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604101537542.png" alt="image-20221112112739680" style="zoom:50%;" />



1). 路径参数携带状态值。

2). 同时，把 id 传递过去，明确对哪个用户进行操作。

3). 返回数据 code 状态是必须，其它是非必须。



### 3.2 代码开发

#### 3.2.1 Controller 层

在 sky-server 模块中，根据接口设计中的请求参数形式对应的在 EmployeeController 中创建启用禁用员工账号的方法：

```java
	/**
     * 启用禁用员工账号
     * @param status
     * @param id
     * @return
     */
    @PostMapping("/status/{status}")
    @ApiOperation(value = "启用禁用员工账号")
    public Result enableOrDisable(@PathVariable Integer status, Long id) {
        log.info("启用禁用员工账号：{}, {}", status, id);

        employeeService.enableOrDisable(status, id);

        return Result.success();
    }
```



#### 3.2.2 Service 层接口

在 EmployeeService 接口中声明启用禁用员工账号的业务方法：

```java
	/**
     * 启用禁用员工账号
     * @param status
     * @param id
     */
    void enableOrDisable(Integer status, Long id);
```



#### 3.2.3 Service 层实现类

在 EmployeeServiceImpl 中实现启用禁用员工账号的业务方法：

```java
	/**
     * 启用禁用员工账号
     * @param status
     * @param id
     */
    public void enableOrDisable(Integer status, Long id) {
        // update employee set status = ? where id = ?

        // 传统构造方法
        // Employee employee = new Employee();
        // employee.setStatus(status);
        // employee.setId(id);

        // 使用 builder 构造
        Employee employee = Employee.builder().status(status).id(id).build();

        employeeMapper.update(employee);
    }
```



#### 3.2.4 Mapper 层

在 EmployeeMapper 接口中声明 update 方法：

```java
	/**
     * 根据主键动态修改属性
     * @param employee
     */
    void update(Employee employee);
```

在 EmployeeMapper.xml 中编写 SQL：

```sql
	<update id="update" parameterType="com.sky.entity.Employee">
        update employee
        <set>
            <if test="name != null">name = #{name},</if>
            <if test="username != null">username = #{username},</if>
            <if test="password != null">password = #{password},</if>
            <if test="phone != null">phone = #{phone},</if>
            <if test="sex != null">sex = #{sex},</if>
            <if test="idNumber != null">id_number = #{idNumber},</if>
            <if test="updateTime != null">update_time = #{updateTime},</if>
            <if test="updateUser != null">update_user = #{updateUser},</if>
            <if test="status != null">status = #{status},</if>
        </set>
        where id = #{id}
    </update>
```



### 3.3 功能测试

#### 3.3.1 接口文档测试

**测试前，**查询 employee 表中员工账号状态

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604101611587.png" alt="image-20221112143142457" style="zoom:67%;" /> 

**开始测试**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604101612232.png" alt="image-20221112143316357" style="zoom:50%;" /> 

**测试完毕后**，再次查询员工账号状态

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604101612178.png" alt="image-20221112143428676" style="zoom: 67%;" /> 



#### 3.3.2 前后端联调测试

**测试前：**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604101612990.png" alt="image-20221112143552246" style="zoom: 33%;" /> 

**点击启用:**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604101612500.png" alt="image-20221112143655318" style="zoom:33%;" /> 



## 4. 编辑员工

### 4.1 需求分析与设计

#### 4.1.1 产品原型

在员工管理列表页面点击 "编辑" 按钮，跳转到编辑页面，在编辑页面回显员工信息并进行修改，最后点击 "保存" 按钮完成编辑操作。

**员工列表原型：**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604101706230.png" alt="image-20221112144731759" style="zoom: 67%;" /> 

**修改页面原型**：

注：点击修改时，数据应该正常回显到修改页面。

![image-20221112144842825](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604101718330.png) 



#### 4.1.2 接口设计

根据上述原型图分析，编辑员工功能涉及到两个接口：

- 根据 id 查询员工信息
- 编辑员工信息

**1). 根据 id 查询员工信息**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604101705592.png" alt="image-20221112145607939" style="zoom:50%;" /> <img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604101705522.png" alt="image-20221112145619775" style="zoom:50%;" />



**2). 编辑员工信息**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604101706955.png" alt="image-20221112145643769" style="zoom:50%;" /> <img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604101706263.png" alt="image-20221112145659035" style="zoom:50%;" />

**注:因为是修改功能，请求方式可设置为 PUT。**



### 4.2 代码开发

#### 4.2.1 回显员工信息功能

**1). Controller 层**

在 EmployeeController 中创建 getById 方法：

```java
	/**
     * 根据 id 查询员工信息
     * @param id
     * @return
     */
    @GetMapping("/{id}")
    @ApiOperation("根据id查询员工信息")
    public Result<Employee> getById(@PathVariable Long id){
        Employee employee = employeeService.getById(id);
        return Result.success(employee);
    }
```



**2). Service 层接口**

在 EmployeeService 接口中声明 getById 方法：

```java
    /**
     * 根据 id 查询员工信息
     * @param id
     * @return
     */
    Employee getById(Long id);
```



**3). Service 层实现类**

在 EmployeeServiceImpl 中实现 getById 方法：

```java
 	/**
     * 根据id查询员工信息
     *
     * @param id
     * @return
     */
    public Employee getById(Long id) {
        Employee employee = employeeMapper.getById(id);
        employee.setPassword("******");
        return employee;
    }
```



**4). Mapper 层**

在 EmployeeMapper 接口中声明 getById 方法：

```java
	/**
     * 根据 id 查询员工信息
     * @param id
     * @return
     */
    @Select("select * from employee where id = #{id}")
    Employee getById(Long id);
```



#### 4.2.2 修改员工信息功能

**1). Controller 层**

在 EmployeeController 中创建 update 方法：

```java
	/**
     * 编辑员工信息
     * @param employeeDTO
     * @return
     */
    @PutMapping
    @ApiOperation("编辑员工信息")
    public Result update(@RequestBody EmployeeDTO employeeDTO){
        log.info("编辑员工信息：{}", employeeDTO);
        employeeService.update(employeeDTO);
        return Result.success();
    }
```



**2). Service 层接口**

在 EmployeeService 接口中声明 update 方法：

```java
    /**
     * 编辑员工信息
     * @param employeeDTO
     */
    void update(EmployeeDTO employeeDTO);
```



**3). Service 层实现类**

在 EmployeeServiceImpl 中实现 update 方法：

```java
 	/**
     * 编辑员工信息
     *
     * @param employeeDTO
     */
    public void update(EmployeeDTO employeeDTO) {
        Employee employee = new Employee();
        BeanUtils.copyProperties(employeeDTO, employee);

        employee.setUpdateTime(LocalDateTime.now());
        employee.setUpdateUser(BaseContext.getCurrentId());

        employeeMapper.update(employee);
    }
```

在实现**启用禁用员工账号**功能时，已实现 employeeMapper.update(employee)，在此不需写 Mapper 层代码。



### 4.3 功能测试

#### 4.3.1 接口文档测试

分别测试**根据 id 查询员工信息**和**编辑员工信息**两个接口

**1). 根据 id 查询员工信息**

查询 employee 表中的数据，以 id=4 的记录为例

![image-20221112154253995](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604101754819.png)

开始测试

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604101754585.png" alt="image-20221112154411245" style="zoom:50%;" /> 

获取到了 id=4 的相关员工信息

**2). 编辑员工信息**

修改 id=4 的员工信息，**name** 由 **zhangsan** 改为**张三丰**，**username** 由**张三**改为 **zhangsanfeng**。

 <img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604101754765.png" alt="image-20221112155001414" style="zoom:50%;" /> 

查看 employee 表数据

![image-20221112155029547](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604101754092.png)



#### 4.3.2 前后端联调测试

进入到员工列表查询

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604101754558.png" alt="image-20221112155206712" style="zoom:50%;" /> 

对员工姓名为杰克的员工数据修改，点击修改，数据已回显

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604101754374.png" alt="image-20221112155430652" style="zoom:50%;" /> 

修改后，点击保存

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604101754003.png" alt="image-20221112155559298" style="zoom:50%;" /> 

