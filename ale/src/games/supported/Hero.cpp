/* *****************************************************************************
 * A.L.E (Arcade Learning Environment)
 * Copyright (c) 2009-2012 by Yavar Naddaf, Joel Veness, Marc G. Bellemare and 
 *   the Reinforcement Learning and Artificial Intelligence Laboratory
 * Released under the GNU General Public License; see License.txt for details. 
 *
 * Based on: Stella  --  "An Atari 2600 VCS Emulator"
 * Copyright (c) 1995-2007 by Bradford W. Mott and the Stella team
 *
 * *****************************************************************************
 */
#include "Hero.hpp"

#include "../RomUtils.hpp"


HeroSettings::HeroSettings() {

    reset();
}


/* create a new instance of the rom */
RomSettings* HeroSettings::clone() const { 
    
    RomSettings* rval = new HeroSettings();
    *rval = *this;
    return rval;
}


/* process the latest information from ALE */
void HeroSettings::step(const System& system) {

    // update the reward
    int score = getDecimalScore(0xB9, 0xB8, 0xB7, &system); 
    int reward = score - m_score;
    m_reward = reward;
    m_score = score;

    // update terminal status
    int lives = readRam(&system, 0xB3);
    m_terminal = lives == 0;
}


/* is end of game */
bool HeroSettings::isTerminal() const {

    return m_terminal;
};


/* get the most recently observed reward */
reward_t HeroSettings::getReward() const { 

    return m_reward; 
}


/* is an action legal */
bool HeroSettings::isLegal(const Action &a) const {

    switch (a) {
        case PLAYER_A_NOOP:
        case PLAYER_A_LEFT:
        case PLAYER_A_RIGHT:
        case PLAYER_A_UP:
        case PLAYER_A_DOWN:
        case PLAYER_A_FIRE:
            return true;
        default:
            return false;
    }   
}


/* reset the state of the game */
void HeroSettings::reset() {
    
    m_reward   = 0;
    m_score    = 0;
    m_terminal = false;
}


        
/* saves the state of the rom settings */
void HeroSettings::saveState(Serializer & ser) {
  ser.putInt(m_reward);
  ser.putInt(m_score);
  ser.putBool(m_terminal);
}

// loads the state of the rom settings
void HeroSettings::loadState(Deserializer & ser) {
  m_reward = ser.getInt();
  m_score = ser.getInt();
  m_terminal = ser.getBool();
}

