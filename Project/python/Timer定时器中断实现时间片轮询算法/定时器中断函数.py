import threading
import schedule
import time

def Start_Timer():
    global timer
    if not Stop_Timer_Flag:
        timer = threading.Timer(InteruptTime,InteruptFuction)
        #Turn on the Timer again
        timer.start()

def Stop_Timer():
    global Stop_Timer_Flag
    Stop_Timer_Flag = True
    if timer is not None:
        timer.cancel()
    print("Program interrupted and stopped.")

def InteruptFuction():
    print("Interupt")
    Start_Timer()


if __name__ == '__main__':
    InteruptTime = 0.5
    timer = None
    Stop_Timer_Flag = False

    timer = threading.Timer(InteruptTime,InteruptFuction)
    timer.start()
    print("Waiting for Interupt!")
    try:
        while(True):
            pass
    except KeyboardInterrupt:
        #cancle the Timer if it's still going
        Stop_Timer()