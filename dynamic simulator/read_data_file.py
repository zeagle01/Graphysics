


import sys




def read_data_from_file(file):
    ret=[]
    frame=[]
    type_string_2_type_converter={'int':int,'float':float}
    with open(file,'r') as fin:
        lines=fin.readlines()
        for i,line in enumerate(lines):
            line=line.split()
            if i==0:
                data_type=line[1]
                col=int(line[2])
                row=int(line[3])
                #frame=[[] for i in range(row)]*col
            elif i%(col+1)!=0:
                line_data=[]
                for word in line:
                   line_data .append(type_string_2_type_converter[data_type](word))
                frame.append(line_data)
            else:
                ret.append(frame)
                frame=[]
    return ret


def convert_2_wire_frame(data):
    ret=[]
    x=[]
    y=[]
    z=[]
    for i1,d1 in enumerate(data):
        fx=[]
        fy=[]
        fz=[]
        for i2,d2 in enumerate(d1):
            for i3,d3 in enumerate(d2):
                fx.append(i1)
                n1=len(d1)
                n2=len(d2)
                fy.append(i2*n2+i3)
                fz.append(d3)
        x.append(fx)
        y.append(fy)
        z.append(fz)
    ret.append(x)
    ret.append(y)
    ret.append(z)
    return ret


file =sys.argv[1]
data=read_data_from_file(file)
data=convert_2_wire_frame(data)



from mpl_toolkits.mplot3d import axes3d
import matplotlib.pyplot as plt


fig, ax1 = plt.subplots(1, 1, figsize=(8, 12), subplot_kw={'projection': '3d'})

# Get the test data
X, Y, Z = data

ax1.plot_wireframe(X, Y, Z,cstride=0)
ax1.set_title("Column (x) stride set to 0")


plt.tight_layout()
plt.show()