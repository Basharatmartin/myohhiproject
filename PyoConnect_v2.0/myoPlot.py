#!/usr/bin/python
# created by Basharat


import matplotlib.pyplot as plt
import matplotlib.animation as ani


Figure = plt.figure()
axis = Figure.add_subplot (1,1,1)


def ploemg (string):
    
    #file_read = open('myo_newRAW.txt', 'r').read()    #print file_read
    #data_array = get_data.split('\n')
    

    file_read = str(string)
    
    print file_read

    '''    
    get_data = file_read.replace('(','').replace(')','')
    data_array = get_data.split('\n')
    
    #data_array = str(obj)
    a_array = []
    b_array = []
    
    #print data_array

    for line in data_array:
        #if len(line) > 1:
            a,b = line.split(',')
            print a,b            
            #x,y = line.split(', ')

            a_array.append(a)
            b_array.append(b)            
            
    axis.clear()
    axis.plot(a_array)
    axis.plot(b_array)
    '''
    
#ani.FuncAnimation(Figure, plotEMG, interval=1000)
#plt.show()