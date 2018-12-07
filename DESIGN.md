# That's A Mood: DESIGN.md

**[That's A Mood](https://annawang7.github.io/cs50-final-proj)** is a project to encourage an open expression of mental health on the Harvard campus. 

## Overall Design
That's A Mood is split into four main components: the web component, the Google Apps Script, the Raspberry Pi, and the Arduino components, each with their separate code in HTML/CSS/JavaScript/jQuery, Google Apps Script (JavaScript-based), Python and shell script, and Arduino C, respectively. The user-facing components are the web and the Arduino components, while the Google Apps Script and the Raspberry Pi serve to communicate between the web and hardware components.

## The Web Component
  ### Usage
The web component is currently a website hosted on Github: **[That's A Mood](https://annawang7.github.io/cs50-final-proj)**. This website holds information about the project as well as the main input method: a color wheel, where users can input how they are feeling in the form of color at the current moment.

  ### Details
We chose to create a Jekyll website as it provides a clean platform to host unique templates as well as a streamlined process for posting. In the future, we may use the website as a platform to tell stories involving mental health and moods on Harvard, and this can easily be accomplished through Jekyll's efficient blogging system.

## Google Apps Script
  ### Usage
The Google Apps Script is not meant to be interfaced by end users, but serves as a repository for our data that's persistent. We chose to use Google Sheets to host our data for several reasons: 1) it does not require us to run our own web server to host the data, 2) Google Sheets features a familiar GUI that boosts readability and ease of use, 3) aggregated mood data can later be analyzed for trends and embedded in the Jekyll site without much extra effort, and 4) Google Sheets can be queried through the URL, returning a JSON file that can be deserialized to access table data.
  
  ### Details
As Jekyll only supports a static website, using a web app containing JavaScript was the easiest way to obtain the best of both worlds with this framework. Once the user submits a color, their selection is sent via a GET request to the Google Apps Script, which was published as a Google Web App. The web app is constantly listening for GET requests and runs the web app upon a GET request. The Google Apps Script, which is running a variant of JavaScript, puts the data into a spreadsheet with a timestamp, red, green, and blue value column in the form of a datetime object and 3 integer values, respectively. This Google Sheet in effect acts as a database for our system and allows us to access data persistently and run analytics on the incoming mood data (an upcoming feature).

The Google Sheet can be accessed through its URL and query parameters can be encoded and appended to the end of the URL such that the query URL is a download link to a JSON file containing the queried information. We appended a query that selects all values from rows A, C, D, and E and had the Python script on the Raspberry Pi run on this queried JSON.

## Raspberry Pi
  ### Usage
The Raspberry Pi constantly queries the Google Spreadsheet to check if there is any new information input. The user only interfaces with the Raspberry Pi by plugging it in. The Raspberry Pi's role is to serve as the processing, power, and Internet element for the hardware setup. Upon boot, the Raspberry Pi begins running the Python script, so the user is not required to have to access the Raspberri Pi through its GUI (the Raspberry Pi runs headless).

  ### Details
Upon boot, the Raspberry Pi begins running a Python script that continually accesses the URL of the Google Sheet with query parameters. The Python script stores the number of rows locally; when there is a change in the number of rows, the Python script writes to the serial port, which is connected to the Arduino. The Python script first deserializes the JSON file and using the json library, stores the red, blue, and green values in a list. The script then stringifies the three values along with a randomly generated pixel number ranging from 0 to 49; this information is fed byte by byte into the serial port. This process is then repeated, as the majority of the script is wrapped in a never-ending while loop.

## Arduino
  ### Usage
The Arduino physically controls the LED output. The user does not have to work with the Arduino, since the Arduino is managed through the Raspberry Pi including its power supply and data processing. The Arduino really just displays the lights given one of several commands that the Raspberry Pi writes through the serial port.

  ### Details
The Arduino is running Arduino C, a variant of C adapted for Arduino usage. We are using the Neopixel library by Adafruit to control the lights. Two methods are necessary to run the Arduino: the setup() method and the loop() method. setup() runs upon power on, and loop() runs continuously by default. The Arduino is listening for a serial input that the Raspberry Pi writes. The serial input is of the form "<pixel_number>^<red_value>,<green_value>#<blue_value>" for inputs that run upon a user submit to the form. However, if "r" is the serial input, then the LEDs display a shifting rainbow pattern. If "c" is passed in, all lights are cleared.

We store the color value of each pixel in three arrays corresponding to R, G, and  B, each with length equal to the number of pixels. This allows us to display cool light features like changing the color in a wave or slow transitions between lights.

## Developer Details
To access this project's web codebase, visit its **[GitHub repository](https://github.com/annawang7/cs50-final-proj)**.

## Study Citations
* **[Mental Health America](https://www.mha-em.org/advocacy/12-media/132-mental-health-treatment-and-stigma-statistics.html)** 
* **[MentalHealth.gov](https://www.mentalhealth.gov/basics/what-is-mental-health)**

## Theme Credits
This theme was created as an open-source project [Moon](https://taylantatli.github.io/Moon) by Taylan Tatli. 