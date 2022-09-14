# pragma once
# include <iostream>
# include <random>
# include "Flight.hpp"
# include "../structs/Queue.hpp"
# include "../structs/PriorityQueue.hpp"

typedef std::default_random_engine randEngine;
typedef std::uniform_int_distribution<int> distribution;

class Airport
{
    private:
        int totalTracks;
        int totalFlights;
        PriorityQueue<Flight>* flightQueue;
        Queue<Flight>* queueTracks;

    public:
        Airport(int pTracks, int pFlights) {
            totalTracks = pTracks;
            totalFlights = pFlights;
            flightQueue = new PriorityQueue<Flight>;
            queueTracks = new Queue<Flight>[totalTracks];
        }

        void fillFlights(int pStartHour, int pEndHour) {
            randEngine generator(time(NULL));
            distribution hourRange(pStartHour, pEndHour-1);
            distribution delayRange(0, 17);
            distribution minRange(0,42);

            for (int count = 0; count < totalFlights; count++)
            {
                int randHour  = hourRange(generator);
                int randDelay = delayRange(generator);
                int randMin   = minRange(generator) + randDelay;

                Flight* newFlight = new Flight(count+1, randHour, randMin);
                flightQueue->enqueue(newFlight, newFlight->getTimeValue());
            }
        }

        void assignTracks() {
            int trackIndex = 0;
            while (! flightQueue->isEmpty()) {
                Flight* ptrFlight = flightQueue->dequeue();
                queueTracks[trackIndex].enqueue(ptrFlight);
                ++trackIndex %= totalTracks;
            }
        }

        void takeOff() {
            int pendingFlights = totalFlights;
            while (pendingFlights > 0) {
                int trackIndex = 0;
                Flight* ptrFlight;
                for (; trackIndex < totalTracks; trackIndex++) {
                    ptrFlight = queueTracks[trackIndex].dequeue();
                    pendingFlights--;
                    if (! pendingFlights) {
                        break;
                    }

                    std::cout << "-> " << ptrFlight->flightTimeString();
                    std::cout << "\tPista_" << trackIndex;
                    std::cout << " Vuelo #" << ptrFlight->getFlightID() << std::endl;
                }
            }
        }
};