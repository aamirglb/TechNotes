#!/usr/bin/env python3

# Script to plot smartlink logs and save them as PNG file
import os
import csv
import sys
from datetime import datetime
import matplotlib.pyplot as plt
from matplotlib.dates import DateFormatter
import numpy as np

from reportlab.pdfgen import canvas

from reportlab.platypus import SimpleDocTemplate, Table, TableStyle, Image
from reportlab.lib import colors
from reportlab.lib.pagesizes import A4
from reportlab.lib.units import inch
from reportlab.lib.styles import getSampleStyleSheet

if len(sys.argv) < 2:
    print("Usage: plot_tool.py file1 [file2 ...]")
    exit()

dt = []
cpu_temp = []
cpu_load = []
mem_used = []

for i in range(1, len(sys.argv)):
    sys_id = sys.argv[i].split('_')[1]
    sys_id = int(sys_id[2:])
    print('Parsing file {}. SYS_ID: {}'.format(sys.argv[i], sys_id))
    with open(sys.argv[i]) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        header = []
        header = next(csv_reader)
        # FIXME!! Last line is NULL
        try:
            # format of log entry is: date,time,cpu_temp,cpu_load,total_mem,free_mem,used_mem
            for row in csv_reader:
                date_str = '{} {}'.format(row[0], row[1])
                date_time = datetime.strptime(date_str, '%d-%m-%Y %H:%M:%S')
                dt.append(date_time)
                #print(datetime.combine(datetime.date(row[0]), datetime.time(row[1])))
                cpu_temp.append(float(row[2]))
                cpu_load.append(float(row[3]))
                total = float(row[4])
                used = float(row[6])
                percent = (used * 100) / total
                mem_used.append(percent)
        except Exception as e:
            pass

images = []

# plot cpu temperature
fig, ax = plt.subplots()
ax.plot(dt, cpu_temp)
plt.xticks(rotation=45)
ax.xaxis.set_major_formatter(DateFormatter('%H:%M:%S'))
ax.set_title(f'UAV-{sys_id} Smartlink CPU Temperature')
ax.set_ylabel('\u00B0C', rotation=0)
ax.set_ylim(ymin=0, ymax=100)
#plt.axhline(y=85, color='r', linestyle='-')
plt.savefig(f'sl-{sys_id}_cpu_temp.png', bbox_inches='tight')
images.append(f'sl-{sys_id}_cpu_temp.png')

fig, ax = plt.subplots()
ax.plot(dt, cpu_load)
plt.xticks(rotation=45)
ax.xaxis.set_major_formatter(DateFormatter('%H:%M:%S'))
ax.set_title(f'UAV-{sys_id} Smartlink CPU Load')
ax.set_ylabel('%', rotation=0)
ax.set_ylim(ymin=0, ymax=100)
plt.savefig(f'sl-{sys_id}_cpu_load.png', bbox_inches='tight')
images.append(f'sl-{sys_id}_cpu_load.png')

fig, ax = plt.subplots()
ax.plot(dt, mem_used)
plt.xticks(rotation=45)
ax.set_title(f'UAV-{sys_id} Memory Usage')
ax.set_ylabel('%', rotation=0)
ax.set_ylim(ymin=0, ymax=100)
plt.savefig(f'sl-{sys_id}_mem_use.png', bbox_inches='tight')
images.append(f'sl-{sys_id}_mem_use.png')
#plt.show()

def add_header_footer(c: canvas.Canvas, page_no: int):
    c.saveState() 
    c.setStrokeColor(colors.black)
    c.drawImage('report_logo.png', width - (2.0 * inch), height - (.5 * inch), 1.8*inch, .2*inch, preserveAspectRatio=False)
    c.line(.3*inch, .7*inch, width - (.3*inch), .7*inch)

    c.setFont('Times-Roman', 12)
    c.setFillColor(colors.black)
    c.drawCentredString(width/2 - (.1*inch), .5*inch, f'Page {page_no}')
    c.restoreState()

_canvas = canvas.Canvas('smartlink_report.pdf', pagesize=A4)
width, height = A4
print(f'{width}, {height}, {inch}')

for i in range(5):
    add_header_footer(_canvas, i+1)
    _canvas.showPage()

_canvas.save()