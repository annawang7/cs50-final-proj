#!/usr/bin/python

START_DELAY = 2 # seconds
REFRESH_FREQ = 0.5 # seconds
NUMPIXELS = 30 # number of pixels, must match with arduino

import urllib
import json
import serial
import time
import random

# Sets active pixel counter to 0
counter = 0;

# Opens serial port
ser = serial.Serial('/dev/ttyACM0', 9600)

# Delay to allow Arduino startup
time.sleep(START_DELAY)

# Generates randomly shuffled list of pixels
random_list = range(NUMPIXELS)
random.shuffle(random_list)

# Enters loop to continuously pull JSON from server
while(True):
    try:
        # Pulls JSON from URL by visiting webapp, URL parameters
        jraw=urllib.urlopen('https://docs.google.com/spreadsheets/d/1IE2KSebrycnvjFtUtkZdEslcSd63natw7JA25weiq64/gviz/tq?tq=select%20C%2C%20D%2C%20E%2C%20A')
        jt=jraw.read()
    except:
        print("error opening link")
    
    # Process raw JSON .txt file
    jstr=jt.split("setResponse",1)[1].split(";",1)[0]
    jstr=jstr[1:len(jstr)-1]
    loaded=json.loads(jstr)
    
    # Access data in JSON
    values=loaded['table']['rows']
    rows=len(values)
    if rows != counter:
        for i in range(rows - counter):
            # Concatenates to "<pixel>^<r>,<g>#<b>"
            rgb_row=str(str(random_list[(counter+i) % NUMPIXELS]) + '^' + str(int(values[rows-1-i]['c'][0]['f'])) + ',' + str(int(values[rows-1-i]['c'][1]['f'])) + '#' + str(int(values[rows-1-i]['c'][2]['f'])))
            
            # Writes to serial
            ser.write(rgb_row)
            print(rgb_row)
            print("executed")
        
        # Updates counter 
        counter = rows
    else:
        print("skipped")

    # Sets delay
    time.sleep(REFRESH_FREQ)