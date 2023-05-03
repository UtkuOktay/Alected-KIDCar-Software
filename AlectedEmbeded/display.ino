
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Declare LCD object for software SPI
#define CLK_1 45
#define DIN_1 47
#define DC_1 49
#define CE_1 51
#define RST_1 53

#define CLK_2 35
#define DIN_2 37
#define DC_2 39
#define CE_2 41
#define RST_2 43

// Adafruit_PCD8544(CLK,DIN,D/C,CE,RST);

Adafruit_PCD8544 display1 = Adafruit_PCD8544(CLK_1, DIN_1, DC_1, CE_1, RST_1);
Adafruit_PCD8544 display2 = Adafruit_PCD8544(CLK_2, DIN_2, DC_2, CE_2, RST_2);

float velocity = 0;
float chart_max_values[] = {100, 10, 100, 100, 100, 100};
float chart_values[] = {80, 5, 99, 50, 10, 20};
char chart_names[6][3] = {"mT", "dT", "I", "V", "%", ":)"};

void display_setup()   {
	display1.begin();
	display1.setContrast(60);
  display2.begin();
  display2.setContrast(60);
}

int compute_length(int number, int font_width) {
  int number_length = 1;
  while(number >= 10){
    number = number / 10;
    number_length++;
  }
  return font_width * number_length;
}

int compute_length(char string[], int font_width) {
  return strlen(string) * font_width;
}

void render_display_1(struct Adafruit_PCD8544 display, int velocity){
  display.clearDisplay();
	display.setTextColor(BLACK);
  display.setCursor(LCDWIDTH/2 - compute_length(velocity, 16)/2, 5);
  display.setTextSize(3);
  display.print(int(velocity));
  display.setTextSize(2);
  display.setCursor(LCDWIDTH/2 - compute_length("km/h", 10)/2, 30);
  display.print("km/h");
	display.display();
}

void render_display_2(struct Adafruit_PCD8544 display, char names[][3], float values[], float max_values[]){
  display.clearDisplay();
	display.setTextColor(BLACK);
  display.setTextSize(1);

  for(int i = 0; i < 6; i++){
    float percentage = values[i] / max_values[i];
    
    int bar_size = 14;
    int bar_width = 4;
    int bar_height = 28;
    int bars_start_level = 38;

    display.fillRect(i*bar_size + bar_size/2 - bar_width/2, bars_start_level, bar_width, -bar_height * percentage, 1);
    display.setCursor(i*bar_size + bar_size/2 - compute_length(values[i], 5)/2, 0);
    display.print(int(values[i]));

    display.setCursor(i*bar_size + bar_size/2 - compute_length(names[i], 5)/2, 40);
    display.print(names[i]);
  }
	display.display();
}

void display_loop() {
  render_display_1(display1, velocity);  
  render_display_2(display2, chart_names, chart_values, chart_max_values);
}