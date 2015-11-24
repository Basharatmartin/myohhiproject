#!/usr/bin/python
# RFduino.py by Basharat

import subprocess
import re
#import ctypes


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
        
        ''' Manisha's coding '''
        
        
        #msg = str(msg)
        #msg = msg.replace(',' ,' ').replace('(','').replace(')','') 
        
        #msg = msg/2
        #print msg
        ####           0x11111111-1111111
        
        
        msg1 = msg[0] / 4
        msg2 = msg[1] / 4
        msg3 = msg[2] / 4
        msg4 = msg[3] / 4
        msg5 = msg[4] / 4
        msg6 = msg[5] / 4
        msg7 = msg[6] / 4
        
        if (msg1 > 255):
            msg1 = 255
        if (msg2 > 255):
            msg2 = 255
        if (msg3 > 255):
            msg3 = 255
        if (msg4 > 255):
            msg4 = 255
        if (msg5 > 255):
            msg5 = 255
        if (msg6 > 255):
            msg6 = 255
        if (msg7 > 255):
            msg7 = 255            


        Mask = (msg1 << 24) | (msg2 << 16) | (msg3 << 8) | msg4
        print msg1, msg2, msg3, msg4, '0x%08x' % Mask
    
        
        '''        
        if ( (msg1 > 255) and (msg2 > 255) and (msg3 > 255) and (msg4 > 255)):
            msg1 = 255
            msg2 = 255
            msg3 = 255
            msg4 = 255
            Mask = (msg1 << 24) | (msg2 << 16) | (msg3 << 8) | msg4              
            #Mask = (Mask)        
            print msg1, msg2, msg3, msg4, Mask
        else:                  
            Mask = (msg1 << 24) | (msg2 << 16) | (msg3 << 8) | msg4              
            #Mask = (Mask)        
            print msg1, msg2, msg3, msg4, Mask
        '''
        #Mask = 'ff'
        #print msg1, msg2, msg3, msg4, Mask
        #print msg/2
        #msg = (0xff00 | msg)
        
        #msg = 0x0000 & msg
        
        
        #msg = 0x000f | msg
        
        #array = ['0x1d', '0x2a', '0x45','0x23']
        
        #msg1 = array
    
        #print msg  
        
        ''' finished '''
        #print msg
        #msg_hex = "".join([hex(ord(c))[2:].zfill(2) for c in msg])
        cmd = "gatttool -b %s -t random --char-write --handle=0x0011 --value=%08x" %  (self.mac, Mask)
        p = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
        (out, error) = p.communicate()

    def read(self):
        if not self.mac:
            raise Exception("MAC is not matched or wrong maybe.. bluetooth is not connected !!!")
   
        cmd = "gatttool -b %s -t random --char-read --handle=0x000e" % (self.mac)
        p = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
        (out, error) = p.communicate()
        out = out.replace(" ", "").strip().split(":")[1]
        return out.decode("hex")

   
