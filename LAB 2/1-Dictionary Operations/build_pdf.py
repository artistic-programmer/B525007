import os
import base64
import subprocess

def get_base64_image(image_path):
    with open(image_path, "rb") as image_file:
        return base64.b64encode(image_file.read()).decode('utf-8')

# Read source files and strip blank lines
src_dir = "src"
code_files = [
    "dictionary.h",
    "unsorted_array.c",
    "sorted_array.c",
    "singly_unsorted.c",
    "singly_sorted.c",
    "doubly_unsorted.c",
    "doubly_sorted.c",
    "main.c"
]

code_sections = []
for fname in code_files:
    fpath = os.path.join(src_dir, fname)
    with open(fpath, "r", encoding="utf-8") as f:
        lines = f.readlines()
    # Strip completely blank lines
    non_blank_lines = [line for line in lines if line.strip() != ""]
    clean_code = "".join(non_blank_lines)
    code_sections.append((fname, clean_code))

# Read images and convert to base64
plots = [
    ("Search Operation", "plots/search_performance.png"),
    ("Insert Operation", "plots/insert_performance.png"),
    ("Delete Operation", "plots/delete_performance.png"),
    ("Minimum Operation", "plots/min_performance.png"),
    ("Maximum Operation", "plots/max_performance.png"),
    ("Predecessor Operation", "plots/predecessor_performance.png"),
    ("Successor Operation", "plots/successor_performance.png")
]

plot_elements = []
for title, ppath in plots:
    b64_img = get_base64_image(ppath)
    plot_elements.append((title, f"data:image/png;base64,{b64_img}"))

