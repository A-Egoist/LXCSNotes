# webbench 压力测试

```bash
webbench -c 1000 -t 30 http://ip:port/
```

![image-20250615221756266](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202506152218864.png)

在使用 webbench 进行服务器压力测试时，正确填写 `http://ip:port/` 非常关键。以下是详细的填写指南：

### 1. 基本格式
```
http://[IP地址或域名]:[端口号]/
```

### 2. IP 地址填写规则

| 测试场景              | IP 填写方式                | 示例                       |
| --------------------- | -------------------------- | -------------------------- |
| **本地测试**          | `127.0.0.1` 或 `localhost` | `http://127.0.0.1:8080/`   |
| **同一内网其他机器**  | 目标服务器的内网 IP        | `http://192.168.1.100:80/` |
| **公网服务器测试**    | 服务器的公网 IP 或域名     | `http://203.0.113.5:8080/` |
| **Docker 容器内测试** | 宿主机的 Docker 网关 IP    | `http://172.17.0.1:8080/`  |

### 3. 端口号填写规则
- 填写你的 Web 服务器实际监听的端口
- 常见端口：
  - HTTP 默认端口：80（可省略端口号）
  - HTTPS 默认端口：443
  - 开发常用端口：8000, 8080, 8888 等

### 4. 具体场景示例

#### 场景 1：测试本机运行的服务器
```bash
# 服务器监听 8080 端口
webbench -c 1000 -t 30 http://127.0.0.1:8080/

# 如果使用默认80端口
webbench -c 1000 -t 30 http://localhost/
```

#### 场景 2：测试同一网络中的其他服务器
```bash
# 目标服务器 IP 192.168.1.100，端口 8080
webbench -c 1000 -t 30 http://192.168.1.100:8080/
```

#### 场景 3：测试 Docker 容器中的服务器
```bash
# 方法 1：从宿主机测试容器映射的端口
# 假设容器将 8080 映射到宿主机的 8080
webbench -c 1000 -t 30 http://127.0.0.1:8080/

# 方法 2：从另一个容器测试（使用容器名）
docker run --rm --link webserver:web tutum/curl curl http://web:8080/
```

### 5. 特殊符号处理
如果 URL 中包含特殊字符，需要正确转义：
```bash
# 测试带参数的路径
webbench -c 1000 -t 30 "http://example.com:8080/search?q=hello%20world"
```

### 6. 验证连接是否正常
在运行压力测试前，先用简单命令验证：
```bash
# 使用 curl 测试连接
curl -I http://127.0.0.1:8080/

# 预期返回类似：
# HTTP/1.1 200 OK
# Server: YourWebServer
# ...

# 使用 telnet 测试端口
telnet 127.0.0.1 8080
```

### 7. 常见错误及解决

| 错误信息                   | 原因                     | 解决方案                 |
| -------------------------- | ------------------------ | ------------------------ |
| `Connect to server failed` | IP或端口错误             | 检查服务器IP和监听端口   |
| `Bad file descriptor`      | 超过系统文件描述符限制   | `ulimit -n 65536`        |
| `Childrens 0 - died`       | 服务器崩溃或无响应       | 检查服务器日志和资源使用 |
| `Socket I/O timed out`     | 网络延迟高或服务器响应慢 | 减少并发数(-c)           |

### 8. 完整测试示例
```bash
# 测试公网服务器，1000并发，持续60秒
webbench -c 1000 -t 60 http://203.0.113.5:8080/api/v1/users

# 结果示例：
Webbench - Simple Web Benchmark 1.5
Copyright (c) Radim Kolar 1997-2004, GPL Open Source Software.

Request:
GET /api/v1/users HTTP/1.0
User-Agent: WebBench 1.5
Host: 203.0.113.5

Runing info: 1000 clients, running 60 sec.

Speed=24563 pages/min, 38762421 bytes/sec.
Requests: 24563 susceed, 0 failed.
```

### 9. 高级技巧

1. **测试 HTTPS 服务**：
   ```bash
   # 安装支持HTTPS的版本
   git clone https://github.com/ErikDubbelboer/webbench-https
   cd webbench-https
   make
   
   # 测试HTTPS
   ./webbench -c 500 -t 30 https://example.com:443/
   ```

2. **保持连接（HTTP Keep-Alive）**：
   ```bash
   webbench -k -c 1000 -t 30 http://127.0.0.1:8080/
   ```

3. **自定义HTTP头**：
   ```bash
   webbench -H "Authorization: Bearer token123" -c 100 -t 10 http://api.example.com/
   ```

4. **测试不同端点**：
   ```bash
   # 测试首页
   webbench -c 1000 -t 30 http://127.0.0.1:8080/
   
   # 测试API接口
   webbench -c 500 -t 30 http://127.0.0.1:8080/api/v1/data
   
   # 测试静态资源
   webbench -c 2000 -t 30 http://127.0.0.1:8080/static/image.jpg
   ```

### 10. 最佳实践建议

1. **渐进式测试**：
   ```bash
   # 从低并发开始，逐步增加
   webbench -c 100 -t 10 http://127.0.0.1:8080/
   webbench -c 500 -t 30 http://127.0.0.1:8080/
   webbench -c 1000 -t 60 http://127.0.0.1:8080/
   ```

2. **监控服务器资源**：
   ```bash
   # 在测试同时监控服务器
   watch -n 1 "echo 'CPU: '; top -bn1 | head -5; echo; echo 'Memory: '; free -m; echo; echo 'TCP: '; netstat -ant | awk '{print $6}' | sort | uniq -c"
   ```

3. **结合其他工具**：
   ```bash
   # 使用 ab (Apache Bench) 对比测试
   ab -n 100000 -c 1000 http://127.0.0.1:8080/
   
   # 使用 wrk 进行更高级测试
   wrk -t12 -c1000 -d30s http://127.0.0.1:8080/
   ```

4. **分析测试结果**：
   - 成功请求数 vs 失败请求数
   - 页面/分钟 速率
   - 字节/秒 吞吐量
   - 结合服务器日志分析错误原因

通过以上指南，您应该能够正确填写 webbench 命令中的 IP 和端口参数，并有效进行服务器压力测试。