
import os
import shutil
import numpy as np
import pandas as pd
import calendar
from datetime import datetime
from fpdf import FPDF

import matplotlib.pyplot as plt
from matplotlib import rcParams

rcParams['axes.spines.top'] = False
rcParams['axes.spines.right'] = False

def generate_sales_data(month: int) -> pd.DataFrame:
    dates = pd.date_range(
        start=datetime(year=2020, month=month, day=1),
        end=datetime(year=2020, month=month, day=calendar.monthrange(2020, month)[1])
    )

    sales = np.random.randint(low=500, high=2500, size=len(dates))
    return pd.DataFrame({
        'Date': dates,
        'ItemSold': sales
    })

def plot(data: pd.DataFrame, filename: str) -> None:
    plt.figure(figsize=(12, 4))
    plt.grid(color='#f2f2f2', alpha=1, zorder=9)
    plt.plot(data['Date'], data['ItemSold'], color='#087e8b', lw=3, zorder=5)
    plt.title(f'Sales 2020/{data["Date"].dt.month[0]}', fontsize=17)
    plt.xlabel('Period', fontsize=13)
    plt.xticks(fontsize=9)
    plt.ylabel('Number of items sold', fontsize=13)
    plt.yticks(fontsize=9)
    plt.savefig(filename, dpi=300, bbox_inches='tight', pad_inches=0)
    plt.close()
    return

PLOT_DIR = 'plots'

def construct():
    try:
        shutil.rmtree(PLOT_DIR)
        os.mkdir(PLOT_DIR)
    except FileNotFoundError:
        os.mkdir(PLOT_DIR)

    for i in range(2, 13):
        plot(data=generate_sales_data(month=i), filename=f'{PLOT_DIR}/{i}.png')

    counter = 0
    pages_data = []
    temp = []
    files = os.listdir(PLOT_DIR)
    files = sorted(os.listdir(PLOT_DIR), key=lambda x: int(x.split('.')[0]))
    for fname in files:
        if counter == 3:
            pages_data.append(temp)
            temp = []
            counter = 0

        temp.append(f'{PLOT_DIR}/{fname}')
        counter += 1
    return [*pages_data, temp]

class PDF(FPDF):
    def __init__(self):
        super().__init__()
        self.WIDTH = 210
        self.HEIGHT = 297

    def header(self):
        # self.image('assets/logo.png', 10, 8, 33)
        # self.set_font('Aerial', 'B', 11)
        self.cell(self.WIDTH - 80)
        self.cell(60, 1, 'Sales Report', 0, 0, 'R')
        self.ln(20)

    def footer(self):
        self.set_y(-15)
        self.set_font('Arial', 'I', 8)
        self.set_text_color(128)
        self.cell(0, 10, 'Page ' + str(self.page_no()), 0, 0, 'C')

    def page_body(self, images):
        if len(images) == 3:
            self.image(images[0], 15, 25, self.WIDTH - 30)
            self.image(images[1], 15, self.WIDTH/ 2 + 5, self.WIDTH - 30)
            self.image(images[2], 15, self.WIDTH / 2 + 90, self.WIDTH - 30)
        elif len(images) == 2:
            self.image(images[0], 15, 25, self.WIDTH - 30)
            self.image(images[1], 15, self.WIDTH / 2 + 5, self.WIDTH - 30)
        else:
            self.image(images[0], 15, 25, self.WIDTH - 30)

    def print_page(self, images):
        self.add_page()
        self.page_body(images)

pdf = PDF()

plots_per_page = construct()
for elem in plots_per_page:
    pdf.print_page(elem)

pdf.output('SalesReport.pdf', 'F')


# plots_per_page = construct()
# print(type(plots_per_page))
# print(plots_per_page)
#plt.imshow(plots_per_page)

# d = generate_sales_data(month=3)
#plot(data=d, filename='december.png')