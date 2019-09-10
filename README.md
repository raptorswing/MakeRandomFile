# MakeRandomFile
Command line utility that creates files with random contents.

I needed a tool to create files of specific sizes with random contents.
I was on Windows so I couldn't just `dd if=/dev/urandom of=file bs=5050` and I wanted something more efficient than PowerShell.
So I wrote this pretty simple utility
