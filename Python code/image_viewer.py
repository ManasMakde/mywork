########## practice project ###########
from tkinter import *
from PIL import ImageTk
from tkinter import filedialog
import os

current_pic=0
img_list = list()
dir_name=''
########## finding all images in a directory and assinging them to img_list #########
def assign_img(dir_name=''):
    extensions = ["jpg", "png", "jpeg", "gif"]
    img_list.clear()
    if dir_name=='':
        lst = os.listdir()
    else:
        lst = os.listdir(dir_name)

    for i in lst:
        i_list = str(i).split(".")
        if i_list[len(i_list) - 1].lower() in extensions:
            img_list.append((dir_name+"/" if dir_name!='' else '')+i)

assign_img()
print(img_list)
####################################################################################


def show_img():
    global lbl_img
    global tmp
    global current_pic
    try:
        tmp = ImageTk.PhotoImage(file=img_list[current_pic])
        lbl_img = Label(image=tmp)
    except:
        lbl_img = Label(text="no images found in current directory...")
    lbl_img.grid(row=2, column=0, columnspan=100,sticky=W+E)


def stat(n=0):
    global stat_lbl
    global current_pic
    global img_list
    if n==0:
        stat_lbl.grid_forget()
    stat_lbl = Label(text="showing image " + str(current_pic+1 if len(img_list)!=0 else 0) + " out of " + str(len(img_list)), relief=SUNKEN,padx=20,anchor=E)
    stat_lbl.grid(row=1, column=0, pady=10, columnspan=10,sticky=W+E)


def change_f():
    global lbl_img
    global current_pic
    global tmp

    lbl_img.grid_forget()
    current_pic = 0 if current_pic+1 == len(img_list) else current_pic+1
    show_img()
    stat()

def change_b():
    global lbl_img
    global tmp
    global current_pic

    lbl_img.grid_forget()
    current_pic = len(img_list)-1 if current_pic-1 <0 else current_pic-1
    show_img()
    stat()

def assign_dir():
    global lbl_img
    global tmp
    global current_pic

    d_name = filedialog.askdirectory()
    assign_img(d_name)
    print(img_list)
    current_pic=0
    change_b()
    stat()


window=Tk()


back_btn=Button(text="<<",width=10,command=change_b).grid(row=0,column=0,padx=5,pady=5)
exit=Button(text="exit",command=quit).grid(row=0,column=1,padx=5,pady=5)
dir_btn=Button(text="dir",command=assign_dir).grid(row=0,column=2)
next_btn=Button(text=">>",width=10,command=change_f).grid(row=0,column=3,padx=5,pady=5)

show_img()
stat(1)
window.title("images")
mainloop()
