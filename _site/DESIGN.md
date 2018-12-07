# That's A Mood: DESIGN.md

**[That's A Mood](https://annawang7.github.io/cs50-final-proj)** is a project to encourage an open expression of mental health on the Harvard campus. 

## Overall Design
  That's A Mood is split into four main components: the web component, the Google Script, the Raspberry Pi, and the Arduino components, each with their separate code. The user-facing components are the web and the Arduino components. 

## The Web Component
  ### Usage
    The web component is currently a website hosted on Github: **[That's A Mood](https://annawang7.github.io/cs50-final-proj)**. This website holds information about the project as well as the main input method: a color wheel, where users can input how they are feeling in the form of color at the current moment.

  ### Details
    We chose to create a Jekyll website as it provides a clean platform to host unique templates as well as a streamlined process for posting. In the future, we may use the website as a platform to tell stories involving mental health and moods on Harvard, and this can easily be accomplished through Jekyll's efficient blogging system. 

## Google Apps Script
  ### Usage
    Once the user submits a color, their selection is sent via a GET request to the Google Apps Script, which puts the data into a spreadsheet and acts as a database for our system. 
  
  ### Details
    We chose to host our database as a Google Spreadsheet because of it can be easily processed into tables and graphs to analyze the data that we receive throughout this entire project. As Jekyll only supports a static website, this was the easiest way to obtain the best of both worlds with this framework.

## Raspberry Pi
  ### Usage
    The Raspberry Pi constantly queries the Google Spreadsheet to check if there is any new information inputt

  ### Details
  Once the user submits a color, this is sent via a GET request to the Goog`

## Developer Details
  To access this project's web codebase, visit its **[Github Repository](https://github.com/annawang7/cs50-final-proj)**.

## Study Citations
  * **[Mental Health America](https://www.mha-em.org/advocacy/12-media/132-mental-health-treatment-and-stigma-statistics.html)** 
  * **[MentalHealth.gov](https://www.mentalhealth.gov/basics/what-is-mental-health)**

## Theme Credits
This theme was created as an open-source project [Moon](https://taylantatli.github.io/Moon) by Taylan Tatli. 