#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <MCUFRIEND_kbv.h>
#include "UserSettings.h"
#include <virtuabotixRTC.h>

#define TFT_CS   10
#define TFT_DC   9
#define TFT_RST  8

int LastMinute = -1; // Initialize to an invalid value

MCUFRIEND_kbv tft;

virtuabotixRTC myRTC(50, 48, 49);

void setup() {
  Serial.begin(9600);

  uint32_t When = millis();
  if (!Serial) delay(5000);
  Serial.println("Serial took " + String((millis() - When)) + "ms to start");

  if (SetTimeOnBoot) {
    myRTC.setDS1302Time(Seconds, Minutes, Hours, DayOfWeek, DayOfMonth, Month, Year);
  }

  tft.reset(); // Reset TFT display
  uint16_t ID = tft.readID(); // Read display ID
  Serial.print("ID = 0x");
  Serial.println(ID, HEX);
  if (ID == 0xD3D3) ID = 0x9481;
  tft.begin(ID); // Initialize TFT display

  tft.setRotation(0);
}

void loop() {
  myRTC.updateTime();

  // Check if the minute has changed
  if (myRTC.minutes != LastMinute) {
    DisplayTime();
    DrawProgressBars();
    LastMinute = myRTC.minutes;
  }

  delay(500); // Add a small delay to avoid rapid updates
}

void DisplayTime() {
  tft.fillScreen(BackColor);

  // Display day of the week
  tft.setTextSize(DayFontSize);
  int DayOfWeek = myRTC.dayofweek;
  String DayOfWeekStr = GetDayOfWeekString(DayOfWeek);
  int DayWidth = DayOfWeekStr.length() * (DayFontSize * 5); // Adjust this value based on the font size
  DayXPos = (tft.width() - DayWidth) / 2 - 20;

  // Set color for the day of the week
  uint16_t DayColor = GetDayColor(DayOfWeek);
  tft.setTextColor(DayColor);

  tft.setCursor(DayXPos, DayYPos);
  tft.print(DayOfWeekStr);

  // Display time
  tft.setTextSize(TimeFontSize);
  tft.setTextColor(TimeColor);
  tft.setCursor(TimeXPos, TimeYPos);

  String TimeStr = GetTimeString(myRTC.hours, myRTC.minutes);
  int TimeWidth = TimeStr.length() * (TimeFontSize * 5); // Adjust this value based on the font size

  tft.print(TimeStr);
}

String GetTimeString(int Hours, int Minutes) {
  String Period = (Hours >= 12) ? "PM" : "AM";
  Hours = (Hours % 12 == 0) ? 12 : Hours % 12;

  // Add AM or PM to the time
  if (Show12h) {
    String TimeStr = String(Hours) + ":" + (Minutes < 10 ? "0" : "") + String(Minutes) + " " + Period;
    return TimeStr;
  } else {
    String TimeStr = String(Hours < 10 ? " " : "") + String(Hours) + ":" + (Minutes < 10 ? "0" : "") + String(Minutes);
    return TimeStr;
  }
}

void DrawProgressBars() {
  // Draw progress bars
  DrawProgressBar(ProgressBarX, 10, ProgressBarWidth, ProgressBarHeight, StartTime1, EndTime1, ProgressBarColor1);
  DrawProgressBar(ProgressBarX, 30 + ProgressBarSpacing, ProgressBarWidth, ProgressBarHeight, StartTime2, EndTime2, ProgressBarColor2);
  DrawProgressBar(ProgressBarX, 50 + 2 * ProgressBarSpacing, ProgressBarWidth, ProgressBarHeight, StartTime3, EndTime3, ProgressBarColor3);
}

void DrawProgressBar(int X, int Y, int Width, int Height, int StartTime, int EndTime, uint16_t Color) {
  // Calculate progress bar length
  int CurrentTime = myRTC.hours * 60 + myRTC.minutes;
  int ProgressBarLength = map(CurrentTime, StartTime, EndTime, 0, Width);

  // Draw the outline of the progress bar
  tft.drawRect(X, Y, Width, Height, ILI9341_WHITE);

  // Draw the filled part of the progress bar
  tft.fillRect(X, Y, min(ProgressBarLength, Width), Height, Color);
}