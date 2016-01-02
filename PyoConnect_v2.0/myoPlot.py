#!/usr/bin/python
# created by Basharat


import matplotlib.pyplot as plt
import matplotlib.animation as ani


Figure = plt.figure()
axis = Figure.add_subplot (1,1,1)


class Plot:
    def __init__ (self, hello):
        self.hello = hello
    
    def plotemg (self, emg):
        #file_open = open('myo_newfile.txt', 'r').read()
        
        #get_data = file_open.replace('(','').replace(')','')
        data_array = get_data.split('\n')
        a_array = []
        b_array = []
        c_array = []
        d_array = []
        e_array = []
        f_array = []
        g_array = []
        h_array = []
        for line in data_array:
            if len(line) > 1:
                a,b,c,d,e,f,g,h = line.split(',')
                #print a,b,c,d,e,f,g,h            
                a_array.append(int(a))
                b_array.append(int(b))            
                c_array.append(int(c))  
                d_array.append(int(d))  
                e_array.append(int(e))  
                f_array.append(int(f))  
                g_array.append(int(g))  
                h_array.append(int(h))  
             
             
        axis.clear()
        axis.plot(a_array)
        axis.plot(b_array)
        axis.plot(c_array)
        axis.plot(d_array)
        axis.plot(e_array)
        axis.plot(f_array)
        axis.plot(g_array)
        axis.plot(h_array)
        
        return "successful"
        
    Ani = ani.FuncAnimation(Figure, plotemg, interval=1000)
    plt.show()


def main():
    graph = Plot()
    graph.plotemg()

if __name__ == '__main__':
    main()
    
    