#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include "Utilities.h"
#include "LineManager.h"

using namespace std;

LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
{
    // Temp Utilities object (use for tokenizing).
    Utilities utils;
    // Opening file.
    ifstream assemblyFile(file);

    // Handling problem with opening the file.
    if (!assemblyFile.is_open())
    {
        throw std::string("Unable to open file.");
    }

    // Record temp string.
    string record;

    // Getting records.
    while (std::getline(assemblyFile, record))
    {
        if (!record.empty())
        {
            // Beggining token extraction.
            size_t pos = 0;
            bool more = true;
            // Current and next stations.
            string nextStation;
            string currentStation = utils.extractToken(record, pos, more);

            if (more)
            {
                nextStation = utils.extractToken(record, pos, more);
            }

            // Creating instances for current and next objects.
            Workstation* currentWS = nullptr;
            Workstation* nextWS = nullptr;

            // Boolean functionalities to match.
            auto findCurrentWS = std::find_if(stations.begin(), stations.end(), [&](Workstation* ws)
                {
                    return ws->getItemName() == currentStation;
                });

            auto findNextWS = std::find_if(stations.begin(), stations.end(), [&](Workstation* ws)
                {
                    return ws->getItemName() == nextStation;
                });

            // Assigning workstations to empty instances.
            if (findCurrentWS != stations.end())
            {
                currentWS = *findCurrentWS;
            }

            if (findNextWS != stations.end())
            {
                nextWS = *findNextWS;
            }

            // Getting first station.
            if (m_activeLine.empty())
            {
                m_firstStation = currentWS;
            }

            // Updating.
            currentWS->setNextStation(nextWS);
            m_activeLine.push_back(currentWS);
        }
    }

    // Closing file.
    assemblyFile.close();
    // Updating orders (size).
    m_cntCustomerOrder = g_pending.size();
}

void LineManager::reorderStations()
{
    vector<Workstation*> newSt;
    Workstation* lastSt = nullptr;

    size_t count = 0u;

    while (count < m_activeLine.size())
    {
        //  Boolean for last station found (presuming false).
        bool foundLast = false;

        for (size_t i = 0u; i < m_activeLine.size() && !foundLast; i++)
        {
            // Reordering stations.
            if (m_activeLine[i]->getNextStation() == lastSt)
            {
                newSt.push_back(m_activeLine[i]);
                lastSt = m_activeLine[i];

                count++;
                foundLast = true;
            }
        }
    }

    // Reversing stations.
    reverse(newSt.begin(), newSt.end());

    // Setting first station.
    m_firstStation = newSt[0];
    m_activeLine = newSt;
}

bool LineManager::run(std::ostream& os)
{
    static size_t count = 0u;
    ++count;

    // Updated counter.
    os << "Line Manager Iteration: " << count << endl;

    // Moving order (removing from the queue).
    if (!g_pending.empty())
    {
        *m_firstStation += move(g_pending.front());
        g_pending.pop_front();
    }

    for (auto src : m_activeLine)
    {
        src->fill(os);
    }

    for (auto src : m_activeLine)
    {
        src->attemptToMoveOrder();
    }

    return m_cntCustomerOrder == g_completed.size() + g_incomplete.size();
}

void LineManager::display(std::ostream& os) const
{
    for (auto src : m_activeLine)
    {
        src->display(os);
    }
}