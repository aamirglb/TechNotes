from reportlab.platypus import SimpleDocTemplate, Paragraph
from reportlab.lib.styles import getSampleStyleSheet

pdf = SimpleDocTemplate('ExternalLink.pdf')

flow_obj = []
styles = getSampleStyleSheet()
text='''Visit <a href=www.google.com>Google</a><br></br>
        Visit <a href=www.bing.com>Bing</a><br></br>
        Visit <a href=www.gmail.com>Gmail</a><br></br>
        Go to <a href=https://www.google.com/maps/@17.3390841,76.8049206,13z><font color="blue"><u>Gulbarga</u></font></a> on google maps'''

para_text = Paragraph(text, style=styles["Normal"])
flow_obj.append(para_text)
pdf.build(flow_obj)