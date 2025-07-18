1.   编写 Python 脚本, 用于获取本机 IP 并发送到指定邮箱

     ```python
     # -*- coding: utf-8 -*- 
     # @File : send_host_ip_to_qq_mail.py
     # @Software : Visual Studio Code
     from subprocess import Popen, PIPE
     import smtplib
     from email.header import Header
     from email.mime.multipart import MIMEMultipart
     from email.mime.text import MIMEText
     from time import asctime
     import os
     
     
     def get_ip():
         p = Popen('hostname -I', shell=True, stdout=PIPE)
         ip = p.stdout.read()
         ip = str(ip, encoding='utf-8').strip()
         return ip
     
     
     def send_mail(parameters):
         try:
             mail_host = parameters['mail_host']
             mail_authorization_code = parameters['mail_authorization_code']
             mail_sender = parameters['mail_sender']
             mail_receiver = parameters['mail_receiver']
             mail_topic = parameters['mail_topic']
             mail_time = parameters['mail_time']
             mail_content = parameters['mail_content']
             mail_message = MIMEMultipart()
             mail_message['From'] = Header(mail_sender)
             mail_message['Subject'] = Header(mail_topic)
             mail_message.attach(MIMEText(mail_time + '\n' + mail_content, 'plain', 'utf-8'))
     
             server = smtplib.SMTP_SSL(mail_host, 465)
             server.login(mail_sender, mail_authorization_code)
             server.sendmail(mail_sender, mail_receiver, mail_message.as_string())
             server.quit()
             print('Success')
         except Exception:
             print('Failure')
     
     
     if __name__ == '__main__':
         with open('/home/username/SendHostIP/ip_old.txt', 'r', encoding='utf-8') as f:
             ip_old = f.read()
         ip = get_ip()
         if ip != ip_old:
             with open('/home/username/SendHostIP/ip_old.txt', 'w', encoding='utf-8') as f:
                 f.write(ip)
             parameters = {'mail_host': 'smtp.qq.com',
                         'mail_authorization_code': '在邮箱设置中查看 smtp 授权码',
                         'mail_sender': '发送邮箱',
                         'mail_receiver': '接收邮箱',
                         'mail_topic': 'The IP address of my Ubuntu server',
                         'mail_time': asctime(),
                         'mail_content': ip}
             send_mail(parameters=parameters)
     
     ```

2.   编写执行脚本

     ```bash
     #! /bin/bash
     # send_host_ip_to_qq_mail.sh
     /home/username/anaconda3/bin/python /home/username/SendHostIP/send_host_ip_to_qq_mail.py
     ```

3.   在 Ubuntu 系统中设置脚本开机自启动

     1.   在 `/etc/systemd/system/` 中创建服务文件

          ```bash
          sudo vi /etc/systemd/system/SendHostIP.service
          ```

     2.   在打开的文件中添加如下内容, 然后退出并保存

          ```bash
          [Unit]
          Description=SendHostIP
          After=network.target
          StartLimitIntervalSec=0
          
          [Service]
          Restart=always
          RestartSec=60
          ExecStart=/home/username/SendHostIP/send_host_ip_to_qq_mail.sh
           
          [Install]
          WantedBy=multi-user.target
          ```
     
          其中, `ExecStart` 指定脚本的绝对路径
     
     3.   给服务和脚本设置权限
     
          ```bash
          sudo chmod 777 /home/username/SendHostIP/send_host_ip_to_qq_mail.sh
          sudo chmod 777 /etc/systemd/system/SendHostIP.service
          ```
     
     4.   重新加载服务的配置文件, 并将服务设置为开机自启动
     
          ```bash
          sudo systemctl daemon-reload
          sudo systemctl enable SendHostIP.service
          ```
     
     5.   然后重启主机, 查看服务状态
     
          ```bash
          sudo systemctl status SendHostIP.service
          ```
     
          

