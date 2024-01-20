/*
File: soccerTeam.cpp
Header file: soccerTeam.h
Version: 1.0
Date: 2023/10/15
Author: Prajwal Nautiyal
*/

#include "soccerTeam.h"
using namespace std;

// set the struct object to empty state
void soccerTeam::setEmpty() {
    m_teamName[0] = '\0';
    m_noFouls = 0;
    m_fines = 0.0;
    m_goals = 0;
}

// return true if the object is not empty
bool soccerTeam::isEmpty() const {
    return (m_teamName[0] != '\0' && m_noFouls >= 0 && m_fines >= 0.0);
}

// set the struct object to the values of the parameter
void soccerTeam::setTeam(const soccerTeam& team) {
    setName(team.m_teamName);
    m_noFouls = team.m_noFouls;
    m_fines = team.m_fines;
}

// set the name of the team
void soccerTeam::setName(const char* tname) {
    strncpy(m_teamName, tname, 40);
    m_teamName[40] = '\0';
}

// sets the number of fouls and fines
void soccerTeam::setFine(double fines, int foul) {
    if (fines >= 0.0 && foul >= 0){
        m_fines = fines;
        m_noFouls = foul;
    }
    else{
        setEmpty();
    }
}

// calculates the fines
void soccerTeam::calFines() {
    m_fines += m_fines * 0.2;
}

// returns the number of fouls
int soccerTeam::fouls() const {
    return m_noFouls;
}

// displays the team name, fines, number of fouls and goals
std::ostream& soccerTeam::display()const{
    std::ostream& disp=std::cout; //making an object if class ostream called print
    if (isEmpty()){
        disp.width(30);
        disp << std::left << m_teamName;
        disp << std::right;
        disp.width(6);
        disp.setf(ios::fixed);
        disp.precision(2);
        disp << m_fines;
        disp.unsetf(ios::fixed);
        disp.width(6);
        disp << m_noFouls;
        disp.width(10);
        disp << m_goals;
        disp << (m_goals > 0 ? "w" : "");
    }

    else{
        disp << "Invalid Team!" << endl;
    }
    return disp;
}

// default constructor
soccerTeam::soccerTeam() {
    setEmpty();
}

// 3 argument constructor
soccerTeam::soccerTeam(const char* tname, double fines, int foul) {
    setName(tname);
    m_fines = fines;
    m_noFouls = foul;
    m_goals = 0;
}