#!/usr/bin/python
# RFduino.py by Basharat

import subprocess
import re
#import ctypes


global data

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

        '''
        if (len(msg) == 3):
            gyro1 = 0x01 & 0xFF
            gyro2 = 0x01 & 0xFF
            gyro3 = abs(msg[1]) / 20  
            gyro4 = 0x01 & 0xFF
            gyro5 = 0x01 & 0xFF
            gyro6 = 0x01 & 0xFF
            gyro7 = 0x01 & 0xFF
            gyro8 = 0x01 & 0xFF
            msg1 = msg2 = msg3 = msg4 = msg5 = msg6 = msg7 = msg8 = 1         
            
 #           if (gyro1 > 255):
 #               gyro1 = 255
 #           if (gyro2 > 255):
 #               gyro2 = 255
            if (gyro3 > 255):
                gyro3 = 255             
              
#            Mask = (gyro2 << 8)
#            print gyro1, gyro2, gyro3, '0x%08x' % Mask , "This is Gyro"
            Mask = (gyro1 << 56) | (gyro2 << 48) | (gyro3 << 40) | (gyro4 << 32) | (gyro5 << 24) | (gyro6 << 16) | (gyro7 << 8) |  gyro8
            print gyro1, gyro2, gyro3, gyro4, gyro5, gyro6, gyro7, gyro8, '0x%08x' % Mask , "This is Gyro"
            
        else:
        '''
        
        
        print (msg)
        
        msg1 = abs(msg[0]) / 10
        msg2 = msg[1] / 4 
        msg3 = msg[2] / 4
        msg4 = msg[3] / 4
        msg5 = msg[4] / 4
        msg6 = msg[5] / 4
        #msg7 = msg[6] / 4
        #msg8 = 0x01 #msg[7] / 4
        
        if (msg1 > 255):
            msg1 = 255
        if (msg1 <= 16):
            msg1 = 16
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
        #if (msg7 > 255):
        #    msg7 = 255            
#            if (msg8 > 255):
#                msg8 = 255         
        
        #Mask = (msg1 << 56) | (msg2 << 48) | (msg3 << 40) | (msg4 << 32) | (msg5 << 24) | (msg6 << 16) | (msg7 << 8) |  msg8
            #print msg1, msg2, msg3, msg4, msg5, msg6, msg7, msg8, '0x%08x' % Mask , "This is EMG"
            
        #print (msg1)

        #gyro2 = 255    
    
        #print  msg1, gyro2, "here Emg and gyro"    
    
        '''
        
        

        #Mask = (msg2 << 24) | (msg4 << 16) | (msg6 << 8) | msg7
        '''
        
        Mask = (msg1 << 40) | (msg2 << 32) | (msg3 << 24) | (msg4 << 16) | (msg5 << 8) | msg6
        print msg1, msg2, msg3, msg4, msg5, msg6, '0x%08x' % Mask
    
        #print '0x%08x' % Mask
        
        '''        
#        if ( (msg1 > 255) and (msg2 > 255) and (msg3 > 255) and (msg4 > 255)):
#            msg1 = 255
#            msg2 = 255
#            msg3 = 255
#            msg4 = 255
#            Mask = (msg1 << 24) | (msg2 << 16) | (msg3 << 8) | msg4              
#            #Mask = (Mask)        
#            print msg1, msg2, msg3, msg4, Mask
#        else: 
#        '''                 
           
            #Mask = (Mask)        
        #print msg1, msg2, msg3, Mask
        
  
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

   
