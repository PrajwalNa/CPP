//Tournament.h
# ifndef TOURNAMENT_H
# define TOURNAMENT_H
# include "soccerTeam.h"

namespace fast{

class Tournament{
    char* m_name;
    int m_num;
    soccerTeam* m_soccer=nullptr;
    int calcFoul = 0;
    double calcFine = 0.0;
    int goal = 0;

    public:
    Tournament();
    Tournament(const char* name, int noOfteam,const soccerTeam* soccer);
    ~Tournament();
    void setTournament(const char* name, int noOfteam,const soccerTeam* soccer);
    bool isEmpty() const;
    void setEmpty();
    Tournament& match(const soccerTeam* ls);
    std::ostream& display() const; 
    
};

}
#endif