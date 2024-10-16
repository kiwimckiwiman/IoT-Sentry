#imports
import cv2
import serial
import time
import mysql.connector

#setting up serial conenction to arduino
SerialObj = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
SerialObj.reset_input_buffer()
SerialObj.bytesize = 8   # Number of data bits = 8
SerialObj.parity  ='N'   # No parity
SerialObj.stopbits = 1   # Number of Stop bits = 1

#set up video capture
vid = cv2.VideoCapture(0)
vid.set(cv2.CAP_PROP_FPS, 30)
vid.set(cv2.CAP_PROP_FOURCC,cv2.VideoWriter_fourcc(*'MJPG'))
faceCascade = cv2.CascadeClassifier('/home/kiwimckiwiman/opencv-4.x/data/haarcascades/haarcascade_frontalface_alt.xml')
width = 320
height = 200

#variables
terminate = False;
timeLimit = 10;
#database credentials
mydb =  mysql.connector.connect(host="localhost", user="pi", password="password", database="sensor_db")

#maiun working loop
while (terminate == False):
    if SerialObj.in_waiting > 0: #if input from arduino
        detect = SerialObj.readline().decode('ascii').rstrip()
        print("received " + detect)
        i = 0
        
        #get active time limit
        mycursor = mydb.cursor()
        mycursor.execute("SELECT active_time FROM settings")
        rows = mycursor.fetchall()
        timeLimit = rows[0][0]
        print(timeLimit)
        mycursor.close()
        
        #start clock for cooldown period
        timeUp = True;
        start = time.time()
        if(detect == "1"): #if motion detected
            #update range and sentry mode from database
            mycursor = mydb.cursor()
            mycursor.execute("SELECT * FROM settings")
            rows = mycursor.fetchall()
            shoot = rows[0][1]
            sRange = rows[0][2]
            mycursor.close()
            
            print(shoot)
            print(sRange)
            
            #video camera loop
            while True:
               end = time.time()
               if(end - start > timeLimit):
                   timeUp == True
                   print("py times up");
                   SerialObj.write(str(6).encode())
                   break;
               ret, frame = vid.read()
               frame = cv2.resize(frame, (320, 200))
               # Convert to greyscale for easier faster accurate face detection
               gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
               gray = cv2.equalizeHist( gray )
               inst = 10
                # Do face detection to search for faces from these captures frames
               faces = faceCascade.detectMultiScale(frame, 1.1, 3, 0, (10, 10))
               
               
               
               for (x, y, w, h) in faces:
                    # Draw a green rectangle around the face (There is a lot of control to be had here, for example If you want a bigger border change 4 to 8)
                    cv2.rectangle(frame, (x, y), (x + w,y +  h), (0, 255, 0), 4)
                    x = x + (w/2)
                    y = y + (h/2)
                    if(x < width/2 - 10):
                        lr = 1
                    elif (width/2 -10 < x < width/2 +10):
                        lr = 2
                    else:
                        lr = 0
                        
                    if (y < height/2 - 10):
                        ud = 0
                    elif (height/2 -10 < y < height/2 +10):
                        ud = 2
                    else:
                        ud = 1
                    
                    #encode action for arduino
                    if (lr == 0):
                        inst = lr
                    elif (lr == 1):
                        inst = lr
                    elif (lr == 2):
                        if (ud == 0):
                            inst = ud + 2
                        elif (ud == 1):
                            inst = ud + 2
                        elif (ud == 2):
                            if(shoot == 1.0):
                                inst = 4
                                start = time.time()
                            else:
                                inst = 5
                                    
                    break

               i = i + 1
               #buffer for serial communication
               if(i%30 == 0):
                   if(inst != 10):
                       #write actions to database
                           mycursor = mydb.cursor()
                           if (inst == 0):
                                sql = "UPDATE actions SET L = L + 1"
                           elif (inst == 1):
                                sql = "UPDATE actions SET R = R + 1"
                           elif (inst == 2):
                                sql = "UPDATE actions SET U = U + 1"
                           elif (inst == 3):
                                sql = "UPDATE actions SET D = D + 1"
                           elif (inst == 4):
                                sql = "UPDATE actions SET S = S + 1"
                           mycursor.execute(sql)
                           mycursor.close()
                           mydb.commit()
                           #send actions to arduino
                           SerialObj.write(str(inst).encode())
                           if(inst == 4):
                                SerialObj.write(str(sRange).encode())
                                time.sleep(0.1)
                                print("send " + str(i) + "| data " + str(inst) + " | range set: " + str(sRange))
                           else:
                                print("send " + str(i) + "| data " + str(inst))
                           
                   i = 0
               cv2.imshow('frame', frame)
               if cv2.waitKey(1) & 0xFF == ord('q'):
                   terminate = True
                   break
              
            cv2.destroyAllWindows()
SerialObj.close()