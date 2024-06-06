# Klåckwörk
## Ideas
- Almanac
  - Categorized roughly as small, normal or big events, which changes how far ahead in the future they are shown.
- Daily/Monthly/Yearly Reminders
- Holy shit, a virtual keyboard?
- Primitive PC application that is used for defining events and reminders, as well as changing some settings. Start with a console program. 

## Requirements (Wio)
I don't like it, but I'm gonna have to go along with it!

### Functional Requirements
- R1: The system shall always display the time.
- R2: The system shall display drastic changes in weather conditions.
- R3: Time sensitive information shall be showed as the system's default state. <!-- I actually don't believe in requirements. SRS requirements seem sillily unspecific and unspecific at the same time. Maybe I'm forgetting something. -->
- R4: The system shall provide a customizable and scheduled timer.
- R5: The system shall provide an alarmclock.
- R6: The system shall display the ambient temperature and humitidy.
- R7: The system shall warn the user of high CO2 levels.
- R8: The system shall remind the user of regularly occuring chores.
- R9: The system shall warn the user when it's battery is running out.


### Non-Functional Requirements
- NFR1: User input should not take longer than 30 ms to register.

### Constraints:
- C1: All internet communication must be encrypted and secure.

### Assumptions
- Millis will reset after ~50 days
- The system is powered by battery, and needs to be recharged.
- The system will spontaneously combust and cause a fire that will claim people's lives and cause major property damage.
- The system will exist in a world, with a lot of things, with a lot of API's. A lot of fun can be had, and wacky things can be achieved.  
