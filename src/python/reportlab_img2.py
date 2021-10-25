from reportlab.lib import styles
from reportlab.platypus import Paragraph, SimpleDocTemplate, Table, TableStyle, Image
from reportlab.lib import colors
from reportlab.lib.styles import getSampleStyleSheet

pdf = SimpleDocTemplate('template.pdf')
flow_obj = []
styles = getSampleStyleSheet()
img1 = Image('../../images/gstreamer/colors.png', 50, 50)
img2 = Image('../../images/gstreamer/gamut.png', 50, 50)
t = Table([[img1 for _ in range(6)],
            [img2 for _ in range(6)],
            [x for x in range(1, 7)]
          ])

t_style = TableStyle([("BOX", (0, 0), (-1, -1), 2, colors.red),
                      ("GRID", (0,0), (-1, -1), 2, colors.black),
                      ("BACKGROUND", (0,0), (-1, -1), colors.lightgrey)
                    ])

t.setStyle(t_style)
flow_obj.append(t)
pdf.build(flow_obj)