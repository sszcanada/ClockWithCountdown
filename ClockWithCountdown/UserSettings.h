// Real-time clock wiring 
// CLK -> 50   DAT -> 48   Reset -> 49   VCC -> 5v   GND -> GND

bool SetTimeOnBoot = false;
int Year = 2023;
int Month = 12;
int DayOfMonth = 30;
int DayOfWeek = 6; // Use A number between 1-7 with Monday as 1
int Hours = 23; // Use 24h time
int Minutes = 8;
int Seconds = 0;

// Variable for background color
uint16_t BackColor = ILI9341_BLACK; // Color for the background

// Variables for text positioning
int DayXPos = 150;
int DayYPos = 140;
int TimeXPos = 28;
int TimeYPos = 190;

// Variable for time color
uint16_t TimeColor = ILI9341_ORANGE; // Color for the time

// Font size variables
int DayFontSize = 4;
int TimeFontSize = 5;

// Add AM or PM to the time
bool Show12h = false;

// Progress bar settings
int ProgressBarX = 10; // X position of progress bars
int ProgressBarWidth = 220; // Width of progress bars
int ProgressBarHeight = 20; // Height of progress bars
int ProgressBarSpacing = 10; // Spacing between progress bars

uint16_t ProgressBarColor1 = ILI9341_YELLOW; // Define color for progress bar 1
int StartTime1 = 0; // Start time for progress bar 1 (12:00 AM)
int EndTime1 = 720; // End time for progress bar 1 (12:00 PM)

uint16_t ProgressBarColor2 = ILI9341_CYAN; // Define color for progress bar 2
int StartTime2 = 0; // Start time for progress bar 2 (12:00 AM)
int EndTime2 = 1020; // End time for progress bar 2 (5:00 PM)

uint16_t ProgressBarColor3 = ILI9341_MAGENTA; // Define color for progress bar 3
int StartTime3 = 0; // Start time for progress bar 3 (12:00 AM)
int EndTime3 = 1140; // End time for progress bar 3 (7:00 PM)

// Customize the color for each day of the week
uint16_t GetDayColor(int DayOfWeek) {
  switch (DayOfWeek) {
    case 1: // Monday
      return ILI9341_GREEN;
    case 2: // Tuesday
      return ILI9341_GREEN;
    case 3: // Wednesday
      return ILI9341_GREEN;
    case 4: // Thursday
      return ILI9341_GREEN;
    case 5: // Friday
      return ILI9341_RED;
    case 6: // Saturday
      return ILI9341_RED;
    case 7: // Sunday
      return ILI9341_GREEN;
    default:
      return ILI9341_WHITE;
  }
}

String GetDayOfWeekString(int DayOfWeek) {
  switch (DayOfWeek) {
    case 1:
      return "Monday";
    case 2:
      return "Tuesday";
    case 3:
      return "Wednesday";
    case 4:
      return "Thursday";
    case 5:
      return "Friday";
    case 6:
      return "Saturday";
    case 7:
      return "Sunday";
    default:
      return "Unknown";
  }
}