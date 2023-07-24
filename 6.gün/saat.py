from tkinter import *
from time import * 
import datetime

ekran=Tk()
ekran.title('Fenerbahce Saat')

def saat():
    metin=strftime("%H:%M:%S")
    label.config(text=metin)
    label.after(1000,saat)


label=Label(ekran,font=("ds-digital",100),background="blue",foreground="yellow")
label.pack(anchor="center")
saat()
mainloop()

