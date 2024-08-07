from pygments import formatters, highlight, lexers
code = "print('Hello World!!')"
text = highlight(code, lexers.Python3Lexer(), formatters.HtmlFormatter())
print(text)
print(formatters.HtmlFormatter().get_style_defs())