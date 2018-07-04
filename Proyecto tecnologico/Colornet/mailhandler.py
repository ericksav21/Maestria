# -*- coding: utf-8 -*-

from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from email.mime.image import MIMEImage
import numpy as np
import skimage.data
import smtplib
import os, sys

def send_email(fromaddr, toaddr, subject, body, password, img_list):
	msg = MIMEMultipart()
	msg['From'] = fromaddr
	msg['To'] = toaddr
	msg['Subject'] = subject
	msg.attach(MIMEText(body, 'plain'))
	if len(img_list) > 0:
		for i in range(len(img_list)):
			try:
				img_data = open(img_list[i], 'rb').read()
			except:
				continue
			image = MIMEImage(img_data, name = os.path.basename(img_list[i]))
			msg.attach(image)

	server = smtplib.SMTP('smtp.gmail.com', 587)
	server.ehlo()
	server.starttls()
	server.login(fromaddr, password)
	text = msg.as_string()
	server.sendmail(fromaddr, toaddr, text)
	server.quit()