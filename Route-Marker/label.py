import cv2
import numpy as np
import pandas as pd

mode = 0
MULTIPLE = 8
COLOR_POINT = [0, 255, 255]
COLOR_AVAI = [30, 130, 0]
COLOR_UNAVAI = [0, 30, 130]
MAX_POINTS_NUM = 1000
Graph = [[0] * MAX_POINTS_NUM for i in range(MAX_POINTS_NUM)]
HAVE_START = False
pnts = []


#创建回调函数
def OnMouseAction(event,x,y,flags,param):
    global x1, y1, img2, img, img3, pnts, HAVE_START

    #Basic Info Display
    img2 = np.zeros((70, 300, 3), np.uint8)
    cv2.putText(img2, "X=" + str(x//MULTIPLE) + ", Y=" + str(y//MULTIPLE), (30, 30), font, 0.8, (255, 255, 255))
    cv2.rectangle(img2, (240,15), (250, 25), img[y][x].tolist(), -1)

    #Line Info Display
    if mode == 1 and HAVE_START:
        img3 = np.zeros((70, 500, 3), np.uint8)
        cv2.putText(img3, "From X=" + str(x1 // MULTIPLE) + ", Y=" + str(y1 // MULTIPLE) + " No." + str(pnts.index([x1 // MULTIPLE,y1 // MULTIPLE])), (30, 30), font, 0.8, (255, 255, 255))
        if (pnts.count([x // MULTIPLE,y // MULTIPLE])>0):
            cv2.putText(img3, "To    X=" + str(x // MULTIPLE) + ", Y=" + str(y // MULTIPLE) + " No." + str(pnts.index([x // MULTIPLE,y // MULTIPLE])), (30, 60), font, 0.8, (255, 255, 255))
        else:
            cv2.putText(img3, "To", (30, 60), font, 0.8, (255, 255, 255))
    elif mode == 0:
        img3 = np.zeros((70, 500, 3), np.uint8)
        cv2.putText(img3, "Not in Line Mode", (30, 30), font, 0.8, (255, 255, 255))
    else:
        img3 = np.zeros((70, 500, 3), np.uint8)
        cv2.putText(img3, "No Start Point", (30, 30), font, 0.8, (255, 255, 255))

    if mode == 1 and event == cv2.EVENT_RBUTTONDOWN:
        if pnts.count([x // MULTIPLE,y // MULTIPLE])>0:
            print("Line右键点击",img[y][x].tolist())
            x1, y1 = x//MULTIPLE*MULTIPLE, y//MULTIPLE*MULTIPLE
            HAVE_START = True

    if mode == 1 and event == cv2.EVENT_LBUTTONDOWN and HAVE_START:
        if (pnts.count([x // MULTIPLE,y // MULTIPLE])>0):
            print("Line左键点击",img[y][x].tolist())
            pts = np.array([[x1,y1],[x1+MULTIPLE,y1+MULTIPLE],[x//MULTIPLE*MULTIPLE+MULTIPLE//2,y//MULTIPLE*MULTIPLE+MULTIPLE//2]], np.int32)
            cv2.fillPoly(img, [pts], (255, 255, 0), 0, 0)
            Graph[pnts.index([x1 // MULTIPLE,y1 // MULTIPLE])][pnts.index([x // MULTIPLE,y // MULTIPLE])]=1
            for i in range(len(pnts)):
                for j in range(len(pnts)):
                    print(Graph[i][j]," ",end='')
                print()

    if mode == 0 and event == cv2.EVENT_LBUTTONDOWN:
        if (img[y][x].tolist()== COLOR_AVAI):
            print("Point左键点击", img[y][x].tolist())
            if pnts.count([x//MULTIPLE,y//MULTIPLE]) == 0:
                pnts.append([x//MULTIPLE,y//MULTIPLE])
            print(pnts)
            #print(Graph[:len(pnts)][:len(pnts)])
            cv2.rectangle(img, (x//MULTIPLE*MULTIPLE, y//MULTIPLE*MULTIPLE), (x//MULTIPLE*MULTIPLE+MULTIPLE, y//MULTIPLE*MULTIPLE+MULTIPLE), COLOR_POINT, -1)

    elif mode == 1 and event==cv2.EVENT_MOUSEMOVE and flags ==cv2.EVENT_FLAG_LBUTTON:
        print("左鍵拖曳1")


data = pd.read_csv('map2.csv',header=None).iloc[:,:200]
print(data.shape)
img = np.zeros((MULTIPLE*data.shape[0],MULTIPLE*data.shape[1],3),np.uint8)
img2 = np.zeros((70,300,3),np.uint8)
img3 = np.zeros((70,500,3),np.uint8)

for i in range(data.shape[0]):
    for j in range(data.shape[1]):
        if (data.iloc[i][j]!=0):
            for x in range(MULTIPLE):
                for y in range(MULTIPLE):
                    img[MULTIPLE*i+x][MULTIPLE*j+y]= COLOR_UNAVAI
        else:
            for x in range(MULTIPLE):
                for y in range(MULTIPLE):
                    img[MULTIPLE*i+x][MULTIPLE*j+y]= COLOR_AVAI


font = cv2.FONT_HERSHEY_SIMPLEX
cv2.namedWindow('Label')
cv2.setMouseCallback('Label',OnMouseAction)
cv2.namedWindow('Basic info')
cv2.namedWindow('Line info')

while(1):
    cv2.imshow('Label',img)
    cv2.imshow('Basic info',img2)
    cv2.imshow('Line info', img3)
    k=cv2.waitKey(1)
    if k==ord('p'):
        mode = 0
    elif k==ord('l'):
        mode = 1
    elif k==ord('q'):
        break
    elif k==ord('s'):
        with open("graph.dat", "w") as f:
            f.write(str(len(pnts))+"\n")
            for i in range(len(pnts)):
                f.write(str(pnts[i][0])+" "+str(pnts[i][1])+"\n")
            for i in range(len(pnts)):
                for j in range(len(pnts)):
                    f.write(str(Graph[i][j])+" ")
                f.write("\n")
        print('Graph Saved')
cv2.destroyAllWindows()
