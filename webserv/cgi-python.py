#! /usr/bin/env python3

import html

header = "Content-type: text/html\r\n\r\n"

html = """<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <title>Current date</title>
</head>
<body>
  <p>
  Date: TODAY
  </p>
  <p>
  Hit count: too much
  </p>
</body>
</html>"""

print(header + html)