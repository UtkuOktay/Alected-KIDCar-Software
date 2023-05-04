#ifndef DEBUG
long int _previous_time;
float function_time_ms;

#define measure_time(x) \
          _previous_time = micros(); \
          x; \
          function_time_ms = (micros() - _previous_time) / 1000.0;

#define print_time(x) \
      measure_time(x); \
      Serial.println(function_time_ms);
#endif
#define DEBUG