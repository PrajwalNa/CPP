/*
File: tournament.cpp
Header file: tournament.h
Version: 1.0
Date: 2023/10/15
Author: Prajwal Nautiyal
*/

# include "tournament.h"

namespace fast {

// Default constructor
Tournament::Tournament() {
    setEmpty();
}

// 3 argument constructor
Tournament::Tournament(const char* name, int noOfteam, const soccerTeam* soccer) {
    setTournament(name, noOfteam, soccer);
}

// Destructor
Tournament::~Tournament() {
    delete[] m_name;
    delete[] m_soccer;
    m_name = nullptr;
    m_soccer = nullptr;
}

// setter function
void Tournament::setTournament(const char* name, int noOfteam, const soccerTeam* soccer) {
    if (name != nullptr && noOfteam > 0) {
        m_name = new char[strlen(name) + 1];
        strcpy(m_name, name);
        m_num = noOfteam;
        m_soccer = new soccerTeam[noOfteam];
        for (int i = 0; i < noOfteam; i++) {
            m_soccer[i] = soccer[i];
        }
    }
    else{
        setEmpty();
        }
}

// return true if the object is not empty
bool Tournament::isEmpty() const { // return true if the object is not empty
    return (m_name != nullptr && m_num > 0 && m_soccer != nullptr);
}

// set the object to empty state
void Tournament::setEmpty() {
    m_name = nullptr;
    m_num = 0;
    m_soccer = nullptr;
}

// match function
Tournament& Tournament::match(const soccerTeam* ls) {
    if (isEmpty() && ls != nullptr) {
        if (calcFine == 0.0 && calcFoul == 0) {
                calcFine = ls[1].m_fines;
                calcFoul = ls[1].fouls();
            }
        if (ls[0].fouls() < calcFoul) {
            if (calcFoul >= MAX_FOUL) {
                calcFoul = -23;
            }
            else {
                calcFoul = calcFoul * 2;
            }
            m_soccer[1].setFine(calcFine, calcFoul);
            m_soccer[1].calFines();
            calcFine = m_soccer[1].m_fines;
            goal += 1;
            m_soccer[0].m_goals = goal;
        }
    }
    return *this;
}

// display function, display the tournament details and return the ostream object
std::ostream& Tournament::display() const {
    std::ostream& os = std::cout;
    if (isEmpty()) {
        os << "Tournament: " << m_name << std::endl;
        os << "Number of teams: " << m_num << std::endl;
        os << "list of the teams:" << std::endl;
        os.width(45);
        os << "Fines";
        os.width(10);
        os << "Fouls";
        os.width(10);
        os << "Goals" << std::endl;
        for (int i = 0; i < m_num; i++) {
            os << "Team[" << i + 1 << "] :";
            m_soccer[i].display();
            os << std::endl;
        }
    }
    else {
        os << "Invalid Tournament!" << std::endl;
    }
    return os;
}

}