# pragma once
# include <ctime>

class Flight
{
    private:
        int flightID;
        time_t flightTime;

        void initFlightTime(int pHour, int pMinutes) {
            flightTime = time(NULL);
            tm *currentTime = localtime(&flightTime);
            flightTime -= (currentTime->tm_hour * 3600);
            flightTime -= (currentTime->tm_min * 60);
            flightTime -= (currentTime->tm_sec);
            flightTime += (pHour*3600) + (pMinutes*60);
        }

    public: 
        Flight(int pID, int pHour, int pMinutes) {
            flightID = pID;
            initFlightTime(pHour, pMinutes);
        }

        int getFlightID() {
            return flightID;
        }

        char* flightTimeString() {
            char result[25];
            char* ptrResult = result;
            tm* currentTime = localtime(&flightTime);
            strftime(result, 25, "%a-%d %b %I:%M %p %Y", currentTime);
            return ptrResult;
        }

        int getTimeValue() {
            tm* currentTime = localtime(&flightTime);
            int result = (currentTime->tm_hour*3600) + (currentTime->tm_min*60);
            return result;
        }
};
