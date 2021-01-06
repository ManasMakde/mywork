########################### gives live subscriber count ################
from time import sleep
from tkinter import *
import requests
import threading

def sub_counter():
    global sub_count
    global channel_id

    while True:
        try:
            html_text = requests.get("https://www.youtube.com/channel/" + channel_id + "/about").text
            s = html_text.split('"')
            n = s.index("subscriberCountText")
            sub_count = s[n + 4]
        except:
            sub_count = "network issues..."
        label.config(text=sub_count)
        sleep(5)

window = Tk()

window.title("Sub counter")
window.geometry("300x50")
window.resizable(0,0)

label = Label(text="starting...")
label.grid(row =0, column=1)
channel_id="UCB86RbiIrnAlArbDpZfPAMQ"
threading.Thread(target=sub_counter).start()
window.attributes('-topmost', True)

window.mainloop()