# Concise, well-balanced HTML Template
html_content = f"""<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<title>Dictionary Operations</title>
<style>
  @page {{
    size: A4;
    margin: 10mm 12mm 10mm 12mm;
  }}
  body {{
    font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Arial, sans-serif;
    font-size: 8.5pt;
    line-height: 1.3;
    color: #1e293b;
    margin: 0;
    padding: 0;
  }}
  h1 {{
    font-size: 15pt;
    font-weight: 700;
    margin: 0 0 8px 0;
    text-align: center;
    color: #0f172a;
    border-bottom: 1.5pt solid #2563eb;
    padding-bottom: 4px;
  }}
  h2 {{
    font-size: 10.5pt;
    font-weight: 600;
    margin: 10px 0 4px 0;
    color: #1e293b;
    border-bottom: 0.8pt solid #cbd5e1;
    padding-bottom: 2px;
  }}
  table {{
    width: 100%;
    border-collapse: collapse;
    margin: 4px 0 8px 0;
    font-size: 7.8pt;
  }}
  th, td {{
    border: 0.5pt solid #cbd5e1;
    padding: 4px 6px;
    text-align: center;
  }}
  th {{
    background-color: #f1f5f9;
    font-weight: 600;
    color: #0f172a;
  }}
  tr:nth-child(even) {{
    background-color: #f8fafc;
  }}
  .plots-grid {{
    display: grid;
    grid-template-columns: 1fr 1fr;
    gap: 8px;
    margin-bottom: 8px;
  }}
  .plot-card {{
    border: 0.5pt solid #e2e8f0;
    border-radius: 3px;
    padding: 4px;
    background: #ffffff;
    text-align: center;
    page-break-inside: avoid;
  }}
  .plot-card img {{
    width: 100%;
    height: auto;
    display: block;
    border-radius: 2px;
  }}
  .plot-title {{
    font-weight: 600;
    font-size: 8pt;
    margin-bottom: 2px;
    color: #0f172a;
  }}
  .code-container {{
    column-count: 2;
    column-gap: 8px;
  }}
  .code-block {{
    border: 0.5pt solid #cbd5e1;
    border-radius: 3px;
    background: #f8fafc;
    overflow: hidden;
    margin-bottom: 6px;
    break-inside: auto;
  }}
  .code-header {{
    background: #f1f5f9;
    font-weight: 600;
    font-size: 7.5pt;
    padding: 3px 6px;
    color: #0f172a;
    border-bottom: 0.5pt solid #cbd5e1;
  }}
  pre {{
    margin: 0;
    padding: 4px 6px;
    font-family: "Consolas", "Courier New", monospace;
    font-size: 6.8pt;
    line-height: 1.18;
    white-space: pre-wrap;
    word-break: break-all;
    color: #0f172a;
  }}
</style>
</head>
<body>

<h1>Dictionary Operations</h1>

<h2>1. Asymptotic Worst-Case Complexity Analysis</h2>
<table>
  <thead>
    <tr>
      <th>Data Structure</th>
      <th>Search</th>
      <th>Insert</th>
      <th>Delete</th>
      <th>Min</th>
      <th>Max</th>
      <th>Predecessor</th>
      <th>Successor</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><strong>Unsorted Array</strong></td>
      <td>O(n)</td>
      <td>O(1)</td>
      <td>O(1)</td>
      <td>O(n)</td>
      <td>O(n)</td>
      <td>O(n)</td>
      <td>O(n)</td>
    </tr>
    <tr>
      <td><strong>Sorted Array</strong></td>
      <td>O(log n)</td>
      <td>O(n)</td>
      <td>O(n)</td>
      <td>O(1)</td>
      <td>O(1)</td>
      <td>O(1)</td>
      <td>O(1)</td>
    </tr>
    <tr>
      <td><strong>Singly Unsorted List</strong></td>
      <td>O(n)</td>
      <td>O(1)</td>
      <td>O(n)</td>
      <td>O(n)</td>
      <td>O(n)</td>
      <td>O(n)</td>
      <td>O(n)</td>
    </tr>
    <tr>
      <td><strong>Singly Sorted List</strong></td>
      <td>O(n)</td>
      <td>O(n)</td>
      <td>O(n)</td>
      <td>O(1)</td>
      <td>O(1)</td>
      <td>O(n)</td>
      <td>O(1)</td>
    </tr>
    <tr>
      <td><strong>Doubly Unsorted List</strong></td>
      <td>O(n)</td>
      <td>O(1)</td>
      <td>O(1)</td>
      <td>O(n)</td>
      <td>O(n)</td>
      <td>O(n)</td>
      <td>O(n)</td>
    </tr>
    <tr>
      <td><strong>Doubly Sorted List</strong></td>
      <td>O(n)</td>
      <td>O(n)</td>
      <td>O(1)</td>
      <td>O(1)</td>
      <td>O(1)</td>
      <td>O(1)</td>
      <td>O(1)</td>
    </tr>
  </tbody>
</table>

<h2>2. Empirical Performance Plots</h2>
<div class="plots-grid">
"""

for title, img_src in plot_elements:
    html_content += f"""  <div class="plot-card">
    <div class="plot-title">{title}</div>
    <img src="{img_src}" alt="{title}">
  </div>
"""

html_content += """</div>

<h2>3. Source Code</h2>
<div class="code-container">
"""

for fname, code_text in code_sections:
    escaped_code = code_text.replace("&", "&amp;").replace("<", "&lt;").replace(">", "&gt;")
    html_content += f"""  <div class="code-block">
    <div class="code-header">{fname}</div>
    <pre>{escaped_code}</pre>
  </div>
"""

html_content += """</div>

</body>
</html>
"""

with open("document.html", "w", encoding="utf-8") as f:
    f.write(html_content)

# Convert HTML to PDF using MS Edge headless
edge_path = r"C:\Program Files (x86)\Microsoft\Edge\Application\msedge.exe"
output_pdf = "Dictionary_Operations.pdf"

cmd = [
    edge_path,
    "--headless",
    "--disable-gpu",
    "--no-pdf-header-footer",
    f"--print-to-pdf={os.path.abspath(output_pdf)}",
    os.path.abspath("document.html")
]

subprocess.run(cmd, check=True)
print(f"PDF successfully updated: {output_pdf}")
