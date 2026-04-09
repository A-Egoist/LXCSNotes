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

