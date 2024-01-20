//SoccerTeam.h
#include <iostream>
#include <cstring>
const int MAX_FOUL = 4; //maximum fouls allowed

struct soccerTeam{
    char m_teamName[41]; 
    int m_noFouls; 
    double m_fines; 
    int m_goals; 

    
    void setEmpty();
    bool isEmpty() const;
    void setTeam(const soccerTeam& team);
    void setName(const char* tname);
    void setFine(double fines, int foul); 
    void calFines(); 
    int fouls() const; 
    std::ostream& display()const; 

   
    soccerTeam(); 
    soccerTeam(const char* tname, double fines, int foul);
    
    
};