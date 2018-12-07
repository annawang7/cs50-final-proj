#include <Adafruit_NeoPixel.h>
#define PIN            6
#define NUMPIXELS      50
#define TIMEINT        20
#define NUMCHANGES     25

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 50; // Delay for half a second
int input; 

// Stores pixel color values
int r[NUMPIXELS];
int g[NUMPIXELS];
int b[NUMPIXELS];

void setup() 
{
  pixels.begin();

  // Opens serial port
  Serial.begin(9600);

  // Sets all pixels to dark
  changeAllPixels(0, 0, 0);
  for (int i = 0; i < NUMPIXELS; i++) 
  {
    r[i] = 0;
    g[i] = 0;
    b[i] = 0;
  }
  delay(500);
}

void loop() 
{
  if (Serial.available() > 0) 
  {
    // Reads serial input until \n
    String colors = Serial.readStringUntil('\n');

    // Serial contains ',' for new pixel
    if (colors.indexOf(",") != -1) 
    {
      int inputPixel = colors.substring(0, colors.indexOf('^')).toInt();
      r[inputPixel] = colors.substring(colors.indexOf('^') + 1, colors.indexOf(',')).toInt();
      g[inputPixel] = colors.substring(colors.indexOf(',') + 1, colors.indexOf('#')).toInt();
      b[inputPixel] = colors.substring(colors.indexOf('#') + 1).toInt();
      wash(inputPixel);
    } 

    // Serial contains 'r' for rainbow
    else if (colors == "r") 
    {
      rainbow();
    }

    // Serial contains 'q' for debugging
    else if (colors == "q")
    {
      for (int i = 0; i < NUMPIXELS; i++)
      {
        Serial.println(r[i]);
        Serial.println(g[i]);
        Serial.println(b[i]);
      }
    }

    // Serial contains 'c' to clear
    else if (colors == "c")
    {
      changeAllPixels(0, 0, 0);
      for (int i = 0; i < NUMPIXELS; i++)
      {
        setPixelArr(i, 0, 0, 0);
      }
    }
  }
}

// Changes all pixels at once
void changeAllPixels(int red, int green, int blue)
{
  for (int i = 0; i < NUMPIXELS; i++)
  {
    pixels.setPixelColor(i, pixels.Color(red, green, blue));
    pixels.show();
    delay(10);
  }
}

// Washes all pixels to a specific pixel's color and fades 
void wash(int pixel)
{
  changeAllPixels(r[pixel], g[pixel], b[pixel]);
  for (int t = 0; t <= NUMCHANGES; t++)
  {
    for (int i = 0; i < NUMPIXELS; i++)
    {
      changePixel(i, r[pixel] + ((r[i]-r[pixel])*t / NUMCHANGES), g[pixel] + ((g[i]-g[pixel])* t / NUMCHANGES), b[pixel] + ((b[i]-b[pixel])* t / NUMCHANGES));
    }
    delay(TIMEINT - 10);
  }
}

// Changes an individual pixel
void changePixel(int pixel, int red, int green, int blue)
{
  pixels.setPixelColor(pixel, pixels.Color(red, green, blue));
  pixels.show();
}

// Changes colors randomly in a rainbow pattern
void rainbow() {
  while (!Serial.available())
  {
    int r_i = rand() % 255;
    int g_i = rand() % 255;
    int b_i = rand() % 255;
    slowTransition(r_i, g_i, b_i);
    for (int i = 0; i < NUMPIXELS; i++)
    {
      setPixelArr(i, r_i, g_i, b_i);
    }
    delay(600);
  }
}

// Changes all pixels via fade
void slowTransition(int final_r, int final_g, int final_b)
{
  for (int t = 0; t <= NUMCHANGES; t++)
  {
    for (int i = 0; i < NUMPIXELS; i++)
    {
      changePixel(i, r[i] + ((final_r-r[i])*t / NUMCHANGES), g[i] + ((final_g-g[i])* t / NUMCHANGES), b[i] + ((final_b-b[i])* t / NUMCHANGES));
    }
    delay(TIMEINT - 10);
  }
}

// Sets a pixel to an RGB value
void setPixelArr(int pixel, int red, int green, int blue)
{
  r[pixel] = red;
  g[pixel] = green;
  b[pixel] = blue;
}
