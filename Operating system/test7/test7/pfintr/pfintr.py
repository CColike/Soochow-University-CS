import re
import time

def get_page_fault():
    pgfault = -1
    with open('/proc/vmstat', 'r') as vmstat:
        match = re.search(r'pgfault\s(\d+)', vmstat.read())
        if match:
            pgfault = int(match.group(1))
    return pgfault

if __name__=="__main__":
    print("Use time: 5s")
    pgfault1 = get_page_fault()
    if pgfault1 < 0:
        print('read file error!')
        exit(1)
    print("Now the number of page fault is "+str(pgfault1))
    time.sleep(5) 
    pgfault2 = get_page_fault()
    if pgfault2 < 0:
        print('read file error!')
        exit(1)
    print("Now the number of page fault is "+str(pgfault2))
    page_fault = pgfault2 - pgfault1
    print("In 5 seconds,system calls "+str(page_fault)+" page fault!")
