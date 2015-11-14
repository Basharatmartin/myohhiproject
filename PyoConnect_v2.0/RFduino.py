#!/usr/bin/python
# RFduino.py by Basharat

import subprocess
import re

class RFduino:
    def __init__(self, mac, name):
        self.mac = mac
        self.name = name
        
    def find (self):
        cmd = 'timeout -s INT 0.5 hcitool lescan'
        p = subprocess.Popen(cmd, bufsize = 0,shell = True, stdout = subprocess.PIPE, stderr = subprocess.STDOUT) 
        (out, err) = p.communicate()
        m = re.search('(.*?) ' + self.name, out) 
        if m:
            self.mac = m.group(1)
            return True
        return False
   

    def send(self, msg):
        ''' sending the emg data !!! '''
        if not self.mac:
            raise Exception("Maybe MAC is wrong ? .. Human_error :P")
            

        ### Manisha ,,, starts !!

        string = str(msg)
        msg = string.replace(',' ,' ').replace('(','').replace(')','')
        
        print msg

        ##### Manisha,,, ends !!!
  
        msg_hex = "".join([hex(ord(c))[2:].zfill(2) for c in msg])
        cmd = "gatttool -b %s -t random --char-write --handle=0x0011 --value=%s" %  (self.mac, msg_hex)
        p = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
        (out, error) = p.communicate()

    def read(self):
        if not self.mac:
            raise Exception("MAC is matched or wrong maybe.. bluetooth is not connected !!!")
   
        cmd = "gatttool -b %s -t random --char-read --handle=0x000e" % (self.mac)
        p = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
        (out, error) = p.communicate()
        out = out.replace(" ", "").strip().split(":")[1]
        return out.decode("hex")
    
