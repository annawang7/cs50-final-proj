#include <Adafruit_NeoPixel.h>
#define PIN            6
#define NUMPIXELS      50
#define TIMEINT        20
#define NUMCHANGES     25

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 50; // delay for half a second
int input;
int r[NUMPIXELS];
int g[NUMPIXELS];
int b[NUMPIXELS];

void setup() {
  pixels.begin();
  Serial.begin(9600);
  changeAllPixels(0, 0, 0);
  for (int i = 0; i < NUMPIXELS; i++) {
    r[i] = 0;
    g[i] = 0;
    b[i] = 0;
  }
  delay(500);
}

void loop() {
  if (Serial.available() > 0) {
    String colors = Serial.readStringUntil('\n');
    if (colors.indexOf(",") != -1) {
      int inputPixel = colors.substring(0, colors.indexOf('^')).toInt();
      r[inputPixel] = colors.substring(colors.indexOf('^') + 1, colors.indexOf(',')).toInt();
      g[inputPixel] = colors.substring(colors.indexOf(',') + 1, colors.indexOf('#')).toInt();
      b[inputPixel] = colors.substring(colors.indexOf('#') + 1).toInt();
      wash(inputPixel);
    } else if (colors == "r") {
      rainbow();
    } else if (colors == "q") {
      for (int i = 0; i < NUMPIXELS; i++) {
        Serial.println(r[i]);
        Serial.println(g[i]);
        Serial.println(b[i]);
      }
    } else if (colors == "c") {
      changeAllPixels(0, 0, 0);
      for (int i = 0; i < NUMPIXELS; i++) {
        setPixelArr(i, 0, 0, 0);
      }
    }
  }
}

void changeAllPixels(int red, int green, int blue) {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(red, green, blue));
    pixels.show();
    delay(10);
  }
}

void wash(int pixel) {
  // r[pixel], g[pixel], b[pixel] are the wash color.
  changeAllPixels(r[pixel], g[pixel], b[pixel]);
  for (int t = 0; t <= NUMCHANGES; t++) {
    for (int i = 0; i < NUMPIXELS; i++) {
      changePixel(i, r[pixel] + ((r[i]-r[pixel])*t / NUMCHANGES), g[pixel] + ((g[i]-g[pixel])* t / NUMCHANGES), b[pixel] + ((b[i]-b[pixel])* t / NUMCHANGES));
    }
    delay(TIMEINT - 10);
  }
}

void changePixel(int pixel, int red, int green, int blue) {
  pixels.setPixelColor(pixel, pixels.Color(red, green, blue));
  pixels.show();
}

void rainbow() {
  while (!Serial.available()) {
    int r_i = rand() % 255;
    int g_i = rand() % 255;
    int b_i = rand() % 255;
    slowTransition(r_i, g_i, b_i);
    for (int i = 0; i < NUMPIXELS; i++) {
      setPixelArr(i, r_i, g_i, b_i);
    }
    delay(600);
  }
}
//
//void travel() {
//  pixels.setPixelColor(0, pixels.Color(r[NUMPIXELS - 1], g[NUMPIXELS - 1], b[NUMPIXELS - 1]));
//  setPixelArr(0, r[NUMPIXELS - 1], g[NUMPIXELS - 1], b[NUMPIXELS - 1]);
//  for (int i = 1; i < NUMPIXELS; i++) {
//    // sets each pixel to value of previous
//    pixels.setPixelColor(i, pixels.Color(r[i-1], g[i-1], b[i-1]));
//    pixels.show();
//  }
//  for (int i = 0; i < NUMPIXELS, i++) {
//  }
//}

// changes all pixels to one color via slow transition
void slowTransition(int final_r, int final_g, int final_b) {
  for (int t = 0; t <= NUMCHANGES; t++) {
    for (int i = 0; i < NUMPIXELS; i++) {
      changePixel(i, r[i] + ((final_r-r[i])*t / NUMCHANGES), g[i] + ((final_g-g[i])* t / NUMCHANGES), b[i] + ((final_b-b[i])* t / NUMCHANGES));
    }
    delay(TIMEINT - 10);
  }
}

void setPixelArr(int pixel, int red, int green, int blue) {
  r[pixel] = red;
  g[pixel] = green;
  b[pixel] = blue;
}
