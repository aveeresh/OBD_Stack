@echo off

pyi-makespec --onefile ScanTool.py
pyinstaller --clean ScanTool.spec

mv .\dist\ScanTool.exe .
rm -rf .\dist
