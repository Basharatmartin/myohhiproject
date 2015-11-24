# -*- coding: utf-8 -*-
"""
Created on Wed Nov 18 17:33:26 2015

@author: manisha
"""
#!/usr/bin/python

#==============================================================================
##    
import Adafruit_BBIO.GPIO as GPIO
import time
   
GPIO.setup("P9_11",GPIO.OUT)
GPIO.setup("P9_12",GPIO.OUT)
GPIO.setup("P9_13",GPIO.OUT)
GPIO.setup("P9_14",GPIO.OUT)
GPIO.setup("P9_15",GPIO.OUT)
GPIO.setup("P9_16",GPIO.OUT)
GPIO.setup("P9_17",GPIO.OUT)
GPIO.setup("P9_18",GPIO.OUT)

#==============================================================================

import re

file_read= "myo_file.txt" #raw_input("enter the file name = ");  # as scan f for input

#def readfile(str):
fh = open (file_read,'r') 

    #data=f.readlines()
line_number = 0
for line in fh:
    
   line = line.rstrip('\n')
   data= line.strip( '(' )
   data = data.replace(',',' ').replace(')','')
   
#   data = data.strip("\w")
#
#   if re.search("[a-z]",data):
#       print "data found"
#       continue

   line_number = line_number+1

   data_array = data.split(' ')
   
   #print data_array[1] 
       
   #print line_number #data_array#

   #split the line to array  
#   data_array = data.split('  ')
#   print int(data_array[1])/2 
#   data_array = data.split(' ')
#   print int(data_array[6])/2 
#   data_array = data.split(' ')

   data_array = data.split(' ')
   sensor_1 = data_array[0]
   sensor_1 =int(sensor_1)
   sensor_1= sensor_1/2
   if sensor_1 > 55:
       print "sensor1 = ",sensor_1 
      GPIO.output("P9_11", GPIO.HIGH) 
  else:
       GPIO.output("P9_11", GPIO.LOW)
      
   
   data_array = data.split('  ')
   sensor_2 = data_array[1]
   sensor_2 =int(sensor_2)
   sensor_2= sensor_2/2
   if sensor_2 > 55:
       print "sensor2 = ",sensor_2
       GPIO.output("P9_12", GPIO.HIGH) 
  else:
       GPIO.output("P9_12", GPIO.LOW)
   
   data_array = data.split(' ')
   sensor_3 = data_array[2]
   sensor_3 =int(sensor_3)
   sensor_3= sensor_3/2
   if sensor_3 > 55:
       print "sensor3 = ",sensor_3
       GPIO.output("P9_13", GPIO.HIGH) 
  else:
       GPIO.output("P9_13", GPIO.LOW)
  
   data_array = data.split('  ')
   sensor_4 = data_array[3]
   sensor_4 =int(sensor_4)
   sensor_4= sensor_4/2
   if sensor_4 > 55:
       print "sensor4 = ",sensor_4
       GPIO.output("P9_14", GPIO.HIGH) 
  else:
       GPIO.output("P9_14", GPIO.LOW)
   
   
   data_array = data.split(' ')
   sensor_5 = data_array[4]
   sensor_5 =int(sensor_5)
   sensor_5= sensor_5/2
   if sensor_5 > 55:
       print "sensor5 = ",sensor_5
       GPIO.output("P9_15", GPIO.HIGH) 
  else:
       GPIO.output("P9_15", GPIO.LOW)
  
   data_array = data.split('  ')
   sensor_6 = data_array[5]
   sensor_6 =int(sensor_6)
   sensor_6= sensor_6/2
   if sensor_6 > 55:
       print "sensor6 = ",sensor_6
       GPIO.output("P9_16", GPIO.HIGH) 
  else:
       GPIO.output("P9_16", GPIO.LOW)
   
   data_array = data.split(' ')
   sensor_7 = data_array[6]
   sensor_7 =int(sensor_7)
   sensor_7= sensor_7/2
   if sensor_7 > 55:
       print "sensor7 = ",sensor_7
       GPIO.output("P9_17", GPIO.HIGH) 
  else:
       GPIO.output("P9_17", GPIO.LOW)
  
   data_array = data.split('  ')
   sensor_8 = data_array[7]
   sensor_8 =int(sensor_8)
   sensor_8= sensor_8/2
   if sensor_8 > 55:
       print "sensor8 = ",sensor_8
       GPIO.output("P9_18", GPIO.HIGH) 
  else:
       GPIO.output("P9_18", GPIO.LOW)
   
   
  
   