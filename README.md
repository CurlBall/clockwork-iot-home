# clockwork-iot-home
## Ideas
- Almanac
- Daily/Monthly/Yearly Reminders
- Holy shit, a virtual keyboard?

## Requirements (Wio)
I don't like it, but I'm gonna have to go along with it!

### Functional Requirements
- R1: The system shall always display the time
- R2: The system shall display drastic changes in weather conditions
- R3: Time sensitive information shall be showed as the system's default state <!-- I actually don't believe in requirements. SRS requirements seem sillily unspecific and unspecific at the same time. Maybe I'm forgetting something. -->
- R4: The system shall provide a customizable and scheduled timer.
- R5: The system shall provide an alarmclock.
- R6: The system shall display the ambient temperature and humitidy.
- R7: The system shall warn the user of high CO2 levels.
- R8: The system shall remind the user of regularly occuring chores.


### Non-Functional Requirements
- R3: User input should not take longer than 30 ms to register

### Constraints:
- Millis will reset after ~50 days
- The system is powered by battery, and needs to be recharged.

### Assumptions
- 
