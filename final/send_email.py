from email.mime.multipart import MIMEMultipart
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
import smtplib

from config import PASSWD
def sendMail(text):
    content = MIMEMultipart()  #建立MIMEMultipart物件
    content["subject"] = "Subject"  #郵件標題
    content["from"] = "ghostcheng.00@gmail.com"  #寄件者
    content["to"] = "t110590001@ntut.org.tw" #收件者
    content.attach(MIMEText("final text = "+text))  #郵件內容

    with smtplib.SMTP(host="smtp.gmail.com", port="587") as smtp:  # 設定SMTP伺服器
        try:
            smtp.ehlo()  # 驗證SMTP伺服器
            smtp.starttls()  # 建立加密傳輸
            smtp.login("ghostcheng.00@gmail.com", PASSWD)  # 登入寄件者gmail
            smtp.send_message(content)  # 寄送郵件
            print("Complete!")
        except Exception as e:
            print("Error message: ", e)